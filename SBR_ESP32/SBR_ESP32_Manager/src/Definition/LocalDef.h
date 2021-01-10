/**
 * @file LocalDef.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Global definitions of SBR
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
#define ESP32_HOSTNAME "SBR_ESP32_Manager"

// ========================== SPI MASTER ========================

/**
 * @brief SPI Clock Speed Hz
 * 
 */
#define SPI_CLOCK (uint32_t) 12000000

/**
 * @brief MOSI Pin: Master Output - Slave Input
 * 
 */
#define MO   22     // verde

/**
 * @brief MISO Pin: Master Input - Slave Output
 * 
 */
#define MI   23     // azul

/**
 * @brief Master Clock Pin
 * 
 */
#define MCLK 19     // morado

// ========================== SPI MANAGER =======================

/**
 * @brief Number of Stop or Empty Request during reading request from slaves
 * 
 */
#define SPI_MANAGER_NUMBER_STOP_EMPTY (uint8_t)3u

// ========================== SPI SLAVES ==========================

/**
 * @brief Chip Select Pin Node01
 * 
 */
#define ESP32_NODE01_CS   18

/**
 * @brief Chip Select Pin Node02
 * 
 */
#define ESP32_NODE02_CS   5

/**
 * @brief Chip Select Pin Node03
 * 
 */
#define ESP32_NODE03_CS   17

/*******************************************************************************************************************************************
 *  												ENUMERATIONS
 *******************************************************************************************************************************************/

/**
 * @brief Enumeration for Devices
 * 
 */
enum Devices_e {
    DEVICE_NONE = -1,       /**< \brief None*/
	DEVICE_ESP32_NODE01,    /**< \brief ESP32 Node01*/
	DEVICE_ESP32_NODE02,    /**< \brief ESP32 Node02*/
	//DEVICE_ESP32_NODE03,    /**< \brief ESP32 Node03*/
    DEVICE_LINUX,           /**< \brief Linux controller*/
    DEVICE_LENGTH           /**< \brief Length*/
};

//=====================================================================================================
/**
 * @brief Enumeration for ESP32 SPI SLAVES
 * 
 */
enum ESP32_SPI_Slave_e {
	SLAVE_NODE01 = 0,   /**< \brief ESP32 Node01*/
	SLAVE_NODE02,       /**< \brief ESP32 Node02*/
	//SLAVE_NODE03,       /**< \brief ESP32 Node03*/
    SLAVE_LENGTH        /**< \brief Length*/
};


#endif /* LOCALDEF_H */