/**
 * @file Register.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to describe a register
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */

#ifndef Register_H
#define Register_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/

#include "../../../Definition/GlobalDef.h"
#include "../../../Definition/LocalDef.h"

/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to describe the Data Table in Runtime
 * 
 */
class Register {
public:  

    uint32_t m_value;                                   /**< \brief Register value*/
    DEVICE_e m_subscribers[DEVICE_e::LENGTH_DEVICE];    /**< \brief Subscribers array*/
    int8_t m_subscribers_index;                         /**< \brief Subscribers index*/

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
     * @brief Add subscriber to a register
     * 
     * @param subscriber Subscriber device
     * @return RC_e Result code
     */
    RC_e AddSubscriber(DEVICE_e subscriber);  

    /**
     * @brief Clean register
     * 
     * @return RC_e Result code
     */
    RC_e Clean();  

    /**
     * @brief Print
     * 
     * @param regId Register ID
     * @return RC_e Result code
     */
    RC_e Print(COM_REQUEST_REG_ID_e regId = COM_REQUEST_REG_ID_e::NONE_REG_ID);

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

    bool m_debugMode = false;           /**< \brief Debug Mode */

    /**
     * @brief Function to print the debug message
     * 
     * @param msg Message
     * @return RC_e Result code
     */
    RC_e Debug(char* msg);

};

#endif // Register_H