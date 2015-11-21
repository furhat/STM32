#include "touch_driver_stmpe811.h"
#include "tm_stm32f4_stmpe811.h"
#include "tm_stm32f4_ili9341.h"

#include "stdio.h"


void touch_driver_stmpe811::initilize(void)
{
	TM_STMPE811_Init();
}

/*
* stmpe811 only support one point
*/
const TouchScreen_Data_t* touch_driver_stmpe811::get_touch_points(void)
{
	static const uint16_t c_max_len = 320;
	static const uint16_t c_max_wid = 240;
	
	char str[30];
	
	reset_data();
	TM_STMPE811_TouchData l_touch_data;
	if(TM_STMPE811_ReadTouch(&l_touch_data) == TM_STMPE811_State_Pressed){
		
		//Touch valid
		sprintf(str, "Pressed    \n\nX: %03d\nY: %03d", l_touch_data.x, l_touch_data.y);
		TM_ILI9341_Puts(20, 80, str, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
		
		// set point number = 1 and id = 0 constantly as this IC can only support one point
		m_touch_data.touch_point = 1;
		m_touch_data.touches[0].t_id = 0;
		
		m_touch_data.touches[0].x = c_max_wid - l_touch_data.x;
		m_touch_data.touches[0].y = c_max_len - l_touch_data.y;
	}else	{
		sprintf(str, "Not Pressed\n\n       \n      ");
		TM_ILI9341_Puts(20, 80, str, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
	}
	
	return &m_touch_data;
}

