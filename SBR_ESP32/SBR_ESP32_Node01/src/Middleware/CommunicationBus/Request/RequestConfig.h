/**
 * @file RequestConfig.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Declaration for the request class
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
    REQUEST_NONE = 0,       /**@brief None operation*/ 
	REQUEST_READ,	        /**@brief Read operation*/
	REQUEST_WRITE,		    /**@brief Write operation*/                   
};


#endif /* REQUESTCONFIG_H */