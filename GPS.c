#include "Sim80x.h"
#if (_SIM80X_USE_GPS==1)
//####################################################################################################
bool GPS_PowerOnOff(bool power)
{
  uint8_t answer;
  bool current_state;
  if (!GPS_GetPowerState(&current_state) ||(current_state == power))
  {
    return false;
  }
  else
  {
    if (power)
    {
    answer = Sim80x_SendAtCommand("AT+CGPSPWR=1\r\n",10000,2,"\r\nOK\r\n","\r\nERROR\r\n");
      if (answer == 1)
      {
        return true;
      }
      else
      {
        return false;
      }
      }
    else
    {
    answer = Sim80x_SendAtCommand("AT+CGPSPWR=0\r\n",10000,2,"\r\nOK\r\n","\r\nERROR\r\n");
      if (answer == 1)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
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
GPSStatus_t GPS_GetStatus(void)
{	
  uint8_t answer = 0;
	answer = Sim80x_SendAtCommand("AT+CGPSSTATUS?\r\n",10000,5,"Location Unknown\r\n\r\nOK\r\n",
    "Location Not Fix\r\n\r\nOK\r\n","Location 2D Fix\r\n\r\nOK\r\n","Location 3D\r\n\r\nOK\r\n");
    if (answer == 1)
    {
      return Fail;
    }
    if (answer == 2)
    {
      return NoFix;
    }
    if (answer == 3)
    {
      return Fix;
    }
    if (answer == 3)
    {
      return AccurateFix;
    }
    else
    {
      return Fail;
    }
}
//####################################################################################################
bool GPS_GetPowerState(bool *state)
{
  uint8_t answer;
  answer = Sim80x_SendAtCommand("AT+CGPSPWR?\r\n",10000,2,"+CGPSPWR: 0\r\n\r\nOK\r\n","+CGPSPWR: 1\r\n\r\nOK\r\n");
  if (answer == 1)
  {
    *state = 0;
  }
  if (answer == 2)
  {
    *state = 1;
  }
  else
  {
    return false;
  }
  return true;
}
//####################################################################################################
bool GPS_GetGPSInfo(float *GPSInfoArray)
{
  if (Sim80x_SendAtCommand("AT+CGPSINF=0\r\n",10000,2,"%f,%f,%f,%f,%f,%f,%f,%f,\r\n\r\nOK\r\n"))
  {
    if(GPS_GetField_float(replyBuffer,Longitude,&GPSInfoArray[0]))
    {
      return true;
    }
    if(GPS_GetField_float(replyBuffer,Latitude,&GPSInfoArray[1]))
    {
      return true;
    }
    if(GPS_GetField_float(replyBuffer,Altitude,&GPSInfoArray[2]))
    {
      return true;
    }
    if(GPS_GetField_float(replyBuffer,Utc,&GPSInfoArray[3]))
    {
      return true;
    }
    if(GPS_GetField_float(replyBuffer,TTFF,&GPSInfoArray[4]))
    {
      return true;
    }
    if(GPS_GetField_float(replyBuffer,SatsInView,&GPSInfoArray[5]))
    {
      return true;
    }
    if(GPS_GetField_float(replyBuffer,Speed,&GPSInfoArray[6]))
    {
      return true;
    }
    if(GPS_GetField_float(replyBuffer,Course,&GPSInfoArray[7]))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}
//####################################################################################################
#endif
