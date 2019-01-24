/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:   uart0.h
 *      Purpose: Microprocessors Laboratory
 *----------------------------------------------------------------------------
 *      
 */
  #include "MKL46Z4.h"	
  #include "slcd.h"	
	#include "leds.h"
 
void uart0Init(void);

void uart0transmit(uint8_t data);
uint8_t uart0receive(void);
void UART0_IRQHandler(void);
uint16_t uart0convert (uint8_t change_me);
uint8_t Ascii_to_int (char* ptr);
void uart0sendblock (int32_t data);

