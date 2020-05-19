# Periféricos



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
    
int canal_id_tc7 = 2; //Canal 2
int freq = 2; //2 Hz, a interrupção acontece 2 vezes por segundo

/** Configura timer TC0, canal 1 */
	TC_init(TC2, ID_TC7, canal_id_tc7, freq);
    
...
}
```





## RTC - Real Time Counter



## RTT - Real Time Timer

## UART 

## AFEC / ADC - Analog Front End Converter 

