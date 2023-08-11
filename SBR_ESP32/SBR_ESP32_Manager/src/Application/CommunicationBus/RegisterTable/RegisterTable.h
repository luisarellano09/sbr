/**
 * @file RegisterTable.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to manage a Table of registers
 * 
 */

#ifndef REGISTERTABLE_H
#define REGISTERTABLE_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "../../../Definition/Global/RC.h"
#include "../../../Middleware/CommunicationBus/Register/Register.h"
#include "../../../Middleware/CommunicationBus/Node/Node.h"


/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to manage a Table of registers
 * 
 */
class RegisterTable {
public:  
    
    Register m_registers[COM_REQUEST_REG_ID_e::LENGTH_REG_ID];      /**@brief Array of registers*/

    /**
     * @brief Construct a new Register Table object
     * 
     * @param NodeESP32 NodeESP32 reference
     * @param NodeLinux NodeLinux reference
     */
    RegisterTable(Node* NodeESP32, Node* NodeLinux);

    /**
     * @brief Destructor
     * 
     */
    ~RegisterTable();

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


private:

    Node* m_NodeESP32 = NULL;           /**@brief Esp32 node*/
    Node* m_NodeLinux = NULL;           /**@brief Linux node*/

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

};

#endif // REGISTERTABLE_H