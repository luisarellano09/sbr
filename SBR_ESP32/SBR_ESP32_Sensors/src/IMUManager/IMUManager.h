/**
 * @file IMUManager.h
 * @author Jorge Salgado (jorgesalgado23@gmail.com)
 * @brief Class to Manage the IMU BNO080
 * @version 1.0
 * @date 11-11-2020
 * 
 * 
 */

#ifndef IMUMANAGER_H
#define IMUMANAGER_H

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include "../Definition/GlobalDef.h"
#include "../BNO080/SparkFun_BNO080_Arduino_Library.h"

/*Define ALERT LED*/
#define LED_ESP32   2

/* PINs IMU*/

#define PS0         33
#define PS1         12
#define CS_IMU      32
#define WAK_IMU     PS0
#define INT_IMU     26
#define RTS_IMU     27

/*SPI 2 Pins*/
#define CLK_IMU     14
#define MISO_IMU    25
#define MOSI_IMU    13

/*Clock Speed*/
#define SPEED_IMU   3000000 //3MHz

extern float AccX_Mesured;

/*******************************************************************************************************************************************
 *  												IMUManager Class
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the IMU in this case BNO080
 * 
 */
class IMUManager{

public:  

	
	BNO080 *myBN080;
	SPIClass *SPI2BNO080 = NULL;  
    
    
    /**
     * @brief Construct a new IMU Manager object
     * 
     * @param 
     * @param 
     * @param 
     */
    IMUManager();

    /**
     * @brief Destroy the IMU Manager object
     * 
     */
    ~IMUManager();

    /**
     * @brief Connect to IMU services
     * 
     * @return RC_e Result code
     */

    RC_e Run();
private:


};

#endif // IMUMANAGER_H