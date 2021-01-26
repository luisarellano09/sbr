/**
 * @file RequestBuffer.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to describe the Buffer of requests
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */

#ifndef RequestBuffer_H
#define RequestBuffer_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "../../../Definition/GlobalDef.h"
#include "../../../Definition/LocalDef.h"
#include "../Request/Request.h"

/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to describe the Buffer of requests
 * 
 */
class RequestBuffer {
public:  

    /**
     * @brief Construct a new spi slave object
     * 
     */
    RequestBuffer();

    /**
     * @brief Destroy the spi slave object
     * 
     */
    ~RequestBuffer();

    /**
     * @brief Add request to the buffer
     * 
     * @param nodeId Node ID
     * @param reqType Request type
     * @param regID Register ID
     * @param data Data Value
     * @return RC_e Result code
     */
    RC_e AddRequest(DEVICE_e nodeId, COM_REQUEST_TYPE_e reqType, COM_REQUEST_REG_ID_e regID, uint32_t data);  

    /**
     * @brief Add request to the buffer
     * 
     * @param request Request
     * @return RC_e Result code
     */
    RC_e AddRequest(Request request);  

    /**
     * @brief Consume request from the buffer
     * 
     * @param request Pointer of request
     * @return RC_e Result code
     */
    RC_e ConsumeRequest(Request* request);  

    /**
     * @brief Clean Buffer of requests
     * 
     * @return RC_e 
     */
    RC_e CleanBuffer();  

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

    Request m_RequestsArray[REQUEST_BUFFER_SIZE];      /**< Array of requests. */
    int16_t m_RequestsArrayIndex;                      /**< Index of array of requests. */

    bool m_debugMode = false;           /**< Debug Mode */

    /**
     * @brief Function to print the debug message
     * 
     * @return RC_e Result code
     */
    RC_e Debug(char* msg);

};

#endif // RequestBuffer_H