/**
 * @file TasksConfig.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Tasks
 * @version 1.0
 * @date 03.02.2023
 * 
 * 
 */

#ifndef TASKSCONFIG_H
#define TASKSCONFIG_H

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include "soc/soc.h"


/*******************************************************************************************************************************************
 *  												DECLARATION
 *******************************************************************************************************************************************/

void InitTasks();
void TaskMonitoring();
void TaskInfoPrint(TaskHandle_t* task);

void TaskCLI(void *parameter);
void TaskGetValueCLI(void *parameter);
void TaskOTA(void *parameter);
void TaskNodeESP32(void *parameter);
void TaskModes(void *parameter);

#endif // TASKSCONFIG_H