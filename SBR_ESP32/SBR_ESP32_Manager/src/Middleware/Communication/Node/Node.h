/**
 * @file Node.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief class to Manage the nodes
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */


#ifndef Node_H
#define Node_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/

#include <Arduino.h>

#include "../../../Definition/GlobalDef.h"
#include "../../../Definition/LocalDef.h"

#include "../Request/Request.h"
#include "../RequestBuffer/RequestBuffer.h"

/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the SPI Master
 * 
 */
class Node {
public:  

    /**
     * @brief Construct a new spi mastermanager object
     * 
     */
    Node(HardwareSerial* serial, uint32_t baud, uint8_t RX, uint8_t TX);

    /**
     * @brief Destroy the spi mastermanager object
     * 
     */
    ~Node();

    /**
     * @brief Function add a request
     * 
     * @param nodeId Node ID
     * @param reqType Request Type
     * @param regId Register ID
     * @param data Data Value
     * @return RC_e Result code
     */
    RC_e AddRequest(DEVICE_e nodeId, COM_REQUEST_TYPE_e reqType, COM_REQUEST_REG_ID_e regId, uint32_t data);

    /**
     * @brief Function add a request
     * 
     * @param request Node ID
     * @return RC_e Result code
     */
    RC_e AddRequest(Request request);

    /**
     * @brief Function to send the next request
     * 
     * @return RC_e Result code
     */
    RC_e SendNextRequest();

    /**
     * @brief Function to listen for request
     * 
     * @return RC_e Result code
     */
    RC_e Listen();

    /**
     * @brief Print Buffer of requests
     * 
     * @return RC_e 
     */
    RC_e PrintBuffer();  

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

    HardwareSerial* m_serial;                       /**< \brief SPI master object */
    RequestBuffer* m_requestBuffer = NULL;                     /**< \brief Array of SPI Slaves */

    bool m_debugMode = false;                                   /**< Debug Mode */

    /**
     * @brief Function to configure serial port
     * 
     * @return RC_e Result code
     */
    RC_e ConfigureSerial(uint32_t baud, uint8_t RX, uint8_t TX);

    /**
     * @brief Function to send a request
     * 
     * @param request Request
     * @return RC_e Result code
     */
    RC_e SendRequest(Request request);

    /**
     * @brief Function to read a request
     * 
     * @param request Reference of a request object
     * @return RC_e Result code
     */
    RC_e ReadRequest(Request* request);

    /**
     * @brief Function to read the next request
     * 
     * @return RC_e Result code
     */
    RC_e ReadNextRequest(Request* request);

    RC_e virtual HandleRequest(Request* request) = 0;

    /**
     * @brief Function to print the debug message
     * 
     * @return RC_e Result code
     */
    RC_e Debug(char* msg);

};

#endif // Node_H