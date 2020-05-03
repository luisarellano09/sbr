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

void test_setup();
void test_run();
void test_run_read();

void test_TX_frame();
void test_RX_frame();




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
                //test_run();
                //test_run_read();
                //test_TX_frame();
                test_RX_frame();
            // ==========================
        }

        // Code for Timer 1 interruption
        if (flagTimer1){
            flagTimer1 = false;

            // ========== Code ==========
                manager->m_wifiManager->Run();
            // ==========================
        }
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
    timerAlarmWrite(timer0, 2000000, true); // 1000000 * 1 us = 1 s, autoreload true

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

    // Setup Master-SPI


}





void test_run(){

/*
    master.beginTransaction(spi_setting);
    digitalWrite(MS, LOW);

    if (count>=99) count = 0;

    master.transfer(count++);
    master.transfer(count++);
    master.transfer(count++);
    master.transfer(count++);
    master.transfer(count++);
    master.transfer(count++);
    master.transfer(count++);
    master.transfer(count++);
    master.transfer(count++);
    master.transfer(count++);

    digitalWrite(MS, HIGH);
    master.endTransaction();

    */
}

void test_run_read(){
    /*
    // Read

    uint32_t fb1 = 0;
    uint8_t fb2 = 0;
    uint8_t data[8] = {1u};

    master.beginTransaction(spi_setting);
    digitalWrite(MS, LOW);

    //fb1 = master.transfer32(0) ;
    //fb2 = master.transfer(0);
    master.transferBytes(data, data, 8);

    digitalWrite(MS, HIGH);
    master.endTransaction();
    Serial.println("================================");
    // Serial.print("Byte1: ");
    // Serial.println((byte)fb1);
    // Serial.print("Byte2: ");
    // Serial.println((byte)(fb1>>8));
    // Serial.print("Byte3: ");
    // Serial.println((byte)(fb1>>16));
    // Serial.print("Byte4: ");
    // Serial.println((byte)(fb1>>24));

    Serial.print("Byte1: ");
    Serial.println(data[0]);
    Serial.print("Byte2: ");
    Serial.println(data[1]);
    Serial.print("Byte3: ");
    Serial.println(data[2]);
    Serial.print("Byte4: ");
    Serial.println(data[3]);
    Serial.print("Byte5: ");
    Serial.println(data[4]);
    Serial.print("Byte6: ");
    Serial.println(data[5]);
    Serial.print("Byte7: ");
    Serial.println(data[6]);
    Serial.print("Byte8: ");
    Serial.println(data[7]);

    //Serial.println(data[0]);
    //Serial.println(data[1]);
    
*/
}

// void test_run_read(){
    
//     // Read

//     uint8_t fb = 0;

//     master.beginTransaction(spi_setting);
//     digitalWrite(MS, LOW);

//     fb = master.transfer(0);

//     digitalWrite(MS, HIGH);
//     master.endTransaction();
//     Serial.println(fb);

// }

void test_TX_frame(){


/*
    localFrame.comFrameReq = COM_FRAME_REQ_e::WRITE;
    localFrame.comFrameRegId = COM_FRAME_REG_ID_e::TLF_DEVCFG2;
    localFrame.data = count++;
    localFrame.CRC = 69;

    uint8_t buffer[FRAME_SIZE];

    buffer[0] = localFrame.comFrameReq;
    buffer[1] = localFrame.comFrameRegId;
    buffer[2] = (byte)localFrame.data;
    buffer[3] = (byte)(localFrame.data>>8);
    buffer[4] = (byte)(localFrame.data>>16);
    buffer[5] = (byte)(localFrame.data>>24);
    buffer[6] = (byte)localFrame.CRC;
    buffer[7] = (byte)(localFrame.CRC>>8);
    
    master.beginTransaction(spi_setting);
    digitalWrite(MS, LOW);

    for(int i=0; i<FRAME_SIZE; i++){
        master.transfer(buffer[i]);
    }

    digitalWrite(MS, HIGH);
    master.endTransaction();

    */
}

void test_RX_frame(){

    /*

    uint8_t buffer[FRAME_SIZE] = {0};

    master.beginTransaction(spi_setting);
    digitalWrite(MS, LOW);

    master.transferBytes(buffer, buffer, 8);

    digitalWrite(MS, HIGH);
    master.endTransaction();

    COM_FRAME_st localFrame;

    //---------REQUEST--------
    localFrame.comFrameReq = buffer[0];

    //------------ID----------
    localFrame.comFrameRegId = buffer[1];

    //------------DATA----------
    localFrame.data = (buffer[2]);
    localFrame.data += (buffer[3])<<8;
    localFrame.data+= (buffer[4])<<16;
    localFrame.data += (buffer[5])<<24;

    //|-----------------CRC-------------------|
    localFrame.CRC = buffer[6];
    localFrame.CRC += (buffer[7])<<8;

    Serial.println("============== RX ==================");
    Serial.print("Req: ");
    Serial.println(localFrame.comFrameReq);
    Serial.print("ReqID: ");
    Serial.println(localFrame.comFrameRegId);
    Serial.print("Data: ");
    Serial.println(localFrame.data);
    Serial.print("CRC: ");
    Serial.println(localFrame.CRC);

*/


}