#  RTOS - ADC

Nesse lab iremos trabalhar com conversão analógica digital e LCD.

!!! note "Preencher ao finalizar o lab"
    <iframe src="https://docs.google.com/forms/d/e/1FAIpQLScqWmljztbSRUTnal07ZktmgSp2qv_cvhJlGzFz3eUzeAK7Ug/viewform?embedded=true" width="700" height="520" frameborder="0" marginheight="0" marginwidth="0">Carregando…</iframe>

## LAB

| Pasta           |
|-----------------|
| `Labs/RTOS-ADC` |

1. Executar demo de ADC
1. Trazer o exemplo para dentro do RTOS-LCD
1. Estruturar tasks
1. Criar `mailbox` de comunicação entre IRQ e tasks
1. Desenhar no display potenciômetro 

### Início

!!! note "Conexão"
     - EXT2: LCD
     - EXT1: Potenciômetro no PC31, conforme exemplo [`SAME70-examples/Perifericos-uC/AFEC-Pin/`](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/AFEC-Pin)
     
!!! warning "Código exemplo"
    - Copie o código exemplo [`SAME70-examples/Screens/RTOS-LCD-maxTouch-Fontes`](https://github.com/Insper/SAME70-examples/tree/master/Screens/RTOS-LCD-maxTouch-Fontes) para a pasta da entrega do seu repositório `Labs/RTOS-ADC`
    - Vamos modificar esse código exemplo.
    
### Exemplo AFEC

Abra o exemplo do AFEC-Pin, localizado em [`SAME70-examples/Perifericos-uC/AFEC-Pin/`](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/AFEC-Pin), leia o README desse exemplo e o execute na sua placa. 

Note que será necessário conectar o potenciômetro ao kit.

### Incorporando AFEC ao RTOS

Vamos incorporar o exemplo do AFEC ao RTOS, iremos criar uma tarefa que será responsável por ler o valor do AFEC.

!!! example "Modifique"
    1. Adicione no ASF o driver do `AFEC`
    1. Traga as funções, defines e variáveis globais do exemplo `AFEC-PIN`
        - variáveis globais: `g_`
        - `defines`
        - `config_afec`
        - `AFEC_pot_Callback()`
    1. Compile o código para ver se está ok
    
Agora vamos criar uma task no RTOS para lidar com a leitura do AFEC, a tarefa tem a estrutura a seguir:

```c

void task_adc(void){
  
  /* inicializa e configura adc */
  config_AFEC_pot(AFEC_POT, AFEC_POT_ID, AFEC_POT_CHANNEL, AFEC_pot_Callback);
  
  /* Selecina canal e inicializa conversão */
  afec_channel_enable(AFEC_POT, AFEC_POT_CHANNEL);
  afec_start_software_conversion(AFEC_POT);
  
  while(1){
    if(g_is_conversion_done){
      printf("%d\n", g_ul_value);
      vTaskDelay(500);
      
      /* Selecina canal e inicializa conversão */
      afec_channel_enable(AFEC_POT, AFEC_POT_CHANNEL);
      afec_start_software_conversion(AFEC_POT);
    }
  }
}
```

Note que a única coisa que eu mudei dessa task para a parte do exemplo que lidava com o AFEC foi que alterei a função `delay_ms` para a função de delay do rtos: `vTaskDelay`. Agora é necessário inicializar essa task no RTOS, no main:

```c
  /* Create task to handler LCD */
  if (xTaskCreate(task_adc, "adc", TASK_LCD_STACK_SIZE, NULL, TASK_LCD_STACK_PRIORITY, NULL) != pdPASS) {
    printf("Failed to create test adc task\r\n");
  }
```

!!! example "Modifique"
    1. Crie a task `task_adc`
    1. Inicialize a task no `RTOS`
    1. Abra o terminal e note que está funcionando!
    
!!! warning
    Essa task continua usando uma flag que é alterada do callback do AFEC para indicar quando o valor está pronto, isso não é bom e vamos mudar mais para frente!

### mailbox - `queue`

Mailbox/ `queue` é uma das maneiras de enviarmos dados em um sistema operacional, com ele podemos comunicar interrupção com tarefa e tarefa com tarefa. Vamos modificar o código criando um fila para comunicar a tarefa `task_adc` com a tarefa `task_lcd`.

!!! note
    > Queues are the primary form of intertask communications. They can be used to send messages between tasks, and between interrupts and tasks. In most cases they are used as thread safe FIFO (First In First Out) buffers with new data being sent to the back of the queue, although data can also be sent to the front. 
    
    ![](https://www.freertos.org/wp-content/uploads/2018/07/queue_animation.gif)
    
    > Writing to and reading from a queue. In this example the queue was created to hold 5 items, and the queue never becomes full.
    
    Material retirado do site: https://www.freertos.org/Embedded-RTOS-Queues.html

!!! tip
    Para mais informações ler o site do freeRTOS sobre filas:
    
    - https://www.freertos.org/Embedded-RTOS-Queues.html
    - https://freertos.org/a00018.html 
    
    


Vamos criar um `queue` chamado de `xQueueADC`, essa variável deve ser global:

```diff
/************************************************************************/
/* RTOS                                                                  */
/************************************************************************/
#define TASK_MXT_STACK_SIZE            (2*1024/sizeof(portSTACK_TYPE))
#define TASK_MXT_STACK_PRIORITY        (tskIDLE_PRIORITY)

#define TASK_LCD_STACK_SIZE            (2*1024/sizeof(portSTACK_TYPE))
#define TASK_LCD_STACK_PRIORITY        (tskIDLE_PRIORITY)

typedef struct {
  uint x;
  uint y;
} touchData;

QueueHandle_t xQueueTouch;

+typedef struct {
+  uint value;
+} adcData;

+QueueHandle_t xQueueADC;
```

Agora modifique a tarefa `task_lcd` para alocar uma fila nesse "endereço", vamos também criar uma variável local da task chamada de `adc` para recebimento de dados dessa fila, e imprimir na tela o resultado:


```diff
void task_lcd(void){
  xQueueTouch = xQueueCreate( 10, sizeof( touchData ) );
+  xQueueADC   = xQueueCreate( 5, sizeof( adcData ) );

  // inicializa LCD e pinta de branco
  configure_lcd();
  draw_screen();

  // strut local para armazenar msg enviada pela task do mxt
  touchData touch;
+  adcData adc;
  
  while (true) {
    if (xQueueReceive( xQueueTouch, &(touch), ( TickType_t )  100 / portTICK_PERIOD_MS)) {
      printf("Touch em: x:%d y:%d\n", touch.x, touch.y);
    }
    
+    // Busca um novo valor na fila do adc!
+    // formata
+    // e imprime no LCD o dado
+    if (xQueueReceive( xQueueADC, &(adc), ( TickType_t )  100 / portTICK_PERIOD_MS)) {
+      char b[512];
+      sprintf(b, "%04d", adc.value);
+      font_draw_text(&arial_72, b, 50, 200, 2);
+    }
  }
}
```

!!! note
    Note que essa task já faz uso de uma outra fila chamada de `xQueueTouch`, ela serve para recebimento de informações do touch screen entre a `task_lcd` e a tarefa que faz a leitura do touch `task_mxt`.
    
Agora precisamos modificar a `task_adc` para enviar o dado por essa fila:

```diff
void task_adc(void){
  
  /* inicializa e configura adc */
  config_AFEC_pot(AFEC_POT, AFEC_POT_ID, AFEC_POT_CHANNEL, AFEC_pot_Callback);
  
  /* Selecina canal e inicializa conversão */
  afec_channel_enable(AFEC_POT, AFEC_POT_CHANNEL);
  afec_start_software_conversion(AFEC_POT);
  
+  adcData adc;
  
  while(1){
    if(g_is_conversion_done){
      printf("%d\n", g_ul_value);
      
+     adc.value = g_ul_value;
+     xQueueSend(xQueueADC, &adc, 0);

      vTaskDelay(500);
      
      /* Selecina canal e inicializa conversão */
      afec_channel_enable(AFEC_POT, AFEC_POT_CHANNEL);
      afec_start_software_conversion(AFEC_POT);
    }
  }
}
```

### semáforo 

Agora vamos modificar o código para usar um semáforo para substituir a flag: `g_is_conversion_done`, esse semáforo precisa ser liberado na `AFEC_pot_Callback` e recebido na `task_adc`.

!!! example "Modifique"
    - substitua a flag `g_is_conversion_done` por um semáforo.

!!! warning ""
    Até aqui é C

## B - Dado direto do IRQ AFEC para a task_lcd

Podemos fazer o envio do dado direto do `AFEC_pot_Callback` para a `task_lcd`, para isso teremos que usar a função [`xQueueSendFromISR`](https://freertos.org/a00119.html) no lugar da `xQueueSend`.

##  A

Faça a exibição do potenciômetro de forma gráfica no LCD, use as funções de desenho que está disponível:

```c
void ili9488_draw_line(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2);
void ili9488_draw_rectangle(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2);
void ili9488_draw_filled_rectangle(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2);
uint32_t ili9488_draw_circle(uint32_t ul_x, uint32_t ul_y, uint32_t ul_r);
uint32_t ili9488_draw_filled_circle(uint32_t ul_x, uint32_t ul_y, uint32_t ul_r);
```

Se for apenas uma barra é B, se for algo mais 'bonito' é A

