/**
 * @file Tasks.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Tasks
 * @version 1.0
 * @date 03.02.2023
 * 
 * 
 */

#ifndef TASKS_H
#define TASKS_H

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include <ArduinoLog.h>
#include "soc/soc.h"
#include "../../Definition/Local/GlobalVar.h"
#include "../CLI/CLI.h"


/*******************************************************************************************************************************************
 *  												DECLARATION
 *******************************************************************************************************************************************/

void InitTasks();
void TaskCLI(void *parameter);
void TaskOTA(void *parameter);
void TaskNodeESP32(void *parameter);


/*******************************************************************************************************************************************
 *  												DEFINITION
 *******************************************************************************************************************************************/

/*  == EXAMPLE ==
    xTaskCreatePinnedToCore(
        LoopCore0,      // Function to implement the task
        "LoopCore0",    // Name of the task 
        10000,          // Stack size in words 
        NULL,           // Task input parameter 
        1,              // Priority of the task, higher Number higher priority
        &TaskCore0,     // Task handle.
        0);             // Core where the task should run 

*/

/**
 * @brief InitTasks 
 * 
 */
void InitTasks(){

    disableLoopWDT();
    disableCore0WDT();
    disableCore1WDT();
    xTaskCreatePinnedToCore(TaskCLI,            "TaskCLI",          2000,   NULL,   1,      &TaskCLIHandle,         1);         
    xTaskCreatePinnedToCore(TaskOTA,            "TaskOTA",          5000,   NULL,   1,      &TaskOTAHandle,         0);  
    xTaskCreatePinnedToCore(TaskNodeESP32,      "TaskNodeESP32",    10000,  NULL,   10,     &TaskNodeESP32Handle,   0);             
}


//=====================================================================================================

/**
 * @brief TaskCLI 
 * 
 */
void TaskCLI(void *parameter){

    F_CLI_Hello();
    F_CLI_Info();
    
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(true) {
        vTaskDelayUntil(&xLastWakeTime, TimerTaskCLI);
        RunCLI();
    }
}


//=====================================================================================================

/**
 * @brief TaskOTA 
 * 
 */
void TaskOTA(void *parameter){
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(true) {
        vTaskDelayUntil(&xLastWakeTime, TimerTaskOTA);
        manager->m_wifiManager->RunOTA();
    }
}


//=====================================================================================================

/**
 * @brief TaskNodeESP32 
 * 
 */
void TaskNodeESP32(void *parameter){
    while(true) {
        manager->m_nodeESP32->Run();
        vTaskDelay(TimerTaskNodeESP32);
    }
}


#endif // TASKS_H