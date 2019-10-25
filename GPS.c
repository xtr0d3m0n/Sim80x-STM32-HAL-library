#include "Sim80x.h"
#if (_SIM80X_USE_GPS==1)
//####################################################################################################
void GPS_PowerOnOff(bool power)
{
  uint8_t answer = 0;
  Sim80x.GPS = Off;
  //GPS_GetPowerState(); 
  if ((power == true) && (Sim80x.GPS == Off))
  {
    answer = Sim80x_SendAtCommand("AT+CGPSPWR=1\r\n",1000,2,"\r\r\nOK\r\n","\r\r\nERROR\r\n");
    if (answer == 1)
    {
      Sim80x.GPS = On;
    }
    else
    {
      Sim80x.GPS = Err;
    }
  }
  if ((power == true) && (Sim80x.GPS == On))
  {
    Sim80x.GPS = On;
  }
 
  if ((power == false) && (Sim80x.GPS == On))
  {
    answer = Sim80x_SendAtCommand("AT+CGPSPWR=0\r\n",1000,2,"\r\r\nOK\r\n","\r\r\nERROR\r\n");
    if (answer == 1)
    {
      Sim80x.GPS = Off;
    }
    else
    {
      Sim80x.GPS = Err;
    }
  }
  if ((power == false) && (Sim80x.GPS == Off))
  {
    Sim80x.GPS = Off;
  } 
}
//####################################################################################################
void GPS_GetField_char(const char* response, GPSField_t field, char** result)
{
  char *pTmp = find(response, ',', (uint8_t)field);
  *result = pTmp;
}
//####################################################################################################
bool GPS_GetField_uint16(const char* response, GPSField_t field, uint16_t* result)
{
  if (field < Speed) return false;
  parse_uint16(response, ',', (uint8_t)field, result);
  return true;
}
//####################################################################################################
bool GPS_GetField_float(const char*response, GPSField_t field, float* result)
{
  if (field != Course && field != Latitude && field != Longitude && field != Altitude && field != Speed )
  {
    return false;
  }
  parse_float(response, ',', (uint8_t)field, result);
  return true;  
}
//####################################################################################################
void GPS_GetStatus(void)
{	
  uint8_t answer = 0;
	answer = Sim80x_SendAtCommand("AT+CGPSSTATUS?\r\n",10000,4,"Location Unknown\r\r\nOK\r\n",
    "Location Not Fix\r\r\nOK\r\n","Location 2D Fix\r\r\nOK\r\n","Location 3D Fix\r\r\nOK\r\n");
    if (answer == 1)
    {
    Sim80x.GPS = Fail;
    }
    if (answer == 2)
    {
    Sim80x.GPS = NoFix;
    }
    if (answer == 3)
    {
    Sim80x.GPS = Fix;
    }
    if (answer == 4)
    {
    Sim80x.GPS = AccurateFix; 
    }
    else
    {
    Sim80x.GPS = Fail;
    }
}
//####################################################################################################
void GPS_GetPowerState()
{
  uint8_t answer = 0;
  //answer = Sim80x_SendAtCommand("AT+CGPSPWR?\r\n",1000,2,"\r\r\n+CGPSPWR:0\r\n\r\nOK\r\n","\r\r\n+CGPSPWR:1\r\n\r\nOK\r\n");
  Sim80x_SendString("AT+CGPSPWR?\r\n");
  if (answer == 1)
  {
    Sim80x.GPS = Off;
  }
  if (answer == 2)
  {
    Sim80x.GPS = On;
  }
  else
  {
    Sim80x.GPS = Fail;
  }
}
//####################################################################################################
bool GPS_GetGPSInfo(float *GPSInfoArray)
{
  Sim80x_SendString("AT+CGPSINF=0\r\n");
    if(GPS_GetField_float((char *)Sim80x.UsartRxBuffer,Longitude,&GPSInfoArray[0]))
    {
      return true;
    }
    if(GPS_GetField_float((char *)Sim80x.UsartRxBuffer,Latitude,&GPSInfoArray[1]))
    {
      return true;
    }
    if(GPS_GetField_float((char *)Sim80x.UsartRxBuffer,Altitude,&GPSInfoArray[2]))
    {
      return true;
    }
    if(GPS_GetField_float((char *)Sim80x.UsartRxBuffer,Utc,&GPSInfoArray[3]))
    {
      return true;
    }
    if(GPS_GetField_float((char *)Sim80x.UsartRxBuffer,TTFF,&GPSInfoArray[4]))
    {
      return true;
    }
    if(GPS_GetField_float((char *)Sim80x.UsartRxBuffer,SatsInView,&GPSInfoArray[5]))
    {
      return true;
    }
    if(GPS_GetField_float((char *)Sim80x.UsartRxBuffer,Speed,&GPSInfoArray[6]))
    {
      return true;
    }
    if(GPS_GetField_float((char *)Sim80x.UsartRxBuffer,Course,&GPSInfoArray[7]))
    {
      return true;
    }
    else
    {
      return false;
    }
}
//####################################################################################################
#endif
