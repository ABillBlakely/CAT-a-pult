#ifndef USART_H_
#define USART_H_

#include <stdlib.h>                 // Standard C library
#include <avr/io.h>                 // Input-output ports, special registers
#include <stdio.h>

#define BAUD_PRESCALE 103

void usart_init(uint16_t baudin, uint32_t clk_speedin);
void usart_send(uint8_t data);
void usart_hex(int hex_val);
uint8_t  usart_recv(void);
uint8_t  usart_istheredata(void);
int usart_test (void);

#endif
