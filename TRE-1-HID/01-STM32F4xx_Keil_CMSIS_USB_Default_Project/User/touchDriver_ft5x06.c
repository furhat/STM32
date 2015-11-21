#include "touchDriver_ft5x06.h"
#include "string.h"

#define FT_ADDRESS 0x38
#define FT_READ_LENGTH	(0x1E + 0x01) 

#define IND_GID				0x01
#define IND_TD_STATUS	0x02
#define IND_TOUCH_1		0x03
#define IND_TOUCH_DIF	0x06


static void initialize_wake_output(void);
static int8_t initialize_EXINT_input(void);


static void initialize_wake_output(void)
{	
	GPIO_InitTypeDef GPIO_InitDef;
	
	RCC_AHB1PeriphClockCmd(FT_WAKE_RCC_AHB1Periph_GROUP, ENABLE);

	GPIO_InitDef.GPIO_Pin = FT_WEAK_PIN;
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;
	//Initialize pins
	GPIO_Init(FT_WEAK_PORT, &GPIO_InitDef);
	
	/* outupte high to wake */
	GPIO_SetBits(FT_WEAK_PORT, FT_WEAK_PIN);
	
}

static int8_t initialize_EXINT_input(void)
{
	/* initilize GPIO for INT */
	/* Attach interrupt on pin PA0 = External line 0 */
	/* Button connected on discovery boards */
	if (TM_EXTI_Attach(FT_INT_PORT, FT_INT_PIN, TM_EXTI_Trigger_Falling) != TM_EXTI_Result_Ok) 
	{
		/* TM_DISCO_LedOn(LED_RED); */
		return 1;
	}
	return 0;	
}

static void intialize_I2C(void)
{
	/* Initialize Delay */
	TM_DELAY_Init();
	/* Initialize I2C */
	TM_I2C_Init(FT_I2C, FT_I2C_PINSPACK, FT_I2C_CLOCK);
}
	
	
	
void initialize_touch_ft5x06(void)
{
	int8_t l_fail = 0;
	
	/* initilize GPIO for WAKE */
	initialize_wake_output();
	
	/* initilize /INT */
	l_fail = initialize_EXINT_input();
	
	intialize_I2C();
	
	if(l_fail)
	{		
	}		
}

void formalize_one_touch_data(OneTouch_t* a_out_touch, const uint8_t* a_raw_buf)
{	
	a_out_touch->x = (uint16_t)(*a_raw_buf & 0x0F) << 8 | *(a_raw_buf + 1);
	a_out_touch->y = (uint16_t)(*(a_raw_buf + 2) & 0x0F) << 8 | *(a_raw_buf + 3);
	a_out_touch->t_id = *(a_raw_buf + 2) >> 4;
	a_out_touch->t_ev = *a_raw_buf >> 6;	
}

void get_touch_data(TouchScreen_Data_t* a_touch_data)
{
	uint8_t l_read_buffer[FT_READ_LENGTH] = {0};
	
	memset(a_touch_data, 0x00, sizeof(TouchScreen_Data_t));
	
	TM_I2C_ReadMulti(FT_I2C, 0x70, 0x00, l_read_buffer, FT_READ_LENGTH);
	a_touch_data->touch_point = l_read_buffer[IND_TD_STATUS] & 0x0F;
	switch(a_touch_data->touch_point)
	{
		case 5:
			formalize_one_touch_data(&a_touch_data->touches[4], l_read_buffer + IND_TOUCH_1 + IND_TOUCH_DIF * 4);			
		case 4:
			formalize_one_touch_data(&a_touch_data->touches[3], l_read_buffer + IND_TOUCH_1 + IND_TOUCH_DIF * 3);
		case 3:
			formalize_one_touch_data(&a_touch_data->touches[2], l_read_buffer + IND_TOUCH_1 + IND_TOUCH_DIF * 2);
		case 2:
			formalize_one_touch_data(&a_touch_data->touches[1], l_read_buffer + IND_TOUCH_1 + IND_TOUCH_DIF);
		case 1:
			formalize_one_touch_data(&a_touch_data->touches[0], l_read_buffer + IND_TOUCH_1);
			break;
		default:
			break;			
	}
	a_touch_data->gid = l_read_buffer[IND_GID];
	
}


