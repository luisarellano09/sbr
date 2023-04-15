/**
 * @file Odometry.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Odometry Class
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "Odometry.h"
#include <ArduinoLog.h>


/*******************************************************************************************************************************************
 *  												DEFINE
 *******************************************************************************************************************************************/

#define FACTOR_CONV_DEG_TO_RAD (double)0.017453293


/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

Odometry::Odometry(Encoder* encoderLeft, Encoder* encoderRight, double radio, double distanceWheels, double ticksRevolution){
    this->m_encoderLeft = encoderLeft;
    this->m_encoderRight = encoderRight;
    this->m_radio = radio;
    this->m_distanceWheels = distanceWheels;
    this->m_ticksRevolution = ticksRevolution;
    this->SetX(0.0);
    this->SetY(0.0);
    this->SetAngle(0.0);
    this->SetDistance(0.0);
}


//=====================================================================================================

Odometry::~Odometry(){
}


/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e Odometry::Run(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    double encoderLeftCount = (double)this->m_encoderLeft->GetCount();
    double encoderRightCount = (double)this->m_encoderRight->GetCount();
    double deltaEncoderLeftCount = encoderLeftCount - this->m_prevEncoderLeftCount;
    double deltaEncoderRightCount = encoderRightCount - this->m_prevEncoderRightCount;

    this->m_distance += PI * this->m_radio * (deltaEncoderLeftCount + deltaEncoderRightCount) / this->m_ticksRevolution;
    this->m_angle += 360.0 * this->m_radio * (deltaEncoderLeftCount - deltaEncoderRightCount) / (this->m_ticksRevolution * this->m_distanceWheels);
    this->m_x += PI * this->m_radio * (deltaEncoderLeftCount + deltaEncoderRightCount) * cos(FACTOR_CONV_DEG_TO_RAD * this->m_angle) / this->m_ticksRevolution;
    this->m_y += PI * this->m_radio * (deltaEncoderLeftCount + deltaEncoderRightCount) * sin(FACTOR_CONV_DEG_TO_RAD * this->m_angle) / this->m_ticksRevolution;

    this->m_prevEncoderLeftCount = encoderLeftCount;
    this->m_prevEncoderRightCount = encoderRightCount;

    return retCode;
}


//=====================================================================================================

RC_e Odometry::SetX(double x){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_x = x;
    Log.traceln("[Odometry::SetX] X coordinate setted: %D", this->m_x);

    return retCode;
}


//=====================================================================================================

double Odometry::GetX(){
    return this->m_x;
}


//=====================================================================================================

RC_e Odometry::SetY(double y){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_y = y;
    Log.traceln("[Odometry::SetY] Y coordinate setted: %D", this->m_y);

    return retCode;
}


//=====================================================================================================

double Odometry::GetY(){
    return this->m_y;
}


//=====================================================================================================

RC_e Odometry::SetAngle(double angle){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_angle = angle;
    Log.traceln("[Odometry::SetAngle] Angle setted: %D", this->m_angle);

    return retCode;
}


//=====================================================================================================

double Odometry::GetAngle(){
    return this->m_angle;
}


//=====================================================================================================

RC_e Odometry::SetDistance(double distance){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_distance = distance;
    Log.traceln("[Odometry::SetDistance] Distance setted: %D", this->m_distance);

    return retCode;
}


//=====================================================================================================

double Odometry::GetDistance(){
    return this->m_distance;
}


//=====================================================================================================

RC_e Odometry::Reset(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_distance = 0.0;
    this->m_angle = 0.0;
    this->m_x = 0;
    this->m_y = 0;

    return retCode;
}


//=====================================================================================================

RC_e Odometry::SetRadio(double radio){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_radio = radio;
    Log.traceln("[Odometry::SetRadio] Radio setted: %D", this->m_radio);

    return retCode;
}


//=====================================================================================================

double Odometry::GetRadio(){
    return this->m_radio;
}


//=====================================================================================================

RC_e Odometry::SetDistanceWheels(double distanceWheels){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_distanceWheels = distanceWheels;
    Log.traceln("[Odometry::SetDistanceWheels] Distance Wheels setted: %D", this->m_distanceWheels);

    return retCode;
}


//=====================================================================================================

double Odometry::GetDistanceWheels(){
    return this->m_distanceWheels;
}


/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

