/**
 * @file GlobalVar.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Global variables of SBR
 * @version 1.0
 * @date 07.02.2023
 * 
 */

#ifndef GLOBALVAR_H
#define GLOBALVAR_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include "../../Application/Manager/Manager.h"

/*******************************************************************************************************************************************
 *  												GLOBAL VARIABLES
 *******************************************************************************************************************************************/

static Manager* manager;                            /**@brief Instance of the manager */
static SemaphoreHandle_t semaphoreMutexGlobVar;     /**@brief Semaphore to Mutex for Global Variables */
static volatile int counter = 0;                    /**@brief Example */


#endif /* GLOBALVAR_H */