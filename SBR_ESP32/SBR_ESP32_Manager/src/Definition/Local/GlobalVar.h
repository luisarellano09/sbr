/**
 * @file GlobalVar.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Global variables of SBR
 * @version 1.0
 * @date 07.02.2023
 * 
 */

#ifndef GLOBALVAR_H
#define GLOBALVAR_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include "../../Application/Manager/Manager.h"

/*******************************************************************************************************************************************
 *  												GLOBAL VARIABLES
 *******************************************************************************************************************************************/

static Manager* manager;                            /**@brief Instance of the manager */

// Task Handlers

TaskHandle_t TaskCLIHandle;
TaskHandle_t TaskOTAHandle;
TaskHandle_t TaskNodeESP32Handle;
TaskHandle_t TaskTestHandle;

// Task Timers (T)

TickType_t TimerTaskCLI = 1000 / portTICK_PERIOD_MS;
TickType_t TimerTaskOTA = 2000 / portTICK_PERIOD_MS;
TickType_t TimerTaskNodeESP32 = 1;


#endif /* GLOBALVAR_H */