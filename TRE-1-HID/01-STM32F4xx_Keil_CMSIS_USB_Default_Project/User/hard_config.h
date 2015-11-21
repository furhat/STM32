#ifndef TOUCH_HARD_CONFIG___H
#define TOUCH_HARD_CONFIG___H


#include "stm32f4xx.h"
#include "touch_defines.h"
#include "touch_driver.h"


class hard_config_t
{
	public:
		touch_driver_t* get_touch_driver(void);

	

};


#endif
