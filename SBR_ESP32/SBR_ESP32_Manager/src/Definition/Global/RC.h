/**
 * @file RC.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Result Codes
 * @version 1.0
 * @date 08.02.2023
 * 
 */

#ifndef RC_H
#define RC_H

/**
 * @brief Enumeration for Result codes
 * 
 */
enum RC_e {
	SUCCESS = 0,                    /**@brief Operation Successful*/
	ERROR,                          /**@brief Error */
	ERROR_NULL_POINTER,             /**@brief Error null pointer */
	ERROR_SIZE_BUFFER,              /**@brief Error size buffer */
	ERROR_CRC,		                /**@brief Error CRC Validation */
    ERROR_WIFI_CONNECTION,          /**@brief Error Wifi connection */
    ERROR_INVALID_REG_ID,           /**@brief Error Invalid register ID */
    ERROR_INVALID_SUBSCRIBER,       /**@brief Error Invalid subscriber */
    ERROR_MAX_NODE_REQUEST_INDEX,   /**@brief Error Max slave request index reached */
    ERROR_MAX_NUMBER_SUBSCRIBERS,   /**@brief Error Max number of subscribers reached */
};


#endif /* RC_H */