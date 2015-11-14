/**
 * @author  wei liu
 * @email   
 * @website 
 * @link    
 * @version v1.0
 * @ide     Keil uVision
 * @license GNU GPL v3
 * @brief  driver of FT5x06
 *				 - use tm_stm32_I2C libs
 *	
**/

#include "stm32f4xx.h"
#include "tm_stm32f4_i2c.h"
#include "tm_stm32f4_delay.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "tm_stm32f4_exti.h"

#ifndef TOUCH_DRIVER_FT5X06_H
#define TOUCH_DRIVER_FT5X06_H 100

/* Hardware resources definition */
#define FT_WAKE_RCC_AHB1Periph_GROUP	RCC_AHB1Periph_GPIOA
#define FT_WEAK_PORT	GPIOA
#define FT_WEAK_PIN		GPIO_Pin_10

#define FT_INT_PORT		GPIOA
#define FT_INT_PIN		GPIO_Pin_9

#define FT_I2C							I2C3
#define FT_I2C_PINSPACK			TM_I2C_PinsPack_1
#define FT_I2C_CLOCK				100000


/*#####################################################*/

typedef struct
{
	uint16_t x;
	uint16_t y;
	uint8_t  t_id;
	uint8_t  t_ev;	
}OneTouch_t;

typedef struct
{
	uint8_t gid;
	uint8_t touch_point;
	OneTouch_t touches[5];	
}TouchScreen_Data_t;



void initialize_touch_ft5x06(void);
void get_touch_data(TouchScreen_Data_t* a_touch_data);


#endif /* TOUCH_DRIVER_FT5X06_H */


