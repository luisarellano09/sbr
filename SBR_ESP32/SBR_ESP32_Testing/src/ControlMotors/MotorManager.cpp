/**
 * @file IMUManager.cpp
 * @author Jorge SALGADO (jorgesalgado23@gmail.com)
 * @brief Class to Manage the Engine, communication with PWM 
 * @version 1.0
 * @date 11-11-2020
 * 
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include "MotorManager.h"

/*******************************************************************************************************************************************
 *  												Constructor
 *******************************************************************************************************************************************/

//=====================================================================================================
MotorManager::MotorManager(){

}

//=====================================================================================================
MotorManager::~MotorManager(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/
/*
Function to configure the Pin of ESP32
Configuration Pin Direction 1 with PWM1
Configuration Pin DIrection 2 with PWM2
*/
RC_e MotorManager::Begin(uint8_t u8DIR1, uint8_t u8DIR2, uint8_t u8PIN_PWM1,uint8_t u8PIN_PWM2){

RC_e retCode = RC_e::ERROR;
    /*Be careful to connect to PINS for other purpose*/
    if((u8PIN_PWM1 != 6)&&(u8PIN_PWM1!=7)){
        this->u8PinDir1 =u8DIR1;
        this->u8PinDir2 =u8DIR2;

        /*Configure Pins Direction of PWM*/
        pinMode(this->u8PinDir1, OUTPUT);   
        pinMode(this->u8PinDir2, OUTPUT);   
        digitalWrite(this->u8PinDir1, HIGH);    
        digitalWrite(this->u8PinDir2, HIGH); 
        
        /*sets the pins as outputs:*/
        ledcAttachPin(u8PIN_PWM1,PWM_CHANNEL_0);
        ledcSetup(PWM_CHANNEL_0,F32PWM_FREQUENCY,U8PWM_RESOLUTION);
        ledcWrite(PWM_CHANNEL_0,0);

        // sets the pins as outputs:
        ledcAttachPin(u8PIN_PWM2,PWM_CHANNEL_1);
        ledcSetup(PWM_CHANNEL_1,F32PWM_FREQUENCY,U8PWM_RESOLUTION);
        ledcWrite(PWM_CHANNEL_1,0);

        retCode = RC_e::SUCCESS;
    }
    else{
        /*Nothing to DO*/
    }
    return retCode;
}

/*
Function to Control the Duty Cycle of the PWM1
@Parameter i8DutyCyle 
range [-100  to 100] values
*/
RC_e MotorManager::PWM1(int8_t i8DutyCyle){
    uint32_t u32freq;
    RC_e retCode = RC_e::ERROR;

    if(i8DutyCyle>=-100 && i8DutyCyle<=100)
    {
        u32freq = (abs(i8DutyCyle)*255)/100;
        //Serial.println(u32freq);
        /*change Duty Cycle*/
        if(i8DutyCyle > 0){

            digitalWrite(this->u8PinDir1, LOW); 
            ledcWrite(PWM_CHANNEL_0,u32freq);
        }
        else
        {
            digitalWrite(this->u8PinDir1, HIGH); 
            ledcWrite(PWM_CHANNEL_0,u32freq);
        }
        retCode = RC_e::SUCCESS;
    }
    else{

    }
    return retCode;
    
}

/*
Function to Control the Duty Cycle of the PWM2
@Parameter i8DutyCyle 
range [-100  to 100] values
*/
RC_e MotorManager::PWM2(int8_t i8DutyCyle){
    uint32_t u32freq;
    RC_e retCode = RC_e::ERROR;

    if(i8DutyCyle>=-100 && i8DutyCyle<=100)
    {
        u32freq = (abs(i8DutyCyle)*255)/100;
        /*change Duty Cycle*/
        if(i8DutyCyle > 0){
            digitalWrite(this->u8PinDir2, HIGH); 
            ledcWrite(PWM_CHANNEL_1,u32freq);
        }
        else
        {
            digitalWrite(this->u8PinDir2, LOW); 
            ledcWrite(PWM_CHANNEL_1,u32freq);
        }
    }
    else{

    }
    return retCode;
}

/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/





