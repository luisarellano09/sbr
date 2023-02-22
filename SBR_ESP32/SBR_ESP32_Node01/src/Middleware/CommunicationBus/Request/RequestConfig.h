/**
 * @file Definition.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Definitions for the Communication Bus
 * @version 1.0
 * @date 08.02.2023
 * 
 */

#ifndef REQUESTCONFIG_H
#define REQUESTCONFIG_H

/*******************************************************************************************************************************************
 *  												ENUMERATION
 *******************************************************************************************************************************************/

/**
 * @brief Defines if a read or write operation shall be performed
 * 
 */
enum COM_REQUEST_TYPE_e {
    NONE = 0,       /**@brief None operation*/ 
	READ,	        /**@brief Read operation*/
	WRITE,		    /**@brief Write operation*/                   
};


#endif /* REQUESTCONFIG_H */