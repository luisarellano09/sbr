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
#include "./Definition/Local/GlobalVar.h"

/*******************************************************************************************************************************************
 *  												DECLARATION
 *******************************************************************************************************************************************/

// Functions

void InitTasks();
void TaskCLI(void *parameter);
void TaskOTA(void *parameter);
void TaskNodeESP32(void *parameter);
void TaskTest(void *parameter);


// Task Handlers

TaskHandle_t TaskCLIHandle;
TaskHandle_t TaskOTAHandle;
TaskHandle_t TaskNodeESP32Handle;
TaskHandle_t TaskTestHandle;

// Task Timers (T)

TickType_t TimerTaskCLI = 1000 / portTICK_PERIOD_MS;
TickType_t TimerTaskOTA = 2000 / portTICK_PERIOD_MS;
TickType_t TimerTaskNodeESP32 = 1;


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
    xTaskCreatePinnedToCore(TaskCLI,            "TaskCLI",          2000,   NULL, 1, &TaskCLIHandle,        1);         
    xTaskCreatePinnedToCore(TaskOTA,            "TaskOTA",          5000,   NULL, 1, &TaskOTAHandle,        0);  
    xTaskCreatePinnedToCore(TaskNodeESP32,      "TaskNodeESP32",    10000,  NULL, 1, &TaskNodeESP32Handle,  0); 
    xTaskCreatePinnedToCore(TaskTest,           "TaskTest",         10000,  NULL, 1, &TaskTestHandle,       1);              
}


//=====================================================================================================
/**
 * @brief TaskCLI 
 * 
 */
void TaskCLI(void *parameter){

    Serial.println(" +++++ ESP32 MANAGER +++++");
    
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(true) {

        vTaskDelayUntil(&xLastWakeTime, TimerTaskCLI);

        if(Serial.available()) {
            Serial.println("checking Serial");
            char incomingByte = Serial.read();
            Serial.flush();
            switch (incomingByte) {
                case 'w':
                case 'W':
                    Serial.println(" +++++ ESP32 MANAGER +++++");
                    break;

                case 'p':
                case 'P':
                    Serial.println("Programming Mode.....");
                    manager->m_nodeESP32->Stop();
                    manager->m_wifiManager->Connect();
                    break;

                case 'r':
                case 'R':
                    Serial.println("Restarting...");
                    ESP.restart();
                    break;

                case 's': 
                case 'S':        
                    manager->m_nodeESP32->Start();
                    Serial.println("Stating ESP32 Node...");
                    break; 

                case '1':
                    manager->m_tableRegister->PrintTable();
                    break;

                case '2':
                    manager->m_nodeESP32->AddRequest(DEVICE_e::ESP32_NODE01, COM_REQUEST_TYPE_e::WRITE, COM_REQUEST_REG_ID_e::REGISTER_10, 69);
                    manager->m_nodeESP32->PrintBuffer();
                    break;

                case '3':
                    manager->m_tableRegister->UpdateRegister(COM_REQUEST_REG_ID_e::REGISTER_50, 150);
                    manager->m_tableRegister->UpdateRegister(COM_REQUEST_REG_ID_e::REGISTER_51, 151);
                    manager->m_tableRegister->UpdateRegister(COM_REQUEST_REG_ID_e::REGISTER_52, 152);
                    break;

                case 'j':
                    if (xSemaphoreTake(semaphoreMutexGlobVar, 0) == pdTRUE){
                        counter++;
                    }
                    break;

                case 'k':
                    xSemaphoreGive(semaphoreMutexGlobVar);
                    break;

                case 'l': 
                    Log.fatalln("Fatal");           
                    Log.errorln("Error");
                    Log.warningln("Warning");
                    Log.infoln("Info %d", counter);
                    Log.noticeln("Notice");
                    Log.traceln("Trace");
                    Log.verboseln("Verbose");
                    break;

                case '4': 
                    Log.setLevel(LOG_LEVEL_FATAL);
                    break;

                case '5': 
                    Log.setLevel(LOG_LEVEL_ERROR);
                    break;

                case '6': 
                    Log.setLevel(LOG_LEVEL_WARNING);
                    break;

                case '7': 
                    Log.setLevel(LOG_LEVEL_INFO);
                    break;

                case '8': 
                    Log.setLevel(LOG_LEVEL_NOTICE);
                    break;

                case '9': 
                    Log.setLevel(LOG_LEVEL_TRACE);
                    break;

                case '0': 
                    Log.setLevel(LOG_LEVEL_VERBOSE);
                    break;


            }
        }
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
 * @brief TaskTest 
 * 
 */
void TaskTest(void *parameter){
    while(true) {
        
        if (xSemaphoreTake(semaphoreMutexGlobVar, 0) == pdTRUE){
            //Serial.println(counter);
            xSemaphoreGive(semaphoreMutexGlobVar);
        } else {
            //Serial.println(".");
        }
        

        vTaskDelay(1000);
    }
}


#endif // TASKS_H