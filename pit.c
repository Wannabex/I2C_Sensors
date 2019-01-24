/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    pit.c
 *      Purpose: Design Laboratory Sensors project
 *----------------------------------------------------------------------------
 *      
 *---------------------------------------------------------------------------*/
 
 #include "pit.h"
 
 #define PIT_IRQ_NBR (IRQn_Type) 22
 
 volatile static uint8_t i=0;
 
 void pitInitialize(void)
 {
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;

	NVIC_ClearPendingIRQ(PIT_IRQ_NBR);				/* Clear NVIC any pending interrupts on PIT */
	NVIC_EnableIRQ(PIT_IRQ_NBR);
	NVIC_SetPriority (PIT_IRQ_NBR, 1); 
	//Channel number 0
	PIT->CHANNEL[0].LDVAL=0x7A1200; // 8 millions for 8MHz clock
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK; //interr en
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK; // timer en

	PIT->MCR = 0x00; // enables pit module
 }
 
 void PIT_IRQHandler(void)
{
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK)
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
		uart0transmit(' ');
		i++;
		i=i%4;	
		
		PIT ->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
	}
	
}
