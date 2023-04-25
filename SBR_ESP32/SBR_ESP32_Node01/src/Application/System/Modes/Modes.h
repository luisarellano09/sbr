/**
 * @file Modes.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Modes of the robot
 * 
 */

#ifndef MODES_H
#define MODES_H


/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include <ArduinoLog.h>
#include "ModesConfig.h"
#include "../../../Definition/Local/GlobalVar.h"


/*******************************************************************************************************************************************
 *  												DEFINITION FUNCTIONS
 *******************************************************************************************************************************************/

void InitModes(){
    Modes[Modes_e::Mode_Idle].Callback = SM_ModeIdle;
    Modes[Modes_e::Mode_Program].Callback = SM_ModeProgram;
    Modes[Modes_e::Mode_Motion].Callback = SM_ModeMotion;

    StartMode(Modes_e::Mode_Idle);
    Log.traceln("[Modes::InitModes] Mode Idle started");
}


//=====================================================================================================

void StartMode(Modes_e mode){
    Modes[mode].status = 1;
}


//=====================================================================================================

void StopMode(Modes_e mode){
    Modes[mode].status = 0;
}


//=====================================================================================================

void RunModes(){
    for (int i=0;i<Modes_e::LENGTH_MODES;i++){
        if (Modes[i].status == 1) {
            Modes[i].Callback((Modes_e)i);
        }
    }
}


//=====================================================================================================

void SM_ModeIdle(Modes_e mode){
    
    stateModeIdle = NextStateModeIdle;

    switch(stateModeIdle){

        case StateModeIdle_e::StateModeIdle_Idle:
            NextStateModeIdle = StateModeIdle_e::StateModeIdle_DeactivateTasks;
            break;

        case StateModeIdle_e::StateModeIdle_DeactivateTasks:
            vTaskSuspend(TaskOTAHandle);
            vTaskSuspend(TaskGetValueCLIHandle);
            vTaskSuspend(TaskMotionControlHandle);
            vTaskSuspend(TaskDatalogHandle);
            NextStateModeIdle = StateModeIdle_e::StateModeIdle_ActivateTaskCLI;
            break;

        case StateModeIdle_e::StateModeIdle_ActivateTaskCLI:
            vTaskResume(TaskCLIHandle);
            NextStateModeIdle = StateModeIdle_e::StateModeIdle_ActivateTaskNodeESP32;
            break;

        case StateModeIdle_e::StateModeIdle_ActivateTaskNodeESP32:
            vTaskResume(TaskNodeESP32Handle);
            vTaskResume(TaskRegistersUpdateFastHandle);
            vTaskResume(TaskRegistersUpdateSlowHandle);
            currentMode = Modes_e::Mode_Idle;
            NextStateModeIdle = StateModeIdle_e::StateModeIdle_ChangeStatusToInactive;
            break;

        case StateModeIdle_e::StateModeIdle_ChangeStatusToInactive:
            StopMode(mode);
            NextStateModeIdle = StateModeIdle_e::StateModeIdle_Idle;
            break;
    }
}


//=====================================================================================================

void SM_ModeProgram(Modes_e mode){

    stateModeProgram = NextStateModeProgram;

    switch(stateModeProgram){

        case StateModeProgram_e::StateModeProgram_Idle:
            NextStateModeProgram = StateModeProgram_e::StateModeProgram_DeactivateTasks;
            break;

        case StateModeProgram_e::StateModeProgram_DeactivateTasks:
            vTaskSuspend(TaskNodeESP32Handle);
            vTaskSuspend(TaskRegistersUpdateFastHandle);
            vTaskSuspend(TaskRegistersUpdateSlowHandle); 
            vTaskSuspend(TaskIMUHandle);
            vTaskSuspend(TaskOdometryHandle);
            vTaskSuspend(TaskMotionControlHandle);
            vTaskSuspend(TaskDatalogHandle);
            manager->m_motorLeft->Stop();
            manager->m_motorRight->Stop();
            NextStateModeProgram = StateModeProgram_e::StateModeProgram_ActivateWifi;
            break;

        case StateModeProgram_e::StateModeProgram_ActivateWifi:
            manager->m_wifiManager->Connect();
            NextStateModeProgram = StateModeProgram_e::StateModeProgram_ActivateTaskOTA;
            break;

        case StateModeProgram_e::StateModeProgram_ActivateTaskOTA:
            vTaskResume(TaskOTAHandle);
            currentMode = Modes_e::Mode_Program;
            NextStateModeProgram = StateModeProgram_e::StateModeProgram_ChangeStatusToInactive;
            break;

        case StateModeProgram_e::StateModeProgram_ChangeStatusToInactive:
            StopMode(mode);
            NextStateModeProgram = StateModeProgram_e::StateModeProgram_Idle;
            break;
    }
}


//=====================================================================================================

void SM_ModeMotion(Modes_e mode){

    stateModeMotion = NextStateModeMotion;

    switch(stateModeMotion){

        case StateModeMotion_e::StateModeMotion_Idle:
            NextStateModeMotion = StateModeMotion_e::StateModeMotion_ActivateTaskIMU;
            break;

        case StateModeMotion_e::StateModeMotion_ActivateTaskIMU:
            vTaskResume(TaskIMUHandle);
            NextStateModeMotion = StateModeMotion_e::StateModeMotion_ActivateTaskOdometry;
            break;

        case StateModeMotion_e::StateModeMotion_ActivateTaskOdometry:
            vTaskResume(TaskOdometryHandle);
            NextStateModeMotion = StateModeMotion_e::StateModeMotion_ActivateTaskMotionControl;
            break;

        case StateModeMotion_e::StateModeMotion_ActivateTaskMotionControl:
            vTaskResume(TaskMotionControlHandle);
            currentMode = Modes_e::Mode_Motion;
            NextStateModeMotion = StateModeMotion_e::StateModeMotion_ChangeStatusToInactive;
            break;

        case StateModeMotion_e::StateModeMotion_ChangeStatusToInactive:
            StopMode(mode);
            NextStateModeMotion = StateModeMotion_e::StateModeMotion_Idle;
            break;
    }
}

#endif // MODES_H