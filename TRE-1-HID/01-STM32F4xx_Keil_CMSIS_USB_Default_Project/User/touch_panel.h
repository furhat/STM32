#ifndef TOUCH_PANEL___H
#define TOUCH_PANEL___H


#include "stm32f4xx.h"
#include "touch_defines.h"
#include "touch_point.h"
#include "touch_driver.h"
#include "touch_action.h"
#include "math.h"

struct touch_point_status
{
	uint8_t n;
	touch_point_t* p[MAX_TOUCH_POINT];
};

typedef struct{
	coord_dist_t pre_dist;
	coord_dist_t cur_dist;
	
	int16_t track_num;
	
	
	void reset(void){
		pre_dist.reset();
		cur_dist.reset();	
		track_num = 0;
	}	
	
	float get_dist_change(void){
		return cur_dist.get_dist() - pre_dist.get_dist();
	}
	
}move_track_t;

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

	int16_t m_move_acc;

	ACTION_FACTORY m_action_factory;

	move_track_t m_move_track;

	bool m_long_press_sent;

	// for debug
	int16_t m_debug_cnt;
	
	
	
};

#endif
