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

    CLIOptions[CLIOptions_e::CLI_Modules_Communication_PrintTable].path = "511";
    CLIOptions[CLIOptions_e::CLI_Modules_Communication_PrintTable].text = "Print Table";
    CLIOptions[CLIOptions_e::CLI_Modules_Communication_PrintTable].Callback = F_CLI_Modules_Communication_PrintTable;

    CLIOptions[CLIOptions_e::CLI_Modules_Communication_PrintBufferEsp32].path = "512";
    CLIOptions[CLIOptions_e::CLI_Modules_Communication_PrintBufferEsp32].text = "Print Buffer ESP32";
    CLIOptions[CLIOptions_e::CLI_Modules_Communication_PrintBufferEsp32].Callback = F_CLI_Modules_Communication_PrintBufferEsp32;

    CLIOptions[CLIOptions_e::CLI_Modules_Communication_PrintBufferLinux].path = "513";
    CLIOptions[CLIOptions_e::CLI_Modules_Communication_PrintBufferLinux].text = "Print Buffer Linux";
    CLIOptions[CLIOptions_e::CLI_Modules_Communication_PrintBufferLinux].Callback = F_CLI_Modules_Communication_PrintBufferLinux;

    CLIOptions[CLIOptions_e::CLI_Modules_Communication_SetRegister].path = "514";
    CLIOptions[CLIOptions_e::CLI_Modules_Communication_SetRegister].text = "Set Registers";
    CLIOptions[CLIOptions_e::CLI_Modules_Communication_SetRegister].Callback = F_CLI_Modules_Communication_SetRegister;

    CLIOptions[CLIOptions_e::CLI_Modules_Communication_ReadRegister].path = "515";
    CLIOptions[CLIOptions_e::CLI_Modules_Communication_ReadRegister].text = "Read Register";
    CLIOptions[CLIOptions_e::CLI_Modules_Communication_ReadRegister].Callback = F_CLI_Modules_Communication_ReadRegister;

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

void F_CLI_Modules_Communication_PrintTable(){
    manager->m_tableRegister->PrintTable();
}


//=====================================================================================================

void F_CLI_Modules_Communication_PrintBufferEsp32(){
    manager->m_nodeESP32->PrintBuffer();
}


//=====================================================================================================

void F_CLI_Modules_Communication_PrintBufferLinux(){
    manager->m_nodeLinux->PrintBuffer();
}


//=====================================================================================================

void F_CLI_Modules_Communication_SetRegister(){
    // Register
    uint16_t reg = 0;
    Serial.println("Enter Register:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        reg = insertedValueCLI.toInt();

        // Data
        int32_t data = 0;
        Serial.println("Enter Data:");
        ActivateGetValueModeCLI();
        if (!insertedValueCLI.equals("")){
            data = insertedValueCLI.toInt();
            manager->m_tableRegister->UpdateRegister((COM_REQUEST_REG_ID_e)reg, data);
            Serial.println("Setted Register[" + String(reg) + "] = " + String(data));
        }
    }
}


//=====================================================================================================

void F_CLI_Modules_Communication_ReadRegister(){
    // Register
    uint16_t reg = 0;
    Serial.println("Enter Register:");
    ActivateGetValueModeCLI();
    if (!insertedValueCLI.equals("")){
        reg = insertedValueCLI.toInt();
        manager->m_tableRegister->PrintRegister((COM_REQUEST_REG_ID_e)reg);
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
    preferences.putInt("LOG_LEVEL", LOG_LEVEL_FATAL);
    F_CLI_Debug_GetLogLevel();
}


//=====================================================================================================

void F_CLI_Debug_SetLogLevelError(){
    Log.setLevel(LOG_LEVEL_ERROR);
    preferences.putInt("LOG_LEVEL", LOG_LEVEL_ERROR);
    F_CLI_Debug_GetLogLevel();
}


//=====================================================================================================

void F_CLI_Debug_SetLogLevelWarning(){
    Log.setLevel(LOG_LEVEL_WARNING);
    preferences.putInt("LOG_LEVEL", LOG_LEVEL_WARNING);
    F_CLI_Debug_GetLogLevel();
}


//=====================================================================================================

void F_CLI_Debug_SetLogLevelInfo(){
    Log.setLevel(LOG_LEVEL_INFO);
    preferences.putInt("LOG_LEVEL", LOG_LEVEL_INFO);
    F_CLI_Debug_GetLogLevel();
}


//=====================================================================================================

void F_CLI_Debug_SetLogLevelTrace(){
    Log.setLevel(LOG_LEVEL_TRACE);
    preferences.putInt("LOG_LEVEL", LOG_LEVEL_TRACE);
    F_CLI_Debug_GetLogLevel();
}


//=====================================================================================================

void F_CLI_Debug_SetLogLevelVerbose(){
    Log.setLevel(LOG_LEVEL_VERBOSE);
    preferences.putInt("LOG_LEVEL", LOG_LEVEL_VERBOSE);
    F_CLI_Debug_GetLogLevel();
}


//=====================================================================================================

void F_CLI_Test(){
    GoIntoNewPath();
}


//=====================================================================================================

void F_CLI_Test_Test1(){

}


//=====================================================================================================

void F_CLI_Test_Test2(){

}


//=====================================================================================================

void F_CLI_Test_Test3(){

}


//=====================================================================================================

void F_CLI_Test_Test4(){

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