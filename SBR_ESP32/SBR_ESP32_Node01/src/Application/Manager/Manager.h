/**
 * @file Manager.h
 * @author Luis Arellano - luis.arellano09@gmail.com
 * @brief Class to Manage the ESP32
 * @version 1.0
 * @date 16.10.2022
 * 
 */

#ifndef MANAGER_H
#define MANAGER_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "../../Definition/Global/RC.h"
#include "../../Middleware/WifiManager/WifiManager.h"
#include "../CommunicationBus/NodeEsp32/NodeEsp32.h"
#include "../../Middleware/Motor/Motor.h"
#include "../../Middleware/IMU/IMU.h"
#include "../MotionControl/MotionControl.h"


/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the ESP32
 * 
 */
class Manager {
public:  

    WifiManager* m_wifiManager = NULL;              /**@brief Instance for Wifimanager. */
    NodeEsp32* m_nodeESP32 = NULL;                  /**@brief Instance for the node ESP32. */
    Motor* m_motorLeft = NULL;                      /**@brief Instance for the left motor. */  
    Motor* m_motorRight = NULL;                     /**@brief Instance for the right motor. */
    IMU* m_IMU = NULL;                              /**@brief Instance for the IMU. */
    MotionControl* m_motionControl = NULL;          /**@brief Instance for the Motion Control. */

    /**
     * @brief Construct a new Manager object
     * 
     */
    Manager();

    /**
     * @brief Destroy the Manager object
     * 
     */
    ~Manager();

   
private:


};

#endif // MANAGER_H