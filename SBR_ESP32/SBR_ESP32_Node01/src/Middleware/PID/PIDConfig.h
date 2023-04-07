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
    PID_DIRECTION_DIRECT = 0,
	PID_DIRECTION_INVERT
};


//=====================================================================================================
/**
 * @brief Enumeration for the PID mode.
 * 
 */
enum PIDMode {
    PID_STOP = 0,
    PID_START
};

#endif /* PIDCONFIG_H */