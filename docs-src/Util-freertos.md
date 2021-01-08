# Freertos

Resumo dos principais recursos do freertos utilizados no curso de computação embarcada.

> Referência extra consultar a API do freeRtos: https://www.freertos.org/a00106.html

## Dicas gerais

1. Faça o código por partes e DEBUG!! Não tente implementar tudo de uma única vez.
1. Leia a documentação!!
1. Antes de "sair fazendo" desenho no papel um diagrama do que pretende implementar.

## Interrupção

1. Toda interrupção de HW deve interagir com as tarefas via um dos recursos do RTOS (semáforo, fila, ...)
1. Todo recurso que for usado na interrupção (semáforo, fila) deve ser iniciado antes do uso!
1. Para interagir com o freeRTOS da interrupção, você deve usar as funcoes especificas que possuem `FromISR`.

## Criando uma tarefa

```c
 BaseType_t xTaskCreate(TaskFunction_t pvTaskCode,
                        const char * const pcName
                        configSTACK_DEPTH_TYPE usStackDepth,
                        void *pvParameters,
                        UBaseType_t uxPriority,
                        TaskHandle_t *pxCreatedTask
                       );
```

Método de como indicamos ao freertos de que uma tarefa deve ser criada (alocar memória, alocar no escalonador, ...).

- API: https://www.freertos.org/a00019.html

Para criarmos uma tarefa é necessário:

1. Criar uma função que será a task
    - Essa função não deve retornar `while(1)`
1. Chamar a função [`xTaskCreate`](https://www.freertos.org/a00125.html)
 
!!! example 

    ```c
    static void task_led(void *pvParameters){
      for (;;) {
        LED_Toggle(LED0);
        vTaskDelay(300);
      }
    }

    void main (void){ 
    
    // ---- hide code block ----
    
      if (xTaskCreate(task_led, "Led", 1024, NULL, 0, NULL) != pdPASS) {
        printf("Failed to create test led task\r\n");
      }
      
    }
    ```

??? tip "parâmetros xTaskCreate"
    - par0: ponteiro para a função que será uma task
    - par1: uma string para nomear a task
    - par2: tamanho da stack reservado para a task
    - par3: se desejar passar alguma informação na criação da task 
    - par4: prioridade 
    - par5: um handler da tarefa, normalmente `NULL`

## vTaskDelay

```c
void vTaskDelay( const TickType_t xTicksToDelay );
```

É uma função de delay do próprio RTOS que faz a tarefa em questão entrar em estado `bloqueada`, ou seja, não será chamada pelo escalonador do sistema operacional. 

Esse método possui avantagem de 'não ocupar' processamento do CORE. O tempo especificado para a função é a quantidade em ticks na qual a task ficara bloqueada. 

- API: https://www.freertos.org/a00127.html 

!!! example 
    ```c
    void vTaskFunction( void * pvParameters ){
      
      // inicializa LED1
      init_led1();
    
      /* Block for 500ms. */
      const TickType_t xDelay = 500 / portTICK_PERIOD_MS;

      for( ;; ){
          /* Simply toggle the LED every 500ms, blocking between each toggle. */
          vToggleLED();
          vTaskDelay( xDelay );
      }
    }
    ```
    
    - `const TickType_t xDelay = 500 / portTICK_PERIOD_MS;` converte ticks para ms.
    
## Semáforo binário

![](https://www.freertos.org/fr-content-src/uploads/2018/07/binary-semaphore.gif)

Semáforos são utilizados para sincronização de tarefas, eles podem ser 'liberados' por outra tarefa ou de uma interrupção. Eles devem ser utilizados como substituto a flag.

- Descrição: https://www.freertos.org/Embedded-RTOS-Binary-Semaphores.html
- API: https://www.freertos.org/a00113.html

Para criarmos e usarmos um semáforo é necessário:

  1. criar a variável global que representará o semáforo
      - `SemaphoreHandle_t xSemaphore;`
  1. criar o semáforo 
      - [`xSemaphoreCreateBinary();`](https://www.freertos.org/xSemaphoreCreateBinary.html)
  1. liberar o semáforo
      - [`xSemaphoreGiveFromISR(xSemaphore, 0);`](https://www.freertos.org/a00124.html) (se for liberado de uma ISR)
      - [`xSemaphoreGive(xSemaphore);`](https://www.freertos.org/a00123.html) (se for liberado de outra task)

  1. esperar pelo semáforo
      - [`xSemaphoreTake(xSemaphore, 500)`](https://www.freertos.org/a00122.html)

!!! example
    ```c
    
    // variável global que é o endereço 
    // do semáforo  
    SemaphoreHandle_t xSemaphore;
    
    void but_callback(void){
      // libera semáforo 
      xSemaphoreGiveFromISR(xSemaphore, 0);
    }
    
    static void task_led(void *pvParameters){
      init_led1();   // inicializa LED1
      init_but1();   // inicializa botao 1, com callback
      
      // cria semáforo binário
      xSemaphore = xSemaphoreCreateBinary();

      // verifica se semáforo foi criado corretamente
      if (xSemaphore == NULL)
          printf("falha em criar o semaforo \n");

      for (;;) {
          // aguarda por até 500 ms pelo se for liberado entra no if
          if( xSemaphoreTake(xSemaphore, 500 / portTICK_PERIOD_MS) == pdTRUE ){
            LED_Toggle(LED0);
          }
        }
    }
    ```
!!! tip
    1. O semáforo deve ser sempre alocado antes do seu uso, caso alguma parte do firmware tente liberar o semáforo antes dele ser criado (`xSemaphoreCreateBinary()`) o código irá travar.
    1. Você deve usar `fromISR` SEMPRE que liberar um semáforo de uma interrupção, caso contrário usar a função `xSemaphoreGive()`


## fila

![](https://www.freertos.org/fr-content-src/uploads/2018/07/queue_animation.gif)

Fila é um recurso do freertos que permite troca de mensagens (qualquer tipo de dado) entre tarefas e entre IRQ e tarefas.

- Descrição: https://www.freertos.org/Embedded-RTOS-Queues.html
- API: https://freertos.org/a00018.html

!!! example
    
    Cria uma fila de chars, e cada botão envia para essa fila uma
    informação referente ao seu id. Uma task fica lendo essa fila e aciona o LED referente ao ID do botão.
    
    ```c
    // fila
    QueueHandle_t xQueueButId;
    
    void but1_callback(void){
      // envia o char `1` na fila
      char id = `1`;
      xQueueSendFromISR(xQueueButId, &id, 0);
    }
    
    void but2_callback(void){
      // envia o char `2` na fila
      char id = `2`;
      xQueueSendFromISR(xQueueButId, &id, 0);
    }

    static void task_led(void *pvParameters){
      // cria fila de 32 slots de char
      xQueueButId = xQueueCreate(32, sizeof(char) );
      
      // verifica se fila foi criada corretamente
      if (xQueueButId == NULL)
          printf("falha em criar a fila \n");

      init_led1();   // inicializa LED1
      init_but1();   // inicializa botao 1, com callback
      init_but2();   // inicializa botao 2, com callback
      
      // variável local para leitura do dado da fila
      char id;

      for (;;) {
          // aguarda por até 500 ms pelo se for liberado entra no if
          if( xQueueReceive( xQueueButId, &id, ( TickType_t ) 500 )){
            
            if(id == 1)
              LED_Toggle(LED1);
            else if(id == 2)
              LED_Toggle(LED2);
          }
        }
    }
    ```
