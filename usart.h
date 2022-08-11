#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

void USART_init(long USART_BAUDRATE)
{
	UCSRB|=(1<<RXEN)|(1<<TXEN);  /* enables RX and TX */
	UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1); /* 8 bit data length */
	UBRRL=BAUD_PRESCALE; /* make sure the UBRR is set correctly */
	UBRRH=(BAUD_PRESCALE>>8);
}
unsigned char  USART_rxc()
{
	while ((UCSRA&(1<<RXC))==0); /* while data received is null */
	return UDR; /* read data from buffer */
}
void USART_txc(char ch)
{
	while (!(UCSRA&(1<<UDRE))); /* wait till UDRE = 1, buffer becomes empty and TX buffer is ready to receive new data */
	UDR=ch; /* return the given command */
}
void USART_send(char *str)
{
	while (*str!='\0')
	{
		USART_txc(*str);
		str++;
	}
}