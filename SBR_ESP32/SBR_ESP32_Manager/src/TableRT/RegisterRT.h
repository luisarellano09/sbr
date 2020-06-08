/**
 * \file RegisterRT.h
 * \author Luis Arellano - luis.arellano09@gmail.com
 * \date 26 April 2020
 *
 * \brief Class to describe a register of the Data Table in Runtime.
 *
 * 
 * 
 * Changes
 * 07.06.2020: Create Class.
 * 
 *
 */

#ifndef REGISTERRT_H
#define REGISTERRT_H

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/

#include "../../lib/Definition/GlobalDef.h"
#include "../Definition/LocalDef.h"


/*******************************************************************************************************************************************
 *  												TableRT Class
 *******************************************************************************************************************************************/

/**
 * \brief Class to describe the Data Table in Runtime.
 */
class RegisterRT
{
public:  

    uint32_t m_value;
    Devices_e m_subscribers[Devices_e::DEVICE_LENGTH] = {Devices_e::DEVICE_NONE};
    uint8_t m_subscribers_index;

    /**
     * \brief Constructor.
     */
    RegisterRT();

    /**
     * \brief Destructor.
     */
    ~RegisterRT();

    /**
     * \brief Add subscriber.
     */
    RC_e AddSubscriber(Devices_e subscriber);  
   
    /**
     * \brief Clean Subscribers.
     */
    RC_e CleanSubscribers();  
   
private:


};

#endif // REGISTERRT_H