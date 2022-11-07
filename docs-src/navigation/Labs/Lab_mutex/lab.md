# LAB - Mutex

Neste laboratório iremos trabalhar usar mutex no freertos para controlar o acesso ao LVGL entre múltiplas tasks. 

## Lab    

| Exemplo base         |               | LAB               |
|----------------------|---------------|-------------------|
| `Lab8-RTOS-LCD-LVGL` | :arrow_right: | `Lab9-RTOS-Mutex` |


!!! warning "Código exemplo"
    - Vamos modificar o código exemplo do laboratório passado, tudo bem se você não terminou de implementar todas as funcionalidades. Faça uma cópia para o seu repositório de laboratórios renomeando para `Lab9-RTOS-Mutex`.

## Mutexes

!!! info
    Sim... sim.. o mesmo mutex de sistema hardware software (`lock` e `unlock`): https://insper.github.io/SistemasHardwareSoftware/aulas/20-sincronizacao/

!!! tip
    Mutex vem de 'MUT'ual 'EX'clusion ou exclusão mútua, a ideia é para ser usado como um bastão, que indica que o recurso está em uso por outra parte do programa.

O LVGL **não é thread-safe by default**, como indicado na página:

- https://docs.lvgl.io/master/porting/os.html

Isso significa que não podemos chamar uma função do LVGL enquanto a anterior não tiver terminado de executar, e caso implementemos o acesso ao LCD em várias partes do nosso programa corremos grande risco disso acontecer (lembrem que o RTOS interrompe uma tarefa para permitir que outra execute, e isso pode ser no meio da função por exemplo de mudar o valor do label).

A documentação do LVGL fala o seguinte:

> If you need to use real tasks or threads, you need a mutex which should be invoked before the call of `lv_timer_handler` and released after it. Also, you have to use the same mutex in other tasks and threads around every LVGL (`lv_...`) related function call and code. This way you can use LVGL in a real multitasking environment. Just make use of a mutex to avoid the concurrent calling of LVGL functions.
> 
> Here is some pseudocode to illustrate the concept:
>   ```c
>   static mutex_t lvgl_mutex; // (1)

>   void lvgl_thread(void)
>   {
>       while(1) {
>           mutex_lock(&lvgl_mutex); // (2)
>           lv_task_handler();
>           mutex_unlock(&lvgl_mutex); // (3)
>           thread_sleep(10); /* sleep for 10 ms */
>       }
>   }

>   void other_thread(void)
>   {
>       /* You must always hold the mutex while using LVGL APIs */
>       mutex_lock(&lvgl_mutex); 
>       lv_obj_t *img = lv_img_create(lv_scr_act());
>       mutex_unlock(&lvgl_mutex);

>       while(1) {
>           mutex_lock(&lvgl_mutex);
>           /* change to the next image */
>           lv_img_set_src(img, next_image);
>           mutex_unlock(&lvgl_mutex);
>           thread_sleep(2000);
>       }
>   }
>   ```
>
> 1. Cria mutex, vamos ter que usar o do freertos
> 1. Indica que o recurso está em uso
> 1. Indica a liberacão do recurso

### Prioridades e Mutex

Imaginem o cenário a seguir: Uma tarefa de baixa prioridade (L) requisita um mutex que está livre, no meio da execução uma tarefa de alta prioridade (H) é colocada para executar pelo escalonador e está tarefa necessita do mesmo mutex que a anterior. O que acontece? ==Pânico no sistema== tudo trava? Não! O escalonador vai permitir que a de baixa execute e a de alta não vai executar pois está esperando o mutex. Isso chama ==inversão de prioridade==.


#### Inversão de prioridade

Inversão de prioridade é uma "consequência" que acontece quando uma tarefa de alta prioridade está aguardando um recurso que não foi liberado por uma tarefa de menor prioridade, o RTOS vai manter a tarefa de baixa prioridade executando, impedindo a de alta de executar (o que não é muito desejado). O negócio começa a ficar mais complicado quando incluímos uma tarefa de média prioridade na jogada, que pode impedir a de baixa e a de alta de executar, travando o sistema:

![](https://www.digikey.com.br/maker-media/92b5e015-d9fc-4940-9a48-f814d06c5f31)

- Acesse o link a seguir para entender mais a respeito:  https://www.digikey.com.br/en/maker/projects/introduction-to-rtos-solution-to-part-11-priority-inversion/abf4b8f7cd4a4c70bece35678d178321

!!! info
    A inversão de prioridade quase colocou fim no *Rover Pathfinder* da NASA que pousou em marte em 1997, uma inversão de prioridade fazia com que o sistema parasse de funcionar, só voltando a operar quando o **Watchdog Timer** do sistema reiniciava o robô. Engenheiros do RTOS usado no robô, o VxWorks, trabalharam horas na réplica em terra do mesmo a fim de identificar o problema, depois de muito depurar o projeto eles conseguiram descobrir o causador do problema, um mutex.
    
    Para saber mais a respeito, acesse: http://www.cs.cornell.edu/courses/cs614/1999sp/papers/pathfinder.html

### mutex no freeRtos

O mutex no FreeRTOS é como um semáforo binário, com uma única diferença: implementa herança prioritária (*priority inheritance*), que tenta minimizar os efeitos da inversão de prioridade. Este mecanismo faz com que a tarefa de baixa prioridade herde temporariamente a prioridade da tarefa de alta que necessita do recurso, ou seja, a tarefa de prioridade baixa, passa a ter alta prioridade até liberar o recurso.

![](https://www.freertos.org/fr-content-src/uploads/2018/07/mutexes.gif)

!!! info
    A solução para o Rover que foi para Marte foi a de ativar o mecanismo de herança prioritária no mutex que estava dando o problema.
    
    > When created, a VxWorks mutex object accepts a boolean parameter that indicates whether priority inheritance should be performed by the mutex. The mutex in question had been initialized with the parameter off; had it been on, the low-priority meteorological thread would have inherited the priority of the high-priority data bus thread blocked on it while it held the mutex, causing it be scheduled with higher priority than the medium-priority communications task, thus preventing the priority inversion. Once diagnosed, it was clear to the JPL engineers that using priority inheritance would prevent the resets they were seeing. 

### Exemplo 

A seguir um exemplo de mutex adaptado do livro do freertos. No caso a task1 necessita utilizar o printf e para isso requisita o mutex, após o uso a task libera o mutex permitindo que outra task utilize o printf.

```c
SemaphoreHandle_t xMutex;


void task1() {

  while(1) {
  
    /* Attempt to take the mutex, blocking indefinitely to wait for the mutex if
    it is not available straight away. The call to xSemaphoreTake() will only
    return when the mutex has been successfully obtained, so there is no need
    to check the function return value. If any other delay period was used then
    the code must check that xSemaphoreTake() returns pdTRUE before accessing
    the shared resource (which in this case is standard out). As noted earlier
    in this book, indefinite time outs are not recommended for production code. */
    xSemaphoreTake( xMutex, portMAX_DELAY );

    /* The following line will only execute once the mutex has been successfully
    obtained. Standard out can be accessed freely now as only one task can
    have the mutex at any one time. */
    printf( "%s", "Ola 1" ); // (1)
    fflush( stdout );

    /* The mutex MUST be given back! */
    xSemaphoreGive( xMutex );

    vTaskDelay(100);
  }
    
}

void task2() {

  while(1) {
  
    xSemaphoreTake( xMutex, portMAX_DELAY );
    printf( "%s", "Ola 2" ); // (2)
    fflush( stdout );
    xSemaphoreGive( xMutex );

    vTaskDelay(100);
  }

}

void main() {
  
   xMutex = xSemaphoreCreateMutex();

   // ....
}
```

1. Região crítica de compartilhamento de recursos.
2. Região crítica de compartilhamento de recursos.

!!! tip 
    Meio ruim ter que ficar utilizando o mutex toda hora que for realizar um printf, a solução para isso é encapsularmos em uma função o uso do mutex e usamos essa função no lugar do printf:
    
    ```c
    void printfMutex(char *s) {
      xSemaphoreTake( xMutex, portMAX_DELAY );
      printf( "%s", pcString );
      fflush( stdout );
      xSemaphoreGive( xMutex );
    }
    
    void task1() {
      while(1) {
        printfMutex("olá 1");
        vTaskDelay(100);
      }
    }
    
    void task2() {
      while(1) {
        printfMutex("olá 2");
        vTaskDelay(100);
      }
    }
    ```

## Programando

Agora vamos começar a programar, lembrem que a documentação do LVGL fala que: *If you need to use real tasks or threads, you need a mutex which should be invoked before the call of `lv_timer_handler` and released after it.*.

!!! info ""
    Como estamos no RTOS estamos usando a funcão `lv_task_handler` no lugar da `lv_timer_handler`.

!!! exercise "Task mutex `lv_task_handler`"
    
    1. Crie a variável global que irá servir de mutex chamado de `xMutexLVGL` do tipo `SemaphoreHandle_t`
    1. No main crie o mutex  com `xSemaphoreCreateMutex();`
    1. Na `task_lcd` faça a requisição do mutex antes de chamar `lv_tick_inc` e a liberação depois do `lv_task_handler`
    
    Execute o código e verifique que ==NADA DEVE TER MUDADO==. Estamos apenas melhorando a qualidade do nosso código e garantindo que não teremos erros futuros.
    
!!! note "Preencher ao finalizar o lab"

   <iframe src="https://docs.google.com/forms/d/e/1FAIpQLSfeZBEEZDfJPwbbelD1uf3iBFlt1B-yS0HP4X90TwejCbcMtw/viewform?embedded=true" width="640" height="320" frameborder="0" marginheight="0" marginwidth="0">Carregando…</iframe>
    
## APS 2

Este laboratório serve para ajudar vocês com a APS2, agora podem ter mais de uma task atualizando partes diferentes do LCD via LVGL, lembrem apenas de requisitar o mutex antes e liberar depois de terem usado. 
