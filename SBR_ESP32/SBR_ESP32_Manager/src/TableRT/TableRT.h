/**
 * @file TableRT.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to describe the Data Table in Runtime
 * @version 1.0
 * @date 13-06-2020
 * 
 * 
 */

#ifndef TABLERT_H
#define TABLERT_H

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/

#include "../../lib/Definition/GlobalDef.h"
#include "../Definition/LocalDef.h"

#include "./RegisterRT.h"

/*******************************************************************************************************************************************
 *  												TableRT Class
 *******************************************************************************************************************************************/

/**
 * @brief Class to describe the Data Table in Runtime
 * 
 */
class TableRT
{
public:  

    RegisterRT m_Registers[COM_REQUEST_REG_ID_e::REQUEST_REG_LENGTH];   /**< \brief Array of registers*/

    /**
     * @brief Construct a new Table RT object
     * 
     */
    TableRT();

    /**
     * @brief Destroy the Table RT object
     * 
     */
    ~TableRT();

    /**
     * @brief Add subscriber to a register
     * 
     * @param regID Register ID
     * @param subscriber Subscriber device
     * @return RC_e Result code
     */
    RC_e AddSubscriber(COM_REQUEST_REG_ID_e regID, Devices_e subscriber);  

    /**
     * @brief Update Register
     * 
     * @param regID Register ID
     * @param data Data Value
     * @return RC_e Result code
     */
    RC_e UpdateRegister(COM_REQUEST_REG_ID_e regID, uint32_t data);  

private:

    /**
     * @brief Clean registers
     * 
     * @return RC_e Result code
     */
    RC_e CleanRegisters();

};

#endif // TABLERT_H