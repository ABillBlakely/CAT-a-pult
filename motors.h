#ifndef MOTORS_H_
#define MOTORS_H_

#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

void initServo(void);
void rotateServo(uint8_t rotation);
void initStepper1(void);
void initStepper2(void);
void step1fwd(int16_t numSteps);
void step1rev(int16_t numSteps);
void step2fwd(int16_t numSteps);
void step2rev(int16_t numSteps);


#endif
