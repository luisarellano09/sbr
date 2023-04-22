/**
 * @file GlobalConfig.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Global Config
 * 
 */

#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H

//=====================================================================================================
/**
 * @brief Number of Bytes of the Request
 * 
 */
#define NODE_REQUEST_SIZE  (uint8_t) 8u 

//=====================================================================================================
/**
 * @brief Request Buffer size 
 * 
 */
#define REQUEST_BUFFER_SIZE (uint16_t) 1000u

//=====================================================================================================
/**
 * @brief Node WatchDog Timeout
 * 
 */
#define NODE_WATCHDOG_TIMEOUT 3000

//=====================================================================================================
/**
 * @brief Node WatchDog feed
 * 
 */
#define NODE_WATCHDOG_FEED 1000

#endif /* GLOBALCONFIG_H */