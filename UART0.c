/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    uart0.c
 *      Purpose: Microprocessors Laboratory
 *----------------------------------------------------------------------------
 *      
 */

 #include "UART0.h"

 
 #define UART0_IRQ_NBR (IRQn_Type) 12
 #define DATA_SIZE 4
 
 	static char ReceivedBlock[DATA_SIZE];
	static uint8_t i=0, j =0;
	static uint8_t text[]="Hello World! ";
	static uint8_t length = sizeof(text)/sizeof(uint8_t)-sizeof(uint8_t);
void uart0Init(void)
{
 SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
 SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; // PTA1 PTA2
	
 PORTA->PCR[1] = PORT_PCR_MUX(2); //RX
 PORTA->PCR[2] = PORT_PCR_MUX(2); //TX
	
 SIM->SOPT2 |= SIM_SOPT2_UART0SRC(2); // OSCERCLK 8MHz external reference clock
 UART0->C2 &= ~ UART_C2_TE_MASK; // blokada nadawania przy konfiguracji
 UART0->C2 &= ~ UART_C2_RE_MASK; // blokada odbierania
 UART0 ->C4 |= UART0_C4_OSR(0b11111); // Over Sampling Ratio x32
  // asynch module clock=8MHz chcemy BR=9600 BR= Asynch Module Clock/((OSR+1)*SBR) => SBR= 26,041
 UART0->BDH |= UART_BDH_SBR(0);
 UART0->BDL = UART_BDL_SBR(26);
 UART0->BDH &= ~UART_BDH_SBNS_MASK; // stop bit number select 0- one stop bit
 UART0->C1 &= ~UART_C1_M_MASK; // mode select 0- rx tx use 8 bit data character
 UART0->C1 &= ~UART_C1_PE_MASK; // parity enable 

 //UART0->C2 |= UART_C2_TIE_MASK; // TRANSMIT INTERRUPT ENABLE; HARDWARE TRIGGER REQUESTED WHEN TDRE=1
 UART0->C2 |= UART_C2_RIE_MASK; // RECEIVE INTERRUPT ENABLE; HARDWARE INTERRUPT REQUESTED WHEN RDRF=1
 NVIC_SetPriority(UART0_IRQ_NBR, 1);
 NVIC_ClearPendingIRQ(UART0_IRQ_NBR);
 NVIC_EnableIRQ(UART0_IRQ_NBR);

 UART0->C2 |= UART_C2_TE_MASK; // blokada nadawania przy konfiguracji
 UART0->C2 |= UART_C2_RE_MASK; // blokada odbierania	
 
 for(i=0;i<length;i++)
		uart0transmit(text[i]);
}
 void uart0transmit(uint8_t data)
 {
	 while(!(UART0->S1 & UART_S1_TDRE_MASK )) {} // TDRE=1 transmit data register empty;
	 UART0->D = data; // wpisanie data do bufora transmitujacego D
 }
 
uint8_t uart0receive(void)
{
	while(!(UART0->S1 & UART_S1_RDRF_MASK )) {} // RDRF=1 receive data register full
	return UART0->D; // odczytamy z bufora odbierajacego D
}
	

void UART0_IRQHandler(void)
{
	//TRANSMITER
//	if(UART0->S1 & UART_S1_TDRE_MASK)
//	{	
//	}
	//TRANSMITER
	//RECEIVER
	if(UART0->S1 & UART_S1_RDRF_MASK)
	{
		if(i<DATA_SIZE)
		{
			ReceivedBlock[i]=UART0->D;
			i++;
		}
		if(i==DATA_SIZE)
		{
			if(Ascii_to_int(&ReceivedBlock[2])==0 && Ascii_to_int(&ReceivedBlock[1])==0 && Ascii_to_int(&ReceivedBlock[0])==0)
		{
			switch (Ascii_to_int(&ReceivedBlock[3]))
			{
				case 1:
				{
				 ledgreenToggle();
				 break;
				}
				case 2:
				{
					ledredToggle();
				 break;
				}
			}
		}
		for(j=0;j<DATA_SIZE;j++)
		{
			slcdSet(ReceivedBlock[j], j+1); // set przyjmuje ascii albo int
			uart0transmit(ReceivedBlock[j]);
		  ReceivedBlock[j]=0;
		}
		i=0;
		j=0;
		
	  }
	}
	//RECEIVER

}
uint8_t Ascii_to_int (char* ptr)
{
	uint8_t result;
	switch (*ptr)
	{
			case 48:
			{
				result = 0;
				break;
			}
		case 49:
			{
				result = 1;
				break;
			}
			case 50:
			{
				result = 2;
				break;
			}
			case 51:
			{
				result = 3;
				break;
			}
			case 52:
			{
				result = 4;
				break;
			}
			case 53:
			{
				result = 5;
				break;
			}
			case 54:
			{
				result = 6;
				break;
			}
			case 55:
			{
				result = 7;
				break;
			}
			case 56:
			{
				result = 8;
				break;
			}
			case 57:
			{
				result = 9;
				break;
			}		
	}	
	return result;
}

uint8_t int_to_ascii (uint8_t* ptr)
{
	uint8_t result;
	switch (*ptr)
	{
			case 0:
			{
				result = 48;
				break;
			}
		case 1:
			{
				result = 49;
				break;
			}
			case 2:
			{
				result = 50;
				break;
			}
			case 3:
			{
				result = 51;
				break;
			}
			case 4:
			{
				result = 52;
				break;
			}
			case 5:
			{
				result = 53;
				break;
			}
			case 6:
			{
				result = 54;
				break;
			}
			case 7:
			{
				result = 55;
				break;
			}
			case 8:
			{
				result = 56;
				break;
			}
			case 9:
			{
				result = 57;
				break;
			}		
	}	
	return result;
}
void uart0sendblock (int32_t data)
{
	uint8_t datasize;
	uint8_t sendme[5];
	uint8_t i=0;
//	if(data<0)
//	{
//		uart0transmit('-');
//		data*=-1;
//	}
			if(data>=10000)
				datasize=5;
			else if(data>=1000)
					datasize=4;
			else if(data>=100 )
					datasize=3;
			else if(data>=10 )
					datasize=2;
			else
				datasize=1;
			
			for (i=0;i< datasize;i++ )
				{
					sendme[datasize-i-1]=data%10;
					data/=10;
				}
				
			for(i=0; i < datasize; i++)
				{	
					uart0transmit(int_to_ascii(&sendme[i]));
				}
				
			uart0transmit(' ');
}
