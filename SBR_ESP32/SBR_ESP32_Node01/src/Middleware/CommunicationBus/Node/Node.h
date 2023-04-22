/**
 * @file Node.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to manage the communication node
 * 
 */


#ifndef NODE_H
#define NODE_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include "../../../Definition/Global/RC.h"
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
     * @param regHeartbeatCounter Register of the Heartbeat counter
     * @return RC_e Result code
     */
    RC_e Run(COM_REQUEST_REG_ID_e regHeartbeatCounter);

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
     * @brief Token the Heartbeat Counter
     * 
     * @param HeartbeatCounter Heartbeat Counter
     * @param regHeartbeatCounter Register of the Heartbeat counter
     * @return RC_e Result code
     */
    RC_e TokenCounter(uint16_t HeartbeatCounter, COM_REQUEST_REG_ID_e regHeartbeatCounter);

    /**
     * @brief WatchDog
     * 
     * @param regHeartbeatCounter Register of the Heartbeat counter
     * @return RC_e Result code
     */
    RC_e WatchDog(COM_REQUEST_REG_ID_e regHeartbeatCounter);

    /**
     * @brief Feed the WatchDog counter
     * 
     * @param regHeartbeatCounter Register of the Heartbeat counter
     * @return RC_e Result code
     */
    RC_e FeedWatchDog(COM_REQUEST_REG_ID_e regHeartbeatCounter);

    /**
     * @brief Get the Error status
     * 
     * @return true Node is in Error
     * @return false Node is ok
     */
    bool GetError();

    /**
     * @brief Print Buffer of requests
     * 
     * @return RC_e Result code
     */
    RC_e PrintBuffer();  


protected:

    HardwareSerial* m_serial;                       /**@brief Reference pointer of Serial Port */
    RequestBuffer* m_requestBuffer = NULL;          /**@brief Request Buffer object */
    bool m_start = false;                           /**@brief Start command */
    uint16_t m_counterHeartbeat = 0;                /**@brief Counter heartbeat */
    uint16_t m_prevCounterHeartbeat = 0;            /**@brief Previous counter heartbeat */
    bool m_error = false;                           /**@brief Error  */
    long m_internalCounter = 0;                     /**@brief Internal Counter  */

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