/**
 * @file Manager.cpp
 * @author Luis Arellano - luis.arellano09@gmail.com
 * @brief Class to Manage the ESP32
 * @version 1.0
 * @date 16.10.2022
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

    // Wifi
    this->m_wifiManager = new WifiManager();
    Log.traceln("[Manager::Manager] WifiManager instanced");

    // Node - Communication Bus
    this->m_nodeESP32 = new NodeEsp32(&Serial1, NODE_ESP32s_BAUDRATE, NODE_ESP32s_RX, NODE_ESP32s_TX);
    Log.traceln("[Manager::Manager] NodeEsp32 instanced");

    // Motors
    this->m_motorLeft = new Motor(PWMChannel_e::PWM1, MOTOR_LEFT_PWM_GPIO, MOTOR_PWM_FREQUENCY, MOTOR_PWM_RESOLUTION, 3.0, MOTOR_LEFT_DIR_GPIO);
    this->m_motorRight = new Motor(PWMChannel_e::PWM2, MOTOR_RIGHT_PWM_GPIO, MOTOR_PWM_FREQUENCY, MOTOR_PWM_RESOLUTION, 3.0, MOTOR_RIGHT_DIR_GPIO, MotorDirection_e::INVERTED);
    Log.traceln("[Manager::Manager] Motors instanced");

    // IMU
    this->m_IMU = new IMU(IMU_CS_GPIO, IMU_WAK_GPIO, IMU_INT_GPIO, IMU_RST_GPIO, IMU_SPI_PORT_SPEED, IMU_CLK_GPIO, IMU_MISO_GPIO, IMU_MOSI_GPIO, IMU_PS0_GPIO, IMU_PS1_GPIO);
    Log.traceln("[Manager::Manager] IMU instanced");

    // Encoders
    this->m_encoderLeft = new Encoder(1, ENCODER_LEFT_CHANNEL_A_GPIO, ENCODER_LEFT_CHANNEL_B_GPIO);
    this->m_encoderRight = new Encoder(2, ENCODER_RIGHT_CHANNEL_A_GPIO, ENCODER_RIGHT_CHANNEL_B_GPIO);
    Log.traceln("[Manager::Manager] Encoders instanced");

    //Odometry
    this->m_odometry = new Odometry(this->m_encoderLeft, this->m_encoderRight, 0.035, 0.231, 960);
    Log.traceln("[Manager::Manager] Odometry instanced");

    // Motion
    this->m_motionControl = new MotionControl(this->m_IMU, this->m_motorLeft, this->m_motorRight);
    Log.traceln("[Manager::Manager] Motion Control instanced");

    // Start Node 
    this->m_nodeESP32->Start();
    Log.traceln("[Manager::Manager] NodeEsp32 started");
    
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

