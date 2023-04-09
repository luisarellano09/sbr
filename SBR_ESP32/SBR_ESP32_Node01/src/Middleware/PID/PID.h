/**
 * @file PID.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief PID Class
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
     * @brief Get SP
     * 
     * @return double SP 
     */
    double GetSP();

    /**
     * @brief Set the PID PV
     * 
     * @param PV PID PV
     * @return RC_e Result code
     */
    RC_e SetPV(double PV);

    /**
     * @brief Get PV
     * 
     * @return double PV 
     */
    double GetPV();

    /**
     * @brief Get the MV
     * 
     * @return double MV
     */
    double GetMV();

    /**
     * @brief Get the Error
     * 
     * @return double Error
     */
    double GetError();

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
     * @brief Set the Kp
     * 
     * @param Kp Kp
     * @return RC_e Result code 
     */
    RC_e SetKp(double Kp);

    /**
     * @brief Get the Kp
     * 
     * @return double Kp
     */
    double GetKp();

    /**
     * @brief Set the Ki
     * 
     * @param Ki Ki
     * @return RC_e Result code 
     */
    RC_e SetKi(double Ki);

    /**
     * @brief Get the Ki
     * 
     * @return double Ki
     */
    double GetKi();

    /**
     * @brief Set the Kd
     * 
     * @param Kd Kd
     * @return RC_e Result code 
     */
    RC_e SetKd(double Kd);

    /**
     * @brief Get the Kd
     * 
     * @return double Kd
     */
    double GetKd();

    /**
     * @brief Set the Cycle Time
     * 
     * @param cycleTime Cycle execution time
     * @return RC_e Ressult code
     */
    RC_e SetCycleTime(double cycleTime);

    /**
     * @brief Get the Cycle Time
     * 
     * @return double Cycle time
     */
    double GetCycleTime();

    /**
     * @brief Set the Direction
     * 
     * @param direction Direction
     * @return RC_e Result code
     */
    RC_e SetDirection(PIDDirection_e direction);

    /**
     * @brief Get the Direction
     * 
     * @return PIDDirection_e Direction
     */
    PIDDirection_e GetDirection();

    /**
     * @brief Get the Mode
     * 
     * @return PIDMode Mode
     */
    PIDMode GetMode();

    /**
     * @brief Set Manipulated Variable Range
     * 
     * @param mvRangeMin Manipulated Variable Range Min
     * @param mvRangeMax Manipulated Variable Range Max
     * @return RC_e Result code
     */
    RC_e SetMVRange(double mvRangeMin, double mvRangeMax);

    /**
     * @brief Set the MV min range
     * 
     * @param mvRangeMin MV min range
     * @return RC_e Result code
     */
    RC_e SetMVRangeMin(double mvRangeMin);

    /**
     * @brief Get the MV min range
     * 
     * @return double MV min range
     */
    double GetMVRangeMin();

    /**
     * @brief Set the MV max range
     * 
     * @param mvRangeMax MV max range
     * @return RC_e Result code
     */
    RC_e SetMVRangeMax(double mvRangeMax);

    /**
     * @brief Get the MV max range
     * 
     * @return double MV max range
     */
    double GetMVRangeMax();
    
    /**
     * @brief Print
     * 
     * @return RC_e Result code
     */
    RC_e Print();


private:

    double m_SP = 0.0;              /**@brief Setpoint */
    double m_PV = 0.0;              /**@brief Process value */
    double m_MV = 0.0;              /**@brief Manipulated variable */
    double m_Kp = 1.0;              /**@brief Proportional constant */
    double m_Ki = 1.0;              /**@brief Integral constant */
    double m_Kd = 1.0;              /**@brief Differential constant */
    double m_error = 0.0;           /**@brief Error = SP - PV */
    double m_cycleTime = 0.1;       /**@brief Cycle Time in seconds*/
    PIDDirection_e m_direction;     /**@brief PID Direction */
    PIDMode m_mode;                 /**@brief PID Mode */
    double m_mvRangeMin = -100.0;   /**@brief Manipulated Variable Range Min */
    double m_mvRangeMax = 100.0;    /**@brief Manipulated Variable Range Max */ 
    double m_prevMVIntegral = 0.0;  /**@brief Previous MV Integral part */
    double m_prevError = 0.0;       /**@brief Previous Error */
};

#endif // PID_H