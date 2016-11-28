#ifndef LCD_DISPLAY_H_
#define LCD_DISPLAY_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define LCD_DataNotCommand PB0
#define LCD_ReadNotWrite PB1
#define LCD_Enable PB2

#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdlib.h>

#include "USART.h"

void initLCD(void);
void LCDWriteLetter(char letter);
void LCDClearAndHome(void);
void LCDWriteInt(uint16_t number);

#endif
