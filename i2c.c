/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    i2c.c
 *      Purpose: Design Laboratory Sensors project
 *----------------------------------------------------------------------------
 *      
 */
 
 
#include "i2c.h"     
																	
#define I2C0_IRQn_NBR (IRQn_Type) 8

	void i2cInitialize(void)
	{
		SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;	
		SIM->SCGC4 |=SIM_SCGC4_I2C0_MASK;
		
		PORTC->PCR[8] |= PORT_PCR_MUX(2); // I2C1 SCL
		PORTC->PCR[9] |= PORT_PCR_MUX(2); // I2C1 SDA
		PORTE->PCR[8] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
		PORTE->PCR[9] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
		I2C0->C1 |= I2C_C1_IICEN_MASK; // I2C ENABLE
		I2C0->C1 |= I2C_C1_IICIE_MASK; // I2C INTERRUPT ENABLE
		I2C0->FLT|= I2C_FLT_STOPIE_MASK;//generate interrupt on stop condition 
		// desired baud rate is 100kHz 100kb/s
		// I2C baud rate = bus speed / (mul*scl)
		I2C0->F |= I2C_F_MULT(0b10); // mul = 4
		I2C0->F &= ~I2C_F_ICR_MASK; // 000000 scl = 20
		
		NVIC_SetPriority(I2C0_IRQn_NBR, 2);
		NVIC_ClearPendingIRQ(I2C0_IRQn_NBR);
		NVIC_EnableIRQ(I2C0_IRQn_NBR);
	}
	
	
	// writing to adressed device's registers
	void i2cWrite(uint8_t slaveadress, uint8_t memoryadress, uint8_t *databuffer, uint8_t datasize) // databuffer is an array
	{
		uint8_t i=0;
		i2cstarttransmit(slaveadress,memoryadress);
		for(i=0;i<datasize;i++,databuffer++)
		{
				//last byte transmitted
			 if(i==datasize-1)
				{
					I2C0->D = *databuffer;
					in_progress();	
				}
				else
				{
					if(I2C0->S & !I2C_S_RXAK_MASK)
						{
						 I2C0->D = *databuffer;
						 in_progress();
						 I2C0->C1 &= ~I2C_C1_MST_MASK; // STOP signal generated
						}
					else
						 I2C0->C1 &= ~I2C_C1_MST_MASK;	 //generate stop
				}
		}
		I2C0->C1 &= ~I2C_C1_MST_MASK; // STOP signal generated
		in_progress();
	}
	
	// writing then repeating START and reading from device
	void i2cRead(uint8_t slaveadress, uint8_t memoryadress, uint8_t *databuffer, uint8_t datasize) // databuffer is an array
	{
		uint8_t i=0;
	
		i2cstarttransmit(slaveadress,memoryadress);
	
		//freaking clock setup 1 was too fast for RSTA
		I2C0->C1 |=I2C_C1_RSTA_MASK; // repeated start for different mode (rx)
		I2C0->D = ((slaveadress<<1) | READ_SLAVE_MASK); // slave adress + READ
		in_progress();
		I2C0->C1 &= ~I2C_C1_TX_MASK; // master as receiver
		
		for(i=0;i<datasize;i++,databuffer++)
		{
			if(i==datasize-1)
				I2C0->C1 |= I2C_C1_TXAK_MASK; // no ack sent 
				*databuffer=I2C0->D;
				in_progress();
		}
	I2C0->C1 &=~I2C_C1_MST_MASK;
		*databuffer=I2C0->D;
	in_progress();
	I2C0->C1 &=~I2C_C1_TXAK_MASK;
  }
	
	void i2cstarttransmit(uint8_t slaveadress, uint8_t memoryadress)

	{
		I2C0->C1 |= I2C_C1_TX_MASK;
		I2C0->C1 |= I2C_C1_MST_MASK; // START signal generated
		I2C0->D = (slaveadress<<1) | WRITE_SLAVE_MASK ; // slave adress + write
		in_progress();
		I2C0->D = memoryadress; // register to write adress
		in_progress();
	}
	
	void I2C0_IRQHandler(void)
	{
		I2C0->FLT|= I2C_FLT_STOPF_MASK; //clear stopf flag
		I2C0->S |=I2C_S_IICIF_MASK; // clear interrupt flag
		if(I2C0->S & I2C_S_TCF_MASK) // transfer complete flag
			 transfer_flag=1;
	}
	
	void in_progress (void)
	{
		while(!transfer_flag);
		transfer_flag=0;
	}



