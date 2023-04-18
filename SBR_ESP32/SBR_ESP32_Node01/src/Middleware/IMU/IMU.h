/**
 * @file IMU.h
 * @author Luis Arellano - luis.arellano09@gmail.com
 * @brief IMU Class
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

    /**
     * @brief Construct a new IMU object
     * 
     * @param user_CSPin CS Pin
     * @param user_WAKPin WAK Pin
     * @param user_INTPin INT Pin
     * @param user_RSTPin RST Pin
     * @param spiPortSpeed SPI Port Speed
     * @param CLK_IMU CLK Pin
     * @param MISO_IMU MISO Pin
     * @param MOSI_IMU MOSI Pin
     * @param PS0_IMU PSO Pin
     * @param PS1_IMU PS1 Pin
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
     * @brief Get the Direction Roll
     * 
     * @return RC_e Result code
     */
    bool GetDirectionRoll();

    /**
     * @brief Invert Pitch
     * 
     * @return RC_e Result code.
     */
    RC_e InvertPitch();

    /**
     * @brief Get the Direction Pitch
     * 
     * @return RC_e Result code
     */
    bool GetDirectionPitch();

    /**
     * @brief Invert Yaw
     * 
     * @return RC_e Result code.
     */
    RC_e InvertYaw();

    /**
     * @brief Get the Direction Yaw
     * 
     * @return RC_e Result code
     */
    bool GetDirectionYaw();

    /**
     * @brief Set the Pitch Offset
     * 
     * @param pitchOffset Pitch Offset
     * @return RC_e Result code.
     */
    RC_e SetPitchOffset(double pitchOffset);

    /**
     * @brief Get the Pitch Offset
     * 
     * @return double Pitch Offset
     */
    double GetPitchOffset();

    /**
     * @brief Get the Roll
     * 
     * @return double Roll
     */
    double GetRoll();

    /**
     * @brief Get the Pitch
     * 
     * @return double Pitch
     */
    double GetPitch();

    /**
     * @brief Get the Yaw
     * 
     * @return double Yaw
     */
    double GetYaw();

   
private:

    BNO080* m_BNO080 = NULL;            /**@brief Instance of the BNO080 IMU sensor. */
    double m_Roll = 0.0;                /**@brief IMU Roll: Front inclination. */
    double m_Pitch = 0.0;               /**@brief IMU Pitch: Lateral inclination. */
    double m_Yaw = 0.0;                 /**@brief IMU Yaw: Rotation. */
    bool m_invertRoll = false;          /**@brief Invert Roll, 0=normal 1=invert */
    bool m_invertPitch = false;         /**@brief Invert Pitch, 0=normal 1=invert */
    bool m_invertYaw = false;           /**@brief Invert Yaw, 0=normal 1=invert */
    double m_pitchOffset = 0.0;         /**@brief Pitch Offset */

    double m_initialYaw = -99999999.9;  /**@brief Initial Yaw */
    int m_numberOfTurns = 0;            /**@brief Number of turns */
    uint8_t m_quadrant = 0;             /**@brief Quadrant */
    uint8_t m_quadrantPrev = 0;         /**@brief Previous quadrant */	

    /**
     * @brief Calculate the IMU values
     * 
     * @return RC_e Result code
     */
    RC_e Calculate();

};

#endif // IMU_H