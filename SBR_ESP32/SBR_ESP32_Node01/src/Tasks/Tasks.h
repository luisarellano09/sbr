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
#include "soc/soc.h"
#include "./main.h"

/*******************************************************************************************************************************************
 *  												DECLARATION
 *******************************************************************************************************************************************/

void InitTasks();
void TaskCLI(void *parameter);
void TaskOTA(void *parameter);
void TaskNodeESP32(void *parameter);


TaskHandle_t TaskCLIHandle;
TaskHandle_t TaskOTAHandle;
TaskHandle_t TaskNodeESP32Handle;


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
    xTaskCreatePinnedToCore(TaskCLI,            "TaskCLI",          2000,   NULL, 1, &TaskCLIHandle,        1);         
    xTaskCreatePinnedToCore(TaskOTA,            "TaskOTA",          2000,   NULL, 1, &TaskOTAHandle,        1);  
    xTaskCreatePinnedToCore(TaskNodeESP32,      "TaskNodeESP32",    10000,  NULL, 1, &TaskNodeESP32Handle,  0);          

}


//=====================================================================================================

void TaskCLI(void *parameter){
    Serial.println(" +++++ ESP32 MANAGER +++++");
    
    while(true) {

        //Serial.printf("\r\nTaskCLI %d", xPortGetCoreID());
        if (Serial.available()){
            Serial.println("checking Serial");
            char incomingByte = Serial.read();
            Serial.flush();
            switch (incomingByte) {
                case 'w':
                case 'W':
                    Serial.println(" +++++ ESP32 NODE01 +++++");
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

                case 'l':
                case 'L':
                    manager->EnableDebugMode();
                    Serial.println("Enable Debug...");
                    break;

                case 'k':
                case 'K':
                    manager->DisableDebugMode();
                    Serial.println("Disable Debug...");


                    break;    

                case 's':
                case 'S':        
                    manager->m_nodeESP32->Start();
                    Serial.println("Stating ESP32 Node...");
                    break;  

                case 'i':
                    manager->m_nodeESP32->PrintBuffer();
                    break;        

                case '1':
                    manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::REGISTER_51, 251);
                    break;

            }
        }        

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}



void TaskOTA(void *parameter){
    while(true) {
        // Run OTA service
        manager->m_wifiManager->RunOTA();
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}


void TaskNodeESP32(void *parameter){
    while(true) {
        manager->m_nodeESP32->Run();
        vTaskDelay(1);
    }
}



#endif // TASKS_H