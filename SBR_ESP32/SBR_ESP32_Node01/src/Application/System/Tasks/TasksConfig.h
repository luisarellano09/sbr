/**
 * @file TasksConfig.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Declarations of the Tasks class
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
 *  												DECLARATION VARIABLES
 *******************************************************************************************************************************************/

TaskHandle_t TaskCLIHandle;                     /**@brief Handle of Task CLI */
TaskHandle_t TaskGetValueCLIHandle;             /**@brief Handle of Task Get Value CLI */
TaskHandle_t TaskOTAHandle;                     /**@brief Handle of Task OTA */
TaskHandle_t TaskNodeESP32Handle;               /**@brief Handle of Task Node ESP32 */
TaskHandle_t TaskModesHandle;                   /**@brief Handle of Task Modes */
TaskHandle_t TaskIMUHandle;                     /**@brief Handle of Task IMU */
TaskHandle_t TaskOdometryHandle;                /**@brief Handle of Task Odometry */
TaskHandle_t TaskMotionControlHandle;           /**@brief Handle of Task Motion */
TaskHandle_t TaskDatalogHandle;                 /**@brief Handle of Task Datalog */
TaskHandle_t TaskRegistersUpdateFastHandle;     /**@brief Handle of Task Registers Update Fast */
TaskHandle_t TaskRegistersUpdateSlowHandle;     /**@brief Handle of Task Registers Update */

TickType_t TimerTaskCLI = 500 / portTICK_PERIOD_MS;                     /**@brief Timer of Task CLI */
TickType_t TimerTaskOTA = 2000 / portTICK_PERIOD_MS;                    /**@brief Timer of Task OTA */
TickType_t TimerTaskNodeESP32 = 1 / portTICK_PERIOD_MS;                 /**@brief Timer of Task Node ESP32 */
TickType_t TimerTaskModes = 500 / portTICK_PERIOD_MS;                   /**@brief Timer of Task Modes */
TickType_t TimerTaskIMU = 5 / portTICK_PERIOD_MS;                       /**@brief Timer of Task IMU */
TickType_t TimerTaskOdometry = 10 / portTICK_PERIOD_MS;                 /**@brief Timer of Task Odometry */
TickType_t TimerTaskMotionControl = 10 / portTICK_PERIOD_MS;            /**@brief Timer of Task Motion */
TickType_t TimerTaskDatalog = 100 / portTICK_PERIOD_MS;                 /**@brief Timer of Task Datalog */
TickType_t TimerTaskRegistersUpdateFast = 100 / portTICK_PERIOD_MS;     /**@brief Timer of Task Registers Update Fast */
TickType_t TimerTaskRegistersUpdateSlow = 5000 / portTICK_PERIOD_MS;    /**@brief Timer of Task Registers Update Slow */


/*******************************************************************************************************************************************
 *  												DECLARATION FUNCTIONS
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
 * @param task Task Handle
 */
void PrintTaskInfo(TaskHandle_t* task);

/**
 * @brief TaskCLI
 * 
 * @param parameter Parameter
 */
void TaskCLI(void *parameter);

/**
 * @brief TaskGetValueCLI 
 * 
 * @param parameter Parameter
 */
void TaskGetValueCLI(void *parameter);

/**
 * @brief TaskOTA 
 * 
 * @param parameter Parameter
 */
void TaskOTA(void *parameter);

/**
 * @brief TaskNodeESP32 
 * 
 * @param parameter Parameter
 */
void TaskNodeESP32(void *parameter);

/**
 * @brief TaskIMU
 * 
 * @param parameter Parameter
 */
void TaskIMU(void *parameter);

/**
 * @brief TaskOdometry
 * 
 * @param parameter Parameter
 */
void TaskOdometry(void *parameter);

/**
 * @brief TaskMotion
 * 
 * @param parameter Parameter
 */
void TaskMotionControl(void *parameter);

/**
 * @brief Task Modes
 * 
 * @param parameter Parameter
 */
void TaskModes(void *parameter);

/**
 * @brief Task Datalog
 * 
 * @param parameter Parameter
 */
void TaskDatalog(void *parameter);

/**
 * @brief Task Registers Update Fast
 * 
 * @param parameter Parameter
 */
void TaskRegistersUpdateFast(void *parameter);

/**
 * @brief Task Registers Update Slow
 * 
 * @param parameter Parameter
 */
void TaskRegistersUpdateSlow(void *parameter);


#endif // TASKSCONFIG_H