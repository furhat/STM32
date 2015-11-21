#ifndef TOUCH_PANEL___H
#define TOUCH_PANEL___H


#include "stm32f4xx.h"
#include "touch_defines.h"
#include "touch_point.h"
#include "touch_driver.h"
#include "touch_action.h"

struct touch_point_status
{
	uint8_t n;
	touch_point_t* p[MAX_TOUCH_POINT];
};

class touch_panel_t
{
public:
	touch_panel_t();
	touch_panel_t(touch_driver_t* a_driver);
	void set_touch_driver(touch_driver_t* a_driver);

	action_t* check_action(void);
	void update_point_data(void);
	

private:
	struct touch_point_status get_active_point(void);
		
	touch_driver_t* m_touch_driver;
	touch_point_t m_points[MAX_TOUCH_POINT];
	//uint8_t m_update_flag;

	action_t* m_last_action;

	ACTION_FACTORY m_action_factory;
	
	
	
};

#endif
