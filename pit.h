/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    pit.h
 *      Purpose: Design Laboratory Sensors project
 *----------------------------------------------------------------------------
 *      
 *---------------------------------------------------------------------------*/
 #include "MKL46Z4.h"
 #include "leds.h"
 #include "slcd.h"
 #include "UART0.h"
 #include "sensors.h"
 
void pitInitialize(void);
void PIT_IRQHandler(void);
