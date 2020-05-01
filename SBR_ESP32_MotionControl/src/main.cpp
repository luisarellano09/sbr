/**
 * \file main.cpp
 * \author Luis Arellano - luis.arellano09@gmail.com
 * \date 16 April 2020
 *
 * \brief main class
 *
 * 
 * 
 * Changes
 * 30.04.2020: Add Manager system.
 * 16.04.2020: Class comments and RC_e concept
 * 13.04.2020: Doc was created
 * 
 *
 */

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/

#include <Arduino.h>
#include "./Manager/Manager.h"

/*******************************************************************************************************************************************
 *  												TEST
 *******************************************************************************************************************************************/
#include "../lib/SBR_Global/SpiSlave/SlaveSPI.h"
#include <SPI.h>

#define SO   (gpio_num_t)22     // azul
#define SI   (gpio_num_t)23     // verde
#define SCLK (gpio_num_t)19     // morado
#define SS   (gpio_num_t)18     // plomo

SlaveSPI slave(HSPI_HOST);  // VSPI_HOST

#include "../lib/SBR_Global/SpiSlave/SimpleArray.h"

typedef SimpleArray<uint8_t, int> array_t;

array_t master_msg(SPI_DEFAULT_MAX_BUFFER_SIZE);
array_t slave_msg(SPI_DEFAULT_MAX_BUFFER_SIZE);


void test_setup();
void test_run();


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
 *  												CORE LOOPS
 *******************************************************************************************************************************************/

// Loop of core 0
void LoopCore0( void * parameter ){
    while(true) {
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
                manager->m_wifiManager->Run();
            // ==========================
        }

        test_run();
        
        delay(1);
    }
}

// Loop of core 1
void LoopCore1( void * parameter ){
    while(true) {
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

    // Serial Port
    Serial.begin(115200);

    // Manager
    manager = new Manager();

    // TEST
    test_setup();

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
    manager->m_logger->Write("start timer 0");
    timer0 = timerBegin(0, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer0, &onTimer0, true); // edge (not level) triggered 
    timerAlarmWrite(timer0, 100000, true); // 1000000 * 1 us = 1 s, autoreload true

    // Timer1
    manager->m_logger->Write("start timer 1");
    timer1 = timerBegin(1, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer1, &onTimer1, true); // edge (not level) triggered 
    timerAlarmWrite(timer1, 1000000, true); // 1000000 * 1 us = 1 s, autoreload true

    // Timer2
    manager->m_logger->Write("start timer 2");
    timer2 = timerBegin(2, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer2, &onTimer2, true); // edge (not level) triggered 
    timerAlarmWrite(timer2, 1000000, true); // 1000000 * 1 us = 1 s, autoreload true

    // Timer3
    manager->m_logger->Write("start timer 3");
    timer3 = timerBegin(3, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer3, &onTimer3, true); // edge (not level) triggered 
    timerAlarmWrite(timer3, 1000000, true); // 1000000 * 1 us = 1 s, autoreload true

    // Enable the timer alarms
    timerAlarmEnable(timer0); // enable
    timerAlarmEnable(timer1); // enable
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

void test_setup(){
    slave.begin(SO, SI, SCLK, SS, 10);
}

void test_run(){
    //manager->m_logger->Write("Putos todos!!");
    if (slave.getInputStream()->length() > 0 && digitalRead(SS) == HIGH) {  // Slave SPI has got data in.
        while (slave.getInputStream()->length()) {
            slave.readToArray(slave_msg);  // Not the sample read() as Serial
        }
        //manager->m_logger->Write("slave input: ");
        //printlnHex(slave_msg);
        //for (int i = 0; i < slave_msg.length(); i++) {
            int a = slave_msg[0] + slave_msg[1] + slave_msg[2] + slave_msg[3] + slave_msg[4] + slave_msg[5] + slave_msg[6] + slave_msg[7] + slave_msg[8] + slave_msg[9];
            Serial.println(a);            
            //manager->m_logger->WriteValue(slave_msg[i]);
        //}
        //Serial.println("================================");
        slave_msg.clear();
        slave.flushInputStream();
    }
    //Serial.println()

}