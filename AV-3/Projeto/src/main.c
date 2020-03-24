#include "asf.h"
#include "main.h"
#include <string.h>

#include "OLED1/gfx_mono_ug_2832hsweg04.h"
#include "OLED1/gfx_mono_text.h"
#include "OLED1/sysfont.h"

/************************************************************************/
/* GENERIC DEFINES                                                      */
/************************************************************************/

/************************************************************************/
/* generic globals                                                      */
/************************************************************************/

/************************************************************************/
/*  RTOS    (defines + globals)                                         */
/************************************************************************/

#define TASK_STRING_STACK_SIZE            (4096/sizeof(portSTACK_TYPE))
#define TASK_STRING_STACK_PRIORITY        (tskIDLE_PRIORITY)

extern void vApplicationStackOverflowHook(xTaskHandle *pxTask,
signed char *pcTaskName);
extern void vApplicationIdleHook(void);
extern void vApplicationTickHook(void);
extern void vApplicationMallocFailedHook(void);
extern void xPortSysTickHandler(void);

extern void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName)
{
	printf("stack overflow %x %s\r\n", pxTask, (portCHAR *)pcTaskName);
	/* If the parameters have been corrupted then inspect pxCurrentTCB to
	 * identify which task has overflowed its stack.
	 */
	for (;;) {
	}
}
extern void vApplicationIdleHook(void)
{
	
}
extern void vApplicationTickHook(void)
{
}
extern void vApplicationMallocFailedHook(void)
{
	/* Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */

	/* Force an assert. */
	configASSERT( ( volatile void * ) NULL );
}


/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

int protocol_check_led(char *string);
int io_init(void);
void led_on(uint id, uint on);

/************************************************************************/
/* IRQS / callbacks                                                     */
/************************************************************************/

void USART1_Handler(void){

  BaseType_t xHigherPriorityTaskWoken = pdFALSE; // freeRTOs
  uint32_t ret = usart_get_status(CONF_UART);  // ACK IRQ

  // Por qual motivo entrou na interrupçcao ? Pode ser varios!
  //  1. RX: Dado disponível para leitura
  if(ret & US_IER_RXRDY){
    // LER DADO DA UART
    // ENVIAR VIA FILA
  } 
}

void button0_callback(void){}

void button1_callback(void){}

void button2_callback(void){}


/************************************************************************/
/* TASKS                                                                */
/************************************************************************/

void task_string(void *pvParameters){
    
  char b[52];
  uint i = 0;
  while(1){
    if(usart_serial_is_rx_ready(CONF_UART)){
      usart_serial_getchar(CONF_UART, &b[i]);
      if(b[i]=='\n'){
        b[i] = NULL;
        i=0;
        printf("recebido: %s\n", b);
      }else{
        i++;
      }          
    }    
  } 
}  


void task_io(void *pvParameters){
  
}

void task_oled1(void *pvParameters){
 
}  




/************************************************************************/
/* CONFIGS/ INITS                                                       */
/************************************************************************/

static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate =		CONF_UART_BAUDRATE,
		.charlength =	CONF_UART_CHAR_LENGTH,
		.paritytype =	CONF_UART_PARITY,
		.stopbits =		CONF_UART_STOP_BITS,
	};

	/* Configure UART console. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}


/************************************************************************/
/* functions                                                            */
/************************************************************************/

int protocol_check_led(char *string){}

int io_init(void){}
  
void led_on(uint id, uint on){}


/************************************************************************/
/* MAIN                                                                 */
/************************************************************************/
int main(void)
{
	/* Initialize the board. */
	sysclk_init();
	board_init();

	/* Initialize the UART console. */
	configure_console();
   
	if (xTaskCreate(task_string, "string", TASK_STRING_STACK_SIZE, NULL, TASK_STRING_STACK_PRIORITY, NULL) != pdPASS) {
		printf("Failed to create Wifi task\r\n");
	}

	vTaskStartScheduler();
	
	while(1) {};
	return 0;

}
