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

/**
 * @brief InitTasks 
 * 
 */
void InitTasks();

/**
 * @brief MonitorTasks
 * 
 */
void MonitorTasks();

/**
 * @brief Print Task information
 * 
 */
void PrintTaskInfo(TaskHandle_t* task);

/**
 * @brief TaskCLI 
 * 
 */
void TaskCLI(void *parameter);

/**
 * @brief TaskGetValueCLI 
 * 
 */
void TaskGetValueCLI(void *parameter);

/**
 * @brief TaskOTA 
 * 
 */
void TaskOTA(void *parameter);

/**
 * @brief TaskNodeESP32 
 * 
 */
void TaskNodeESP32(void *parameter);

/**
 * @brief Task Modes
 * 
 */
void TaskModes(void *parameter);

#endif // TASKSCONFIG_H