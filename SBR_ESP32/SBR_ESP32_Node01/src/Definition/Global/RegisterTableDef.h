/**
 * @file RegisterTableDef.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Register Table
 * 
 */

#ifndef REGISTERTABLEDEF_H
#define REGISTERTABLEDEF_H

/**
 * @brief Enumeration for SBR registers.
 * 
 */
enum COM_REQUEST_REG_ID_e {
    NONE_REG_ID = 0,
    STATUS_HEARTBEAT_ESP32_COUNTER_R,           /**@brief Counter */
    STATUS_HEARTBEAT_LINUX_COUNTER_R,	        /**@brief Counter */
    STATUS_NODE_LINUX_R,	                    /**@brief Bit */
    STATUS_NODE_ESP32_R,	                    /**@brief Bit */
    MODE_MANAGER_RESTART_W,	                    /**@brief Bit */
    MODE_MANAGER_PROGRAM_W,	                    /**@brief Bit */
    MODE_MANAGER_GET_DATA_RW,	                /**@brief 0=NoRequest; 1=Request; 2=inProcess; 3=Completed; 4=Loaded */
    MODE_LINUX_GET_DATA_RW,	                    /**@brief 0=NoRequest; 1=Request; 2=inProcess; 3=Completed; 4=Loaded */
    MODE_NODE1_RESTART_W,	                    /**@brief Bit */
    MODE_NODE1_PROGRAM_W,	                    /**@brief Bit */
    MODE_NODE1_GET_DATA_RW,	                    /**@brief 0=NoRequest; 1=Request; 2=inProcess; 3=Completed; 4=Loaded */
    MODE_NODE1_START_W,                         /**@brief Bit */
    MODE_NODE1_STOP_W,	                        /**@brief Bit */
    MODE_NODE1_MODE_R,	                        /**@brief 0=NA; 1=IDLE; 2=Motion */
    SETUP_MOTOR_LEFT_OFFSET_W,	                /**@brief Factor: 100 */
    SETUP_MOTOR_LEFT_OFFSET_R,	                /**@brief Factor: 100  */
    SETUP_MOTOR_LEFT_DIRECTION_W,	            /**@brief Bit */
    SETUP_MOTOR_LEFT_DIRECTION_R,	            /**@brief Bit */
    SETUP_MOTOR_RIGHT_OFFSET_W,	                /**@brief Factor: 100  */
    SETUP_MOTOR_RIGHT_OFFSET_R,	                /**@brief Factor: 100  */
    SETUP_MOTOR_RIGHT_DIRECTION_W,	            /**@brief Bit */
    SETUP_MOTOR_RIGHT_DIRECTION_R,	            /**@brief Bit  */
    SETUP_IMU_INVERT_PITCH_W,	                /**@brief Bit */
    SETUP_IMU_INVERT_PITCH_R,	                /**@brief Bit */
    SETUP_IMU_INVERT_ROLL_W,	                /**@brief Bit */
    SETUP_IMU_INVERT_ROLL_R,                    /**@brief Bit */
    SETUP_IMU_INVERT_YAW_W,	                    /**@brief Bit */
    SETUP_IMU_INVERT_YAW_R,	                    /**@brief Bit */
    SETUP_IMU_OFFSET_PITCH_W,	                /**@brief Bit */
    SETUP_IMU_OFFSET_PITCH_R,	                /**@brief Bit */
    SETUP_ENCODER_DIRECTION_W,	                /**@brief Bit */
    SETUP_ENCODER_DIRECTION_R,	                /**@brief Bit */
    SETUP_ODOMETRY_WHEEL_RADIO_W,	            /**@brief Factor: 1000 */
    SETUP_ODOMETRY_WHEEL_RADIO_R,	            /**@brief Factor: 1000  */
    SETUP_ODOMETRY_DISTANCE_WHEELS_W,           /**@brief Factor: 1000  */
    SETUP_ODOMETRY_DISTANCE_WHEELS_R,           /**@brief Factor: 1000  */
    SETUP_ODOMETRY_TICKS_ENCODER_REV_W,	        /**@brief Factor: 1000  */
    SETUP_ODOMETRY_TICKS_ENCODER_REV_R,	        /**@brief Factor: 1000  */
    SETUP_MOTION_PID_PITCH_KP_W,	            /**@brief Factor: 1000  */
    SETUP_MOTION_PID_PITCH_KP_R,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_PITCH_KI_W,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_PITCH_KI_R,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_PITCH_KD_W,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_PITCH_KD_R,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_PITCH_CYCLE_R,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_PITCH_DIRECTION_W,         /**@brief Bit */
    SETUP_MOTION_PID_PITCH_DIRECTION_R,	        /**@brief Bit */
    SETUP_MOTION_PID_PITCH_MV_MIN_W,	        /**@brief Factor: 100 */
    SETUP_MOTION_PID_PITCH_MV_MIN_R,	        /**@brief Factor: 100 */
    SETUP_MOTION_PID_PITCH_MV_MAX_W,	        /**@brief Factor: 100 */
    SETUP_MOTION_PID_PITCH_MV_MAX_R,	        /**@brief Factor: 100 */
    SETUP_MOTION_PID_POSITION_KP_W,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_POSITION_KP_R,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_POSITION_KI_W,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_POSITION_KI_R,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_POSITION_KD_W,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_POSITION_KD_R,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_POSITION_CYCLE_R,	        /**@brief Factor: 1000 */
    SETUP_MOTION_PID_POSITION_DIRECTION_W,      /**@brief Bit */
    SETUP_MOTION_PID_POSITION_DIRECTION_R,	    /**@brief Bit */
    SETUP_MOTION_PID_POSITION_MV_MIN_W,	        /**@brief Factor: 100 */
    SETUP_MOTION_PID_POSITION_MV_MIN_R,	        /**@brief Factor: 100 */
    SETUP_MOTION_PID_POSITION_MV_MAX_W,	        /**@brief Factor: 100 */
    SETUP_MOTION_PID_POSITION_MV_MAX_R,	        /**@brief Factor: 100 */
    SETUP_MOTION_PID_ANGLE_KP_W,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_ANGLE_KP_R,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_ANGLE_KI_W,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_ANGLE_KI_R,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_ANGLE_KD_W,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_ANGLE_KD_R,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_ANGLE_CYCLE_R,	            /**@brief Factor: 1000 */
    SETUP_MOTION_PID_ANGLE_DIRECTION_W,         /**@brief Bit */
    SETUP_MOTION_PID_ANGLE_DIRECTION_R,	        /**@brief Bit */
    SETUP_MOTION_PID_ANGLE_MV_MIN_W,	        /**@brief Factor: 100 */
    SETUP_MOTION_PID_ANGLE_MV_MIN_R,	        /**@brief Factor: 100 */
    SETUP_MOTION_PID_ANGLE_MV_MAX_W,            /**@brief Factor: 100 */
    SETUP_MOTION_PID_ANGLE_MV_MAX_R,            /**@brief Factor: 100 */
    LIVE_MOTOR_LEFT_SPEED_W,                    /**@brief Factor: 100 */
    LIVE_MOTOR_LEFT_SPEED_R,                    /**@brief Factor: 100 */
    LIVE_MOTOR_RIGHT_SPEED_W,                   /**@brief Factor: 100 */
    LIVE_MOTOR_RIGHT_SPEED_R,	                /**@brief Factor: 100 */
    LIVE_IMU_PITCH_R,                           /**@brief Factor: 100 */
    LIVE_IMU_ROLL_R,	                        /**@brief Factor: 100 */
    LIVE_IMU_YAW_R,	                            /**@brief Factor: 100 */
    LIVE_ENCODER_LEFT_COUNT_R,	                /**@brief Factor: 1 */
    LIVE_ENCODER_RIGHT_COUNT_R,	                /**@brief Factor: 1 */
    LIVE_ODOMETRY_X_W,	                        /**@brief Factor: 1000 */
    LIVE_ODOMETRY_X_R,	                        /**@brief Factor: 1000 */
    LIVE_ODOMETRY_Y_W,	                        /**@brief Factor: 1000 */
    LIVE_ODOMETRY_Y_R,	                        /**@brief Factor: 1000 */
    LIVE_ODOMETRY_ANGLE_W,	                    /**@brief Factor: 100 */
    LIVE_ODOMETRY_ANGLE_R,                      /**@brief Factor: 100 */
    LIVE_ODOMETRY_DISTANCE_W,	                /**@brief Factor: 1000 */
    LIVE_ODOMETRY_DISTANCE_R,	                /**@brief Factor: 1000 */
    LIVE_ODOMETRY_RESET_W,	                    /**@brief Bit */
    LIVE_MOTION_SP_POSITION_W,	                /**@brief Factor: 1000 */
    LIVE_MOTION_SP_POSITION_R,	                /**@brief Factor: 1000 */
    LIVE_MOTION_SP_ANGLE_W,	                    /**@brief Factor: 100 */
    LIVE_MOTION_SP_ANGLE_R,	                    /**@brief Factor: 100 */
	LENGTH_REG_ID                               /**@brief Number of registers */					            
};

#endif /* REGISTERTABLEDEF_H */