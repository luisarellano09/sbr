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
float PID_Manager::UpdatePID(float PositionMesured){
    float RetValue;
    float error = PositionDesired-PositionMesured;
    float P = UpdateP(error);
    float I = UpdateI(error);
    float D = UpdateD(error, Prev_error);
    RetValue = P+I+D;
    Prev_error = error;
    return RetValue;
}
/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/

float PID_Manager::UpdateP(float error){
    float RetValue;
    RetValue = error*P_Gain;
    return RetValue;
}


float PID_Manager::UpdateI(float error){
    float RetValue;
    /*float iMax = 1000;//0.1(maxOut-minOut)/I_Gain;
    float iMin = -1000;//-0.1(maxOut-minOut)/I_Gain;*/

    IState += error;
    RetValue = IState;
    /*Apply anti-windup*/
    /*if(RetValue>iMax){
        RetValue = iMax;
    }
    else if(RetValue<iMin){
        RetValue = iMin;
    }*/
    RetValue *= I_Gain;
    return RetValue;    
}



float PID_Manager::UpdateD(float error, float Prev_error){
    float RetValue;
    RetValue = (error-Prev_error)*D_Gain;
    return RetValue;    
}