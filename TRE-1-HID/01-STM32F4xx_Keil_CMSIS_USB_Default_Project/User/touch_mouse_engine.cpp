
#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_stmpe811.h"
#include "tm_stm32f4_usb_hid_device.h"

#include "touch_mouse_engine.h"
#include "stdio.h"

typedef enum{
	TOUCH_STATE_IDLE = 0,
	TOUCH_STATE_PRESSING,
	TOUCH_STATE_MOVING,	
} TOUCH_STATE;

//Create TouchData struct
static	TM_STMPE811_TouchData g_touchData;
static	TM_STMPE811_TouchData g_touchData_pre;

static 	TM_USB_HIDDEVICE_Mouse_t g_mouseData;

static 	TOUCH_STATE g_touch_state = TOUCH_STATE_IDLE;

static const uint16_t PIX_THRESHOLD_MOVE = 2;

static ACTION_FACTORY g_action_factory;


	
static 	uint16_t get_coordinate_diff(TM_STMPE811_TouchData a_touch_1, TM_STMPE811_TouchData a_touch_2)
{
	return abs(a_touch_1.x - a_touch_2.x) + abs(a_touch_1.y - a_touch_2.y);
}


action_t* check_touch_mouse_state(void)
{
	char str[30];
	
	action_t* l_action = &g_action_factory.act_null;
	
	TOUCH_EVENT l_event = TOUCH_EVENT_NONE;
	
	/* Set default values for mouse struct */
	TM_USB_HIDDEVICE_MouseStructInit(&g_mouseData);	
	
	if (TM_STMPE811_ReadTouch(&g_touchData) == TM_STMPE811_State_Pressed) {
		//Touch valid
		sprintf(str, "Pressed    \n\nX: %03d\nY: %03d", g_touchData.x, g_touchData.y);
		TM_ILI9341_Puts(20, 80, str, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);

		//if(g_touchData_pre.pressed == TM_STMPE811_State_Released)
		//TM_ILI9341_DrawPixel(g_touchData.x, g_touchData.y, 0x0000);
		
		switch(g_touch_state)
		{
			case TOUCH_STATE_IDLE:
				g_touch_state = TOUCH_STATE_PRESSING;
				l_action = &g_action_factory.act_l1_click_down;
			
				//g_mouseData.LeftButton = TM_USB_HIDDEVICE_Button_Pressed;
				//l_event = TOUCH_EVENT_ACTION;
				break;
			case TOUCH_STATE_PRESSING:
			case TOUCH_STATE_MOVING:
				if(get_coordinate_diff(g_touchData_pre, g_touchData) > PIX_THRESHOLD_MOVE)
				{
					g_touch_state = TOUCH_STATE_MOVING;
					g_action_factory.act_mouse_move.set_value(2* (g_touchData_pre.x - g_touchData.x), 2* (g_touchData_pre.y - g_touchData.y));
					l_action = &g_action_factory.act_mouse_move;
					//g_mouseData.XAxis = 2* (g_touchData_pre.x - g_touchData.x);
					//g_mouseData.YAxis = 2* (g_touchData_pre.y - g_touchData.y);
					//l_event = TOUCH_EVENT_ACTION;						
				}
				break;
			default:
				break;
		}
		
		g_touchData_pre = g_touchData;
		
		
	} else {
		sprintf(str, "Not Pressed\n\n       \n      ");
		TM_ILI9341_Puts(20, 80, str, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
		
		if(g_touchData_pre.pressed == TM_STMPE811_State_Pressed)
		{
		
			switch(g_touch_state)
			{
				case TOUCH_STATE_PRESSING:
					//g_mouseData.LeftButton = TM_USB_HIDDEVICE_Button_Released;
					l_action = &g_action_factory.act_l1_click_up;
					l_event = TOUCH_EVENT_ACTION;
					break;
				case TOUCH_STATE_IDLE:
				case TOUCH_STATE_MOVING:
				default:
					break;
				
			}
			g_touchData_pre = g_touchData;
			g_touch_state = TOUCH_STATE_IDLE;			
		}		
	}	
	//return l_event;
	return l_action;
}

TM_USB_HIDDEVICE_Mouse_t get_mouse_data(void)
{
		return g_mouseData;
}
