/**
 * @file MotionControl.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Motion Control Class
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
    double steer = 0.0;

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

    /**
     * @brief Set SP Position
     * 
     * @param spPosition Position SP
     * @return RC_e Result Code
     */
    RC_e SetSPPos(double spPosition);

    /**
     * @brief Get SP Position
     * 
     * @return double SP Position
     */
    double GetSPPos();

    /**
     * @brief Set SP Angle
     * 
     * @param spAngle Angle SP
     * @return RC_e Result Code
     */
    RC_e SetSPAngle(double spAngle);

    /**
     * @brief Get SP Angle
     * 
     * @return double SP Angle
     */
    double GetSPAngle();

    /**
     * @brief Set Falldown Offset
     * 
     * @param offset Falldown Offset
     * @return RC_e Result Code
     */
    RC_e SetFalldownOffset(double offset);

    /**
     * @brief Get Falldown Offset
     * 
     * @return double Falldown Offset
     */
    double GetFalldownOffset();

    /**
     * @brief Is Falldown
     * 
     * @return true Falldown
     * @return false Not Falldown
     */
    bool IsFalldown();

    /**
     * @brief Calculate the Falldown
     * 
     * @return RC_e Result Code
     */
    RC_e CalculateFalldown();

    /**
     * @brief Start the Motion control
     * 
     * @return RC_e Result Code.
     */
    RC_e Start();

    /**
     * @brief Stop the Motion control
     * 
     * @return RC_e 
     */
    RC_e Stop();


private:

    IMU* m_IMU = NULL;              /**@brief Reference of an IMU object. */
    Odometry* m_odometry = NULL;    /**@brief Reference of an Odometry object. */
    Motor* m_motorLeft = NULL;      /**@brief Reference of a Motor (Left) object. */
    Motor* m_motorRight = NULL;     /**@brief Reference of a Motor (Right) object. */
    double m_SPAngle = 0.0;         /**@brief Angle SP. */
    double m_SPPos = 0.0;           /**@brief Position SP. */
    long m_CycleCounter = 0;        /**@brief Cycle counter. */
    double m_FalldownOffset = 45.0; /**@brief Falldown offset. */
    bool m_Falldown = true;         /**@brief Falldown flag. */
};

#endif // MOTIONCONTROL_H