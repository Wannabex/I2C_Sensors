/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    sensors.h
 *      Purpose: Design Laboratory Sensors project
 *----------------------------------------------------------------------------
 *      
 */

 
 #ifndef sensors_h
 #define sensors_h
 
 #include "MKL46Z4.h"
 #include "i2c.h"
 
 // slave adresses
#define STLM75 0x49// temperature sensor adress
#define TSL25721 0x39 // light sensor adress ALS abmient light sensor 
#define LPS331 0x5d // pressure sensor adress
#define HTS221 0x5f // humidity sensor adress


// temperature sensor registers
#define TempDataRegisterMemAdr 0x00 // R 16b
#define TempConfRegisterMemAdr 0x01 // R/W 8b
#define TempOvertempShtdwnMemAdr 0x03 // R/W 16b

// light sensor registers
#define ALSEnableRegisterMemAdr 0x00 // R/W 8b
#define ALSConfRegisterMemAdr 0x0D // R/W 8b
#define ALSCh0DataLRegisterMemAdr 0x14 // R 8b   Ch0 is for visible and infrared
#define ALSCh0DataHRegisterMemAdr 0x15 // R 8b
#define ALSCh1DataLRegisterMemAdr 0x16 // R 8b   Ch1 is for infrared
#define ALSCh1DataHRegisterMemAdr 0x17 // R 8b
#define ALSTimeRegisterMemAdr 0x01 // R/W 8b
#define COMMANDnormMemAdr  0b10000000 // always use COMMAND with memory register 
#define COMMANDincrMemAdr 0b10100000
#define ALSEnable 0b00000010  // enable register
#define ALSPowerOn 0b00000001 // enable register
#define ALStime101ms 0xDB // ALSTimeReg  

//pressure sensor registers
#define PresCtrl1RegisterMemAdr 0x20 // R/W 8b
#define PresOutXLRegisterMemAdr 0x28 // R 8b
#define PresOutHRegisterMemAdr 0x29 // R 8b 
#define PresOutLRegisterMemAdr 0x30 // R 8b 
#define PresPowerDownMode 0b10000000 // ctrl1 register
#define PresOutDataRate7Hz 0b00100000 // ctrl1 register

//humidity sensor registers
#define HumConfigRegisterMemAdr 0x10 // R/W 8b
#define HumCtrl1RegisterMemAdr 0x20 // R/W 8b
#define HumOutLRegisterMemAdr 0x28 // R 8b
#define HumOutHRegisterMemAdr 0x29 // R 8b
#define HumNumberOfSamples64 0b00000100 // congif
#define HumPowerDown 0b10000000 // control 1
#define HumOutDataRate7Hz 0b00000010 // control 1
#define HumCalCoeff0RegisterMemadr 0x30 // for calibration
#define HumCalCoeff1RegisterMemadr 0x31
#define HumCalInterpol0RegisterMemadr 0x36 // for more callibration also 0x37
#define HumCalInterpol1RegisterMemadr 0x3A // also 0x3B
 
void tempsensorInitialize(void);
void lightsensorInitialize(void);
void pressensorInitialize(void);
void humidsensorInitialize(void);
 
float tempRead (void);
float lightRead (void);
float pressRead (void);
float humidRead (void);
////////////////////////////////' 
static uint8_t databuffer[4];

static int16_t temperature_value;
static uint16_t visiblelight,infralight;
static int32_t pressure_value;
static int16_t humidity_value;

static float tempresult,pressresult,lightresult;
static uint16_t humresult;
static float cpl, lux1, lux2;
static uint8_t Hcoeff0, Hcoeff1;
static uint16_t Hinterpol0, Hinterpol1;

 #endif
