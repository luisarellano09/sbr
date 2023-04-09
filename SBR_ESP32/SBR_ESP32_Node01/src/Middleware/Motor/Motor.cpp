/**
 * @file Motor.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to control a motor
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "Motor.h"
#include <ArduinoLog.h>


/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

Motor::Motor(PWMChannel_e pwmChannel, uint8_t pwmPin, double frequency, uint8_t resolution, double offset, uint8_t dirPin, MotorDirection_e direction){
    this->m_pwmChannel = pwmChannel;
    this->m_pwmPin = pwmPin;
    this->m_frequency = frequency;
    this->m_resolution = resolution;
    this->m_offset = offset,
    this->m_dirPin = dirPin;
    this->m_direction = direction;

    // Init Motor
    this->Init();
}


//=====================================================================================================

Motor::~Motor(){
}


/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e Motor::SetSpeed(double speed){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    if(speed == 0.0){
        this->Stop();
    } else{
        if(speed > 100.0 || speed < -100.0){
            Log.warningln("[Motor::SetSpeed] Motor[%d] speed out of range: %D%", this->m_pwmChannel, speed);
        }
        
        double tempModSpeed = this->m_offset + abs(speed) * (100.0 - this->m_offset) / 100.0;
        uint32_t duty = (abs(tempModSpeed) * pow(2,this->m_resolution)) / 100.0;

        ledcWrite(this->m_pwmChannel,duty);

        this->m_speed = speed;
        
        if (m_direction == MotorDirection_e::MOTOR_DIRECTION_INVERTED){
            speed *= -1.0;
        }

        if(speed > 0.0){
            digitalWrite(this->m_dirPin, HIGH); 
        }
        else{
            digitalWrite(this->m_dirPin, LOW); 
        }
    }

    Log.traceln("[Motor::SetSpeed] Motor[%d] speed setted to %D%", this->m_pwmChannel, speed);

    return retCode;
}


//=====================================================================================================

double Motor::GetSpeed(){
    return this->m_speed;
}


//=====================================================================================================

RC_e Motor::Stop(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    digitalWrite(this->m_dirPin, LOW); 
    ledcWrite(this->m_pwmChannel,0);

    return retCode;
}


//=====================================================================================================

RC_e Motor::Print(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    Serial.println("*****************");
    Serial.printf("Motor[%d] Info:\r\n", this->m_pwmChannel);
    Serial.printf(" - PWM Channel: %d\r\n", this->m_pwmChannel);
    Serial.printf(" - PWM GPIO Pin: %d\r\n", this->m_pwmPin);
    Serial.printf(" - PWM Frequency: %.1f\r\n", this->m_frequency);
    Serial.printf(" - PWM Resolution: %d\r\n", this->m_resolution);
    Serial.printf(" - Speed Offset: %d\r\n", this->m_offset);
    Serial.printf(" - Direction GPIO Pin: %d\r\n", this->m_dirPin);
    Serial.printf(" - Direction (Inverted) : %d\r\n", this->m_direction);
    Serial.println("*****************");
    
    return retCode;
}


/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

RC_e Motor::Init(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    ledcSetup(this->m_pwmChannel,this->m_frequency,this->m_resolution);

    pinMode(this->m_dirPin, OUTPUT);     
    digitalWrite(this->m_dirPin, LOW);
    
    ledcAttachPin(this->m_pwmPin,this->m_pwmChannel);
    
    this->Stop();
    
    return retCode;
}