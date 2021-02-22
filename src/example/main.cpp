// Header file(s) for watchdogSetup(), init(), delay(), and RingBuffer & UARTClass objects
#include <Arduino.h>

int
main( void )
{
	watchdogSetup();
	init();
	delay(1);

	RingBuffer rx_buffer;
	RingBuffer tx_buffer;
	UARTClass uart(UART, UART_IRQn, ID_UART, &rx_buffer, &tx_buffer);

	uart.begin(9600);
	for (;;)
	{
		printf("Hello world!\r\n");
		delay(3000);
	}
	return 0;
}