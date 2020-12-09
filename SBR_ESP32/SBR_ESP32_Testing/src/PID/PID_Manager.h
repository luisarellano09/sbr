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

#define P_Gain  (float)120.0f
#define I_Gain  (float)20.0f
#define D_Gain  (float)60.0f

#define POSITIONDESIRED     (float)0.0f
#define MAX_RADIAN          (float)0.87f          //miliRadian = 50°
#define MIN_RADIAN          (float)-0.87f         //miliRadian = 50°

#define MAX_ACC_INTEGRAL    (float)4.00f
#define MIN_ACC_INTEGRAL    (float)-4.00f
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
    float PIDSetpoint = POSITIONDESIRED;       
    float Kp    = P_Gain;   // Kp -  proportional gain
    float Ki    = I_Gain;   // Ki -  Integral gain
    float Kd    = D_Gain;   // Kd -  derivative gain

    /**
     * @brief Construct a new Motor Manager object
     * 
     * @param 
     * @param 
     * @param 
     */
    PID_Manager();
    PID_Manager(float _Setpoint, float _kp, float _ki, float _kd);
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

    
    RC_e GetConsigne(float *_Setpoint);

    RC_e SetConsigne(float _Setpoint);


    RC_e GetKp(float *_Kp);
    RC_e GetKi(float *_Ki);
    RC_e GetKd(float *_Kd);

    RC_e SetKp(float _kp);
    RC_e SetKi(float _ki);
    RC_e SetKd(float _kd);

private:
    /*Variable*/
    float Prev_error = 0.0f;     //  e(k-1)
    float AccIntegral = 0.0f;
    /*functions*/
    float UpdateP(float error);  
    float UpdateI(float error);  
    float UpdateD(float error, float Prev_error);  
    float ComputeError(float _PositionMesured);
};

#endif // PID_MANAGER_H