/**
 * @file Odometry.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Odometry Class
 * 
 */

#ifndef ODOMETRY_H
#define ODOMETRY_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include <Arduino.h>
#include "../Encoder/Encoder.h"
#include "../../Definition/Global/RC.h"


/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Odometry Class
 * 
 */
class Odometry {
public:  

    /**
     * @brief Construct a new Odometry object
     * 
     * @param encoderLeft Encoder Left
     * @param encoderRight Encoder Right
     * @param radio Radio of the wheel
     * @param D Distance between the wheels 
     * @param TR Number of counts in one revolution
     */
    Odometry(Encoder* encoderLeft, Encoder* encoderRight, double radio, double D, double TR);

    /**
     * @brief Destructor
     * 
     */
    ~Odometry();

    /**
     * @brief Run
     * 
     * @return RC_e Result Code
     */
    RC_e Run();

    /**
     * @brief Set X coordinate 
     * 
     * @param x X coordinate 
     * @return RC_e Result Code
     */
    RC_e SetX(double x);

    /**
     * @brief Set Y coordinate 
     * 
     * @param y Y coordinate 
     * @return RC_e Result Code
     */
    RC_e SetY(double y);

    /**
     * @brief Set the Angle
     * 
     * @param angle Angle
     * @return RC_e Result Code
     */
    RC_e SetAngle(double angle);

    /**
     * @brief Set the Distance
     * 
     * @param distance Distance
     * @return RC_e Result Code
     */
    RC_e SetDistance(double distance);

    /**
     * @brief Get X coordinate
     * 
     * @return double X coordinate
     */
    double GetX();

    /**
     * @brief Get Y coordinate
     * 
     * @return double X coordinate 
     */
    double GetY();

    /**
     * @brief Get the Angle
     * 
     * @return double Angle
     */
    double GetAngle();

    /**
     * @brief Get the Distance
     * 
     * @return double Distance
     */
    double GetDistance();


private:

    Encoder* m_encoderLeft = NULL;          /**@brief Encoder left */
    Encoder* m_encoderRight = NULL;         /**@brief Encoder right */
    double m_x;                             /**@brief X coordinate */
    double m_y;                             /**@brief Y coordinate */
    double m_distance;                      /**@brief Distance */
    double m_angle;                         /**@brief Angle */
    double m_radio;                         /**@brief Radio of the wheel*/            
    double m_D;                             /**@brief Distance between the wheels */
    double m_TR;                            /**@brief Number of counts in one revolution */
    double m_prevEncoderLeftCount = 0.0;    /**@brief Previous encoder left count */
    double m_prevEncoderRightCount = 0.0;   /**@brief Previous encoder right count */
};

#endif // ODOMETRY_H