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
 *  												DECLARATION VARIABLES
 *******************************************************************************************************************************************/

TaskHandle_t TaskCLIHandle;             /**@brief Handle of Task CLI */
TaskHandle_t TaskGetValueCLIHandle;     /**@brief Handle of Task Get Value CLI */
TaskHandle_t TaskOTAHandle;             /**@brief Handle of Task OTA */
TaskHandle_t TaskNodeESP32Handle;       /**@brief Handle of Task Node ESP32 */
TaskHandle_t TaskModesHandle;           /**@brief Handle of Task Modes*/
TaskHandle_t TaskIMUHandle;             /**@brief Handle of Task IMU*/
TaskHandle_t TaskOdometryHandle;        /**@brief Handle of Task Odometry*/
TaskHandle_t TaskMotionControlHandle;   /**@brief Handle of Task Motion*/
TaskHandle_t TaskDatalogHandle;         /**@brief Handle of Task Datalog*/
TaskHandle_t TaskReg10Handle;

TickType_t TimerTaskCLI = 500 / portTICK_PERIOD_MS;             /**@brief Timer of Task CLI */
TickType_t TimerTaskOTA = 2000 / portTICK_PERIOD_MS;            /**@brief Timer of Task OTA */
TickType_t TimerTaskNodeESP32 = 1;                              /**@brief Timer of Task Node ESP32 */
TickType_t TimerTaskModes = 500 / portTICK_PERIOD_MS;           /**@brief Timer of Task Modes */
TickType_t TimerTaskIMU = 5 / portTICK_PERIOD_MS;               /**@brief Timer of Task IMU */
TickType_t TimerTaskOdometry = 10 / portTICK_PERIOD_MS;         /**@brief Timer of Task Odometry */
TickType_t TimerTaskMotionControl = 10 / portTICK_PERIOD_MS;    /**@brief Timer of Task Motion */
TickType_t TimerTaskDatalog = 100 / portTICK_PERIOD_MS;         /**@brief Timer of Task Datalog */


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
 * @brief TaskOdometry
 * 
 */
void TaskOdometry(void *parameter);

/**
 * @brief TaskMotion
 * 
 */
void TaskMotionControl(void *parameter);

/**
 * @brief Task Modes
 * 
 */
void TaskModes(void *parameter);

/**
 * @brief Task Datalog
 * 
 */
void TaskDatalog(void *parameter);

/**
 * @brief TaskReg10 
 * 
 */
void TaskReg10(void *parameter);

#endif // TASKSCONFIG_H