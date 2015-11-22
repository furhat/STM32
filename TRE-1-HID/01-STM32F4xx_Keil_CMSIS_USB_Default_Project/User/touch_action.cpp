
#include "touch_action.h"
#include "tm_stm32f4_usb_hid_device.h"
#include "tm_stm32f4_delay.h"
#include "key_define.h"


//--------------------------------------------------------
void action_null_t::report_hid()
{
	// do nothing
}

//--------------------------------------------------------

void action_l1_click_down_t::report_hid()
{
	TM_USB_HIDDEVICE_Mouse_t l_mouse_data;
	TM_USB_HIDDEVICE_MouseStructInit(&l_mouse_data);
	l_mouse_data.LeftButton = TM_USB_HIDDEVICE_Button_Pressed;
	TM_USB_HIDDEVICE_MouseSend(&l_mouse_data);	
}


//--------------------------------------------------------

void action_l1_click_up_t::report_hid()
{
	TM_USB_HIDDEVICE_Mouse_t l_mouse_data;
	TM_USB_HIDDEVICE_MouseStructInit(&l_mouse_data);	
	TM_USB_HIDDEVICE_MouseSend(&l_mouse_data);	
}

//--------------------------------------------------------
void action_l1_click_t::report_hid()
{
	TM_USB_HIDDEVICE_Mouse_t l_mouse_data;
	TM_USB_HIDDEVICE_MouseStructInit(&l_mouse_data);
	l_mouse_data.LeftButton = TM_USB_HIDDEVICE_Button_Pressed;
	TM_USB_HIDDEVICE_MouseSend(&l_mouse_data);
	
	Delayms(50);
	
	TM_USB_HIDDEVICE_MouseStructInit(&l_mouse_data);	
	TM_USB_HIDDEVICE_MouseSend(&l_mouse_data);
}


//--------------------------------------------------------
void action_back_t::report_hid()
{
	// send press down
	TM_USB_HIDDEVICE_Keyboard_t l_keyboard;
	TM_USB_HIDDEVICE_KeyboardStructInit(&l_keyboard);
	l_keyboard.Key1 = KEY_ESC;
	TM_USB_HIDDEVICE_KeyboardSend(&l_keyboard);
	
	Delayms(50);
	
	//send press up
	TM_USB_HIDDEVICE_KeyboardStructInit(&l_keyboard);
	TM_USB_HIDDEVICE_KeyboardSend(&l_keyboard);
}

//--------------------------------------------------------
void action_menu_t::report_hid()
{
	// send press down
	TM_USB_HIDDEVICE_Keyboard_t l_keyboard;
	TM_USB_HIDDEVICE_KeyboardStructInit(&l_keyboard);
	l_keyboard.Key1 = KEY_WIN_MENU;
	TM_USB_HIDDEVICE_KeyboardSend(&l_keyboard);
	
	Delayms(50);
	
	//send press up
	TM_USB_HIDDEVICE_KeyboardStructInit(&l_keyboard);
	TM_USB_HIDDEVICE_KeyboardSend(&l_keyboard);
}

//--------------------------------------------------------
action_mouse_move_t::action_mouse_move_t(void):m_x_move(0),m_y_move(0)
{
}

action_mouse_move_t::action_mouse_move_t(int16_t x, int16_t y):m_x_move(x),m_y_move(y)
{
}

	
void action_mouse_move_t::report_hid(void)
{
	TM_USB_HIDDEVICE_Mouse_t l_mouse_data;
	TM_USB_HIDDEVICE_MouseStructInit(&l_mouse_data);
	l_mouse_data.XAxis = m_x_move;
	l_mouse_data.YAxis = m_y_move;	
	
	TM_USB_HIDDEVICE_MouseSend(&l_mouse_data);	
}


void action_mouse_move_t::set_value(int16_t x, int16_t y)
{
	m_x_move = x;
	m_y_move = y;
}


//--------------------------------------------------------

action_scroll_t::action_scroll_t(int16_t value):m_scroll_value(value){	
}

action_scroll_t::action_scroll_t(void):m_scroll_value(0){
}

void action_scroll_t::set_value(int16_t value){
	m_scroll_value = value;
}

void action_scroll_t::report_hid(void){
	TM_USB_HIDDEVICE_Mouse_t l_mouse_data;
	TM_USB_HIDDEVICE_MouseStructInit(&l_mouse_data);
	l_mouse_data.Wheel = m_scroll_value;
	TM_USB_HIDDEVICE_MouseSend(&l_mouse_data);	
}

//--------------------------------------------------------

action_zoom_t::action_zoom_t(int16_t value):m_zoom_value(value){	
}

action_zoom_t::action_zoom_t(void):m_zoom_value(0){
}

void action_zoom_t::set_value(int16_t value){
	m_zoom_value = value;
}

void action_zoom_t::report_hid(void){
	// send press down
	TM_USB_HIDDEVICE_Keyboard_t l_keyboard;
	TM_USB_HIDDEVICE_KeyboardStructInit(&l_keyboard);
	
	l_keyboard.L_CTRL = TM_USB_HIDDEVICE_Button_Pressed;
	if(m_zoom_value == -1){
		l_keyboard.Key1 = 0x2D;
	}else{
		l_keyboard.Key1 = 0x2E;		
	}		
	
	TM_USB_HIDDEVICE_KeyboardSend(&l_keyboard);
	
	Delayms(50);
	
	//send press up
	TM_USB_HIDDEVICE_KeyboardStructInit(&l_keyboard);
	TM_USB_HIDDEVICE_KeyboardSend(&l_keyboard);
}

