/**
 * @file MotionControl.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Motion Control Class
 * @date 29.03.2023
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "MotionControl.h"
#include <ArduinoLog.h>


/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

MotionControl::MotionControl(IMU* imu, Motor* motorLeft, Motor* motorRight){
    this->m_PIDPitch = new PID(PIDDirection_e::INVERT);
    this->m_IMU = imu;
    this->m_motorLeft = motorLeft;
    this->m_motorRight = motorRight;
}


//=====================================================================================================

MotionControl::~MotionControl(){
}


/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e MotionControl::Run(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    if (this->m_IMU->m_Pitch > 35.0 || this->m_IMU->m_Pitch < -35.0) {
        m_motorLeft->Stop();
        m_motorRight->Stop();
        //m_PIDPitch->SetMode(PIDMode::STOP);
    } else {
        if (this->m_IMU->m_Pitch < 1.0 && this->m_IMU->m_Pitch > -1.0) {
            //m_motorLeft->Stop();
            //m_motorRight->Stop();
        } else {
            this->m_PIDPitch->SetPV(m_IMU->m_Pitch);
            this->m_PIDPitch->Run();
            this->m_motorLeft->SetSpeed(this->m_PIDPitch->m_MV);
            this->m_motorRight->SetSpeed(this->m_PIDPitch->m_MV);
        }
    }

    return retCode;
}