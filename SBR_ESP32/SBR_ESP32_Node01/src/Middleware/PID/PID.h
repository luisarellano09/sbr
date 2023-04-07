/**
 * @file PID.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief PID Class
 * @date 28.03.2023
 * 
 */

#ifndef PID_H
#define PID_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "PIDConfig.h"
#include <Arduino.h>
#include "../../Definition/Global/RC.h"

/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief PID Class
 * 
 */
class PID {
public:  

    double m_SP = 0.0;              /**@brief Setpoint */
    double m_PV = 0.0;              /**@brief Process value */
    double m_MV = 0.0;              /**@brief Manipulated variable */
    double m_kp = 1.0;              /**@brief Proportional constant */
    double m_ki = 1.0;              /**@brief Integral constant */
    double m_kd = 1.0;              /**@brief Differential constant */
    double m_error = 0.0;           /**@brief Error = SP - PV */
    double m_cycleTime = 0.1;       /**@brief Cycle Time in seconds*/
    PIDDirection_e m_direction;     /**@brief PID Direction */
    PIDMode m_mode;                 /**@brief PID Mode */
    double m_mvRangeMin = -100.0;   /**@brief Manipulated Variable Range Min */
    double m_mvRangeMax = 100.0;    /**@brief Manipulated Variable Range Max */ 
    
    /**
     * @brief Construct a new PID object
     * 
     * @param direction PID direction
     */
    PID(PIDDirection_e direction = PIDDirection_e::PID_DIRECTION_DIRECT);

    /**
     * @brief Destroy the PID object
     * 
     */
    ~PID();

    RC_e Run();

    /**
     * @brief Set the Parameters
     * 
     * @param kp Proportional constant
     * @param ki Integral constant
     * @param kd Differential constant
     * @return RC_e Result code
     */
    RC_e SetParameters(double kp, double ki, double kd);

    /**
     * @brief Set the Cycle Time in seconds
     * 
     * @param cycleTime Cycle time in seconds
     * @return RC_e Result code
     */
    RC_e SetCycleTime(double cycleTime);

    /**
     * @brief Set the Direction
     * 
     * @param direction PID direction
     * @return RC_e Result code
     */
    RC_e SetDirection(PIDDirection_e direction);

    /**
     * @brief Set Manipulated Variable Range
     * 
     * @param mvRangeMin Manipulated Variable Range Min
     * @param mvRangeMax Manipulated Variable Range Max
     * @return RC_e Result code
     */
    RC_e SetMVRange(double mvRangeMin, double mvRangeMax);

    /**
     * @brief Start PID
     * 
     * @return RC_e Result code
     */
    RC_e Start();

    /**
     * @brief Stop PID
     * 
     * @return RC_e Result code
     */
    RC_e Stop();

    /**
     * @brief Set the PID SP
     * 
     * @param SP PID SP
     * @return RC_e Result code
     */
    RC_e SetSP(double SP);

    /**
     * @brief Set the PID PV
     * 
     * @param PV PID PV
     * @return RC_e Result code
     */
    RC_e SetPV(double PV);

    /**
     * @brief Get the MV
     * 
     * @return MV MV
     */
    double GetMV();

    /**
     * @brief Print
     * 
     * @return RC_e Result code
     */
    RC_e Print();

private:

    double m_prevMVIntegral = 0.0;  /**@brief Previous MV Integral part */
    double m_prevError = 0.0;       /**@brief Previous Error */
};

#endif // PID_H