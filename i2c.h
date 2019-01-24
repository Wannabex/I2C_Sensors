/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    i2c.h
 *      Purpose: Design Laboratory Sensors project
 *----------------------------------------------------------------------------
 *      
 */
 
#ifndef i2c_h
#define i2c_h
 
 #include "MKL46Z4.h"
 #include "leds.h"
 //#include "UART0.h"
 #define READ_SLAVE_MASK 1
 #define WRITE_SLAVE_MASK 0

 volatile static uint8_t transfer_flag=0;
 
 void i2cInitialize(void);
 void i2cWrite(uint8_t slaveadress,uint8_t memoryadress, uint8_t *databuffer, uint8_t datasize);
 void i2cRead(uint8_t slaveadress, uint8_t memoryadress, uint8_t *databuffer, uint8_t datasize);
 void i2cstarttransmit(uint8_t slaveadress, uint8_t memoryadress);
 void I2C0_IRQHandler(void);
 void in_progress (void);
 
#endif
