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

int test_exi(void) {
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
	
	/* Attach interrupt on pin PA0 = External line 0 */
	/* Button connected on discovery boards */
	if (TM_EXTI_Attach(GPIOA, GPIO_Pin_0, TM_EXTI_Trigger_Rising) == TM_EXTI_Result_Ok) {
		TM_DISCO_LedOn(LED_RED);
	}
	
	/* Attach interrupt on pin PC13 = External line 13 */
	/* Button connected on nucleo boards */
	if (TM_EXTI_Attach(GPIOC, GPIO_Pin_13, TM_EXTI_Trigger_Falling) == TM_EXTI_Result_Ok) {
		TM_DISCO_LedOn(LED_GREEN);
	}
	
	while (1) {
		
	}
}

#if 0

void TM_EXTI_Handler(uint16_t GPIO_Pin) {
	
	volatile static uint8_t counter = 0;
	
	/* Handle external line 0 interrupts */
	if (GPIO_Pin == GPIO_Pin_0) {
		/* Toggle RED led */
		TM_DISCO_LedToggle(LED_RED);
		TM_ILI9341_Puts(20, 80, "button pressed, button pressed, button pressed, button pressed, button pressed, button pressed, button pressed, button pressed, ", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
		/* Check counter */
		if (++counter >= 10) {
			/* Detach external interrupt for GPIO_Pin_0 no matter on which GPIOx is connected */
			TM_EXTI_Detach(GPIO_Pin_0);
			TM_ILI9341_Puts(20, 80, "Exi detached", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
		}
	}
	
	/* Handle external line 13 interrupts */
	if (GPIO_Pin == GPIO_Pin_13) {
		/* Toggle GREEN led */
		TM_DISCO_LedToggle(LED_GREEN);
		/* Check counter */
		if (++counter >= 10) {
			/* Detach external interrupt for GPIO_Pin_0 no matter on which GPIOx is connected */
			TM_EXTI_Detach(GPIO_Pin_13);
		}
	}
}

#endif



