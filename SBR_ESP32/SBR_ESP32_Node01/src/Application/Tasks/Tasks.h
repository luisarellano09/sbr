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

void InitTasks(){
    InitQueues();
    disableLoopWDT();
    disableCore0WDT();
    disableCore1WDT();
    xTaskCreatePinnedToCore(TaskCLI,            "TaskCLI",          5000,   NULL,   1,      &TaskCLIHandle,         1);         
    xTaskCreatePinnedToCore(TaskGetValueCLI,    "TaskGetValueCLI",  1000,   NULL,   1,      &TaskGetValueCLIHandle, 1);  
    xTaskCreatePinnedToCore(TaskOTA,            "TaskOTA",          5000,   NULL,   1,      &TaskOTAHandle,         0);  
    xTaskCreatePinnedToCore(TaskNodeESP32,      "TaskNodeESP32",    10000,  NULL,   2,      &TaskNodeESP32Handle,   0);         
    xTaskCreatePinnedToCore(TaskIMU,            "TaskIMU",          2000,   NULL,   1,      &TaskIMUHandle,         1);   
    xTaskCreatePinnedToCore(TaskMotion,         "TaskMotion",       2000,   NULL,   1,      &TaskMotionHandle,      1);         
    xTaskCreatePinnedToCore(TaskModes,          "TaskModes",        10000,  NULL,   1,      &TaskModesHandle,       1);
}


//=====================================================================================================

void InitQueues(){
    queue_Register10 = xQueueCreate(10,sizeof(double));
}


//=====================================================================================================

void MonitorTasks(){
    PrintTaskInfo(&TaskCLIHandle);
    PrintTaskInfo(&TaskGetValueCLIHandle);
    PrintTaskInfo(&TaskOTAHandle);
    PrintTaskInfo(&TaskNodeESP32Handle);
    PrintTaskInfo(&TaskIMUHandle);
    PrintTaskInfo(&TaskMotionHandle);
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

void TaskIMU(void *parameter){
    while(true) {
        manager->m_IMU->Run();
        vTaskDelay(TimerTaskIMU);
    }
}


//=====================================================================================================

void TaskMotion(void *parameter){
    while(true) {
        manager->m_motion->Run();
        vTaskDelay(TimerTaskMotion);
    }
}


//=====================================================================================================

void TaskModes(void *parameter){
    while(true) {
        RunModes();
        vTaskDelay(TimerTaskModes);
    }
}


//=====================================================================================================

void TaskReg10(void *parameter){
    while(true) {
        // double data_Register10 = 0.0;
        // if (xQueueReceive(queue_Register10, &data_Register10, 0) == pdTRUE){
        //     Log.infoln("New reg10: %D", data_Register10);
        //     //manager->counter = data_Register10;
        // }

        //manager->counter = manager->counter + 0.1;
        //Log.infoln("Reg10: %D", manager->counter);
        //manager->m_IMU->Run();
        //vTaskDelay(5);
    }
}

#endif // TASKS_H