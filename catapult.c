
#include "catapult.h"

int main(void)
{
    char letter = 'a';

    initBtns();
    initDebug();
    initLCD();

    sei();

    DDRD |= 1 << PD6;

    while(1)
    {
        toggleLED();
        if (letter <= 'f')
        {
            LCDWriteLetter(letter);
            letter++;
        }
        else
        {
            LCDClearAndHome();
            letter = 'a';
        }

        rotate50();
        _delay_ms(1000);
        rotateLess();
        _delay_ms(1000);
        rotateMore();
        _delay_ms(1000);
    }
    return 0;
}


void toggleLED(void)
{
    PORTB ^= 1 << LED;
}


void initDebug(void)
{
    DDRB |= 1 << LED;
}

void rotate50(void)
{
    int jj = 0;

    DDRD |= 1 << PD6;

    for(jj = 0; jj < 1000; jj++)
    {
        PORTD ^= 1 << PD6;
        _delay_ms(1.5);

    }
    PORTD &= ~(1 << PD6);
}

void rotateLess(void)
{
    int jj = 0;

    DDRD |= 1 << PD6;

    for(jj = 0; jj < 500; jj++)
    {
        PORTD |= 1 << PD6;
        _delay_ms(1);
        PORTD &= ~(1 << PD6);
        _delay_ms(2);
    }
}
void rotateMore(void)
{
    int jj = 0;

    DDRD |= 1 << PD6;

    for(jj = 0; jj < 500; jj++)
    {
        PORTD |= 1 << PD6;
        _delay_ms(2);
        PORTD &= ~(1 << PD6);
        _delay_ms(1);
    }
}
