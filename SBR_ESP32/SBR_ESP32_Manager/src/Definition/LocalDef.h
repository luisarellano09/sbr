/**
 * @file LocalDef.h
 * @author Luis Arellano
 * @brief Definitions of ESP32 Project.
 * @version 1.0
 * @date 2020-06-13
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

// ========================== LOGGER ==========================

/**
 * @brief Logger Port
 * 
 */
#define LOGGER_PORT (uint16_t)4000

/**
 * @brief Logger Host
 * 
 */
#define LOGGER_HOST "ubuntudev"

// ========================== SPI MASTER ========================

/**
 * @brief SPI Clock Speed Hz
 * 
 */
#define SPI_CLOCK (uint32_t)12000000

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
 * @brief Number of Bytes of the Request
 * 
 */
#define SPI_MANAGER_REQUEST_SIZE  (uint8_t)8u  

/**
 * @brief Number of Stop or Empty Request during reading request from slaves
 * 
 */
#define SPI_MANAGER_NUMBER_STOP_EMPTY (uint8_t)20u

// ========================== SPI SLAVES ==========================

/**
 * @brief Max length of requests to send to the a slave
 * 
 */
#define SPI_SLAVE_REQUESTS_ARRAY_SIZE (uint8_t) 100u

/**
 * @brief Chip Select Pin Motion
 * 
 */
#define MOTION_CS   18     // plomo

/**
 * @brief Chip Select Pin Sensors
 * 
 */
#define SENSORS_CS   5     // white

/*******************************************************************************************************************************************
 *  												ENUMERATIONS
 *******************************************************************************************************************************************/

/**
 * @brief Enumeration for Devices
 * 
 */
enum Devices_e{
    DEVICE_NONE         =-1,        /**< \brief None*/
	DEVICE_MOTION	    = 0,        /**< \brief ESP32 Motion Control*/
	DEVICE_SENSOR,                  /**< \brief ESP32 Sensors*/
	DEVICE_UTIL,                    /**< \brief ESP32 Util*/
    DEVICE_LINUX,                   /**< \brief Linux controller*/
    DEVICE_LENGTH                   /**< \brief Length*/
};

/**
 * @brief Enumeration for ESP32
 * 
 */
enum ESP32_Slave_e{
	SLAVE_MOTION  = Devices_e::DEVICE_MOTION,   /**< \brief ESP32 Motion Control*/
	SLAVE_SENSOR  = Devices_e::DEVICE_SENSOR,   /**< \brief ESP32 Sensors*/
	SLAVE_UTIL    = Devices_e::DEVICE_UTIL,     /**< \brief ESP32 Util*/
    SLAVE_LENGTH                                /**< \brief Length*/
};


#endif /* LOCALDEF_H */