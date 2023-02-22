/**
 * @file ModesConfig.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief ModesConfig
 * @version 1.0
 * @date 19.02.2023
 * 
 * 
 */

#ifndef MODESCONFIG_H
#define MODESCONFIG_H

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include <Arduino.h>


/*******************************************************************************************************************************************
 *  												ENUMERATIONS
 *******************************************************************************************************************************************/

/**
 * @brief Enumeration of the Modes
 * 
 */
enum Modes_e {
    Mode_Idle = 0,
	Mode_Program,
    LENGTH_MODES                                               
};


//=====================================================================================================

/**
 * @brief Enumeration of States of Idle Mode
 * 
 */
enum StateModeIdle_e {
    StateModeIdle_Idle,
	StateModeIdle_DeactivateTasks,
    StateModeIdle_ActivateTaskCLI,
    StateModeIdle_ActivateTaskNodeESP32,
    StateModeIdle_ChangeStatusToInactive
};


//=====================================================================================================

/**
 * @brief Enumeration of States of Program Mode
 * 
 */
enum StateModeProgram_e {
    StateModeProgram_Idle,
	StateModeProgram_DeactivateTasks,
    StateModeProgram_ActivateTaskOTA,
    StateModeProgram_ActivateWifi,
    StateModeProgram_ChangeStatusToInactive
};


/*******************************************************************************************************************************************
 *  												STRUCTURES
 *******************************************************************************************************************************************/

/**
 * @brief Struct of a Mode
 * 
 */
struct Mode_t{
    uint8_t status = 0;                 /**@brief Status of the Mode. 0=inactive; 1=active*/
    void (*Callback)(Modes_e) = NULL;      /**@brief Function callback of the Mode*/
};


/*******************************************************************************************************************************************
 *  												DECLARATION VARIABLES
 *******************************************************************************************************************************************/

Mode_t Modes[Modes_e::LENGTH_MODES];        /**@brief Array of Modes */

StateModeIdle_e stateModeIdle = StateModeIdle_e::StateModeIdle_Idle;
StateModeIdle_e NextStateModeIdle = StateModeIdle_e::StateModeIdle_Idle;

StateModeProgram_e stateModeProgram = StateModeProgram_e::StateModeProgram_Idle;
StateModeProgram_e NextStateModeProgram = StateModeProgram_e::StateModeProgram_Idle;


/*******************************************************************************************************************************************
 *  												DECLARATION FUNCTIONS
 *******************************************************************************************************************************************/

/**
 * @brief Init Mode
 * 
 */
void InitModes();


//=====================================================================================================

/**
 * @brief Start Mode
 * 
 */
void StartMode(Modes_e mode);


//=====================================================================================================

/**
 * @brief Stop Mode
 * 
 */
void StopMode(Modes_e mode);


//=====================================================================================================

/**
 * @brief Run Modes
 * 
 */
void RunModes();


//=====================================================================================================

/**
 * @brief State Machine: Idle Mode
 * 
 */
void SM_ModeIdle(Modes_e mode);


//=====================================================================================================

/**
 * @brief State Machine: Program Mode
 * 
 */
void SM_ModeProgram(Modes_e mode);


#endif // MODESCONFIG_H