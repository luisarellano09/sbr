/**
 * @file PID_Manager.cpp
 * @author Jorge SALGADO (jorgesalgado23@gmail.com)
 * @brief Class to Manage the Engine, communication with PWM 
 * @version 1.0
 * @date 18-11-2020
 * 
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include "PID_Manager.h"
#include "GlobalDef.h"
/*******************************************************************************************************************************************
 *  												Constructor
 *******************************************************************************************************************************************/

//=====================================================================================================
PID_Manager::PID_Manager(){

}

//=====================================================================================================
PID_Manager::~PID_Manager(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/
RC_e PID_Manager::UpdatePID(float _PositionMesured, float *_PiD_Result){
    
    RC_e RetValue = RC_e::ERROR;
    float error;

    /*Input*/
    error = Setpoint - _PositionMesured;
    float P = UpdateP(error);
    float I = UpdateI(error);
    float D = UpdateD(error, Prev_error);
    
    if(*_PiD_Result != NULL){
        
        *_PiD_Result = P+I+D;
        
        Prev_error = error;
        RetValue = RC_e::SUCCESS;
    }
   

    return RetValue;
}


RC_e PID_Manager::GetKp(float *_kp){
    RC_e RetValue = RC_e::ERROR;
    if(*_kp >= 0.0f){
        *_kp = Kp;
        RetValue = RC_e::SUCCESS;
    }   
    return RetValue;
}

RC_e PID_Manager::GetKi(float *_ki){
    RC_e RetValue = RC_e::ERROR;
    if(*_ki >= 0.0f){
        *_ki = Ki;
       RetValue = RC_e::SUCCESS;
    }
    return RetValue;
}
RC_e PID_Manager::GetKd(float *_kd){
    RC_e RetValue = RC_e::ERROR;    
    if(*_kd >= 0.0f){
        *_kd = Kd;
        RetValue = RC_e::SUCCESS;
    }
    return RetValue;
}

RC_e PID_Manager::SetKp(float _kp){
    RC_e RetValue = RC_e::ERROR;
    if(_kp >= 0.0f){
        this->Kp = _kp;
        RetValue = RC_e::SUCCESS;
    }
    
    
    return RetValue;
}

RC_e PID_Manager::SetKi(float _ki){
    RC_e RetValue = RC_e::ERROR;
    if(_ki >= 0){
        this->Ki = _ki;
        RetValue = RC_e::SUCCESS;
    }
    return RetValue;
}

RC_e PID_Manager::SetKd(float _kd){
    RC_e RetValue = RC_e::ERROR;
    if(_kd >= NULL){
        this->Kd = _kd;
        RetValue = RC_e::SUCCESS;
    }
    return RetValue;
}


/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/

float PID_Manager::UpdateP(float error){
    float RetValue;
    RetValue = error*Kp;
    return RetValue;
}


float PID_Manager::UpdateI(float error){
    float RetValue;
    static float value;

    value +=error;
    RetValue = value*Ki;

    return RetValue;    
}

float PID_Manager::UpdateD(float error, float Prev_error){
    float RetValue;
    RetValue = (error-Prev_error)*Kd;
    return RetValue;    
}