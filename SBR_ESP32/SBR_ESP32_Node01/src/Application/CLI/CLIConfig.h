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
    CLI_Modes_Restart,
    CLI_Modes_Program,
    CLI_Modes_Motion,
    CLI_Settings,
    CLI_Settings_Read,
    CLI_Settings_Write,
    CLI_Settings_Write_WifiName,
    CLI_Settings_Write_WifiPassword,
    CLI_Monitor,
    CLI_Monitor_Tasks,
    CLI_Monitor_Memory,
    CLI_Modules,
    CLI_Modules_Communication,
    CLI_Modules_Communication_PrintBufferEsp32,
    CLI_Modules_Motors,
    CLI_Modules_Motors_SetSpeedMotorLeft,
    CLI_Modules_Motors_SetSpeedMotorRight,
    CLI_Modules_Motors_PrintInfo,
    CLI_Modules_IMU,
    CLI_Modules_IMU_RotationVector,
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
String insertedValueCLI = "";                               /**@brief Inserted value in the CLI*/


/*******************************************************************************************************************************************
 *  												DECLARATION FUNCTIONS
 *******************************************************************************************************************************************/

void InitCLI();
void RunCLI();
void MenuModeCLI();
void GetValueCLI();
void ActivateGetValueModeCLI();
void DeactivateGetValueModeCLI();
void GoIntoNewPath();
void F_CLI_GotoHome();
void F_CLI_GotoPrevious();
void F_CLI_Info();
void F_CLI_Hello();
void F_CLI_Status();
void F_CLI_Modes();
void F_CLI_Modes_Restart();
void F_CLI_Modes_Program();
void F_CLI_Modes_Motion();
void F_CLI_Settings();
void F_CLI_Settings_Read();
void F_CLI_Settings_Write();
void F_CLI_Settings_Write_WifiName();
void F_CLI_Settings_Write_WifiPassword();
void F_CLI_Monitor();
void F_CLI_Monitor_Tasks();
void F_CLI_Monitor_Memory();
void F_CLI_Modules();
void F_CLI_Modules_Communication();
void F_CLI_Modules_Communication_PrintBufferEsp32();
void F_CLI_Modules_Motors();
void F_CLI_Modules_Motors_SetSpeedMotorLeft();
void F_CLI_Modules_Motors_SetSpeedMotorRight();
void F_CLI_Modules_Motors_PrintInfo();
void F_CLI_Modules_IMU();
void F_CLI_Modules_IMU_RotationVector();
void F_CLI_Debug();
void F_CLI_Debug_GetLogLevel();
void F_CLI_Debug_SetLogLevelFatal();
void F_CLI_Debug_SetLogLevelError();
void F_CLI_Debug_SetLogLevelWarning();
void F_CLI_Debug_SetLogLevelInfo();
void F_CLI_Debug_SetLogLevelTrace();
void F_CLI_Debug_SetLogLevelVerbose();
void F_CLI_Test();
void F_CLI_Test_Test1();
void F_CLI_Test_Test2();
void F_CLI_Test_Test3();
void F_CLI_Test_Test4();
void F_CLI_Test_Test5();
void F_CLI_Test_Test6();
void F_CLI_Test_Test7();
void F_CLI_Test_Test8();
void F_CLI_Test_Test9();


#endif // CLICONFIG_H