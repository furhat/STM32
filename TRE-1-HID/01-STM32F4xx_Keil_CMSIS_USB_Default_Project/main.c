/*------------------------------------------------------------------------ 
 * CMSIS-RTOS 'main' function template 
 *----------------------------------------------------------------------*/  
#include "log.h"

extern int test_exi(void);
extern int test_ft5x06(void);


/* 
 * main: initialize and start the system 
 */ 
int main (void) { 
	
	
	/* test_exi(); */
	test_ft5x06();
	return 0; 
	
}
