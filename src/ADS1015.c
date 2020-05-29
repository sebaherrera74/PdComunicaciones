/*==============================================================================
 * Program: ADS1015
 * Date: 2020/05
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/


#include "sapi.h"
#include "ADS1015.h"



void setGain(adsGain_t gain){
	m_gain=gain;
}



uint16_t readADC_SingleEnded(uint8_t channel) {

	bool_t retVal = TRUE; // True if OK

  if (channel > 3) {
    return 0;
  }

  // Start with default values
  uint16_t config =0;

  config=
      ADS1015_REG_CONFIG_CQUE_NONE |     // Disable the comparator (default val)
      ADS1015_REG_CONFIG_CLAT_NONLAT |   // Non-latching (default val)
      ADS1015_REG_CONFIG_CPOL_ACTVLOW |  // Alert/Rdy active low   (default val)
      ADS1015_REG_CONFIG_CMODE_TRAD |    // Traditional comparator (default val)
      ADS1015_REG_CONFIG_DR_1600SPS |    // 1600 samples per second (default)
      ADS1015_REG_CONFIG_MODE_SINGLE;    // Single-shot mode (default)
  //hasta aqui config=0x0183 de acuerdo a lo calculado anteriormente

  // Set PGA/voltage range
  config |= 0x0000 ;  //m_gain;

  //de acuerdo a lo que seleccino aqui m_gain me parametriza el vlor de conffig
  //si sellecciono m_gain=0x0000 entonces config =0x0183

  // Set single-ended input channel
  switch (channel) {
  case (0):
    config |= ADS1015_REG_CONFIG_MUX_SINGLE_0;  //0x4183
    break;
  case (1):
    config |= ADS1015_REG_CONFIG_MUX_SINGLE_1; //0x5183
    break;
  case (2):
    config |= ADS1015_REG_CONFIG_MUX_SINGLE_2; //0x6183
    break;
  case (3):
    config |= ADS1015_REG_CONFIG_MUX_SINGLE_3; //0x7183
    break;
  }

  //canal 0 -> config =0x4183
  //canal 1 -> config=0x5183
  //canal 2 -> config=0x6183
  //canal 3 -> config=0x7183

  // Set 'start single-conversion' bit
  config |= ADS1015_REG_CONFIG_OS_SINGLE;



  ////canal 0 -> config =0xC183
  //  canal 1  0xD183
  // canal 2   0xE183
  // canal3    0xF183



  uint8_t transmitDataBuffer[3]={ADS1015_REG_POINTER_CONFIG,config>>8,config & 0xFF};  //config>>8 me da la parte alta de config,config&0XFF la parte baja


  uint8_t dataToReadBuffer[1]={ ADS1015_REG_POINTER_CONVERT};
  uint8_t receiveDataBuffer[2]={0};

  retVal=i2cWrite(I2C0,ADS1015_ADDRESS,transmitDataBuffer,3,TRUE);

   delay(ADS1015_CONVERSIONDELAY);


   retVal=i2cRead(I2C0,ADS1015_ADDRESS,dataToReadBuffer,1,1,receiveDataBuffer,2,1) ;
   delay(ADS1015_CONVERSIONDELAY);
   if (retVal==TRUE){
	   return ((receiveDataBuffer[1]<<8) |(receiveDataBuffer[0]))>>4;
   }

   else return 0;




}

