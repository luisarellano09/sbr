/**
 * @file IMUManager.cpp
 * @author Jorge SALGADO (jorgesalgado23@gmail.com)
 * @brief Class to Manage the IMU, communication with HSPI 
 * This library handles the initialization of the BNO080.
 * https://github.com/sparkfun/SparkFun_BNO080_Arduino_Library the original library.
 * this file is modified to our project.
 * @version 1.0
 * @date 11-11-2020
 * 
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include "IMUManager.h"
#include "SPI.h"

float AccX_Mesured =0.0;
/*******************************************************************************************************************************************
 *  												Constructor
 *******************************************************************************************************************************************/

//=====================================================================================================
IMUManager::IMUManager(){


    /*DIOD PS0 PS1 IMU*/
	pinMode(PS0, OUTPUT);   
    digitalWrite(PS0, HIGH); //PS0 to HIGH
    pinMode(PS1, OUTPUT);   
    digitalWrite(PS1, HIGH); //PS1 to HIGH
	
	SPI2BNO080 = new SPIClass();
    SPI2BNO080->begin(CLK_IMU,MISO_IMU,MOSI_IMU,CS_IMU);

    myBN080 = new BNO080();
	
	if(myBN080->beginSPI(CS_IMU, WAK_IMU, INT_IMU, RTS_IMU,SPEED_IMU,*SPI2BNO080) == false)
    {
		/*In case IMU absent or Problem, ALERT LED*/
		pinMode(LED_ESP32, OUTPUT);
		
		while(1){
			digitalWrite(LED_ESP32, HIGH); //Deselect BNO080
			delay(50);
			digitalWrite(LED_ESP32, LOW); //Deselect BNO080
			delay(50);
		}
    }
	
	//myBN080->enableRotationVector(50);//Send data update every 50ms
	myBN080->enableAccelerometer(10);

}

//=====================================================================================================
IMUManager::~IMUManager(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/
RC_e IMUManager::Run(){
	RC_e retCode = RC_e::ERROR;
	if(myBN080->dataAvailable() == true){
		AccX_Mesured = myBN080->getAccelX();
        float AccY = myBN080->getAccelY();
        float AccZ = myBN080->getAccelZ();
		Serial.print(AccX_Mesured, 2);
		Serial.print(F(","));
		Serial.print(AccX_Mesured, 2);
		Serial.print(F(","));
		Serial.print(AccX_Mesured, 2);
		Serial.print("\n");
		
		retCode = RC_e::SUCCESS;
	}
	return retCode;
}


//=====================================================================================================

/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/





