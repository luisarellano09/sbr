/**
 * @file TasksConfig.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Declarations of the Tasks class
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
 * @brief Initialization of Queues 
 * 
 */
void InitQueues();

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
 * @brief TaskIMU
 * 
 */
void TaskIMU(void *parameter);

/**
 * @brief TaskMotion
 * 
 */
void TaskMotion(void *parameter);

/**
 * @brief Task Modes
 * 
 */
void TaskModes(void *parameter);

/**
 * @brief TaskReg10 
 * 
 */
void TaskReg10(void *parameter);

#endif // TASKSCONFIG_H