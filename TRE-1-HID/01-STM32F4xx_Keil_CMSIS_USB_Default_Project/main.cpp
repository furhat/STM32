/*------------------------------------------------------------------------ 
 * CMSIS-RTOS 'main' function template 
 *----------------------------------------------------------------------*/  
#include "log.h"
#include "defines.h"
#include "tm_stm32f4_disco.h"
#include "touch_point.h"
#include "stdio.h"

extern "C" 
{
	int test_exi(void);
	int test_ft5x06(void);		
	int test_STMPE811(void);
}

extern int touch_mouse(void);


/* 
 * main: initialize and start the system 
 */ 
int main (void) { 
	
//	touch_point_t l_touch;
//	l_touch.reset();
//	printf("well done\n");
	
	
	// test_exi();
	// test_ft5x06();
	touch_mouse();
	// test_STMPE811();
	return 0; 
	
}
