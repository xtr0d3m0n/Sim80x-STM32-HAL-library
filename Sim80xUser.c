#include "Sim80x.h"

void  Sim80x_UserInit(void)
{
  #if (_SIM80X_USE_GNSS==1)
    GNSS_PowerOnOff(true); 
  #endif
  #if (_SIM80X_USE_GPRS==1)
    if(GPRS_ConnectToNetwork("","","",false) == true)
  	{
  	}
	#endif
  //GPRS_ConnectToNetwork("mcinet","","",false);
  //GPRS_HttpGet("www.google.com");  
}
