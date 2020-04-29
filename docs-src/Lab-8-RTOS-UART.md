# RTOS - UART

![Camelos](imgs/RTOS-UART/camelos.png){width=100%}

Nesse lab iremos trabalhar com comunicação UART (aquela do terminal / printf). Praticando RTOS (queue)
    
## Lab    

| LAB                |
|--------------------|
| `Labs/8-RTOS-UART` |

### Início 

!!! warning "Código exemplo"
    - Vamos modificar o [lab-RTOS](https://github.com/Insper/SAME70-examples/tree/master/RTOS/RTOS-LED) (aquele dos leds e botões), faça uma cópia do seu lab para a nova pasta no seu seu repositório `Labs/8-RTOS-UART`

!!! note "Terminal"
    Esse exemplo faz uso da comunicação UART para debug de código (via printf), para acessar o terminal no atmel estúdio clique em:  :arrow_right: View :arrow_right: Terminal Window
    
    Configure o terminal para a porta que (COM) correta (verificar no windiows) e para operar com um BaudRate de `115200`.

Esse código exemplo já possui a comunicação UART configurada pela função (`configure_console`), essa função configura a utilização do periférico USART1 operando em modo de comunicação serial assíncrona. Os pinos `TX` e `RX` da comunicação serial são conectados ao EDGB, chip responsável pela gravação e debug do kit de desenvolvimento SAME70-XPLD.

A comunicação UART é um protocolo de comunicação muito utilizado para comunicação entre dois dispositivos ([`Machine-to-Machine`](https://en.wikipedia.org/wiki/Machine_to_machine m2m), é utilizado por exemplo no arduino para a gravação e debug (print), é utilizado por diversos equipamentos para comunicação e configuração (impressoras térmicas, máquinas de cartão de crédito, GPP, sensores de biometria, ...).

!!! note
    No nosso microcontrolador, temos dois periféricos capazes de realizar comunicação serial o `UART` e `USART`, nesse exemplo, utilizamos o `USART`.

Essa função configura o periférico `USART1` para operar como `stdio` do nosso código C, toda vez que invocamos a função `printf` a saída dos caracteres é enviada para o periférico e é serializado por ele.

!!! info
    Para mais detalhes de como o `stdio` faz o mapeamento para o periférico em questão, analise o include [`src/ASF/common/utils/stdio/stdio_serial/stdio_serial.h`](https://github.com/Insper/SAME70-examples/blob/master/RTOS/RTOS-LED/src/ASF/common/utils/stdio/stdio_serial/stdio_serial.h)
    
Vamos adicionar uma nova função (`USART1_init`) que faz praticamente a mesma coisa, porém configura a interrupção desse periférico. A interrupção ativada é para o recebimento de dados pela serial (`US_IER_RXRDY`), toda vez que um novo dado é recebido pela serial, o handler `USART1_Handler` é chamado. 

??? note "Outras interrupções do USART1"
    Outras interrupções suportadas pelo USART1:

    - RXRDY: RXRDY Interrupt Enable
    - TXRDY: TXRDY Interrupt Enable
    - OVRE: Overrun Error Interrupt Enable
    - FRAME: Framing Error Interrupt Enable
    - PARE: Parity Error Interrupt Enable
    - TIMEOUT: Time-out Interrupt Enable
    - TXEMPTY: TXEMPTY Interrupt Enable

### Preparando exemplo

Adicione as funções `USART1_init`, `usart1_puts` e o handler `USART1_Handler` ao exemplo.

??? example "`USART1_init`"
    ```c
    static void USART1_init(void){
      /* Configura USART1 Pinos */
      sysclk_enable_peripheral_clock(ID_PIOB);
      sysclk_enable_peripheral_clock(ID_PIOA);
      pio_set_peripheral(PIOB, PIO_PERIPH_D, PIO_PB4); // RX
      pio_set_peripheral(PIOA, PIO_PERIPH_A, PIO_PA21); // TX
      MATRIX->CCFG_SYSIO |= CCFG_SYSIO_SYSIO4;
    ```

      /* Configura opcoes USART */
      const sam_usart_opt_t usart_settings = {
          .baudrate       = 115200,
          .char_length    = US_MR_CHRL_8_BIT,
          .parity_type    = US_MR_PAR_NO,
          .stop_bits   	= US_MR_NBSTOP_1_BIT	,
          .channel_mode   = US_MR_CHMODE_NORMAL
      };
    
      /* Ativa Clock periferico USART0 */
      sysclk_enable_peripheral_clock(ID_USART1);
    
      stdio_serial_init(CONF_UART, &usart_settings);
    
      /* Enable the receiver and transmitter. */
      usart_enable_tx(USART1);
      usart_enable_rx(USART1);
    
      /* map printf to usart */
      ptr_put = (int (*)(void volatile*,char))&usart_serial_putchar;
      ptr_get = (void (*)(void volatile*,char*))&usart_serial_getchar;
    
      /* ativando interrupcao */
      usart_enable_interrupt(USART1, US_IER_RXRDY);
      NVIC_SetPriority(ID_USART1, 4);
      NVIC_EnableIRQ(ID_USART1);
    }
    ```

??? example "`USART1_Handler`"
    ```c
    void USART1_Handler(void){
      uint32_t ret = usart_get_status(USART_COM);

      BaseType_t xHigherPriorityTaskWoken = pdTRUE;
      char c;
    
      // Verifica por qual motivo entrou na interrupçcao?
      // RXRDY ou TXRDY
      
      //  Dados disponível para leitura
      if(ret & US_IER_RXRDY){
          usart_serial_getchar(USART1, &c);
          printf("%c", c);
    
      // -  Transmissoa finalizada
      } else if(ret & US_IER_TXRDY){
    
      }
    }
    ```

A função `usart1_puts` envia uma string para a serial pelo periférico USART1.

??? example "`usart1_puts`"
    ```c
    uint32_t usart1_puts(uint8_t *pstring){
        uint32_t i ;

        while(*(pstring + i))
            if(uart_is_tx_empty(USART1))
                usart_serial_putchar(USART1, *(pstring+i++));
    }
    ```

Edite o `main` para chamarmos a função `USART1_init` no lugar do `configure_console`:

```diff
int main(void)
{
	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Initialize the console uart */
-	configure_console();
+	USART1_init();
```

!!! example "Modifique"
    1. Inclua `USART1_init`
    1. Inclua `USART1_Handler`
    1. Inclua `usart1_puts`
    1. Substitua  `configure_console` por `USART1_init`


## Lab 

Agora com o exemplo preparado vamos implementar o firmware que foi desenvolvido em aula.

!!! tip ""
    diagrama feito em sala, enviado no teams

O usuário pode modificar os LEDs (recurso) de duas maneiras diferentes: enviando uma mensagem pela UART (terminal) ou apertando os botões da placa. Os botões e a UART servem como 'produtores' de comandos que serão processados por uma tarefa específica. 

A vantagem desse formato é: 

- a flexibilidade de criação de novos produtores (é fácil adicionar por exemplo uma segunda uart, ou uma outra comunicação), basta enviar os dados na fila de comandos; 
- o isolamento entre diferentes partes do firmware.


#### xQueueChar

Deve ser uma fila de caracteres, especificar um tamanho que caiba os comandos.

??? tip
    Criar na `task_uartRX`

#### USART1_handler

Irá receber um caracter da uart e colocar ele na fila `xQueueChar`

??? tip
    No `USART1_Handler` a função `usart_serial_getchar` pega um char da serial e salva em `c`. 
    
    - Você deve enviar esse dado na dila `xQueueChar`
    
    ```c
      //  Dados disponível para leitura
      if(ret & US_IER_RXRDY){
          usart_serial_getchar(USART_COM, &c);
          printf("%c", c);
    ```

#### task_uartRX

Ficará lendo a fila `xQueueChar` e montando uma string interna, quando detectado um `\n` envia a string para a fila `xQueueCommand`.

??? tip
    1. Criar um buffer de chars
    1. Ficar fazendo a leitura da fila `xQueueChar` e alimentando esse buffer
    1. Encontrado `\n`? Coloca NULL e envia o buffer para a fila `xQueueCommand`
    1. Começa tudo de novo

#### xQueueCommand

Uma fila de strings que representam comandos, você deve criar o seu protocolo de comandos. O comando deve ser capaz de inverter o valor dos leds.

- `led 3 toggle`: Inverte led 3  
- `led 1 toggle`: Inverte led 1

??? tip
    Criar na `task_execute`

#### task_execute

Tarefa que fica lendo a fila de comandos `xQueueCommand` e realizando os comandos que são enviados por ela.

#### task_led1, task_led2

Tarefas que controlam individualmente cada LED da placa OLED

!!! tip "Como validar tudo?"
    - Envie um comando pela UART e veja o LED mudar de status
    - Aperte o botão da placa OLED e veja o LED mudar de status

### B

Diagrama do firmware de como seria esse código caso a parte do LCD touch (`task_lcd` e `task_mxt`) fosse inserida nele, entrando como um novo produtor.

### A 

Comandos: `led x on` e `led x off`

- `led 1 on`: Acende led 1
- `led 2 off`: Apaga led 2
