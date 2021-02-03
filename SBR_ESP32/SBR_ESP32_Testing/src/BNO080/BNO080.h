/**
 * @file BNO080.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @author Jorge Salgado (jorgesalgado23@gmail.com)
 * @brief Class to BNO080 IMU sensor
 * this is a library modified from sparkfun library  :
 * https://github.com/sparkfun/SparkFun_BNO080_Arduino_Library
 * @version 3.0
 * @date 28.01.2021
*/

#ifndef BNO080_H
#define BNO080_H
/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include "../Definition/GlobalDef.h"

//The default I2C address for the BNO080 on the SparkX breakout is 0x4B. 0x4A is also possible.
#define BNO080_DEFAULT_ADDRESS 0x4B

//Platform specific configurations

//Define the size of the I2C buffer based on the platform the user has
//The catch-all default is 32
#define I2C_BUFFER_LENGTH 32


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
 *  												CLASS
 *******************************************************************************************************************************************/
/**
 * @brief Class BNO080 IMU manager
 * 
 */
class BNO080
{
public:
     #define DIRECT_ROLL      0    /**< positive forward in Roll     */
     #define REVERSE_ROLL     1    /**< negative forward in Roll     */
     #define DIRECT_PITCH     0    /**< positive forward in Pitch    */
     #define REVERSE_PITCH    1    /**< negative forward in Pitch    */
     #define DIRECT_YAW       0    /**< positive forward in Yaw      */
     #define REVERSE_YAW      1    /**< negative forward in Yaw      */

	float m_quatI, m_QuatJ, m_QuatK, m_QuatReal;		/**< Quaternion Variable */
	float m_QuatRadianAccuracy, m_quatAccuracy;			
	float m_Roll, m_Pitch, m_Yaw; 						/**< Euler variables */
	float m_calibYaw, m_absYaw, m_absYawCalib; 			/**< Yaw Calibration variable */
     int m_direction_Roll;
     int m_direction_Pitch;
     int m_direction_Yaw;

	uint8_t shtpHeader[4]; 								/**<Each packet has a header of 4 bytes*/
	uint8_t shtpData[MAX_PACKET_SIZE];
	uint8_t sequenceNumber[6] = {0, 0, 0, 0, 0, 0}; 	/**<There are 6 com channels. Each channel has its own seqnum*/
	uint8_t commandSequenceNumber = 0;					/**<Commands have a seqNum as well. These are inside command packet, the header uses its own seqNum per channel*/
	uint32_t metaData[MAX_METADATA_SIZE];				/**<There is more than 10 words in a metadata record but we'll stop at Q point 3*/

    /**
     * @brief Constructor
     * 
     */
	BNO080();
    /**
     * @brief Destructor
     * 
     */
	~BNO080();

	/**
	 * @brief Configure the BNO080 
	 * 
	 * 
	 * @return RC_e Result code
	 */
	RC_e configure(uint8_t deviceAddress = BNO080_DEFAULT_ADDRESS, TwoWire &wirePort = Wire, uint8_t intPin = 255, uint8_t PS0_IMU = 255, uint8_t PS1_IMU = 255); //By default use the default I2C addres, and use Wire port, and don't declare an INT pin
	
	/**
	 * @brief Configure the BNO080 
	 * 
	 * @param user_CSPin Chip Select Pin
      * @param user_WAKPin Wake up Pin (same pin PS0)
      * @param user_INTPin Interrupt pin
	 * @param user_RSTPin Reset Pin
      * @param spiPortSpeed Spi Speed max 3Mbps
      * @param CLK_IMU Clock Pin 
	 * @param MISO_IMU Master Input Slave Output
      * @param MOSI_IMU Master Output Slave Input
      * @param PS0_IMU PS0 Pin select Mode IMU (optional)
	 * @param PS1_IMU PS1 Pin select Mode IMU (optional)
	 *  
	 * @return RC_e Result code
	 */
     RC_e configure(uint8_t user_CSPin, uint8_t user_WAKPin, uint8_t user_INTPin, uint8_t user_RSTPin, uint32_t spiPortSpeed, uint8_t CLK_IMU, uint8_t MISO_IMU, uint8_t MOSI_IMU, int DirectionRoll, int DirectionPitch, int DirectionYaw,uint8_t PS0_IMU = 255, uint8_t PS1_IMU = 255);
	
  	/**
     * @brief Set the YawCalib to zero position
     * 
     * @return RC_e Result code
     */
	RC_e calibrationAngles();

    /**
     * @brief Update all public variables
     * 
     * @return RC_e Result code
     */
	RC_e Run();


    /**
     * @brief Turn on debug printing. If user doesn't specify then Serial will be used.
     * 
     * @return None
     */
	void enableDebugging(Stream &debugPort = Serial);

   	/**
     * @brief try to reset the IMU via software
     * 
     * @return None
     */
	void softReset();

	/**
     * @brief Query the IMU for the reason it last reset
     * 
     * @return 1 = POR, 2 = Internal reset, 3 = Watchdog, 4 = External reset, 5 = Other
     */
	uint8_t resetReason(); 

	/**
     * @brief Given a Q value, converts fixed point floating to regular floating point number
     * 
     * @return Conversion en float
     */
	float qToFloat(int16_t fixedPointValue, uint8_t qPoint); 

	/**
     * @brief Delay based polling for I2C traffic
     * 
     * @return false if failed
     */
	boolean waitForI2C(); 

	/**
     * @brief Delay based polling for INT pin to go low
     * 
     * @return True if IMU sent Data
     */
	boolean waitForSPI();

	/**
     * @brief receive the Packet
     * 
     * @return true if everything is ok
     */
	boolean receivePacket(void);

	/**
     * @brief Given a number of bytes, send the requests in I2C_BUFFER_LENGTH chunks
     * 
     * @return true if everything is ok
     */
	boolean getData(uint16_t bytesRemaining); 

	/**
     * @brief send the packet
     * 
     * @return true if everything is ok
     */
	boolean sendPacket(uint8_t channelNumber, uint8_t dataLength);

	/**
     * @brief Prints the current shtp header and data packets
     * 
     * @return None
     */
	void printPacket(void); 

	/**
     * @brief Prints the current shtp header (only)
     * 
     * @return None
     */
	void printHeader(void);

	/**
     * @brief Enable Rotation Vector
     * 
     * @return None
     */
	void enableRotationVector(uint16_t timeBetweenReports);

	/**
     * @brief Enable Game Rotation Vector
     * 
     * @return None
     */
	void enableGameRotationVector(uint16_t timeBetweenReports);

	/**
     * @brief Enable ARVVR stabilized Rotation Vector
     * 
     * @return None
     */
	void enableARVRStabilizedRotationVector(uint16_t timeBetweenReports);

	/**
     * @brief enable ARVR stabilized Game Rotation Vector
     * 
     * @return None
     */
	void enableARVRStabilizedGameRotationVector(uint16_t timeBetweenReports);

	/**
     * @brief Enable Accelerometer
     * 
     * @return None
     */
	void enableAccelerometer(uint16_t timeBetweenReports);

	/**
     * @brief Enable Linear Accelerometer
     * 
     * @return None
     */
	void enableLinearAccelerometer(uint16_t timeBetweenReports);

	/**
     * @brief enable Gyro
     * 
     * @return None
     */
	void enableGyro(uint16_t timeBetweenReports);

	/**
     * @brief enable Magnetometer
     * 
     * @return None
     */
	void enableMagnetometer(uint16_t timeBetweenReports);

	/**
     * @brief enable Step Counter
     * 
     * @return None
     */
	void enableStepCounter(uint16_t timeBetweenReports);

	/**
     * @brief enable Stability Classifier
     * 
     * @return None
     */
	void enableStabilityClassifier(uint16_t timeBetweenReports);

	/**
     * @brief enable Activity Classifier
     * 
     * @return None
     */
	void enableActivityClassifier(uint16_t timeBetweenReports, uint32_t activitiesToEnable, uint8_t (&activityConfidences)[9]);
	
	
	/**
     * @brief enable Raw Accelerometer
     * 
     * @return None
     */
	void enableRawAccelerometer(uint16_t timeBetweenReports);

	/**
     * @brief enable Raw Gyro
     * 
     * @return None
     */
	void enableRawGyro(uint16_t timeBetweenReports);

	/**
     * @brief enable Raw Magnetometer
     * 
     * @return None
     */
	void enableRawMagnetometer(uint16_t timeBetweenReports);

	/**
     * @brief enable Gyro Integrated Rotation Vector
     * 
     * @return None
     */
	void enableGyroIntegratedRotationVector(uint16_t timeBetweenReports);

	/**
     * @brief data Available
     * 
     * @return true if everything is ok
     */
	bool dataAvailable(void);

	/**
     * @brief Parse sensor readings out of report
     * 
     * @return None
     */
	void parseInputReport(void);   

	/**
     * @brief Parse command responses out of report
     * 
     * @return None
     */
	void parseCommandReport(void); //

	/**
     * @brief get Quaternion I
     * 
     * @return value in float
     */
	float getQuatI();

	/**
     * @brief get Quaternion J
     * 
     * @return value in float
     */
	float getQuatJ();

	/**
     * @brief get Quaternion K
     * 
     * @return value in float
     */
	float getQuatK();

	/**
     * @brief get Quaternion Real
     * 
     * @return value in float
     */
	float getQuatReal();

	/**
     * @brief get quaternion Radian Accuracy
     * 
     * @return value in float
     */
	float getQuatRadianAccuracy();

	/**
     * @brief get Quaternion Accuracy
     * 
     * @return value in uint8_t
     */
	uint8_t getQuatAccuracy();

	/**
     * @brief get Accel X
     * 
     * @return value in float
     */
	float getAccelX();

	/**
     * @brief get Accel Y
     * 
     * @return value in float
     */
	float getAccelY();

	/**
     * @brief get Accel Z
     * 
     * @return value in float
     */
	float getAccelZ();

	/**
     * @brief get Accel Accuracy
     * 
     * @return value in uint8_t
     */
	uint8_t getAccelAccuracy();

	/**
     * @brief get Lin Accel X
     * 
     * @return value in float
     */
	float getLinAccelX();

	/**
     * @brief get Lin Accel Y
     * 
     * @return value in float
     */
	float getLinAccelY();

	/**
     * @brief get Lin Accel Z
     * 
     * @return value in float
     */
	float getLinAccelZ();

	/**
     * @brief get Lin Accel Accuracy
     * 
     * @return value in uint8_t
     */
	uint8_t getLinAccelAccuracy();

	/**
     * @brief get Gyro X
     * 
     * @return value in float
     */
	float getGyroX();

	/**
     * @brief get Gyro Y
     * 
     * @return value in float
     */
	float getGyroY();

	/**
     * @brief get Gyro Z
     * 
     * @return value in float
     */
	float getGyroZ();

	/**
     * @brief get Gyro Accuracy
     * 
     * @return value in uint8_t
     */
	uint8_t getGyroAccuracy();

	/**
     * @brief get fast Gyro X
     * 
     * @return value in float
     */
	float getFastGyroX();

	/**
     * @brief get Fast Gyro Y
     * 
     * @return value in float
     */
	float getFastGyroY();

	/**
     * @brief get Fast Gyro Z
     * 
     * @return value in float
     */
	float getFastGyroZ();


	/**
     * @brief get magnetometer X
     * 
     * @return value in float
     */
	float getMagX();

	/**
     * @brief get magnetometer Y
     * 
     * @return value in float
     */
	float getMagY();

	/**
     * @brief get magnetometer Z
     * 
     * @return value in float
     */
	float getMagZ();

	/**
     * @brief get magnetometer Accuracy
     * 
     * @return value in uint8_t
     */
	uint8_t getMagAccuracy();

	/**
     * @brief calibrate Accelerometer
     * 
     * @return None
     */
	void calibrateAccelerometer();

	/**
     * @brief Calibrate Gyroscope
     * 
     * @return None
     */
	void calibrateGyro();

	/**
     * @brief calibrate Magnetometer
     * 
     * @return None
     */
	void calibrateMagnetometer();

	/**
     * @brief calibrate Planar Accelerometer
     * 
     * @return None
     */
	void calibratePlanarAccelerometer();

	/**
     * @brief calibrate All
     * 
     * @return None
     */
	void calibrateAll();

	/**
     * @brief end Calibration
     * 
     * @return None
     */
	void endCalibration();

	/**
     * @brief save Calibration
     * 
     * @return None
     */
	void saveCalibration();

	/**
     * @brief Sends command to get status
     * 
     * @return None
     */
	void requestCalibrationStatus();

	/**
     * @brief Checks ME Cal response for byte 5, R0 - Status
     * 
     * @return true ifeverything is ok
     */
	boolean calibrationComplete();   

	/**
     * @brief get Time Stamp
     * 
     * @return value in uint32_t
     */
	uint32_t getTimeStamp();

	/**
     * @brief get Step Count
     * 
     * @return value in uint16_t
     */
	uint16_t getStepCount();

	/**
     * @brief get Stability Classifier
     * 
     * @return value in uint8_t
     */
	uint8_t getStabilityClassifier();

	/**
     * @brief get Activity Classifier
     * 
     * @return value in uint8_t
     */
	uint8_t getActivityClassifier();

	/**
     * @brief get Raw Accel X
     * 
     * @return value in int16_t
     */
	int16_t getRawAccelX();

	/**
     * @brief get Raw Accel Y
     * 
     * @return value in int16_t
     */
	int16_t getRawAccelY();

	/**
     * @brief get Raw Accel Z
     * 
     * @return value in int16_t
     */
	int16_t getRawAccelZ();

	/**
     * @brief get Raw Gyro X
     * 
     * @return value in int16_t
     */
	int16_t getRawGyroX();

	/**
     * @brief get Raw Gyro Y
     * 
     * @return value in int16_t
     */
	int16_t getRawGyroY();

	/**
     * @brief get Raw Gyro Z
     * 
     * @return value in int16_t
     */
	int16_t getRawGyroZ();

	/**
     * @brief get Raw Mag X
     * 
     * @return value in int16_t
     */
	int16_t getRawMagX();

	/**
     * @brief get Raw Mag Y
     * 
     * @return value in int16_t
     */
	int16_t getRawMagY();

	/**
     * @brief get Raw Mag Z
     * 
     * @return value in int16_t
     */
	int16_t getRawMagZ();

	/**
     * @brief get Roll value
     * 
     * @return value in float
     */
	float getRoll();

	/**
     * @brief Get Pitch value
     * 
     * @return value in float
     */
	float getPitch();

	/**
     * @brief get Yaw value
     * 
     * @return value in float
     */
	float getYaw();

	/**
     * @brief set Feature Command
     * 
	 * @param reportID	Id 
	 * @param timeBetweenReports period
	 * 
     * @return None
     */
	void setFeatureCommand(uint8_t reportID, uint16_t timeBetweenReports);

	/**
     * @brief set Feature Command
	 * 
	 * @param reportID	Id 
	 * @param timeBetweenReports period
	 * @param specificConfig Config
	 * 
     * @return None
     */
	void setFeatureCommand(uint8_t reportID, uint16_t timeBetweenReports, uint32_t specificConfig);

	/**
     * @brief send Command
	 *
	 * @param command command
     * 
     * @return None
     */
	void sendCommand(uint8_t command);

	/**
     * @brief send Calibrate command
	 * 
	 * @param thingToCalibrate page 50 of reference manual and the 1000-4044 calibration docor
     * 
     * @return None
     */
	void sendCalibrateCommand(uint8_t thingToCalibrate);

	//Metadata functions
	/**
     * @brief get Quaternion 1
     * 
	 * @param recordID ID 
	 * 
     * @return value in int16_t
     */
	int16_t getQ1(uint16_t recordID);

	/**
     * @brief get Quaternion 2
	 * 
	 * @param recordID ID 
     * 
     * @return value in int16_t
     */
	int16_t getQ2(uint16_t recordID);

	/**
     * @brief get Quaternion 3
	 * 
	 * @param recordID ID 
     * 
     * @return value in int16_t
     */
	int16_t getQ3(uint16_t recordID);

	/**
     * @brief get Resolution
	 * 
	 * @param recordID ID 
     * 
     * @return value in float
     */
	float getResolution(uint16_t recordID);

	/**
     * @brief get Range
	 * 
	 * @param recordID ID 
     * 
     * @return value in float
     */
	float getRange(uint16_t recordID);

	/**
     * @brief Read FRS word
	 * 
	 * @param recordID ID 
	 * @param wordNumber Number 
     * 
     * @return Value in uint32_t
     */
	uint32_t readFRSword(uint16_t recordID, uint8_t wordNumber);

	/**
     * @brief frs Read Request
	 * 
	 * @param recordID ID 
	 * @param readOffset offset 
	 * @param blockSize size 
     * 
     * @return None
     */
	void frsReadRequest(uint16_t recordID, uint16_t readOffset, uint16_t blockSize);

	/**
     * @brief read FRS data
	 * 
	 * @param recordID ID 
	 * @param startLocation location 
	 * @param wordsToRead size  
	 * 
     * @return None
     */
	bool readFRSdata(uint16_t recordID, uint8_t startLocation, uint8_t wordsToRead);



private:

    bool m_isConnected = false;				/**< IMU is coneceted*/
	int m_numberOfTurns = 0;				/**< Number of turns */
	uint8_t m_quadrant, m_quadrantPrev;		/**< quadrant value and previous*/
	float offsetYaw = 0;					/**< Offset of the Yaw value*/

	TwoWire *_i2cPort;		/**<The generic connection to user's chosen I2C hardware*/
	uint8_t _deviceAddress; /**<Keeps track of I2C address. setI2CAddress changes this.*/

	Stream *_debugPort;			 /**<The stream to send debug messages to if enabled. Usually Serial.*/
	boolean _printDebug = false; /**<Flag to print debugging variables*/

	SPIClass* _spiPort;			 /**<The generic connection to user's chosen SPI hardware*/
	unsigned long _spiPortSpeed; /**<Optional user defined port speed*/
	uint8_t _cs;				 /**<Pins needed for SPI*/
	uint8_t _wake;
	uint8_t _int;
	uint8_t _rst;

	
	uint16_t rawAccelX, rawAccelY, rawAccelZ, accelAccuracy; /**<These are the raw sensor values (without Q applied) pulled from the user requested Input Report*/
	uint16_t rawLinAccelX, rawLinAccelY, rawLinAccelZ, accelLinAccuracy;
	uint16_t rawGyroX, rawGyroY, rawGyroZ, gyroAccuracy;
	uint16_t rawMagX, rawMagY, rawMagZ, magAccuracy;
	uint16_t rawQuatI, rawQuatJ, rawQuatK, rawQuatReal, rawQuatRadianAccuracy, quatAccuracy;
	uint16_t rawFastGyroX, rawFastGyroY, rawFastGyroZ;
	uint16_t stepCount;
	uint32_t timeStamp;
	uint8_t stabilityClassifier;
	uint8_t activityClassifier;
	uint8_t *_activityConfidences;						  /**<Array that store the confidences of the 9 possible activities*/
	uint8_t calibrationStatus;							  /**<Byte R0 of ME Calibration Response*/
	uint16_t memsRawAccelX, memsRawAccelY, memsRawAccelZ; /**<Raw readings from MEMS sensor*/
	uint16_t memsRawGyroX, memsRawGyroY, memsRawGyroZ;	/**<Raw readings from MEMS sensor*/
	uint16_t memsRawMagX, memsRawMagY, memsRawMagZ;		  /**<aw readings from MEMS sensor*/

	/**<These Q values are defined in the datasheet but can also be obtained by querying the meta data records*/
	/**<See the read metadata example for more info*/
	int16_t rotationVector_Q1 = 14;
	int16_t rotationVectorAccuracy_Q1 = 12; /**<Heading accuracy estimate in radians. The Q point is 12.*/
	int16_t accelerometer_Q1 = 8;
	int16_t linear_accelerometer_Q1 = 8;
	int16_t gyro_Q1 = 9;
	int16_t magnetometer_Q1 = 4;
	int16_t angular_velocity_Q1 = 10;

	/**
     * @brief Configure for I2C
     * 
     * @return None
     */
    boolean begin(uint8_t deviceAddress = BNO080_DEFAULT_ADDRESS, TwoWire &wirePort = Wire, uint8_t intPin = 255); //By default use the default I2C addres, and use Wire port, and don't declare an INT pin
	
	/**
     * @brief Configure for SPI
	 * 
	 * @param user_CSPin Chip Select
	 * @param user_WAKPin Wake up Pin (PS0)
	 * @param user_INTPin Interrupt Pin
	 * @param user_RSTPin Reset Pin
	 * @param spiPortSpeed Speed (max 3M)
	 * @param CLK_IMU Clock
	 * @param MISO_IMU MISO
	 * @param MOSI_IMU MOSI
     * 
     * @return None
     */
	boolean beginSPI(uint8_t user_CSPin, uint8_t user_WAKPin, uint8_t user_INTPin, uint8_t user_RSTPin, uint32_t spiPortSpeed, uint8_t CLK_IMU, uint8_t MISO_IMU, uint8_t MOSI_IMU);

};

#endif // BNO080_H


