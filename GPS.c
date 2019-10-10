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
    answer = Sim80x_SendAtCommand("AT+CGPSPWR=%d\r\n",10000,2,"\r\nOK\r\n","\r\nERROR\r\n",(int)power);
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
//####################################################################################################
void GPS_GetField_char(const char* response, SIM808GpsField field, char** result)
{
  char *pTmp = find(response, ',', (uint8_t)field);
  *result = pTmp;
}
//####################################################################################################
bool GPS_GetField_uint16(const char* response, SIM808GpsField field, uint16_t* result)
{
  if (field < SIM808GpsField::Speed) return false;
  parse_uint8(response, ',', (uint8_t)field, result);
  return true;
}
//####################################################################################################
bool GPS_GetField_float(const char*response, GPSField_t field, float* result)
{
  if (field != GPSField_t.Course && field != GPSField_t.Latitude && field != GPSField_t.Longitude && field != GPSField_t.Altitude && field != GPSField_t.Speed )
  {
    return false;
  }
  parse_uint8(response, ',', (uint8_t)field, result);
  return true;  
}
//####################################################################################################
GPSStatus_t GPS_GetStatus(char * response, size_t responseSize, uint8_t minSatellitesForAccurateFix)
{
  GPSStatus_t result = GPSStatus_t.NoFix;
  //at
  if(waitResponse(TO_F(TOKEN_GPS_INFO)) != 0)
  {
    return GPSStatus_t.Fail;
  }

  uint16_t shift = strlen_P(TOKEN_GPS_INFO) + 2;

  if(replyBuffer[shift] == '0')
    {
      result = GPSStatus_t.Off;
    }
  if(replyBuffer[shift + 2] == '1') // fix acquired
    {
      uint16_t satellitesUsed;
      GPS_GetField(replyBuffer, GPSStatus_t.GnssUsed, &satellitesUsed);

      result = satellitesUsed > minSatellitesForAccurateFix ?
      GPSStatus_t.AccurateFix :
      GPSStatus_t.Fix;
      copyCurrentLine(response, responseSize, shift);
    }

  if(waitResponse() != 0) 
    {
      return GPSStatus_t.Fail;
    }
  return result;
}
//####################################################################################################
bool GPS_GetPowerState(bool *state)
{
  uint8_t answer;
  answer = Sim80x_SendAtCommand("AT+CGPSPWR?\r\n",10000,2,"+CGPSPWR: 0\r\n\r\nOK\r\n","+CGPSPWR: 1\r\n\r\nOK\r\n");
  if (answer = 1)
  {
    *state = 0;
  }
  if (answer = 2)
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
#endif
