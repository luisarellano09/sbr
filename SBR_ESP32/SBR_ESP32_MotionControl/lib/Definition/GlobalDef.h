/**
 * @file GlobalDef.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Global definitions of SBR
 * @version 1.0
 * @date 14-06-2020
 * 
 *
 */

#ifndef GLOBALDEF_H
#define GLOBALDEF_H

#include <Arduino.h>

/*******************************************************************************************************************************************
 *  												RESULT CODE
 *******************************************************************************************************************************************/

/**
 * @brief Enumeration for Result codes
 * 
 */
enum RC_e{
	SUCCESS = 0,                /**< \brief Operation Successful*/
	ERROR,                      /**< \brief Error */
	ERROR_NULL_POINTER,         /**< \brief Error null pointer */
	ERROR_SIZE_BUFFER,          /**< \brief Error size buffer */
	ERROR_CRC,		            /**< \brief Error CRC Validation */
    ERROR_WIFI_CONNECTION,      /**< \brief Error Wifi connection */
    ERROR_NO_CS,                /**< \brief Error No Chip Select */
    ERROR_INVALID_REG_ID        /**< \brief Error Invalid register ID */
} ;


/*******************************************************************************************************************************************
 *  												SBR REGISTER ID ADDRESSES
 *******************************************************************************************************************************************/

/**
 * @brief Enumeration for SBR registers IDs. The number defines the register offset
 * 
 */
enum COM_REQUEST_REG_ID_e{
    REQUEST_INITIAL_RED_ID = 10,
	R0,                     /**< \brief R0 */
    R1,	                    /**< \brief R1 */
    R2,	                    /**< \brief R2 */
    R3,	                    /**< \brief R3 */
    R4,	                    /**< \brief R4 */
    R5,	                    /**< \brief R5 */
    R6,	                    /**< \brief R6 */
    R7,	                    /**< \brief R7 */
    R8,	                    /**< \brief R8 */
    R9,	                    /**< \brief R9 */
    R10,	                /**< \brief R10 */
	REQUEST_REG_LENGTH      /**< \brief Number of registers */					            
};

/*******************************************************************************************************************************************
 *  												COMMUNICATION REQUEST
 *******************************************************************************************************************************************/

/**
 * @brief Defines if a read or write operation shall be performed
 * 
 */
enum COM_REQUEST_TYPE_e{
	READ	    =0x0,		        /**< \brief Read operation*/
	WRITE		=0x1,				/**< \brief Write operation*/
    STOP		=0x2,				/**< \brief STOP operation*/
    NONE      	=0x3,				/**< \brief None operation*/                      
};

/**
 * @brief Structure to define the communication request
 * 
 */
struct COM_REQUEST_st
{
    uint8_t    comRequestType;      /**< Request type: Read or Write. */
    uint16_t   comRequestRegId;     /**< Request ID. */
    uint32_t   data;                /**< Data payload. */
    uint16_t   CRC;                 /**< Frame consistency. */
};

#endif /* GLOBALDEF_H */