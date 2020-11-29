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

#define P_Gain  11.0
#define I_Gain  1.0
#define D_Gain  10.0

#define PositionDesired     (float)0.0

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
    float Prev_error = 0.0;
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

    float UpdatePID(float PositionMesured);

private:
    float UpdateP(float error);  
    float UpdateI(float error);  
    float UpdateD(float error, float Prev_error);  
};

#endif // PID_MANAGER_H