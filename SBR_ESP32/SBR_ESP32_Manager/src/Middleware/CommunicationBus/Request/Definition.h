/**
 * @file Definition.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Definitions for the Communication Bus
 * @version 1.0
 * @date 08.02.2023
 * 
 */

#ifndef DEFNITION_H
#define DEFNITION_H

/*******************************************************************************************************************************************
 *  												ENUMERATION
 *******************************************************************************************************************************************/

/**
 * @brief Defines if a read or write operation shall be performed
 * 
 */
enum COM_REQUEST_TYPE_e {
    NONE = 0,   /** None operation*/   
	READ,	    /** Read operation*/
	WRITE,		/** Write operation*/                   
};


#endif /* DEFNITION_H */