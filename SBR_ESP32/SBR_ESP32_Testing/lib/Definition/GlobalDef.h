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
//#define PI  (float)3.141592653
#define FACTOR_CONV_RAD_TO_DEG	(float)57.295779513
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
	TEST_R01,                       /**< \brief Testing register R01 */
    TEST_R02,	                    /**< \brief Testing register R02 */
    TEST_R03,	                    /**< \brief Testing register R03 */
    TEST_R04,	                    /**< \brief Testing register R04 */
    TEST_R05,	                    /**< \brief Testing register R05 */
    TEST_R06,	                    /**< \brief Testing register R06 */
    TEST_R07,	                    /**< \brief Testing register R07 */
    TEST_R08,	                    /**< \brief Testing register R08 */
    TEST_R09,	                    /**< \brief Testing register R09 */
    TEST_R10,	                    /**< \brief Testing register R10 */
    TEST_R11,                       /**< \brief Testing register R11 */
    TEST_R12,	                    /**< \brief Testing register R12 */
    TEST_R13,	                    /**< \brief Testing register R13 */
    TEST_R14,	                    /**< \brief Testing register R14 */
    TEST_R15,	                    /**< \brief Testing register R15 */
    TEST_R16,	                    /**< \brief Testing register R16 */
    TEST_R17,	                    /**< \brief Testing register R17 */
    TEST_R18,	                    /**< \brief Testing register R18 */
    TEST_R19,	                    /**< \brief Testing register R19 */
    TEST_R20,	                    /**< \brief Testing register R20 */
    TEST_R21,                       /**< \brief Testing register R21 */
    TEST_R22,	                    /**< \brief Testing register R22 */
    TEST_R23,	                    /**< \brief Testing register R23 */
    TEST_R24,	                    /**< \brief Testing register R24 */
    TEST_R25,	                    /**< \brief Testing register R25 */
    TEST_R26,	                    /**< \brief Testing register R26 */
    TEST_R27,	                    /**< \brief Testing register R27 */
    TEST_R28,	                    /**< \brief Testing register R28 */
    TEST_R29,	                    /**< \brief Testing register R29 */
    TEST_R30,                       /**< \brief Testing register R30 */
    TEST_R31,                       /**< \brief Testing register R31 */
    TEST_R32,	                    /**< \brief Testing register R32 */
    TEST_R33,	                    /**< \brief Testing register R33 */
    TEST_R34,	                    /**< \brief Testing register R34 */
    TEST_R35,	                    /**< \brief Testing register R35 */
    TEST_R36,	                    /**< \brief Testing register R36 */
    TEST_R37,	                    /**< \brief Testing register R37 */
    TEST_R38,	                    /**< \brief Testing register R38 */
    TEST_R39,	                    /**< \brief Testing register R39 */
    TEST_R40,	                    /**< \brief Testing register R40 */
    TEST_R41,                       /**< \brief Testing register R41 */
    TEST_R42,	                    /**< \brief Testing register R42 */
    TEST_R43,	                    /**< \brief Testing register R43 */
    TEST_R44,	                    /**< \brief Testing register R44 */
    TEST_R45,	                    /**< \brief Testing register R45 */
    TEST_R46,	                    /**< \brief Testing register R46 */
    TEST_R47,	                    /**< \brief Testing register R47 */
    TEST_R48,	                    /**< \brief Testing register R48 */
    TEST_R49,	                    /**< \brief Testing register R49 */
    TEST_R50,	                    /**< \brief Testing register R50 */
    TEST_R51,                       /**< \brief Testing register R51 */
    TEST_R52,	                    /**< \brief Testing register R52 */
    TEST_R53,	                    /**< \brief Testing register R53 */
    TEST_R54,	                    /**< \brief Testing register R54 */
    TEST_R55,	                    /**< \brief Testing register R55 */
    TEST_R56,	                    /**< \brief Testing register R56 */
    TEST_R57,	                    /**< \brief Testing register R57 */
    TEST_R58,	                    /**< \brief Testing register R58 */
    TEST_R59,	                    /**< \brief Testing register R59 */
    TEST_R60,	                    /**< \brief Testing register R60 */
    TEST_R61,                       /**< \brief Testing register R61 */
    TEST_R62,	                    /**< \brief Testing register R62 */
    TEST_R63,	                    /**< \brief Testing register R63 */
    TEST_R64,	                    /**< \brief Testing register R64 */
    TEST_R65,	                    /**< \brief Testing register R65 */
    TEST_R66,	                    /**< \brief Testing register R66 */
    TEST_R67,	                    /**< \brief Testing register R67 */
    TEST_R68,	                    /**< \brief Testing register R68 */
    TEST_R69,	                    /**< \brief Testing register R69 */
    TEST_R70,	                    /**< \brief Testing register R70 */
    TEST_R71,                       /**< \brief Testing register R71 */
    TEST_R72,	                    /**< \brief Testing register R72 */
    TEST_R73,	                    /**< \brief Testing register R73 */
    TEST_R74,	                    /**< \brief Testing register R74 */
    TEST_R75,	                    /**< \brief Testing register R75 */
    TEST_R76,	                    /**< \brief Testing register R76 */
    TEST_R77,	                    /**< \brief Testing register R77 */
    TEST_R78,	                    /**< \brief Testing register R78 */
    TEST_R79,	                    /**< \brief Testing register R79 */
    TEST_R80,	                    /**< \brief Testing register R80 */
    TEST_R81,                       /**< \brief Testing register R81 */
    TEST_R82,	                    /**< \brief Testing register R82 */
    TEST_R83,	                    /**< \brief Testing register R83 */
    TEST_R84,	                    /**< \brief Testing register R84 */
    TEST_R85,	                    /**< \brief Testing register R85 */
    TEST_R86,	                    /**< \brief Testing register R86 */
    TEST_R87,	                    /**< \brief Testing register R87 */
    TEST_R88,	                    /**< \brief Testing register R88 */
    TEST_R89,	                    /**< \brief Testing register R89 */
    TEST_R90,                       /**< \brief Testing register R90 */
    TEST_R91,                       /**< \brief Testing register R91 */
    TEST_R92,	                    /**< \brief Testing register R92 */
    TEST_R93,	                    /**< \brief Testing register R93 */
    TEST_R94,	                    /**< \brief Testing register R94 */
    TEST_R95,	                    /**< \brief Testing register R95 */
    TEST_R96,	                    /**< \brief Testing register R96 */
    TEST_R97,	                    /**< \brief Testing register R97 */
    TEST_R98,	                    /**< \brief Testing register R98 */
    TEST_R99,	                    /**< \brief Testing register R99 */
    TEST_R100,	                    /**< \brief Testing register R100 */
	REQUEST_REG_LENGTH              /**< \brief Number of registers */					            
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
    NONE1      	=0x3,				/**< \brief None operation*/                      
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