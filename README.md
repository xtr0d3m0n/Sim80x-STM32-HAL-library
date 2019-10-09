# Sim80x-STM32-HAL-library
STM32 HAL based library for SIM80x devices.
This Library is heavily based on this https://github.com/nimaltd/Sim800_V2
All credit goes to the original authur

Use Keil MDK and CubeMX To generate the base code with RTOS enabled.
1) Enable FreeRTOS.
2) Config your usart and enable RX interrupt and TX DMA on CubeMX.
3) If you want Turn On By Microcontroller, One control Pin needed. (PowerKey>>>>output,open drain,default to SET)
PowerKey connect to Sim800 Power Key.(if Needed,See Sim80xConfig.h)
4) Select "General peripheral Initalizion as a pair of '.c/.h' file per peripheral" on project settings.
5) Config your Sim80xConfig.h file.
6) Add Sim80x_RxCallBack() on usart interrupt routin.
7) call Sim80x_Init(osPriorityLow) on your app.
8) Config your app on Sim80xUser.c,GsmUser.c,BlutoothUser.c,GprsUser.c.
#include "Sim80x.h"
.
.
.
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  Sim80x_RxCallBack();
}
.
.
.
/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{
  Sim80x_Init(osPriorityLow);
  osDelay(10000);
  Gsm_MsgSendText("+98911xxxxx,"test msg\r\n");
  for(;;)
  {
    osDelay(10);
  }
