/**
 * @file PID_Manager.h
 * @author Jorge Salgado (jorgesalgado23@gmail.com)
 * @brief Class to Manage the 2 motors
 * @version 1.0
 * @date 18-11-2020
 * 
 * 
 */

#ifndef PID_MANAGER_H
#define PID_MANAGER_H

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include "../Definition/GlobalDef.h"

#define P_Gain  120.0f
#define I_Gain  20.0f
#define D_Gain  60.0f

#define POSITIONDESIRED     (float)0.0f

/*******************************************************************************************************************************************
 *  												IMUManager Class
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the IMU in this case BNO080
 * 
 */
class PID_Manager{

public: 
    /*Global Variables*/
    float Setpoint = POSITIONDESIRED;       
    float Kp    = P_Gain;   // Kp -  proportional gain
    float Ki    = I_Gain;   // Ki -  Integral gain
    float Kd    = D_Gain;   // Kd -  derivative gain
    float dt    = 0.0;       // dt -  loop interval time

    float IState =0.0;

    /**
     * @brief Construct a new Motor Manager object
     * 
     * @param 
     * @param 
     * @param 
     */
    PID_Manager();

    /**
     * @brief Destroy the Motor Manager object
     * 
     */
    ~PID_Manager();

    /**
     * @brief Connect to 
     * 
     * @return RC_e Result code
     */

    RC_e UpdatePID(float _PositionMesured, float *_PiD_Result);

    RC_e GetKp(float *_Kp);
    RC_e GetKi(float *_Ki);
    RC_e GetKd(float *_Kd);

    RC_e SetKp(float _kp);
    RC_e SetKi(float _ki);
    RC_e SetKd(float _kd);


private:
    /*Variable*/
    float Prev_error = 0.0;     //  e(k-1)
    /*functions*/
    float UpdateP(float error);  
    float UpdateI(float error);  
    float UpdateD(float error, float Prev_error);  
};

#endif // PID_MANAGER_H