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

#include "key_define.h"



int test_hid(void) {
	uint8_t already = 0;
	
	/* Set structs for all examples */
	TM_USB_HIDDEVICE_Keyboard_t Keyboard;
	TM_USB_HIDDEVICE_Gamepad_t Gamepad1, Gamepad2;
	TM_USB_HIDDEVICE_Mouse_t Mouse;
	
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
	
	/* Set default values for mouse struct */
	TM_USB_HIDDEVICE_MouseStructInit(&Mouse);
	/* Set default values for keyboard struct */
	TM_USB_HIDDEVICE_KeyboardStructInit(&Keyboard);
	/* Set default values for gamepad structs */
	TM_USB_HIDDEVICE_GamepadStructInit(&Gamepad1);
	TM_USB_HIDDEVICE_GamepadStructInit(&Gamepad2);

	while (1) {		  
		/* If we are connected and drivers are OK */
		if (TM_USB_HIDDEVICE_GetStatus() == TM_USB_HIDDEVICE_Status_Connected) {
			/* Turn on green LED */
			TM_DISCO_LedOn(LED_GREEN);
			
/* Simple sketch start */	
#if 0			
			/* If you pressed button right now and was not already pressed */
			if (TM_DISCO_ButtonPressed() && already == 0) { /* Button on press */
				already = 1;
				
				/* Set pressed keys = WIN + R */
				/* Keyboard.L_GUI = TM_USB_HIDDEVICE_Button_Pressed; */	/* Win button */
				Keyboard.Key1 = 0xB1; 								/* R */
				/* Result = "Run" command */
				
				/* Send keyboard report */
				TM_USB_HIDDEVICE_KeyboardSend(&Keyboard);
			} else if (!TM_DISCO_ButtonPressed() && already == 1) { /* Button on release */
				already = 0;
				
				/* Release all buttons */
				// Keyboard.L_GUI = TM_USB_HIDDEVICE_Button_Released;	/* No button */
				/* Keyboard.Key1 = 0x00; */ 								/* No key */
				/* Result = Released everything */
				
				/* Send keyboard report */
				TM_USB_HIDDEVICE_KeyboardSend(&Keyboard);
			}
#else
			/* If you pressed button right now and was not already pressed */
			if (TM_DISCO_ButtonPressed() && already == 0) { /* Button on press */
				already = 1;
				
				/* Left button on mouse is pressed */
				// Mouse.LeftButton = TM_USB_HIDDEVICE_Button_Pressed;
				
				/* mouse moved */
				Mouse.XAxis = 2;
				Mouse.YAxis = 2;
				
				/* Send mouse report */
				TM_USB_HIDDEVICE_MouseSend(&Mouse);
			} else if (!TM_DISCO_ButtonPressed() && already == 1) { /* Button on release */
				already = 0;
				
				/* Left button on mouse is released */
				// Mouse.LeftButton = TM_USB_HIDDEVICE_Button_Released;
				
				Mouse.XAxis = 2;
				Mouse.YAxis = 2;
				
				/* Send mouse report */
				TM_USB_HIDDEVICE_MouseSend(&Mouse);
			}
#endif
			
/* Simple sketch end */
			
		} else {
			/* Turn off green LED */
			TM_DISCO_LedOff(LED_GREEN);
		}
	}
}


