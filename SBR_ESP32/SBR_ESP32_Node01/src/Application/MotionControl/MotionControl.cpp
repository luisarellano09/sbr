/**
 * @file MotionControl.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Motion Control Class
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
    this->m_PIDPitch = new PID(true);
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

    this->m_CycleCounter++;

    // Check if the Robot is falldown
    if (this->IsFalldown()) {
        // Stop the motors
        this->m_motorLeft->Stop();
        this->m_motorRight->Stop();

        // Reset the Odometry
        this->m_odometry->Reset();

        // Reset the PID
        this->SetSPPos(0.0);
        this->SetSPAngle(0.0);
        this->m_PIDAngle->Reset();
        this->m_PIDPitch->Reset();
        this->m_PIDPosition->Reset();

        // Reset the Cycle Counter
        this->m_CycleCounter = 0;
        
        vTaskDelay(2000);
    } else {

        // Reduce the call cycle 
        if (m_CycleCounter %10 == 0){
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
        this->m_motorLeft->SetSpeed(this->m_PIDPitch->GetMV()*0.8 + this->m_PIDAngle->GetMV()*0.2) ;
        this->m_motorRight->SetSpeed(this->m_PIDPitch->GetMV()*0.8 - this->m_PIDAngle->GetMV()*0.2);
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

double MotionControl::GetSPPos(){
    return this->m_SPPos;
}


//=====================================================================================================

RC_e MotionControl::SetSPAngle(double spAngle){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_SPAngle = spAngle;

    return retCode;
}


//=====================================================================================================

double MotionControl::GetSPAngle(){
    return this->m_SPAngle;
}


//=====================================================================================================

RC_e MotionControl::SetFalldownOffset(double offset){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_FalldownOffset = offset;

    return retCode;
}


//=====================================================================================================

double MotionControl::GetFalldownOffset(){
    return this->m_FalldownOffset;
}


//=====================================================================================================
bool MotionControl::IsFalldown(){
    return this->m_Falldown;
}


//=====================================================================================================

RC_e MotionControl::CalculateFalldown(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    if (abs(this->m_IMU->GetPitch()) > this->m_FalldownOffset) {
        this->m_Falldown = true;
    } else {
        this->m_Falldown = false;
    }

    return retCode;
}


//=====================================================================================================

RC_e MotionControl::Start(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_odometry->Reset();
    this->SetSPPos(0.0);
    this->SetSPAngle(0.0);
    this->m_PIDAngle->Reset();
    this->m_PIDPitch->Reset();
    this->m_PIDPosition->Reset();

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
    this->m_motorLeft->Stop();
    this->m_motorRight->Stop();

    return retCode;
}


/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

