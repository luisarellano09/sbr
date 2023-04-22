/**
 * @file CLI.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief CLI
 * 
 */

#ifndef CLI_H
#define CLI_H

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include <ArduinoLog.h>
#include "CLIConfig.h"
#include "../../../Definition/Local/GlobalVar.h"
#include "../../../Definition/Local/LocalConfig.h"
#include "../Tasks/TasksConfig.h"
#include "../Modes/ModesConfig.h"
#include "../Datalog/DatalogConfig.h"


/*******************************************************************************************************************************************
 *  												DEFINITION FUNCTIONS
 *******************************************************************************************************************************************/

void InitCLI(){

    CLIOptions[CLIOptions_e::CLI_GotoHome].path = "g";
    CLIOptions[CLIOptions_e::CLI_GotoHome].text = "GO TO HOME";
    CLIOptions[CLIOptions_e::CLI_GotoHome].Callback = F_CLI_GotoHome;

    CLIOptions[CLIOptions_e::CLI_GotoPrevious].path = "p";
    CLIOptions[CLIOptions_e::CLI_GotoPrevious].text = "GO TO PREVIOUS";
    CLIOptions[CLIOptions_e::CLI_GotoPrevious].Callback = F_CLI_GotoPrevious;

    CLIOptions[CLIOptions_e::CLI_Info].path = "h";
    CLIOptions[CLIOptions_e::CLI_Info].text = "HELP";
    CLIOptions[CLIOptions_e::CLI_Info].Callback = F_CLI_Info;

    CLIOptions[CLIOptions_e::CLI_Hello].path = "s";
    CLIOptions[CLIOptions_e::CLI_Hello].text = "SAY HELLO\r\n";
    CLIOptions[CLIOptions_e::CLI_Hello].Callback = F_CLI_Hello;

    CLIOptions[CLIOptions_e::CLI_Status].path = "1";
    CLIOptions[CLIOptions_e::CLI_Status].text = "Status";
    CLIOptions[CLIOptions_e::CLI_Status].Callback = F_CLI_Status;

    CLIOptions[CLIOptions_e::CLI_Modes].path = "2";
    CLIOptions[CLIOptions_e::CLI_Modes].text = "Modes ->";
    CLIOptions[CLIOptions_e::CLI_Modes].Callback = F_CLI_Modes;

    CLIOptions[CLIOptions_e::CLI_Modes_Restart].path = "21";
    CLIOptions[CLIOptions_e::CLI_Modes_Restart].text = "Restart";
    CLIOptions[CLIOptions_e::CLI_Modes_Restart].Callback = F_CLI_Modes_Restart;

    CLIOptions[CLIOptions_e::CLI_Modes_Program].path = "22";
    CLIOptions[CLIOptions_e::CLI_Modes_Program].text = "Program";
    CLIOptions[CLIOptions_e::CLI_Modes_Program].Callback = F_CLI_Modes_Program;

    CLIOptions[CLIOptions_e::CLI_Modes_Motion].path = "23";
    CLIOptions[CLIOptions_e::CLI_Modes_Motion].text = "Motion";
    CLIOptions[CLIOptions_e::CLI_Modes_Motion].Callback = F_CLI_Modes_Motion;

    CLIOptions[CLIOptions_e::CLI_Settings].path = "3";
    CLIOptions[CLIOptions_e::CLI_Settings].text = "Settings ->";
    CLIOptions[CLIOptions_e::CLI_Settings].Callback = F_CLI_Settings;

    CLIOptions[CLIOptions_e::CLI_Settings_Read].path = "31";
    CLIOptions[CLIOptions_e::CLI_Settings_Read].text = "Read";
    CLIOptions[CLIOptions_e::CLI_Settings_Read].Callback = F_CLI_Settings_Read;

    CLIOptions[CLIOptions_e::CLI_Settings_Write].path = "32";
    CLIOptions[CLIOptions_e::CLI_Settings_Write].text = "Write ->";
    CLIOptions[CLIOptions_e::CLI_Settings_Write].Callback = F_CLI_Settings_Write;

    CLIOptions[CLIOptions_e::CLI_Settings_Write_WifiName].path = "321";
    CLIOptions[CLIOptions_e::CLI_Settings_Write_WifiName].text = "Wifi Name";
    CLIOptions[CLIOptions_e::CLI_Settings_Write_WifiName].Callback = F_CLI_Settings_Write_WifiName;

    CLIOptions[CLIOptions_e::CLI_Settings_Write_WifiPassword].path = "322";
    CLIOptions[CLIOptions_e::CLI_Settings_Write_WifiPassword].text = "Wifi Password";
    CLIOptions[CLIOptions_e::CLI_Settings_Write_WifiPassword].Callback = F_CLI_Settings_Write_WifiPassword;

    CLIOptions[CLIOptions_e::CLI_Monitor].path = "4";
    CLIOptions[CLIOptions_e::CLI_Monitor].text = "Monitor ->";
    CLIOptions[CLIOptions_e::CLI_Monitor].Callback = F_CLI_Monitor;

    CLIOptions[CLIOptions_e::CLI_Monitor_Tasks].path = "41";
    CLIOptions[CLIOptions_e::CLI_Monitor_Tasks].text = "Tasks";
    CLIOptions[CLIOptions_e::CLI_Monitor_Tasks].Callback = F_CLI_Monitor_Tasks;

    CLIOptions[CLIOptions_e::CLI_Monitor_Memory].path = "42";
    CLIOptions[CLIOptions_e::CLI_Monitor_Memory].text = "Memory";
    CLIOptions[CLIOptions_e::CLI_Monitor_Memory].Callback = F_CLI_Monitor_Memory;

    CLIOptions[CLIOptions_e::CLI_Modules].path = "5";
    CLIOptions[CLIOptions_e::CLI_Modules].text = "Modules ->";
    CLIOptions[CLIOptions_e::CLI_Modules].Callback = F_CLI_Modules;

    CLIOptions[CLIOptions_e::CLI_Modules_Communication].path = "51";
    CLIOptions[CLIOptions_e::CLI_Modules_Communication].text = "Communication ->";
    CLIOptions[CLIOptions_e::CLI_Modules_Communication].Callback = F_CLI_Modules_Communication;

    CLIOptions[CLIOptions_e::CLI_Modules_Communication_PrintBufferEsp32].path = "511";
    CLIOptions[CLIOptions_e::CLI_Modules_Communication_PrintBufferEsp32].text = "Print Buffer ESP32";
    CLIOptions[CLIOptions_e::CLI_Modules_Communication_PrintBufferEsp32].Callback = F_CLI_Modules_Communication_PrintBufferEsp32;

    CLIOptions[CLIOptions_e::CLI_Modules_Motors].path = "52";
    CLIOptions[CLIOptions_e::CLI_Modules_Motors].text = "Motors ->";
    CLIOptions[CLIOptions_e::CLI_Modules_Motors].Callback = F_CLI_Modules_Motors;

    CLIOptions[CLIOptions_e::CLI_Modules_Motors_SetSpeedMotorLeft].path = "521";
    CLIOptions[CLIOptions_e::CLI_Modules_Motors_SetSpeedMotorLeft].text = "Set Speed Motor Left";
    CLIOptions[CLIOptions_e::CLI_Modules_Motors_SetSpeedMotorLeft].Callback = F_CLI_Modules_Motors_SetSpeedMotorLeft;

    CLIOptions[CLIOptions_e::CLI_Modules_Motors_SetSpeedMotorRight].path = "522";
    CLIOptions[CLIOptions_e::CLI_Modules_Motors_SetSpeedMotorRight].text = "Set Speed Motor Right";
    CLIOptions[CLIOptions_e::CLI_Modules_Motors_SetSpeedMotorRight].Callback = F_CLI_Modules_Motors_SetSpeedMotorRight;

    CLIOptions[CLIOptions_e::CLI_Modules_Motors_PrintInfo].path = "523";
    CLIOptions[CLIOptions_e::CLI_Modules_Motors_PrintInfo].text = "Print Motors Info";
    CLIOptions[CLIOptions_e::CLI_Modules_Motors_PrintInfo].Callback = F_CLI_Modules_Motors_PrintInfo;

    CLIOptions[CLIOptions_e::CLI_Modules_IMU].path = "53";
    CLIOptions[CLIOptions_e::CLI_Modules_IMU].text = "IMU ->";
    CLIOptions[CLIOptions_e::CLI_Modules_IMU].Callback = F_CLI_Modules_IMU;

    CLIOptions[CLIOptions_e::CLI_Modules_IMU_RotationVector].path = "531";
    CLIOptions[CLIOptions_e::CLI_Modules_IMU_RotationVector].text = "Show Rotation vector";
    CLIOptions[CLIOptions_e::CLI_Modules_IMU_RotationVector].Callback = F_CLI_Modules_IMU_RotationVector;

    CLIOptions[CLIOptions_e::CLI_Modules_Encoders].path = "54";
    CLIOptions[CLIOptions_e::CLI_Modules_Encoders].text = "Encoders ->";
    CLIOptions[CLIOptions_e::CLI_Modules_Encoders].Callback = F_CLI_Modules_Encoders;

    CLIOptions[CLIOptions_e::CLI_Modules_Encoders_Status].path = "541";
    CLIOptions[CLIOptions_e::CLI_Modules_Encoders_Status].text = "Status";
    CLIOptions[CLIOptions_e::CLI_Modules_Encoders_Status].Callback = F_CLI_Modules_Encoders_Status;

    CLIOptions[CLIOptions_e::CLI_Modules_Encoders_SetValues].path = "542";
    CLIOptions[CLIOptions_e::CLI_Modules_Encoders_SetValues].text = "Set Values ->";
    CLIOptions[CLIOptions_e::CLI_Modules_Encoders_SetValues].Callback = F_CLI_Modules_Encoders_SetValues;

    CLIOptions[CLIOptions_e::CLI_Modules_Encoders_SetValues_SetCountEncoderLeft].path = "5421";
    CLIOptions[CLIOptions_e::CLI_Modules_Encoders_SetValues_SetCountEncoderLeft].text = "Set Count Encoder Left";
    CLIOptions[CLIOptions_e::CLI_Modules_Encoders_SetValues_SetCountEncoderLeft].Callback = F_CLI_Modules_Encoders_SetValues_SetCountEncoderLeft;

    CLIOptions[CLIOptions_e::CLI_Modules_Encoders_SetValues_SetCountEncoderRight].path = "5422";
    CLIOptions[CLIOptions_e::CLI_Modules_Encoders_SetValues_SetCountEncoderRight].text = "Set Count Encoder Right";
    CLIOptions[CLIOptions_e::CLI_Modules_Encoders_SetValues_SetCountEncoderRight].Callback = F_CLI_Modules_Encoders_SetValues_SetCountEncoderRight;

    CLIOptions[CLIOptions_e::CLI_Modules_Encoders_PrintInfo].path = "543";
    CLIOptions[CLIOptions_e::CLI_Modules_Encoders_PrintInfo].text = "Print Info";
    CLIOptions[CLIOptions_e::CLI_Modules_Encoders_PrintInfo].Callback = F_CLI_Modules_Encoders_PrintInfo;

    CLIOptions[CLIOptions_e::CLI_Modules_Odometry].path = "55";
    CLIOptions[CLIOptions_e::CLI_Modules_Odometry].text = "Odometry ->";
    CLIOptions[CLIOptions_e::CLI_Modules_Odometry].Callback = F_CLI_Modules_Odometry;

    CLIOptions[CLIOptions_e::CLI_Modules_Odometry_Status].path = "551";
    CLIOptions[CLIOptions_e::CLI_Modules_Odometry_Status].text = "Status";
    CLIOptions[CLIOptions_e::CLI_Modules_Odometry_Status].Callback = F_CLI_Modules_Odometry_Status;

    CLIOptions[CLIOptions_e::CLI_Modules_Odometry_SetValues].path = "552";
    CLIOptions[CLIOptions_e::CLI_Modules_Odometry_SetValues].text = "Set Values ->";
    CLIOptions[CLIOptions_e::CLI_Modules_Odometry_SetValues].Callback = F_CLI_Modules_Odometry_SetValues;

    CLIOptions[CLIOptions_e::CLI_Modules_Odometry_SetValues_SetX].path = "5521";
    CLIOptions[CLIOptions_e::CLI_Modules_Odometry_SetValues_SetX].text = "Set X";
    CLIOptions[CLIOptions_e::CLI_Modules_Odometry_SetValues_SetX].Callback = F_CLI_Modules_Odometry_SetValues_SetX;

    CLIOptions[CLIOptions_e::CLI_Modules_Odometry_SetValues_SetY].path = "5522";
    CLIOptions[CLIOptions_e::CLI_Modules_Odometry_SetValues_SetY].text = "Set Y";
    CLIOptions[CLIOptions_e::CLI_Modules_Odometry_SetValues_SetY].Callback = F_CLI_Modules_Odometry_SetValues_SetY;

    CLIOptions[CLIOptions_e::CLI_Modules_Odometry_SetValues_SetDistance].path = "5523";
    CLIOptions[CLIOptions_e::CLI_Modules_Odometry_SetValues_SetDistance].text = "Set Distance";
    CLIOptions[CLIOptions_e::CLI_Modules_Odometry_SetValues_SetDistance].Callback = F_CLI_Modules_Odometry_SetValues_SetDistance;

    CLIOptions[CLIOptions_e::CLI_Modules_Odometry_SetValues_SetAngle].path = "5524";
    CLIOptions[CLIOptions_e::CLI_Modules_Odometry_SetValues_SetAngle].text = "Set Angle";
    CLIOptions[CLIOptions_e::CLI_Modules_Odometry_SetValues_SetAngle].Callback = F_CLI_Modules_Odometry_SetValues_SetAngle;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion].path = "56";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion].text = "Motion Control ->";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion].Callback = F_CLI_Modules_Motion;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_Start].path = "561";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_Start].text = "Start";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_Start].Callback = F_CLI_Modules_Motion_Start;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_Stop].path = "562";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_Stop].text = "Stop";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_Stop].Callback = F_CLI_Modules_Motion_Stop;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_ShowSP].path = "563";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_ShowSP].text = "Show SPs";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_ShowSP].Callback = F_CLI_Modules_Motion_ShowSP;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_SetSPAngle].path = "564";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_SetSPAngle].text = "Set SP Angle";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_SetSPAngle].Callback = F_CLI_Modules_Motion_SetSPAngle;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_SetSPPosition].path = "565";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_SetSPPosition].text = "Set SP Position";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_SetSPPosition].Callback = F_CLI_Modules_Motion_SetSPPosition;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam].path = "566";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam].text = "PID Pitch Param ->";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam].Callback = F_CLI_Modules_Motion_PIDPitchParam;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam_Show].path = "5661";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam_Show].text = "Show Param";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam_Show].Callback = F_CLI_Modules_Motion_PIDPitchParam_Show;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam_Kp].path = "5662";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam_Kp].text = "Set Kp";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam_Kp].Callback = F_CLI_Modules_Motion_PIDPitchParam_Kp;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam_Ki].path = "5663";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam_Ki].text = "Set Ki";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam_Ki].Callback = F_CLI_Modules_Motion_PIDPitchParam_Ki;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam_Kd].path = "5664";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam_Kd].text = "Set Kd";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam_Kd].Callback = F_CLI_Modules_Motion_PIDPitchParam_Kd;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam_MVmin].path = "5665";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam_MVmin].text = "Set MV min";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam_MVmin].Callback = F_CLI_Modules_Motion_PIDPitchParam_MVmin;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam_MVmax].path = "5666";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam_MVmax].text = "Set MV max";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPitchParam_MVmax].Callback = F_CLI_Modules_Motion_PIDPitchParam_MVmax;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam].path = "567";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam].text = "PID Pos Param ->";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam].Callback = F_CLI_Modules_Motion_PIDPosParam;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam_Show].path = "5671";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam_Show].text = "Show Param";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam_Show].Callback = F_CLI_Modules_Motion_PIDPosParam_Show;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam_Kp].path = "5672";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam_Kp].text = "Set Kp";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam_Kp].Callback = F_CLI_Modules_Motion_PIDPosParam_Kp;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam_Ki].path = "5673";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam_Ki].text = "Set Ki";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam_Ki].Callback = F_CLI_Modules_Motion_PIDPosParam_Ki;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam_Kd].path = "5674";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam_Kd].text = "Set Kd";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam_Kd].Callback = F_CLI_Modules_Motion_PIDPosParam_Kd;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam_MVmin].path = "5675";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam_MVmin].text = "Set MV min";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam_MVmin].Callback = F_CLI_Modules_Motion_PIDPosParam_MVmin;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam_MVmax].path = "5676";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam_MVmax].text = "Set MV max";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDPosParam_MVmax].Callback = F_CLI_Modules_Motion_PIDPosParam_MVmax;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam].path = "568";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam].text = "PID Angle Param ->";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam].Callback = F_CLI_Modules_Motion_PIDAngleParam;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam_Show].path = "5681";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam_Show].text = "Show Param";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam_Show].Callback = F_CLI_Modules_Motion_PIDAngleParam_Show;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam_Kp].path = "5682";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam_Kp].text = "Set Kp";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam_Kp].Callback = F_CLI_Modules_Motion_PIDAngleParam_Kp;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam_Ki].path = "5683";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam_Ki].text = "Set Ki";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam_Ki].Callback = F_CLI_Modules_Motion_PIDAngleParam_Ki;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam_Kd].path = "5684";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam_Kd].text = "Set Kd";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam_Kd].Callback = F_CLI_Modules_Motion_PIDAngleParam_Kd;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam_MVmin].path = "5685";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam_MVmin].text = "Set MV min";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam_MVmin].Callback = F_CLI_Modules_Motion_PIDAngleParam_MVmin;

    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam_MVmax].path = "5686";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam_MVmax].text = "Set MV max";
    CLIOptions[CLIOptions_e::CLI_Modules_Motion_PIDAngleParam_MVmax].Callback = F_CLI_Modules_Motion_PIDAngleParam_MVmax;

    CLIOptions[CLIOptions_e::CLI_Debug].path = "6";
    CLIOptions[CLIOptions_e::CLI_Debug].text = "Debug ->";
    CLIOptions[CLIOptions_e::CLI_Debug].Callback = F_CLI_Debug;

    CLIOptions[CLIOptions_e::CLI_Debug_GetLogLevel].path = "60";
    CLIOptions[CLIOptions_e::CLI_Debug_GetLogLevel].text = "Get Log Level";
    CLIOptions[CLIOptions_e::CLI_Debug_GetLogLevel].Callback = F_CLI_Debug_GetLogLevel;

    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelFatal].path = "61";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelFatal].text = "Set FATAL Log level";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelFatal].Callback = F_CLI_Debug_SetLogLevelFatal;
    
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelError].path = "62";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelError].text = "Set ERROR Log level";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelError].Callback = F_CLI_Debug_SetLogLevelError;

    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelWarning].path = "63";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelWarning].text = "Set WARNING Log level";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelWarning].Callback = F_CLI_Debug_SetLogLevelWarning;

    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelInfo].path = "64";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelInfo].text = "Set INFO Log level";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelInfo].Callback = F_CLI_Debug_SetLogLevelInfo;

    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelTrace].path = "65";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelTrace].text = "Set TRACE Log level";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelTrace].Callback = F_CLI_Debug_SetLogLevelTrace;

    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelVerbose].path = "66";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelVerbose].text = "Set VERBOSE Log level";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelVerbose].Callback = F_CLI_Debug_SetLogLevelVerbose;

    CLIOptions[CLIOptions_e::CLI_Datalog].path = "7";
    CLIOptions[CLIOptions_e::CLI_Datalog].text = "Datalog ->";
    CLIOptions[CLIOptions_e::CLI_Datalog].Callback = F_CLI_Datalog;

    CLIOptions[CLIOptions_e::CLI_Datalog_Start].path = "71";
    CLIOptions[CLIOptions_e::CLI_Datalog_Start].text = "Start";
    CLIOptions[CLIOptions_e::CLI_Datalog_Start].Callback = F_CLI_Datalog_Start;

    CLIOptions[CLIOptions_e::CLI_Datalog_Stop].path = "72";
    CLIOptions[CLIOptions_e::CLI_Datalog_Stop].text = "Stop";
    CLIOptions[CLIOptions_e::CLI_Datalog_Stop].Callback = F_CLI_Datalog_Stop;

    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets].path = "73";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets].text = "Datasets ->";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets].Callback = F_CLI_Datalog_Datasets;

    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_Motor].path = "731";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_Motor].text = "Motor ->";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_Motor].Callback = F_CLI_Datalog_Datasets_Motor;

    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_Motor_Activate].path = "7311";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_Motor_Activate].text = "Activate";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_Motor_Activate].Callback = F_CLI_Datalog_Datasets_Motor_Activate;

    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_Motor_Deactivate].path = "7312";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_Motor_Deactivate].text = "Deactivate";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_Motor_Deactivate].Callback = F_CLI_Datalog_Datasets_Motor_Deactivate;

    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_IMU].path = "732";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_IMU].text = "IMU ->";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_IMU].Callback = F_CLI_Datalog_Datasets_IMU;

    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_IMU_Activate].path = "7321";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_IMU_Activate].text = "Activate";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_IMU_Activate].Callback = F_CLI_Datalog_Datasets_IMU_Activate;

    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_IMU_Deactivate].path = "7322";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_IMU_Deactivate].text = "Deactivate";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_IMU_Deactivate].Callback = F_CLI_Datalog_Datasets_IMU_Deactivate;

    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_Odometry].path = "733";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_Odometry].text = "Oddometry ->";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_Odometry].Callback = F_CLI_Datalog_Datasets_Odometry;

    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_Odometry_Activate].path = "7331";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_Odometry_Activate].text = "Activate";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_Odometry_Activate].Callback = F_CLI_Datalog_Datasets_Odometry_Activate;

    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_Odometry_Deactivate].path = "7332";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_Odometry_Deactivate].text = "Deactivate";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_Odometry_Deactivate].Callback = F_CLI_Datalog_Datasets_Odometry_Deactivate;

    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_MotionControl].path = "734";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_MotionControl].text = "Motion Control ->";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_MotionControl].Callback = F_CLI_Datalog_Datasets_MotionControl;

    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_MotionControl_Activate].path = "7341";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_MotionControl_Activate].text = "Activate";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_MotionControl_Activate].Callback = F_CLI_Datalog_Datasets_MotionControl_Activate;

    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_MotionControl_Deactivate].path = "7342";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_MotionControl_Deactivate].text = "Deactivate";
    CLIOptions[CLIOptions_e::CLI_Datalog_Datasets_MotionControl_Deactivate].Callback = F_CLI_Datalog_Datasets_MotionControl_Deactivate;

    CLIOptions[CLIOptions_e::CLI_Datalog_Cycle].path = "74";
    CLIOptions[CLIOptions_e::CLI_Datalog_Cycle].text = "Cycle ->";
    CLIOptions[CLIOptions_e::CLI_Datalog_Cycle].Callback = F_CLI_Datalog_Cycle;

    CLIOptions[CLIOptions_e::CLI_Datalog_SetCycle].path = "741";
    CLIOptions[CLIOptions_e::CLI_Datalog_SetCycle].text = "Set Cycle";
    CLIOptions[CLIOptions_e::CLI_Datalog_SetCycle].Callback = F_CLI_Datalog_SetCycle;

    CLIOptions[CLIOptions_e::CLI_Profiles].path = "8";
    CLIOptions[CLIOptions_e::CLI_Profiles].text = "Profiles ->";
    CLIOptions[CLIOptions_e::CLI_Profiles].Callback = F_CLI_Profiles;

    CLIOptions[CLIOptions_e::CLI_Profile_Profile1].path = "81";
    CLIOptions[CLIOptions_e::CLI_Profile_Profile1].text = "Profile1";
    CLIOptions[CLIOptions_e::CLI_Profile_Profile1].Callback = F_CLI_Profile_Profile1;

    CLIOptions[CLIOptions_e::CLI_Profile_Profile2].path = "82";
    CLIOptions[CLIOptions_e::CLI_Profile_Profile2].text = "Profile2";
    CLIOptions[CLIOptions_e::CLI_Profile_Profile2].Callback = F_CLI_Profile_Profile2;

    CLIOptions[CLIOptions_e::CLI_Test].path = "t";
    CLIOptions[CLIOptions_e::CLI_Test].text = "Test ->";
    CLIOptions[CLIOptions_e::CLI_Test].Callback = F_CLI_Test;

    CLIOptions[CLIOptions_e::CLI_Test_Test1].path = "t1";
    CLIOptions[CLIOptions_e::CLI_Test_Test1].text = "Test1";
    CLIOptions[CLIOptions_e::CLI_Test_Test1].Callback = F_CLI_Test_Test1;

    CLIOptions[CLIOptions_e::CLI_Test_Test2].path = "t2";
    CLIOptions[CLIOptions_e::CLI_Test_Test2].text = "Test2";
    CLIOptions[CLIOptions_e::CLI_Test_Test2].Callback = F_CLI_Test_Test2;

    CLIOptions[CLIOptions_e::CLI_Test_Test3].path = "t3";
    CLIOptions[CLIOptions_e::CLI_Test_Test3].text = "Test3";
    CLIOptions[CLIOptions_e::CLI_Test_Test3].Callback = F_CLI_Test_Test3;

    CLIOptions[CLIOptions_e::CLI_Test_Test4].path = "t4";
    CLIOptions[CLIOptions_e::CLI_Test_Test4].text = "Test4";
    CLIOptions[CLIOptions_e::CLI_Test_Test4].Callback = F_CLI_Test_Test4;

    CLIOptions[CLIOptions_e::CLI_Test_Test5].path = "t5";
    CLIOptions[CLIOptions_e::CLI_Test_Test5].text = "Test5";
    CLIOptions[CLIOptions_e::CLI_Test_Test5].Callback = F_CLI_Test_Test5;

    CLIOptions[CLIOptions_e::CLI_Test_Test6].path = "t6";
    CLIOptions[CLIOptions_e::CLI_Test_Test6].text = "Test6";
    CLIOptions[CLIOptions_e::CLI_Test_Test6].Callback = F_CLI_Test_Test6;

    CLIOptions[CLIOptions_e::CLI_Test_Test7].path = "t7";
    CLIOptions[CLIOptions_e::CLI_Test_Test7].text = "Test7";
    CLIOptions[CLIOptions_e::CLI_Test_Test7].Callback = F_CLI_Test_Test7;

    CLIOptions[CLIOptions_e::CLI_Test_Test8].path = "t8";
    CLIOptions[CLIOptions_e::CLI_Test_Test8].text = "Test8";
    CLIOptions[CLIOptions_e::CLI_Test_Test8].Callback = F_CLI_Test_Test8;

    CLIOptions[CLIOptions_e::CLI_Test_Test9].path = "t9";
    CLIOptions[CLIOptions_e::CLI_Test_Test9].text = "Test9";
    CLIOptions[CLIOptions_e::CLI_Test_Test9].Callback = F_CLI_Test_Test9;
}


//=====================================================================================================

void RunCLI(){
    MenuModeCLI();
}


//=====================================================================================================

void MenuModeCLI(){

    if(Serial.available()) {

        incomingCharCLI = Serial.read();
        Serial.flush();

        for (int indexOptions=0; indexOptions<CLIOptions_e::LENGTH_CLI_OPTIONS; indexOptions++){
            if (CLIOptions[indexOptions].path == "g" || CLIOptions[indexOptions].path == "p" || CLIOptions[indexOptions].path == "h" || CLIOptions[indexOptions].path == "s"){
                if (String(incomingCharCLI) ==  CLIOptions[indexOptions].path){
                    CLIOptions[indexOptions].Callback();
                    return;
                }
            }
            if (currentCLIPath.length() == CLIOptions[indexOptions].path.length() - 1){
                if ((currentCLIPath + String(incomingCharCLI)) ==  CLIOptions[indexOptions].path) {
                    CLIOptions[indexOptions].Callback();
                    return;
                }
            }
        }    
    }
}


//=====================================================================================================

void GetValueCLI(){
    if(Serial.available()) {
        incomingCharCLI = Serial.read();
        Serial.flush();
        Serial.print(incomingCharCLI);

        if (incomingCharCLI == '\n' || incomingCharCLI == '\r'){
            Serial.println("Value: " + insertedValueCLI);
            DeactivateGetValueModeCLI();
        } else if (incomingCharCLI == '\t'){
            insertedValueCLI = "";
            Serial.println("\rInsert aborted");
            DeactivateGetValueModeCLI();
        } else {         
            insertedValueCLI = insertedValueCLI + String(incomingCharCLI);
        }
    }
}


//=====================================================================================================

void ActivateGetValueModeCLI(){
    insertedValueCLI = "";
    vTaskResume(TaskGetValueCLIHandle);
    vTaskSuspend(TaskCLIHandle);
}


//=====================================================================================================

void DeactivateGetValueModeCLI(){
    vTaskResume(TaskCLIHandle);
    vTaskSuspend(TaskGetValueCLIHandle);
}


//=====================================================================================================

void GoIntoNewPath(){
    currentCLIPath = currentCLIPath + String(incomingCharCLI);
    F_CLI_Info();
}

//=====================================================================================================

void F_CLI_GotoHome(){
    currentCLIPath.clear();
    F_CLI_Info();
}


//=====================================================================================================

void F_CLI_GotoPrevious(){
    String newPath = "";
    if (currentCLIPath.length() == 0){
        newPath = "";
    } else {
        for (int i=0; i<currentCLIPath.length()-1; i++){
            newPath = newPath + String(currentCLIPath[i]);
        }
    } 

    currentCLIPath = newPath;
    F_CLI_Info();
}


//=====================================================================================================

void F_CLI_Info(){
    String fullpathCLI = "/";
    String tempPath = "";
    for (int indexPath=0; indexPath<currentCLIPath.length(); indexPath++){
        tempPath = tempPath + String(currentCLIPath[indexPath]);
        for (int indexOptions=0; indexOptions<CLIOptions_e::LENGTH_CLI_OPTIONS; indexOptions++){
            if (tempPath == CLIOptions[indexOptions].path){
                fullpathCLI = fullpathCLI + CLIOptions[indexOptions].text + "/";
            }
        }
    }

    Serial.println("*********************************************************");
    Serial.print("Path: ");
    Serial.println(fullpathCLI);
    Serial.println("Options: ");
    for (int indexOptions=0; indexOptions<CLIOptions_e::LENGTH_CLI_OPTIONS; indexOptions++){

        if (CLIOptions[indexOptions].path == "g" || CLIOptions[indexOptions].path == "p" || CLIOptions[indexOptions].path == "h" || CLIOptions[indexOptions].path == "s"){
            Serial.println("  " + String(CLIOptions[indexOptions].path) + ":       " + CLIOptions[indexOptions].text);
        }

        if (currentCLIPath.length() == CLIOptions[indexOptions].path.length() - 1){
            if ((currentCLIPath + String(CLIOptions[indexOptions].path[currentCLIPath.length()])) == CLIOptions[indexOptions].path) {
                if (CLIOptions[indexOptions].path != "g" && CLIOptions[indexOptions].path != "p" && CLIOptions[indexOptions].path != "h" && CLIOptions[indexOptions].path != "s"){
                    Serial.println("  " + String(CLIOptions[indexOptions].path[currentCLIPath.length()]) + ":       " + CLIOptions[indexOptions].text);
                }
            }
        }
    }
    Serial.println("*********************************************************");
}


//=====================================================================================================

void F_CLI_Hello(){
    Serial.println("======= " + String(ESP32_HOSTNAME) + " =======");
}


//=====================================================================================================

void F_CLI_Status(){
    Serial.println("F_CLI_Status");
}


//=====================================================================================================

void F_CLI_Modes(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Modes_Restart(){
    Serial.println("Restarting...");
    ESP.restart();
}


//=====================================================================================================

void F_CLI_Modes_Program(){
    Serial.println("Program Mode.....");
    StartMode(Modes_e::Mode_Program);
    Log.traceln("[CLI::F_CLI_Modes_Program] Mode Program started");
}


//=====================================================================================================

void F_CLI_Modes_Motion(){
    Serial.println("Motion Mode.....");
    StartMode(Modes_e::Mode_Motion);
    Log.traceln("[CLI::F_CLI_Modes_Program] Mode Motion started");
}


//=====================================================================================================

void F_CLI_Settings(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Settings_Read(){
    Serial.println(" - WifiName: " + preferences.getString("WifiName"));
    Serial.println(" - WifiPass: " + preferences.getString("WifiPass"));
}


//=====================================================================================================

void F_CLI_Settings_Write(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Settings_Write_WifiName(){
    Serial.println("Enter WifiName: ");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        preferences.putString("WifiName", insertedValueCLI);
        Serial.println("WifiName: " + preferences.getString("WifiName"));
    }
}


//=====================================================================================================

void F_CLI_Settings_Write_WifiPassword(){
    Serial.println("Enter WifiPass: ");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        preferences.putString("WifiPass", insertedValueCLI);
        Serial.println("WifiPass: " + preferences.getString("WifiPass"));
    }
}


//=====================================================================================================

void F_CLI_Monitor(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Monitor_Tasks(){
    MonitorTasks();
}


//=====================================================================================================

void F_CLI_Monitor_Memory(){
    Serial.println("Free Heap: " + String(ESP.getFreeHeap()) + "/" + String(ESP.getHeapSize()));
}


//=====================================================================================================

void F_CLI_Modules(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Modules_Communication(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Modules_Communication_PrintBufferEsp32(){
    manager->m_nodeESP32->PrintBuffer();
}


//=====================================================================================================

void F_CLI_Modules_Motors(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Modules_Motors_SetSpeedMotorLeft(){
    float res = 0.0;
    Serial.println("Enter Speed of the left Motor:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_motorLeft->SetSpeed(res);
        Serial.println("Left Motor Speed: " + String(manager->m_motorLeft->GetSpeed()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motors_SetSpeedMotorRight(){
    float res = 0.0;
    Serial.println("Enter Speed of the right Motor:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_motorRight->SetSpeed(res);
        Serial.println("Right Motor Speed: " + String(manager->m_motorRight->GetSpeed()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motors_PrintInfo(){
    manager->m_motorLeft->Print();
    manager->m_motorRight->Print();
}


//=====================================================================================================

void F_CLI_Modules_IMU(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Modules_IMU_RotationVector(){
    Serial.printf("m_Pitch= %f, m_Roll= %f, m_Yaw= %f\r\n", manager->m_IMU->GetPitch(), manager->m_IMU->GetRoll(), manager->m_IMU->GetYaw());
}


//=====================================================================================================

void F_CLI_Modules_Encoders(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Modules_Encoders_Status(){
    Serial.println("Encoder Left Count: " + String(manager->m_encoderLeft->GetCount()));
    Serial.println("Encoder Right Count: " + String(manager->m_encoderRight->GetCount()));
}


//=====================================================================================================

void F_CLI_Modules_Encoders_SetValues(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Modules_Encoders_SetValues_SetCountEncoderLeft(){
    int64_t res = 0;
    Serial.println("Enter Count of the left Encoder:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toInt();
        manager->m_encoderLeft->SetCount(res);
        Serial.println("Left encoder count: " + String(manager->m_encoderLeft->GetCount()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Encoders_SetValues_SetCountEncoderRight(){
    int64_t res = 0;
    Serial.println("Enter Count of the right Encoder:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toInt();
        manager->m_encoderRight->SetCount(res);
        Serial.println("Right encoder count: " + String(manager->m_encoderRight->GetCount()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Encoders_PrintInfo(){
    manager->m_encoderLeft->Print();
    manager->m_encoderRight->Print();
}


//=====================================================================================================

void F_CLI_Modules_Odometry(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Modules_Odometry_Status(){
    Serial.printf("Distance: %.5f, X: %.5f, Y: %.5f, Angle: %.5f \r\n", manager->m_odometry->GetDistance(), manager->m_odometry->GetX(), manager->m_odometry->GetY(), manager->m_odometry->GetAngle());
}


//=====================================================================================================

void F_CLI_Modules_Odometry_SetValues(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Modules_Odometry_SetValues_SetX(){
    float res = 0.0;
    Serial.println("Enter X value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_odometry->SetX(res);
        Serial.println("Odometry X value: " + String(manager->m_odometry->GetX()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Odometry_SetValues_SetY(){
    float res = 0.0;
    Serial.println("Enter Y value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_odometry->SetY(res);
        Serial.println("Odometry Y value: " + String(manager->m_odometry->GetY()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Odometry_SetValues_SetDistance(){
    float res = 0.0;
    Serial.println("Enter Distance value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_odometry->SetY(res);
        Serial.println("Odometry Distance value: " + String(manager->m_odometry->GetDistance()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Odometry_SetValues_SetAngle(){
    float res = 0.0;
    Serial.println("Enter Angle value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_odometry->SetAngle(res);
        Serial.println("Odometry Angle value: " + String(manager->m_odometry->GetAngle()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motion(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Modules_Motion_Start(){
    manager->m_motionControl->Start();
    Serial.println("Motion control started");
}


//=====================================================================================================

void F_CLI_Modules_Motion_Stop(){
    manager->m_motionControl->Stop();
    Serial.println("Motion control stopped");
}


//=====================================================================================================

void F_CLI_Modules_Motion_ShowSP(){
    Serial.println("SP Position: " + String(manager->m_motionControl->GetSPPos()));
    Serial.println("SP Angle: " + String(manager->m_motionControl->GetSPAngle()));
}


//=====================================================================================================

void F_CLI_Modules_Motion_SetSPAngle(){
    float res = 0.0;
    Serial.println("Enter SP Angle value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat() + manager->m_motionControl->GetSPAngle();
        manager->m_motionControl->SetSPAngle(res);
        Serial.println("Motion SP Angle: " + String(manager->m_motionControl->GetSPAngle()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motion_SetSPPosition(){
    float res = 0.0;
    Serial.println("Enter SP Position value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat() + manager->m_motionControl->GetSPPos();
        manager->m_motionControl->SetSPPos(res);
        Serial.println("Motion SP Position: " + String(manager->m_motionControl->GetSPPos()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDPitchParam(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDPitchParam_Show(){
    manager->m_motionControl->m_PIDPitch->Print();
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDPitchParam_Kp(){
    float res = 0.0;
    Serial.println("Enter Kp value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_motionControl->m_PIDPitch->SetKp(res);
        Serial.println("PID Pitch Kp value: " + String(manager->m_motionControl->m_PIDPitch->GetKp()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDPitchParam_Ki(){
    float res = 0.0;
    Serial.println("Enter Ki value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_motionControl->m_PIDPitch->SetKi(res);
        Serial.println("PID Pitch Ki value: " + String(manager->m_motionControl->m_PIDPitch->GetKi()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDPitchParam_Kd(){
    float res = 0.0;
    Serial.println("Enter Kd value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_motionControl->m_PIDPitch->SetKd(res);
        Serial.println("PID Pitch Kd value: " + String(manager->m_motionControl->m_PIDPitch->GetKd()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDPitchParam_MVmin(){
    float res = 0.0;
    Serial.println("Enter MV min value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_motionControl->m_PIDPitch->SetMVRangeMin(res);
        Serial.println("PID Pitch MV min value: " + String(manager->m_motionControl->m_PIDPitch->GetMVRangeMin()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDPitchParam_MVmax(){
    float res = 0.0;
    Serial.println("Enter MV max value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_motionControl->m_PIDPitch->SetMVRangeMax(res);
        Serial.println("PID Pitch MV max value: " + String(manager->m_motionControl->m_PIDPitch->GetMVRangeMax()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDPosParam(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDPosParam_Show(){
    manager->m_motionControl->m_PIDPosition->Print();
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDPosParam_Kp(){
    float res = 0.0;
    Serial.println("Enter Kp value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_motionControl->m_PIDPosition->SetKp(res);
        Serial.println("PID Position Kp value: " + String(manager->m_motionControl->m_PIDPosition->GetKp()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDPosParam_Ki(){
    float res = 0.0;
    Serial.println("Enter Ki value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_motionControl->m_PIDPosition->SetKi(res);
        Serial.println("PID Position Ki value: " + String(manager->m_motionControl->m_PIDPosition->GetKi()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDPosParam_Kd(){
    float res = 0.0;
    Serial.println("Enter Kd value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_motionControl->m_PIDPosition->SetKd(res);
        Serial.println("PID Position Kd value: " + String(manager->m_motionControl->m_PIDPosition->GetKd()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDPosParam_MVmin(){
    float res = 0.0;
    Serial.println("Enter MV min value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_motionControl->m_PIDPosition->SetMVRangeMin(res);
        Serial.println("PID Position MV min value: " + String(manager->m_motionControl->m_PIDPosition->GetMVRangeMin()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDPosParam_MVmax(){
    float res = 0.0;
    Serial.println("Enter MV max value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_motionControl->m_PIDPosition->SetMVRangeMax(res);
        Serial.println("PID Position MV max value: " + String(manager->m_motionControl->m_PIDPosition->GetMVRangeMax()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDAngleParam(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDAngleParam_Show(){
    manager->m_motionControl->m_PIDAngle->Print();
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDAngleParam_Kp(){
    float res = 0.0;
    Serial.println("Enter Kp value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_motionControl->m_PIDAngle->SetKp(res);
        Serial.println("PID Angle Kp value: " + String(manager->m_motionControl->m_PIDAngle->GetKp()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDAngleParam_Ki(){
    float res = 0.0;
    Serial.println("Enter Ki value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_motionControl->m_PIDAngle->SetKi(res);
        Serial.println("PID Angle Ki value: " + String(manager->m_motionControl->m_PIDAngle->GetKi()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDAngleParam_Kd(){
    float res = 0.0;
    Serial.println("Enter Kd value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_motionControl->m_PIDAngle->SetKd(res);
        Serial.println("PID Angle Kd value: " + String(manager->m_motionControl->m_PIDAngle->GetKd()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDAngleParam_MVmin(){
    float res = 0.0;
    Serial.println("Enter MV min value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_motionControl->m_PIDAngle->SetMVRangeMin(res);
        Serial.println("PID Angle MV min value: " + String(manager->m_motionControl->m_PIDAngle->GetMVRangeMin()));
    }
}


//=====================================================================================================

void F_CLI_Modules_Motion_PIDAngleParam_MVmax(){
    float res = 0.0;
    Serial.println("Enter MV max value:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        res = insertedValueCLI.toFloat();
        manager->m_motionControl->m_PIDAngle->SetMVRangeMax(res);
        Serial.println("PID Angle MV max value: " + String(manager->m_motionControl->m_PIDAngle->GetMVRangeMax()));
    }
}


//=====================================================================================================

void F_CLI_Debug(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Debug_GetLogLevel(){
    Serial.println("Log Level: " + String(Log.getLevel()));
}


//=====================================================================================================

void F_CLI_Debug_SetLogLevelFatal(){
    Log.setLevel(LOG_LEVEL_FATAL);
    F_CLI_Debug_GetLogLevel();
}


//=====================================================================================================

void F_CLI_Debug_SetLogLevelError(){
    Log.setLevel(LOG_LEVEL_ERROR);
    F_CLI_Debug_GetLogLevel();
}


//=====================================================================================================

void F_CLI_Debug_SetLogLevelWarning(){
    Log.setLevel(LOG_LEVEL_WARNING);
    F_CLI_Debug_GetLogLevel();
}


//=====================================================================================================

void F_CLI_Debug_SetLogLevelInfo(){
    Log.setLevel(LOG_LEVEL_INFO);
    F_CLI_Debug_GetLogLevel();
}


//=====================================================================================================

void F_CLI_Debug_SetLogLevelTrace(){
    Log.setLevel(LOG_LEVEL_TRACE);
    F_CLI_Debug_GetLogLevel();
}


//=====================================================================================================

void F_CLI_Debug_SetLogLevelVerbose(){
    Log.setLevel(LOG_LEVEL_VERBOSE);
    F_CLI_Debug_GetLogLevel();
}


//=====================================================================================================

void F_CLI_Datalog(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Datalog_Start(){
    vTaskResume(TaskDatalogHandle);
}


//=====================================================================================================

void F_CLI_Datalog_Stop(){
    vTaskSuspend(TaskDatalogHandle);
}


//=====================================================================================================

void F_CLI_Datalog_Datasets(){
    GoIntoNewPath();
    Serial.println("Dataset Motor: " + String(datalogDatasets[Datasets_e::DATASET_MOTOR].active));
    Serial.println("Dataset IMU: " + String(datalogDatasets[Datasets_e::DATASET_IMU].active));
    Serial.println("Dataset Odometry: " + String(datalogDatasets[Datasets_e::DATASET_ODOMETRY].active));
    Serial.println("Dataset Motion Control: " + String(datalogDatasets[Datasets_e::DATASET_MOTION_CONTROL].active));
}


//=====================================================================================================

void F_CLI_Datalog_Datasets_Motor(){
    GoIntoNewPath();
    Serial.println("Dataset Motor: " + String(datalogDatasets[Datasets_e::DATASET_MOTOR].active));
}


//=====================================================================================================

void F_CLI_Datalog_Datasets_Motor_Activate(){
    datalogDatasets[Datasets_e::DATASET_MOTOR].active = true;
    Serial.println("Dataset Motor: " + String(datalogDatasets[Datasets_e::DATASET_MOTOR].active));
}


//=====================================================================================================

void F_CLI_Datalog_Datasets_Motor_Deactivate(){
    datalogDatasets[Datasets_e::DATASET_MOTOR].active = false;
    Serial.println("Dataset Motor: " + String(datalogDatasets[Datasets_e::DATASET_MOTOR].active));
}


//=====================================================================================================

void F_CLI_Datalog_Datasets_IMU(){
    GoIntoNewPath();
    Serial.println("Dataset IMU: " + String(datalogDatasets[Datasets_e::DATASET_IMU].active));
}


//=====================================================================================================

void F_CLI_Datalog_Datasets_IMU_Activate(){
    datalogDatasets[Datasets_e::DATASET_IMU].active = true;
    Serial.println("Dataset IMU: " + String(datalogDatasets[Datasets_e::DATASET_IMU].active));
}


//=====================================================================================================

void F_CLI_Datalog_Datasets_IMU_Deactivate(){
    datalogDatasets[Datasets_e::DATASET_IMU].active = false;
    Serial.println("Dataset IMU: " + String(datalogDatasets[Datasets_e::DATASET_IMU].active));
}


//=====================================================================================================

void F_CLI_Datalog_Datasets_Odometry(){
    GoIntoNewPath();
    Serial.println("Dataset Odometry: " + String(datalogDatasets[Datasets_e::DATASET_ODOMETRY].active));
}


//=====================================================================================================

void F_CLI_Datalog_Datasets_Odometry_Activate(){
    datalogDatasets[Datasets_e::DATASET_ODOMETRY].active = true;
    Serial.println("Dataset Odometry: " + String(datalogDatasets[Datasets_e::DATASET_ODOMETRY].active));
}


//=====================================================================================================

void F_CLI_Datalog_Datasets_Odometry_Deactivate(){
    datalogDatasets[Datasets_e::DATASET_ODOMETRY].active = false;
    Serial.println("Dataset Odometry: " + String(datalogDatasets[Datasets_e::DATASET_ODOMETRY].active));
}


//=====================================================================================================

void F_CLI_Datalog_Datasets_MotionControl(){
    GoIntoNewPath();
    Serial.println("Dataset Motion Control: " + String(datalogDatasets[Datasets_e::DATASET_MOTION_CONTROL].active));
}


//=====================================================================================================

void F_CLI_Datalog_Datasets_MotionControl_Activate(){
    datalogDatasets[Datasets_e::DATASET_MOTION_CONTROL].active = true;
    Serial.println("Dataset Motion Control: " + String(datalogDatasets[Datasets_e::DATASET_MOTION_CONTROL].active));
}


//=====================================================================================================

void F_CLI_Datalog_Datasets_MotionControl_Deactivate(){
    datalogDatasets[Datasets_e::DATASET_MOTION_CONTROL].active = false;
    Serial.println("Dataset Motion Control: " + String(datalogDatasets[Datasets_e::DATASET_MOTION_CONTROL].active));
}


//=====================================================================================================

void F_CLI_Datalog_Cycle(){
    GoIntoNewPath();
    Serial.println("Datalog cycle time: " + String(TimerTaskDatalog));
}


//=====================================================================================================

void F_CLI_Datalog_SetCycle(){
    uint cycle = 0;
    Serial.println("Enter the cycle Time (ms) of the Datalog:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        cycle = insertedValueCLI.toInt();
        TimerTaskDatalog = cycle;
        Serial.println("Datalog cycle time: " + String(TimerTaskDatalog));
    }
}


//=====================================================================================================

void F_CLI_Profiles(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Profile_Profile1(){

    Serial.println("Profle1 loaded");
}


//=====================================================================================================

void F_CLI_Profile_Profile2(){

    manager->m_IMU->SetPitchOffset(0.0);

    manager->m_motionControl->m_PIDPitch->SetCycleTime(0.01);
    manager->m_motionControl->m_PIDPitch->SetParameters(11.0, 3.0, 0.04);
    manager->m_motionControl->m_PIDPitch->SetMVRange(-100.0, 100.0);

    manager->m_motionControl->m_PIDPosition->SetCycleTime(0.01);
    manager->m_motionControl->m_PIDPosition->SetParameters(1.0, 1.0, 0.8);
    manager->m_motionControl->m_PIDPosition->SetMVRange(-10.0, 10.0);
    
    manager->m_motionControl->m_PIDAngle->SetCycleTime(0.01);
    manager->m_motionControl->m_PIDAngle->SetParameters(11.0, 2.0, 0.02);
    manager->m_motionControl->m_PIDAngle->SetMVRange(-100.0, 100.0);

    manager->m_motionControl->m_PIDPitch->Print();
    manager->m_motionControl->m_PIDPosition->Print();
    manager->m_motionControl->m_PIDAngle->Print();

    Serial.println("Profle2 loaded");
}


//=====================================================================================================

void F_CLI_Test(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Test_Test1(){
    //manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::REGISTER_51, 251);
}


//=====================================================================================================

void F_CLI_Test_Test2(){

    manager->m_IMU->SetPitchOffset(0.0);

    manager->m_motionControl->m_PIDPitch->SetCycleTime(0.01);
    manager->m_motionControl->m_PIDPitch->SetParameters(11.0, 3.0, 0.04);
    manager->m_motionControl->m_PIDPitch->SetMVRange(-100.0, 100.0);

    manager->m_motionControl->m_PIDPosition->SetCycleTime(0.01);
    manager->m_motionControl->m_PIDPosition->SetParameters(1.0, 1.0, 0.8);
    manager->m_motionControl->m_PIDPosition->SetMVRange(-10.0, 10.0);
    
    manager->m_motionControl->m_PIDAngle->SetCycleTime(0.01);
    manager->m_motionControl->m_PIDAngle->SetParameters(11.0, 2.0, 0.02);
    manager->m_motionControl->m_PIDAngle->SetMVRange(-100.0, 100.0);

    manager->m_motionControl->m_PIDPitch->Print();
    manager->m_motionControl->m_PIDPosition->Print();
    manager->m_motionControl->m_PIDAngle->Print();
    Serial.println("Profle2 loaded");
}


//=====================================================================================================

void F_CLI_Test_Test3(){

}


//=====================================================================================================

void F_CLI_Test_Test4(){

    StartMode(Modes_e::Mode_Motion);

    manager->m_motionControl->Start();

    manager->m_motionControl->m_PIDPitch->Print();
    manager->m_motionControl->m_PIDPosition->Print();
    manager->m_motionControl->m_PIDAngle->Print();
}


//=====================================================================================================

void F_CLI_Test_Test5(){
}


//=====================================================================================================

void F_CLI_Test_Test6(){

}


//=====================================================================================================

void F_CLI_Test_Test7(){

}


//=====================================================================================================

void F_CLI_Test_Test8(){

}


//=====================================================================================================

void F_CLI_Test_Test9(){
    
}


#endif // CLI_H