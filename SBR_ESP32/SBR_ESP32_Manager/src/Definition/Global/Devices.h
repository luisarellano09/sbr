/**
 * @file Devices.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Devices
 * 
 */

#ifndef DEVICES_H
#define DEVICES_H

/**
 * @brief Enumeration for Devices
 * 
 */
enum DEVICE_e {
    NONE_DEVICE = 0,    /**@brief None */
	ESP32_NODE01,       /**@brief ESP32 Node01 */
	ESP32_NODE02,       /**@brief ESP32 Node02 */
    LINUX,              /**@brief Linux */
    NODE_MANAGER,       /**@brief Node Manager */
    LENGTH_DEVICE,      /**@brief Length */
    NEXT_ONE            /**@brief The next device */
};


#endif /* DEVICES_H */