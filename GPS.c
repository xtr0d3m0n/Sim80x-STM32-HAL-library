#include "Sim80x.h"
#if (_SIM80X_USE_GPS==1)
//####################################################################################################
void  GPS_PowerOnOff(bool power)
{
  uint8_t answer = 0;
  Sim80x.GPS.Off = 0;
  Sim80x.GPS.On = 0;
  Sim80x.GPS.Fail = 0;
  Sim80x.GPS.Err = 0;

  GPS_GetPowerState(); 
  if ((power == true) && (Sim80x.GPS.Off))
  {      
    HAL_Delay(100);
    answer = Sim80x_SendAtCommand("AT+CGPSPWR=1\r\n",1000,2,"AT+CGPSPWR=1\r\r\nOK\r\n","AT+CGPSPWR=1\r\r\nERROR\r\n");
    if (answer == 1)
    {
      Sim80x.GPS.On = 1;
    }
    else
    {

      Sim80x.GPS.Err = 1;
    }
  }
  if ((power == true) && (Sim80x.GPS.On))
  {
    Sim80x.GPS.On = 1;
  }
 
  if ((power == false) && (Sim80x.GPS.On))
  {
    answer = Sim80x_SendAtCommand("AT+CGPSPWR=0\r\n",1000,2,"AT+CGPSPWR=0\r\r\nOK\r\n","AT+CGPSPWR=0\r\r\nERROR\r\n");
    if (answer == 1)
    {
      Sim80x.GPS.Off = 1;
    }
    else
    {
      Sim80x.GPS.Err = 1;
    }
  }
  if ((power == false) && (Sim80x.GPS.Off))
  {
    Sim80x.GPS.Off = 1;
  }
  else
  {
    Sim80x.GPS.Fail = 1;
  } 
}
//####################################################################################################
void  GPS_GetField_char(const char* response, GPSField_t field, char** result)
{
  char *pTmp = find(response, ',', (uint8_t)field);
  *result = pTmp;
}
//####################################################################################################
bool  GPS_GetField_uint16(const char* response, GPSField_t field, uint16_t* result)
{
  if (field != SatsInView && field != TTFF)
  {
    return false;
  }
  if(parse_uint16(response, ',', (uint8_t)field, result))
    {
      return true;
    }
	else
	{
		return false;
	}
}
//####################################################################################################
bool  GPS_GetField_float(const char* response, GPSField_t field, float* result)
{
  if ((field != Course) && (field != Latitude) && (field != Longitude) && (field != Altitude) && (field != Speed))
  {
    return false;
  }
  if(parse_float(response, ',', (uint8_t)field, result))
  {
    return true;
  }
	else
	{
		return false;
	}
}
//####################################################################################################
void  GPS_GetStatus(void)
{	
  uint8_t answer = 0;
  Sim80x.GPS.Fail = 0;
  Sim80x.GPS.NoFix = 0;
  Sim80x.GPS.Fix = 0;
  Sim80x.GPS.AccurateFix = 0;

	answer = Sim80x_SendAtCommand("AT+CGPSSTATUS?\r\n",10000,4,"Location Unknown\r\n\r\nOK\r\n",
    "Location Not Fix\r\n\r\nOK\r\n","Location 2D Fix\r\n\r\nOK\r\n","Location 3D Fix\r\n\r\nOK\r\n");
    if (answer == 1)
    {
    Sim80x.GPS.Fail = 1;
    }
    else if (answer == 2)
    {
    Sim80x.GPS.NoFix = 1;
    }
    else if (answer == 3)
    {
    Sim80x.GPS.Fix = 1;
    }
    else if (answer == 4)
    {
    Sim80x.GPS.AccurateFix = 1; 
    }
    else
    {
    Sim80x.GPS.Fail = 1;
    }
}
//####################################################################################################
void  GPS_GetPowerState()
{
  uint8_t answer = 0;
  Sim80x.GPS.On = 0;
  Sim80x.GPS.Off = 0;
  Sim80x.GPS.Fail = 0;

  answer = Sim80x_SendAtCommand("AT+CGPSPWR?\r\n",1000,2,"+CGPSPWR: 0\r\n\r\nOK\r\n","+CGPSPWR: 1\r\n\r\nOK\r\n");
  if (answer == 1)
  {
    Sim80x.GPS.Off = 1;
  }
  else if (answer == 2)
  {
    Sim80x.GPS.On = 1;
  }
  else
  {
    Sim80x.GPS.Fail = 1;
  }
}
//####################################################################################################
void  GPS_Reset(uint8_t resetmode)
{
  uint8_t answer = 0;
  Sim80x.GPS.ColdReset = 0;
  Sim80x.GPS.HotReset = 0;
  Sim80x.GPS.WarmReset = 0;
  Sim80x.GPS.Err = 0;
  Sim80x.GPS.Fail = 0;
  
  answer = Sim80x_SendAtCommand("AT+CGPSRST?\r\n",1000,3,"+CGPSRST= 0\r\n\r\nOK\r\n","+CGPSRST= 1\r\n\r\nOK\r\n","+CGPSRST= 2\r\n\r\nOK\r\n");
  if (!(resetmode == (answer - 1)))
  {
    if(Sim80x_SendAtCommand("AT+CGPSRST=0\r\n",1000,2,"AT+CGPSRST=0\r\r\nOK\r\n","AT+CGPSRST=0\r\r\nERROR\r\n") == 1)
    {
      Sim80x.GPS.ColdReset = 1;
    }
    else
    {
      Sim80x.GPS.Err = 1; 
    }
  }
  else  if (!(resetmode == (answer - 1)))
  {
    if(Sim80x_SendAtCommand("AT+CGPSRST=1\r\n",1000,2,"AT+CGPSRST=1\r\r\nOK\r\n","AT+CGPSRST=1\r\r\nERROR\r\n") == 1)
    {
      Sim80x.GPS.HotReset = 1;
    }
    else
    {
      Sim80x.GPS.Err = 1; 
    }
  }
  else  if (!(resetmode == (answer - 1)))
  {
    if(Sim80x_SendAtCommand("AT+CGPSRST=2\r\n",1000,2,"AT+CGPSRST=2\r\r\nOK\r\n","AT+CGPSRST=2\r\r\nERROR\r\n") == 1)
    {
      Sim80x.GPS.WarmReset = 1;
    }
    else
    {
      Sim80x.GPS.Err = 1; 
    }
  } 
  else
  {
    Sim80x.GPS.Fail = 1;
  } 

}
//####################################################################################################
bool  GPS_GetGPSInfo(float *float_data,uint16_t *uint16_t_data)
{
  Sim80x_SendString("AT+CGPSINF=0\r\n");
  HAL_Delay(500);
    if(GPS_GetField_float((char *)Sim80x.UsartRxBuffer,Longitude,&float_data[0])  &&
       GPS_GetField_float((char *)Sim80x.UsartRxBuffer,Latitude,&float_data[1])   &&
       GPS_GetField_float((char *)Sim80x.UsartRxBuffer,Altitude,&float_data[2])   &&
       GPS_GetField_float((char *)Sim80x.UsartRxBuffer,Utc,&float_data[2])        &&
       GPS_GetField_float((char *)Sim80x.UsartRxBuffer,Speed,&float_data[3])      &&
       GPS_GetField_float((char *)Sim80x.UsartRxBuffer,Course,&float_data[4])
      )
		{
      return true;
    }
    if(GPS_GetField_uint16((char *)Sim80x.UsartRxBuffer,TTFF,&uint16_t_data[0])  &&
       GPS_GetField_uint16((char *)Sim80x.UsartRxBuffer,SatsInView,&uint16_t_data[1])
      )
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
