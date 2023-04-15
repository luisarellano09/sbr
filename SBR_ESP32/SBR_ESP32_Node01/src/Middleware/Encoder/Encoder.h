/**
 * @file Encoder.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Encoder class
 * 
 */

#ifndef ENCODER_H
#define ENCODER_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include "ESP32Encoder.h"
#include "../../Definition/Global/RC.h"


/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Encoder class
 * 
 */
class Encoder {
public:  

    /**
     * @brief Construct a new Encoder object
     * 
     * @param channel Encoder channel
     * @param channelAPin Pin of encoder channel A
     * @param channelBPin Pin of encoder channel B
     * @param direction Encoder direction 0=Normal, 1=Invert 
     */
    Encoder(uint8_t channel, uint8_t channelAPin, uint8_t channelBPin, bool direction = 0);

    /**
     * @brief Destructor
     * 
     */
    ~Encoder();

    /**
     * @brief Get the Count
     * 
     * @return int64_t Current count
     */
    int64_t GetCount();

    /**
     * @brief Set the Count
     * 
     * @param count Encoder count
     * @return RC_e Result Code
     */
    RC_e SetCount(int64_t count);

    /**
     * @brief Invert Direction
     * 
     * @return RC_e Result code
     */
    RC_e InvertDirection();

    /**
     * @brief Get the Direction
     * 
     * @return true Direction inverted
     * @return false Direction normal
     */
    bool GetDirection();

    /**
     * @brief Function to print the encoder info
     * 
     * @return RC_e Result code
     */
    RC_e Print();  


private:

    ESP32Encoder* m_ESP32Encoder = NULL;    /**@brief ESP32 Encoder object */
    uint8_t m_channel;                      /**@brief Encoder Channel */
    uint8_t m_channelAPin;                  /**@brief Pin of channel A */
    uint8_t m_channelBPin;                  /**@brief Pin of channel B */
    bool m_direction;                       /**@brief Encoder direction 0=Normal, 1=Invert  */

};

#endif // ENCODER_H