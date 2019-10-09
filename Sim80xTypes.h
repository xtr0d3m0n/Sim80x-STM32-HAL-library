#ifndef	_SIM80XTYPES_H
#define	_SIM80XTYPES_H

#include "usart.h"
#include "Cmsis_OS.h"
#include "Sim80xConfig.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
//######################################################################################################################
//######################################################################################################################
//######################################################################################################################
typedef enum
{
  Sim80xTone_DialTone=1,
  Sim80xTone_CalledSubscriberBusy=2,
  Sim80xTone_Congestion=3,
  Sim80xTone_RadioPathAcknowledge=4,
  Sim80xTone_RadioPathNotAvailable_CallDropped=5,
  Sim80xTone_Error_SpecialInformation=6,
  Sim80xTone_CallWaitingTone=7,
  Sim80xTone_RingingTone=8,
  Sim80xTone_GeneralBeep=16,
  Sim80xTone_PositiveAcknowledgementTone=17,
  Sim80xTone_NegativeAcknowledgementOrErrorTone=18,
  Sim80xTone_IndianDialTone=19,
  Sim80xTone_AmericanDialTone=20,
  
}Sim80xTone_t;
//######################################################################################################################
typedef enum
{
  Sim80xWave_Idle=0,
  Sim80xWave_Recording,
  Sim80xWave_Playing,
  
}Sim80xWave_t;
//######################################################################################################################
typedef enum
{
  GsmVoiceStatus_Idle,
  GsmVoiceStatus_ReturnError,
  GsmVoiceStatus_ReturnNoDialTone,
  GsmVoiceStatus_ReturnNoCarrier,
  GsmVoiceStatus_ReturnNoAnswer,
  GsmVoiceStatus_ReturnBusy,
  GsmVoiceStatus_IAnswerTheCall,
  GsmVoiceStatus_MyCallAnswerd,
  GsmVoiceStatus_Ringing,
  GsmVoiceStatus_Calling,
  
}GsmVoiceStatus_t;
//######################################################################################################################
typedef enum
{
  GsmTECharacterSet_Error,
	GsmTECharacterSet_GSM,
	GsmTECharacterSet_UCS2,
	GsmTECharacterSet_IRA,
	GsmTECharacterSet_HEX,
	GsmTECharacterSet_PCCP,
	GsmTECharacterSet_PCDN,
	GsmTECharacterSet_8859_1,	
	
}GsmTECharacterSet_t;
//######################################################################################################################
typedef enum
{
  GsmMsgMemory_Error,
  GsmMsgMemory_OnSim,
	GsmMsgMemory_OnModule,
	
}GsmMsgMemory_t;
//######################################################################################################################
typedef enum
{
  GsmMsgFormat_Error,
  GsmMsgFormat_PDU,
	GsmMsgFormat_Text,
	
}GsmMsgFormat_t;
//######################################################################################################################
typedef enum
{
  BluetoothStatus_Error=-1,
	BluetoothStatus_Initial=0,
	BluetoothStatus_Disactivating=1,
	BluetoothStatus_Activating=2,
	BluetoothStatus_Idle=5,
	BluetoothStatus_Scanning=6,
	BluetoothStatus_Inquiry_Res_Ind=7,
	BluetoothStatus_StoppingScanning=8,
	BluetoothStatus_Bonding=9,
	BluetoothStatus_Connecting=12,
	BluetoothStatus_Unpairing=13,
	BluetoothStatus_DeletingPairedDevice=14,
	BluetoothStatus_DeletingAllPairedDevice=15,
	BluetoothStatus_Disconnecting=16,
	BluetoothStatus_PairingConfirmWhilePassivePairing=19,
	BluetoothStatus_WaitingForRemoteConfirmWhilePassivePairing=20,
	BluetoothStatus_AcceptingConnection=25,
	BluetoothStatus_SDC_Refreshing=26,
	BluetoothStatus_SettingHostName=29,
	BluetoothStatus_ReleasingAllConnection=30,
	BluetoothStatus_ReleasingConnection=31,
	BluetoothStatus_ActivatingService=36,
	
}BluetoothStatus_t;
//######################################################################################################################
typedef struct
{
  char                  SendCommand[128];
  char                  ReceiveAnswer[10][64];
  uint32_t              SendCommandStartTime;
  uint32_t              ReceiveAnswerExeTime;
  uint16_t              ReceiveAnswerMaxWaiting;  
  uint8_t               FindAnswer; 
  
}Sim80xAtCommand_t;
//######################################################################################################################
typedef struct
{
  uint8_t               RegisterdToNetwork;
  uint8_t               DataTransferMode:1;
  uint8_t               Busy:1;
  uint8_t               Power:1;
  uint8_t               SmsReady:1;  
  uint8_t               CallReady:1;  
 
  uint8_t               BatteryCharging:1;
  uint8_t               BatteryFull:1;
  uint8_t               BatteryPercent;
  float                 BatteryVoltage;
  
  uint8_t               Signal; 
  
}Sim80xStatus_t;
//######################################################################################################################
typedef struct
{
  uint8_t               HaveNewCall:1;
  uint8_t               MsgReadIsOK:1;  
  uint8_t               MsgSent:1;  

  GsmVoiceStatus_t      GsmVoiceStatus;         
  char                  CallerNumber[16];
  char                  DiallingNumber[16]; 

  uint8_t               MsgTextModeParameterFo;
  uint8_t               MsgTextModeParameterVp;
  uint8_t               MsgTextModeParameterPid;
  uint8_t               MsgTextModeParameterDcs;
  char                  MsgServiceNumber[16];
  char                  MsgSentNumber[16];
  char                  MsgNumber[16];
  char                  MsgDate[8];
  char                  MsgTime[8];
  char                  Msg[_SIM80X_BUFFER_SIZE]; 
  GsmTECharacterSet_t   TeCharacterFormat;
  GsmMsgMemory_t        MsgMemory;
  GsmMsgFormat_t        MsgFormat;
  uint8_t               MsgCapacity;
  uint8_t               MsgUsed;
  uint8_t               HaveNewMsg[10];  
  
}Sim80xGsm_t;
//######################################################################################################################
typedef enum
{
  BluetoothProfile_NotSet=0,
  BluetoothProfile_GAP,
  BluetoothProfile_SDAP,
  BluetoothProfile_SSP,
  BluetoothProfile_GOEP,
  BluetoothProfile_OPP,
  BluetoothProfile_HSP_HFP,
  BluetoothProfile_A2DP,  
  
}BluetoothProfile_t;
//######################################################################################################################
typedef struct
{
  uint8_t               Visibility:1;
  uint8_t               NeedGetStatus:1;
  BluetoothStatus_t     Status;
  char                  HostName[19];
  char                  HostAddress[19];
  char                  PairingPassword[17];
  uint8_t               ConnectedID;
  char                  ConnectedName[19];
  char                  ConnectedAddress[19];
  BluetoothProfile_t    ConnectedProfile[5];
  BluetoothProfile_t    ConnectingRequestProfile;
  uint16_t              SPPLen;
  char                  SPPBuffer[1024];  
  
}Sim80xBluetooth_t;
//######################################################################################################################
typedef enum
{
  GPRSConnection_Idle=0,
  GPRSConnection_AlreadyConnect,
  GPRSConnection_ConnectOK,
  GPRSConnection_ConnectFail,    
  
}GPRSConnection_t;
//######################################################################################################################
typedef enum
{
  GPRSSendData_Idle=0,
  GPRSSendData_SendOK,
  GPRSSendData_SendFail,
  
}GPRSSendData_t;
//######################################################################################################################
typedef enum
{
  GPRSHttpMethod_GET=0,
  GPRSHttpMethod_POST=1,
  GPRSHttpMethod_HEAD=2,
  GPRSHttpMethod_DELETE=3,
  
}GPRSHttpMethod_t;
//######################################################################################################################
typedef struct 
{
  uint8_t                 CopyToBuffer;
  GPRSHttpMethod_t        Method;
  uint16_t                ResultCode;
  uint32_t                DataLen;
  uint32_t                TransferStartAddress;
  uint16_t                TransferDataLen;
  char                    Data[256];
  
}GPRSHttpAction_t;
//######################################################################################################################
typedef struct
{
  uint8_t               MultiConnection:1;
  char                  APN[17];
  char                  APN_UserName[17];
  char                  APN_Password[17];
  char                  LocalIP[17]; 
  GPRSConnection_t      Connection[5];
  GPRSSendData_t        SendStatus[5];
  
  GPRSHttpAction_t      HttpAction;  
  
}GPRS_t;
//######################################################################################################################
typedef enum
{
  uint8_t Fail;
  uint8_t Off;
  uint8_t NoFix;
  uint8_t Fix;
  uint8_t AccurateFix; 
}GPSStatus_t;
//######################################################################################################################
typedef enum
{
  uint8_t Longitude = 2;  
  uint8_t Latitude = 3;
  uint8_t Altitude = 4;
  uint8_t Utc = 5;
  uint8_t TTFF = 6;
  uint8_t GpsInView = 7; 
  uint8_t Speed = 8;
  uint8_t Course = 9;  
  //uint8_t GnssUsed = 10;
}GPSField_t;
//######################################################################################################################
typedef struct
{
  uint32_t              BufferStartTime;
  uint8_t               BufferExeTime;
  
	uint16_t	            UsartRxIndex;
	uint8_t		            UsartRxTemp;
	uint8_t		            UsartRxBuffer[_SIM80X_BUFFER_SIZE];
	uint32_t	            UsartRxLastTime;
  //
  Sim80xWave_t          WaveState;    
  //
  char                  IMEI[16];
  uint8_t               RingVol;
  uint8_t               LoadVol;
  uint8_t               MicGainMain;
  uint8_t               MicGainAux;
  uint8_t               MicGainMainHandsfree;
  uint8_t               MicGainAuxHandsfree;
  uint8_t               ToneVol;
  
  uint16_t              EchoHandset_NonlinearProcessing;
  uint16_t              EchoHandfree_NonlinearProcessing;
  uint16_t              EchoHandset_AcousticEchoCancellation;
  uint16_t              EchoHandfree_AcousticEchoCancellation;
  uint16_t              EchoHandset_NoiseReduction;
  uint16_t              EchoHandfree_NoiseReduction;
  uint16_t              EchoHandset_NoiseSuppression;
  uint16_t              EchoHandfree_NoiseSuppression;

	//
  Sim80xStatus_t        Status;
  //
  Sim80xAtCommand_t     AtCommand;
  //
  Sim80xGsm_t           Gsm;
  //
  #if (_SIM80X_USE_BLUETOOTH==1)
  Sim80xBluetooth_t     Bluetooth;
  #endif
	//
  #if (_SIM80X_USE_GPRS==1)
  GPRS_t                GPRS;
  #endif
  
}Sim80x_t;
//######################################################################################################################
#endif
