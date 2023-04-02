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
#include <Preferences.h>
#include "../../Application/Manager/Manager.h"

/*******************************************************************************************************************************************
 *  												GLOBAL VARIABLES
 *******************************************************************************************************************************************/

static Manager* manager;                /**@brief Instance of the manager */


//=====================================================================================================

static Preferences preferences;        /**@brief Preferences instance*/


//=====================================================================================================

QueueHandle_t queue_Register10;


//=====================================================================================================

TaskHandle_t TaskCLIHandle;             /**@brief Handle of Task CLI */
TaskHandle_t TaskGetValueCLIHandle;     /**@brief Handle of Task Get Value CLI */
TaskHandle_t TaskOTAHandle;             /**@brief Handle of Task OTA */
TaskHandle_t TaskNodeESP32Handle;       /**@brief Handle of Task Node ESP32 */
TaskHandle_t TaskModesHandle;           /**@brief Handle of Task Modes*/
TaskHandle_t TaskIMUHandle;             /**@brief Handle of Task IMU*/
TaskHandle_t TaskMotionControlHandle;   /**@brief Handle of Task Motion*/
TaskHandle_t TaskDatalogHandle;         /**@brief Handle of Task Datalog*/
TaskHandle_t TaskReg10Handle;

TickType_t TimerTaskCLI = 500 / portTICK_PERIOD_MS;             /**@brief Timer of Task CLI */
TickType_t TimerTaskOTA = 2000 / portTICK_PERIOD_MS;            /**@brief Timer of Task OTA */
TickType_t TimerTaskNodeESP32 = 1;                              /**@brief Timer of Task Node ESP32 */
TickType_t TimerTaskModes = 500 / portTICK_PERIOD_MS;           /**@brief Timer of Task Modes */
TickType_t TimerTaskIMU = 5 / portTICK_PERIOD_MS;               /**@brief Timer of Task IMU */
TickType_t TimerTaskMotionControl = 20 / portTICK_PERIOD_MS;    /**@brief Timer of Task Motion */
TickType_t TimerTaskDatalog = 100 / portTICK_PERIOD_MS;         /**@brief Timer of Task Datalog */


#endif /* GLOBALVAR_H */