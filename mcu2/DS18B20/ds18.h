/** @file ds18.h
 * 
 * Author : Mohamed yousry mohamed rashad 
 * 
 * Description : This file contains commands and byte locations for the ds18b20 temperature sensor.
 * 
 * */
 
 
#ifndef DS18_TOKEN 
#define DS18_TOKEN 1

// main header 
#include "../appconfig/appconfig.h"



// Conversion times in ms  

#define T_ALLOW 5
#define T_BIT_INIT 6   // LOW TIME BEFORE EACH BIT 
#define T_BIT 65  
#define T_VALID 20

#define TCONV_12BIT 750
#define TCONV_11BIT 375
#define TCONV_10BIT 188
#define TCONV_9BIT  94

#define T_RESET_PULSE 480 




// Commands 


#define CMD_SEARCH_ROM       0XF0
#define CMD_READ_ROM         0X33
#define CMD_MATCH_ROM        0X55
#define CMD_SKIP_ROM         0XCC
#define CMD_ALARM_SEARCH     0XEC
#define CMD_CONVERT_T        0X44
#define CMD_WRITE_SCRATCHPAD 0X4E
#define CMD_READ_SCRATCHPAD  0XBE
#define CMD_COPY_SCRATCHPAD  0X48
#define CMD_RECALL_DATA      0XB8
#define CMD_READ_PS          0XB4 







__attribute__((always_inline)) static inline void tsen_pin_out ( void ) {
	tsen_ddr |= ( 1 << tsen_pin_num  ) ; //OUTPUT 
}

__attribute__((always_inline)) static inline void tsen_pin_in ( void ) {
	
	tsen_port&=~( 1 << tsen_pin_num  ) ; // Disable internal PULLUP 
	tsen_ddr&= ~( 1 << tsen_pin_num ) ; //Input 
}
	

__attribute__((always_inline)) static inline void tsen_OL ( void ) {
		
	clear_bit( tsen_pin_num , tsen_port ) ; 
		tsen_pin_out() ;

}


__attribute__((always_inline)) static inline void tsen_OH ( void ) {
	
					tsen_pin_in();
}


typedef struct {
	
	uint8_t temp_l ;
	uint8_t temp_h ;
	uint8_t alarm_h ;
	uint8_t alarm_l ;
	uint8_t config ;
	uint8_t reserved_1;
	uint8_t reserved_2;
	uint8_t reserved_3;
	uint8_t crc ; 
} sc_pad ; 



void ds18_read_spad (  sc_pad * mem_pad  );

#endif
