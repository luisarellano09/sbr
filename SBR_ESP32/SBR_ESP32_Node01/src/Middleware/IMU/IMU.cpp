/**
 * @file IMU.cpp
 * @author Luis Arellano - luis.arellano09@gmail.com
 * @brief IMU Class
 * @version 1.0
 * @date 15.03.2023
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "IMU.h"
#include "../../Definition/Local/LocalConfig.h"
#include <ArduinoLog.h>


/*******************************************************************************************************************************************
 *  												DEFINE
 *******************************************************************************************************************************************/

#define FACTOR_CONV_RAD_TO_DEG	(double)57.295779513


/*******************************************************************************************************************************************
 *  												CONSTRUCTOR
 *******************************************************************************************************************************************/

IMU::IMU(uint8_t user_CSPin, uint8_t user_WAKPin, uint8_t user_INTPin, uint8_t user_RSTPin, uint32_t spiPortSpeed, uint8_t CLK_IMU, uint8_t MISO_IMU, uint8_t MOSI_IMU, uint8_t PS0_IMU, uint8_t PS1_IMU){

    // Create instance
    this->m_BNO080 = new BNO080();

    // Set PS0
    pinMode(PS0_IMU, OUTPUT);   
    digitalWrite(PS0_IMU, HIGH); //PS0 to HIGH

    // Set PS1
    pinMode(PS1_IMU, OUTPUT);   
    digitalWrite(PS1_IMU, HIGH); //PS1 to HIGH

    // Begin SPI
    this->m_BNO080->beginSPI(user_CSPin, user_WAKPin, user_INTPin, user_RSTPin, spiPortSpeed, CLK_IMU, MISO_IMU, MOSI_IMU);
}


//=====================================================================================================

IMU::~IMU(){}


/*******************************************************************************************************************************************
 *  												PUBLIC METHODS
 *******************************************************************************************************************************************/

RC_e IMU::SetCycleRotationVector(uint16_t cycleRotationVector){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    this->m_BNO080->enableRotationVector(cycleRotationVector);

    Log.traceln("[IMU::SetCycleRotationVector] Cycle of rotation vector setted to: %d", cycleRotationVector);

    return retCode;
}


//=====================================================================================================

RC_e IMU::Run(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    if( this->m_BNO080->dataAvailable() ){
        this->Calculate();
    }

    return retCode;
}


/*******************************************************************************************************************************************
 *  												PRIVATE METHODS
 *******************************************************************************************************************************************/

RC_e IMU::Calculate(){
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Roll
    this->m_Roll = FACTOR_CONV_RAD_TO_DEG * this->m_BNO080->getRoll();
    double tempRoll = FACTOR_CONV_RAD_TO_DEG * this->m_BNO080->getRoll();

    if(tempRoll > 0.0){
        this->m_Roll = 180- tempRoll;
    } else{
        this->m_Roll = -180 - tempRoll;
    }

    // Pitch
    this->m_Pitch = FACTOR_CONV_RAD_TO_DEG * this->m_BNO080->getPitch();

    // Yaw
    if (this->m_initialYaw == -999999999999.9) {
        this->m_initialYaw = FACTOR_CONV_RAD_TO_DEG * this->m_BNO080->getYaw();
    }
    double tempYaw = FACTOR_CONV_RAD_TO_DEG * this->m_BNO080->getYaw();
            
    // Compute the quadrant of yaw
    if( (tempYaw > -180.0) && (tempYaw < -90.0) ){
        this->m_quadrant = 1;
    }
    else if( (tempYaw > -90.0)&&(tempYaw< 0.0) ){
        this->m_quadrant = 2;
    }
    else if( (tempYaw > 0.0)&&(tempYaw< 90.0) ){
        this->m_quadrant = 3;
    }
    else if((tempYaw > 90.0)&&(tempYaw < 180.0)){
        this->m_quadrant = 4;
    }
    
    // Absolute Yaw
    if( (this->m_quadrantPrev == 4) && (m_quadrant == 1) ){
        this->m_numberOfTurns++;
    }
    else if( (m_quadrantPrev == 1) && (m_quadrant == 4) ){
        this->m_numberOfTurns--;	
    }

    this->m_Yaw = tempYaw - this->m_initialYaw + (double)m_numberOfTurns * 360.0; 

    m_quadrantPrev = m_quadrant;

    return retCode;
}