#include "motors.h"
#define MDELAY 3

// 2048 steps per rotation

uint8_t static volatile timer_flag = 0;
uint8_t static volatile SavedPosition1 = 0x80;
uint8_t static volatile SavedPosition2 = 0x08;

static void initServoTimer(void);
static void initStepperTimer(void);


void initStepper1(void)
{
    DDRD |= 0xF0;
    // initStepperTimer();
}


void step1fwd(uint16_t numSteps)
{
    uint16_t jj;

    // Restore state
    PORTD = (SavedPosition1 & 0xF0) | (PIND & 0x0F);

    for(jj = 0; jj < numSteps; jj++)
    {
        if (PIND & 0x10)
        {
            PORTD = (PIND & 0x0F) | 0x8F;
        }
        else
        {
            PORTD = ((PIND & 0xE0) >> 1) | (PIND & 0x0F);
        }
        while (!timer_flag);
        timer_flag = 0;
    }

    // Save state and turn off pin while motor is not running.
    SavedPosition1 = PIND;
    PORTD = PIND & 0x0F;
}


void step1rev(uint16_t numSteps)
{
    uint16_t jj;

    // Restore state
    PORTD = (SavedPosition1 & 0xF0) | (PIND & 0x0F);

    for(jj = 0; jj < numSteps; jj++)
    {

        if (PIND & 0x80)
        {
            PORTD = (PIND & 0x0F) | 0x1F;
        }
        else
        {
            PORTD = ((PIND & 0x70) << 1) | (PIND & 0x0F);
        }
        while (!timer_flag);
        timer_flag = 0;
    }
    SavedPosition1 = PIND;
    PORTD = PIND & 0x0F;
}


void initStepper2(void)
{
    DDRC |= 0x0F;
    initStepperTimer();
}


void step2fwd(uint16_t numSteps)
{
    uint16_t jj;

    // Restore state
    PORTC = (SavedPosition2 & 0x0F) | (PINC & 0xF0);

    for(jj = 0; jj < numSteps; jj++)
    {
        if (PINC & 0x01)
        {
            PORTC = (PINC & 0xF0) | 0xF8;
        }
        else
        {
            PORTC = ((PINC & 0x0E) >> 1) | (PINC & 0xF0);
        }
        while (!timer_flag);
        timer_flag = 0;
    }
    // Store State
    SavedPosition2 = PINC;
    // PORTC = PINC & 0xF0;
}


void step2rev(uint16_t numSteps)
{
    uint16_t jj;

    // Restore state
    PORTC = (SavedPosition2 & 0x0F) | (PINC & 0xF0);

    for(jj = 0; jj < numSteps; jj++)
    {

        if (PINC & 0x08)
        {
            PORTC = (PINC & 0xF0) | 0xF1;
        }
        else
        {
            PORTC = ((PINC & 0x07) << 1) | (PINC & 0xF0);
        }
        while (!timer_flag);
        timer_flag = 0;
    }
    // Store State
    SavedPosition2 = PINC;
    PORTC = PINC & 0xF0;
}


void rotateServo(uint8_t rotation)
{
    // Accepts a value from 0 to 10 that adjusts the rotation.
    OCR0A = 20 + 5 * rotation;
}


void initServo(void)
{
    initServoTimer();
}


static void initStepperTimer(void)
{
     // Set timer mode to CTC.
    TCCR0A = (1 << WGM01);

    // Set prescaler to 1024 for a minimum frequency of 32.8 Hz.
    TCCR0B = (1 << CS02) | (1 << CS00);

    // Set compare match to control motor speed.
    // Torque lost  below 45, stop spinning below 30
    OCR0A = STEP_INTERVAL;

    TIMSK0 = 1 << OCIE0A;
}


static void initServoTimer(void)
{
    /* Initialize Phase correct PWM mode.
    *
    * Excerpt from the data sheet:

    The counter counts repeatedly from BOTTOM to TOP and then from TOP to BOT-
    TOM. TOP is defined as 0xFF when WGM2:0 = 1 In non-inverting Compare
    Output mode, the Output Compare (OC0x) is cleared on the compare
    matchbetween TCNT0 and OCR0x while upcounting, and set on the compare
    match while downcounting. In inverting Output Compare mode, the operation
    is inverted. The dual-slope operation haslower maximum operation frequency
    than single slope operation. However, due to the symmet-ric feature of the
    dual-slope PWM modes, these modes are preferred for motor
    controlapplications.

    *
    */

    // Set output to Phase correct PWM.
    TCCR0A |= 1 << WGM00;

    // Non inverted PWM output on OC0A (pin PD6)
    DDRD |= 1 << PD6;
    TCCR0A |= 1 << COM0A1;

    // Set prescaler to 1024 for a frequency of 30.6 Hz.
    TCCR0B = (1 << CS02);

    // Setting OCR0A sets the positive width of the PWM. Setting to 0 is off.
    OCR0A = 0;

}

ISR(TIMER0_COMPA_vect)
{
    timer_flag = 1;
}
