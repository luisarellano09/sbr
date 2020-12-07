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
PID_Manager::PID_Manager(float _Setpoint, float _kp, float _ki, float _kd){
    this->PIDSetpoint = _Setpoint;
    this->Kp = _kp;
    this->Ki = _ki;
    this->Kd = _kd;
}
//=====================================================================================================
PID_Manager::~PID_Manager(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/
/**
 * @brief Compute the error and update the ouput of PID
 * 
 * @param _PositionMesured Input the get the error
 * @param _PiD_Result Output of the PID
 * @return RC_e Result code
 */
RC_e PID_Manager::UpdatePID(float _PositionMesured, float *_PiD_Result){
    
    RC_e RetValue = RC_e::ERROR;

    /*Input*/
    float error = ComputeError(_PositionMesured);
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

/**
 * @brief Get the Setpoint value of the PID
 *          
 * @param _Setpoint Output of the setpoint PID  value
 * @return RC_e Result code
 */
RC_e PID_Manager::GetConsigne(float *_Setpoint){
    RC_e RetValue = RC_e::ERROR;
    if((*_Setpoint < MAX_RADIAN)&&(*_Setpoint > MIN_RADIAN)){
        *_Setpoint = this->PIDSetpoint;
        RetValue = RC_e::SUCCESS;
    }
    return RetValue;
}

/**
 * @brief Set the value of the Setpoint of the PID 
 *          range [-50° to 50°]
 * 
 * @param _Setpoint Input the value of the new Setpoint
 * @return RC_e Result code
 */
RC_e PID_Manager::SetConsigne(float _Setpoint){
    RC_e RetValue = RC_e::ERROR;
    if((_Setpoint < MAX_RADIAN)&&(_Setpoint > MIN_RADIAN)){
        this->PIDSetpoint = _Setpoint;
        RetValue = RC_e::SUCCESS;
    }
        
    return RetValue;
}

/**
 * @brief Get the Coefficient Proportional Kp  of the PID
 *          
 * @param _kp Output of the Kp PID  value
 * @return RC_e Result code
 */
RC_e PID_Manager::GetKp(float *_kp){
    RC_e RetValue = RC_e::ERROR;
    if(*_kp >= 0.0f){
        *_kp = this->Kp;
        RetValue = RC_e::SUCCESS;
    }   
    return RetValue;
}

/**
 * @brief Get the Coefficient Integral Ki  of the PID
 *          
 * @param _ki Output of the Ki PID  value
 * @return RC_e Result code
 */
RC_e PID_Manager::GetKi(float *_ki){
    RC_e RetValue = RC_e::ERROR;
    if(*_ki >= 0.0f){
        *_ki = this->Ki;
       RetValue = RC_e::SUCCESS;
    }
    return RetValue;
}


/**
 * @brief Get the Coefficient derivative Kd  of the PID
 *          
 * @param _kd Output of the Kd PID  value
 * @return RC_e Result code
 */
RC_e PID_Manager::GetKd(float *_kd){
    RC_e RetValue = RC_e::ERROR;    
    if(*_kd >= 0.0f){
        *_kd = this->Kd;
        RetValue = RC_e::SUCCESS;
    }
    return RetValue;
}

/**
 * @brief Set the Coefficient Proportional Kp  of the PID
 *          
 * @param _kp Input value
 * @return RC_e Result code
 */
RC_e PID_Manager::SetKp(float _kp){
    RC_e RetValue = RC_e::ERROR;
    if(_kp >= 0.0f){
        this->Kp = _kp;
        RetValue = RC_e::SUCCESS;
    }
    return RetValue;
}

/**
 * @brief Set the Coefficient Integral Ki  of the PID
 *          
 * @param _ki input value
 * @return RC_e Result code
 */
RC_e PID_Manager::SetKi(float _ki){
    RC_e RetValue = RC_e::ERROR;
    if(_ki >= 0){
        this->Ki = _ki;
        RetValue = RC_e::SUCCESS;
    }
    return RetValue;
}

/**
 * @brief Set the Coefficient Integral Kd  of the PID
 *          
 * @param _kd input value
 * @return RC_e Result code
 */
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

float PID_Manager::ComputeError(float _PositionMesured){
    float RetValue;
    RetValue = this->PIDSetpoint - _PositionMesured;
    return RetValue;
}