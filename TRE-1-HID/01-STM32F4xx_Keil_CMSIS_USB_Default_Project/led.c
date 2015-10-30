/*------------------------------------------------------------------------ 
 * File LED.c 
 *----------------------------------------------------------------------*/ 
#include "stm32f4xx.h" // Device header 
#include "cmsis_os.h" // RTOS:Keil RTX header 
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_delay.h"
 
void blink_LED (void const *argument); // Prototype function 
 
osThreadDef (blink_LED, osPriorityNormal, 1, 0); // Define blinky thread 
 
// Initialize GPIO Port 
void LED_Initialize (void) { 
 RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // Enable Port D clock 
 GPIOD->MODER |= GPIO_MODER_MODER15_0; // Port D.13 output 
} 
 
/* Turn LED on */ 
void LED_On (void) { 
 GPIOD->BSRRL = (1<<15); // LED on: set Port 
} 
 
/* Turn LED off */ 
void LED_Off (void) { 
 GPIOD->BSRRH = (1<<15); // LED off: clear Port 
} 
// Blink LED function 
void blink_LED(void const *argument) { 
	
#if 0	
	/* Reset counter to 0 */
	TM_DELAY_SetTime(0);
	while (1) {
		/* If time is more than 500ms */
		if (TM_DELAY_Time() >= 500) {
			/* Reset time */
			TM_DELAY_SetTime(0);
			/* Toggle leds here */
			TM_DISCO_LedToggle(LED_RED | LED_GREEN);
		}
		/* Place your code here */
		/* Code here will be checked without any delay */
		/* Constantly */
	}
#endif
	
#if 1
 for (;;) { 
 //LED_On (); // Switch LED on 
	osDelay(1000);
	TM_DISCO_LedToggle(LED_RED | LED_GREEN);
 }
#endif

} 
 
void Init_BlinkyThread (void) { 
 osThreadCreate (osThread(blink_LED), NULL); // Create thread 
}
