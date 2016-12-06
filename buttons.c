#include "buttons.h"

static void btnPress(void);
static void initPCINT(void);
static void initDebounceTimer(void);

//
// Public Functions
//
uint8_t getBtnFlag(void)
{
    uint8_t current_flag;

    current_flag = btn_flag;
    btn_flag = 0;
    return current_flag;
}


void initBtns(void)
{
    // Configure Pullups
    BTNPORT |= BTNMASK;

    initPCINT();
    initDebounceTimer();
}


//
// Private Functions
//
static void btnPress(void)
{
    if (!(BTNPIN & (1 << BTN1)))
        btn_flag = 1;

    else if (!(BTNPIN & (1 << BTN2)))
        btn_flag = 2;

    else
        btn_flag = 0;
}


static void initPCINT(void)
{
    // Enable PCINT for correct port.
    PCICR = (1 << BTNIPort);

    // Enable PCINT on btn pins.
    BTNIMaskReg |= BTNMASK;

    // Clear all PCINT flags.
    PCIFR = 0x7;
}


static void initDebounceTimer(void)
{
    // Timer overflow mode Normal Mode
    TCCR2A = 0x00;

    // Timer clk = system clk / 1024
    TCCR2B = (1<<CS22) | (1<<CS21) | (1<<CS20);

    // Clear previous timer overflow
    TIFR2 = 0x07;

    // Initialize counter variable.
    myINTCounter = 0;
}


ISR(TIMER2_OVF_vect)
{
    // Timer is enabled by PCI interrupt vector.
    myINTCounter++;
    if (myINTCounter == 8)
    {
        if(old_pin_value == (BTNPIN & BTNMASK))
            btnPress();
        myINTCounter = 0;
        TIMSK2 = 0x00;
    }
}


ISR(BTNIVect)
{
    // Check that any pin had falling edge.
    if ((BTNPIN & BTNMASK) ^ BTNMASK)
    {
        // If falling edge store value of all button pins
        old_pin_value = (BTNPIN & BTNMASK);

        // Clear count and start counter.
        myINTCounter = 0;
        TIMSK2 = 1 << TOIE2;
    }
}
