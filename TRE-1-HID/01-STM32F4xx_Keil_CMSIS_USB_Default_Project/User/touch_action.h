#ifndef TOUCH_ACTION___H
#define TOUCH_ACTION___H

#include "stm32f4xx.h"


//========================================================
class action_t
{
public:
	virtual void report_hid(void) = 0;
};

//--------------------------------------------------------

class action_null_t:public action_t
{
public:	
	virtual void report_hid(void);
};

//--------------------------------------------------------
class action_l1_click_down_t:public action_t
{
public:
	virtual void report_hid(void);	
};

//--------------------------------------------------------
class action_l1_click_up_t:public action_t
{
public:
	virtual void report_hid(void);	
};

//--------------------------------------------------------
class action_l1_click_t:public action_t
{
public:
	virtual void report_hid(void);	
};


//--------------------------------------------------------
class action_back_t:public action_t
{
public:	
	virtual void report_hid(void);
};


//--------------------------------------------------------
class action_mouse_move_t:public action_t
{
public:
	action_mouse_move_t(void);
	action_mouse_move_t(int16_t x, int16_t y);
	void set_value(int16_t x, int16_t y);
	virtual void report_hid(void);
private:
	int16_t m_x_move;
	int16_t m_y_move;
};

//--------------------------------------------------------

class action_scroll_t:public action_t
{
public:
	action_scroll_t(void);
	action_scroll_t(int16_t value);
	void set_value(int16_t value);
	virtual void report_hid(void);	
private:
	int16_t m_scroll_value;
	
};


//--------------------------------------------------------

class action_zoom_t:public action_t
{
public:
	action_zoom_t(void);
	action_zoom_t(int16_t value);
	void set_value(int16_t value);
	virtual void report_hid(void);	
private:
	int16_t m_zoom_value;	
};

//--------------------------------------------------------
// action factory to pre-creat all the actions
typedef struct
{
	action_null_t act_null;
	action_l1_click_t	act_l1_click_t;
	action_l1_click_down_t act_l1_click_down;
	action_l1_click_up_t act_l1_click_up;
	action_back_t act_back;
	action_mouse_move_t act_mouse_move;
	action_scroll_t act_scroll;
	action_zoom_t act_zoom;
	
}ACTION_FACTORY;




#endif
