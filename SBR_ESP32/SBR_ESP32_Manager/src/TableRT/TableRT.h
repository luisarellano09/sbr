/**
 * \file TableRT.h
 * \author Luis Arellano - luis.arellano09@gmail.com
 * \date 26 April 2020
 *
 * \brief Class to describe the Data Table in Runtime.
 *
 * 
 * 
 * Changes
 * 07.06.2020: Create Class.
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
 * \brief Class to describe the Data Table in Runtime.
 */
class TableRT
{
public:  

    RegisterRT m_Registers[COM_REQUEST_REG_ID_e::REQUEST_REG_LENGTH];

    /**
     * \brief Constructor.
     */
    TableRT();

    /**
     * \brief Destructor.
     */
    ~TableRT();

    /**
     * \brief Add subscriber to a register.
     */
    RC_e AddSubscriber(COM_REQUEST_REG_ID_e regID, Devices_e subscriber);  

    /**
     * \brief Update Register.
     */
    RC_e UpdateRegister(COM_REQUEST_REG_ID_e regID, uint32_t data);  
   
private:

    /**
     * \brief Clean Registers.
     */
    RC_e CleanRegisters();  

};

#endif // TABLERT_H