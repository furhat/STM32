/*------------------------------------------------------------------------ 
 * File LED.h 
 *----------------------------------------------------------------------*/ 
#ifndef LED_DEFINES_H
#define LED_DEFINES_H

void LED_Initialize ( void ); // Initialize GPIO 
void LED_On ( void ); // Switch Pin on 
void LED_Off ( void ); // Switch Pin off 
 
void blink_LED ( void const *argument ); // Blink LEDs in a thread 
void Init_BlinkyThread ( void ); // Initialize thread

#endif
