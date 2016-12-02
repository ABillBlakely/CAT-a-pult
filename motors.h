#ifndef MOTORS_H_
#define MOTORS_H_

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
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
