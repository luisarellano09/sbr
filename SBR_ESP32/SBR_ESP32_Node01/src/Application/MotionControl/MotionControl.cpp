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
    this->m_PIDPitch = new PID(PIDDirection_e::INVERT);
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

    if (this->m_IMU->m_Pitch > 35.0 || this->m_IMU->m_Pitch < -35.0) {
        m_motorLeft->Stop();
        m_motorRight->Stop();
    } else {

        if (count %10 == 0){
            this->m_PIDAngle->SetSP(this->m_SPAngle);
            this->m_PIDAngle->SetPV(this->m_odometry->GetAngle());
            this->m_PIDAngle->Run();

            this->m_PIDPosition->SetSP(this->m_SPPos);
            this->m_PIDPosition->SetPV(this->m_odometry->GetDistance());
            this->m_PIDPosition->Run();
        }


        this->m_PIDPitch->SetSP(this->m_PIDPosition->GetMV());
        this->m_PIDPitch->SetPV(this->m_IMU->m_Pitch);
        this->m_PIDPitch->Run();



        this->m_motorLeft->SetSpeed((this->m_PIDPitch->m_MV + this->m_PIDAngle->m_MV) / 2.0);
        this->m_motorRight->SetSpeed((this->m_PIDPitch->m_MV - this->m_PIDAngle->m_MV) / 2.0);

    }

    return retCode;
}


/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

double MotionControl::GetDistancePoints(double x1, double y1, double x2, double y2){
	return sqrt( pow(x1-x2,2.0) + pow(y1-y2,2.0) );
}