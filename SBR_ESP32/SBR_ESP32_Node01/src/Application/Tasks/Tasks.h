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
#include "TasksConfig.h"
#include <Arduino.h>
#include <ArduinoLog.h>
#include "soc/soc.h"
#include "./Definition/Local/GlobalVar.h"
#include "../CLI/CLIConfig.h"
#include "../Modes/ModesConfig.h"


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
    InitQueues();
    disableLoopWDT();
    disableCore0WDT();
    disableCore1WDT();
    xTaskCreatePinnedToCore(TaskCLI,            "TaskCLI",          5000,   NULL,   1,      &TaskCLIHandle,         1);         
    xTaskCreatePinnedToCore(TaskGetValueCLI,    "TaskGetValueCLI",  1000,   NULL,   1,      &TaskGetValueCLIHandle, 1);  
    xTaskCreatePinnedToCore(TaskOTA,            "TaskOTA",          5000,   NULL,   1,      &TaskOTAHandle,         0);  
    xTaskCreatePinnedToCore(TaskNodeESP32,      "TaskNodeESP32",    10000,  NULL,   10,     &TaskNodeESP32Handle,   0);         
    //xTaskCreatePinnedToCore(TaskReg10,          "TaskReg10",        10000,  NULL,   1,      &TaskReg10Handle,       1);          
    xTaskCreatePinnedToCore(TaskModes,          "TaskModes",        10000,  NULL,   1,      &TaskModesHandle,       1);
}


//=====================================================================================================

/**
 * 
 * @brief Initialization of Queues 
 * 
 */
void InitQueues(){
    queue_Register10 = xQueueCreate(10,sizeof(double));
}


//=====================================================================================================

/**
 * 
 * @brief Task Monitoring
 * 
 */
void TaskMonitoring(){
    TaskInfoPrint(&TaskCLIHandle);
    TaskInfoPrint(&TaskOTAHandle);
    TaskInfoPrint(&TaskNodeESP32Handle);
}


//=====================================================================================================

/**
 * 
 * @brief Print Task information
 * 
 */
void TaskInfoPrint(TaskHandle_t* task){
    Serial.println( "|Task: " + String(pcTaskGetName(*task)) + " | State: " + String(eTaskGetState(*task)) + " | Prio: " + String(uxTaskPriorityGet(*task)) + " | FreeStack: " + String(uxTaskGetStackHighWaterMark(*task)) );    
}


//=====================================================================================================

/**
 * 
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
 * 
 * @brief TaskGetValueCLI 
 * 
 */
void TaskGetValueCLI(void *parameter){
    
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(true) {
        vTaskDelayUntil(&xLastWakeTime, TimerTaskCLI);
        GetValueCLI();
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


//=====================================================================================================

/**
 * @brief TaskReg10 
 * 
 */
void TaskReg10(void *parameter){
    while(true) {
        double data_Register10 = 0.0;
        if (xQueueReceive(queue_Register10, &data_Register10, 0) == pdTRUE){
            Log.infoln("New reg10: %D", data_Register10);
            manager->counter = data_Register10;
        }

        manager->counter = manager->counter + 0.1;
        Log.infoln("Reg10: %D", manager->counter);
        
        vTaskDelay(1000);
    }
}


//=====================================================================================================

/**
 * @brief Task Modes
 * 
 */
void TaskModes(void *parameter){
    while(true) {
        RunModes();
        vTaskDelay(TimerTaskModes);
    }
}


#endif // TASKS_H