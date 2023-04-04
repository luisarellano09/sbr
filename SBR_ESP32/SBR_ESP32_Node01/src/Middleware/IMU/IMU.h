/**
 * @file IMU.h
 * @author Luis Arellano - luis.arellano09@gmail.com
 * @brief IMU Class
 * @version 1.0
 * @date 15.03.2023
 * 
 */

#ifndef IMU_H
#define IMU_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "../../Definition/Global/RC.h"
#include "../../Middleware/IMU/BNO080.h"


/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief IMU Class
 * 
 */
class IMU {
public:  

    double m_Roll = 0.0;        /**@brief IMU Roll: Front inclination. */
    double m_Pitch = 0.0;       /**@brief IMU Pitch: Lateral inclination. */
    double m_Yaw = 0.0;         /**@brief IMU Yaw: Rotation. */
    bool m_invertRoll = false;  /**@brief Invert Roll, 0=normal 1=invert */
    bool m_invertPitch = false; /**@brief Invert Pitch, 0=normal 1=invert */
    bool m_invertYaw = false;   /**@brief Invert Yaw, 0=normal 1=invert */

    double m_initialYaw = -999999999999.9;
    int m_numberOfTurns = 0;
    uint8_t m_quadrant;
    uint8_t m_quadrantPrev;	

    /**
     * @brief Construct a new object
     * 
     */
    IMU(uint8_t user_CSPin, uint8_t user_WAKPin, uint8_t user_INTPin, uint8_t user_RSTPin, uint32_t spiPortSpeed, uint8_t CLK_IMU, uint8_t MISO_IMU, uint8_t MOSI_IMU, uint8_t PS0_IMU, uint8_t PS1_IMU);

    /**
     * @brief Destroy object
     * 
     */
    ~IMU();

    /**
     * @brief Set the Cycle Rotation Vector
     * 
     * @param cycleRotationVector Time in miliseconds
     * @return RC_e Result code
     */
    RC_e SetCycleRotationVector(uint16_t cycleRotationVector);

    /**
     * @brief Run
     * 
     * @return RC_e Result code
     */
    RC_e Run();

    /**
     * @brief Invert Roll
     * 
     * @return RC_e Result code.
     */
    RC_e InvertRoll();

    /**
     * @brief Invert Pitch
     * 
     * @return RC_e Result code.
     */
    RC_e InvertPitch();

    /**
     * @brief Invert Yaw
     * 
     * @return RC_e Result code.
     */
    RC_e InvertYaw();

   
private:

    BNO080* m_BNO080 = NULL;        /**@brief Instance of the BNO080 IMU sensor. */

    /**
     * @brief Calculate the IMU values
     * 
     * @return RC_e Result code
     */
    RC_e Calculate();

};

#endif // IMU_H