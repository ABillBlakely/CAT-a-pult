#include "motors.h"


static void initTimer0(void);

void rotatePercent(uint16_t rotation)
{
    // Accepts a value from 0 to 10 that adjusts the rotation.

    // OCR0A = (rotation * 255 * 9) / 330;
    OCR0A = 20 + 5 * rotation;
}

void initMotor(void)
{
    initTimer0();
}


static void initTimer0(void)
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

}