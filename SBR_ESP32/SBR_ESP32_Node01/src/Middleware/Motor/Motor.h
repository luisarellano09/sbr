/**
 * @file Motor.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to control a motor
 * @date 26.02.2023
 * 
 */

#ifndef MOTOR_H
#define MOTOR_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "MotorDef.h"
#include <Arduino.h>
#include "../../Definition/Global/RC.h"

/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to control a motor
 * 
 */
class Motor {
public:  

    PWMChannel_e m_pwmChannel;      /**@brief Request type: Read or Write */
    uint8_t m_pwmPin;               /**@brief PWM Pin */
    double m_frequency;             /**@brief PWM Frecuency */
    uint8_t m_resolution;           /**@brief PWM resolution 1-20 bits */
    double m_offset;                /**@brief Correction offset */
    uint8_t m_dirPin;               /**@brief Pin to control the direction */
    MotorDirection_e m_direction;   /**@brief Invert the motor direction 0=Normal, 1=Invert */


    /**
     * @brief Construct a new Motor object
     * 
     * @param pwmChannel PWM Channel
     * @param pwmPin PWM Pin
     * @param frequency PWM frequency 
     * @param resolution PWM resolution 1-20 bits
     * @param offset Correction offset 
     * @param dirPin GPIO PIN to control the motor direction
     * @param direction Direction of the Motor
     */
    Motor(PWMChannel_e pwmChannel, uint8_t pwmPin, double frequency, uint8_t resolution, double offset, uint8_t dirPin, MotorDirection_e direction = MotorDirection_e::NORMAL);

    /**
     * @brief Destructor
     * 
     */
    ~Motor();

    /**
     * @brief Set the Speed of the motor
     * 
     * @param speed Speed -100% to 100%
     * @return RC_e Result code
     */
    RC_e SetSpeed(double speed);

    /**
     * @brief Stop the motor
     * 
     * @return RC_e Result code
     */
    RC_e Stop();

    /**
     * @brief Function to print the motor status
     * 
     * @return RC_e Result code
     */
    RC_e Print();  

private:

    /**
     * @brief Initializate the Motor
     * 
     * @return RC_e Result code
     */
    RC_e Init();

};

#endif // MOTOR_H