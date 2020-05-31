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
#define ESP32_HOSTNAME "SBR_ESP32_MotionControl"

// ============ LOGGER =================
#define LOGGER_PORT (uint16_t)4000
#define LOGGER_HOST "ubuntudev"

// ============ SPI SLAVE =================
#define SO   (gpio_num_t)22     // azul
#define SI   (gpio_num_t)23     // verde
#define SCLK (gpio_num_t)19     // morado
#define SS   (gpio_num_t)18     // plomo

// ============ SPI MANAGER =================
#define SPI_MANAGER_REQUEST_SIZE  (uint8_t)8u                 /*Number of Bytes of the Frame*/
#define SPI_SLAVE_REQUESTS_ARRAY_SIZE (uint8_t) 100u


#endif /* LOCALDEF_H */