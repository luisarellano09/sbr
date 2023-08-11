/**
 * @file NodeLinux.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the NodeLinux
 * 
 */

#ifndef NODELINUX_H
#define NODELINUX_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include "../../../Middleware/CommunicationBus/Node/Node.h"
#include "../RegisterTable/RegisterTable.h"


/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the NodeLinux
 * 
 */
class NodeLinux: public Node {
public:  

    /**
     * @brief Construct a new Node Linux object
     * 
     * @param serial Serial port
     * @param baud Baudrate
     * @param RX RX Pin
     * @param TX TX Pin
     */
    NodeLinux(HardwareSerial* serial, uint32_t baud, uint8_t RX, uint8_t TX);

    /**
     * @brief Destroy the spi mastermanager object
     * 
     */
    ~NodeLinux();

    /**
     * @brief Function to connect with a Table Register.
     * 
     * @param tableRegister Reference of a Table Register
     * @return RC_e Result code
     */
    RC_e ConnectRegisterTable(RegisterTable* tableRegister);

    /**
     * @brief Run
     * 
     * @return RC_e Result code
     */
    RC_e Run();

    /**
     * @brief Pointer of a function to handle a request externally
     * 
     * @param request Reference of a request object
     * @return RC_e Result code
     */
    RC_e (*ExtHandler)(Request* request);


private:

    RegisterTable* m_tableRegister = NULL;          /**@brief Reference of Table Register object */

    /**
     * @brief Function to handle a request
     * 
     * @param request Reference of a request object
     * @return RC_e Result code
     */
    RC_e HandleRequest(Request* request);

};

#endif // NODELINUX_H