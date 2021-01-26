/**
 * @file GlobalDef.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Global definitions of SBR
 * @version 2.0
 * @date 09.01.2021
 * 
 */

#ifndef GLOBALDEF_H
#define GLOBALDEF_H

#include <Arduino.h>

/*******************************************************************************************************************************************
 *  												DEFINE
 *******************************************************************************************************************************************/

/**
 * @brief Number of Bytes of the Request
 * 
 */
#define NODE_REQUEST_SIZE  (uint8_t) 8u 

//=====================================================================================================
/**
 * @brief REQUEST_BUFFER_SIZE
 * 
 */
#define REQUEST_BUFFER_SIZE (uint16_t) 1000u

/*******************************************************************************************************************************************
 *  												ENUMERATION
 *******************************************************************************************************************************************/

/**
 * @brief Enumeration for Result codes
 * 
 */
enum RC_e {
	SUCCESS = 0,                    /** Operation Successful*/
	ERROR,                          /** Error */
	ERROR_NULL_POINTER,             /** Error null pointer */
	ERROR_SIZE_BUFFER,              /** Error size buffer */
	ERROR_CRC,		                /** Error CRC Validation */
    ERROR_WIFI_CONNECTION,          /** Error Wifi connection */
    ERROR_INVALID_REG_ID,           /** Error Invalid register ID */
    ERROR_INVALID_SUBSCRIBER,       /** Error Invalid subscriber */
    ERROR_MAX_NODE_REQUEST_INDEX,   /** Error Max slave request index reached */
    ERROR_MAX_NUMBER_SUBSCRIBERS,   /** Error Max number of subscribers reached */
};

//=====================================================================================================
/**
 * @brief Enumeration for Devices
 * 
 */
enum DEVICE_e {
    NONE_DEVICE = 0,    /** None*/
	ESP32_NODE01,       /** ESP32 Node01*/
	ESP32_NODE02,       /** ESP32 Node02*/
	//ESP32_NODE03,     /** ESP32 Node03*/
    BROADCAST_ESP32,    /** ESP32 Broadcast*/
    LINUX,              /** Linux*/
    MANAGER,            /** Manager*/
    LENGTH_DEVICE       /** Length*/
};

//=====================================================================================================
/**
 * @brief Defines if a read or write operation shall be performed
 * 
 */
enum COM_REQUEST_TYPE_e {
    NONE = 0,   /** None operation*/   
	READ,	    /** Read operation*/
	WRITE,		/** Write operation*/                   
};

//=====================================================================================================
/**
 * @brief Enumeration for SBR registers IDs. The number defines the register offset
 * 
 */
enum COM_REQUEST_REG_ID_e {
    NONE_REG_ID = 0,
	REGISTER_01,                        /** REGISTER 01 */
    REGISTER_02,	                    /** REGISTER 02 */
    REGISTER_03,	                    /** REGISTER 03 */
    REGISTER_04,	                    /** REGISTER 04 */
    REGISTER_05,	                    /** REGISTER 05 */
    REGISTER_06,	                    /** REGISTER 06 */
    REGISTER_07,	                    /** REGISTER 07 */
    REGISTER_08,	                    /** REGISTER 08 */
    REGISTER_09,	                    /** REGISTER 09 */
    REGISTER_10,	                    /** REGISTER 10 */
    REGISTER_11,                        /** REGISTER 11 */
    REGISTER_12,	                    /** REGISTER 12 */
    REGISTER_13,	                    /** REGISTER 13 */
    REGISTER_14,	                    /** REGISTER 14 */
    REGISTER_15,	                    /** REGISTER 15 */
    REGISTER_16,	                    /** REGISTER 16 */
    REGISTER_17,	                    /** REGISTER 17 */
    REGISTER_18,	                    /** REGISTER 18 */
    REGISTER_19,	                    /** REGISTER 19 */
    REGISTER_20,	                    /** REGISTER 20 */
    REGISTER_21,                        /** REGISTER 21 */
    REGISTER_22,	                    /** REGISTER 22 */
    REGISTER_23,	                    /** REGISTER 23 */
    REGISTER_24,	                    /** REGISTER 24 */
    REGISTER_25,	                    /** REGISTER 25 */
    REGISTER_26,	                    /** REGISTER 26 */
    REGISTER_27,	                    /** REGISTER 27 */
    REGISTER_28,	                    /** REGISTER 28 */
    REGISTER_29,	                    /** REGISTER 29 */
    REGISTER_30,                        /** REGISTER 30 */
    REGISTER_31,                        /** REGISTER 31 */
    REGISTER_32,	                    /** REGISTER 32 */
    REGISTER_33,	                    /** REGISTER 33 */
    REGISTER_34,	                    /** REGISTER 34 */
    REGISTER_35,	                    /** REGISTER 35 */
    REGISTER_36,	                    /** REGISTER 36 */
    REGISTER_37,	                    /** REGISTER 37 */
    REGISTER_38,	                    /** REGISTER 38 */
    REGISTER_39,	                    /** REGISTER 39 */
    REGISTER_40,	                    /** REGISTER 40 */
    REGISTER_41,                        /** REGISTER 41 */
    REGISTER_42,	                    /** REGISTER 42 */
    REGISTER_43,	                    /** REGISTER 43 */
    REGISTER_44,	                    /** REGISTER 44 */
    REGISTER_45,	                    /** REGISTER 45 */
    REGISTER_46,	                    /** REGISTER 46 */
    REGISTER_47,	                    /** REGISTER 47 */
    REGISTER_48,	                    /** REGISTER 48 */
    REGISTER_49,	                    /** REGISTER 49 */
    REGISTER_50,	                    /** REGISTER 50 */
    REGISTER_51,                        /** REGISTER 51 */
    REGISTER_52,	                    /** REGISTER 52 */
    REGISTER_53,	                    /** REGISTER 53 */
    REGISTER_54,	                    /** REGISTER 54 */
    REGISTER_55,	                    /** REGISTER 55 */
    REGISTER_56,	                    /** REGISTER 56 */
    REGISTER_57,	                    /** REGISTER 57 */
    REGISTER_58,	                    /** REGISTER 58 */
    REGISTER_59,	                    /** REGISTER 59 */
    REGISTER_60,	                    /** REGISTER 60 */
    REGISTER_61,                        /** REGISTER 61 */
    REGISTER_62,	                    /** REGISTER 62 */
    REGISTER_63,	                    /** REGISTER 63 */
    REGISTER_64,	                    /** REGISTER 64 */
    REGISTER_65,	                    /** REGISTER 65 */
    REGISTER_66,	                    /** REGISTER 66 */
    REGISTER_67,	                    /** REGISTER 67 */
    REGISTER_68,	                    /** REGISTER 68 */
    REGISTER_69,	                    /** REGISTER 69 */
    REGISTER_70,	                    /** REGISTER 70 */
    REGISTER_71,                        /** REGISTER 71 */
    REGISTER_72,	                    /** REGISTER 72 */
    REGISTER_73,	                    /** REGISTER 73 */
    REGISTER_74,	                    /** REGISTER 74 */
    REGISTER_75,	                    /** REGISTER 75 */
    REGISTER_76,	                    /** REGISTER 76 */
    REGISTER_77,	                    /** REGISTER 77 */
    REGISTER_78,	                    /** REGISTER 78 */
    REGISTER_79,	                    /** REGISTER 79 */
    REGISTER_80,	                    /** REGISTER 80 */
    REGISTER_81,                        /** REGISTER 81 */
    REGISTER_82,	                    /** REGISTER 82 */
    REGISTER_83,	                    /** REGISTER 83 */
    REGISTER_84,	                    /** REGISTER 84 */
    REGISTER_85,	                    /** REGISTER 85 */
    REGISTER_86,	                    /** REGISTER 86 */
    REGISTER_87,	                    /** REGISTER 87 */
    REGISTER_88,	                    /** REGISTER 88 */
    REGISTER_89,	                    /** REGISTER 89 */
    REGISTER_90,                        /** REGISTER 90 */
    REGISTER_91,                        /** REGISTER 91 */
    REGISTER_92,	                    /** REGISTER 92 */
    REGISTER_93,	                    /** REGISTER 93 */
    REGISTER_94,	                    /** REGISTER 94 */
    REGISTER_95,	                    /** REGISTER 95 */
    REGISTER_96,	                    /** REGISTER 96 */
    REGISTER_97,	                    /** REGISTER 97 */
    REGISTER_98,	                    /** REGISTER 98 */
    REGISTER_99,	                    /** REGISTER 99 */
    REGISTER_100,	                    /** REGISTER 100 */
	LENGTH_REG_ID = 1000                /** Number of registers */					            
};

#endif /* GLOBALDEF_H */