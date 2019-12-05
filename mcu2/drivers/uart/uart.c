/** @file uart.c
 * 
 * Author : Mohamed yousry mohamed rashad. 
 * 
 * Description : implementations of basic uart transceive functions .
 * 
 * 
 * */
 
 #include "uart.h"
 
 
 
 void uart_sendb( uint8_t my_uint8 ) {
	 UDR = my_uint8 ; 
	 while ( ! ( UCSRA & (  1 << UDRE ) ) );
 }
 
 
 uint8_t uart_recb( void ) {
	 while ( ! ( UCSRA & ( 1 << RXC ) ) ) ;
	 return UDR; 
 }
 
 
 void uart_senda( uint8_t* ptr , uint8_t len , uint8_t startc , uint8_t endc ) {
	 if ( startc ) { uart_sendb( startc) ;} 
	 for ( uint8_t i = 0 ; i <= len-1 ; i++){
		 uart_sendb(*(ptr+i) ) ;
	}
	if ( endc ) { uart_sendb( endc) ;} 
}



void uart_print( uint8_t* str ){
	
	for(;(*(str) )!= 0 ;++str ){
		uart_sendb( *str ) ;

}
}


void uart_print_hex ( uint8_t hex_val ){
	
	uint8_t itoa_buff[5] ;
	
	itoa( hex_val , itoa_buff , 16 ) ;
	
	uart_print( itoa_buff ) ;
	
}
	
