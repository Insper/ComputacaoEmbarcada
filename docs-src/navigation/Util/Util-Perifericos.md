# 	Periféricos

Um pequeno resumo de como utilizar os periféricos do microcontrolador SAME70 no kit SAME70-XPLD.

- https://asf.microchip.com/docs/latest/search.html?device=same70 

## PIO - Parallel Input Output

| Exemplos                                                                                                |
| --------                                                                                                |
| [Perifericos-uC/PIO-IO/](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/PIO-IO)   |
| [Perifericos-uC/PIO-IRQ/](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/PIO-IRQ) |

### output

Use defines para facilitar:

``` c
// LED da placa
#define LED_PIO        PIOC
#define LED_PIO_ID     ID_PIOC
#define LED_IDX        8
#define LED_IDX_MASK   (1 << LED_IDX)
```

Configura o `PC8` como sendo output:

``` c
pmc_enable_periph_clk(LED_PIO_ID);
pio_configure(LED_PIO, PIO_OUTPUT_0, LED_IDX_MASK, PIO_DEFAULT);
```

Acionando o pino:

``` c
pio_set(LED_PIO, LED_IDX_MASK);   // coloca pino em 1
pio_clear(LED_PIO, LED_IDX_MASK); // coloca pino em 0
```

### input     

Use defines para facilitar:

``` c
//Defines dos botões
#define BUT_PIO 		PIOA
#define BUT_PIO_ID		ID_PIOA
#define BUT_IDX 		11
#define BUT_IDX_MASK	(1 << BUT_IDX)
```

Defina a função de callback:

``` c
//Callback da IRQ do botão
void but_callback(void){
    // ----------------------//
    // seu código vem aqui!  //
    // ----------------------//

}
```
    
Configura `PA11` com interrupção na borda de descida configurando a função `but_callback` 
para ser chamada sempre que acontece uma interrupção.

Esse exemplo ativa debounce de 60hz nesse pino.

``` c
pmc_enable_periph_clk(BUT_PIO_ID);
pio_configure(BUT_PIO, PIO_INPUT, BUT_IDX_MASK, PIO_PULLUP);
pio_handler_set(BUT_PIO, BUT_PIO_ID, BUT_IDX_MASK, PIO_IT_FALL_EDGE, but_callback);
pio_set_debounce_filter(LED_PIO, LED_IDX_MASK, 60);
pio_enable_interrupt(BUT_PIO, BUT_IDX_MASK);
pio_get_interrupt_status(BUT_PIO);
NVIC_SetPriority(BUT_PIO_ID, 4);
NVIC_EnableIRQ(BUT_PIO_ID);
```

Para ler o pino:

```c
uint32_t pin = pio_get(BUT_PIO, BUT_IDX_MASK);
```

- `pin > 0`: Pinos em `1`
- `pin = 0`: Pinos em `0`

## TC - Timer Counter

| Exemplos                                                                                              |
| --------                                                                                              |
| [Perifericos-uC/TC-IRQ/](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/TC-IRQ) |


| Biblioteca |
| ---------  |
| https://asf.microchip.com/docs/latest/same70/html/group__asfdoc__sam__drivers__tc__group.html           |

A família SAM E70 possui 3 TCs, cada TC possui 3 canais (0, 1 e 2):

|          | **CH0** |  **CH1**   | **CH2** |
| :------: | :-----: | :--------: | :-----: |
| **TC0:** | ID_TC0  |   ID_TC1   | ID_TC2  |
| **TC1**  | ID_TC3  |   ID_TC4   | ID_TC5  |
| **TC2**  | ID_TC6  | ==ID_TC7== | ID_TC8  |

!!! example ""
    Exemplo para configuração do TC2 - Canal 1 (==ID_TC7==) a 4 Hz


Defina a função Handler que será chamada quando ocorrer uma interrupção:

```C
void TC7_Handler(void){ 
	volatile uint32_t ul_dummy;
	ul_dummy = tc_get_status(TC2, 1); // ID_TC7 -> TC2 - Canal 1
	UNUSED(ul_dummy);
    
    // ----------------------//
    // seu código vem aqui!  //
    // ----------------------//
}
```

Defina a função `TC_init` que ajuda na configuração do TC

```c
void TC_init(Tc * TC, int ID_TC, int TC_CHANNEL, int freq){
	uint32_t ul_div;
	uint32_t ul_tcclks;
	uint32_t ul_sysclk = sysclk_get_cpu_hz();
	
	pmc_enable_periph_clk(ID_TC);

	tc_find_mck_divisor(freq, ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk);
	tc_init(TC, TC_CHANNEL, ul_tcclks | TC_CMR_CPCTRG);
	tc_write_rc(TC, TC_CHANNEL, (ul_sysclk / ul_div) / freq);

    NVIC_SetPriority(ID_TC, 4);
	NVIC_EnableIRQ((IRQn_Type) ID_TC);
	tc_enable_interrupt(TC, TC_CHANNEL, TC_IER_CPCS);
}
```

Chame a função quando for querer inicializar o TC

```C
int canal_ID_TC7 = 2; // Canal 2
int freq         = 4; // 4 Hz, a interrupção acontece 4 vezes por segundo

// Configura timer TC2, canal 1 
TC_init(TC2, ID_TC7, canal_ID_TC7, freq);

// Inicalize o TC
tc_start(TC, TC_CHANNEL);
```

!!! tip
    - Se quiser parar a contagem do TC `tc_stop(TC, TC_CHANNEL);`

## RTC - Real Time Counter

Defina o struct para ajudar

```c
typedef struct {
  uint32_t year;
  uint32_t month;
  uint32_t day;
  uint32_t week;
  uint32_t hour;
  uint32_t minute;
  uint32_t seccond;
} calendar
```

Configure o handler para ser chamado na interrupção

``` c
void RTC_Handler(void){
  uint32_t ul_status = rtc_get_status(RTC);

  // Instrução a ser executada quando a IRQ por SEGUNDO for ativada
  if ((ul_status & RTC_SR_SEC) == RTC_SR_SEC){
    rtc_clear_status(RTC, RTC_SCCR_SECCLR);

    // ----------------------//
    // seu código vem aqui!  //
    // ----------------------//
  }

  // Instrução a ser executada quando a IRQ por ALARME for ativada
  if ((ul_status & RTC_SR_ALARM) == RTC_SR_ALARM){ 
    rtc_clear_status(RTC, RTC_SCCR_ALRCLR);

    // ----------------------//
    // seu código vem aqui!  //
    // ----------------------//
  }

  rtc_clear_status(RTC, RTC_SCCR_ACKCLR);
  rtc_clear_status(RTC, RTC_SCCR_TIMCLR);
  rtc_clear_status(RTC, RTC_SCCR_CALCLR);
  rtc_clear_status(RTC, RTC_SCCR_TDERRCLR);
}
```

Declare a função de configuração do RTC

``` c
void RTC_init(Rtc *rtc, uint32_t id_rtc, calendar t, uint32_t irq_type){
  pmc_enable_periph_clk(ID_RTC);

  rtc_set_hour_mode(rtc, 0);
  rtc_set_date(rtc, t.year, t.month, t.day, t.week);
  rtc_set_time(rtc, t.hour, t.minute, t.seccond);

  NVIC_DisableIRQ(id_rtc);
  NVIC_ClearPendingIRQ(id_rtc);
  NVIC_SetPriority(id_rtc, 4);
  NVIC_EnableIRQ(id_rtc);

  rtc_enable_interrupt(rtc, irq_type);
}
```

=== "RTT com IRQ de segundos"

    ``` c
    calendar rtc_initial = {2020, 7, 10, 28, 15, 45 ,1};

    //RTC_IER_SECEN - IRQ por SEGUNDO
    RTC_init(RTC, ID_RTC, rtc_initial, RTC_IER_SECEN); 
    ```
    
=== "RTT com IRQ de segundos e alarme"

    ``` c
    calendar rtc_initial = {2020, 7, 10, 28, 15, 45 ,1};

    //RTC_IER_ALREN - IRQ por ALARME
    //RTC_IER_SECEN - IRQ por SEGUNDO
    RTC_init(RTC, ID_RTC, rtc_initial, RTC_IER_ALREN | RTC_IER_SECEN); 

    /* configura alarme do RTC */
    rtc_set_date_alarm(RTC, 1, rtc_initial.month, 1, rtc_initial.day);
    rtc_set_time_alarm(RTC, 1, rtc_initial.hour, 1, rtc_initial.minute, 1, rtc_initial.seccond + 10);
    ```
    
    Nesse exemplo uma alarme é configurado para +10 segundos após a inicialização.

## RTT - Real Time Timer

```C
void RTT_Handler(void)
{

  uint32_t ul_status;
  ul_status = rtt_get_status(RTT);
    
  // instrução a ser executada quando a IRQ por TICK (pllPreScale) for ativada
  if ((ul_status & RTT_SR_RTTINC) == RTT_SR_RTTINC) {
    // ----------------------//
    // seu código vem aqui!  //
    // ----------------------//
  }

  // instrução a ser executada quando a IRQ por ALARME for ativada
  if ((ul_status & RTT_SR_ALMS) == RTT_SR_ALMS) {
    // ----------------------//
    // seu código vem aqui!  //
    // ----------------------//
  } 
}
```

```c
static void RTT_init(uint16_t pllPreScale, uint32_t IrqNPulses)
{
    
  uint32_t ul_previous_time;

  /* Configure RTT for a 1 second tick interrupt */
  rtt_sel_source(RTT, false);
  rtt_init(RTT, pllPreScale);
  
  ul_previous_time = rtt_read_timer_value(RTT);
  while (ul_previous_time == rtt_read_timer_value(RTT));
  
  rtt_write_alarm_time(RTT, IrqNPulses+ul_previous_time);

  /* Enable RTT interrupt */
  NVIC_DisableIRQ(RTT_IRQn);
  NVIC_ClearPendingIRQ(RTT_IRQn);
  NVIC_SetPriority(RTT_IRQn, 4);
  NVIC_EnableIRQ(RTT_IRQn);
    
  rtt_enable_interrupt(RTT, RTT_MR_ALMIEN | RTT_MR_RTTINCIEN);
    
}
```

```C
int main(void){
...
    
	uint16_t pllPreScale = (int) (((float) 32768) / 4.0);
    uint32_t irqRTTvalue = 8;
      
	// reinicia RTT para gerar um novo IRQ
	RTT_init(pllPreScale, irqRTTvalue);         

...
}
```

!!! alert
    O RTT não possui reinicialização automática, quando ocorrer a interrupção é necessário iniciá-lo novamente.

## UART 



## AFEC / ADC - Analog Front End Converter 

