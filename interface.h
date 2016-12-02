#ifndef interface_H_
#define interface_H_


#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include "LCD_display.h"
#include "buttons.h"
#include "motors.h"
#include "catapult.h"
#define LED PB5

void toggleLED(void);
void initDebug(void);


#endif

