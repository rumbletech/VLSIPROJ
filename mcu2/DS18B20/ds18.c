/** @file ds18.c
 *
 * Author : Mohamed yousry mohamed rashad . 
 * Description : This file contains implemenations of functions that read temperature data and/or set alarm mode for the temp module .
 * 
 * */
 
 
 
 
 #include "ds18.h"
 
 
 
 
 void ds18_reset( void ) {
	 
	 //pull tsin low  _________
	 tsen_OL();
	 // wait for minimum Treset
	 _delay_us( T_RESET_PULSE ) ; 
	 // go back to input 
	 tsen_pin_in();
	 //wait for presence pulse 
	 while( tsen_pin & ( 1 << tsen_pin_num ) );
	 //wait for presence pulse to end
	 while( !(tsen_pin & ( 1 << tsen_pin_num ) ) );
	// initialization sequence done 
}



void ds18_wrb ( uint8_t cmd ) {
	
	for ( uint8_t i=0 ; i <=7 ; i++ ) {
		
	// LOW PULSE FOR T_BIT_INIT	
	tsen_OL(); 
	_delay_us(T_BIT_INIT);
	//Write the bit 
	if ( cmd & 1 ) { 
		tsen_OH();
	}
	else{
		tsen_OL();
	}
	// wait for bit time 
	_delay_us(T_BIT) ;
	
	//recovery period
	
	tsen_OH();
	_delay_us(T_BIT_INIT);
	
	// Next bit ;
	cmd>>= 1 ; 
}
//leave the bus after write
tsen_OH();
}


uint8_t ds18_rb ( void ) {
	
	uint8_t val = 0 ; 
	for ( uint8_t i = 0 ; i <= 7 ; i++ ) {
	
	// LOW PULSE FOR T_BIT_INIT	
	tsen_OL(); 
	_delay_us(T_BIT_INIT);
	// Release the bus 
	tsen_pin_in();
	// wait for valid time
	_delay_us( T_VALID ) ;
	//sample the input 
	val |= ( tsen_pin & ( 1 << tsen_pin_num ) ) ? (1<<7) : 0;
	//wait the rest of the duration
	_delay_us( T_BIT - 15 ) ;
	//recovery
	
		tsen_OH();
	_delay_us(T_BIT_INIT);
	
	// get next bit 
	val >>= 1 ; 
	
	
} 
//leave bus
tsen_OH();

return val ; 	
}




void ds18_read_spad (  sc_pad * mem_pad  ) { 
	
	// reset 
	ds18_reset();
	//read scratch pad command 
	ds18_wrb ( CMD_READ_SCRATCHPAD ) ;
	//START READING EACH BYTE
	for( uint8_t i = 0 ; i <= 8 ; i++ ) {
		
		*((uint8_t *)mem_pad+i) = ds18_rb();   // read in each byte ;
	}
	
}
	
	
	
