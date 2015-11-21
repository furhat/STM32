#ifndef TOUCH_DRIVER___H
#define TOUCH_DRIVER___H

#include "stm32f4xx.h"
#include "string.h"

typedef struct{
	uint16_t x;
	uint16_t y;
	uint8_t  t_id;
	uint8_t  t_ev;	
}OneTouch_t;

typedef struct{
	uint8_t gid;
	uint8_t touch_point;
	OneTouch_t touches[5];
}TouchScreen_Data_t;

class touch_driver_t
{
	public:
		virtual void initilize(void) = 0;
		virtual const TouchScreen_Data_t* get_touch_points(void) = 0;
	
	protected:
		TouchScreen_Data_t m_touch_data;
	
		void reset_data(void){
			memset(&m_touch_data, 0x00, sizeof(TouchScreen_Data_t));
		}
		
};

#endif
