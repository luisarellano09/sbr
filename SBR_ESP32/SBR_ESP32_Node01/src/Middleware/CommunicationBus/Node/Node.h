/**
 * @file Node.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to manage the communication node
 * @version 1.0
 * @date 10.09.2022
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

#include "../RequestBuffer/RequestBuffer.h"

/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to manage the communication node
 * 
 */
class Node {
public:  

    bool m_start = false;                           /**@brief Start command*/
    
    /**
     * @brief Constructor
     * 
     * @param serial Pointer of serialport
     * @param baud Baud rate speed
     * @param RX RX GPIO
     * @param TX TX GPIO
     */
    Node(HardwareSerial* serial, uint32_t baud, uint8_t RX, uint8_t TX);

    /**
     * @brief Destructor
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
     * @brief Function to add request to the buffer
     * 
     * @param request Pointer of request
     * @return RC_e Result code
     */
    RC_e AddRequest(Request* request);  

    /**
     * @brief Function to send the next request
     * 
     * @return RC_e Result code
     */
    RC_e SendNextRequest();

    /**
     * @brief Function to read the next request
     * 
     * @param request Reference of a request object
     * @return RC_e Result code
     */
    RC_e ReadNextRequest(Request* request);

    /**
     * @brief Function to Run the Node
     * 
     * @return RC_e Result code
     */
    RC_e Run();

    /**
     * @brief Function to start Run
     * 
     * @return RC_e Result code
     */
    RC_e Start();

    /**
     * @brief Function to stop Run
     * 
     * @return RC_e Result code
     */
    RC_e Stop();

    /**
     * @brief Print Buffer of requests
     * 
     * @return RC_e 
     */
    RC_e PrintBuffer();  

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

    /**
     * @brief Function to print the debug message
     * 
     * @param msg Message
     * @return RC_e Result code
     */
    RC_e Debug(char* msg);

private:

    HardwareSerial* m_serial;                       /**@brief Reference pointer of Serial Port */
    RequestBuffer* m_requestBuffer = NULL;          /**@brief Request Buffer object */

    bool m_debugMode = false;                       /**@brief Debug Mode */

    /**
     * @brief Function to configure serial port
     * 
     * @param baud Baud rate speed
     * @param RX RX GPIO
     * @param TX TX GPIO
     * @return RC_e Result code
     */
    RC_e ConfigureSerial(uint32_t baud, uint8_t RX, uint8_t TX);

    /**
     * @brief Function to send a request
     * 
     * @param request Reference of a request object
     * @return RC_e Result code
     */
    RC_e SendRequest(Request* request);

    /**
     * @brief Function to read a request
     * 
     * @param request Reference of a request object
     * @return RC_e Result code
     */
    RC_e ReadRequest(Request* request);

    /**
     * @brief Virtual-Function to handle the respuest
     * 
     * @param request Reference of a request object
     * @return RC_e Result code
     */
    RC_e virtual HandleRequest(Request* request) = 0;

};

#endif // Node_H