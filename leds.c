/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    leds.c
 *      Purpose: Design Laboratory Sensors project
 *----------------------------------------------------------------------------
 *      
 */
 
 
 #include "leds.h"

/*----------------------------------------------------------------------------
  Function that initializes LEDs
 *----------------------------------------------------------------------------*/
void ledsInitialize(void){
	
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK; /* Enable Clock to Port D & E */ 
  PORTD->PCR[5] = PORT_PCR_MUX(1UL);  /* Pin PTD5 is GPIO */
	PORTE->PCR[29] = PORT_PCR_MUX(1UL);  /* Pin PTE29 is GPIO */
	
	
	
	PTD->PDDR |= led_mask[ledGreen];  /* enable PTD5 as Output */
	PTE->PDDR |= led_mask[ledRed];  /* enable PTE29 as Output */
	
	PTD->PSOR = led_mask[ledGreen];  /* switch Green LED off */
	PTE->PSOR = led_mask[ledRed];  /* switch Red LED off */
	
	//welcome sequence
	ledredBlink(2,50);
	ledgreenBlink(1,25);
}
/*----------------------------------------------------------------------------
  Function that blinks (x) times green led with (y) delay in mc
 *----------------------------------------------------------------------------*/
void ledgreenBlink(uint32_t x, uint32_t y){
	uint32_t count;
	
	for(count = 0; count < x; count++)
	{	
		PTD->PCOR = led_mask[ledGreen];
		delay_mc(y);		
		PTD->PSOR = led_mask[ledGreen];
		delay_mc(y);
	}
}
/*----------------------------------------------------------------------------
  Function that blinks (x) times red led with (y) delay in mc
 *----------------------------------------------------------------------------*/
void ledredBlink(uint32_t x, uint32_t y){
	uint32_t count;
	
	for(count = 0; count < x; count++){	
		PTE->PCOR = led_mask[ledRed];
		delay_mc(y);		
		PTE->PSOR = led_mask[ledRed];
		delay_mc(y);	
	}
}
/*----------------------------------------------------------------------------
  Function that turns all LEDs off
 *----------------------------------------------------------------------------*/
void ledsOff(void) {
		PTD->PSOR = led_mask[ledGreen];          /* switch Red LED off  */
	  PTE->PSOR = led_mask[ledRed];       /* switch Green LED off  */
}
/*----------------------------------------------------------------------------
  Function that turns all LEDs on
 *----------------------------------------------------------------------------*/
void ledsOn(void) {
		PTD->PCOR = led_mask[ledGreen];      	/* switch Red LED on  */
	  PTE->PCOR = led_mask[ledRed];     	/* switch Green LED on */
}

void ledredOn(void)
{
		PTD->PCOR = led_mask[ledGreen]; 
}
void ledgreenOn(void)
{	
		PTE->PCOR = led_mask[ledRed];
}
void ledredToggle(void)
{
	PTE->PTOR = led_mask[ledRed];
}
	
void ledgreenToggle(void)
{
	PTD->PTOR = led_mask[ledGreen];
}
