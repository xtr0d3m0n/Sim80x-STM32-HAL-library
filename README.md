# Sim80x-STM32-HAL-library
STM32 HAL based library for SIM80x devices.
This Library is heavily based on this https://github.com/nimaltd/Sim800_V2
All credit goes to the original author.

Use Keil MDK and CubeMX To generate the base code with RTOS enabled.
1) Config your usart and enable RX interrupt and TX DMA on CubeMX.
2) If you want Turn On By Microcontroller, One control Pin needed. (PowerKey>>>>output,open drain,default to SET)
PowerKey connect to Sim800 Power Key.(if Needed,See Sim80xConfig.h)
3) Select "General peripheral Initalizion as a pair of '.c/.h' file per peripheral" on project settings.
4) Config your Sim80xConfig.h file.
5) Add Sim80x_RxCallBack() on usart interrupt routin.
6) Config your app on Sim80xUser.c,GsmUser.c,BlutoothUser.c,GprsUser.c.
#include "Sim80x.h"
.
.
.
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  Sim80x_RxCallBack();
}
