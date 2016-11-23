
#include "catapult.h"

int main(void)
{
    uint8_t current_btn = 0;

    initBtns();
    initDebug();

    sei();

    while(1)
    {
        current_btn = getBtnFlag();
        switch (current_btn)
        {
            case 1: toggleLED(); break;
            case 2: toggleLED(); break;
            case 3: toggleLED(); break;
            case 4: toggleLED(); break;
            default: break;
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
