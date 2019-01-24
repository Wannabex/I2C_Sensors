/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    sensors.c
 *      Purpose: Design Laboratory Sensors project
 *----------------------------------------------------------------------------
 *      
 */

#include "sensors.h"

 // initialization functions
 void tempsensorInitialize(void) 
 {
 }
 void lightsensorInitialize(void)
 {
	 databuffer[0] = ALSEnable | ALSPowerOn;
	i2cWrite(TSL25721,COMMANDnormMemAdr| ALSEnableRegisterMemAdr, databuffer, 1);
	 databuffer[0] = ALStime101ms;
	i2cWrite(TSL25721,COMMANDnormMemAdr | ALSTimeRegisterMemAdr, databuffer, 1);
  cpl=(float)(101*1)/(1*60);
 }
 void pressensorInitialize(void)
 {
	databuffer[0]= PresPowerDownMode | PresOutDataRate7Hz;
	i2cWrite(LPS331,PresCtrl1RegisterMemAdr, databuffer, 1);
	
 }
 void humidsensorInitialize(void)
 {
	 databuffer[0]=HumPowerDown | HumOutDataRate7Hz;
   i2cWrite(HTS221,HumCtrl1RegisterMemAdr, databuffer, 1);
	 databuffer[0]= HumNumberOfSamples64;
	 i2cWrite(HTS221,HumConfigRegisterMemAdr, databuffer, 1);
	 
	 // Let's read callibration coefficients for interpolation
	i2cRead(HTS221,HumCalCoeff0RegisterMemadr | (1<<7), databuffer, 2 );
	  Hcoeff0 = databuffer[0] / 2;
	  Hcoeff1 = databuffer[1] / 2;
	i2cRead(HTS221,HumCalInterpol0RegisterMemadr | (1<<7), databuffer, 2 );
	Hinterpol0 =  (((uint16_t)databuffer[1]) << 8) | databuffer[0] ;
	i2cRead(HTS221,HumCalInterpol1RegisterMemadr | (1<<7), databuffer, 2 ); 
	 Hinterpol1 =  (((uint16_t)databuffer[1]) << 8) | databuffer[0]; 
 }

 //read functions
float tempRead ()
 {
 i2cRead(STLM75,TempDataRegisterMemAdr, databuffer, 2 );
	temperature_value =(((uint16_t)databuffer[1] << 8) | databuffer[0]) >>7;
	 if(temperature_value && ((uint16_t)(1<<8)) ==1) 
	 tempresult=(-0.5)*(float)temperature_value;
	 else
	 tempresult=0.5*(float)temperature_value;
	 
 return tempresult;
 }
float lightRead (void)
{
		i2cRead(TSL25721,COMMANDincrMemAdr| ALSCh0DataLRegisterMemAdr, databuffer, 2); 
	visiblelight= (uint16_t)databuffer[1] <<8 | databuffer[0];
		i2cRead(TSL25721,COMMANDincrMemAdr| ALSCh1DataLRegisterMemAdr, databuffer, 2); 
	infralight= (uint16_t)databuffer[1] <<8 | databuffer[0];
	lux1=(float)(1*(float)visiblelight-1.87*(float)infralight)/cpl;
  lux2=(float)(0.63*(float)visiblelight-1*(float)infralight)/cpl;
  
	lightresult= ((lux1>lux2? lux1:lux2));
	lightresult=(lightresult>0 ? lightresult:0);

	return lightresult;
}
float pressRead (void)
{
	i2cRead(LPS331, PresOutXLRegisterMemAdr| (1<<7), databuffer, 3);
	pressure_value = databuffer[0] | (((uint16_t)databuffer[1]) << 8) | (((uint32_t)databuffer[2]) << 16); 
	pressresult=(float)pressure_value/4096;
	return pressresult;
}
float humidRead (void)
{
	 i2cRead(HTS221,HumOutLRegisterMemAdr | (1<<7), databuffer, 2);
	 humidity_value=(((uint16_t)databuffer[1]) <<8)|databuffer[0];
	 humresult= (float)( ( (uint16_t)Hcoeff1 - (uint16_t)Hcoeff0) * (humidity_value - Hinterpol0)) / (float)(Hinterpol1 - Hinterpol0) + (uint16_t)Hcoeff0; // interpolacja
	if (humresult>100)
		humresult/=10;
	return humresult;
}
 
