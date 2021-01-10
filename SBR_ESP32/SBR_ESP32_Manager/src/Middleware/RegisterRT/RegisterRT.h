/**
 * @file RegisterRT.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to describe a register of the Data Table in Runtime
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */

#ifndef REGISTERRT_H
#define REGISTERRT_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/

#include "../../lib/Definition/GlobalDef.h"
#include "../../Definition/LocalDef.h"


/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to describe the Data Table in Runtime
 * 
 */
class RegisterRT {
public:  

    uint32_t m_value;               /**< \brief Register value*/
    Devices_e m_subscribers[Devices_e::DEVICE_LENGTH] = {Devices_e::DEVICE_NONE};   /**< \brief Subscribers array*/
    int8_t m_subscribers_index;     /**< \brief Subscribers index*/

    /**
     * @brief Construct a new Register RT object
     * 
     */
    RegisterRT();

    /**
     * @brief Destroy the Register R T object
     * 
     */
    ~RegisterRT();

    /**
     * @brief Add subscriber to a register
     * 
     * @param subscriber Subscriber device
     * @return RC_e Result code
     */
    RC_e AddSubscriber(Devices_e subscriber);  

    /**
     * @brief Clean Subscribers
     * 
     * @return RC_e Result code
     */
    RC_e CleanSubscribers();  

    /**
     * @brief Enable the debug mode of the class
     * 
     * @return RC_e Result code
     */
    RC_e EnableDebugMode();

    /**
     * @brief Disable the debug mode of the class
     * 
     * @return RC_e Result code
     */
    RC_e DisableDebugMode();
   
private:

    bool m_debugMode = false;           /**< Debug Mode */

    /**
     * @brief Function to print the debug message
     * 
     * @return RC_e Result code
     */
    RC_e Debug(char* msg);

};

#endif // REGISTERRT_H