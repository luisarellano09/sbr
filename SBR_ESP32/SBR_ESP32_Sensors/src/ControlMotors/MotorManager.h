/**
 * @file IMUManager.h
 * @author Jorge Salgado (jorgesalgado23@gmail.com)
 * @brief Class to Manage the 2 motors
 * @version 1.0
 * @date 17-11-2020
 * 
 * 
 */

#ifndef MOTOR_MANAGER_H
#define MOTOR_MANAGER_H

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include "../Definition/GlobalDef.h"


#define PWM_CHANNEL_0 0x0
#define PWM_CHANNEL_1 0x1
#define F32PWM_FREQUENCY (float)1000u
#define U8PWM_RESOLUTION (uint8_t)8u
/*******************************************************************************************************************************************
 *  												IMUManager Class
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the IMU in this case BNO080
 * 
 */
class MotorManager{

public: 
    /*Global Variables*/

    /**
     * @brief Construct a new Motor Manager object
     * 
     * @param 
     * @param 
     * @param 
     */
    MotorManager();

    /**
     * @brief Destroy the Motor Manager object
     * 
     */
    ~MotorManager();

    /**
     * @brief Connect to Motor services
     * 
     * @return RC_e Result code
     */
    RC_e Begin(uint8_t u8DIR1, uint8_t u8DIR2, uint8_t u8PIN_PWM1,uint8_t u8PIN_PWM2);
    
    RC_e PWM1(int8_t i8DutyCyle);

    RC_e PWM2(int8_t i8DutyCyle);



private:
    uint8_t u8PinDir1;
    uint8_t u8PinDir2;

};

#endif // MOTOR_MANAGER_H