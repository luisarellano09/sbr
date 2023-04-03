/**
 * @file MotionControl.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Motion Control Class
 * @date 29.03.2023
 * 
 */

#ifndef MOTIONCONTROL_H
#define MOTIONCONTROL_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include "../../Middleware/PID/PID.h"
#include "../../Middleware/IMU/IMU.h"
#include "../../Middleware/Motor/Motor.h"
#include "../../Definition/Global/RC.h"

/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Motion Control Class
 * 
 */
class MotionControl {
public:  

    PID* m_PIDPitch = NULL;              /**@brief Instance for PID. */
    IMU* m_IMU = NULL;
    Motor* m_motorLeft = NULL;
    Motor* m_motorRight = NULL;

    /**
     * @brief Construct a new Motion Control object
     * 
     */
    MotionControl(IMU* imu, Motor* motorLeft, Motor* motorRight);

    /**
     * @brief Destroy the Motion Control object
     * 
     */
    ~MotionControl();

    /**
     * @brief Run
     * 
     * @return RC_e Result Code
     */
    RC_e Run();

private:


};

#endif // MOTIONCONTROL_H