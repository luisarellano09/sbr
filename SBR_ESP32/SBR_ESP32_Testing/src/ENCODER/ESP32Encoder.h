/**
 * @file ESP32Encoder.h
 * @author Jorge Salgado (jorgesalgado23@gmail.com)
 * @brief Class to manage the Encoder 
 * the original library is from Arduino, only modified for this project.
 * @version 2.0
 * @date 09.01.2021
 * 
 * 
 */
#ifndef ESP32ENCODER_H
#define ESP32ENCODER_H


/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include <driver/gpio.h>
#include "driver/pcnt.h"

#define MAX_ESP32_ENCODERS PCNT_UNIT_MAX
#define 	_INT16_MAX 32766
#define  	_INT16_MIN -32766

enum encType {
	single,
	half,
	full
};
enum puType {
	UP,
	DOWN,
	NONE
};


/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the Encoder into ESP32
 * 
 */
class ESP32Encoder {
	public:

	static ESP32Encoder *encoders[MAX_ESP32_ENCODERS];	/**< Max Object created of the Class */
	gpio_num_t aPinNumber;			/**< Channel A */
	gpio_num_t bPinNumber;			/**< Channel B */
	pcnt_unit_t unit;				/**< unit */
	bool fullQuad=false;			/**< is it full Quad */
	int countsMode = 2;				/**< Count Mode */
	volatile int64_t count=0;		/**< Count from Interrupt */
	pcnt_config_t r_enc_config;		/**< Encoder Config */
	static enum puType useInternalWeakPullResistors;	/**< Internal Weak Pull value */

    /**
     * @brief Constructor
     * 
     */
	ESP32Encoder();

    /**
     * @brief Destructor
     * 
     */
	~ESP32Encoder();

   	/**
     * @brief attachHalfQuad
	 * 
	 * @param aPintNumber Chanel A
	 * @param bPinNumber Chanel B
     * 
     * @return None
     */	
	void attachHalfQuad(int aPintNumber, int bPinNumber);

	/**
     * @brief attachFullQuad
	 * 
	 * @param aPintNumber Chanel A
	 * @param bPinNumber Chanel B
     * 
     * @return None
     */	
	void attachFullQuad(int aPintNumber, int bPinNumber);

	/**
     * @brief attachSingleEdge
	 * 
	 * @param aPintNumber Chanel A
	 * @param bPinNumber Chanel B
     * 
     * @return None
     */	
	void attachSingleEdge(int aPintNumber, int bPinNumber);

	/**
     * @brief get Count
     * 
     * @return value in int64_t
     */		
	int64_t getCount();

	/**
     * @brief clear Count
     * 
     * @return value int64_t
     */	
	int64_t clearCount();

	/**
     * @brief pause Count
     * 
     * @return value int64_t
     */	
	int64_t pauseCount();

	/**
     * @brief resume Count
     * 
     * @return value int64_t
     */	
	int64_t resumeCount();
	/**
     * @brief is Attached
     * 
     * @return true if it attached.
     */	
	boolean isAttached(){return attached;}

	/**
     * @brief Set count
     * 
	 * @param value value to set
	 * 
     * @return None
     */	
	void setCount(int64_t value);

private:

	boolean attached=false;						/**< is is attached*/
	static  pcnt_isr_handle_t user_isr_handle; 	/**<user's ISR service handle*/
    bool direction;								/**< direction */
    bool working;								/**< is it Working */
	static bool attachedInterrupt;				/**< is it attached Interrupt */

	/**
     * @brief attach the pins
     * 
	 * @param aPintNumber Chanel A
	 * @param bPinNumber Chanel B
	 * @param et Encoder type
	 * 
     * @return None
     */	
	void attach(int aPintNumber, int bPinNumber, enum encType et);

	/**
     * @brief Get Count Raw
     * 
     * @return value in int64_t
     */
	int64_t getCountRaw();


};

#endif // ESP32ENCODER_H

