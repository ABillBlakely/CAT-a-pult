#include "LCD_Display.h"

static void LCDWriteCMD(char command);


void LCDWriteLetter(char letter)
{
    // Very sensitive to the order things happen.
    PORTB |= (1 << LCD_DataNotCommand); // RS
    LCDWriteCMD(letter);
    PORTB &= ~(1 << LCD_DataNotCommand);
    _delay_us(50);
}

void LCDClearAndHome(void)
{
    LCDWriteCMD(0x01);
}


void initLCD(void)
{
    DDRD = 0x0F;
    DDRB = 0x7 | 1<<PB5;
    
    PORTB &= ~(1<<LCD_Enable & 1<<LCD_ReadNotWrite & 1<<LCD_DataNotCommand);
    
    // PORTD = (PORTD & 0xF0);
    
    // Wait 20 ms or more after power, probs not needed.
    _delay_ms(50);

    // Set 2 lines, 5x8 font, 4 bit bus.
    LCDWriteCMD(0x20 | 0x02);
    LCDWriteCMD(0x20 | 0x08);
    //Turn on screen, cursor. Blink.
    LCDWriteCMD(0x8|0x4|0x2|0x1);
    // //Clear and return home.
    LCDWriteCMD(0x01);

}


static void LCDWriteCMD(char command)
{   
    // Not publicly accesible, 
    // write a function to send commands if additional commands are needed.
    
    // Send upper nibble:
    PORTB |= (1 << LCD_Enable);
    PORTD = (PORTD & 0xF0) | ((command >> 4) & 0x0F);
    PORTB &= ~(1 << LCD_Enable);
    PORTD = PORTD & 0xF0;
    _delay_us(1);

    // Send lower nibble.
    PORTB |= (1 << LCD_Enable);
    PORTD = (PORTD & 0xF0) | (command  & 0x0F);
    PORTB &= ~(1 << LCD_Enable);
    _delay_us(1);
    PORTB &= ~(1 << LCD_Enable);
    PORTD = PORTD & 0xF0;

    _delay_ms(2);
}
