/**
 * @file Register.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to describe a register
 * 
 */

#ifndef REGISTER_H
#define REGISTER_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include "../../../Definition/Global/RC.h"
#include "../../../Definition/Global/Devices.h"
#include "../../../Definition/Global/RegisterTableDef.h"


/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to describe a register
 * 
 */
class Register {
public:  

    uint32_t m_value;                                   /**@brief Register value*/
    DEVICE_e m_subscribers[DEVICE_e::LENGTH_DEVICE];    /**@brief Subscribers array*/
    int8_t m_subscribers_index;                         /**@brief Subscribers index*/

    /**
     * @brief Constructor
     * 
     */
    Register();

    /**
     * @brief Destructor
     * 
     */
    ~Register();

    /**
     * @brief Function to add subscriber to a register
     * 
     * @param subscriber Subscriber device
     * @return RC_e Result code
     */
    RC_e AddSubscriber(DEVICE_e subscriber);  

    /**
     * @brief Function to clean register
     * 
     * @return RC_e Result code
     */
    RC_e Clean();  

    /**
     * @brief Function to print the register
     * 
     * @param regId Register ID
     * @return RC_e Result code
     */
    RC_e Print(COM_REQUEST_REG_ID_e regId = COM_REQUEST_REG_ID_e::NONE_REG_ID);

};

#endif // REGISTER_H