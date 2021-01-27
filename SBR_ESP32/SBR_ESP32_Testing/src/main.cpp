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
/*******************************************************************************************************************************************
 *  												INCLUDES - SBR
 *******************************************************************************************************************************************/
#include "./Manager/Manager.h"
#include "./ControlMotors/MotorManager.h"
// This optional setting causes Encoder to use more optimized code,
// It must be defined before Encoder.h is included.
#include "./ENCODER/ESP32Encoder.h"

#include "./BNO080/BNO080.h"



/*******************************************************************************************************************************************
 *  												GLOBAL VARIABLES
 *******************************************************************************************************************************************/

#define SIZE_FILTER 6

// Manager Instance
Manager* manager;
//PID instance
//PID *myPID;
//IMU instance
BNO080 *myIMU;
MotorManager *myMotors;

ESP32Encoder encoderRight;
ESP32Encoder encoderLeft;


unsigned long encoder2lastToggled;
bool encoder2Paused = false;

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

extern float AccX_Mesured;
float AccX_Filtered = 0;
float buffer[SIZE_FILTER];
float PIDResult = 5.0f;
float Consigne = 0.0f;
float myKp = 0.0f;
float myKi = 0.0f;
float myKd = 0.0f;
float TestValue = 0.0f;
char Pressed = '0';
/*******************************************************************************************************************************************
 *  												TEST
 *******************************************************************************************************************************************/
void test_Add_Requests();
uint32_t test_counter = 0;
int8_t i8DutyCycle = 50;

double inputPID = 0;
double outputPID = 0;
double SetpointPID = 0;
double Kp = 1;
double Ki = 1;
double Kd = 1;
int POn = 1;
int ControllerDirectionPID = 1;

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

            /*if((Pitch_Mesured < 0.03)&&(Pitch_Mesured > -0.03))
            {
                Pitch_Mesured = 0;
            }*/
            //if(myPID->Compute()){

                /*if(outputPID>100){
                    outputPID =100;
                }
                else if(outputPID <-100)
                {
                    outputPID = -100;
                }*/
                
                //myMotors->PWM1(PIDResult);
                //myMotors->PWM2(PIDResult);
                
                //Serial.println(outputPID);
            //}
            //else{
                //Serial.println("ERROR PID");
            //}

        }

        // Code for Timer 1 interruption
        if (flagTimer1){
            flagTimer1 = false;
        }

        /****************************************************/
        /*      Manager TASK IMU*/
        /****************************************************/
        if(RC_e::SUCCESS == myIMU->Run()){
            inputPID = myIMU->m_Pitch;
            Serial.print(F("Roll="));
        	Serial.print(myIMU->m_Roll, 2);
            Serial.print(F("\tPitch="));
            Serial.print(myIMU->m_Pitch, 2);
            Serial.print(F("\t"));
            Serial.print(F("Yaw="));
            Serial.print(myIMU->m_Yaw, 2);
            Serial.print(F("\tabsYaw="));
            Serial.print(myIMU->m_absYaw, 2);
            Serial.print(F("\tabsYawCalib="));
            Serial.print(myIMU->m_absYawCalib, 2);
            Serial.print(F("\tyawcalib="));
            Serial.print(myIMU->m_calibYaw, 2);            
            Serial.println("\n");
        } else {
            Serial.println("IMU not connected!!!");
        }

        Serial.println("Encoder count = "+String((int32_t)encoderLeft.getCount())+" "+String((int32_t)encoderRight.getCount()));
        delay(10);
                
        
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
                    myIMU->calibrationAngles();
                    break;
                case 'p':
                case 'P':

                    break;
                case 'r':
                case 'R':
 
                    
                    break;
                case '1':
                    Pressed = '1';
                break;   
                case '2':
                    Pressed = '2';
                break;     
                case '3':
                    Pressed = '3';
                break;      
                case '4':
                    Pressed = '4';
                break;         
                case '+':
                    switch (Pressed)

                    {
                    case '1':
                        /* code */
                        //myPID->GetConsigne(&TestValue);
                        TestValue +=0.1f;
                        //myPID->SetConsigne(TestValue);
                        Serial.printf("consinge: %f\n",TestValue);
                        break;
                    case '2':
                        /* code */
                        //myPID->GetKp(&TestValue);
                        TestValue +=1.0f;
                        //myPID->SetKp(TestValue);
                        Serial.printf("Kp: %f\n",TestValue);;
                        break;
                    case '3':
                        /* code */
                        //myPID->GetKi(&TestValue);
                        TestValue +=1.0f;
                        //myPID->SetKi(TestValue);
                        Serial.printf("ki: %f\n",TestValue);;
                        break;
                    case '4':
                        /* code */
                        //myPID->GetKd(&TestValue);
                        TestValue +=1.0f;
                        //myPID->SetKd(TestValue);
                        Serial.printf("kd: %f\n",TestValue);;
                        break;
                    }
                break;  
                case '-':
                    switch (Pressed)

                    {
                    case '1':
                        /* code */
                        //myPID->GetConsigne(&TestValue);
                        TestValue -=0.1f;
                        //myPID->SetConsigne(TestValue);
                        Serial.printf("consinge: %f\n",TestValue);;
                        break;
                    case '2':
                        /* code */
                        //myPID->GetKp(&TestValue);
                        TestValue -=1.0f;
                        //myPID->SetKp(TestValue);
                        Serial.printf("kp: %f\n",TestValue);
                        break;
                    case '3':
                        /* code */
                        //myPID->GetKi(&TestValue);
                        TestValue -=1.0f;
                        //myPID->SetKi(TestValue);
                        Serial.printf("ki: %f\n",TestValue);
                        break;
                    case '4':
                        /* code */
                        //myPID->GetKd(&TestValue);
                        TestValue -=1.0f;
                        //myPID->SetKd(TestValue);
                        Serial.printf("kd: %f\n",TestValue);
                        break;
                    }
                break; 
            }
        }

        // Run OTA service
        //manager->m_wifiManager->RunOTA();

        // Delay to feed WDT
        delay(10);
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
    Serial.println(" +++++ ESP32 TESTING +++++");


    /*****************************************************************************************/
    /* Manager INIT IMU*/
    myIMU = new BNO080();
    myIMU->configure(32, 18, 26, 27, 3000000, 14, 25, 13,18,12);
    myIMU->enableRotationVector(5);
    /*****************************************************************************************/
    myMotors = new MotorManager();

    myMotors->Begin(5,2,4,15);
    i8DutyCycle = 0;
    

    /************************************************************************************************/
    /* Manager INIT PID*/
    //myPID = new PID(&inputPID, &outputPID, &SetpointPID, Kp, Ki, Kd, POn, ControllerDirectionPID);
    //turn the PID on
    //myPID->SetMode(AUTOMATIC);
    //myPID->SetOutputLimits(-100,+100);
    /*************************************************************************************************/

    ESP32Encoder::useInternalWeakPullResistors = UP;
    
/* rotary encoder */
/*#define PINENC1A 34 
#define PINENC1B 35

#define PINENC2A 22 
#define PINENC2B 23*/
    encoderLeft.attachFullQuad(34,35);
    encoderRight.attachSingleEdge(22,23);
    
    encoderRight.setCount(0);
    encoderLeft.clearCount();
    //Serial.println("Encodr Start ="+String((int32_t)encoderRight.getCount()));
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
    timerAlarmWrite(timer0, 80000, true); // 1000000 * 1 us = 1 s, autoreload true

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
    timerAlarmEnable(timer0); // enable
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


