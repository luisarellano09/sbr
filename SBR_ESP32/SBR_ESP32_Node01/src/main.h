/**
 * @file main.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief main
 * 
 */

#ifndef MAIN_H
#define MAIN_H

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include <ArduinoLog.h>
#include "soc/rtc_cntl_reg.h"
#include "./Application/Tasks/Tasks.h"
#include "./Application/CLI/CLI.h"
#include "./Application/Datalog/Datalog.h"
#include "./Application/CommunicationBus/NodeEsp32/NodeHandler.h"
#include "./Application/Modes/Modes.h"


/*******************************************************************************************************************************************
 *  												DECLARATION
 *******************************************************************************************************************************************/

/**
 * @brief Init 
 * 
 */
void Init();


/*******************************************************************************************************************************************
 *  												DEFINITIONS
 *******************************************************************************************************************************************/

void Init(){

    // Disable brownout detector
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); 

    // Serial Port
    Serial.begin(115200);

    // Preferences
    preferences.begin("SBR", false);

    // Logging
    Log.begin(LOG_LEVEL_INFO, &Serial);

    // Manager Instance
    manager = new Manager();

    // Wifi Config
    manager->m_wifiManager->SetWifiCredencials(preferences.getString("WifiName"), preferences.getString("WifiPass"), String(ESP32_HOSTNAME));

    // IMU
    manager->m_IMU->SetCycleRotationVector(TimerTaskIMU*2);

    // External Handler
    manager->m_nodeESP32->ExtHandler = ExtHandler;

    // Init CLI
    InitCLI();

    // Init Modes
    InitModes();

    // Init Datalog
    InitDatalog();
    ActivateDataset(Datasets_e::DATASET_MOTOR);
    ActivateDataset(Datasets_e::DATASET_IMU);
    ActivateDataset(Datasets_e::DATASET_ODOMETRY);
    //ActivateDataset(Datasets_e::DATASET_MOTION_CONTROL);
}


#endif // MAIN_H