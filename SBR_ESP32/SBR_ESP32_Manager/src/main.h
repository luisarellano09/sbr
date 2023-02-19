/**
 * @file main.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief main
 * @version 1.0
 * @date 03.02.2023
 * 
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
#include "./Definition/Local/GlobalVar.h"
#include "./Application/Tasks/Tasks.h"
#include "./Application/CLI/CLI.h"

/*******************************************************************************************************************************************
 *  												DECLARATION
 *******************************************************************************************************************************************/

/**
 * @brief InitMain 
 * 
 */
void InitMain();


/*******************************************************************************************************************************************
 *  												DEFINITION
 *******************************************************************************************************************************************/

void InitMain(){

    // Disable brownout detector
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); 
    Log.traceln("Disable brownout detector");

    // Serial Port
    Serial.begin(115200);

    // Logging
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);

    // Manager Instance
    manager = new Manager();

    // Init CLI
    InitCLI();

    // Init Tasks
    InitTasks();

}



#endif // MAIN_H