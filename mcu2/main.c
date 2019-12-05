/** @file main.c
 * 
 * Author : Mohamed yousry mohamed rashad 
 * 
 * Subject : VLSI Project .
 * 
 * 
 * This file is the main application c file , to be built . 
 * Dependencies : driver files in the driver folder and general defines in the header files in the appconfig folder .
 * to configure the app for your liking : change the configuration in the appconfig folder .
 * 
 */ 


#include "appconfig/appconfig.h"
#include "drivers/uart/uart.h"
#include "DS18B20/ds18.h"





int main ( void ) {

// init uart module at 9600 	
uart_init();

sc_pad scratchpad ;

ds18_read_spad( &scratchpad ); 	


while(1){
	uart_print("\n REG0 : "); 
	uart_print_hex( scratchpad.temp_l);
	uart_print("\n REG1 : "); 
	uart_print_hex( scratchpad.temp_h);
	uart_print("\n REG2 : "); 
	uart_print_hex( scratchpad.alarm_h);
	uart_print("\n REG3 : "); 
	uart_print_hex( scratchpad.alarm_l);
	uart_print("\n REG4 : "); 
	uart_print_hex( scratchpad.config);
	uart_print("\n REG5 : "); 
	uart_print_hex( scratchpad.reserved_1);
	uart_print("\n REG6 : "); 
	uart_print_hex( scratchpad.reserved_2);
	uart_print("\n REG7 : "); 
	uart_print_hex( scratchpad.reserved_3);
	uart_print("\n REG8 : "); 
	uart_print_hex( scratchpad.crc);
	 
	 _delay_ms(2000);

	
}
	
	
	
	
}
