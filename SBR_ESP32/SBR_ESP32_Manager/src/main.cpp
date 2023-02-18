/**
 * @file main.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief main class
 * @version 
 * @date 13-06-2020
 * 
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include "main.h"

/*******************************************************************************************************************************************
 *  												SETUP
 *******************************************************************************************************************************************/
void setup() {
    InitMain();
    InitTasks();
}

/*******************************************************************************************************************************************
 *  												Main Loop
 *******************************************************************************************************************************************/
// Loop not used
void loop() {
    vTaskDelete(NULL);
}

