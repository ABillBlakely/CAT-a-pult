#include "interface.h"

void testFunction(void);

int main(void)
{
    uint8_t restingstate = 1; //start in resting state
    uint8_t tensionedstate = 0;
    uint8_t releasedstate = 0;
    uint8_t pressed_button;

    initBtns();
    initLCD();
    initCatapult();

    sei();

    // testFunction();

    LCDWriteString("Press to tension");

    while(1)
    {
        pressed_button = getBtnFlag();
        switch(pressed_button)
        {
            case 1:
            { //button 1 tensions the band and releases pin
                if(restingstate && !tensionedstate && !releasedstate)
                {
                    LCDWriteString("Tensioning...");
                    setTension(); // tension band
                    restingstate = 0; //change states
                    tensionedstate = 1;
                    LCDWriteString("Press to fire");
                    break;
                }
                else if(!restingstate && tensionedstate && !releasedstate)
                {
                    LCDWriteString("FIRING");
                    releaseLatch(); //release pin upon second press
                    tensionedstate = 0; //change states
                    releasedstate = 1;
                    //delay_ms(5000); //wait 5s? relax band, maybe start timer instead?
                    LCDWriteString("Resetting...");
                    releaseTension();  //relax band
                }
                break;
            }
            case 2:
            { // button for detecting if lever arm has fallen back
                if(!restingstate && !tensionedstate && releasedstate)
                {
                    setLatch();
                    releasedstate = 0;
                    restingstate = 1;
                    LCDWriteString("Press to tension");
                }
                break;
            }
            default: break;
        }
    }
    return 0;
}

void testFunction(void)
{
    uint8_t pressed_button;
    
    while(1)
    {        
        pressed_button = getBtnFlag();
        LCDWriteInt(pressed_button);
        _delay_ms(1000);
    }
}
