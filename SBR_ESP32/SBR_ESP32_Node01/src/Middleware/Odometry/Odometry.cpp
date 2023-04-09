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

Odometry::Odometry(Encoder* encoderLeft, Encoder* encoderRight, double radio, double D, double TR){
    this->m_encoderLeft = encoderLeft;
    this->m_encoderRight = encoderRight;
    this->m_radio = radio;
    this->m_D = D;
    this->m_TR = TR;
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

    this->m_distance = PI * this->m_radio * (encoderLeftCount + encoderRightCount) / this->m_TR;

    this->m_angle += 360.0 * this->m_radio * ((encoderLeftCount - this->m_prevEncoderLeftCount) - (encoderRightCount - this->m_prevEncoderRightCount)) / (this->m_TR * this->m_D);
    this->m_x += PI * this->m_radio * ((encoderLeftCount - this->m_prevEncoderLeftCount) + (encoderRightCount - this->m_prevEncoderRightCount)) * cos(FACTOR_CONV_DEG_TO_RAD * this->m_angle) / this->m_TR;
    this->m_y += PI * this->m_radio * ((encoderLeftCount - this->m_prevEncoderLeftCount) + (encoderRightCount - this->m_prevEncoderRightCount)) * sin(FACTOR_CONV_DEG_TO_RAD * this->m_angle) / this->m_TR;

    this->m_prevEncoderLeftCount = encoderLeftCount;
    this->m_prevEncoderRightCount = encoderRightCount;

    return retCode;
}


//=====================================================================================================

RC_e Odometry::SetX(double x){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_x = x;
    Log.traceln("[Odometry::SetX] X coordinate setted: ", this->m_x);

    return retCode;
}


//=====================================================================================================

RC_e Odometry::SetY(double y){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_y = y;
    Log.traceln("[Odometry::SetY] Y coordinate setted: ", this->m_y);

    return retCode;
}


//=====================================================================================================

RC_e Odometry::SetAngle(double angle){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_angle = angle;
    Log.traceln("[Odometry::SetAngle] Angle setted: ", this->m_angle);

    return retCode;
}


//=====================================================================================================

RC_e Odometry::SetDistance(double distance){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_distance = distance;
    Log.traceln("[Odometry::SetDistance] Distance setted: ", this->m_distance);

    return retCode;
}


//=====================================================================================================

double Odometry::GetX(){
    return this->m_x;
}


//=====================================================================================================

double Odometry::GetY(){
    return this->m_y;
}


//=====================================================================================================

double Odometry::GetAngle(){
    return this->m_angle;
}


//=====================================================================================================

double Odometry::GetDistance(){
    return this->m_distance;
}

/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

