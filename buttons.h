/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    buttons.h
 *      Purpose: Design Laboratory Sensors project
 *----------------------------------------------------------------------------
 *      
 */
 
 
#ifndef buttons_h
#define buttons_h

#include "MKL46Z4.h"                    // Device header
#include "leds.h"
#include "sensors.h"

void buttonsInitialize(void);
void button1Service(void);							//buttons' interrupt service procedure
void button3Service(void);
int32_t button1Read(void);
int32_t button3Read(void);
uint8_t current_function (void);

#endif

