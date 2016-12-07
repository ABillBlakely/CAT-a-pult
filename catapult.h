#ifndef catapult_H_
#define catapult_H_

#define FULLTURN 2048
#define LATCHTURN 600
#define TENSIONTURN 2500

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include "motors.h"

void initCatapult(void);
void setLatch(void);
void releaseLatch(void);
void setTension(void);
void releaseTension(void);


#endif

