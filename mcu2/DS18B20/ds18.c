/** @file ds18.c
 *
 * Author : Mohamed yousry mohamed rashad . 
 * Description : This file contains implemenations of functions that read temperature data and/or set alarm mode for the temp module .
 * 
 * */
 
 
 
 
 #include "ds18.h"
 
 
 void ds18_init ( void ) {
	 tsen_port &= ~ ( 1 << tsen_pin_num ) ; // THIS BIT SHOULD ALWAYS BE CLEAR SINCE THE BUS IS ALREADY PULLED UP 
	 tsen_OH();    							// RELEASE THE BUS 
	 _delay_us(DS18_DELAY_480 ) ;  			// wait 480 us	  
 }
 
 
static void ds18_wr1 ( void ) {
	 
	 // DRIVE LOW  AND DELAY 
	 tsen_OL(); 
	 _delay_us( DS18_DELAY_6 ) ; 
	 
	 //RELEASE AND DELAY
	 tsen_OH();
	 _delay_us( DS18_DELAY_64);
	 
 }
 
 
 static uint8_t ds18_rbit ( void ){
	 
	uint8_t retval = 0  ; 
	     
    // Drive bus low and delay.
    tsen_OL();
    _delay_us(DS18_DELAY_6);
    
    // Release bus and delay.
    tsen_OH();
    _delay_us(DS18_DELAY_9);
	 
	// SAMPLE BUS and delay.
	retval = tsen_pin & ( 1 << tsen_pin_num ) ; 
	_delay_us(DS18_DELAY_55);
	
	return ( retval ? 1 : 0 ) ;
	 
	 
 }
 
 
 static void ds18_wr0 ( void ){
	 
	 // DRIVE LOW  AND DELAY 
	 tsen_OL(); 
	 _delay_us( DS18_DELAY_60 ) ; 
	 
	 //RELEASE AND DELAY
	 tsen_OH();
	 _delay_us( DS18_DELAY_10);
	 
 }
 
 
 static void ds18_reset( void ) {
	 
	 //pull tsin low  _________
	 tsen_OL();
	 // wait for minimum Treset
	 _delay_us( DS18_DELAY_480 ) ; 
	 // go back to input 
	 tsen_OH();
	 _delay_us(DS18_DELAY_70);
	 _delay_us(DS18_DELAY_410);
}



static void ds18_wrb ( uint8_t cmd ) {
	
	for ( uint8_t i=0 ; i <=7 ; i++ ) {
		
	if ( cmd & 1 ) { 
		ds18_wr1();  // write one 
	}
	else{
		ds18_wr0(); // write 0 
	}
	// Next bit ;
	cmd>>= 1 ; 
}

}

static uint8_t ds18_rb ( void ) {
	
	uint8_t val = 0 ; 
	for ( uint8_t i = 0 ; i <= 7 ; i++ ) {
	// get next bit 
	val >>= 1 ; 
	// read bit
	val |= ( ds18_rbit() << 7 ) ; 

} 
return val ; 	
}




void ds18_read_spad (  sc_pad * mem_pad  ) { 
	
	// reset 
	ds18_reset();
	//skiprom
	ds18_wrb( CMD_SKIP_ROM );
	//read scratch pad command 
	ds18_wrb ( CMD_READ_SCRATCHPAD ) ;
	//START READING EACH BYTE
	for( uint8_t i = 0 ; i <= 8 ; i++ ) {
		
		*((uint8_t *)mem_pad+i) = ds18_rb();   // read in each byte ;
	}
	
}

void ds18_tconv ( void ){
	// reset 
	ds18_reset();
	//skiprom
	ds18_wrb( CMD_SKIP_ROM );
	//convert
	ds18_wrb ( CMD_CONVERT_T ) ;		
}



	
	
	
