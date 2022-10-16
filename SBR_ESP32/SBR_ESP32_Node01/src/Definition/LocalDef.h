/**
 * @file LocalDef.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Local definitions of SBR
 * @version 2.0
 * @date 09.01.2021
 * 
 */

#ifndef LOCALDEF_H
#define LOCALDEF_H

#include <Arduino.h>

/*******************************************************************************************************************************************
 *  												DEFINE
 *******************************************************************************************************************************************/

// ========================== NODE_ID =======================

#define NODE_ID DEVICE_e::ESP32_NODE01

// ========================== WIFI ==========================

/**
 * @brief Wifi name
 * 
 */
#define WIFI_SSID "sbrap"

/**
 * @brief Wifi password
 * 
 */
#define WIFI_PASSWORD "La123456"

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


#endif /* LOCALDEF_H */