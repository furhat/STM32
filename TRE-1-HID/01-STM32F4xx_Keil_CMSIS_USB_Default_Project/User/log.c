#include "log.h"
#include "tm_stm32f4_ili9341.h"



/* blank string used to flush before output */
static char str_blank[LOG_MAX_SIZE];

void initialize_log_func(void)
{
	//Initialize LCD
	TM_ILI9341_Init();
	//Fill with orange color
	TM_ILI9341_Fill(ILI9341_COLOR_ORANGE);
	//Rotate LCD
	TM_ILI9341_Rotate(TM_ILI9341_Orientation_Portrait_2);
	
	memset(str_blank, 0x20, LOG_MAX_SIZE);	
	str_blank[LOG_MAX_SIZE - 1] = '\0';	
}

void log(uint8_t id, char* str)
{
	if(id == 1)
	{
		TM_ILI9341_Puts(0, 160, str_blank, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
		TM_ILI9341_Puts(0, 160, str, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
	}
	else
	{
		TM_ILI9341_Puts(0, 10, str_blank, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
		TM_ILI9341_Puts(0, 10, str, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
	}
}
