/**
 * @file LocalConfig.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Local Config
 * 
 */

#ifndef LOCALCONFIG_H
#define LOCALCONFIG_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include "../Global/Devices.h"


/*******************************************************************************************************************************************
 *  												DEFINE
 *******************************************************************************************************************************************/

// ========================== NODE_ID =======================
/**
 * @brief Node ID
 * 
 */
#define NODE_ID DEVICE_e::ESP32_NODE01


// ========================== HOSTNAME =======================
/**
 * @brief Hostname of the ESP32
 * 
 */
#define ESP32_HOSTNAME "SBR_ESP32_Node01"


// ========================== NODE ESP32s =====================
/**
 * @brief NODE_ESP32s_BAUDRATE
 * 
 */
#define NODE_ESP32s_BAUDRATE 460800

/**
 * @brief NODE_ESP32s_TX
 * 
 */
#define NODE_ESP32s_TX   19

/**
 * @brief NODE_ESP32s_RX
 * 
 */
#define NODE_ESP32s_RX   21


// ========================== MOTORS =====================
/**
 * @brief PWM GPIO of the left Motor
 * 
 */
#define MOTOR_LEFT_PWM_GPIO 4

/**
 * @brief PWM GPIO of the right Motor
 * 
 */
#define MOTOR_RIGHT_PWM_GPIO 15

/**
 * @brief GPIO to control the direction of the left Motor
 * 
 */
#define MOTOR_LEFT_DIR_GPIO 5

/**
 * @brief GPIO to control the direction of the right Motor
 * 
 */
#define MOTOR_RIGHT_DIR_GPIO 2

/**
 * @brief Motor PWM Frequency
 * 
 */
#define MOTOR_PWM_FREQUENCY 20000

/**
 * @brief Motor PWM Resolution
 * 
 */
#define MOTOR_PWM_RESOLUTION 10

/**
 * @brief Motor left Offset
 * 
 */
#define MOTOR_LEFT_OFFSET (double) 3.0

/**
 * @brief Motor right Offset
 * 
 */
#define MOTOR_RIGHT_OFFSET (double) 3.0


// ========================== ENCODERS =====================
/**
 * @brief GPIO of the Channel A of left Encoder
 * 
 */
#define ENCODER_LEFT_CHANNEL_A_GPIO 34

/**
 * @brief GPIO of the Channel B of left Encoder
 * 
 */
#define ENCODER_LEFT_CHANNEL_B_GPIO 35

/**
 * @brief GPIO of the Channel A of right Encoder
 * 
 */
#define ENCODER_RIGHT_CHANNEL_A_GPIO 22

/**
 * @brief GPIO of the Channel B of right Encoder
 * 
 */
#define ENCODER_RIGHT_CHANNEL_B_GPIO 23


// ========================== IMU =====================
/**
 * @brief IMU CS
 * 
 */
#define IMU_CS_GPIO 32

/**
 * @brief IMU WAK
 * 
 */
#define IMU_WAK_GPIO 18

/**
 * @brief IMU INT
 * 
 */
#define IMU_INT_GPIO 26

/**
 * @brief IMU RST
 * 
 */
#define IMU_RST_GPIO 27

/**
 * @brief IMU SPI PORT SPEED
 * 
 */
#define IMU_SPI_PORT_SPEED 3000000

/**
 * @brief IMU CLK
 * 
 */
#define IMU_CLK_GPIO 14

/**
 * @brief IMU MISO
 * 
 */
#define IMU_MISO_GPIO 25

/**
 * @brief IMU MOSI
 * 
 */
#define IMU_MOSI_GPIO 13

/**
 * @brief IMU PS0
 * 
 */
#define IMU_PS0_GPIO 18

/**
 * @brief IMU PS1
 * 
 */
#define IMU_PS1_GPIO 12


// ========================== ODOMETRY =====================
/**
 * @brief ODOMETRY__WHEEL_RADIO
 * 
 */
#define ODOMETRY_WHEEL_RADIO (double)0.035 

/**
 * @brief ODOMETRY_DISTANCE_WHEELS
 * 
 */
#define ODOMETRY_DISTANCE_WHEELS (double)0.231

/**
 * @brief ODOMETRY_TICKS_REVOLUTION
 * 
 */
#define ODOMETRY_TICKS_REVOLUTION 960 

#endif /* LOCALCONFIG_H */