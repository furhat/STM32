#ifndef TOUCH_DRIVER_FT5X06_CLASS___H
#define TOUCH_DRIVER_FT5X06_CLASS___H

#include "stm32f4xx.h"
#include "touch_driver.h"

/*#####################################################*/


class touch_driver_ft5x06:public touch_driver_t
{
	public:
		virtual void initilize(void);
		virtual const TouchScreen_Data_t* get_touch_points(void);
		uint16_t get_exti_pin(void);
		
	private:
		void initialize_wake_output(void);
		int8_t initialize_EXINT_input(void);
	  void intialize_I2C(void);
		void formalize_one_touch_data(OneTouch_t* a_out_touch, const uint8_t* a_raw_buf);
		void adjust_one_coord(OneTouch_t* a_p);	
		void adjust_coords(void);
		void read_touch_data(void);
		
	
};

#endif /* TOUCH_DRIVER_FT5X06_H */


