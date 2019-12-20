/** @file uart.h
 * 
 * Author : Mohamed yousry mohamed rashad .
 * 
 * Description : header file for the uart module .
 * 
 * Note : this module uses baud rate defines for the old avrs .
 * 
 * */
 
 
 
 
 #ifndef UART_TOKEN 
 #define UART_TOKEN 1 
 
 // main config files 
 
 #include "../../appconfig/appconfig.h"
 
 
 
 #ifndef OVERRIDE_BAUD_CALC
  
 #if ( F_CPU == 1000000UL ) 
 
#define BAUD_2400_N2X 25 
#define BAUD_4800_N2X 12 

#define BAUD_2400_U2X 51 | ( 1 << 11 )
#define BAUD_4800_U2X 25 | ( 1 << 11 )
#define BAUD_9600_U2X 12 | ( 1 << 11 )


#elif ( F_CPU == 1843200UL ) 

#define BAUD_2400_N2X   47
#define BAUD_4800_N2X   23
#define BAUD_9600_N2X   11
#define BAUD_14400_N2X  7
#define BAUD_19200_N2X  5
#define BAUD_28800_N2X  3
#define BAUD_38400_N2X  2
#define BAUD_57600_N2X  1
#define BAUD_115200_N2X 0

#define BAUD_2400_U2X    95
#define BAUD_4800_U2X    47
#define BAUD_9600_U2X    23
#define BAUD_14400_U2X   15
#define BAUD_19200_U2X   11
#define BAUD_28800_U2X   7
#define BAUD_38400_U2X   5
#define BAUD_57600_U2X   3
#define BAUD_76800_U2X   2
#define BAUD_115200_U2X  1
#define BAUD_230400_U2X  0


#elif ( F_CPU == 2000000UL )


#define BAUD_2400_N2X   51
#define BAUD_4800_N2X   25
#define BAUD_9600_N2X   12


#define BAUD_2400_U2X    103
#define BAUD_4800_U2X    51
#define BAUD_9600_U2X    25
#define BAUD_19200_U2X   12
#define BAUD_250000_U2X  0


#elif ( F_CPU == 3686400UL )

#define BAUD_2400_N2X   95
#define BAUD_4800_N2X   47
#define BAUD_9600_N2X   23
#define BAUD_14400_N2X  15
#define BAUD_19200_N2X  11
#define BAUD_28800_N2X  7
#define BAUD_38400_N2X  5
#define BAUD_57600_N2X  3
#define BAUD_76800_N2X  2
#define BAUD_115200_N2X 1

#define BAUD_2400_U2X    191
#define BAUD_4800_U2X    95
#define BAUD_9600_U2X    47
#define BAUD_14400_U2X   31
#define BAUD_19200_U2X   23
#define BAUD_28800_U2X   15
#define BAUD_38400_U2X   11
#define BAUD_57600_U2X   7
#define BAUD_76800_U2X   5
#define BAUD_115200_U2X  3
#define BAUD_230400_U2X  1


#elif ( F_CPU == 4000000UL )

#define BAUD_2400_N2X   103
#define BAUD_4800_N2X   51
#define BAUD_9600_N2X   25
#define BAUD_19200_N2X  12
#define BAUD_250000_N2X 0

#define BAUD_2400_U2X    207
#define BAUD_4800_U2X    103
#define BAUD_9600_U2X    51
#define BAUD_19200_U2X   25
#define BAUD_38400_U2X   12
#define BAUD_250000_U2X  1
#define BAUD_500000_U2X  0


#elif ( F_CPU == 7372800UL )

#define BAUD_2400_N2X   191
#define BAUD_4800_N2X   95
#define BAUD_9600_N2X   47
#define BAUD_14400_N2X  31
#define BAUD_19200_N2X  23
#define BAUD_28800_N2X  15
#define BAUD_38400_N2X  11
#define BAUD_57600_N2X  7
#define BAUD_76800_N2X  5
#define BAUD_115200_N2X 3
#define BAUD_230400_N2X 1

#define BAUD_2400_U2X    383
#define BAUD_4800_U2X    191
#define BAUD_9600_U2X    95
#define BAUD_14400_U2X   63
#define BAUD_19200_U2X   47
#define BAUD_28800_U2X   31
#define BAUD_38400_U2X   23
#define BAUD_57600_U2X   15
#define BAUD_76800_U2X   11
#define BAUD_115200_U2X  7
#define BAUD_230400_U2X  3


#elif ( F_CPU == 8000000UL )

#define BAUD_2400_N2X   207
#define BAUD_4800_N2X   103
#define BAUD_9600_N2X   51
#define BAUD_19200_N2X  25
#define BAUD_38400_N2X  12
#define BAUD_250000_N2X 1
#define BAUD_500000_N2X 0

#define BAUD_2400_U2X    416
#define BAUD_4800_U2X    207
#define BAUD_9600_U2X    103
#define BAUD_19200_U2X   51
#define BAUD_38400_U2X   25
#define BAUD_76800_U2X   12
#define BAUD_250000_U2X  3
#define BAUD_500000_U2X  1
#define BAUD_1000000_U2X 0


#elif ( F_CPU == 16000000UL )

#define BAUD_2400_N2X    416
#define BAUD_4800_N2X    207
#define BAUD_9600_N2X    103
#define BAUD_19200_N2X   51
#define BAUD_38400_N2X   25
#define BAUD_76800_N2X   12
#define BAUD_250000_N2X  3
#define BAUD_500000_N2X  1
#define BAUD_1000000_N2X 0

#define BAUD_2400_U2X    832
#define BAUD_4800_U2X    416
#define BAUD_9600_U2X    207
#define BAUD_19200_U2X   103
#define BAUD_38400_U2X   51
#define BAUD_76800_U2X   25
#define BAUD_250000_U2X  7
#define BAUD_500000_U2X  3
#define BAUD_1000000_U2X 1
#define BAUD_2000000_U2X 0



#elif ( F_CPU == 11059200UL )

#define BAUD_2400_N2X   287
#define BAUD_4800_N2X   143
#define BAUD_9600_N2X   71
#define BAUD_14400_N2X  47
#define BAUD_19200_N2X  35
#define BAUD_28800_N2X  23
#define BAUD_38400_N2X  17
#define BAUD_57600_N2X  11
#define BAUD_76800_N2X  8
#define BAUD_115200_N2X 5
#define BAUD_230400_N2X 2

#define BAUD_2400_U2X    575
#define BAUD_4800_U2X    287
#define BAUD_9600_U2X    143
#define BAUD_14400_U2X   95
#define BAUD_19200_U2X   71
#define BAUD_28800_U2X   47
#define BAUD_38400_U2X   35
#define BAUD_57600_U2X   23
#define BAUD_76800_U2X   17
#define BAUD_115200_U2X  11
#define BAUD_230400_U2X  5


#elif ( F_CPU == 14745600UL )

#define BAUD_2400_N2X   383
#define BAUD_4800_N2X   191
#define BAUD_9600_N2X   95
#define BAUD_14400_N2X  63
#define BAUD_19200_N2X  47
#define BAUD_28800_N2X  31
#define BAUD_38400_N2X  23
#define BAUD_57600_N2X  15
#define BAUD_76800_N2X  11
#define BAUD_115200_N2X 7
#define BAUD_230400_N2X 3

#define BAUD_2400_U2X    767
#define BAUD_4800_U2X    383
#define BAUD_9600_U2X    191
#define BAUD_14400_U2X   127
#define BAUD_19200_U2X   95
#define BAUD_28800_U2X   63
#define BAUD_38400_U2X   47
#define BAUD_57600_U2X   31
#define BAUD_76800_U2X   23
#define BAUD_115200_U2X  15
#define BAUD_230400_U2X  7

#else 
#warning " No Predefined baud rate exists for the chosen F_CPU and chosen F_BAUD "

#endif

#if ( F_BAUD == 2400 ) 

#if ( BAUD_2400_N2X )
#define CALC_BAUD BAUD_2400_N2X
#define U2X 0 
#elif ( BAUD_2400_U2X )
#define U2X 1
#define CALC_BAUD BAUD_2400_U2X 
#else 
#warning " No Predefined baud rate exists for the chosen F_CPU and chosen F_BAUD "
#define CALC_BAUD -1
#endif  


#elif ( F_BAUD == 4800 ) 


#if ( BAUD_4800_N2X )
#define CALC_BAUD BAUD_4800_N2X
#define U2X_VAL 0
#elif ( BAUD_4800_U2X )
#define U2X_VAL 1
#define CALC_BAUD BAUD_4800_U2X 
#else 
#warning " No Predefined baud rate exists for the chosen F_CPU and chosen F_BAUD "
#define CALC_BAUD -1
#endif  




#elif ( F_BAUD == 9600 )

#if ( BAUD_9600_N2X )
#define CALC_BAUD BAUD_9600_N2X
#define U2X_VAL 0
#elif ( BAUD_9600_U2X )
#define CALC_BAUD BAUD_9600_U2X
#define U2X_VAL 1 
#else 
#warning " No Predefined baud rate exists for the chosen F_CPU and chosen F_BAUD "
#define CALC_BAUD -1
#endif  


#elif ( F_BAUD == 14400 )


#if ( BAUD_14400_N2X )
#define CALC_BAUD BAUD_14400_N2X
#define U2X_VAL 0
#elif ( BAUD_14400_U2X )
#define CALC_BAUD BAUD_14400_U2X 
#define U2X_VAL 1
#else 
#warning " No Predefined baud rate exists for the chosen F_CPU and chosen F_BAUD "
#define CALC_BAUD -1
#endif  


#elif ( F_BAUD == 19200 )

#if ( BAUD_19200_N2X )
#define CALC_BAUD BAUD_19200_N2X
#define U2X_VAL 0
#elif ( BAUD_19200_U2X )
#define CALC_BAUD BAUD_19200_U2X 
#define U2X_VAL 1
#else 
#warning " No Predefined baud rate exists for the chosen F_CPU and chosen F_BAUD "
#define CALC_BAUD -1
#endif  

#elif ( F_BAUD == 28800 )

#if ( BAUD_28800_N2X )
#define CALC_BAUD BAUD_28800_N2X
#define U2X_VAL 0
#elif ( BAUD_28800_U2X )
#define CALC_BAUD BAUD_28800_U2X 
#define U2X_VAL 1
#else 
#warning " No Predefined baud rate exists for the chosen F_CPU and chosen F_BAUD "
#define CALC_BAUD -1
#endif  

#elif ( F_BAUD == 38400 )

#if ( BAUD_38400_N2X )
#define CALC_BAUD BAUD_38400_N2X
#define U2X_VAL 0
#elif ( BAUD_38400_U2X )
#define CALC_BAUD BAUD_38400_U2X 
#define U2X_VAL 1
#else 
#warning " No Predefined baud rate exists for the chosen F_CPU and chosen F_BAUD "
#define CALC_BAUD -1
#endif  

#elif ( F_BAUD == 57600 )

#if ( BAUD_57600_N2X )
#define CALC_BAUD BAUD_57600_N2X
#define U2X_VAL 0
#elif ( BAUD_57600_U2X )
#define CALC_BAUD BAUD_57600_U2X 
#define U2X_VAL 1
#else 
#warning " No Predefined baud rate exists for the chosen F_CPU and chosen F_BAUD "
#define CALC_BAUD -1
#endif  

#elif ( F_BAUD == 76800 )

#if ( BAUD_76800_N2X )
#define CALC_BAUD BAUD_76800_N2X
#define U2X_VAL 0
#elif ( BAUD_76800_U2X )
#define CALC_BAUD BAUD_76800_U2X 
#define U2X_VAL 1
#else 
#warning " No Predefined baud rate exists for the chosen F_CPU and chosen F_BAUD "
#define CALC_BAUD -1
#endif  

#elif ( F_BAUD == 115200 )

#if ( BAUD_115200_N2X )
#define CALC_BAUD BAUD_115200_N2X
#define U2X_VAL 0
#elif ( BAUD_115200_U2X )
#define CALC_BAUD BAUD_115200_U2X 
#define U2X_VAL 1
#else 
#warning " No Predefined baud rate exists for the chosen F_CPU and chosen F_BAUD "
#define CALC_BAUD -1
#endif  

#elif ( F_BAUD == 230400 )

#if ( BAUD_230400_N2X )
#define CALC_BAUD BAUD_230400_N2X
#define U2X_VAL 0
#elif ( BAUD_230400_U2X )
#define CALC_BAUD BAUD_230400_U2X 
#define U2X_VAL 1
#else 
#warning " No Predefined baud rate exists for the chosen F_CPU and chosen F_BAUD "
#define CALC_BAUD -1
#endif  

#elif ( F_BAUD == 250000 )

#if ( BAUD_250000_N2X )
#define CALC_BAUD BAUD_250000_N2X
#define U2X_VAL 0
#elif ( BAUD_250000_U2X )
#define CALC_BAUD BAUD_250000_U2X 
#define U2X_VAL 1
#else 
#warning " No Predefined baud rate exists for the chosen F_CPU and chosen F_BAUD "
#define CALC_BAUD -1
#endif  

#elif ( F_BAUD == 500000 )

#if ( BAUD_500000_N2X )
#define CALC_BAUD BAUD_500000_N2X
#define U2X_VAL 0
#elif ( BAUD_500000_U2X )
#define CALC_BAUD BAUD_500000_U2X 
#define U2X_VAL 1
#else 
#warning " No Predefined baud rate exists for the chosen F_CPU and chosen F_BAUD "
#define CALC_BAUD -1
#endif  

#elif ( F_BAUD == 1000000 )

#if ( BAUD_1000000_N2X )
#define CALC_BAUD BAUD_1000000_N2X
#define U2X_VAL 0
#elif ( BAUD_1000000_U2X )
#define CALC_BAUD BAUD_1000000_U2X 
#define U2X_VAL 1
#else 
#warning " No Predefined baud rate exists for the chosen F_CPU and chosen F_BAUD "
#define CALC_BAUD -1
#endif  

#elif ( F_BAUD == 2000000 )

#if ( BAUD_2000000_N2X )
#define CALC_BAUD BAUD_2000000_N2X
#define U2X_VAL 0
#elif ( BAUD_2000000_U2X )
#define CALC_BAUD BAUD_2000000_U2X 
#define U2X_VAL 1
#else 
#warning " No Predefined baud rate exists for the chosen F_CPU and chosen F_BAUD "
#define CALC_BAUD -1
#endif  

#else 
#warning " No Predefined baud rate exists for the chosen F_CPU and chosen F_BAUD "
#define CALC_BAUD -1


#endif


/** Description : This function initializes the UART module in 8 bit data , 1 stop bit , no parity , both rx and tx are enabled.
 * */
 /*
__attribute__((always_inline)) static inline void uart_init( void ) {
	
	UBRRL = (uint8_t ) CALC_BAUD;
	UBRRH = CALC_BAUD >> 8 ; 
	
	UCSRA = ( U2X_VAL << U2X ) ;
    UCSRB = ( 1 << RXEN ) | ( 1 << TXEN )  ;
    UCSRC = ( 0B11 << UCSZ0 ) ; 
    
	
} 
* */

/** Description : This function initializes the UART module in 8 bit data , 1 stop bit , no parity , both rx and tx enabled, RX interrupt enabled.
 * */
 
__attribute__((always_inline)) static inline void uart_init_rxie( void ) {
	
	UBRRL = (uint8_t ) CALC_BAUD;
	UBRRH = CALC_BAUD >> 8 ; 
	
	UCSRA = ( U2X_VAL << U2X ) ;
    UCSRB = ( 1 << RXEN ) | ( 1 << TXEN ) | ( 1 << RXCIE ) ;
    UCSRC = ( 0B11 << UCSZ0 ) ; 
    
	
} 

__attribute__((always_inline)) static inline void uart_init_rxie_txie( void ) {
	
	UBRRL = (uint8_t ) CALC_BAUD;
	UBRRH = CALC_BAUD >> 8 ; 
	
	UCSRA = ( U2X_VAL << U2X ) ;
    UCSRB = ( 1 << RXEN ) | ( 1 << TXEN ) | ( 1 << RXCIE )|( 1<< TXCIE) ;
    UCSRC = ( 0B11 << UCSZ0 ) ; 
    
	
} 


  
#endif 

#ifdef OVERRIDE_BAUD_CALC
/*
__attribute__((always_inline)) static inline void uart_init( uint16_t baud_val ) {
	
	UBRRL = (uint8_t ) baud_val ;
	UBRRH = baud_val >> 8 ; 
	
	UCSRA = ( U2X_VAL << U2X ) ;
    UCSRB = ( 1 << RXEN ) | ( 1 << TXEN )  ;
    UCSRC = ( 0B11 << UCSZ0 ) ; 
    
	
} 
* */

#endif 

// Protos 

/** Description : this function sends a single byte using the usart module .
 * @param my_uint8 : the byte to be sent.
 * @retval void : returns nothing .
 * NOTE : This function is blocking.
 * */
 
// void uart_sendb( uint8_t my_uint8 ) ; 
 
 /** Description : this function receives a single byte using the usart module .
 * @retval : returns the received byte .
 * NOTE : This function is blocking.
 * */
 //uint8_t uart_recb( void );
 
 
  /** Description : this function transmits an array of bytes of length 'len' with starting frame character 'startc' and ends with 'endc'.
 * @param ptr : pointer to the array of bytes .
 * @param len : length of the array .
 * @param startc : starting character.
 * @param endc   : end character .
 * @retval void : returns nothing .
 * NOTE : This function is blocking.
 * */
  void uart_senda( uint8_t* ptr , uint8_t len , uint8_t startc , uint8_t endc ) ;


//void uart_print( uint8_t* str );


//void uart_print_hex ( uint8_t hex_val );


 void uartb_transmit ( uint8_t byte );

#endif 
