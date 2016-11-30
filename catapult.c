
#include "catapult.h"

int main(void)
{
    uint8_t pressed_button;
    initBtns();
    initDebug();
    initLCD();
    initMotor();
    sei();


    while(1)
    {
        pressed_button = getBtnFlag();
        switch(pressed_button)
        {
            case 1: rotateMotor(0);
                    LCDClearAndHome();
                    LCDWriteInt(0);
                    LCDWriteLetter('%');
                    toggleLED();
                    break;
            case 2: rotateMotor(4);
                    LCDClearAndHome();
                    LCDWriteInt(4*10);
                    LCDWriteLetter('%');
                    toggleLED();
                    break;
            case 3: rotateMotor(6);
                    LCDClearAndHome();
                    LCDWriteInt(6*10);
                    LCDWriteLetter('%');
                    toggleLED();
                    break;
            case 4: rotateMotor(10);
                    LCDClearAndHome();
                    LCDWriteInt(100);
                    LCDWriteLetter('%');
                    toggleLED();
                    break;
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


