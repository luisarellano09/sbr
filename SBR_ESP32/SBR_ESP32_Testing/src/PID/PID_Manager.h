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




private:

};

#endif // PID_MANAGER_H