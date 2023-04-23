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

    //request->Print();

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
            //ToDo
            break;
        }
        
        case COM_REQUEST_REG_ID_e::MODE_NODE1_START_W: {
            Serial.println("Motion Mode.....");
            StartMode(Modes_e::Mode_Motion);
            Log.infoln("[NodeHandler::MODE_NODE1_START_W] Mode Motion started");
            break;
        }
        
        case COM_REQUEST_REG_ID_e::MODE_NODE1_STOP_W: {
            Serial.println("Idle Mode.....");
            StartMode(Modes_e::Mode_Idle);
            Log.infoln("[NodeHandler::MODE_NODE1_STOP_W] Mode Idle started");
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTOR_LEFT_OFFSET_W: {
            manager->m_motorLeft->SetOffset((double)request->data / 100.0);
            Log.infoln("[NodeHandler::SETUP_MOTOR_LEFT_OFFSET_W] Motor left offset setted: %D", manager->m_motorLeft->GetOffset());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTOR_LEFT_DIRECTION_W: {
            if ((bool)request->data == true){
                manager->m_motorLeft->InvertDirection();
                Log.infoln("[NodeHandler::SETUP_MOTOR_LEFT_DIRECTION_W] Motor left direction inverted: %T", manager->m_motorLeft->GetDirection());
            }
            break;
        }
          
        case COM_REQUEST_REG_ID_e::SETUP_MOTOR_RIGHT_OFFSET_W: {
            manager->m_motorRight->SetOffset((double)request->data / 100.0);
            Log.infoln("[NodeHandler::SETUP_MOTOR_RIGHT_OFFSET_W] Motor right offset setted: %D", manager->m_motorRight->GetOffset());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTOR_RIGHT_DIRECTION_W: {
            if ((bool)request->data == true){
                manager->m_motorRight->InvertDirection();
                Log.infoln("[NodeHandler::SETUP_MOTOR_RIGHT_DIRECTION_W] Motor right direction inverted: %T", manager->m_motorRight->GetDirection());
            }
            break;
        }

        case COM_REQUEST_REG_ID_e::SETUP_IMU_INVERT_PITCH_W: {
            if ((bool)request->data == true){
                manager->m_IMU->InvertPitch();
                Log.infoln("[NodeHandler::SETUP_IMU_INVERT_PITCH_W] IMU Pitch inverted: %T", manager->m_IMU->GetDirectionPitch());
            }
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_IMU_INVERT_ROLL_W: {
            if ((bool)request->data == true){
                manager->m_IMU->InvertRoll();
                Log.infoln("[NodeHandler::SETUP_IMU_INVERT_ROLL_W] IMU Roll inverted: %T", manager->m_IMU->GetDirectionRoll());
            }
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_IMU_INVERT_YAW_W: {
            if ((bool)request->data == true){
                manager->m_IMU->InvertYaw();
                Log.infoln("[NodeHandler::SETUP_IMU_INVERT_YAW_W] IMU Yaw inverted: %T", manager->m_IMU->GetDirectionYaw());
            }
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_IMU_OFFSET_PITCH_W: {
            manager->m_IMU->SetPitchOffset((double)request->data / 100.0);
            Log.infoln("[NodeHandler::SETUP_IMU_OFFSET_PITCH_W] IMU Pitch offset setted: %D", manager->m_IMU->GetPitchOffset());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_ENCODER_LEFT_DIRECTION_W: {
            if ((bool)request->data == true){
                manager->m_encoderLeft->InvertDirection();
                Log.infoln("[NodeHandler::SETUP_ENCODER_LEFT_DIRECTION_W] Encoder left direction inverted: %T", manager->m_encoderLeft->GetDirection());
            }
            break;
        }

        case COM_REQUEST_REG_ID_e::SETUP_ENCODER_RIGHT_DIRECTION_W: {
            if ((bool)request->data == true){
                manager->m_encoderRight->InvertDirection();
                Log.infoln("[NodeHandler::SETUP_ENCODER_RIGHT_DIRECTION_W] Encoder right direction inverted: %T", manager->m_encoderRight->GetDirection());
            }
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_ODOMETRY_WHEEL_RADIO_W: {
            manager->m_odometry->SetRadio((double)request->data / 1000.0);
            Log.infoln("[NodeHandler::SETUP_ODOMETRY_WHEEL_RADIO_W] Odometry Wheel radio setted: %D", manager->m_odometry->GetRadio());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_ODOMETRY_DISTANCE_WHEELS_W: {
            manager->m_odometry->SetDistanceWheels((double)request->data / 1000.0);
            Log.infoln("[NodeHandler::SETUP_ODOMETRY_DISTANCE_WHEELS_W] Odometry distance between wheels setted: %D", manager->m_odometry->GetDistanceWheels());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_KP_W: {
            manager->m_motionControl->m_PIDPitch->SetKp((double)request->data / 1000.0);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_PITCH_KP_W] Motion Control PID Pitch Kp setted: %D", manager->m_motionControl->m_PIDPitch->GetKp());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_KI_W: {
            manager->m_motionControl->m_PIDPitch->SetKi((double)request->data / 1000.0);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_PITCH_KI_W] Motion Control PID Pitch Ki setted: %D", manager->m_motionControl->m_PIDPitch->GetKi());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_KD_W: {
            manager->m_motionControl->m_PIDPitch->SetKd((double)request->data / 1000.0);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_PITCH_KD_W] Motion Control PID Pitch Kd setted: %D", manager->m_motionControl->m_PIDPitch->GetKd());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_DIRECTION_W: {
            if ((bool)request->data == true){
                manager->m_motionControl->m_PIDPitch->SetDirection(PIDDirection_e::PID_DIRECTION_INVERT);
                Log.infoln("[NodeHandler::SETUP_MOTION_PID_PITCH_DIRECTION_W] Motion Control PID Pitch direction inverted: %T", manager->m_motionControl->m_PIDPitch->GetDirection());
            }
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_MV_MIN_W: {
            manager->m_motionControl->m_PIDPitch->SetMVRangeMin((double)request->data / 100.0);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_PITCH_MV_MIN_W] Motion Control PID Pitch MV min setted: %D", manager->m_motionControl->m_PIDPitch->GetMVRangeMin());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_MV_MAX_W: {
            manager->m_motionControl->m_PIDPitch->SetMVRangeMax((double)request->data / 100.0);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_PITCH_MV_MAX_W] Motion Control PID Pitch MV max setted: %D", manager->m_motionControl->m_PIDPitch->GetMVRangeMax());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_KP_W: {
            manager->m_motionControl->m_PIDPosition->SetKp((double)request->data / 1000.0);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_POSITION_KP_W] Motion Control PID Position Kp setted: %D", manager->m_motionControl->m_PIDPosition->GetKp());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_KI_W: {
            manager->m_motionControl->m_PIDPosition->SetKi((double)request->data / 1000.0);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_POSITION_KI_W] Motion Control PID Position Ki setted: %D", manager->m_motionControl->m_PIDPosition->GetKi());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_KD_W: {
            manager->m_motionControl->m_PIDPosition->SetKd((double)request->data / 1000.0);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_POSITION_KD_W] Motion Control PID Position Kd setted: %D", manager->m_motionControl->m_PIDPosition->GetKd());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_DIRECTION_W: {
            if ((bool)request->data == true){
                manager->m_motionControl->m_PIDPosition->SetDirection(PIDDirection_e::PID_DIRECTION_INVERT);
                Log.infoln("[NodeHandler::SETUP_MOTION_PID_POSITION_DIRECTION_W] Motion Control PID Position direction inverted: %T", manager->m_motionControl->m_PIDPosition->GetDirection());
            }
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_MV_MIN_W: {
            manager->m_motionControl->m_PIDPosition->SetMVRangeMin((double)request->data / 100.0);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_POSITION_MV_MIN_W] Motion Control PID Position MV min setted: %D", manager->m_motionControl->m_PIDPosition->GetMVRangeMin());
            break;
        }
        
        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_MV_MAX_W: {
            manager->m_motionControl->m_PIDPosition->SetMVRangeMax((double)request->data / 100.0);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_POSITION_MV_MAX_W] Motion Control PID Angle MV max setted: %D", manager->m_motionControl->m_PIDPosition->GetMVRangeMax());
            break;
        }

        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_KP_W: {
            manager->m_motionControl->m_PIDAngle->SetKp((double)request->data / 1000.0);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_ANGLE_KP_W] Motion Control PID Angle Kp setted: %D", manager->m_motionControl->m_PIDAngle->GetKp());
            break;
        }

        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_KI_W: {
            manager->m_motionControl->m_PIDAngle->SetKi((double)request->data / 1000.0);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_ANGLE_KI_W] Motion Control PID Angle Ki setted: %D", manager->m_motionControl->m_PIDAngle->GetKi());
            break;
        }

        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_KD_W: {
            manager->m_motionControl->m_PIDAngle->SetKd((double)request->data / 1000.0);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_ANGLE_KD_W] Motion Control PID Angle Kd setted: %D", manager->m_motionControl->m_PIDAngle->GetKd());
            break;
        }

        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_DIRECTION_W: {
            if ((bool)request->data == true){
                manager->m_motionControl->m_PIDAngle->SetDirection(PIDDirection_e::PID_DIRECTION_INVERT);
                Log.infoln("[NodeHandler::SETUP_MOTION_PID_ANGLE_DIRECTION_W] Motion Control PID Angle direction inverted: %T", manager->m_motionControl->m_PIDAngle->GetDirection());
            }
            break;
        }

        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_MV_MIN_W: {
            manager->m_motionControl->m_PIDAngle->SetMVRangeMin((double)request->data / 100.0);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_ANGLE_MV_MIN_W] Motion Control PID Angle MV min setted: %D", manager->m_motionControl->m_PIDAngle->GetMVRangeMin());
            break;
        }

        case COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_MV_MAX_W: {
            manager->m_motionControl->m_PIDAngle->SetMVRangeMax((double)request->data / 100.0);
            Log.infoln("[NodeHandler::SETUP_MOTION_PID_ANGLE_MV_MAX_W] Motion Control PID Angle MV max setted: %D", manager->m_motionControl->m_PIDAngle->GetMVRangeMax());
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
            if ((bool)request->data == true){
                manager->m_odometry->Reset();
                // ToDo: send response. Implemente commands states
                Log.infoln("[NodeHandler::LIVE_ODOMETRY_RESET_W] Odometry resetted");
            }
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


#endif // NODEHANDLER_H