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
#include "tm_stm32f4_ili9341.h"

#include "touchDriver_ft5x06.h"
#include "string.h"
#include "stdio.h"


int test_ft5x06(void) {
	/* Initialize system */
	SystemInit();

	/* Initialize LEDS */
	TM_DISCO_LedInit();
	
	//Initialize LCD
	TM_ILI9341_Init();
	//Fill with orange color
	TM_ILI9341_Fill(ILI9341_COLOR_ORANGE);
	//Rotate LCD
	TM_ILI9341_Rotate(TM_ILI9341_Orientation_Portrait_2);
	
	
	initialize_touch_ft5x06();
	
	while (1) {
		
	}
}

void TM_EXTI_Handler(uint16_t GPIO_Pin) {
	static int16_t count = 0; 
	char str[128] = {0};
	char str_blank[128];
	TouchScreen_Data_t l_t_data;
	
	memset(str_blank, 0x20, 127);
	str_blank[127] = '\0';
	
	if (GPIO_Pin == FT_INT_PIN) {
		/* Toggle RED led */
		TM_DISCO_LedToggle(LED_RED);
		
		get_touch_data(&l_t_data);
		if(l_t_data.touch_point > 0)
		{		
			TM_ILI9341_Puts(20, 80, str_blank, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
			
			sprintf(str, "touch detected %d times. touch point: %d, x1=%d, y1=%d; x2=%d, y2=%d", 
				count++, l_t_data.touch_point, l_t_data.touches[0].x, l_t_data.touches[0].y, l_t_data.touches[1].x, l_t_data.touches[1].y);
			
			
			TM_ILI9341_Puts(20, 80, str, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
		}
	}
}
