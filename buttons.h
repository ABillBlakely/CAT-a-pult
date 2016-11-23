#ifndef TIMERS_H_
#define TIMERS_H_

#include <avr/interrupt.h>
#include <avr/io.h>

// All button properties should be changed here.
#define BTN1 PC0
#define BTN2 PC1
#define BTN3 PC2
#define BTN4 PC3
#define BTNMASK (1 << BTN1 | 1 << BTN2 | 1 << BTN3 | 1 << BTN4)
#define BTNPIN PINC
#define BTNPORT PORTC
#define BTNIPort PCIE1
#define BTNIMaskReg PCMSK1
#define BTNIVect PCINT1_vect

// Public Functions
void initBtns(void);
uint8_t getBtnFlag();

// Private functions
// static void btnPress(void);
// static void initPCINT(void);
// static void initDebounceTimer(void);

uint8_t static volatile timer_flag;
uint8_t static volatile btn_flag;
uint8_t static volatile old_pin_value;
uint8_t static volatile myINTCounter;


#endif


