#include "USART.h"

void usart_init(uint16_t baudin, uint32_t clk_speedin)
{
    uint32_t ubrr = (clk_speedin/16UL)/baudin-1;
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    /*UBRR0H = (BAUD_PRESCALE>>8);
    UBRR0L = BAUD_PRESCALE;*/
    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
    UCSR0A &= ~(1<<U2X0);
}

/*the send function will put 8bits on the trans line. */
void usart_send( uint8_t data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) );
    /* Put data into buffer, sends the data */
    UDR0 = data;
}


void usart_hex(int hex_val)
{
    int jj = 0;
    char string[3];
    sprintf(string, "%X", hex_val);
    while(string[jj] != '\0')
    {
        usart_send(string[jj]);
        jj++;
    }
    usart_send('\n');
    usart_send('\r');
}


/* the receive data function. Note that this a blocking call
Therefore you may not get control back after this is called
until a much later time. It may be helpfull to use the
istheredata() function to check before calling this function
    @return 8bit data packet from sender
*/
uint8_t  usart_recv(void)
{
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) )
    ;
    /* Get and return received data from buffer */
    return UDR0;
}

/* function check to see if there is data to be received
    @return true is there is data ready to be read */
uint8_t  usart_istheredata(void)
{
     return (UCSR0A & (1<<RXC0));
}

int usart_test (void)
{
    usart_init(9600, 16000000 );

    while(1)
    {
        char received;
        while (usart_istheredata())
        {
            received = usart_recv();
            switch (received)
            {
                case 'L': received = '1'; break;
                case 'E': received = '3'; break;
                case 'T': received = '7'; break;
                case '\n':
                case '\r':
                    usart_send('\n');
                    break;
                default: break;
            }
            usart_send(received);
            }
        }
    return 0;
}

