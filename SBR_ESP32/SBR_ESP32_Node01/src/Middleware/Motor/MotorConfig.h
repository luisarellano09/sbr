/**
 * @file MotorConfig.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Config for the Motor Class
 * @date 26.02.2023
 * 
 */

#ifndef MOTORCONFIG_H
#define MOTORCONFIG_H

/*******************************************************************************************************************************************
 *  												ENUMERATION
 *******************************************************************************************************************************************/

/**
 * @brief Enumeration for the PWM Channel
 * 
 */
enum PWMChannel_e {
    PWM1 = 0,
	PWM2,
	PWM3,
    PWM4,
    PWM5,
    PWM6,
    PWM7,
    PWM8,
    PWM9,
    PWM10,
    PWM11,
    PWM12,
    PWM13,
    PWM14,
    PWM15
};


//=====================================================================================================
/**
 * @brief Enumeration for the Motor direction.
 * 
 */
enum MotorDirection_e {
    NORMAL = 0,
    INVERTED
};

#endif /* MOTORCONFIG_H */