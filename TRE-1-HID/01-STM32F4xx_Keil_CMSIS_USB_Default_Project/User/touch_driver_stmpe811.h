#ifndef TOUCH_DRIVER_STMPE811___H
#define TOUCH_DRIVER_STMPE811___H

#include "stm32f4xx.h"
#include "touch_driver.h"


class touch_driver_stmpe811:public touch_driver_t
{
	public:
		virtual void initilize(void);
		virtual const TouchScreen_Data_t* get_touch_points(void);		
};

#endif
