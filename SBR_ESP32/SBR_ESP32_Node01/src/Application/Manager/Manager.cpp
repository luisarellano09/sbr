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
    this->m_motorLeft = new Motor(PWMChannel_e::PWM1, MOTOR_LEFT_PWM_GPIO, MOTOR_PWM_FREQUENCY, MOTOR_PWM_RESOLUTION, 0, MOTOR_LEFT_DIR_GPIO);
    this->m_motorRight = new Motor(PWMChannel_e::PWM2, MOTOR_RIGHT_PWM_GPIO, MOTOR_PWM_FREQUENCY, MOTOR_PWM_RESOLUTION, 0, MOTOR_RIGHT_DIR_GPIO, MotorDirection_e::INVERTED);

    // Start Node 
    this->m_nodeESP32->Start();
    
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

