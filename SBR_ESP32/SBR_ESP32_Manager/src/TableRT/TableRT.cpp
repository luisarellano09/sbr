/**
 * \file TableRT.cpp
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


/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include "./TableRT.h"

/*******************************************************************************************************************************************
 *  												Constructor
 *******************************************************************************************************************************************/
TableRT::TableRT(){
    // Clean all registers
    CleanRegisters();
}

TableRT::~TableRT(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/

RC_e TableRT::AddSubscriber(COM_REQUEST_REG_ID_e regID, Devices_e subscriber){
    m_Registers[regID].AddSubscriber(subscriber);
    return RC_e::SUCCESS;
}

RC_e TableRT::UpdateRegister(COM_REQUEST_REG_ID_e regID, uint32_t data){
    // Update value
    m_Registers[regID].m_value = data;
    return RC_e::SUCCESS;
}

/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/

RC_e TableRT::CleanRegisters(){
    // Iterate all registers
    for(auto i = 0; i < COM_REQUEST_REG_ID_e::REQUEST_REG_LENGTH; i++){
        m_Registers[i].CleanSubscribers();
    }
    return RC_e::SUCCESS;
}
