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
#include "../../Middleware/Odometry/Odometry.h"
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

    PID* m_PIDPitch = NULL;         /**@brief Instance for PID Pitch. */
    PID* m_PIDPosition = NULL;      /**@brief Instance for PID Position. */
    PID* m_PIDAngle = NULL;         /**@brief Instance for PID Angle. */
    IMU* m_IMU = NULL;
    Odometry* m_odometry = NULL;
    Motor* m_motorLeft = NULL;
    Motor* m_motorRight = NULL;
    double m_SPAngle = 0.0;
    double m_SPPos = 0.0;
    long count = 0;


    /**
     * @brief Construct a new Motion Control object
     * 
     */
    MotionControl(IMU* imu, Odometry* odometry, Motor* motorLeft, Motor* motorRight);

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

    double GetDistancePoints(double x1, double y1, double x2, double y2);
};

#endif // MOTIONCONTROL_H