/**
 * @file Motion.cpp
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Motion Class
 * @date 29.03.2023
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "Motion.h"
#include <ArduinoLog.h>


/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

Motion::Motion(){
    this->m_PID = new PID();
}


//=====================================================================================================

Motion::~Motion(){
}


/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e Motion::Run(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_PID->Run();

    return retCode;
}