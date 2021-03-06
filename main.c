/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    main.c
 *      Purpose: Design Laboratory Sensors project
 *----------------------------------------------------------------------------
 *      
 *---------------------------------------------------------------------------*/

#include "MKL46Z4.h"
#include "slcd.h"
#include "leds.h"
#include "i2c.h"
#include "UART0.h"
#include "sensors.h"
#include "pit.h"


int main()
{
	
	slcdInitialize();
	ledsInitialize();
	uart0Init();
	
	i2cInitialize();
	tempsensorInitialize();
	lightsensorInitialize();
	pressensorInitialize();
	humidsensorInitialize();
	pitInitialize();
	
	while(1)
	{
	}
}
