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
#include "../lib//Definition/GlobalDef.h"
#include "soc/rtc_wdt.h"
//#include "SPI.h"
/*******************************************************************************************************************************************
 *  												INCLUDES - SBR
 *******************************************************************************************************************************************/
#include "./Manager/Manager.h"
//#include "./IMUManager/IMUManager.h"
#include "./BNO080/SparkFun_BNO080_Arduino_Library.h"

/*******************************************************************************************************************************************
 *  												GLOBAL VARIABLES
 *******************************************************************************************************************************************/
// Manager Instance
Manager* manager;
//IMU Instance
//IMUManager *myIMU;
BNO080 *myIMU;
SPIClass *SPI2BNO080 = NULL;   
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
void test_Add_Requests();
uint32_t test_counter = 0;

/*******************************************************************************************************************************************
 *  												CORE LOOPS
 *******************************************************************************************************************************************/
// Loop of core 0
void LoopCore0( void * parameter ){
    while(true) {
        //Serial.println("TEST");
        // Code for Timer 0 interruption
        if (flagTimer0){
            flagTimer0 = false;

            // ========== Code ==========
            /*Nothing to DO*/
            // ==========================

        }

        // Code for Timer 1 interruption
        if (flagTimer1){
            flagTimer1 = false;
        }
        // ========== Code ==========
        if(Serial.available()){
            Serial.println("checking Serial");
            char incomingByte = Serial.read();
            Serial.flush();
            switch (incomingByte)
            {
                case 'w':
                case 'W':
                    Serial.println(" +++++ ESP32 SENSORS +++++");
                    break;
                case 'p':
                case 'P':
                    //myIMU = new IMUManager();
                    //Serial.println("myIMU created");
                    SPI2BNO080 = new SPIClass();
                    SPI2BNO080->begin(14,25,13,15);
                    myIMU = new BNO080();
                    //myIMU->enableDebugging(Serial);

                    if(myIMU->beginSPI(15, 4, 26, 27,1000000,*SPI2BNO080) == false)
                    {
                        Serial.println("myIMU error");
                        while(1);
                    }
                    break;
                case 'r':
                case 'R':
                    Serial.println("Restarting...");
                    
                    break;
                case '0':
                    myIMU->enableRotationVector(50); //Send data update every 50ms
                    myIMU->enableAccelerometer(50);
                    Serial.println(F("Rotation vector enabled"));
                    Serial.println(F("Output in form i, j, k, real, accuracy"));
                    break;
                case '1':
                    Serial.println("Adding requests....");
                    while(1){
                    delay(10); //You can do many other things. We spend most of our time printing and delaying.
  
                    //Look for reports from the IMU
                    if (myIMU->dataAvailable() == true)
                    {
                        float AccX = myIMU->getAccelX();
                        float AccY = myIMU->getAccelY();
                        float AccZ = myIMU->getAccelZ();
                        float Accurancy = myIMU->getAccelAccuracy();
                        //float quatI = myIMU->getQuatI();
                        //float quatJ = myIMU->getQuatJ();
                        //float quatK = myIMU->getQuatK();
                        //float quatReal = myIMU->getQuatReal();
                        //float quatRadianAccuracy = myIMU->getQuatRadianAccuracy();

                        Serial.print(AccX, 2);
                        Serial.print(F(","));
                        Serial.print(AccY, 2);
                        Serial.print(F(","));
                        Serial.print(AccZ, 2);
                        Serial.print(F(","));
                        Serial.print(Accurancy, 2);
                        Serial.print(F(","));
                        //Serial.print(quatRadianAccuracy, 2);
                        //Serial.print(F(","));
                        //Serial.print((float)measurements / ((millis() - startTime) / 1000.0), 2);
                        //Serial.print(F("Hz"));
                        Serial.println();
                    }
                    }
                    break;
            }
        }

        // Run OTA service
        //manager->m_wifiManager->RunOTA();

        // Delay to feed WDT
        delay(1);
        // ==========================

        // Run SPI Slave service
        //manager->m_spiSlaveManager->ListenRequest();
    }
}

// Loop of core 1
void LoopCore1( void * parameter ){
    while(true) {
        //Serial.println("TEST");
        // Code for Timer 2 interruption
        if (flagTimer2){
            flagTimer2 = false;

            // ========== Code ==========

            // ==========================
        }

        // Code for Timer 3 interruption
        if (flagTimer3){
            flagTimer3 = false;

            // ========== Code ==========

            // ==========================
        }

        // Delay to feed WDT
        delay(1);
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
    //WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); 
    //rtc_wdt_protect_off();
    //rtc_wdt_disable();



    // Serial Port
    Serial.begin(115200);
    Serial.println(" +++++ ESP32 SENSORS +++++");

    // Manager
    //manager = new Manager();
   
    
    /*Test PS0 PS1 IMU*/
	pinMode(2, OUTPUT);   
    digitalWrite(2, HIGH); //PS1 to HIGH
    pinMode(4, OUTPUT);   
    digitalWrite(4, HIGH); //PS1 to HIGH
    //myIMU = new IMUManager();

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
    Serial.println("start timer 0");
    timer0 = timerBegin(0, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer0, &onTimer0, true); // edge (not level) triggered 
    timerAlarmWrite(timer0, 10000, true); // 1000000 * 1 us = 1 s, autoreload true

    // Timer1
    Serial.println("start timer 1");
    timer1 = timerBegin(1, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer1, &onTimer1, true); // edge (not level) triggered 
    timerAlarmWrite(timer1, 2000000, true); // 1000000 * 1 us = 1 s, autoreload true

    // Timer2
    Serial.println("start timer 2");
    timer2 = timerBegin(2, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer2, &onTimer2, true); // edge (not level) triggered 
    timerAlarmWrite(timer2, 1000000, true); // 1000000 * 1 us = 1 s, autoreload true

    // Timer3
    Serial.println("start timer 3");
    timer3 = timerBegin(3, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer3, &onTimer3, true); // edge (not level) triggered 
    timerAlarmWrite(timer3, 1000000, true); // 1000000 * 1 us = 1 s, autoreload true

    // Enable the timer alarms
    //timerAlarmEnable(timer0); // enable
    //timerAlarmEnable(timer1); // enable
    //timerAlarmEnable(timer2); // enable
    //timerAlarmEnable(timer3); // enable
}

/*******************************************************************************************************************************************
 *  												Main Loop
 *******************************************************************************************************************************************/
// Loop not used
void loop() {
    vTaskDelete(NULL);
}

void test_Add_Requests(){
    manager->m_spiSlaveManager->AddWriteRequest(COM_REQUEST_REG_ID_e::TEST_R05, test_counter++);
    manager->m_spiSlaveManager->AddWriteRequest(COM_REQUEST_REG_ID_e::TEST_R06, 7);
    manager->m_spiSlaveManager->AddWriteRequest(COM_REQUEST_REG_ID_e::TEST_R07, 8);
    manager->m_spiSlaveManager->AddWriteRequest(COM_REQUEST_REG_ID_e::TEST_R08, 9);
    manager->m_spiSlaveManager->AddWriteRequest(COM_REQUEST_REG_ID_e::TEST_R09, test_counter++);
}


