/**
 * @file CLIConfig.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief CLIConfig
 * @version 1.0
 * @date 15.02.2023
 * 
 * 
 */

#ifndef CLICONFIG_H
#define CLICONFIG_H

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include <Arduino.h>


/*******************************************************************************************************************************************
 *  												STRUCTURES
 *******************************************************************************************************************************************/

/**
 * @brief Struct of CLI Option
 * 
 */
struct CLIOption_t{
    String path = "";                   /**@brief Path of the CLI Option */
    String text = "";                   /**@brief Text of the CLI Option */
    void (*Callback)(void) = NULL;      /**@brief Function callback of the CLI Option*/
};


/*******************************************************************************************************************************************
 *  												ENUMERATION
 *******************************************************************************************************************************************/

/**
 * @brief Enumeration of CLI Options
 * 
 */
enum CLIOptions_e {
    CLI_GotoHome = 0,
	CLI_GotoPrevious,
    CLI_Info,
	CLI_Hello,
  	CLI_Status,
    CLI_Modes,
    CLI_Modes_Program,
    CLI_Modes_Restart,
    CLI_Settings,
    CLI_Settings_Read,
    CLI_Settings_Write,
    CLI_Settings_Write_WifiName,
    CLI_Settings_Write_WifiPassword,
    CLI_Monitor,
    CLI_Monitor_Tasks,
    CLI_Monitor_Memory,
    CLI_Monitor_Communication,
    CLI_Monitor_Communication_PrintTable,
    CLI_Monitor_Communication_PrintBufferEsp32,
    CLI_Monitor_Communication_Variables,
    CLI_Debug,
    CLI_Debug_GetLogLevel,
    CLI_Debug_SetLogLevelFatal,
    CLI_Debug_SetLogLevelError,
    CLI_Debug_SetLogLevelWarning,
    CLI_Debug_SetLogLevelInfo,
    CLI_Debug_SetLogLevelTrace,
    CLI_Debug_SetLogLevelVerbose,
    CLI_Test,
    CLI_Test_Test1,
    CLI_Test_Test2,
    CLI_Test_Test3,
    CLI_Test_Test4,
    CLI_Test_Test5,
    CLI_Test_Test6,
    CLI_Test_Test7,
    CLI_Test_Test8,
    CLI_Test_Test9,
    LENGTH_CLI_OPTIONS                                                 
};


/*******************************************************************************************************************************************
 *  												DECLARATION VARIABLES
 *******************************************************************************************************************************************/

CLIOption_t CLIOptions[CLIOptions_e::LENGTH_CLI_OPTIONS];   /**@brief Array of CLI Options */
String currentCLIPath = "";                                 /**@brief Current CLI path */
char incomingCharCLI = ' ';                                 /**@brief Incomming character in the CLI*/


#endif // CLICONFIG_H