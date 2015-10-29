/**
 * @author  wei liu
 * @email   
 * @website 
 * @link    
 * @version v1.0
 * @ide     Keil uVision
 * @license GNU GPL v3
 * @brief  detect touch panel action, output mouse event 
 *	
**/

#ifndef TOUCH_MOUSE_ENGINE_H
#define TOUCH_MOUSE_ENGINE_H 100





typedef enum{
	TOUCH_EVENT_NONE = 0,
	TOUCH_EVENT_ACTION,
	TOUCH_EVENT_RELEASE
} TOUCH_EVENT;

TOUCH_EVENT check_touch_mouse_state(void);

TM_USB_HIDDEVICE_Mouse_t get_mouse_data(void);

#endif
