/*------------------------------------------------------------------------ 
 * CMSIS-RTOS 'main' function template 
 *----------------------------------------------------------------------*/ 
 
#define osObjectsPublic // Define objects in main module 
#include "osObjects.h" // RTOS object definitions 
#include "cmsis_os.h" // ARM::CMSIS:RTOS:Keil RTX 
#include "LED.h" // Initialize and set GPIO Port 
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_delay.h"
 
 #if 0
/* 
 * main: initialize and start the system 
 */ 
int main (void) { 
	
	/* Initialize system */
	SystemInit();
	
	/* Initialize delay */
	//TM_DELAY_Init();
	
	/* Initialize onboard leds */
	TM_DISCO_LedInit();
	
 osKernelInitialize (); // Initialize CMSIS-RTOS 
 // initialize peripherals here 
 //LED_Initialize (); // Initialize LEDs


 
 // create 'thread' functions that start executing, 
 // example: tid_name = osThreadCreate (osThread(name), NULL); 
 Init_BlinkyThread (); // Start Blinky thread 
 osKernelStart (); // Start thread execution 
 
 while (1); 
}
#endif

