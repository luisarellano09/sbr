/**
 * @file GlobalVar.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Global variables of SBR
 * 
 */

#ifndef GLOBALVAR_H
#define GLOBALVAR_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include <Preferences.h>
#include "../../Application/Manager/Manager.h"


/*******************************************************************************************************************************************
 *  												GLOBAL VARIABLES
 *******************************************************************************************************************************************/

static Manager* manager;                /**@brief Instance of the manager */
static Preferences preferences;         /**@brief Preferences instance*/

QueueHandle_t queue_Register10;


#endif /* GLOBALVAR_H */