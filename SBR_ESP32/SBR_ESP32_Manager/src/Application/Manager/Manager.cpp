/**
 * @file Manager.cpp
 * @author Luis Arellano - luis.arellano09@gmail.com
 * @brief Class to Manage the ESP32
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "Manager.h"
#include "../../Definition/Local/LocalConfig.h"
#include <ArduinoLog.h>

/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

Manager::Manager(){

    // Wifi Manager
    this->m_wifiManager = new WifiManager();
    Log.traceln("[Manager::Manager] WifiManager instanced");

    // Nodes Manager
    this->m_nodeESP32 = new NodeEsp32(&Serial1, NODE_ESP32s_BAUDRATE, NODE_ESP32s_RX, NODE_ESP32s_TX);
    Log.traceln("[Manager::Manager] NodeEsp32 instanced");
    this->m_nodeLinux = new NodeLinux(&Serial2, NODE_LINUX_BAUDRATE, NODE_LINUX_RX, NODE_LINUX_TX);
    Log.traceln("[Manager::Manager] NodeLinux instanced");

    // Table RT
    this->m_tableRegister = new RegisterTable(this->m_nodeESP32, this->m_nodeLinux);
    Log.traceln("[Manager::Manager] RegisterTable instanced");

    // Add Subscribers
    this->AddSubscribers();
    Log.traceln("[Manager::Manager] Subscribers added");

    // Connect table to Nodes
    this->m_nodeESP32->ConnectRegisterTable(this->m_tableRegister);
    Log.traceln("[Manager::Manager] Table connected to node ESP32");
    this->m_nodeLinux->ConnectRegisterTable(this->m_tableRegister);
    Log.traceln("[Manager::Manager] Table connected to node Linux");

    // Start Node 
    this->m_nodeESP32->Start();
    Log.traceln("[Manager::Manager] NodeEsp32 started");
    this->m_nodeLinux->Start();
    Log.traceln("[Manager::Manager] NodeLinux started");

    Log.traceln("[Manager::Manager] Manager initialization finished");
}


//=====================================================================================================

Manager::~Manager(){}


/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/



/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

RC_e Manager::AddSubscribers(){

    // LINUX
    
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::STATUS_NODE_LINUX_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::STATUS_NODE_ESP32_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::MODE_MANAGER_SYNC_DATA_RW, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::MODE_LINUX_SYNC_DATA_RW, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::MODE_NODE1_MODE_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTOR_LEFT_OFFSET_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTOR_RIGHT_OFFSET_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTOR_LEFT_DIRECTION_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTOR_RIGHT_DIRECTION_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_IMU_INVERT_PITCH_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_IMU_INVERT_ROLL_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_IMU_INVERT_YAW_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_IMU_OFFSET_PITCH_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_ENCODER_LEFT_DIRECTION_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_ENCODER_RIGHT_DIRECTION_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_ODOMETRY_WHEEL_RADIO_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_ODOMETRY_DISTANCE_WHEELS_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_KP_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_KI_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_KD_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_CYCLE_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_DIRECTION_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_MV_MIN_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_MV_MAX_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_KP_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_KI_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_KD_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_CYCLE_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_DIRECTION_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_MV_MIN_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_MV_MAX_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_KP_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_KI_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_KD_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_CYCLE_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_DIRECTION_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_MV_MIN_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_MV_MAX_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_MOTOR_LEFT_SPEED_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_MOTOR_RIGHT_SPEED_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_IMU_PITCH_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_IMU_ROLL_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_IMU_YAW_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_ENCODER_LEFT_COUNT_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_ENCODER_RIGHT_COUNT_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_X_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_Y_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_ANGLE_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_DISTANCE_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_MOTION_SP_POSITION_R, DEVICE_e::LINUX);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_MOTION_SP_ANGLE_R, DEVICE_e::LINUX);
    


    // ESP32_NODE01
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::MODE_NODE1_RESTART_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::MODE_NODE1_PROGRAM_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::MODE_NODE1_SYNC_DATA_RW, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::MODE_NODE1_START_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::MODE_NODE1_STOP_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTOR_LEFT_OFFSET_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTOR_LEFT_DIRECTION_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTOR_RIGHT_OFFSET_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTOR_RIGHT_DIRECTION_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_IMU_INVERT_PITCH_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_IMU_INVERT_ROLL_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_IMU_INVERT_YAW_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_IMU_OFFSET_PITCH_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_ENCODER_LEFT_DIRECTION_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_ENCODER_RIGHT_DIRECTION_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_ODOMETRY_WHEEL_RADIO_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_ODOMETRY_DISTANCE_WHEELS_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_KP_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_KI_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_KD_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_DIRECTION_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_MV_MIN_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_MV_MAX_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_KP_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_KI_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_KD_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_DIRECTION_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_MV_MIN_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_MV_MAX_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_KP_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_KI_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_KD_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_DIRECTION_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_MV_MIN_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_MV_MAX_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_MOTOR_LEFT_SPEED_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_MOTOR_RIGHT_SPEED_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_X_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_Y_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_ANGLE_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_DISTANCE_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_RESET_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_MOTION_SP_POSITION_W, DEVICE_e::ESP32_NODE01);
    this->m_tableRegister->AddSubscriber(COM_REQUEST_REG_ID_e::LIVE_MOTION_SP_ANGLE_W, DEVICE_e::ESP32_NODE01);

    return RC_e::SUCCESS;
}
