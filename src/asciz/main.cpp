// Header file(s) for watchdogSetup(), init(), delay(), and RingBuffer & UARTClass objects
#include <Arduino.h>

#include "print_asciz.h"

extern "C" void application(const char * s);

int
main( void )
{
	watchdogSetup();
	init();
	delay(1);

	const char * s = " Hello world, the ANSWER is 42! @[]`{}~\r\n";

	RingBuffer rx_buffer;
	RingBuffer tx_buffer;
	UARTClass uart(UART, UART_IRQn, ID_UART, &rx_buffer, &tx_buffer);

	uart.begin(9600);

	for (;;)
	{
		printf("\nCPP: ");
		print_asciz(s);
		printf("ASM: ");
		application(s);
		delay(3000);
	}
	return 0;
}