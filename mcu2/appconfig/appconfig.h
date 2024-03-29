
/** @file appconfig.h
 * 
 * Author : Mohamed yousry mohamed rashad
 * 
 * This file contains :  general project configuration before build .
 * */
 
 #ifndef APP_CONFIG_TOKEN 
 #define APP_CONFIG_TOKEN 1 
 
  //CPU FREQ.
 #define F_CPU 8000000UL
 //APP BAUD_RATE
 #define F_BAUD 9600
 
 
 
 
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include <util/delay.h>
 #include <stdlib.h>
 #include <stdint.h>
 #include <string.h>
 #include <math.h>
 
 



// undefine the following to cancel baudrate defines and calculate ur own 
//#define OVERRIDE_BAUD_CALC 1 

 
//LDR sensor register defines   
// Can be changed to any port with analog comparator on your micro 
// Do not change this if you're building for the attiny2313

#define ldr_pin  PINB
#define ldr_port PORTB
#define ldr_ddr  DDRB 
 
 
// LDR sensor pins can be ( PINB0 , PINB1 ) only on attiny2313  ( analog comparator pins )
// Can be changed to any pin with an analog comparator input  

#define ldr_pin_num PINB0
	
//Temperature sensor register defines
// can be changed to any port with a free digital pin on your micro 

#define tsen_pin   PIND
#define tsen_port  PORTD
#define tsen_ddr 	DDRD

//Temperature sensor pin defines
// can be changed to any free digital pin on your micro 
#define tsen_pin_num PD4
 

// PIR Motion sensor register defines , can be changed to any port with external interrupts

#define pir_pin  PIND
#define pir_port PORTD
#define pir_ddr  DDRB

//PIR Motion sensor pin define , can be changed to any external interrupt pin number on your micro 

#define pir_pin_num PD2


// LDR_LED PINS

#define LDR_LED_PIN     PIND
#define LDR_LED_PORT    PORTD
#define LDR_LED_DDR     DDRD
#define LDR_LED_PIN_NUM PD5

//MOTOR DRIVER PINS

#define FAN_PIN        PINB
#define FAN_PORT       PORTB
#define FAN_DDR        DDRB
#define FAN_PIN_NUM    PB2


#define MOTOR_PIN        PINB
#define MOTOR_PORT       PORTB
#define MOTOR_DDR        DDRB
#define MOTOR_PIN1_NUM   PB4
#define MOTOR_PIN2_NUM   PB3 



//Useful tools

// useful defines 
 
#define set_bit( PIN_NUM , PORT ) PORT|=( 1 << PIN_NUM ) 
#define clear_bit( PIN_NUM , PORT ) PORT &= ~( 1 << PIN_NUM )


typedef enum {
	INT_LOW_LEVEL    = 0B00 , 
	INT_LOGIC_CHANGE = 0B01 ,
	INT_FALLING_EDGE = 0B10 ,
	INT_RISING_EDGE  = 0B11 ,
	
} int_level ; 


typedef enum {
	
	INT_OUTPUT_TOGGLE       = 0B00 ,
	INT_OUTPUT_FALLING_EDGE = 0B10 ,
	INT_OUTPUT_RISING_EDGE = 0B11 ,
	
} acint_level ; 


__attribute__((always_inline)) static inline void int0_set ( int_level my_int_level ) {
	
	MCUCR |= ( my_int_level << ISC00 ) ; 
	GIMSK |= ( 1 << INT0 ) ; 

}

__attribute__((always_inline)) static inline void int0_clear ( int_level my_int_level ) {
	
	MCUCR &= ~( my_int_level << ISC00 ) ; 
	GIMSK &= ~( 1 << INT0 ) ; 

}


__attribute__((always_inline)) static inline void int1_set ( int_level my_int_level ) {
	
	MCUCR |= ( my_int_level << ISC10 ) ; 
	GIMSK |= ( 1 << INT1 ) ; 

}


__attribute__((always_inline)) static inline void int1_clear ( int_level my_int_level ) {
	
	MCUCR &= ~( my_int_level << ISC10 ) ; 
	GIMSK &= ~( 1 << INT1 ) ; 

}



__attribute__((always_inline)) static inline void ac_init( acint_level acint ) {
	
	// Disable digital input buffer 
	DIDR = (0B11 << AIN0D ) ;
	// Enable Analog comparator , with int_level
	ACSR = ( 1 << ACIE ) | ( acint << ACIS0 )  ; 
	
}


__attribute__((always_inline)) static inline uint8_t aco_ret ( void ) {
	
	return ( ( ACSR & ( 1 << ACO ) ) ? 1 : 0 ) ; 
}

// SMALL PWM stuff

__attribute__((always_inline)) static inline void timer0_fastpwm_oca_init ( void ){ 
	
	// FAST PWM , OCA0
	TCCR0A = ( 0B11 << WGM00 ) | ( 0B10 << COM0A0 ) ;
	// 1024 PRESCALER 
	TCCR0B = ( 0B101 << CS00 ) ;
	//init as 0 
	OCR0A = 0 ;  
}


__attribute__((always_inline)) static inline void timer0_oca_update ( uint8_t val ) {
	
	OCR0A = val ; 
	
}


__attribute__((always_inline)) static inline void timer1_init( void ) {
	
	TCCR1A = 0 ; // NORMAL OPERATION 
	OCR1A  = 8 ; // THIS GIVES INTERRUPT EVERY 1 MS 
	TCNT1 = 0 ; 
	TIMSK  = ( 1 << OCIE1A ) ; // OCIE1A INTERRUPT 
	TCCR1B = ( 1 << WGM12 ) | ( 0B101 << CS10 ) ; // CTC , 1024 PRESCALER 
	
	
}







#endif
