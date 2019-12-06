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
	FAN_SPEED4 = 250 ,
	
} fan_st ; 


typedef enum {
	
	TCONV_IDLE =  0X00 , 
	TCONV_BUSY =  0X01 ,

} tconv_st ; 

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
volatile uint32_t debounce_delay = 0 ;
volatile uint32_t temp_delay = 0 ; 

volatile uint8_t data_array[5] = { 0 , 0 , 0 , 0 , '#' } ;
volatile uint8_t i = 0 ; 
//*****************************************************************************************************************************
//small funcs 
//*****************************************************************************************************************************
static inline void door_open ( void ) {
	set_bit( MOTOR_PIN1_NUM , MOTOR_PORT ) ;
	clear_bit( MOTOR_PIN2_NUM , MOTOR_PORT ) ;
}

static inline void door_close ( void ) {
	set_bit( MOTOR_PIN2_NUM , MOTOR_PORT ) ;
	clear_bit( MOTOR_PIN1_NUM , MOTOR_PORT ) ;
}

static inline void motor_off( void ) {
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
LDR_LED_PORT|= ( 1 << LDR_LED_PIN_NUM ) ;
ldr_state = LDR_OVER_THRESHHOLD ; 
}
else
{
LDR_LED_PORT&= ~( 1 << LDR_LED_PIN_NUM ) ;
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

if ( UDR == '*' ) {
	UDR = '#' ; 
}

	
}

//*****************************************************************************************************************************
//*****************************************************************************************************************************
ISR( USART_TX_vect ) {


	if ( i < 5) {
	UDR = data_array[i++];
}
else{
	i = 0 ;
}
}



int main ( void ) {
	
//scratch pad placeholder
//*****************************************************************************************************************************
sc_pad scratchpad ;  
//*****************************************************************************************************************************
// init uart module at F_BAUD 
//*****************************************************************************************************************************	
uart_init_rxie_txie();
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

if ( ( pir_state == PIR_MOTION_DETECTED ) &&( motor_state == MOTOR_IDLE ) ){
	door_open();                   // RUN MOTOR IN FORWARD DIRECTION 
	motor_state = MOTOR_OPENING;   // DOOR IS BEING OPENED 
	door_delay = count ;           // door_delay initial value 
}



if (  motor_state == MOTOR_LOCKED && pir_state == PIR_MOTION_DETECTED  ){
	
	door_close();                    // RUN MOTOR IN FORWARD DIRECTION
	motor_state = MOTOR_CLOSING ;    // DOOR IS BEING CLOSED
	door_delay = count ;
}


if ( (motor_state == MOTOR_OPENING || motor_state == MOTOR_CLOSING ) && ( ( count - door_delay ) >= 10000 ) ){
	motor_state = (motor_state == MOTOR_OPENING) ? (MOTOR_LOCKED) : (MOTOR_IDLE );    // DOOR IS EITHER GOING TO END UP LOCKED OR OPENED(IDLE)
	motor_off();                   // STOP MOTORS 
	pir_state = PIR_IDLE ;         // PIR RETURNS TO IDLE 

}

if ( tconv_state == TCONV_IDLE ) {
	
	temp_delay = count ; // save count value ;
	ds18_tconv() ;       // REQUEST CONVERSION
	tconv_state = TCONV_BUSY ; // BUSY
}

if( tconv_state == TCONV_BUSY && ( ( count - temp_delay) >= 1000 ) ) {
	
	ds18_read_spad( &scratchpad ) ;   // READ scratchpad 
	tconv_state = TCONV_IDLE ;        // BACK TO IDLE 

}
// update data 
data_array[0] = scratchpad.temp_h ;
data_array[1] = scratchpad.temp_l ;
data_array[2] = motor_state ;
data_array[3] = fan_state ;





	
}
	
	
	
	
}
