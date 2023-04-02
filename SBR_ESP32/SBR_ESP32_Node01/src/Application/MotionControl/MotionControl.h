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

    PID* m_PID = NULL;              /**@brief Instance for PID. */

    /**
     * @brief Construct a new Motion Control object
     * 
     */
    MotionControl();

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