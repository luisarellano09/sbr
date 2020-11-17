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
#include <SPI.h>

//Registers
const byte CHANNEL_COMMAND = 0;
const byte CHANNEL_EXECUTABLE = 1;
const byte CHANNEL_CONTROL = 2;
const byte CHANNEL_REPORTS = 3;
const byte CHANNEL_WAKE_REPORTS = 4;
const byte CHANNEL_GYRO = 5;

//All the ways we can configure or talk to the BNO080, figure 34, page 36 reference manual
//These are used for low level communication with the sensor, on channel 2
#define SHTP_REPORT_COMMAND_RESPONSE 0xF1
#define SHTP_REPORT_COMMAND_REQUEST 0xF2
#define SHTP_REPORT_FRS_READ_RESPONSE 0xF3
#define SHTP_REPORT_FRS_READ_REQUEST 0xF4
#define SHTP_REPORT_PRODUCT_ID_RESPONSE 0xF8
#define SHTP_REPORT_PRODUCT_ID_REQUEST 0xF9
#define SHTP_REPORT_BASE_TIMESTAMP 0xFB
#define SHTP_REPORT_SET_FEATURE_COMMAND 0xFD

//All the different sensors and features we can get reports from
//These are used when enabling a given sensor
#define SENSOR_REPORTID_ACCELEROMETER 0x01
#define SENSOR_REPORTID_GYROSCOPE 0x02
#define SENSOR_REPORTID_MAGNETIC_FIELD 0x03
#define SENSOR_REPORTID_LINEAR_ACCELERATION 0x04
#define SENSOR_REPORTID_ROTATION_VECTOR 0x05
#define SENSOR_REPORTID_GRAVITY 0x06
#define SENSOR_REPORTID_GAME_ROTATION_VECTOR 0x08
#define SENSOR_REPORTID_GEOMAGNETIC_ROTATION_VECTOR 0x09
#define SENSOR_REPORTID_GYRO_INTEGRATED_ROTATION_VECTOR 0x2A
#define SENSOR_REPORTID_TAP_DETECTOR 0x10
#define SENSOR_REPORTID_STEP_COUNTER 0x11
#define SENSOR_REPORTID_STABILITY_CLASSIFIER 0x13
#define SENSOR_REPORTID_RAW_ACCELEROMETER 0x14
#define SENSOR_REPORTID_RAW_GYROSCOPE 0x15
#define SENSOR_REPORTID_RAW_MAGNETOMETER 0x16
#define SENSOR_REPORTID_PERSONAL_ACTIVITY_CLASSIFIER 0x1E
#define SENSOR_REPORTID_AR_VR_STABILIZED_ROTATION_VECTOR 0x28
#define SENSOR_REPORTID_AR_VR_STABILIZED_GAME_ROTATION_VECTOR 0x29

//Record IDs from figure 29, page 29 reference manual
//These are used to read the metadata for each sensor type
#define FRS_RECORDID_ACCELEROMETER 0xE302
#define FRS_RECORDID_GYROSCOPE_CALIBRATED 0xE306
#define FRS_RECORDID_MAGNETIC_FIELD_CALIBRATED 0xE309
#define FRS_RECORDID_ROTATION_VECTOR 0xE30B

//Command IDs from section 6.4, page 42
//These are used to calibrate, initialize, set orientation, tare etc the sensor
#define COMMAND_ERRORS 1
#define COMMAND_COUNTER 2
#define COMMAND_TARE 3
#define COMMAND_INITIALIZE 4
#define COMMAND_DCD 6
#define COMMAND_ME_CALIBRATE 7
#define COMMAND_DCD_PERIOD_SAVE 9
#define COMMAND_OSCILLATOR 10
#define COMMAND_CLEAR_DCD 11

#define CALIBRATE_ACCEL 0
#define CALIBRATE_GYRO 1
#define CALIBRATE_MAG 2
#define CALIBRATE_PLANAR_ACCEL 3
#define CALIBRATE_ACCEL_GYRO_MAG 4
#define CALIBRATE_STOP 5

#define MAX_PACKET_SIZE 128 //Packets can be up to 32k but we don't have that much RAM.
#define MAX_METADATA_SIZE 9 //This is in words. There can be many but we mostly only care about the first 9 (Qs, range, etc)
/*******************************************************************************************************************************************
 *  												IMUManager Class
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the IMU in this case BNO080
 * 
 */
class IMUManager{

public:  
    SPIClass *_spiPort = NULL;              /**< Instance for SPI */

    //Global Variables
	uint8_t shtpHeader[4]; //Each packet has a header of 4 bytes
	uint8_t shtpData[MAX_PACKET_SIZE];
	uint8_t sequenceNumber[6] = {0, 0, 0, 0, 0, 0}; //There are 6 com channels. Each channel has its own seqnum
	uint8_t commandSequenceNumber = 0;				//Commands have a seqNum as well. These are inside command packet, the header uses its own seqNum per channel
	uint32_t metaData[MAX_METADATA_SIZE];			//There is more than 10 words in a metadata record but we'll stop at Q point 3
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
    void BeginSPI(uint8_t user_CSPin, uint8_t user_WAKPin, uint8_t user_INTPin, uint8_t user_RSTPin, uint32_t spiPortSpeed, SPIClass &spiPort);

    boolean waitForSPI();
    void setFeatureCommand(uint8_t reportID, uint16_t timeBetweenReports);
    void setFeatureCommand(uint8_t reportID, uint16_t timeBetweenReports, uint32_t specificConfig);
    void enableRotationVector(uint16_t timeBetweenReports);
    void enableAccelerometer(uint16_t timeBetweenReports);
    boolean receivePacket(void);

    boolean sendPacket(uint8_t channelNumber, uint8_t dataLength);

    bool dataAvailable(void);

    void parseInputReport(void);

    float qToFloat(int16_t fixedPointValue, uint8_t qPoint); //Given a Q value, converts fixed point floating to regular floating point number
    uint32_t floatToQ(float floatValue, uint8_t qPoint);// oposite of above
    
    float getQuatI();
	float getQuatJ();
	float getQuatK();
	float getQuatReal();
	float getQuatRadianAccuracy();
	uint8_t getQuatAccuracy();

	float getAccelX();
	float getAccelY();
	float getAccelZ();
	uint8_t getAccelAccuracy();

	float getLinAccelX();
	float getLinAccelY();
	float getLinAccelZ();
	uint8_t getLinAccelAccuracy();

	float getGyroX();
	float getGyroY();
	float getGyroZ();
	uint8_t getGyroAccuracy();

	float getFastGyroX();
	float getFastGyroY();
	float getFastGyroZ();

	float getMagX();
	float getMagY();
	float getMagZ();
	uint8_t getMagAccuracy();

private:

    unsigned long _spiPortSpeed; //Optional user defined port speed
	uint8_t _cs;				 //Pins needed for SPI
	uint8_t _wake;
	uint8_t _int;
	uint8_t _rst;
    //These are the raw sensor values (without Q applied) pulled from the user requested Input Report
	uint16_t rawAccelX, rawAccelY, rawAccelZ, accelAccuracy;
	uint16_t rawLinAccelX, rawLinAccelY, rawLinAccelZ, accelLinAccuracy;
	uint16_t rawGyroX, rawGyroY, rawGyroZ, gyroAccuracy;
	uint16_t rawMagX, rawMagY, rawMagZ, magAccuracy;
	uint16_t rawQuatI, rawQuatJ, rawQuatK, rawQuatReal, rawQuatRadianAccuracy, quatAccuracy;
	uint16_t rawFastGyroX, rawFastGyroY, rawFastGyroZ;
	uint16_t stepCount;
	uint32_t timeStamp;
	uint8_t stabilityClassifier;
	uint8_t activityClassifier;
	uint8_t *_activityConfidences;						  //Array that store the confidences of the 9 possible activities
	uint8_t calibrationStatus;							  //Byte R0 of ME Calibration Response
	bool calibrationSaveConfirmed;   // Have we received confirmation that calibration was saved?
	uint16_t memsRawAccelX, memsRawAccelY, memsRawAccelZ; //Raw readings from MEMS sensor
	uint16_t memsRawGyroX, memsRawGyroY, memsRawGyroZ;	//Raw readings from MEMS sensor
	uint16_t memsRawMagX, memsRawMagY, memsRawMagZ;		  //Raw readings from MEMS sensor
    uint8_t memsRawMagStatus;

	//These Q values are defined in the datasheet but can also be obtained by querying the meta data records
	//See the read metadata example for more info
	int16_t rotationVector_Q1 = 14;
	int16_t rotationVectorAccuracy_Q1 = 12; //Heading accuracy estimate in radians. The Q point is 12.
	int16_t accelerometer_Q1 = 8;
	int16_t linear_accelerometer_Q1 = 8;
	int16_t gyro_Q1 = 9;
	int16_t magnetometer_Q1 = 4;
	int16_t angular_velocity_Q1 = 10;
};

#endif // IMUMANAGER_H