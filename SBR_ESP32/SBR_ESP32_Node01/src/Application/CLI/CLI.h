/**
 * @file CLI.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief CLI
 * @version 1.0
 * @date 15.02.2023
 * 
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
#include "../../Definition/Local/GlobalVar.h"
#include "../../Definition/Local/LocalConfig.h"
#include "../Tasks/Tasks.h"


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

    CLIOptions[CLIOptions_e::CLI_Modes_Program].path = "21";
    CLIOptions[CLIOptions_e::CLI_Modes_Program].text = "Program";
    CLIOptions[CLIOptions_e::CLI_Modes_Program].Callback = F_CLI_Modes_Program;

    CLIOptions[CLIOptions_e::CLI_Modes_Restart].path = "22";
    CLIOptions[CLIOptions_e::CLI_Modes_Restart].text = "Restart";
    CLIOptions[CLIOptions_e::CLI_Modes_Restart].Callback = F_CLI_Modes_Restart;

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

    CLIOptions[CLIOptions_e::CLI_Monitor_Communication].path = "43";
    CLIOptions[CLIOptions_e::CLI_Monitor_Communication].text = "Communication ->";
    CLIOptions[CLIOptions_e::CLI_Monitor_Communication].Callback = F_CLI_Monitor_Communication;

    CLIOptions[CLIOptions_e::CLI_Monitor_Communication_PrintBufferEsp32].path = "431";
    CLIOptions[CLIOptions_e::CLI_Monitor_Communication_PrintBufferEsp32].text = "Print Buffer ESP32";
    CLIOptions[CLIOptions_e::CLI_Monitor_Communication_PrintBufferEsp32].Callback = F_CLI_Monitor_Communication_PrintBufferEsp32;

    CLIOptions[CLIOptions_e::CLI_Debug].path = "5";
    CLIOptions[CLIOptions_e::CLI_Debug].text = "Debug ->";
    CLIOptions[CLIOptions_e::CLI_Debug].Callback = F_CLI_Debug;

    CLIOptions[CLIOptions_e::CLI_Debug_GetLogLevel].path = "50";
    CLIOptions[CLIOptions_e::CLI_Debug_GetLogLevel].text = "Get Log Level";
    CLIOptions[CLIOptions_e::CLI_Debug_GetLogLevel].Callback = F_CLI_Debug_GetLogLevel;

    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelFatal].path = "51";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelFatal].text = "Set FATAL Log level";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelFatal].Callback = F_CLI_Debug_SetLogLevelFatal;
    
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelError].path = "52";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelError].text = "Set ERROR Log level";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelError].Callback = F_CLI_Debug_SetLogLevelError;

    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelWarning].path = "53";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelWarning].text = "Set WARNING Log level";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelWarning].Callback = F_CLI_Debug_SetLogLevelWarning;

    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelInfo].path = "54";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelInfo].text = "Set INFO Log level";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelInfo].Callback = F_CLI_Debug_SetLogLevelInfo;

    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelTrace].path = "55";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelTrace].text = "Set TRACE Log level";
    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelTrace].Callback = F_CLI_Debug_SetLogLevelTrace;

    CLIOptions[CLIOptions_e::CLI_Debug_SetLogLevelVerbose].path = "56";
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
    currentCLIPath = currentCLIPath + String(incomingCharCLI);
    F_CLI_Info();
}
		          

//=====================================================================================================

void F_CLI_Modes_Program(){
    Serial.println("Program Mode.....");
    manager->m_nodeESP32->Stop();
    manager->m_wifiManager->Connect();
}
		                 

//=====================================================================================================

void F_CLI_Modes_Restart(){
    Serial.println("Restarting...");
    ESP.restart();
}
		                 

//=====================================================================================================

void F_CLI_Settings(){
    currentCLIPath = currentCLIPath + String(incomingCharCLI);
    F_CLI_Info();
}
		                 

//=====================================================================================================

void F_CLI_Settings_Read(){
    Serial.println("F_CLI_Settings_Read");
}
		                   

//=====================================================================================================

void F_CLI_Settings_Write(){
    currentCLIPath = currentCLIPath + String(incomingCharCLI);
    F_CLI_Info();
}
		                  

//=====================================================================================================

void F_CLI_Settings_Write_WifiName(){
    Serial.println("F_CLI_Settings_Write_WifiName");
}
		                    

//=====================================================================================================

void F_CLI_Settings_Write_WifiPassword(){
    Serial.println("F_CLI_Settings_Write_WifiPassword");
}
		                       

//=====================================================================================================

void F_CLI_Monitor(){
    currentCLIPath = currentCLIPath + String(incomingCharCLI);
    F_CLI_Info();
}
		                   

//=====================================================================================================

void F_CLI_Monitor_Tasks(){
    TaskMonitoring();
}
		                   

//=====================================================================================================

void F_CLI_Monitor_Memory(){
    Serial.println("Free Heap: " + String(ESP.getFreeHeap()) + "/" + String(ESP.getHeapSize()));
}
		                     

//=====================================================================================================

void F_CLI_Monitor_Communication(){
    currentCLIPath = currentCLIPath + String(incomingCharCLI);
    F_CLI_Info();
}
                   

//=====================================================================================================

void F_CLI_Monitor_Communication_PrintBufferEsp32(){
    manager->m_nodeESP32->PrintBuffer();
}


//=====================================================================================================

void F_CLI_Debug(){
    currentCLIPath = currentCLIPath + String(incomingCharCLI);
    F_CLI_Info();
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

void F_CLI_Test(){
    currentCLIPath = currentCLIPath + String(incomingCharCLI);
    F_CLI_Info();
}


//=====================================================================================================

void F_CLI_Test_Test1(){
    manager->m_nodeESP32->Start();
    Serial.println("Stating ESP32 Node...");
}


//=====================================================================================================

void F_CLI_Test_Test2(){
    manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::REGISTER_51, 251);
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