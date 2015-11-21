/**
 *	Keil project for USB HID Device
 *
 *	Before you start, select your target, on the right of the "Load" button
 *
 *	@author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@ide		Keil uVision 5
 */
/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_usb_hid_device.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_stmpe811.h"
#include "tm_stm32f4_exti.h"

#include "key_define.h"

#include "touch_mouse_engine.h"
//#include "touchDriver_ft5x06.h"
#include "log.h"
#include "stdio.h"
#include "touch_action.h"
#include "touch_driver.h"
#include "hard_config.h"
#include "touch_panel.h"



static hard_config_t g_hard_config;
static touch_panel_t g_touch_panel;



int touch_mouse(void) {

	uint8_t already = 0;
	TM_USB_HIDDEVICE_Keyboard_t Keyboard;
	
	
	/* Initialize system */
	SystemInit();
	
	/* Initialize leds */
	TM_DISCO_LedInit();
	
	/* Initialize button */
	TM_DISCO_ButtonInit();
	
	/* Initialize delay */
	TM_DELAY_Init();
	
	/* Initialize USB HID Device */
	TM_USB_HIDDEVICE_Init();
	TM_USB_HIDDEVICE_KeyboardStructInit(&Keyboard);	
	
	//initialize_touch_ft5x06();
	
	initialize_log_func();
	
	/* Attach interrupt on pin PA0 = External line 0 */
	/* Button connected on discovery boards */
	if (TM_EXTI_Attach(GPIOA, GPIO_Pin_0, TM_EXTI_Trigger_Rising) == TM_EXTI_Result_Ok) {
		TM_DISCO_LedOn(LED_RED);
	}
	
	
	touch_driver_t* l_touch_driver = g_hard_config.get_touch_driver();
	l_touch_driver->initilize();
	
	g_touch_panel.set_touch_driver(l_touch_driver);
	
	
	
	
	
#if 0	
	//Initialize Touch
	if (TM_STMPE811_Init() != TM_STMPE811_State_Ok) {
		TM_ILI9341_Puts(20, 20, "STMPE811 Error", &TM_Font_11x18, ILI9341_COLOR_ORANGE, ILI9341_COLOR_BLACK);
		
		while (1);
	}
#endif


	while (1) {

			Delayms(50);
		
			/* If we are connected and drivers are OK */
			if (TM_USB_HIDDEVICE_GetStatus() == TM_USB_HIDDEVICE_Status_Connected) {			
				TM_DISCO_LedOn(LED_GREEN);
			}else {			
				TM_DISCO_LedOff(LED_GREEN);
			}
	
			
			/* If you pressed button right now and was not already pressed */
			if (TM_DISCO_ButtonPressed() && already == 0) { /* Button on press */
				already = 1;
				
				/* Set pressed keys = WIN + R */
				/* Keyboard.L_GUI = TM_USB_HIDDEVICE_Button_Pressed; */	/* Win button */
				Keyboard.Key1 = KEY_ESC;
				
				/*
				Keyboard.L_CTRL = TM_USB_HIDDEVICE_Button_Pressed;
				Keyboard.Key1 = 0x12;
				*/
				
				/*
				Keyboard.Key1 = KEY_WIN_MENU;
				Keyboard.Key2 = KEY_O;
				*/
				
				/* Send keyboard report */
				
				/* TM_USB_HIDDEVICE_KeyboardSend(&Keyboard); */
			} else if (!TM_DISCO_ButtonPressed() && already == 1) { /* Button on release */
				already = 0;
				
				/* Release all buttons */
				// Keyboard.L_GUI = TM_USB_HIDDEVICE_Button_Released;	/* No button */
				/* Keyboard.Key1 = 0x00; */ 								/* No key */
				/* Result = Released everything */
			
				/*
				TM_USB_HIDDEVICE_KeyboardStructInit(&Keyboard);				
				TM_USB_HIDDEVICE_KeyboardSend(&Keyboard);
				*/
				
				action_back_t l_act_back;
				action_t* l_act = &l_act_back;
				l_act->report_hid();
				
			}

#if 0			
			action_t* l_action = check_touch_mouse_state();
			l_action->report_hid();			
#endif
			
			g_touch_panel.update_point_data();
			action_t* l_action = g_touch_panel.check_action();
			l_action->report_hid();
			
			
		} /* while(1) */	
}

/* Set structs for all examples */
	
#if 0
void TM_EXTI_Handler(uint16_t GPIO_Pin) {
	static int16_t count = 0; 
	static int8_t last_gid = 0x01;
	
	TM_DISCO_LedToggle(LED_RED);
	
	if (GPIO_Pin == FT_INT_PIN) {
		TouchScreen_Data_t l_t_data;		
		get_touch_data(&l_t_data);
		
		if(l_t_data.touch_point > 0){
			char str[LOG_MAX_SIZE] = {0};
			sprintf(str, "touch detected %d times. touch point: %d, x1=%d, y1=%d; x2=%d, y2=%d", 
				count++, l_t_data.touch_point, l_t_data.touches[0].x, l_t_data.touches[0].y, l_t_data.touches[1].x, l_t_data.touches[1].y);			
			log(1, str);

			
		}
		
		if(last_gid != l_t_data.gid || l_t_data.gid != 0)
		{			
			if(l_t_data.gid == 0){
				log(0, "No gesture detected.");					
			}else			{
				char str[LOG_MAX_SIZE];
				sprintf(str, "Gesture detected: ID = 0x%02x", l_t_data.gid);
				log(0, str);	
			}
			last_gid = l_t_data.gid;			
		}		
	}
}
#endif 
