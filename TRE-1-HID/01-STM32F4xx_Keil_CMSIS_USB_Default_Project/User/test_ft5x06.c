/**
 *	Keil project for external interrupts library
 *
 *	Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@ide		Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 *	@stdperiph	STM32F4xx Standard peripheral drivers version 1.4.0 or greater required
 */
/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_exti.h"

#include "touchDriver_ft5x06.h"
#include "string.h"
#include "stdio.h"
#include "log.h"


int test_ft5x06(void) {
	/* Initialize system */
	SystemInit();

	/* Initialize LEDS */
	TM_DISCO_LedInit();	
	
	initialize_touch_ft5x06();
	
	initialize_log_func();
	
	while (1) {
		
	}
}

void TM_EXTI_Handler(uint16_t GPIO_Pin) {
	static int16_t count = 0; 
	static int8_t last_gid = 0x01;
	
	
	TouchScreen_Data_t l_t_data;	
	
	if (GPIO_Pin == FT_INT_PIN) {
		/* Toggle RED led */
		TM_DISCO_LedToggle(LED_RED);
		
		get_touch_data(&l_t_data);
		if(l_t_data.touch_point > 0)
		{
			char str[LOG_MAX_SIZE] = {0};
			sprintf(str, "touch detected %d times. touch point: %d, x1=%d, y1=%d; x2=%d, y2=%d", 
				count++, l_t_data.touch_point, l_t_data.touches[0].x, l_t_data.touches[0].y, l_t_data.touches[1].x, l_t_data.touches[1].y);			
			log(1, str);			
		}
		
		if(last_gid != l_t_data.gid || l_t_data.gid != 0)
		{			
			if(l_t_data.gid == 0)
			{
				log(0, "No gesture detected.");					
			}
			else
			{
				char str[LOG_MAX_SIZE];
				sprintf(str, "Gesture detected: ID = 0x%02x", l_t_data.gid);
				log(0, str);	
			}
			last_gid = l_t_data.gid;
			
		}
		
	}
}
