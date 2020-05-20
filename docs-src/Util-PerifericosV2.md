# 	Periféricos v2

Um pequeno resumo de como utilizar os periféricos do microcontrolador SAME70 no kit SAME70-XPLD.


## PIO - Paralelel Input Output

| Exemplos                                                                                                |
| --------                                                                                                |
| [Perifericos-uC/PIO-IO/](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/PIO-IO)   |
| [Perifericos-uC/PIO-IRQ/](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/PIO-IRQ) |



=== "output"
    
    ``` c
    // LED da placa
    #define LED_PIO      PIOC
    #define LED_PIO_ID   ID_PIOC
    #define LED_IDX      8
    #define LED_IDX_MASK (1 << LED_IDX)
    ```
    
    Configura o `PC8` como sendo output.
    
    ``` c
    pmc_enable_periph_clk(LED_PIO_ID);
	pio_configure(LED_PIO, PIO_OUTPUT_0, LED_IDX_MASK, PIO_DEFAULT);
    ```
    
    Acionando o pino
    
    ``` c
    pio_set(LED_PIO, LED_IDX_MASK);   // coloca pino em 1
    pio_clear(LED_PIO, LED_IDX_MASK); // coloca pino em 0
    ```

=== "input com interrupção"

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
    //Instruções a serem executadas
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
 
    Para ler o pino

    ```c
    uint32_t pin = pio_get(BUT_PIO, BUT_IDX_MASK);
    ```

    - `pin > 0`: Pinos em `1`
    - `pin = 0`: Pinos em `0`
