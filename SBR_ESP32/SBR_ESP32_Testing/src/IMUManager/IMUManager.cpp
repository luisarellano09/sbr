/**
 * @file IMUManager.cpp
 * @author Jorge SALGADO (jorgesalgado23@gmail.com)
 * @brief Class to Manage the IMU, communication with HSPI
 * @version 1.0
 * @date 11-11-2020
 * 
 * 
 */

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include "IMUManager.h"

/*******************************************************************************************************************************************
 *  												Constructor
 *******************************************************************************************************************************************/

//=====================================================================================================
IMUManager::IMUManager(){
 
    _spiPort = new SPIClass(HSPI);
    BeginSPI(15, 4, 2, 26,27,*_spiPort);
}

//=====================================================================================================
IMUManager::~IMUManager(){}

/*******************************************************************************************************************************************
 *  												Public Methods
 *******************************************************************************************************************************************/

//=====================================================================================================
void IMUManager::BeginSPI(uint8_t user_CSPin, uint8_t user_WAKPin, uint8_t user_INTPin, uint8_t user_RSTPin, uint32_t spiPortSpeed, SPIClass &spiPort){
	//Get user settings
	_spiPort = &spiPort;
	_spiPortSpeed = spiPortSpeed;
	if (_spiPortSpeed > 3000000)
		_spiPortSpeed = 3000000; //BNO080 max is 3MHz

	_cs = user_CSPin;
	_wake = user_WAKPin;
	_int = user_INTPin;
	_rst = user_RSTPin;

	pinMode(_cs, OUTPUT);
	pinMode(_wake, OUTPUT);
	pinMode(_int, INPUT_PULLUP);
	pinMode(_rst, OUTPUT);

    digitalWrite(_cs, HIGH); //Deselect BNO080
    //Configure the BNO080 for SPI communication
	digitalWrite(_wake, HIGH); //Before boot up the PS0/WAK pin must be high to enter SPI mode
	digitalWrite(_rst, LOW);   //Reset BNO080
	delay(2);				   //Min length not specified in datasheet?
	digitalWrite(_rst, HIGH);  //Bring out of reset

	//Wait for first assertion of INT before using WAK pin. Can take ~104ms
	waitForSPI();

	//if(wakeBNO080() == false) //Bring IC out of sleep after reset
	//  Serial.println("BNO080 did not wake up");

	_spiPort->begin(); //Turn on SPI hardware

	//At system startup, the hub must send its full advertisement message (see 5.2 and 5.3) to the
	//host. It must not send any other data until this step is complete.
	//When BNO080 first boots it broadcasts big startup packet
	//Read it and dump it
	waitForSPI(); //Wait for assertion of INT before reading advert message.
	receivePacket();

	//The BNO080 will then transmit an unsolicited Initialize Response (see 6.4.5.2)
	//Read it and dump it
	waitForSPI(); //Wait for assertion of INT before reading Init response
	receivePacket();

	//Check communication with device
	shtpData[0] = SHTP_REPORT_PRODUCT_ID_REQUEST; //Request the product ID and reset info
	shtpData[1] = 0;							  //Reserved

	//Transmit packet on channel 2, 2 bytes
	sendPacket(CHANNEL_CONTROL, 2);
}

//Blocking wait for BNO080 to assert (pull low) the INT pin
//indicating it's ready for comm. Can take more than 104ms
//after a hardware reset
boolean IMUManager::waitForSPI()
{
	for (uint8_t counter = 0; counter < 125; counter++) //Don't got more than 255
	{
		if (digitalRead(_int) == LOW)
			return (true);
		delay(1);
	}
	return (false);
}

//Check to see if there is any new data available
//Read the contents of the incoming packet into the shtpData array
boolean IMUManager::receivePacket(void)
{

    if (digitalRead(_int) == HIGH)
        return (false); //Data is not available

    //Old way: if (waitForSPI() == false) return (false); //Something went wrong

    //Get first four bytes to find out how much data we need to read

    _spiPort->beginTransaction(SPISettings(_spiPortSpeed, MSBFIRST, SPI_MODE3));
    digitalWrite(_cs, LOW);

    //Get the first four bytes, aka the packet header
    uint8_t packetLSB = _spiPort->transfer(0);
    uint8_t packetMSB = _spiPort->transfer(0);
    uint8_t channelNumber = _spiPort->transfer(0);
    uint8_t sequenceNumber = _spiPort->transfer(0); //Not sure if we need to store this or not

    //Store the header info
    shtpHeader[0] = packetLSB;
    shtpHeader[1] = packetMSB;
    shtpHeader[2] = channelNumber;
    shtpHeader[3] = sequenceNumber;

    //Calculate the number of data bytes in this packet
    uint16_t dataLength = ((uint16_t)packetMSB << 8 | packetLSB);
    dataLength &= ~(1 << 15); //Clear the MSbit.
    //This bit indicates if this package is a continuation of the last. Ignore it for now.
    //TODO catch this as an error and exit
    if (dataLength == 0)
    {
        //Packet is empty
        return (false); //All done
    }
    dataLength -= 4; //Remove the header bytes from the data count

    //Read incoming data into the shtpData array
    for (uint16_t dataSpot = 0; dataSpot < dataLength; dataSpot++)
    {
        uint8_t incoming = _spiPort->transfer(0xFF);
        if (dataSpot < MAX_PACKET_SIZE)	//BNO080 can respond with upto 270 bytes, avoid overflow
            shtpData[dataSpot] = incoming; //Store data into the shtpData array
    }

    digitalWrite(_cs, HIGH); //Release BNO080

    _spiPort->endTransaction();


	return (true); //We're done!
}

//Given the data packet, send the header then the data
//Returns false if sensor does not ACK
//TODO - Arduino has a max 32 byte send. Break sending into multi packets if needed.
boolean IMUManager::sendPacket(uint8_t channelNumber, uint8_t dataLength)
{
	uint8_t packetLength = dataLength + 4; //Add four bytes for the header

    //Wait for BNO080 to indicate it is available for communication
    if (waitForSPI() == false)
        return (false); //Something went wrong

    //BNO080 has max CLK of 3MHz, MSB first,
    //The BNO080 uses CPOL = 1 and CPHA = 1. This is mode3
    _spiPort->beginTransaction(SPISettings(_spiPortSpeed, MSBFIRST, SPI_MODE3));
    digitalWrite(_cs, LOW);

    //Send the 4 byte packet header
    _spiPort->transfer(packetLength & 0xFF);			 //Packet length LSB
    _spiPort->transfer(packetLength >> 8);				 //Packet length MSB
    _spiPort->transfer(channelNumber);					 //Channel number
    _spiPort->transfer(sequenceNumber[channelNumber]++); //Send the sequence number, increments with each packet sent, different counter for each channel

    //Send the user's data packet
    for (uint8_t i = 0; i < dataLength; i++)
    {
        _spiPort->transfer(shtpData[i]);
    }

    digitalWrite(_cs, HIGH);
    _spiPort->endTransaction();

	return (true);
}

/*******************************************************************************************************************************************
 *  												Private Methods
 *******************************************************************************************************************************************/





