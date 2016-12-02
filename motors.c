#include "motors.h"
// 4096 steps per rotation

uint8_t static timer_flag = 0;
static void initServoTimer(void);
static void initStepperTimer(void);
void initStepper1(void)
{
    DDRD |= 0xF0;
    initStepperTimer();

    // set to know starting value
    PORTD = 0x80 | (PORTD & 0x0F);
}


void step1fwd(int16_t numSteps)
{
    uint16_t jj;
    for(jj = 0; jj < numSteps; jj++)
    {
        if (PORTD & 0x10)
        {
            PORTD = (PORTD & 0x0F) | 0x8F;
        }
        else
        {
            PORTD = ((PORTD & 0xE0) >> 1) | (PORTD & 0x0F);
        }
    //     while (!timer_flag);
    //     timer_flag = 0;
        _delay_ms(1);
    }
}


void step1rev(int16_t numSteps)
{
    uint16_t jj;
    for(jj = 0; jj < numSteps; jj++)
    {

        if (PORTD & 0x80)
        {
            PORTD = (PORTD & 0x0F) | 0x1F;
        }
        else
        {
            PORTD = ((PORTD & 0x70) << 1) | (PORTD & 0x0F);
        }
        // while (!timer_flag);
        // timer_flag = 0;
        _delay_ms(1);
    }
}


void initStepper2(void)
{
    DDRC |= 0x0F;
    initStepperTimer();

    // set to known starting value
    PORTC = 0x08 | (PORTC & 0xF0);
}


void step2fwd(int16_t numSteps)
{
    uint16_t jj;
    for(jj = 0; jj < numSteps; jj++)
    {
        if (PORTC & 0x01)
        {
            PORTC = (PORTC & 0xF0) | 0xF8;
        }
        else
        {
            PORTC = ((PORTC & 0x0E) >> 1) | (PORTC & 0xF0);
        }
        // while (!timer_flag);
        // timer_flag = 0;
        _delay_ms(1);
    }
}


void step2rev(int16_t numSteps)
{
    uint16_t jj;
    for(jj = 0; jj < numSteps; jj++)
    {

        if (PORTC & 0x08)
        {
            PORTC = (PORTC & 0xF0) | 0xF1;
        }
        else
        {
            PORTC = ((PORTC & 0x07) << 1) | (PORTD & 0xF0);
        }
        // while (!timer_flag);
        // timer_flag = 0;
        _delay_ms(1);
    }
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
    TCCR0B = (1 << CS02);

    // Set compare match to control motor speed.
    OCR0A = 2;

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
    PORTB ^= 1 << PB5;
    timer_flag = 1;
}
