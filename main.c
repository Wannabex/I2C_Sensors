/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    main.c
 *      Purpose: Design Laboratory Sensors project
 *----------------------------------------------------------------------------
 *      
 *---------------------------------------------------------------------------*/

#include "MKL46Z4.h"
#include "buttons.h"
#include "slcd.h"
#include "leds.h"
#include "i2c.h"
#include "UART0.h"
#include "sensors.h"

uint8_t j;
int main()
{
	//buttonsInitialize();
	slcdInitialize();
	ledsInitialize();
	ledredBlink(2,50);
	uart0Init();
	
	i2cInitialize();
	tempsensorInitialize();
	lightsensorInitialize();
	pressensorInitialize();
	humidsensorInitialize();
	
	while(1)
	{
		for(i=0;i<4;i++)
		{
			switch(i)
			{
				case 0 :
			{
				ledsOff();
				slcdDisplay(tempRead(),10);
				uart0sendblock(tempRead());
			 break;
			}
			case 1 :
			{
				ledredOn();
				slcdDisplay(lightRead(),10);
				uart0sendblock(lightRead());
			 break;
			}
			case 2 :
			{
				ledsOff();
				ledgreenOn();
				slcdDisplay(pressRead(),10);	
				uart0sendblock(pressRead());
			 break;
			}
			case 3 :
			{
				ledredOn();			
				slcdDisplay(humidRead(),10);	
				uart0sendblock(humidRead());
			 break;
			}
			}
			delay_mc(200);
		}
	i=0;
		uart0transmit(' ');
	}
}
