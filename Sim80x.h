#ifndef	_SIM80X_H
#define	_SIM80X_H

#include "usart.h"
#include "Cmsis_OS.h"
#include "Sim80xConfig.h"
#include "Sim80xTypes.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
//######################################################################################################################
//######################################################################################################################
//######################################################################################################################
extern Sim80x_t         Sim80x;
#define BUFFER_SIZE 64
extern char replyBuffer[BUFFER_SIZE];
#define min(X, Y) (((X) > (Y)) ? (X) : (Y));
//######################################################################################################################
//######################################################################################################################
//######################################################################################################################
void	                  Sim80x_SendString(char *str);
void                    Sim80x_SendRaw(uint8_t *Data,uint16_t len);
uint8_t                 Sim80x_SendAtCommand(char *AtCommand,int32_t  MaxWaiting_ms,uint8_t HowMuchAnswers,...);
//######################################################################################################################
void                    Sim80x_UserInit(void);
void				            Sim80x_RxCallBack(void);
void				            Sim80x_Init(osPriority Priority);
void                    Sim80x_SaveParameters(void);
void                    Sim80x_SetPower(bool TurnOn);
void                    Sim80x_SetFactoryDefault(void);
void                    Sim80x_GetIMEI(char *IMEI);
uint8_t                 Sim80x_GetRingVol(void);
bool                    Sim80x_SetRingVol(uint8_t Vol_0_to_100);
uint8_t                 Sim80x_GetLoadVol(void);
bool                    Sim80x_SetLoadVol(uint8_t Vol_0_to_100);
Sim80xWave_t            Sim80x_WaveGetState(void);
bool                    Sim80x_WaveRecord(uint8_t ID,uint8_t TimeLimitInSecond);  
bool                    Sim80x_WavePlay(uint8_t ID);  
bool                    Sim80x_WaveStop(void);  
bool                    Sim80x_WaveDelete(uint8_t ID);
bool                    Sim80x_SetMicGain(uint8_t Channel_0_to_4,uint8_t Gain_0_to_15);
bool                    Sim80x_GetMicGain(void);
bool                    Sim80x_TonePlay(Sim80xTone_t Sim80xTone,uint32_t  Time_ms);
bool                    Sim80x_ToneStop(void);
uint8_t                 Sim80x_GetToneVol(void);
bool                    Sim80x_SetToneVol(uint8_t Vol_0_to_100);
bool                    Sim80x_SetRingTone(uint8_t Tone_0_to_19,bool Save);
bool                    Sim80x_SetEchoParameters(uint8_t  SelectMic_0_or_1,uint16_t NonlinearProcessingRemove,uint16_t AcousticEchoCancellation,uint16_t NoiseReduction,uint16_t NoiseSuppression);
//######################################################################################################################
void                    Gsm_User(uint32_t StartupTime);
void                    Gsm_UserNewCall(const char *CallerNumber);
void                    Gsm_UserNewMsg(char *Number,char *Date,char *Time,char *msg);

bool                    Gsm_Ussd(char *send,char *receive);

bool                    Gsm_CallAnswer(void);
bool                    Gsm_CallDisconnect(void);
GsmVoiceStatus_t        Gsm_Dial(char *Number,uint8_t WaitForAnswer_second); 
GsmVoiceStatus_t        Gsm_GetLastVoiceActivity(void);
GsmMsgFormat_t          Gsm_MsgGetFormat(void);
bool                    Gsm_MsgSetFormat(GsmMsgFormat_t GsmMsgFormat);  
GsmMsgMemory_t          Gsm_MsgGetMemoryStatus(void);
bool                    Gsm_MsgSetMemoryLocation(GsmMsgMemory_t GsmMsgMemory);
GsmTECharacterSet_t     Gsm_MsgGetCharacterFormat(void);  
bool                    Gsm_MsgSetCharacterFormat(GsmTECharacterSet_t GsmTECharacterSet);
bool                    Gsm_MsgRead(uint8_t index);
bool                    Gsm_MsgDelete(uint8_t index);
bool                    Gsm_MsgGetServiceNumber(void);
bool                    Gsm_MsgSetServiceNumber(char *ServiceNumber);
bool                    Gsm_MsgGetTextModeParameter(void);
bool                    Gsm_MsgSetTextModeParameter(uint8_t fo,uint8_t vp,uint8_t pid,uint8_t dcs);
bool                    Gsm_MsgSendText(char *Number,char *msg);  
//######################################################################################################################
void                    Bluetooth_UserNewPairingRequest(char *Name,char *Address,char *Pass);
void                    Bluetooth_UserConnectingSpp(void);
void                    Bluetooth_UserNewSppData(char *NewData,uint16_t len);
bool                    Bluetooth_SetPower(bool TurnOn);
bool                    Bluetooth_GetHostName(void);  
bool                    Bluetooth_SetHostName(char *HostName);
BluetoothStatus_t       Bluetooth_GetStatus(void);
bool                    Bluetooth_AcceptPair(bool Accept);  
bool                    Bluetooth_AcceptPairWithPass(char *Pass);  
bool                    Bluetooth_SetAutoPair(bool  Enable);
bool                    Bluetooth_SetPairPassword(char  *Pass);
bool                    Bluetooth_Unpair(uint8_t  Unpair_0_to_all);  
bool                    Bluetooth_GetVisibility(void);
void                    Bluetooth_SetVisibility(bool Visible);
void                    Bluetooth_SppAllowConnection(bool Accept);
bool                    Bluetooth_SppSend(char *DataString);
//######################################################################################################################
bool                    GPRS_DeactivatePDPContext(void);
bool                    GPRS_GetAPN(char *Name,char *username,char *password);
bool                    GPRS_SetAPN(char *Name,char *username,char *password);
bool                    GPRS_StartUpGPRS(void);
void                    GPRS_GetLocalIP(char *IP);
void                    GPRS_GetCurrentConnectionStatus(void);
bool                    GPRS_GetMultiConnection(void);
bool                    GPRS_SetMultiConnection(bool Enable);


void                    GPRS_UserHttpGetAnswer(char *data,uint32_t StartAddress,uint16_t dataLen);
bool                    GPRS_ConnectToNetwork(char *Name,char *username,char *password,bool EnableMultiConnection);
bool                    GPRS_HttpGet(char *URL);

//######################################################################################################################
bool GPS_PowerOnOff(bool power);
bool GPS_GetPowerState(bool *state);
GPSStatus_t GPS_GetStatus(void);
bool GPS_GetGPSInfo(float *GPSInfoArray);
void GPS_GetField_char(const char* response, GPSField_t field, char** result);
bool GPS_GetField_uint16(const char* response, GPSField_t field, uint16_t* result);
bool GPS_GetField_float(const char* response, GPSField_t field, float* result);
//######################################################################################################################
size_t readNext(char * buffer, size_t size, uint16_t * timeout, char stop);
size_t copyCurrentLine(char *dst, size_t dstSize, uint16_t shift);
size_t safeCopy(const char *src, char *dst, size_t dstSize);
char* find(const char* str, char divider, uint8_t index);
bool parse_uint8(const char* str, char divider, uint8_t index, uint8_t* result);
bool parse_int8(const char* str, char divider, uint8_t index, int8_t* result);
bool parse_uint16(const char* str, char divider, uint8_t index, uint16_t* result);
#if defined(NEED_SIZE_T_OVERLOADS)
bool parse_size(const char* str, char divider, uint8_t index, size_t* result);
#endif
bool parse_int16(const char* str, char divider, uint8_t index, int16_t* result);
bool parse_float(const char* str, char divider, uint8_t index, float* result);
//######################################################################################################################
#endif
