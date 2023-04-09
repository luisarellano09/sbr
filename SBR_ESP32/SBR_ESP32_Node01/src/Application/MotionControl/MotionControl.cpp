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

MotionControl::MotionControl(IMU* imu, Odometry* odometry, Motor* motorLeft, Motor* motorRight){
    this->m_PIDPitch = new PID(PIDDirection_e::PID_DIRECTION_INVERT);
    this->m_PIDPosition = new PID();
    this->m_PIDAngle = new PID();
    this->m_IMU = imu;
    this->m_odometry = odometry;
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

    this->count++;

    // Check if the Robot is down
    if (this->m_IMU->GetPitch() > 55.0 || this->m_IMU->GetPitch() < -55.0) {
        m_motorLeft->Stop();
        m_motorRight->Stop();
    } else {

        // Reduce the call cycle 
        if (count %10 == 0){
            // PID Angle
            this->m_PIDAngle->SetSP(this->m_SPAngle);
            this->m_PIDAngle->SetPV(this->m_odometry->GetAngle());
            this->m_PIDAngle->Run();

            // PID Position
            this->m_PIDPosition->SetSP(this->m_SPPos);
            this->m_PIDPosition->SetPV(this->m_odometry->GetDistance());
            this->m_PIDPosition->Run();
        }

        // PID Pitch
        this->m_PIDPitch->SetSP(this->m_PIDPosition->GetMV());
        this->m_PIDPitch->SetPV(this->m_IMU->GetPitch());
        this->m_PIDPitch->Run();
        
        // Assign speed to Motors
        this->m_motorLeft->SetSpeed((this->m_PIDPitch->GetMV() + this->m_PIDAngle->GetMV()) / 2.0);
        this->m_motorRight->SetSpeed((this->m_PIDPitch->GetMV() - this->m_PIDAngle->GetMV()) / 2.0);
    }

    return retCode;
}


//=====================================================================================================

RC_e MotionControl::SetSPPos(double spPosition){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_SPPos = spPosition;

    return retCode;
}


//=====================================================================================================

RC_e MotionControl::SetSPAngle(double spAngle){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_SPAngle = spAngle;

    return retCode;
}


//=====================================================================================================

RC_e MotionControl::Start(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_PIDPitch->Start();
    this->m_PIDPosition->Start();
    this->m_PIDAngle->Start();

    return retCode;
}


//=====================================================================================================

RC_e MotionControl::Stop(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_PIDPitch->Stop();
    this->m_PIDPosition->Stop();
    this->m_PIDAngle->Stop();

    return retCode;
}

/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

