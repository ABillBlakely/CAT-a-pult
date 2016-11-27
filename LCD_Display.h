#ifndef LCD_DISPLAY_H_
#define LCD_DISPLAY_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define LCD_DataNotCommand PB0
#define LCD_ReadNotWrite PB1
#define LCD_Enable PB2

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "USART.h"

void initLCD(void);
void LCD_write_letter(char letter);
void LCD_clear_and_home(void);

#endif
