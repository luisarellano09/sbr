/**
 * @file PID.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief PID Class
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "PID.h"
#include <ArduinoLog.h>


/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

PID::PID(PIDDirection_e direction){
    this->m_direction = direction;
    this->m_mode = PIDMode::PID_STOP;
    this->m_prevError = 0.0;
    this->m_prevMVIntegral = 0.0;
}


//=====================================================================================================

PID::~PID(){
}


/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e PID::Run(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    double mvP = 0.0;
    double mvI = 0.0;
    double mvD = 0.0;
    double mvU = 0.0;

    if (this->m_mode == PIDMode::PID_START){
        // Error
        this->m_error = this->m_SP - this->m_PV;
        
        // Proportional
        mvP = this->m_Kp * this->m_error;

        // Integral
        mvI = this->m_prevMVIntegral + this->m_cycleTime * this->m_Ki * (this->m_error + this->m_prevError) / 2.0;

        // Differential
        mvD = this->m_Kd * (this->m_error - this->m_prevError) / this->m_cycleTime;

        // U
        mvU = mvP + mvI + mvD;

        // Anti-windup
        if (mvU > this->m_mvRangeMax || mvU < this->m_mvRangeMin) {
            mvI = this->m_prevMVIntegral;
        }

        // Output Limit
        if (mvU > this->m_mvRangeMax){
            mvU = this->m_mvRangeMax;
        } else if (mvU < this->m_mvRangeMin){
            mvU = this->m_mvRangeMin;
        }

        // Assign Output
        if (this->m_direction == PIDDirection_e::PID_DIRECTION_DIRECT){
            this->m_MV = mvU;
        } else {
            this->m_MV = mvU * -1.0;
        }
        
        // Save Previous
        this->m_prevError = this->m_error;
        this->m_prevMVIntegral = mvI;
        
    } else{
        this->m_prevError = 0.0;
        this->m_prevMVIntegral = 0.0;
        this->m_MV = 0.0;
    }

    return retCode;
}


//=====================================================================================================

RC_e PID::Start(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_mode = PIDMode::PID_START;
    Log.traceln("[PID::Start] PID Started");

    return retCode;
}


//=====================================================================================================

RC_e PID::Stop(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_mode = PIDMode::PID_STOP;
    Log.traceln("[PID::Stop] PID stopped");

    return retCode;
}


//=====================================================================================================

RC_e PID::SetSP(double SP){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_SP = SP;

    Log.traceln("[PID::SetSP] SP setted: %D", this->m_SP);

    return retCode;
}


//=====================================================================================================

RC_e PID::SetPV(double PV){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_PV = PV;

    Log.traceln("[PID::SetPV] PV setted: %D", this->m_PV);

    return retCode;
}


//=====================================================================================================

double PID::GetPV(){
    return this->m_PV;
}


//=====================================================================================================

double PID::GetSP(){
    return this->m_SP;
}


//=====================================================================================================

double PID::GetMV(){
    return this->m_MV;
}


//=====================================================================================================

double PID::GetError(){
    return this->m_error;
}


//=====================================================================================================

RC_e PID::SetParameters(double Kp, double Ki, double Kd){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_Kp = Kp;
    this->m_Ki = Ki;
    this->m_Kd = Kd;

    Log.traceln("[PID::SetParameters] Parameters setted Kp: %D, Ki: %D, Kd: %D", this->m_Kp, this->m_Ki, this->m_Kd);

    return retCode;
}


//=====================================================================================================

RC_e PID::SetKp(double Kp){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_Kp = Kp;

    Log.traceln("[PID::SetKp] Kp setted: %D", this->m_Kp);

    return retCode;
}


//=====================================================================================================

double PID::GetKp(){
    return this->m_Kp;
}


//=====================================================================================================

RC_e PID::SetKi(double Ki){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_Ki = Ki;

    Log.traceln("[PID::SetKi] Ki setted: %D", this->m_Ki);

    return retCode;
}


//=====================================================================================================

double PID::GetKi(){
    return this->m_Ki;
}


//=====================================================================================================

RC_e PID::SetKd(double Kd){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_Kd = Kd;

    Log.traceln("[PID::SetKd] Kd setted: %D", this->m_Kd);

    return retCode;
}


//=====================================================================================================

double PID::GetKd(){
    return this->m_Kd;
}


//=====================================================================================================

RC_e PID::SetCycleTime(double cycleTime){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_cycleTime = cycleTime;

    Log.traceln("[PID::SetCycleTime] CycleTine setted: %D", this->m_cycleTime);

    return retCode;
}


//=====================================================================================================

double PID::GetCycleTime(){
    return this->m_cycleTime;
}


//=====================================================================================================

RC_e PID::SetDirection(PIDDirection_e direction){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_direction = direction;

    Log.traceln("[PID::SetDirection] Direction setted: %D", this->m_direction);

    return retCode;
}


//=====================================================================================================

PIDDirection_e PID::GetDirection(){
    return this->m_direction;
}


//=====================================================================================================

PIDMode PID::GetMode(){
    return this->m_mode;
}


//=====================================================================================================

RC_e PID::SetMVRange(double mvRangeMin, double mvRangeMax){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_mvRangeMin = mvRangeMin;
    this->m_mvRangeMax = mvRangeMax;

    Log.traceln("[PID::SetMVRange] MV Range setted Min: %D, Max: %D", this->m_mvRangeMin, this->m_mvRangeMax);

    return retCode;
}


//=====================================================================================================

RC_e PID::SetMVRangeMin(double mvRangeMin){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_mvRangeMin = mvRangeMin;

    Log.traceln("[PID::SetMVRangeMin] MVRangeMin setted: %D", this->m_mvRangeMin);

    return retCode;
}


//=====================================================================================================

double PID::GetMVRangeMin(){
    return this->m_mvRangeMin;
}


//=====================================================================================================

RC_e PID::SetMVRangeMax(double mvRangeMax){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_mvRangeMax = mvRangeMax;

    Log.traceln("[PID::SetMVRangeMax] MVRangeMin setted: %D", this->m_mvRangeMax);

    return retCode;
}


//=====================================================================================================

double PID::GetMVRangeMax(){
    return this->m_mvRangeMax;
}


//=====================================================================================================

RC_e PID::Print(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    Serial.println("*****************");
    Serial.printf(" - Mode: %d\r\n", this->m_mode);
    Serial.printf(" - SP: %f\r\n", this->m_SP);
    Serial.printf(" - PV: %f\r\n", this->m_PV);
    Serial.printf(" - Error: %f\r\n", this->m_error);
    Serial.printf(" - MV: %f\r\n", this->m_MV);
    Serial.printf(" - Kp: %f\r\n", this->m_Kp);
    Serial.printf(" - Ki: %f\r\n", this->m_Ki);
    Serial.printf(" - Kd: %f\r\n", this->m_Kd);
    Serial.printf(" - Cycle Time: %f\r\n", this->m_cycleTime);
    Serial.printf(" - Direction: %d\r\n", this->m_direction);
    Serial.printf(" - MV Range Min: %f\r\n", this->m_mvRangeMin);
    Serial.printf(" - MV Range Max: %f\r\n", this->m_mvRangeMax);
    Serial.println("*****************");

    return retCode;
}
