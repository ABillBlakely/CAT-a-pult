#include "LCD_Display.h"

static void LCD_write_cmd(char command)
{   // Requires longer delay because some commands take > 1.5 ms

    // Send upper nibble:
    PORTB |= (1 << LCD_Enable);
    PORTD = (PORTD & 0xF0) | ((command >> 4) & 0x0F);
    PORTB &= ~(1 << LCD_Enable);
    PORTD = PORTD & 0xF0;
    _delay_us(1);

    // usart_hex(PORTD);
    // Send lower nibble.
    PORTB |= (1 << LCD_Enable);
    PORTD = (PORTD & 0xF0) | (command  & 0x0F);
    PORTB &= ~(1 << LCD_Enable);
    _delay_us(1);
    PORTB &= ~(1 << LCD_Enable);
    PORTD = PORTD & 0xF0;

    _delay_ms(2);
}

static void LCD_write_half_cmd(char command)
{
    // Send lower nibble.
    PORTB |= (1 << LCD_Enable);
    PORTD = (PORTD & 0xF0) | (command  & 0x0F);
    PORTB &= ~(1 << LCD_Enable);
    // usart_hex(PORTB);
    // _delay_ms(2000);
}
void initLCD(void)
{
    DDRD = 0x0F;
    DDRB = 0x7 | 1<<PB5;
    PORTB &= ~(1<<LCD_Enable & 1<<LCD_ReadNotWrite & 1<<LCD_DataNotCommand);

    usart_init(9600, 16000000);

    // Wait 20 ms or more after power, probs not needed.
    _delay_ms(50);

    // LCD_write_half_cmd(0x2);
    // LCD_write_half_cmd(0x2);
    // LCD_write_half_cmd(0x2);
    // LCD_write_half_cmd(0x8|0x4);
    // _delay_us(50);
    // LCD_write_half_cmd(0x0);
    // LCD_write_half_cmd(0xF);
    // _delay_us(50);
    // LCD_write_half_cmd(0x0);
    // LCD_write_half_cmd(0x1);

    // Set 2 lines, 5x8 font, 4 bit bus.
    LCD_write_cmd(0x20 | 0x02);
    LCD_write_cmd(0x20 | 0x08);
    //Turn on screen, cursor. Blink.
    LCD_write_cmd(0x8|0x4|0x2|0x1);
    //Clear and return home.
    LCD_write_cmd(0x01);

    PORTB ^= 1 << PB5;
    _delay_ms(2000);
}


void LCD_write_letter(char letter)
{
    // Very sensitive to the order things happen.
    PORTB |= (1 << LCD_DataNotCommand); // RS
    PORTB |= (1 << LCD_Enable); // E
    PORTD = letter;
    _delay_us(1);
    PORTB &= ~(1 << LCD_Enable);
    PORTB &= ~(1 << LCD_DataNotCommand);
    _delay_us(50);
}

void LCD_clear_and_home(void)
{
    LCD_write_cmd(0x01);
}
