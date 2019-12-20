/** @file uart.c
 * 
 * Author : Mohamed yousry mohamed rashad. 
 * 
 * Description : implementations of basic uart transceive functions .
 * 
 * 
 * */
 
 #include "uart.h"
 
 
 void uartb_transmit ( uint8_t byte ) {
	 
	 while ( ! ( UCSRA & ( 1 << UDRE ) ) ) ;
	 UDR = byte ; 

 }
