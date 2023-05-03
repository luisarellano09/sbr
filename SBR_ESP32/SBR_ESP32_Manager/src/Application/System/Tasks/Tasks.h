/**
 * @file Tasks.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Tasks
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
#include "../../../Definition/Local/GlobalVar.h"
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

void InitTasks(){
    disableLoopWDT();
    disableCore0WDT();
    disableCore1WDT();
    xTaskCreatePinnedToCore(TaskCLI,            "TaskCLI",          5000,   NULL,   1,      &TaskCLIHandle,         1);
    xTaskCreatePinnedToCore(TaskGetValueCLI,    "TaskGetValueCLI",  1000,   NULL,   1,      &TaskGetValueCLIHandle, 1);  
    xTaskCreatePinnedToCore(TaskOTA,            "TaskOTA",          5000,   NULL,   1,      &TaskOTAHandle,         0);
    xTaskCreatePinnedToCore(TaskNodeESP32,      "TaskNodeESP32",    10000,  NULL,   1,      &TaskNodeESP32Handle,   0);
    xTaskCreatePinnedToCore(TaskNodeLinux,      "TaskNodeLinux",    10000,  NULL,   1,      &TaskNodeLinuxHandle,   1);
    xTaskCreatePinnedToCore(TaskModes,          "TaskModes",        10000,  NULL,   1,      &TaskModesHandle,       1);
}


//=====================================================================================================

void MonitorTasks(){
    PrintTaskInfo(&TaskCLIHandle);
    PrintTaskInfo(&TaskGetValueCLIHandle);
    PrintTaskInfo(&TaskOTAHandle);
    PrintTaskInfo(&TaskNodeESP32Handle);
    PrintTaskInfo(&TaskNodeLinuxHandle);
    PrintTaskInfo(&TaskModesHandle);
}


//=====================================================================================================

void PrintTaskInfo(TaskHandle_t* task){
    Serial.println( "|Task: " + String(pcTaskGetName(*task)) + " | State: " + String(eTaskGetState(*task)) + " | Prio: " + String(uxTaskPriorityGet(*task)) + " | FreeStack: " + String(uxTaskGetStackHighWaterMark(*task)) );    
}


//=====================================================================================================

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

void TaskGetValueCLI(void *parameter){
    
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(true) {
        vTaskDelayUntil(&xLastWakeTime, TimerTaskCLI);
        GetValueCLI();
    }
}


//=====================================================================================================

void TaskOTA(void *parameter){
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(true) {
        vTaskDelayUntil(&xLastWakeTime, TimerTaskOTA);
        manager->m_wifiManager->RunOTA();
    }
}


//=====================================================================================================

void TaskNodeESP32(void *parameter){
    while(true) {
        manager->m_nodeESP32->Run();
        vTaskDelay(TimerTaskNodeESP32);
    }
}


//=====================================================================================================

void TaskNodeLinux(void *parameter){
    while(true) {
        manager->m_nodeLinux->Run();
        vTaskDelay(TimerTaskNodeLinux);
    }
}


//=====================================================================================================

void TaskModes(void *parameter){
    while(true) {
        RunModes();
        vTaskDelay(TimerTaskModes);
    }
}

#endif // TASKS_H