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
 *  												INCLUDES - ARDUINO
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

/*******************************************************************************************************************************************
 *  												INCLUDES - SBR
 *******************************************************************************************************************************************/
#include "./Manager/Manager.h"

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
#include "../lib/SlaveSPI/SlaveSPI.h"
#include <SPI.h>

#define SO   (gpio_num_t)22     // azul
#define SI   (gpio_num_t)23     // verde
#define SCLK (gpio_num_t)19     // morado
#define SS   (gpio_num_t)18     // plomo

SlaveSPI slave(HSPI_HOST);   // VSPI_HOST

#include "../lib/SlaveSPI/SimpleArray.h"

typedef SimpleArray<uint8_t, int> array_t;

array_t master_msg(SPI_DEFAULT_MAX_BUFFER_SIZE);
array_t slave_msg(SPI_DEFAULT_MAX_BUFFER_SIZE);


void test_setup();
void test_run();
void test_run_read();

#define FRAME_SIZE              (uint8_t)8u                 /*Number of Bytes of the Frame*/
void test_Get_frames();
void test_Get_frame(array_t* buffer);
void test_RX_frame(COM_FRAME_st localFrame);
void test_TX_frame();

u32_t count = 0;

u32_t count_logger = 0;

u32_t test_data = 0;


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
                manager->m_wifiManager->RunOTA();
                delay(1); // To feed the WDT
            // ==========================
        }

        test_Get_frames();
        //test_run();

    }
}

// Loop of core 1
void LoopCore1( void * parameter ){
    while(true) {
        // Code for Timer 2 interruption
        if (flagTimer2){
            flagTimer2 = false;

            // ========== Code ==========
            manager->m_logger->WriteValue(count_logger++);
            // ==========================
        }

        // Code for Timer 3 interruption
        if (flagTimer3){
            flagTimer3 = false;

            // ========== Code ==========

            // ==========================
        }

        manager->m_logger->Run();

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
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); 

    // Serial Port
    Serial.begin(115200);

    // Manager
    manager = new Manager();

    delay(1000);
    // TEST
    test_setup();

    delay(1000);

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
    //manager->m_logger->Write("start timer 0");
    timer0 = timerBegin(0, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer0, &onTimer0, true); // edge (not level) triggered 
    timerAlarmWrite(timer0, 1000000, true); // 1000000 * 1 us = 1 s, autoreload true

    // Timer1
    //manager->m_logger->Write("start timer 1");
    timer1 = timerBegin(1, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer1, &onTimer1, true); // edge (not level) triggered 
    timerAlarmWrite(timer1, 2000000, true); // 1000000 * 1 us = 1 s, autoreload true

    // Timer2
    //manager->m_logger->Write("start timer 2");
    timer2 = timerBegin(2, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer2, &onTimer2, true); // edge (not level) triggered 
    timerAlarmWrite(timer2, 1000000, true); // 1000000 * 1 us = 1 s, autoreload true

    // Timer3
    //manager->m_logger->Write("start timer 3");
    timer3 = timerBegin(3, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer3, &onTimer3, true); // edge (not level) triggered 
    timerAlarmWrite(timer3, 1000000, true); // 1000000 * 1 us = 1 s, autoreload true

    // Enable the timer alarms
    timerAlarmEnable(timer0); // enable
    timerAlarmEnable(timer1); // enable
    timerAlarmEnable(timer2); // enable
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
    slave.begin(SO, SI, SCLK, SS, 8);
}

void test_run(){
    //manager->m_logger->Write("Putos todos!!");
    if (slave.getInputStream()->length() >= 128 && digitalRead(SS) == HIGH) {  // Slave SPI has got data in.
        while (slave.getInputStream()->length()) {
            slave.readToArray(slave_msg);  // Not the sample read() as Serial
        }

        // int a = slave_msg[0] + slave_msg[1] + slave_msg[2] + slave_msg[3] + slave_msg[4] + slave_msg[5] + slave_msg[6] + slave_msg[7] + slave_msg[8] + slave_msg[9];
        // Serial.println(a);  
       
        Serial.println("================================");
        for (int i = 0; i < slave_msg.length(); i++) {
            Serial.println(slave_msg[i]);            
        }


        slave_msg.clear();
        slave.flushInputStream();

        //test_run_read();  
    }
}


void test_run_read(){

    // test
    master_msg.clear();
    master_msg.append(10);
    master_msg.append(20);
    master_msg.append(30);
    master_msg.append(40);
    master_msg.append(50);
    master_msg.append(60);
    master_msg.append(70);
    master_msg.append(80);

    slave.flushOutputStream();


    slave.writeFromArray(master_msg);
    Serial.println("********* TO SEND *******");
    for (int i = 0; i < master_msg.length(); i++) {
        Serial.println(master_msg[i]);            
    }


}


void test_Get_frames(){

    // Get length of the buffer stream
    int length = slave.getInputStream()->length();

    if (length >= 32 && digitalRead(SS) == HIGH) {  // Slave SPI has got data in.

        array_t _buffer(length);

        while (slave.getInputStream()->length()) {
            slave.readToArray(_buffer);
        }

        // Flush the input buffer
        slave.flushInputStream();
        
        for(int i=0; i<length/FRAME_SIZE; i++){
            // Create Buffer for one frame
            array_t _bufferOneFrame(FRAME_SIZE);

            // Calculate offset
            auto _offset = FRAME_SIZE*i;

            // Assign buffer bytes
            _bufferOneFrame.append(_buffer[_offset + 0]);
            _bufferOneFrame.append(_buffer[_offset + 1]);
            _bufferOneFrame.append(_buffer[_offset + 2]);
            _bufferOneFrame.append(_buffer[_offset + 3]);
            _bufferOneFrame.append(_buffer[_offset + 4]);
            _bufferOneFrame.append(_buffer[_offset + 5]);
            _bufferOneFrame.append(_buffer[_offset + 6]);
            _bufferOneFrame.append(_buffer[_offset + 7]);

            // Get frame
            test_Get_frame(&_bufferOneFrame);
        }
        

    }
}


void test_Get_frame(array_t* buffer){

    // Local Frame
    COM_FRAME_st localFrame;

    // REQUEST
    localFrame.comFrameReq = (*buffer)[0];

    // ID
    localFrame.comFrameRegId = (*buffer)[1];

    // DATA
    localFrame.data = ((*buffer)[2]);
    localFrame.data += ((*buffer)[3])<<8;
    localFrame.data += ((*buffer)[4])<<16;
    localFrame.data += ((*buffer)[5])<<24;

    // CRC
    localFrame.CRC = (*buffer)[6];
    localFrame.CRC += ((*buffer)[7])<<8;

    // Read Write Selector
    if(localFrame.comFrameReq == COM_FRAME_REQ_e::WRITE){
        test_RX_frame(localFrame);
    } else if(localFrame.comFrameReq == COM_FRAME_REQ_e::READ){
        test_TX_frame();
    }
}


void test_RX_frame(COM_FRAME_st localFrame){
    // Serial.println("======== RX =========");
    // Serial.print("Req: ");
    // Serial.println(localFrame.comFrameReq);
    // Serial.print("ReqID: ");
    // Serial.println(localFrame.comFrameRegId);
    // Serial.print("Data: ");
    // Serial.println(localFrame.data);
    // Serial.print("CRC: ");
    // Serial.println(localFrame.CRC);

    if (test_data != localFrame.data){
        Serial.print("Error: ");
        Serial.print(test_data);
        Serial.print(" != ");
        Serial.println(localFrame.data);
        test_data = localFrame.data;
    }

    test_data++;

    if (test_data > 10000) test_data = 0;

    

    

}

void test_TX_frame(){

    COM_FRAME_st localFrame;

    count++;
    localFrame.comFrameReq = COM_FRAME_REQ_e::WRITE;
    localFrame.comFrameRegId = COM_FRAME_REG_ID_e::TLF_IF;
    localFrame.data = count;
    localFrame.CRC = 169;

    array_t buffer(FRAME_SIZE);

    buffer.append(localFrame.comFrameReq);
    buffer.append(localFrame.comFrameRegId);
    buffer.append((byte)localFrame.data);
    buffer.append((byte)(localFrame.data>>8));
    buffer.append((byte)(localFrame.data>>16));
    buffer.append((byte)(localFrame.data>>24));
    buffer.append((byte)localFrame.CRC);
    buffer.append((byte)(localFrame.CRC>>8));

    slave.flushOutputStream();
    slave.writeFromArray(buffer);

    Serial.println("======== TX =========");
    Serial.print("Req: ");
    Serial.println(localFrame.comFrameReq);
    Serial.print("ReqID: ");
    Serial.println(localFrame.comFrameRegId);
    Serial.print("Data: ");
    Serial.println(localFrame.data);
    Serial.print("CRC: ");
    Serial.println(localFrame.CRC);

}


