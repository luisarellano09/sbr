//======================================================== INCLUDES =========================================================================
#include <Arduino.h>
#include "../lib/SBR_Global/WifiManager/WifiManager.h"
#include "../lib/SBR_Global/Definition/GlobalDef.h"


//======================================================== TEST =================================================================

void test();


//======================================================== GLOBAL VARIABLES =================================================================
// Wifi parameters
char* ssid = "luiss10";
char* password = "12345678";
char* hostName = "SBR_ESP32_Manager";

// Wifi instance
WifiManager *myWifiManager; 

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

//======================================================== CORE LOOPS =======================================================================

// Loop of core 0
void LoopCore0( void * parameter ){
    while(true) {
        // Code for Timer 0 interruption
        if (flagTimer0){
            flagTimer0 = false;
            // Code 
            Serial.println("TIMER 0");
        }

        // Code for Timer 1 interruption
        if (flagTimer1){
            flagTimer1 = false;
            // Code 
            myWifiManager->Run();
            Serial.println("TIMER 1");
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
            // Code 
            Serial.println("TIMER 2");
        }

        // Code for Timer 3 interruption
        if (flagTimer3){
            flagTimer3 = false;
            // Code 
            Serial.println("TIMER 3");
        }
        delay(1);
    }
}

//======================================================== TIMERS ===========================================================================

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

//======================================================== SETUP ==============================================================================

void setup() {

    // Serial Port
    Serial.begin(115200);

    // TEST
    test();

    // Wifi Manager
    myWifiManager = new WifiManager(ssid, password, hostName);

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
    timerAlarmWrite(timer0, 1000000, true); // 1000000 * 1 us = 1 s, autoreload true

    // Timer1
    Serial.println("start timer 1");
    timer1 = timerBegin(1, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer1, &onTimer1, true); // edge (not level) triggered 
    timerAlarmWrite(timer1, 1000000, true); // 1000000 * 1 us = 1 s, autoreload true

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

//======================================================== MAIN LOOP ============================================================================
// Loop not used
void loop() {
    vTaskDelete(NULL);
}

void test(){

    COM_FRAME_u data;

    u8_t U8[8];

    data.comFrameReq = (u8_t)COM_FRAME_REQ_e::WRITE;
    data.comFrameRegId = (u8_t)COM_FRAME_REG_ID_e::TLF_DEVCFG2;
    data.data = (u32_t) 0xBEAFDEAD;
    data.CRC = (u16_t)0xCDEF;

    U8[0] = data.comFrameReq;
    U8[1] = data.comFrameRegId;
 



    Serial.println("==== TEST TRAMA =====");
    Serial.println(U8[0], HEX);
    Serial.println(U8[1], HEX);
    Serial.println(U8[2], HEX);
    Serial.println(U8[3], HEX);
    Serial.println(U8[4], HEX);
    Serial.println(U8[5], HEX);
    Serial.println(U8[6], HEX);
    Serial.println(U8[7], HEX);
    Serial.println("====================");

    Serial.println("==== TEST TRAMA =====");
    Serial.println(data.comFrameReq, HEX);
    Serial.println(data.comFrameRegId, HEX);
    Serial.println(data.data, HEX);
    Serial.println(data.CRC, HEX);
    Serial.println("====================");


}