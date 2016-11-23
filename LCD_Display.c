#include "LCD_Display.h"

void LCD_write_cmd(char command)
{
    // Requires longer delay because some commands take > 1.5 ms
    PORTB |= (1<<LCD_Enable);
    PORTD = command;
    _delay_us(1);
    PORTB &= ~(1<<LCD_Enable);
    _delay_ms(2);
}

void LCD_Init(void)
{
    DDRD = 0xFF;
    DDRB |= ((1<<LCD_Enable) & (1<<LCD_ReadNotWrite) & (1<<LCD_DataNotCommand));

    // Wait 20 ms or more after power, probs not needed.
    _delay_ms(20);
    // Set 2 lines, 5x7 font.
    LCD_write_cmd(0x20|0x10|0x8);
    //Clear and return home.
    LCD_write_cmd(0x01);
    //Turn on screen, cursor. Blink.
    LCD_write_cmd(0x8|0x4|0x2|0x1);
}


void LCD_write_letter(char letter)
{
    // Very sensitive to the order things happen.
    PORTB |= (1<<LCD_DataNotCommand); // RS
    PORTB |= (1<<LCD_Enable); // E
    PORTD = letter;
    _delay_us(1);
    PORTB &= ~(1<<LCD_Enable);
    PORTB &= ~(1<<LCD_DataNotCommand);
    _delay_us(50);
}

void LCD_clear_and_home(void)
{
    LCD_write_cmd(0x01);
}
