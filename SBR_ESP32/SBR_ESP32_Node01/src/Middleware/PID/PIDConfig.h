/**
 * @file PIDConfig.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Config for the PID Class
 * @date 28.03.2023
 * 
 */

#ifndef PIDCONFIG_H
#define PIDCONFIG_H

/*******************************************************************************************************************************************
 *  												ENUMERATION
 *******************************************************************************************************************************************/

/**
 * @brief Enumeration for the PID Direction 
 * 
 */
enum PIDDirection_e {
    DIRECT = 0,
	INVERT
};


//=====================================================================================================
/**
 * @brief Enumeration for the PID mode.
 * 
 */
enum PIDMode {
    STOP = 0,
    AUTO
};

#endif /* PIDCONFIG_H */