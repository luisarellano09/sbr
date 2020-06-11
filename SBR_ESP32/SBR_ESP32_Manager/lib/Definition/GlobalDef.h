/**
 * \file GlobalDef.h
 * \author Luis Arellano
 * \date 13 Jun 2020
 * \todo .
 *
 * \brief All globla definitions of SBR Project.
 * 
 * Changes
 * 07.06.2020: [LA] COM_REQUEST_REG_ID_e update
 * 03.05.2020: [LA] RC_e update
 * 16.04.2020: [LA] RC_e update 
 * 14.04.2020: [JS] new ERRORS ENUM added 
 * 14.04.2020: [LA] Communication enums and struct
 * 14.04.2020: [JS] Comment header was added.
 * 13.04.2020: [LA] Doc was created
 *
 *
 */
#ifndef GLOBALDEF_H
#define GLOBALDEF_H

#include <Arduino.h>

/*******************************************************************************************************************************************
 *  												RESULT CODE
 *******************************************************************************************************************************************/

/** \brief  Enumeration for TLF errors.  */
enum RC_e{
	SUCCESS						= 0,                                /**< \brief Operation Successful				*/
	ERROR,                                                          /**< \brief Error 						        */
	ERROR_NULL_POINTER,                                             /**< \brief Error null pointer					*/
	ERROR_SIZE_BUFFER,                                             	/**< \brief Error size buffer					*/
	ERROR_CRC,		                                             	/**< \brief Error CRC Validation				*/
    ERROR_WIFI_CONNECTION,                                          /**< \brief Error Wifi connection   			*/
    ERROR_NO_CS                                                     /**< \brief Error No Chip Select   			    */
} ;


/*******************************************************************************************************************************************
 *  												SBR REGISTER ID ADDRESSES
 *******************************************************************************************************************************************/

/** \brief  Enumeration for SBR registers IDs. The number defines the register offset */
enum COM_REQUEST_REG_ID_e{
	R0 = 0,	        /**< \brief R0 */
    R1,	            /**< \brief R1 */
    R2,	            /**< \brief R2 */
    R3,	            /**< \brief R3 */
    R4,	            /**< \brief R4 */
    R5,	            /**< \brief R5 */
    R6,	            /**< \brief R6 */
    R7,	            /**< \brief R7 */
    R8,	            /**< \brief R8 */
    R9,	            /**< \brief R9 */
    R10,	        /**< \brief R10 */
	REQUEST_REG_LENGTH					            
};


/*******************************************************************************************************************************************
 *  												COMMUNICATION REQUEST
 *******************************************************************************************************************************************/

/** \brief Defines if a read or write operation shall be performed. */
enum COM_REQUEST_TYPE_e{
	READ							=0x0,							/**< \brief Read operation*/
	WRITE							=0x1,							/**< \brief Write operation*/
    STOP							=0x2,							/**< \brief STOP operation*/
    NONE      						=0x3,							/**< \brief None operation*/                      
};


/** \brief Structure to define the communication request. */
struct COM_REQUEST_st
{
    uint8_t    comRequestType;      /**< Request type: Read or Write. */
    uint16_t   comRequestRegId;     /**< Request ID. */
    uint32_t   data;                /**< Data payload. */
    uint16_t   CRC;                 /**< Frame consistency. */
};


#endif /* GLOBALDEF_H */