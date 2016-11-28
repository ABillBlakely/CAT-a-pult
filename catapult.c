
#include "catapult.h"

int main(void)
{
    char letter = 'a';
    uint8_t jj = 0;

    initBtns();
    initDebug();
    initLCD();
    initMotor();
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
        for (jj = 0; jj <= 10; jj++)
            {
                rotatePercent(jj);
                LCDWriteLetter(0x30 | jj );
                _delay_ms(2000);
            }

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


