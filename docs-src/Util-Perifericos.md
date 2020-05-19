# 	Periféricos



## PIO - Paralelel Input Output

```c
//Defines dos botões
#define BUT_PIO 		PIOA
#define BUT_PIO_ID		ID_PIOA
#define BUT_IDX 		11
#define BUT_IDX_MASK	(1 << BUT_IDX)
```

```c
//Callback da IRQ do botão
void but_callback(void){
 //Instruções a serem executadas
}
```

```C
//Inicialização do botão com IRQ
void but_init(void){
    
pmc_enable_periph_clk(BUT_PIO_ID);
pio_configure(BUT_PIO, PIO_INPUT, BUT_IDX_MASK, PIO_PULLUP);
pio_handler_set(BUT_PIO, BUT_PIO_ID, BUT_IDX_MASK, PIO_IT_FALL_EDGE, but_callback);
    
NVIC_SetPriority(BUT_PIO_ID, 4);
NVIC_EnableIRQ(BUT_PIO_ID);
    
pio_enable_interrupt(BUT_PIO, BUT_IDX_MASK);
    
}
```



## TC - Timer Counter

A família SAM E70 possui 3 TCs, cada TC possui 3 canais (0, 1 e 2):

|          | **CH0** |  **CH1**   | **CH2** |
| :------: | :-----: | :--------: | :-----: |
| **TC0:** | ID_TC0  |   ID_TC1   | ID_TC2  |
| **TC1**  | ID_TC3  |   ID_TC4   | ID_TC5  |
| **TC2**  | ID_TC6  | **ID_TC7** | ID_TC8  |



Abaixo, exemplo para configuração do TC2 - Canal 1 (**ID_TC7**):

```C
//Handler a ser executado quando a IRQ do TC é ativada

void TC7_Handler(void){ //ID_TC7 -> TC2 - Canal 1
    
	volatile uint32_t ul_dummy;

	ul_dummy = tc_get_status(TC2, 1); //ID_TC7 -> TC2 - Canal 1

	UNUSED(ul_dummy);

	flag_tc = 1; //Instrução a ser executada quando a interrupção acontecer
    
}
```

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
	
	tc_start(TC, TC_CHANNEL);
    
}
```

```C
int main(void){
...
    
int canal_ID_TC7 = 2; //Canal 2
int freq = 2; //2 Hz, a interrupção acontece 2 vezes por segundo

/** Configura timer TC2, canal 1 */
	TC_init(TC2, ID_TC7, canal_ID_TC7, freq);
    
...
    
}
```





## RTC - Real Time Counter

```c
/**
 *  Informacoes para o RTC
 *  poderia ser extraida do __DATE__ e __TIME__
 *  ou ser atualizado pelo PC.
 */
typedef struct  {
  uint32_t year;
  uint32_t month;
  uint32_t day;
  uint32_t week;
  uint32_t hour;
  uint32_t minute;
  uint32_t seccond;
} calendar
```

```C
void RTC_Handler(void)
{
    
	uint32_t ul_status = rtc_get_status(RTC);

	if ((ul_status & RTC_SR_SEC) == RTC_SR_SEC){ //Se a interrupção for por SEGUNDO
		rtc_clear_status(RTC, RTC_SCCR_SECCLR);
		...
		//instrução a ser executada quando a IRQ por SEGUNDO for ativada
		...
	}
	
	if ((ul_status & RTC_SR_ALARM) == RTC_SR_ALARM){ //Se a interrupção for por ALARME
		rtc_clear_status(RTC, RTC_SCCR_ALRCLR);
		...
		//instrução a ser executada quando a IRQ por ALARME for ativada
		...
	}
	
	rtc_clear_status(RTC, RTC_SCCR_ACKCLR);
	rtc_clear_status(RTC, RTC_SCCR_TIMCLR);
	rtc_clear_status(RTC, RTC_SCCR_CALCLR);
	rtc_clear_status(RTC, RTC_SCCR_TDERRCLR);
    
}

```

```c
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

```C
int main(void){
...

	calendar rtc_initial = {2020, 7, 10, 28, 15, 45 ,1};
	RTC_init(RTC, ID_RTC, rtc_initial, RTC_IER_ALREN | RTC_IER_SECEN); //RTC_IER_ALREN - IRQ por ALARME
    													  //RTC_IER_SECEN - IRQ por SEGUNDO

	/* configura alarme do RTC */
	rtc_set_date_alarm(RTC, 1, rtc_initial.month, 1, rtc_initial.day);
	rtc_set_time_alarm(RTC, 1, rtc_initial.hour, 1, rtc_initial.minute, 1, rtc_initial.seccond);

...
}
```

!!! alert

​    O RTC não possui reinicialização automática na IRQ por ALARME, quando ocorrer a interrupção é necessário iniciá-lo novamente com um novo valor para o ALARME.



## RTT - Real Time Timer

```C
void RTT_Handler(void)
{

  uint32_t ul_status;

  ul_status = rtt_get_status(RTT);
    
  if ((ul_status & RTT_SR_RTTINC) == RTT_SR_RTTINC) {
      
    ...
	//instrução a ser executada quando a IRQ por TICK (pllPreScale) for ativada
	...
  
    }

  if ((ul_status & RTT_SR_ALMS) == RTT_SR_ALMS) {
      
    ...
	//instrução a ser executada quando a IRQ por ALARME for ativada
	...
         
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

​    O RTT não possui reinicialização automática, quando ocorrer a interrupção é necessário iniciá-lo novamente.

## UART 



## AFEC / ADC - Analog Front End Converter 

