
#include "interface.h"

int main(void)
{
    initLCD();
    initCatapult();
    sei();


    while(1)
    {
        LCDWriteInt(1);
        setLatch();

        LCDWriteInt(2);
        setTension();

        LCDWriteInt(3);
        releaseLatch();

        LCDWriteInt(4);
        releaseTension();
        toggleLED();
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


