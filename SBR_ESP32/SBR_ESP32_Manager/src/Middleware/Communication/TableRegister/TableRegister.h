/**
 * @file TableRegister.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to describe the Data Table in Runtime
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */

#ifndef TableRegister_H
#define TableRegister_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/

#include "../../../Definition/GlobalDef.h"
#include "../../../Definition/LocalDef.h"
#include "../Request/Request.h"

#include "../Register/Register.h"
#include "../Node/Node.h"


/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to describe the Data Table in Runtime
 * 
 */
class TableRegister {
public:  

    Register m_registers[COM_REQUEST_REG_ID_e::LENGTH_REG_ID];   /**< \brief Array of registers*/
    
    /**
     * @brief Construct a new Table RT object
     * 
     */
    TableRegister(Node* NodeESP32, Node* NodeLinux);

    /**
     * @brief Destroy the Table RT object
     * 
     */
    ~TableRegister();

    /**
     * @brief Add subscriber to a register
     * 
     * @param regId Register ID
     * @param subscriber Subscriber device
     * @return RC_e Result code
     */
    RC_e AddSubscriber(COM_REQUEST_REG_ID_e regId, DEVICE_e subscriber);  

    /**
     * @brief Update Register
     * 
     * @param regId Register ID
     * @param data Data Value
     * @return RC_e Result code
     */
    RC_e UpdateRegister(COM_REQUEST_REG_ID_e regId, int32_t data);

    /**
     * @brief Function to handle a read slave request
     * 
     * @param request Reference of a request object
     * @return RC_e Result code
     */
    RC_e HandleRequest(Request* request);

    /**
     * @brief Print
     * @param regId Register ID
     * 
     * @return RC_e Result code
     */
    RC_e Print(COM_REQUEST_REG_ID_e regId);

    /**
     * @brief Print
     * 
     * @return RC_e Result code
     */
    RC_e PrintTable();

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

    Node* m_NodeESP32 = NULL;
    Node* m_NodeLinux = NULL;

    bool m_debugMode = false;           /**< Debug Mode */

    /**
     * @brief Clean registers
     * 
     * @return RC_e Result code
     */
    RC_e CleanRegisters();

    /**
     * @brief Function to add a request to the subscribed slaves
     * 
     * @param regId Register ID
     * @param data Data Value
     * @return RC_e Result code
     */
    RC_e AddRequestToSubscribers(COM_REQUEST_REG_ID_e regId, int32_t data);

    /**
     * @brief Function to print the debug message
     * 
     * @return RC_e Result code
     */
    RC_e Debug(char* msg);

};

#endif // TableRegister_H