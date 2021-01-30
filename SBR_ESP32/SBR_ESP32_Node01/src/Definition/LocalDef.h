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

// ========================== WIFI ==========================

/**
 * @brief Wifi name
 * 
 */
#define WIFI_SSID "ap01"

/**
 * @brief Wifi password
 * 
 */
#define WIFI_PASSWORD "12345678"

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
#define NODE_ESP32s_BAUDRATE 921600 //921600

/**
 * @brief NODE_ESP32s_TX
 * 
 */
#define NODE_ESP32s_TX   22

/**
 * @brief MNODE_ESP32s_RX
 * 
 */
#define NODE_ESP32s_RX   23


#endif /* LOCALDEF_H */