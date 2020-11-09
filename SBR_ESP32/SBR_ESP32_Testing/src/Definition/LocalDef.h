/**
 * @file LocalDef.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Definitions of ESP32 Project.
 * @version 1.0
 * @date 14-06-2020
 * 
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
#define ESP32_HOSTNAME "SBR_ESP32_Sensors"

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

// ========================== SPI SLAVE ========================

/**
 * @brief Slave Output Pin
 * 
 */
#define SO   (gpio_num_t)22     // azul

/**
 * @brief Slave Input Pin
 * 
 */
#define SI   (gpio_num_t)23     // verde

/**
 * @brief Clock Pin
 * 
 */
#define SCLK (gpio_num_t)19     // morado

/**
 * @brief Slave Select Pin
 * 
 */
#define SS   (gpio_num_t)18     // plomo

// ========================== SPI MANAGER =======================

/**
 * @brief Number of Bytes of the Request
 * 
 */
#define SPI_MANAGER_REQUEST_SIZE  (uint8_t)8u  


/**
 * @brief Max length of requests to send to the a slave
 * 
 */
#define SPI_SLAVE_REQUESTS_ARRAY_SIZE (uint8_t) 100u


#endif /* LOCALDEF_H */