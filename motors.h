#ifndef MOTORS_H_
#define MOTORS_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

void initMotor(void);
void rotateMotor(uint8_t rotation);



#endif
