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


#define MOTOR_CMD_OPEN 1
#define MOTOR_CMD_CLOSE 2
#define LED_CMD_TOGGLE 1
#define LED_CMD_SEND 2 
#define FAN_CMD_INCREMENT 1
#define FAN_CMD_DECREMENT 2 
#define NO_CMD 0 

//*****************************************************************************************************************************
//DEFS
//*****************************************************************************************************************************
//*****************************************************************************************************************************
typedef enum {
	
	PIR_IDLE            = 0X00 , 
	PIR_MOTION_DETECTED = 0X01 ,
	
	
}pir_st ; 


typedef enum{
	
	LDR_UNDER_THRESHHOLD = 0X00 , 
	LDR_OVER_THRESHHOLD  = 0X01 ,
 
} ldr_st ;

typedef enum{
	
	MOTOR_IDLE    = 0X00 , 
	MOTOR_OPENING = 0X01 ,
	MOTOR_LOCKED  = 0X02 ,
	MOTOR_CLOSING = 0X03 ,
	
}motor_st ; 


typedef enum {
	FAN_OFF    = 0 , 
	FAN_SPEED1 = 60 ,
	FAN_SPEED2 = 120 , 
	FAN_SPEED3 = 200 , 
	
} fan_st ; 


typedef enum {
	
	TCONV_IDLE =  0X00 , 
	TCONV_BUSY =  0X01 ,

} tconv_st ; 

typedef enum{
	
	CTRL_MANUAL = 0X00 , 
	CTRL_AUTO   = 0X01 , 
	
}ctrl ; 

//*****************************************************************************************************************************
//GLOBS
//*****************************************************************************************************************************

volatile pir_st pir_state = PIR_IDLE ;
volatile ldr_st ldr_state = LDR_UNDER_THRESHHOLD ;
volatile motor_st motor_state = MOTOR_IDLE ;
volatile fan_st   fan_state   = FAN_OFF ; 
volatile tconv_st tconv_state = TCONV_IDLE ; 
volatile uint32_t count = 0 ;
volatile uint32_t door_delay = 0 ;
volatile uint32_t temp_delay = 0 ; 
// some variables to handle auto/manual 

volatile ctrl motor_am = CTRL_AUTO ; 
volatile ctrl fan_am   = CTRL_AUTO ; 
volatile ctrl led_am   = CTRL_AUTO ;  

volatile uint8_t led_cmd = 0 ;
volatile uint8_t motor_cmd = 0 ; 
volatile uint8_t fan_cmd   = 0 ; 
volatile uint8_t temp_start_send = 0 ;
volatile uint8_t data_array[8] = { 0 , 0 , 0 , '.' , 0 , 0 , 0 , 0  } ;
volatile uint8_t op = 0 ; 
uint8_t rand1,rand2 ;
uint16_t rand3 ; 
//*****************************************************************************************************************************
//small funcs 
//*****************************************************************************************************************************
void door_open ( void ) {
	set_bit( MOTOR_PIN1_NUM , MOTOR_PORT ) ;
	clear_bit( MOTOR_PIN2_NUM , MOTOR_PORT ) ;
}

void door_close ( void ) {
	set_bit( MOTOR_PIN2_NUM , MOTOR_PORT ) ;
	clear_bit( MOTOR_PIN1_NUM , MOTOR_PORT ) ;
}

void motor_off( void ) {
	clear_bit( MOTOR_PIN1_NUM , MOTOR_PORT ) ;
	clear_bit( MOTOR_PIN2_NUM , MOTOR_PORT ) ;	
}
//*****************************************************************************************************************************
//*****************************************************************************************************************************
//Analog Comparator interrupt vector. ( LDR ) 
//*****************************************************************************************************************************

ISR( ANA_COMP_vect ) { 

if ( aco_ret() )
{	
ldr_state = LDR_OVER_THRESHHOLD ; 
}
else
{
ldr_state = LDR_UNDER_THRESHHOLD ; 
}
		
}
//*****************************************************************************************************************************
//*****************************************************************************************************************************
// External INTERRUPT INT0 vector . ( PIR ) 
//*****************************************************************************************************************************
ISR( INT0_vect ) {
	
		pir_state =  PIR_MOTION_DETECTED ;
		 

}
//*****************************************************************************************************************************
//*****************************************************************************************************************************

ISR( TIMER1_COMPA_vect ){
	
	count++ ;
	TCNT1= 0 ;
	
	
}

//*****************************************************************************************************************************
//*****************************************************************************************************************************

ISR( USART_RX_vect ) {

switch ( UDR ) {
	
	
	case '2' :
	
	//close the door manually 
	motor_am = CTRL_MANUAL ; 
	// close it 
	motor_cmd = MOTOR_CMD_CLOSE ;
	
		if ( motor_state == MOTOR_CLOSING || motor_state == MOTOR_IDLE ){
		UDR = '0' ;
	}
	else{
		UDR = '1' ;
	}
	break ;
	
	case '3' :
	
	// open door manually 
	motor_am = CTRL_MANUAL ; 
	//open it 
	motor_cmd = MOTOR_CMD_OPEN ;
	if ( motor_state == MOTOR_OPENING || motor_state == MOTOR_LOCKED ){
		UDR = '0' ;
	}
	else{
		UDR = '1' ;
	}
	break;
	
	
	
	case '5' :
	
	//toggle leds manually 
	led_am = CTRL_MANUAL ;
	// toggle 
	led_cmd = LED_CMD_TOGGLE ; 
	
	break ; 
	
	case '6' :
	
	led_cmd = LED_CMD_SEND ; 
	break ; 
	
	case '+' :
	
	//Increment manually 
	fan_am = CTRL_MANUAL ;
	// increment 
	fan_cmd = FAN_CMD_INCREMENT ;
	break;
	
	case '-':
	
	//Decrement manually 
	fan_am = CTRL_MANUAL ;
	// Decrement 
	fan_cmd = FAN_CMD_DECREMENT ;
	break;
	
	case 'a' :
	
	// return auto and clear left over commands 
	fan_am = CTRL_AUTO ;
	led_am = CTRL_AUTO ;
	motor_am = CTRL_AUTO ; 
	fan_cmd = NO_CMD; 
	led_cmd = NO_CMD ;
	motor_cmd = NO_CMD ;
	break ;
	
	
	case '9' :
	
	temp_start_send = 1  ;
	break ;
}
	
	
	
}

	


//*****************************************************************************************************************************
//*****************************************************************************************************************************
/*
ISR( USART_TX_vect ) {

if ( temp_start_send ){

	if ( op < 9 ) {
	UDR = data_array[op++];
}
else{
	op = 0 ;
	temp_start_send = 0 ; 
}
}


}

*/

int main ( void ) {
	
//scratch pad placeholder
//*****************************************************************************************************************************
sc_pad scratchpad ;  
//*****************************************************************************************************************************
// init uart module at F_BAUD 
//*****************************************************************************************************************************	
//uart_init_rxie_txie();
uart_init_rxie();
//*****************************************************************************************************************************
//Init DS18B20 module 
//*****************************************************************************************************************************
ds18_init();
//*****************************************************************************************************************************
// Initialize analog comparator with TOGGLE INTERRUPT LEVEL 
//*****************************************************************************************************************************
ac_init( INT_OUTPUT_TOGGLE );
//*****************************************************************************************************************************
//*****************************************************************************************************************************
//make INT0 an input
pir_port&=~ ( 1 << pir_pin_num ) ;
pir_ddr&= ~ ( 1 << pir_pin_num ) ; 
//*****************************************************************************************************************************
//Enable external interrupt on pin PD2 , INT0
int0_set( INT_FALLING_EDGE ) ; 
//*****************************************************************************************************************************
//*****************************************************************************************************************************
//Initialize LED PINS
//*****************************************************************************************************************************
LDR_LED_PORT&= ~ ( 1 << LDR_LED_PIN_NUM ) ;
LDR_LED_DDR|= ( 1 << LDR_LED_PIN_NUM ) ;
//*****************************************************************************************************************************
//Initialize Motor pins . 
MOTOR_PORT&= ~ ( ( 1 << MOTOR_PIN1_NUM ) | ( 1 << MOTOR_PIN2_NUM ) ) ;
MOTOR_DDR |= (( 1 << MOTOR_PIN1_NUM ) | ( 1 << MOTOR_PIN2_NUM ) ) ;
//*****************************************************************************************************************************
//*****************************************************************************************************************************
//Initialize fan pin.
FAN_PORT&= ~ ( 1 << FAN_PIN_NUM ) ;
FAN_DDR|= ( 1 << FAN_PIN_NUM ) ;
//*****************************************************************************************************************************
//*****************************************************************************************************************************
//run fast pwm 
//*****************************************************************************************************************************
timer0_fastpwm_oca_init();
timer0_oca_update( fan_state ) ; 
//*****************************************************************************************************************************
//TIMER1 Init
timer1_init();
//*****************************************************************************************************************************
//*****************************************************************************************************************************
//Set global interrupt flag :D
//*****************************************************************************************************************************
sei();
//*****************************************************************************************************************************


while(1){


if ( (( pir_state == PIR_MOTION_DETECTED ) &&( motor_state == MOTOR_IDLE ) && ( motor_am == CTRL_AUTO ) ) || ( ( motor_state == MOTOR_IDLE ) && (motor_am == CTRL_MANUAL ) && (motor_cmd == MOTOR_CMD_OPEN ) ) ){
	door_open();                   // RUN MOTOR IN FORWARD DIRECTION 
	motor_state = MOTOR_OPENING;   // DOOR IS BEING OPENED 
	door_delay = count ;           // door_delay initial value 
	motor_cmd = NO_CMD ;  
}



if (  ( ( motor_state == MOTOR_LOCKED) && (pir_state == PIR_MOTION_DETECTED)  && ( motor_am == CTRL_AUTO ) ) || ( ( motor_state == MOTOR_LOCKED) && (motor_am == CTRL_MANUAL ) && (motor_cmd == MOTOR_CMD_CLOSE ) ) ){
	
	door_close();                    // RUN MOTOR IN FORWARD DIRECTION
	motor_state = MOTOR_CLOSING ;    // DOOR IS BEING CLOSED
	door_delay = count ;
	motor_cmd = NO_CMD ;  
}


if ( (motor_state == MOTOR_OPENING || motor_state == MOTOR_CLOSING ) && ( ( count - door_delay ) >= 10000 ) ){
	motor_state = (motor_state == MOTOR_OPENING) ? (MOTOR_LOCKED) : (MOTOR_IDLE );    // DOOR IS EITHER GOING TO END UP LOCKED OR OPENED(IDLE)
	motor_off();                   // STOP MOTORS 
	pir_state = PIR_IDLE ;         // PIR RETURNS TO IDLE 

}



//Auto mode on 
if ( led_am == CTRL_AUTO ){
	
	//LDR Over threshhold val 
if ( ldr_state == LDR_OVER_THRESHHOLD  ){
	
	// turn on led 
LDR_LED_PORT|= ( 1 << LDR_LED_PIN_NUM ) ;
	
	
}
// UNDER THRESHHOLD 
else { 
	
	LDR_LED_PORT&= ~ ( 1 << LDR_LED_PIN_NUM ) ;
}


}

if ( (led_am == CTRL_MANUAL) && (led_cmd != NO_CMD ) ){
	
	switch ( led_cmd ) {
		
		
		case LED_CMD_TOGGLE :
		// toggle 
		LDR_LED_PORT^= ( 1 << LDR_LED_PIN_NUM ) ;
		
		break;
		
		case LED_CMD_SEND :
		//SEND 
		UDR = ( LDR_LED_PORT & ( 1 << LDR_LED_PIN_NUM ) ) ? '1' : '0' ;
		
		break;
		
	}
	
	led_cmd = NO_CMD ;
	
}

// FAN AUTO CONTROL 
if ( fan_am == CTRL_AUTO ) {
	
	rand1 =  scratchpad.temp_h | ( scratchpad.temp_l >> 4 ) ;  
	
	if ( rand1 < 25 ){
		fan_state = FAN_OFF ; 
	}
		
	else if (  ( rand1 >= 25 ) && ( rand1 <= 28 ) ){
		
	fan_state = FAN_SPEED1 ; 
}
else if ( ( rand1 >= 28 ) && ( rand1 <= 32 ) ){
	fan_state = FAN_SPEED2 ;
}

else if ( ( rand1 >= 32 ) && ( rand1 <= 36 )){
	fan_state = FAN_SPEED3 ; 
}




}
	
	
if ( fan_am == CTRL_MANUAL && fan_cmd != NO_CMD  ) {
	
 switch ( fan_cmd ) {
	 
	 case FAN_CMD_INCREMENT:
	 
	 if ( fan_state == FAN_OFF ) {
		 fan_state = FAN_SPEED1 ; 
	 }
	 else if ( fan_state == FAN_SPEED1 ) {
		 fan_state = FAN_SPEED2 ; 
	 }	 
	 else if ( fan_state == FAN_SPEED2 ) {
		 fan_state = FAN_SPEED3 ; 
	 }	 
	 else if ( fan_state == FAN_SPEED3 ) {
		 fan_state = FAN_OFF ; 
	 }	 

	 
	 break;
	 
	 
	  case FAN_CMD_DECREMENT : 
	  

	if ( fan_state == FAN_SPEED1 ) {
		 fan_state = FAN_OFF ; 
	 }	 
	 else if ( fan_state == FAN_SPEED2 ) {
		 fan_state = FAN_SPEED1 ; 
	 }	 
	 else if ( fan_state == FAN_SPEED3 ) {
		 fan_state = FAN_SPEED2 ; 
	 }	 
	 
	 break;	  
	 	 
	 
	 
	 
 }	
	fan_cmd = NO_CMD ; // DONE 
	
	
}

if ( tconv_state == TCONV_IDLE ) {
	
	temp_delay = count ; // save count value ;
	ds18_tconv() ;       // REQUEST CONVERSION
	tconv_state = TCONV_BUSY ; // BUSY
}

if( tconv_state == TCONV_BUSY && ( ( count - temp_delay) >= 1000 ) ) {
	
	ds18_read_spad( &scratchpad ) ;   // READ scratchpad 
	tconv_state = TCONV_IDLE ;        // BACK TO IDLE 
	
	// update temperature
	rand2 = (scratchpad.temp_h)  | (scratchpad.temp_l>>4) ;
	rand3 = scratchpad.temp_l & 0B00001111 ; 
	
		
		data_array[0] = ( rand2 / 100 ) + '0' ; 
		rand2 = rand2 %100 ;
		data_array[1] = ( rand2 / 10 ) + '0' ;
		rand2 = rand2 % 10 ; 
		data_array[2] = rand2 + '0' ;
		
		rand3 = rand3 * 625 ; 
				
		data_array[4] = rand3 / 1000 + '0' ;
		rand3= rand3%1000 ;
		data_array[5] = rand3/ 100 + '0' ;
		rand3= rand3%100 ;
		data_array[6] = rand3/10 +'0';
		rand3= rand3%10 ; 
		data_array[7] = rand3 +'0';
		

	 

}
	timer0_oca_update( fan_state ) ; // update fan speed 
//motor_state ;
//fan_state ; 

if ( temp_start_send ) {
	
 uartb_transmit ( (0B00001111&scratchpad.temp_h)  | (scratchpad.temp_l>>4) ) ;
		//for ( uint8_t j = 0 ; j < 8 ;j++){
		//	uartb_transmit( data_array[j] ) ; 
	
	//}
	
	temp_start_send =0;

	
}
	
	
}	
}
