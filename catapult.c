
#include "catapult.h"

int main(void)
{
    char letter = 'a';

    initBtns();
    initDebug();
    initLCD();

    sei();

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
