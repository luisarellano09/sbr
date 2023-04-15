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

Encoder::Encoder(uint8_t channel, uint8_t channelAPin, uint8_t channelBPin, bool direction){
    this->m_ESP32Encoder = new ESP32Encoder();
    this->m_channel = channel;
    this->m_channelAPin = channelAPin;
    this->m_channelBPin = channelBPin;
    this->m_direction = direction;
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
    if (this->m_direction == 0){
        return this->m_ESP32Encoder->getCount();
    } else {
        return (-1 * this->m_ESP32Encoder->getCount());
    }
}


//=====================================================================================================

RC_e Encoder::SetCount(int64_t count){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    if (this->m_direction == 0){
        this->m_ESP32Encoder->setCount(count);
    } else {
        this->m_ESP32Encoder->setCount((-1 * count));
    }

    Log.traceln("[Encoder::SetCount] Encoder[%d] count setted to %d%", this->m_channel, count);

    return retCode;
}


//=====================================================================================================

RC_e Encoder::InvertDirection(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_direction = true;
    Log.traceln("[Encoder::InvertDirection] Encoder[%d] Direction inverted", this->m_channel);

    return retCode;
}


//=====================================================================================================

bool Encoder::GetDirection(){
    return this->m_direction;
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
    Serial.printf(" - Direction (Inverted) : %d\r\n", this->m_direction);
    Serial.println("*****************");
    
    return retCode;
}