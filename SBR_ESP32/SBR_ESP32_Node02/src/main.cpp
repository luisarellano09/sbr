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
 *  												INCLUDES - ARDUINO
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

#include "./Application/Manager/Manager.h"

/*******************************************************************************************************************************************
 *  												GLOBAL VARIABLES
 *******************************************************************************************************************************************/
// Manager Instance
Manager* manager;

// Task declaration
TaskHandle_t TaskCore0, TaskCore1;

// Timer declaration
hw_timer_t * timer0 = NULL;
hw_timer_t * timer1 = NULL;
hw_timer_t * timer2 = NULL;
hw_timer_t * timer3 = NULL;
portMUX_TYPE timerMux0 = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE timerMux1 = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE timerMux2 = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE timerMux3 = portMUX_INITIALIZER_UNLOCKED;

// Timer Flags
bool flagTimer0 = false;
bool flagTimer1 = false;
bool flagTimer2 = false;
bool flagTimer3 = false;

/*******************************************************************************************************************************************
 *  												TEST
 *******************************************************************************************************************************************/


/*******************************************************************************************************************************************
 *  												CORE LOOPS
 *******************************************************************************************************************************************/
// Loop of core 0
void LoopCore0( void * parameter ){
    disableLoopWDT();
    disableCore0WDT();
    while (true) {
        // Code for Timer 0 interruption
        if (flagTimer0){
            flagTimer0 = false;

            // ========== Code ==========

            // ==========================
        }

        // Code for Timer 1 interruption
        if (flagTimer1){
            flagTimer1 = false;

            // ========== Code ==========
                if (Serial.available()){
                    Serial.println("checking Serial");
                    char incomingByte = Serial.read();
                    Serial.flush();
                    switch (incomingByte) {
                        case 'w':
                        case 'W':
                            Serial.println(" +++++ ESP32 NODE02 +++++");
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
                            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::REGISTER_50, 250);
                            break;
                    }
                }

                // Run OTA service
                manager->m_wifiManager->RunOTA();

            // ==========================
        }

        manager->m_nodeESP32->Run();

        feedLoopWDT();
    }
}

// Loop of core 1
void LoopCore1( void * parameter ){
    disableLoopWDT();
    disableCore1WDT();
    while(true) {
        // Code for Timer 2 interruption
        if (flagTimer2){
            flagTimer2 = false;

            // ========== Code ==========
            //manager->CommunicationTestPublish();

            // ==========================
        }

        // Code for Timer 3 interruption
        if (flagTimer3){
            flagTimer3 = false;

            // ========== Code ==========

            // ==========================
        }

        feedLoopWDT();
    }
}

/*******************************************************************************************************************************************
 *  												TIMERS
 *******************************************************************************************************************************************/
// TIMER 0
void IRAM_ATTR onTimer0(){
    portENTER_CRITICAL_ISR(&timerMux0);

    flagTimer0 = true;

    portEXIT_CRITICAL_ISR(&timerMux0);
}

// TIMER 1
void IRAM_ATTR onTimer1(){
    portENTER_CRITICAL_ISR(&timerMux1);

    flagTimer1 = true;

    portEXIT_CRITICAL_ISR(&timerMux1);
}

// TIMER 2
void IRAM_ATTR onTimer2(){
    portENTER_CRITICAL_ISR(&timerMux2);

    flagTimer2 = true;

    portEXIT_CRITICAL_ISR(&timerMux2);
}

// TIMER 3
void IRAM_ATTR onTimer3(){
    portENTER_CRITICAL_ISR(&timerMux3);

    flagTimer3 = true;

    portEXIT_CRITICAL_ISR(&timerMux3);
}

/*******************************************************************************************************************************************
 *  												SETUP
 *******************************************************************************************************************************************/
void setup() {

    // Disable brownout detector
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); 

    // Serial Port
    Serial.begin(115200);
    Serial.println(" +++++ ESP32 NODE02 +++++");

    // Manager
    manager = new Manager();

    // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // Task of core 0
    xTaskCreatePinnedToCore(
        LoopCore0,  /* Function to implement the task */
        "LoopCore0",    /* Name of the task */
        10000,      /* Stack size in words */
        NULL,       /* Task input parameter */
        1,          /* Priority of the task */
        &TaskCore0, /* Task handle. */
        0);         /* Core where the task should run */

    delay(500);  // needed to start-up task1

    // Task of core 1
    xTaskCreatePinnedToCore(
        LoopCore1,  /* Function to implement the task */
        "LoopCore1",    /* Name of the task */
        10000,      /* Stack size in words */
        NULL,       /* Task input parameter */
        1,          /* Priority of the task */
        &TaskCore1, /* Task handle. */
        1);         /* Core where the task should run */
    
    // Timer0
    timer0 = timerBegin(0, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer0, &onTimer0, true); // edge (not level) triggered 
    timerAlarmWrite(timer0, 1000000, true); // 1000000 * 1 us = 1 s, autoreload true

    // Timer1
    timer1 = timerBegin(1, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer1, &onTimer1, true); // edge (not level) triggered 
    timerAlarmWrite(timer1, 2000000, true); // 2000000 * 1 us = 2 s, autoreload true

    // Timer2
    timer2 = timerBegin(2, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer2, &onTimer2, true); // edge (not level) triggered 
    timerAlarmWrite(timer2, 100000, true); //   1 us = 1 s, autoreload true

    // Timer3
    timer3 = timerBegin(3, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer3, &onTimer3, true); // edge (not level) triggered 
    timerAlarmWrite(timer3, 1000000, true); // 1000000 * 1 us = 1 s, autoreload true

    // Enable the timer alarms
    timerAlarmEnable(timer0); // enable
    timerAlarmEnable(timer1); // enable
    timerAlarmEnable(timer2); // enable
    timerAlarmEnable(timer3); // enable

}

/*******************************************************************************************************************************************
 *  												Main Loop
 *******************************************************************************************************************************************/
// Loop not used
void loop() {
    vTaskDelete(NULL);
}
