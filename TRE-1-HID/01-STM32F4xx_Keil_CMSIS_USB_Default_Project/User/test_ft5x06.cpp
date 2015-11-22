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

//#include "touchDriver_ft5x06.h"
#include "string.h"
#include "stdio.h"
#include "log.h"
#include "touch_driver_ft5x06.h"
#include "tm_stm32f4_delay.h"

#define HIS_DATA_LEN 5

static touch_driver_ft5x06 g_ft5x06;


void get_data(void)
{
	static int16_t count = 0; 
	static int8_t last_gid = 0x01;	
	static TouchScreen_Data_t	l_t_data_his[HIS_DATA_LEN + 1];
	
	count++;	
		
	const TouchScreen_Data_t* l_t_data;
	
	/* Toggle RED led */
	TM_DISCO_LedToggle(LED_RED);
	
	/* get the touch data */
	l_t_data = g_ft5x06.get_touch_points();
	
	/* ripple the history data, data[0] is the latest */
	{
		int16_t i;
		for(i = HIS_DATA_LEN; i > 0; i--)
		{
			l_t_data_his[i] = l_t_data_his[i-1];				
		}
		l_t_data_his[0] = *l_t_data;			
	}
	
	if(count % HIS_DATA_LEN == 0)
	{
		count--;
		count++;
	}
	
	if(l_t_data->touch_point == 0)
	{
		count = 0;
	}
		
	if(l_t_data->touch_point > 0)
	{
		//if(count % HIS_DATA_LEN == 0)
		//{
			char str[LOG_MAX_SIZE] = {0};
			sprintf(str, "touch %d times\npoints: %d\nid=%d,x1=%d,y1=%d\nid=%d, x2=%d, y2=%d\n...", 
				count, l_t_data->touch_point, l_t_data->touches[0].t_id, l_t_data->touches[0].x, l_t_data->touches[0].y, l_t_data->touches[1].t_id, l_t_data->touches[1].x, l_t_data->touches[1].y);			
			log2lcd(1, str);
		//}
					
	}
	
	if(last_gid != l_t_data->gid || l_t_data->gid != 0)
	{			
		if(l_t_data->gid == 0)
		{
			log2lcd(0, "No gesture detected.");					
		}
		else
		{
			char str[LOG_MAX_SIZE];
			sprintf(str, "Gesture detected: ID = 0x%02x", l_t_data->gid);
			log2lcd(0, str);	
		}
		last_gid = l_t_data->gid;
		
	}
		
	
}


int test_ft5x06(void) {
	/* Initialize system */
	SystemInit();

	/* Initialize LEDS */
	TM_DISCO_LedInit();	
	
	//initialize_touch_ft5x06();
	g_ft5x06.initilize();
	
	initialize_log_func();
	
	while (1) {		
		Delayms(50);
		get_data();
		
		
	}
}

#if 0
void TM_EXTI_Handler(uint16_t GPIO_Pin) {
	if (GPIO_Pin == g_ft5x06.get_exti_pin()) {
		//get_data();		
	}
}
#endif
