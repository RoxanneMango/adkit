//#include "i2c_scanner.h" //i2c_scanner();

#include <Wire.h>
#include <RTCDue.h>

#include "draw.h"

// Due	20 (SDA), 21 (SCL), SDA1, SCL1

int
main( void )
{
	// INIT_ARDUINO_DUE
	watchdogSetup();
	init();
	delay(1);
	
	// UART
	RingBuffer rx_buffer;
	RingBuffer tx_buffer;
	UARTClass uart(UART, UART_IRQn, ID_UART, &rx_buffer, &tx_buffer);
	//
	uart.begin(9600);
	
	// OLED_DISPLAY
	Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
	display.clearDisplay();
	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
	{ 
		printf("SSD1306 allocation failed\n\r");
		for(;;)
		{
			// "DON'T FORGET: YOU'RE HERE FOREVER" - Mr Burns
		}
	}

	// REAL_TIME_CLOCK
	RTCDue rtc(RC);
	//
	uint8_t seconds = 50;
	uint8_t minutes = 59;
	uint8_t hours = 12;
	//
	const uint8_t day = 1;
	const uint8_t month = 1;
	const uint16_t year = 1970;
	//
	rtc.begin();
	//
	rtc.setHours(hours);
	rtc.setMinutes(minutes);
	rtc.setSeconds(seconds);
	//
	rtc.setDay(day);
	rtc.setMonth(month);
	rtc.setYear(year);

	// CONSTEXPR_LOOKUP_TABLES
	constexpr LookupTable_time<24,18,12> lookup_table_h;
	constexpr LookupTable_time<60,24,60> lookup_table_m;
	constexpr LookupTable_time<60,24,60> lookup_table_s;
	//
	constexpr LookupTable_clock_face<12> clock_face;

	display.clearDisplay();
	draw_clock_face(display, clock_face);

	// CHANGE_TIME_BUTTONS // Using 10k pull-down resistors
	const int minute_button = 6;
	const int hour_button = 7;
	//
	pinMode(minute_button, INPUT);
	pinMode(hour_button, INPUT);
	//
	bool minute_state = 0;
	bool hour_state = 0;
	// LATCH
	bool minute_pressed = 0;
	bool hour_pressed = 0;
	
	for (;;)
	{
		minute_state = digitalRead(minute_button);
		hour_state = digitalRead(hour_button);
		//
		minute_pressed = !minute_state ? 0 : minute_pressed;
		hour_pressed = !hour_state ? 0 : hour_pressed;
		//
		if(minute_state && !minute_pressed)
		{
			minute_pressed = 1;
			rtc.setMinutes( hour_state ? ( rtc.getMinutes() == 0 ? 59 : minutes-1 ) : ( rtc.getMinutes() == 59 ? 0 : minutes+1 ));
		}
		if(hour_state && !hour_pressed)
		{
			hour_pressed = 1;
			rtc.setHours( minute_state ? ( rtc.getHours() == 1 ? 12 : hours-1 ) : ( rtc.getHours() == 12 ? 1 : hours+1 ) );
		}
		
		if((rtc.getSeconds() != seconds) || hour_pressed || minute_pressed)
		{
			draw_clock_face(display, clock_face);
			redraw_clock_face_elements(display);
			//
			draw_second(display, rtc.getSeconds(), 1, lookup_table_s);
			draw_minute(display, rtc.getMinutes(), 1, lookup_table_m);
			draw_hour(display, rtc.getHours(),1, lookup_table_h);
			//
			display.display(); 
			//
			seconds=rtc.getSeconds();
			minutes=rtc.getMinutes();
			hours=rtc.getHours();
			//
			display.clearDisplay();
		}
	}
	return 0;
}

	// Wire definition:
	// TwoWire Wire = TwoWire(WIRE_INTERFACE, Wire_Init, Wire_Deinit);
	// arduino/hardware/sam/1.6.12/libraries/Wire/src/Wire.cpp

	// WIRE_INTERFACE definition:
	// arduino/hardware/sam/1.6.12/variants/arduino_due_x/variant.h
	// #define PIN_WIRE_SDA         (20u)
	// #define PIN_WIRE_SCL         (21u)
	// #define WIRE_INTERFACE       TWI1
	// #define WIRE_INTERFACE_ID    ID_TWI1
	// #define WIRE_ISR_HANDLER     TWI1_Handler
	// #define WIRE_ISR_ID          TWI1_IRQn
	
	// WIRE_INTERFACE definition definitions:
	// arduino/hardware/sam/1.6.12/system/CMSIS/Device/ATMEL/sam3xa/include/sam3x8e.h
	// TWI1_IRQn            = 23, /**< 23 SAM3X8E Two-Wire Interface 1 (TWI1) */
	// void TWI1_Handler       ( void );
	// #define ID_TWI1   (23) /**< \brief Two-Wire Interface 1 (TWI1) */
	// #define TWI1       (0x40090000U) /**< \brief (TWI1      ) Base Address */
