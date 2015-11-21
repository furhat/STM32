/**
 * @author  wei liu
 * @email   
 * @website 
 * @link    
 * @version v1.0
 * @ide     Keil uVision
 * @license GNU GPL v3
 * @brief  output log strings to LCD
 *				divide the LCD to 2 areas, log1 and log2
 *	
**/

#ifndef LOG___H
#define LOG___H

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f4xx.h"

#define LOG_MAX_SIZE 192

void initialize_log_func(void);
void log(uint8_t id, char* str);
	
/* C++ detection */
#ifdef __cplusplus
}
#endif


#endif



