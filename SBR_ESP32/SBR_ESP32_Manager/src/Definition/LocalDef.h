/**
 * \file LocalDef.h
 * \author Luis Arellano
 * \date 13 Jun 2020
 * \todo .
 *
 * \brief All globla definitions of SBR Project.
 * 
 * Changes
 * 03.05.2020: [LA] File was created
 *
 *
 */
#ifndef LOCALDEF_H
#define LOCALDEF_H

#include <Arduino.h>

/*******************************************************************************************************************************************
 *  												DEFINE
 *******************************************************************************************************************************************/

// ============ WIFI =================
#define WIFI_SSID "ap01"
#define WIFI_PASSWORD "12345678"

// ============ HOSTNAME =================
#define ESP32_HOSTNAME "SBR_ESP32_Manager"

// ============ LOGGER =================
#define LOGGER_PORT (uint16_t)4000
#define LOGGER_HOST "ubuntudev"

// ============ SPI MASTER =================
#define SPI_CLOCK (uint32_t)12000000
#define MO   22     // verde
#define MI   23     // azul
#define MCLK 19     // morado

// ============ SPI MANAGER =================
#define SPI_MANAGER_REQUEST_SIZE  (uint8_t)8u                 /*Number of Bytes of the Frame*/
#define SPI_MANAGER_NUMBER_SLAVES (uint8_t)1u

// ============ SPI SLAVES =================
#define SPI_SLAVE_REQUESTS_ARRAY_SIZE (uint8_t) 100u
#define MOTION_CS   18     // plomo


/*******************************************************************************************************************************************
 *  												ENUMERATIONS
 *******************************************************************************************************************************************/

/** \brief  Enumeration for ESP32.  */
enum Devices_e{
    DEVICE_NONE         =-1,
	DEVICE_MOTION	    = 0,        /**< \brief ESP32 Motion Control*/
	DEVICE_SENSOR,                 /**< \brief ESP32 Sensors*/
	DEVICE_UTIL,                   /**< \brief ESP32 Util*/
    DEVICE_LINUX,                  /**< \brief Linux controller*/
    DEVICE_LENGTH
};

/** \brief  Enumeration for ESP32.  */
enum ESP32_Slave_e{
	SLAVE_MOTION  = Devices_e::DEVICE_MOTION,
	SLAVE_SENSOR  = Devices_e::DEVICE_SENSOR,
	SLAVE_UTIL    = Devices_e::DEVICE_UTIL,
    SLAVE_LENGTH
};


#endif /* LOCALDEF_H */