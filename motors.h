#ifndef MOTORS_H_
#define MOTORS_H_

#ifndef F_CPU
#define F_CPU 16000000
#endif

// Set STEP_INTERVAL to control motor speed.
// Larger is slower, max is 255.
// Significant torque is lost  below about 50,
// Unloaded movement stops below 30.

#define STEP_INTERVAL 60

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

void initServo(void);
void rotateServo(uint8_t rotation);
void initStepper1(void);
void initStepper2(void);
void step1fwd(uint16_t numSteps);
void step1rev(uint16_t numSteps);
void step2fwd(uint16_t numSteps);
void step2rev(uint16_t numSteps);


#endif
