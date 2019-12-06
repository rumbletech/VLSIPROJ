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

#define DS18_DELAY_480				(480)
#define DS18_DELAY_6 				(6)
#define DS18_DELAY_9 				(9)
#define DS18_DELAY_64 				(64)
#define DS18_DELAY_60 				(60)
#define DS18_DELAY_70 				(70)
#define DS18_DELAY_10 				(10)
#define DS18_DELAY_55 				(55)
#define DS18_DELAY_410				(410) 


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








__attribute__((always_inline)) static inline void tsen_pin_in ( void ) {
	
	tsen_port&=~( 1 << tsen_pin_num  ) ; // Disable internal PULLUP 
	tsen_ddr&= ~( 1 << tsen_pin_num ) ; //Input 
}
	

__attribute__((always_inline)) static inline void tsen_OL ( void ) {
	
	tsen_ddr |= ( 1 << tsen_pin_num  ) ;     // PULL THE BUS LOW BY SWITCHING TO OUTPUT 

}


__attribute__((always_inline)) static inline void tsen_OH ( void ) {
					tsen_ddr &=~ ( 1 << tsen_pin_num ) ;    // RELEASE THE BUS BY SWITCHING TO INPUT 
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


/** Description : reads the scratch pad of the DS18B20 Temperature sensor chip.
 * @param mem_pad : pointer to a scratch pad structure that will hold the returned registers.
 * @retval void.
 * */
void ds18_read_spad (  sc_pad * mem_pad  );

/** Description : initializes the tsen pin , it takes up to 480 us to initialize.
 * */
void ds18_init ( void ) ;
/** Description : sends a conversion command to the ds18 , conversion time can take up to 750 ms YIKES.
 * */
void ds18_tconv ( void );

#endif
