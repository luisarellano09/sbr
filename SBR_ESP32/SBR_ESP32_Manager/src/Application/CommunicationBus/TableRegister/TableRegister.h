/**
 * @file TableRegister.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to manage a Table of registers
 * @version 1.0
 * @date 16.10.2022
 * 
 */

#ifndef TableRegister_H
#define TableRegister_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/

#include "../../../Definition/GlobalDef.h"
#include "../../../Definition/LocalDef.h"

#include "../../../Middleware/CommunicationBus/Register/Register.h"
#include "../../../Middleware/CommunicationBus/Node/Node.h"

/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to manage a Table of registers
 * 
 */
class TableRegister {
public:  
    
    Register m_registers[COM_REQUEST_REG_ID_e::LENGTH_REG_ID];      /**< \brief Array of registers*/

    /**
     * @brief Constructor
     * 
     */
    TableRegister(Node* NodeESP32, Node* NodeLinux);

    /**
     * @brief Destructor
     * 
     */
    ~TableRegister();

    /**
     * @brief Function to add subscriber to a register
     * 
     * @param regId Register ID
     * @param subscriber Subscriber device
     * @return RC_e Result code
     */
    RC_e AddSubscriber(COM_REQUEST_REG_ID_e regId, DEVICE_e subscriber);  

    /**
     * @brief Function to update Register
     * 
     * @param regId Register ID
     * @param data Data Value
     * @return RC_e Result code
     */
    RC_e UpdateRegister(COM_REQUEST_REG_ID_e regId, int32_t data);

    /**
     * @brief Function to handle a request
     * 
     * @param request Reference of a request object
     * @return RC_e Result code
     */
    RC_e HandleRequest(Request* request);

    /**
     * @brief Function to print Register
     * 
     * @param regId Register ID
     * 
     * @return RC_e Result code
     */
    RC_e PrintRegister(COM_REQUEST_REG_ID_e regId);

    /**
     * @brief Function to print the table
     * 
     * @return RC_e Result code
     */
    RC_e PrintTable();

    /**
     * @brief Function to enable the debug mode of the class
     * 
     * @return RC_e Result code
     */
    RC_e EnableDebugMode();

    /**
     * @brief Function to disable the debug mode of the class
     * 
     * @return RC_e Result code
     */
    RC_e DisableDebugMode();

private:

    Node* m_NodeESP32 = NULL;                                       /**< \brief Esp32 node*/
    Node* m_NodeLinux = NULL;                                       /**< \brief Linux node*/

    bool m_debugMode = false;                                       /**< \brief Debug Mode */

    /**
     * @brief Function to clean registers
     * 
     * @return RC_e Result code
     */
    RC_e CleanRegisters();

    /**
     * @brief Function to add a request to the subscribed slaves
     * 
     * @param regId Register ID
     * @param data Data Value
     * 
     * @return RC_e Result code
     */
    RC_e AddRequestToSubscribers(COM_REQUEST_REG_ID_e regId, int32_t data);

    /**
     * @brief Function to print the debug message
     * 
     * @param msg Message
     * 
     * @return RC_e Result code
     */
    RC_e Debug(char* msg);

};

#endif // TableRegister_H