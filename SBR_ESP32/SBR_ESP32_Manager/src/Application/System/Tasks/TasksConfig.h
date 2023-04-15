/**
 * @file TasksConfig.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Tasks
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
 *  												VARIABLES DECLARATION
 *******************************************************************************************************************************************/

TaskHandle_t TaskCLIHandle;             /**@brief Handle of Task CLI */
TaskHandle_t TaskGetValueCLIHandle;     /**@brief Handle of Task Get Value CLI */
TaskHandle_t TaskOTAHandle;             /**@brief Handle of Task OTA */
TaskHandle_t TaskNodeESP32Handle;       /**@brief Handle of Task Node ESP32 */  
TaskHandle_t TaskModesHandle;           /**@brief Handle of Task Modes*/  

TickType_t TimerTaskCLI = 500 / portTICK_PERIOD_MS;         /**@brief Timer of Task CLI */
TickType_t TimerTaskOTA = 2000 / portTICK_PERIOD_MS;        /**@brief Timer of Task OTA */
TickType_t TimerTaskNodeESP32 = 1;                          /**@brief Timer of Task Node ESP32 */
TickType_t TimerTaskModes= 500 / portTICK_PERIOD_MS;        /**@brief Timer of Task Modes */


/*******************************************************************************************************************************************
 *  												FUNCTIONS DECLARATION
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
 * @param task Task handle
 */
void PrintTaskInfo(TaskHandle_t* task);

/**
 * @brief TaskCLI
 * 
 * @param parameter Parameters
 */
void TaskCLI(void *parameter);

/**
 * @brief TaskGetValueCLI 
 * 
 * @param parameter Parameters
 */
void TaskGetValueCLI(void *parameter);

/**
 * @brief TaskOTA 
 * 
 * @param parameter Parameters
 */
void TaskOTA(void *parameter);

/**
 * @brief TaskNodeESP32 
 * 
 * @param parameter Parameters
 */
void TaskNodeESP32(void *parameter);

/**
 * @brief Task Modes
 * 
 * @param parameter Parameters
 */
void TaskModes(void *parameter);

#endif // TASKSCONFIG_H