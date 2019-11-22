#include "Sim80x.h"
#if (_SIM80X_USE_GNSS==1)
//####################################################################################################
void	GNSS_PowerOnOff(bool power)
{ 
	uint8_t answer = 0;
  	Sim80x.GNSS.Fail = 0;
  	Sim80x.GNSS.Err = 0;
  	Sim80x.GNSS.PwrSts = 0;
  	Sim80x.GNSS.Fix = 0;
  	Sim80x.GNSS.RunSts = 0;

  	GNSS_GetPowerState();
  if ((power == true) && (Sim80x.GNSS.PwrSts == 0))
  {      
    answer = Sim80x_SendAtCommand("AT+CGNSPWR=1\r\n",1000,2,"AT+CGNSPWR=1\r\r\nOK\r\n","AT+CGNSPWR=1\r\r\nERROR\r\n");
    if (answer == 1)
    {
      Sim80x.GNSS.PwrSts = 1;
    }
    else
    {
      Sim80x.GNSS.Err = 1;
    }
  }
  if ((power == true) && (Sim80x.GNSS.PwrSts == 1))
  {
    Sim80x.GNSS.PwrSts = 1;
  }
 
  if ((power == false) && (Sim80x.GNSS.PwrSts == 1))
  {
    answer = Sim80x_SendAtCommand("AT+CGNSPWR=0\r\n",1000,2,"AT+CGNSPWR=0\r\r\nOK\r\n","AT+CGNSPWR=0\r\r\nERROR\r\n");
    if (answer == 1)
    {
      Sim80x.GNSS.PwrSts = 0;
    }
    else
    {
      Sim80x.GNSS.Err = 1;
    }
  }
  if ((power == false) && (Sim80x.GNSS.PwrSts == 0))
  {
    Sim80x.GNSS.PwrSts = 0;
  }
}
//####################################################################################################
void	GNSS_GetPowerState(void)
{
	uint8_t answer = 0;
  Sim80x.GNSS.Fail = 0;
  Sim80x.GNSS.Err = 0;
  Sim80x.GNSS.PwrSts = 0;
  	 
  answer = Sim80x_SendAtCommand("AT+CGNSPWR?\r\n",1000,2,"+CGNSPWR: 0\r\n\r\nOK\r\n","+CGNSPWR: 1\r\n\r\nOK\r\n");
  if (answer == 1)
  {
   	Sim80x.GNSS.PwrSts = 0;
  }
  else if (answer == 2)
  {
   	Sim80x.GNSS.PwrSts = 1;
  }
  else
  {
  	Sim80x.GNSS.Err = 1;
  }
}
//####################################################################################################
void 	GNSS_GetStatus(void)
{
  uint8_t answer = 0;
  if (Sim80x.GNSS.PwrSts == 1)
  {
    answer = Sim80x_SendAtCommand("AT+CGNSINF\r\n",1000,1,"\r\n\r\nOK\r\n");
    if(answer == 1)
    {
      uint16_t temp = 0;
      if(GNSS_GetField_uint16((char *)Sim80x.UsartRxBuffer,Run,&temp) && (temp == 1))
      {
        Sim80x.GNSS.RunSts = 1;
      }
      else
      {
        Sim80x.GNSS.RunSts = 0;
      }
      if(GNSS_GetField_uint16((char *)Sim80x.UsartRxBuffer,Fix,&temp) && (temp == 1))
      {
        Sim80x.GNSS.Fix = 1;
      }
      else
      {
        Sim80x.GNSS.Fix = 0;
      }
    }
  }
  else
  {
    Sim80x.GNSS.RunSts = 0;
    Sim80x.GNSS.Fix = 0;
  }
}
//####################################################################################################
void  GNSS_GetField_char(const char* response, GNSSField_t field, char** result)
{
  char *pTmp = find(response, ',', (uint8_t)field);
  *result = pTmp;
}
//####################################################################################################
bool  GNSS_GetField_uint16(const char* response, GNSSField_t field, uint16_t* result)
{
  if (field != Run && field != Fix && field != GNSSSatsInView)
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
bool  GNSS_GetField_float(const char* response, GNSSField_t field, float* result)
{
  if ((field != Course) && (field != Latitude) && (field != Longitude) && (field != Altitude) && (field != Speed) && (field != UTC))
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
bool  GNSS_GetField_double(const char* response, GNSSField_t field, double* result)
{
  if ((field != Course) && (field != Latitude) && (field != Longitude) && (field != Altitude) && (field != Speed) && (field != UTC))
  {
    return false;
  }
  if(parse_double(response, ',', (uint8_t)field, result))
  {
    return true;
  }
  else
  {
    return false;
  }
}
//####################################################################################################
bool  GNSS_GetInfo(double *double_data,uint16_t *uint16_t_data)
{
	uint8_t answer = 0;
	GNSS_GetStatus();
	if(Sim80x.GNSS.RunSts == 1 && Sim80x.GNSS.Fix == 1)
	{
    answer = Sim80x_SendAtCommand("AT+CGNSINF\r\n",1000,1,"\r\n\r\nOK\r\n");
    if(answer == 1)
    {
		  if (GNSS_GetField_double((char *)Sim80x.UsartRxBuffer,UTC,&double_data[0])				&&
       		GNSS_GetField_double((char *)Sim80x.UsartRxBuffer,Latitude,&double_data[1])	 	&&
       		GNSS_GetField_double((char *)Sim80x.UsartRxBuffer,Longitude,&double_data[2])	&&
       		GNSS_GetField_double((char *)Sim80x.UsartRxBuffer,Altitude,&double_data[3])  	&&
       		GNSS_GetField_double((char *)Sim80x.UsartRxBuffer,Speed,&double_data[4])     	&&
       		GNSS_GetField_double((char *)Sim80x.UsartRxBuffer,Course,&double_data[5]))
		  {
			  return true;
		  }
		  else
		  {
			  return false;
		  }
    }
	}
	else
	{
		return false;
	}
}
//####################################################################################################
#endif
