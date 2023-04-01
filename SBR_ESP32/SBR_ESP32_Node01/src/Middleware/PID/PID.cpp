/**
 * @file PID.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief PID Class
 * @date 28.03.2023
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
    this->m_mode = PIDMode::STOP;
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

    if (this->m_mode == PIDMode::AUTO){
        // Error
        this->m_error = this->m_SP - this->m_PV;
        
        // Proportional
        mvP = this->m_kp * this->m_error;

        // Integral
        mvI = this->m_prevMVIntegral + this->m_cycleTime * this->m_ki * (this->m_error + this->m_prevError) / 2.0;

        // Differential
        mvD = this->m_kd * (this->m_error - this->m_prevError) / this->m_cycleTime;

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
        if (this->m_direction == PIDDirection_e::DIRECT){
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

RC_e PID::SetParameters(double kp, double ki, double kd){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_kp = kp;
    this->m_ki = ki;
    this->m_kd = kd;

    Log.traceln("[PID::SetParameters] Parameters setted Kp: %D, Ki: %D, Kd: %D", this->m_kp, this->m_ki, this->m_kd);

    return retCode;
}


//=====================================================================================================

RC_e PID::SetCycleTime(double cycleTime){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_cycleTime = cycleTime;

    Log.traceln("[PID::SetCycleTime] Cycle Time setted: %D", this->m_cycleTime);

    return retCode;
}


//=====================================================================================================

RC_e PID::SetDirection(PIDDirection_e direction){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_direction = direction;

    Log.traceln("[PID::SetDirection] Direction setted: %d", this->m_direction);

    return retCode;
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

RC_e PID::SetMode(PIDMode mode){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_mode = mode;

    Log.traceln("[PID::SetMode] Mode setted: %d", this->m_mode);

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

double PID::GetMV(){

    return this->m_MV;
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
    Serial.printf(" - Kp: %f\r\n", this->m_kp);
    Serial.printf(" - Ki: %f\r\n", this->m_ki);
    Serial.printf(" - Kd: %f\r\n", this->m_kd);
    Serial.printf(" - Cycle Time: %f\r\n", this->m_cycleTime);
    Serial.printf(" - Direction: %d\r\n", this->m_direction);
    Serial.printf(" - MV Range Min: %f\r\n", this->m_mvRangeMin);
    Serial.printf(" - MV Range Max: %f\r\n", this->m_mvRangeMax);
    Serial.println("*****************");

    return retCode;
}



