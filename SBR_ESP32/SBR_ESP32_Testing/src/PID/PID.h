/**
 * @file PID.h
 * @author jorge Salgado (jorgesalgado23@gmail.com)
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Class to Manage the PID
 * @version 1.0
 * @date 02.02.2021
 * 
 * 
 */

#ifndef PID_h
#define PID_h


/*******************************************************************************************************************************************
 *  												CLASS
 *******************************************************************************************************************************************/

/**
 * @brief Class to Manage the PID
 * 
 */
class PID
{


public:

  //Constants used in some of the functions below
  #define AUTOMATIC	1   /**<  */
  #define MANUAL	  0   /**<  */
  #define DIRECT    0   /**< positive forward             */
  #define REVERSE   1   /**< negative forward             */
  #define P_ON_M    0   /**< Proportional on Measurement  */
  #define P_ON_E    1   /**< Proportional on Error        */


  double kp;          /**< (P)roportional Tuning Parameter  */
  double ki;          /**< (I)ntegral Tuning Parameter      */
  double kd;          /**< (D)erivative Tuning Parameter    */
  
  /**
   * @brief Constructor commonly used functions
   * 
   * @param Input Input of PID
   * @param Output Output value of PID
   * @param Setpoint Initial tuning parameters are also set here.
   * @param Kp proportional coefficient
   * @param Ki Integral coefficient
   * @param Kd Derivative coefficient
   * @param POn proportional on Measurement or Error
   * @param ControllerDirection Positive or Negative forward
   */
  PID(double*, double*, double*, double, double, double, int, int); 
                                        
  /**
   * @brief Constructor commonly used functions
   * 
   * @param Input Input of PID
   * @param Output Output value of PID
   * @param Setpoint Setpoint
   * @param Kp proportional coefficient
   * @param Ki Integral coefficient
   * @param Kd Derivative coefficient
   * @param POn proportional on Measurement or Error
   */
  PID(double*, double*, double*, double, double, double, int);    

  /**
   * @brief sets PID to either Manual (0) or Auto (non-0)
   * 
   * @param Mode AUTOMATIC or MANUAL
   */	
  void SetMode(int Mode); 

  /**
   * @brief performs the PID calculation.  it should be
   * called every time loop() cycles. ON/OFF and
   * calculation frequency can be set using SetMode
   * SetSampleTime respectively
   * 
   * @return true if compute into the range of Simpletime
   */
  bool Compute();                       

  /**
   * @brief clamps the output to a specific range. 0-255 by default, but
   * it's likely the user will want to change this depending on
   * the application
   * 
   * @param Min Min Value
   * @param Max Max Value
   * 
   * @return None
   */
  void SetOutputLimits(double, double); 

  //available but not commonly used functions ********************************************************
  /**
   * @brief While most users will set the tunings once in the 
   * constructor, this function gives the user the option
   * of changing tunings during runtime for Adaptive control
   * 
   * @param Kp  New Proportional Coefficient
   * @param Ki  New integral Coefficient
   * @param Kd  New derivative Coefficient
   * 
   * @return None
   */
  void SetTunings(double, double, double);  

  /**
   * @brief overload for specifying proportional mode
   * 
   * @param Kp New Proportional Coefficient
   * @param Ki New Integral Coefficient
   * @param Kd New Derivative Coefficient
   * @param pOn Proportional on Measurement or Error
   * 
   * @return None
   */                                    
  void SetTunings(double, double, double, int);         	  


  /**
   * @brief Sets the Direction, or "Action" of the controller. DIRECT
   * means the output will increase when error is positive. REVERSE
   * means the opposite.  it's very unlikely that this will be needed
   * once it is set in the constructor.
   * 
   * @param Direction DIRECT or REVERSE
   * 
   * @return None
   */
	void SetControllerDirection(int);	   

  /**
   * @brief sets the frequency, in Milliseconds, with which 
   * the PID calculation is performed.  default is 1ms
   * 
   * @param NewSampleTime New period
   * 
   * @return None
   */
  void SetSampleTime(int);           

  /*Display functions ****************************************************************
  * These functions query the pid for interal values.
  * they were created mainly for the pid front-end,
  * where it's important to know what is actually 
  * inside the PID.*/
  /**
   * @brief get Kp
   * 
   * @return Kp Value
   */
	double GetKp();						  

  /**
   * @brief Get Ki
   * 
   * @return Ki Value
   */
	double GetKi();

  /**
   * @brief Get kd
   * 
   * @return Kd Value
   */
	double GetKd();	

  /**
   * @brief Get mode
   * 
   * @return  AUTOMATIC or MANUAL
   */
	int GetMode();						 

  /**
   * @brief Get Direction
   * 
   * @return controllerDirection
   */
	int GetDirection();					

  private:

	double dispKp;				// * we'll hold on to the tuning parameters in user-entered 
	double dispKi;				//   format for display purposes
	double dispKd;				//

	int controllerDirection;
	int pOn;

  double *myInput;              // * Pointers to the Input, Output, and Setpoint variables
  double *myOutput;             //   This creates a hard link between the variables and the 
  double *mySetpoint;           //   PID, freeing the user from having to constantly tell us
                                //   what these values are.  with pointers we'll just know.
	unsigned long lastTime;
	double outputSum, lastInput;

	unsigned long SampleTime;
	double outMin, outMax;
	bool inAuto, pOnE;

  /**
   * @brief does all the things that need to happen to ensure a bumpless transfer
   *  from manual to automatic mode.
   * 
   * @return None
   */
	void Initialize();
	

};
#endif  //PIS_H

