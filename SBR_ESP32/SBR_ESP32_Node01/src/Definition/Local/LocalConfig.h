/**
 * @file LocalConfig.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Local Config
 * @version 1.0
 * @date 16.10.2022
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
 * @brief MNODE_ESP32s_RX
 * 
 */
#define NODE_ESP32s_RX   21


#endif /* LOCALCONFIG_H */