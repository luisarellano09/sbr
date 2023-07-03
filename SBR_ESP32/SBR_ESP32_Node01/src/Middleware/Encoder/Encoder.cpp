/**
 * @file Encoder.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Encoder class
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "Encoder.h"
#include <ArduinoLog.h>


/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

Encoder::Encoder(uint8_t channel, uint8_t channelAPin, uint8_t channelBPin, bool invertDirection){
    this->m_ESP32Encoder = new ESP32Encoder();
    this->m_channel = channel;
    this->m_channelAPin = channelAPin;
    this->m_channelBPin = channelBPin;
    this->m_invertDirection = invertDirection;
    this->m_ESP32Encoder->attachHalfQuad(channelAPin, channelBPin);
    this->SetCount(0);
}


//=====================================================================================================

Encoder::~Encoder(){
}


/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

int64_t Encoder::GetCount(){
    if (this->m_invertDirection == 0){
        return this->m_ESP32Encoder->getCount();
    } else {
        return (-1 * this->m_ESP32Encoder->getCount());
    }
}


//=====================================================================================================

RC_e Encoder::SetCount(int64_t count){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    if (this->m_invertDirection == 0){
        this->m_ESP32Encoder->setCount(count);
    } else {
        this->m_ESP32Encoder->setCount((-1 * count));
    }

    Log.traceln("[Encoder::SetCount] Encoder[%d] count setted to %d%", this->m_channel, count);

    return retCode;
}


//=====================================================================================================

RC_e Encoder::SetDirection(bool direction){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_invertDirection = direction;
    Log.traceln("[Encoder::SetDirection] Encoder[%d] Direction: %T", this->m_channel, this->m_invertDirection);

    return retCode;
}


//=====================================================================================================

bool Encoder::GetDirection(){
    return this->m_invertDirection;
}


//=====================================================================================================

RC_e Encoder::Print(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    Serial.println("*****************");
    Serial.printf("Encoder[%d] Info:\r\n", this->m_channel);
    Serial.printf(" - Encoder Channel: %d\r\n", this->m_channel);
    Serial.printf(" - Channel A Pin: %d\r\n", this->m_channelAPin);
    Serial.printf(" - Channel B Pin: %d\r\n", this->m_channelBPin);
    Serial.printf(" - Direction (Inverted) : %d\r\n", this->m_invertDirection);
    Serial.println("*****************");
    
    return retCode;
}