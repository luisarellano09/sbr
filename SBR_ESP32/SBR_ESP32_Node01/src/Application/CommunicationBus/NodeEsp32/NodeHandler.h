/**
 * @file NodeHandler.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Handler of the Node
 * 
 */

#ifndef NODEHANDLER_H
#define NODEHANDLER_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "../../../Middleware/CommunicationBus/Request/Request.h"
#include "../../System/Tasks/Tasks.h"
#include <ArduinoLog.h>


/*******************************************************************************************************************************************
 *  												DEFINITION FUNCTIONS
 *******************************************************************************************************************************************/

RC_e ExtHandler(Request* request){
    
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check if the pointer is null
    if (request == NULL){
        Log.fatalln("[NodeHandler::ExtHandler] request ERROR_NULL_POINTER");
        return RC_e::ERROR_NULL_POINTER;
    }

    Log.traceln("[NodeHandler::ExtHandler] Request received: nodeId=%d, reqType=%d, regId=%d, data=%d, CRC=%d", request->nodeId, request->reqType, request->regId, request->data, request->CRC);

    switch(request->regId){

        case COM_REQUEST_REG_ID_e::STATUS_HEARTBEAT_ESP32_COUNTER_R: {
            manager->m_nodeESP32->TokenCounter(request->data, COM_REQUEST_REG_ID_e::STATUS_HEARTBEAT_ESP32_COUNTER_R);
            break;
        }
        
        case COM_REQUEST_REG_ID_e::MODE_NODE1_RESTART_W: {
            Serial.println("Restarting...");
            ESP.restart();
            break;
        }
        
        case COM_REQUEST_REG_ID_e::MODE_NODE1_PROGRAM_W: {
            Serial.println("Program Mode.....");
            StartMode(Modes_e::Mode_Program);
            Log.infoln("[NodeHandler::MODE_NODE1_PROGRAM_W] Mode Program started");
            break;
        }
        
        case COM_REQUEST_REG_ID_e::MODE_NODE1_SYNC_DATA_RW: {
            if ( (RegisterCommand_e)request->data == RegisterCommand_e::CMD_READY_TO_COMPLETE ) {
                manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::MODE_NODE1_SYNC_DATA_RW, RegisterCommand_e::CMD_COMPLETED);
            }
            break;
        }
        
        case COM_REQUEST_REG_ID_e::MODE_NODE1_START_W: {
            manager->m_motionControl->Start();
            Log.infoln("[NodeHandler::MODE_NODE1_START_W] Start Motion");
            break;
        }
        
        case COM_REQUEST_REG_ID_e::MODE_NODE1_STOP_W: {
            manager->m_motionControl->Stop();
            Log.infoln("[NodeHandler::MODE_NODE1_STOP_W] Stop Motion");
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTOR_LEFT_OFFSET_W: {
            manager->m_motorLeft->SetOffset((double)request->data / 100.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTOR_LEFT_OFFSET_R, manager->m_motorLeft->GetOffset() * 100);
            Log.infoln("[NodeHandler::SETUP_MOTOR_LEFT_OFFSET_W] Motor left offset setted: %D", manager->m_motorLeft->GetOffset());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTOR_LEFT_DIRECTION_W: {
            manager->m_motorLeft->SetDirection((bool)request->data);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTOR_LEFT_DIRECTION_R, manager->m_motorLeft->GetDirection());
            Log.infoln("[NodeHandler::SETUP_MOTOR_LEFT_DIRECTION_W] Motor left direction: %T", manager->m_motorLeft->GetDirection());
            break;
        }
          
        case COM_REQUEST_REG_ID_e::SETUP_MOTOR_RIGHT_OFFSET_W: {
            manager->m_motorRight->SetOffset((double)request->data / 100.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTOR_RIGHT_OFFSET_R, manager->m_motorRight->GetOffset() * 100);
            Log.infoln("[NodeHandler::SETUP_MOTOR_RIGHT_OFFSET_W] Motor right offset setted: %D", manager->m_motorRight->GetOffset());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTOR_RIGHT_DIRECTION_W: {
            manager->m_motorRight->SetDirection((bool)request->data);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTOR_RIGHT_DIRECTION_R, manager->m_motorRight->GetDirection());
            Log.infoln("[NodeHandler::SETUP_MOTOR_RIGHT_DIRECTION_W] Motor right direction: %T", manager->m_motorRight->GetDirection());
            break;
        }

        case COM_REQUEST_REG_ID_e::SETUP_IMU_INVERT_PITCH_W: {
            manager->m_IMU->SetDirectionPitch((bool)request->data);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_IMU_INVERT_PITCH_R, manager->m_IMU->GetDirectionPitch());
            Log.infoln("[NodeHandler::SETUP_IMU_INVERT_PITCH_W] IMU Pitch direction: %T", manager->m_IMU->GetDirectionPitch());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_IMU_INVERT_ROLL_W: {
            manager->m_IMU->SetDirectionRoll((bool)request->data);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_IMU_INVERT_ROLL_R, manager->m_IMU->GetDirectionRoll());
            Log.infoln("[NodeHandler::SETUP_IMU_INVERT_ROLL_W] IMU Roll direction: %T", manager->m_IMU->GetDirectionRoll());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_IMU_INVERT_YAW_W: {
            manager->m_IMU->SetDirectiontYaw((bool)request->data);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_IMU_INVERT_YAW_R, manager->m_IMU->GetDirectionYaw());
            Log.infoln("[NodeHandler::SETUP_IMU_INVERT_YAW_W] IMU Yaw direction: %T", manager->m_IMU->GetDirectionYaw());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_IMU_OFFSET_PITCH_W: {
            manager->m_IMU->SetPitchOffset((double)request->data / 100.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_IMU_OFFSET_PITCH_R, manager->m_IMU->GetPitchOffset() * 100);
            Log.infoln("[NodeHandler::SETUP_IMU_OFFSET_PITCH_W] IMU Pitch offset setted: %D", manager->m_IMU->GetPitchOffset());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_ENCODER_LEFT_DIRECTION_W: {
            manager->m_encoderLeft->SetDirection((bool)request->data);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_ENCODER_LEFT_DIRECTION_R, manager->m_encoderLeft->GetDirection());
            Log.infoln("[NodeHandler::SETUP_ENCODER_LEFT_DIRECTION_W] Encoder left direction: %T", manager->m_encoderLeft->GetDirection());
            break;
        }

        case COM_REQUEST_REG_ID_e::SETUP_ENCODER_RIGHT_DIRECTION_W: {
            manager->m_encoderRight->SetDirection((bool)request->data);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_ENCODER_RIGHT_DIRECTION_R, manager->m_encoderRight->GetDirection());
            Log.infoln("[NodeHandler::SETUP_ENCODER_RIGHT_DIRECTION_W] Encoder right direction: %T", manager->m_encoderRight->GetDirection());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_ODOMETRY_WHEEL_RADIO_W: {
            manager->m_odometry->SetRadio((double)request->data / 1000.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_ODOMETRY_WHEEL_RADIO_R, manager->m_odometry->GetRadio() * 1000);
            Log.infoln("[NodeHandler::SETUP_ODOMETRY_WHEEL_RADIO_W] Odometry Wheel radio setted: %D cm", manager->m_odometry->GetRadio() * 100);
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_ODOMETRY_DISTANCE_WHEELS_W: {
            manager->m_odometry->SetDistanceWheels((double)request->data / 1000.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_ODOMETRY_DISTANCE_WHEELS_R, manager->m_odometry->GetDistanceWheels() * 1000);
            Log.infoln("[NodeHandler::SETUP_ODOMETRY_DISTANCE_WHEELS_W] Odometry distance between wheels setted: %D cm", manager->m_odometry->GetDistanceWheels() * 100);
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_KP_W: {
            manager->m_motionControl->m_PIDPitch->SetKp((double)request->data / 1000.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_KP_R, manager->m_motionControl->m_PIDPitch->GetKp() * 1000);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_PITCH_KP_W] Motion Control PID Pitch Kp setted: %D", manager->m_motionControl->m_PIDPitch->GetKp());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_KI_W: {
            manager->m_motionControl->m_PIDPitch->SetKi((double)request->data / 1000.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_KI_R, manager->m_motionControl->m_PIDPitch->GetKi() * 1000);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_PITCH_KI_W] Motion Control PID Pitch Ki setted: %D", manager->m_motionControl->m_PIDPitch->GetKi());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_KD_W: {
            manager->m_motionControl->m_PIDPitch->SetKd((double)request->data / 1000.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_KD_R, manager->m_motionControl->m_PIDPitch->GetKd() * 1000);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_PITCH_KD_W] Motion Control PID Pitch Kd setted: %D", manager->m_motionControl->m_PIDPitch->GetKd());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_DIRECTION_W: {
            manager->m_motionControl->m_PIDPitch->SetDirection((bool)request->data);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_DIRECTION_R, manager->m_motionControl->m_PIDPitch->GetDirection());
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_CYCLE_R, manager->m_motionControl->m_PIDPitch->GetCycleTime() * 1000.0);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_PITCH_DIRECTION_W] Motion Control PID Pitch direction: %T", manager->m_motionControl->m_PIDPitch->GetDirection());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_MV_MIN_W: {
            manager->m_motionControl->m_PIDPitch->SetMVRangeMin((double)request->data / 100.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_MV_MIN_R, manager->m_motionControl->m_PIDPitch->GetMVRangeMin() * 100);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_PITCH_MV_MIN_W] Motion Control PID Pitch MV min setted: %D", manager->m_motionControl->m_PIDPitch->GetMVRangeMin());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_MV_MAX_W: {
            manager->m_motionControl->m_PIDPitch->SetMVRangeMax((double)request->data / 100.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_MV_MAX_R, manager->m_motionControl->m_PIDPitch->GetMVRangeMax() * 100);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_PITCH_MV_MAX_W] Motion Control PID Pitch MV max setted: %D", manager->m_motionControl->m_PIDPitch->GetMVRangeMax());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_KP_W: {
            manager->m_motionControl->m_PIDPosition->SetKp((double)request->data / 1000.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_KP_R, manager->m_motionControl->m_PIDPosition->GetKp() * 1000);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_POSITION_KP_W] Motion Control PID Position Kp setted: %D", manager->m_motionControl->m_PIDPosition->GetKp());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_KI_W: {
            manager->m_motionControl->m_PIDPosition->SetKi((double)request->data / 1000.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_KI_R, manager->m_motionControl->m_PIDPosition->GetKi() * 1000);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_POSITION_KI_W] Motion Control PID Position Ki setted: %D", manager->m_motionControl->m_PIDPosition->GetKi());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_KD_W: {
            manager->m_motionControl->m_PIDPosition->SetKd((double)request->data / 1000.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_KD_R, manager->m_motionControl->m_PIDPosition->GetKd() * 1000);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_POSITION_KD_W] Motion Control PID Position Kd setted: %D", manager->m_motionControl->m_PIDPosition->GetKd());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_DIRECTION_W: {
            manager->m_motionControl->m_PIDPosition->SetDirection((bool)request->data);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_DIRECTION_R, manager->m_motionControl->m_PIDPosition->GetDirection());
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_CYCLE_R, manager->m_motionControl->m_PIDPosition->GetCycleTime() * 1000.0);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_POSITION_DIRECTION_W] Motion Control PID Position direction: %T", manager->m_motionControl->m_PIDPosition->GetDirection());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_MV_MIN_W: {
            manager->m_motionControl->m_PIDPosition->SetMVRangeMin((double)request->data / 100.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_MV_MIN_R, manager->m_motionControl->m_PIDPosition->GetMVRangeMin() * 100);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_POSITION_MV_MIN_W] Motion Control PID Position MV min setted: %D", manager->m_motionControl->m_PIDPosition->GetMVRangeMin());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_MV_MAX_W: {
            manager->m_motionControl->m_PIDPosition->SetMVRangeMax((double)request->data / 100.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_MV_MAX_R, manager->m_motionControl->m_PIDPosition->GetMVRangeMax() * 100);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_POSITION_MV_MAX_W] Motion Control PID Angle MV max setted: %D", manager->m_motionControl->m_PIDPosition->GetMVRangeMax());
            break;
        }

        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_KP_W: {
            manager->m_motionControl->m_PIDAngle->SetKp((double)request->data / 1000.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_KP_R, manager->m_motionControl->m_PIDAngle->GetKp() * 1000);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_ANGLE_KP_W] Motion Control PID Angle Kp setted: %D", manager->m_motionControl->m_PIDAngle->GetKp());
            break;
        }

        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_KI_W: {
            manager->m_motionControl->m_PIDAngle->SetKi((double)request->data / 1000.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_KI_R, manager->m_motionControl->m_PIDAngle->GetKi() * 1000);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_ANGLE_KI_W] Motion Control PID Angle Ki setted: %D", manager->m_motionControl->m_PIDAngle->GetKi());
            break;
        }

        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_KD_W: {
            manager->m_motionControl->m_PIDAngle->SetKd((double)request->data / 1000.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_KD_R, manager->m_motionControl->m_PIDAngle->GetKd() * 1000);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_ANGLE_KD_W] Motion Control PID Angle Kd setted: %D", manager->m_motionControl->m_PIDAngle->GetKd());
            break;
        }

        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_DIRECTION_W: {
            manager->m_motionControl->m_PIDAngle->SetDirection((bool)request->data);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_DIRECTION_R, manager->m_motionControl->m_PIDAngle->GetDirection());
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_CYCLE_R, manager->m_motionControl->m_PIDAngle->GetCycleTime() * 1000.0);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_ANGLE_DIRECTION_W] Motion Control PID Angle direction: %T", manager->m_motionControl->m_PIDAngle->GetDirection());
            break;
        }

        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_MV_MIN_W: {
            manager->m_motionControl->m_PIDAngle->SetMVRangeMin((double)request->data / 100.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_MV_MIN_R, manager->m_motionControl->m_PIDAngle->GetMVRangeMin() * 100);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_ANGLE_MV_MIN_W] Motion Control PID Angle MV min setted: %D", manager->m_motionControl->m_PIDAngle->GetMVRangeMin());
            break;
        }

        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_MV_MAX_W: {
            manager->m_motionControl->m_PIDAngle->SetMVRangeMax((double)request->data / 100.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_MV_MAX_R, manager->m_motionControl->m_PIDAngle->GetMVRangeMax() * 100);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_ANGLE_MV_MAX_W] Motion Control PID Angle MV max setted: %D", manager->m_motionControl->m_PIDAngle->GetMVRangeMax());
            break;
        }

        case COM_REQUEST_REG_ID_e::SETUP_MOTION_FALLDOWN_OFFSET_W: {
            manager->m_motionControl->SetFalldownOffset((double)request->data / 100.0);
            manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::SETUP_MOTION_FALLDOWN_OFFSET_R, manager->m_motionControl->GetFalldownOffset() * 100);
            Log.infoln("[NodeHandler::SETUP_MOTION_FALLDOWN_OFFSET_W] Motion Control FallDown offset setted: %D", manager->m_motionControl->GetFalldownOffset());
            break;
        }

        case COM_REQUEST_REG_ID_e::LIVE_MOTOR_LEFT_SPEED_W: {
            manager->m_motorLeft->SetSpeed((double)request->data / 100.0);
            Log.infoln("[NodeHandler::LIVE_MOTOR_LEFT_SPEED_W] Motor left speed setted: %D", manager->m_motorLeft->GetSpeed());
            break;
        }

        case COM_REQUEST_REG_ID_e::LIVE_MOTOR_RIGHT_SPEED_W: {
            manager->m_motorRight->SetSpeed((double)request->data / 100.0);
            Log.infoln("[NodeHandler::LIVE_MOTOR_RIGHT_SPEED_W] Motor right speed setted: %D", manager->m_motorRight->GetSpeed());
            break;
        }

        case COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_X_W: {
            manager->m_odometry->SetX((double)request->data / 1000.0);
            Log.infoln("[NodeHandler::LIVE_ODOMETRY_X_W] Odometry X setted: %D", manager->m_odometry->GetX());
            break;
        }

        case COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_Y_W: {
            manager->m_odometry->SetY((double)request->data / 1000.0);
            Log.infoln("[NodeHandler::LIVE_ODOMETRY_Y_W] Odometry Y setted: %D", manager->m_odometry->GetY());
            break;
        }

        case COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_ANGLE_W: {
            manager->m_odometry->SetAngle((double)request->data / 100.0);
            Log.infoln("[NodeHandler::LIVE_ODOMETRY_ANGLE_W] Odometry Angle setted: %D", manager->m_odometry->GetAngle());
            break;
        }

        case COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_DISTANCE_W: {
            manager->m_odometry->SetDistance((double)request->data / 1000.0);
            Log.infoln("[NodeHandler::LIVE_ODOMETRY_DISTANCE_W] Odometry Distance setted: %D", manager->m_odometry->GetDistance());
            break;
        }

        case COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_RESET_W: {
            manager->m_odometry->Reset();
            Log.infoln("[NodeHandler::LIVE_ODOMETRY_RESET_W] Odometry resetted");
            break;
        }

        case COM_REQUEST_REG_ID_e::LIVE_MOTION_SP_POSITION_W: {
            manager->m_motionControl->SetSPPos( manager->m_motionControl->GetSPPos() + (double)request->data / 1000.0 );
            Log.infoln("[NodeHandler::LIVE_MOTION_SP_POSITION_W] Motion Control Position SP setted: %D", manager->m_motionControl->GetSPPos());
            break;
        }

        case COM_REQUEST_REG_ID_e::LIVE_MOTION_SP_ANGLE_W: {
            manager->m_motionControl->SetSPAngle( manager->m_motionControl->GetSPAngle() + (double)request->data / 100.0 );
            Log.infoln("[NodeHandler::LIVE_MOTION_SP_ANGLE_W] Motion Control Angle SP setted: %D", manager->m_motionControl->GetSPAngle());
            break;
        }
    }

    return retCode;
}


//=====================================================================================================

RC_e UpdateRegistersRT(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    if (manager->m_nodeESP32->GetError() == false) {
        manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::MODE_NODE1_MODE_R, currentMode);
        manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::LIVE_MOTOR_LEFT_SPEED_R, manager->m_motorLeft->GetSpeed() * 100);
        manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::LIVE_MOTOR_RIGHT_SPEED_R, manager->m_motorRight->GetSpeed() * 100);
        manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::LIVE_IMU_PITCH_R, manager->m_IMU->GetPitch() * 100);
        manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::LIVE_IMU_ROLL_R, manager->m_IMU->GetRoll() * 100);
        manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::LIVE_IMU_YAW_R, manager->m_IMU->GetYaw() * 100);
        manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::LIVE_ENCODER_LEFT_COUNT_R, manager->m_encoderLeft->GetCount());
        manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::LIVE_ENCODER_RIGHT_COUNT_R, manager->m_encoderRight->GetCount());
        manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_X_R, manager->m_odometry->GetX() * 1000);
        manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_Y_R, manager->m_odometry->GetY() * 1000);
        manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_ANGLE_R, manager->m_odometry->GetAngle() * 100);
        manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_DISTANCE_R, manager->m_odometry->GetDistance() * 1000);
        manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::LIVE_MOTION_SP_POSITION_R, manager->m_motionControl->GetSPPos() * 1000);
        manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::LIVE_MOTION_SP_ANGLE_R, manager->m_motionControl->GetSPAngle() * 100);
        manager->m_nodeESP32->UpdateRegister(COM_REQUEST_REG_ID_e::LIVE_MOTION_FALLDOWN_R, manager->m_motionControl->IsFalldown());
    }

    return retCode;
}


#endif // NODEHANDLER_H