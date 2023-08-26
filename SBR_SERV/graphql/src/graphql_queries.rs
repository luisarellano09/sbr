
use juniper::{graphql_object, FieldResult};
use crate::graphql_context::ContextGraphQL;
use crate::graphql_types::{Esp32LiveMotors, Esp32Status, Esp32Mode, Esp32SetupMotors, Esp32SetupIMU, Esp32SetupEncoders, Esp32SetupMotionPID, Esp32LiveIMU, Esp32LiveEncoders, Esp32LiveOdometry, Esp32LiveMotion, Esp32Setup, RegisterCommand, Esp32SetupOdometry};
use crate::postgres_connection::connect_postgres;
use r2d2_redis::redis::{Commands, RedisResult};


//=====================================================================================================
pub struct Queries;


//=====================================================================================================
#[graphql_object(context = ContextGraphQL)]
impl Queries {

    //=====================================================================================================
    fn GetEsp32Status( context: &ContextGraphQL) -> FieldResult<Esp32Status> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let heartbeat_raw: i32 = conn.get("ESP32.READ.STATUS.HEARTBEAT")?;
        let node_linux_raw: bool = conn.get("ESP32.READ.STATUS.NODE_LINUX_R")?;
        let node_esp32_raw: bool = conn.get("ESP32.READ.STATUS.NODE_ESP32_R")?;

        Ok(Esp32Status { 
            heartbeat: heartbeat_raw,
            node_linux: node_linux_raw,
            node_esp32: node_esp32_raw,
        })
    }


    //=====================================================================================================
    fn GetEsp32ModeManagerSyncData( context: &ContextGraphQL) -> FieldResult<RegisterCommand> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let res_cmd: RedisResult<i32> = conn.get("ESP32.READ.MODE.MANAGER.SYNC_DATA_RW");

        match res_cmd {
            Ok(cmd) => {
                match cmd{
                    0 => Ok(RegisterCommand::None), 
                    1 => Ok(RegisterCommand::Requested),
                    2 => Ok(RegisterCommand::InProgress),
                    3 => Ok(RegisterCommand::ReadyToComplete),
                    4 => Ok(RegisterCommand::Completed),
                    _ => Ok(RegisterCommand::None),
                }
            }, 
            Err(_) => {
                Ok(RegisterCommand::None)
            }
        }
    }


    //=====================================================================================================
    fn GetEsp32ModeLinuxSyncData( context: &ContextGraphQL) -> FieldResult<RegisterCommand> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let res_cmd: RedisResult<i32> = conn.get("ESP32.READ.MODE.LINUX.SYNC_DATA_RW");

        match res_cmd {
            Ok(cmd) => {
                match cmd{
                    0 => Ok(RegisterCommand::None), 
                    1 => Ok(RegisterCommand::Requested),
                    2 => Ok(RegisterCommand::InProgress),
                    3 => Ok(RegisterCommand::ReadyToComplete),
                    4 => Ok(RegisterCommand::Completed),
                    _ => Ok(RegisterCommand::None),
                }
            }, 
            Err(_) => {
                Ok(RegisterCommand::None)
            }
        }
    }


    //=====================================================================================================
    fn GetEsp32ModeNode1SyncData( context: &ContextGraphQL) -> FieldResult<RegisterCommand> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let res_cmd: RedisResult<i32> = conn.get("ESP32.READ.MODE.NODE1.SYNC_DATA_RW");

        match res_cmd {
            Ok(cmd) => {
                match cmd{
                    0 => Ok(RegisterCommand::None), 
                    1 => Ok(RegisterCommand::Requested),
                    2 => Ok(RegisterCommand::InProgress),
                    3 => Ok(RegisterCommand::ReadyToComplete),
                    4 => Ok(RegisterCommand::Completed),
                    _ => Ok(RegisterCommand::None),
                }
            }, 
            Err(_) => {
                Ok(RegisterCommand::None)
            }
        }
    }

    
    //=====================================================================================================
    fn GetEsp32Mode( context: &ContextGraphQL) -> FieldResult<Esp32Mode> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let manager_sync_data_raw: i32 = conn.get("ESP32.READ.MODE.MANAGER.SYNC_DATA_RW")?;
        let linux_sync_data_raw: i32 = conn.get("ESP32.READ.MODE.LINUX.SYNC_DATA_RW")?;

        Ok(Esp32Mode { 
            manager_sync_data: manager_sync_data_raw,
            linux_sync_data: linux_sync_data_raw,
        })
    }

    
    //=====================================================================================================
    fn GetEsp32SetupMotors( context: &ContextGraphQL) -> FieldResult<Esp32SetupMotors> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let motor_left_offset_raw: i32 = conn.get("ESP32.READ.SETUP.MOTOR_LEFT.OFFSET_R")?;
        let motor_right_offset_raw: i32 = conn.get("ESP32.READ.SETUP.MOTOR_RIGHT.OFFSET_R")?;
        let motor_left_direction_raw: bool = conn.get("ESP32.READ.SETUP.MOTOR_LEFT.DIRECTION_R")?;
        let motor_right_direction_raw: bool = conn.get("ESP32.READ.SETUP.MOTOR_RIGHT.DIRECTION_R")?;

        Ok(Esp32SetupMotors { 
            motor_left_offset: Some((motor_left_offset_raw as f64) / 100.0),
            motor_right_offset: Some((motor_right_offset_raw as f64) / 100.0),
            motor_left_direction: Some(motor_left_direction_raw),
            motor_right_direction: Some(motor_right_direction_raw),
        })
    }


    //=====================================================================================================
    fn GetEsp32SetupEncoders( context: &ContextGraphQL) -> FieldResult<Esp32SetupEncoders> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let encoder_left_direction_raw: bool = conn.get("ESP32.READ.SETUP.ENCODER_LEFT.DIRECTION_R")?;
        let encoder_right_direction_raw: bool = conn.get("ESP32.READ.SETUP.ENCODER_RIGHT.DIRECTION_R")?;

        Ok(Esp32SetupEncoders { 
            encoder_left_direction: Some(encoder_left_direction_raw),
            encoder_right_direction: Some(encoder_right_direction_raw),
        })
    }
    
    
    //=====================================================================================================
    fn GetEsp32SetupIMU( context: &ContextGraphQL) -> FieldResult<Esp32SetupIMU> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let invert_pitch_raw: bool = conn.get("ESP32.READ.SETUP.IMU.INVERT_PITCH_R")?;
        let invert_roll_raw: bool = conn.get("ESP32.READ.SETUP.IMU.INVERT_ROLL_R")?;
        let invert_yaw_raw: bool = conn.get("ESP32.READ.SETUP.IMU.INVERT_YAW_R")?;
        let offset_pitch_raw: i32 = conn.get("ESP32.READ.SETUP.IMU.OFFSET_PITCH_R")?;

        Ok(Esp32SetupIMU { 
            invert_pitch: Some(invert_pitch_raw),
            invert_roll: Some(invert_roll_raw),
            invert_yaw: Some(invert_yaw_raw),
            offset_pitch: Some((offset_pitch_raw as f64) / 100.0),
        })
    }


    //=====================================================================================================
    fn GetEsp32SetupOdometry( context: &ContextGraphQL) -> FieldResult<Esp32SetupOdometry> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let wheel_radio_raw: i32 = conn.get("ESP32.READ.SETUP.ODOMETRY.DISTANCE_WHEELS_R")?;
        let distance_wheels_raw: i32 = conn.get("ESP32.READ.SETUP.ODOMETRY.WHEEL_RADIO_R")?;

        Ok(Esp32SetupOdometry { 
            wheel_radio: Some((wheel_radio_raw as f64) / 1000.0),
            distance_wheels: Some((distance_wheels_raw as f64) / 1000.0),
        })
    }

    
    //=====================================================================================================
    fn GetEsp32SetupMotionPidPitch( context: &ContextGraphQL) -> FieldResult<Esp32SetupMotionPID> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let kp_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.KP_R")?;
        let ki_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.KI_R")?;
        let kd_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.KD_R")?;
        let cycle_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.CYCLE_R")?;
        let direction_raw: bool = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.DIRECTION_R")?;
        let mv_min_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.MV_MIN_R")?;
        let mv_max_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.MV_MAX_R")?;

        Ok(Esp32SetupMotionPID { 
            kp: Some((kp_raw as f64) / 1000.0),
            ki: Some((ki_raw as f64) / 1000.0),
            kd: Some((kd_raw as f64) / 1000.0),
            cycle: Some((cycle_raw  as f64) / 1000.0),
            direction: Some(direction_raw),
            mv_min: Some((mv_min_raw as f64) / 100.0),
            mv_max: Some((mv_max_raw as f64) / 100.0),
        })
    }

    
    //=====================================================================================================
    fn GetEsp32SetupMotionPidPosition( context: &ContextGraphQL) -> FieldResult<Esp32SetupMotionPID> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let kp_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.KP_R")?;
        let ki_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.KI_R")?;
        let kd_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.KD_R")?;
        let cycle_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.CYCLE_R")?;
        let direction_raw: bool = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.DIRECTION_R")?;
        let mv_min_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.MV_MIN_R")?;
        let mv_max_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.MV_MAX_R")?;

        Ok(Esp32SetupMotionPID { 
            kp: Some((kp_raw as f64) / 1000.0),
            ki: Some((ki_raw as f64) / 1000.0),
            kd: Some((kd_raw as f64) / 1000.0),
            cycle: Some((cycle_raw  as f64) / 1000.0),
            direction: Some(direction_raw),
            mv_min: Some((mv_min_raw as f64) / 100.0),
            mv_max: Some((mv_max_raw as f64) / 100.0),
        })
    }

    
    //=====================================================================================================
    fn GetEsp32SetupMotionPidAngle( context: &ContextGraphQL) -> FieldResult<Esp32SetupMotionPID> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let kp_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.KP_R")?;
        let ki_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.KI_R")?;
        let kd_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.KD_R")?;
        let cycle_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.CYCLE_R")?;
        let direction_raw: bool = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.DIRECTION_R")?;
        let mv_min_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.MV_MIN_R")?;
        let mv_max_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.MV_MAX_R")?;

        Ok(Esp32SetupMotionPID { 
            kp: Some((kp_raw as f64) / 1000.0),
            ki: Some((ki_raw as f64) / 1000.0),
            kd: Some((kd_raw as f64) / 1000.0),
            cycle: Some((cycle_raw  as f64) / 1000.0),
            direction: Some(direction_raw),
            mv_min: Some((mv_min_raw as f64) / 100.0),
            mv_max: Some((mv_max_raw as f64) / 100.0),
        })
    }


    //=====================================================================================================
    fn GetEsp32Setup( context: &ContextGraphQL) -> FieldResult<Esp32Setup> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let motor_left_offset_raw: i32 = conn.get("ESP32.READ.SETUP.MOTOR_LEFT.OFFSET_R")?;
        let motor_right_offset_raw: i32 = conn.get("ESP32.READ.SETUP.MOTOR_RIGHT.OFFSET_R")?;
        let motor_left_direction_raw: bool = conn.get("ESP32.READ.SETUP.MOTOR_LEFT.DIRECTION_R")?;
        let motor_right_direction_raw: bool = conn.get("ESP32.READ.SETUP.MOTOR_RIGHT.DIRECTION_R")?;

        let encoder_left_direction_raw: bool = conn.get("ESP32.READ.SETUP.ENCODER_LEFT.DIRECTION_R")?;
        let encoder_right_direction_raw: bool = conn.get("ESP32.READ.SETUP.ENCODER_RIGHT.DIRECTION_R")?;

        let invert_pitch_raw: bool = conn.get("ESP32.READ.SETUP.IMU.INVERT_PITCH_R")?;
        let invert_roll_raw: bool = conn.get("ESP32.READ.SETUP.IMU.INVERT_ROLL_R")?;
        let invert_yaw_raw: bool = conn.get("ESP32.READ.SETUP.IMU.INVERT_YAW_R")?;
        let offset_pitch_raw: i32 = conn.get("ESP32.READ.SETUP.IMU.OFFSET_PITCH_R")?;

        let wheel_radio_raw: i32 = conn.get("ESP32.READ.SETUP.ODOMETRY.DISTANCE_WHEELS_R")?;
        let distance_wheels_raw: i32 = conn.get("ESP32.READ.SETUP.ODOMETRY.WHEEL_RADIO_R")?;

        let motion_pid_pitch_kp_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.KP_R")?;
        let motion_pid_pitch_ki_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.KI_R")?;
        let motion_pid_pitch_kd_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.KD_R")?;
        let motion_pid_pitch_cycle_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.CYCLE_R")?;
        let motion_pid_pitch_direction_raw: bool = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.DIRECTION_R")?;
        let motion_pid_pitch_mv_min_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.MV_MIN_R")?;
        let motion_pid_pitch_mv_max_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.MV_MAX_R")?;

        let motion_pid_position_kp_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.KP_R")?;
        let motion_pid_position_ki_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.KI_R")?;
        let motion_pid_position_kd_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.KD_R")?;
        let motion_pid_position_cycle_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.CYCLE_R")?;
        let motion_pid_position_direction_raw: bool = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.DIRECTION_R")?;
        let motion_pid_position_mv_min_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.MV_MIN_R")?;
        let motion_pid_position_mv_max_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.MV_MAX_R")?;

        let motion_pid_angle_kp_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.KP_R")?;
        let motion_pid_angle_ki_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.KI_R")?;
        let motion_pid_angle_kd_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.KD_R")?;
        let motion_pid_angle_cycle_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.CYCLE_R")?;
        let motion_pid_angle_direction_raw: bool = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.DIRECTION_R")?;
        let motion_pid_angle_mv_min_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.MV_MIN_R")?;
        let motion_pid_angle_mv_max_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.MV_MAX_R")?;

        Ok( Esp32Setup{
            motors: Some(Esp32SetupMotors { 
                motor_left_offset: Some((motor_left_offset_raw as f64) / 100.0),
                motor_right_offset: Some((motor_right_offset_raw as f64) / 100.0),
                motor_left_direction: Some(motor_left_direction_raw),
                motor_right_direction: Some(motor_right_direction_raw),
            }), 
            encoders: Some(Esp32SetupEncoders { 
                encoder_left_direction: Some(encoder_left_direction_raw),
                encoder_right_direction: Some(encoder_right_direction_raw),
            }),
            imu: Some(Esp32SetupIMU { 
                invert_pitch: Some(invert_pitch_raw),
                invert_roll: Some(invert_roll_raw),
                invert_yaw: Some(invert_yaw_raw),
                offset_pitch: Some((offset_pitch_raw as f64) / 100.0),
            }),
            odometry: Some(Esp32SetupOdometry { 
                wheel_radio: Some((wheel_radio_raw as f64) / 1000.0),
                distance_wheels: Some((distance_wheels_raw as f64) / 1000.0),
            }),
            motion_pid_pitch: Some(Esp32SetupMotionPID { 
                kp: Some((motion_pid_pitch_kp_raw as f64) / 1000.0),
                ki: Some((motion_pid_pitch_ki_raw as f64) / 1000.0),
                kd: Some((motion_pid_pitch_kd_raw as f64) / 1000.0),
                cycle: Some((motion_pid_pitch_cycle_raw  as f64) / 1000.0),
                direction: Some(motion_pid_pitch_direction_raw),
                mv_min: Some((motion_pid_pitch_mv_min_raw as f64) / 100.0),
                mv_max: Some((motion_pid_pitch_mv_max_raw as f64) / 100.0),
            }),
            motion_pid_position: Some(Esp32SetupMotionPID { 
                kp: Some((motion_pid_position_kp_raw as f64) / 1000.0),
                ki: Some((motion_pid_position_ki_raw as f64) / 1000.0),
                kd: Some((motion_pid_position_kd_raw as f64) / 1000.0),
                cycle: Some((motion_pid_position_cycle_raw  as f64) / 1000.0),
                direction: Some(motion_pid_position_direction_raw),
                mv_min: Some((motion_pid_position_mv_min_raw as f64) / 100.0),
                mv_max: Some((motion_pid_position_mv_max_raw as f64) / 100.0),
            }),
            motion_pid_angle: Some(Esp32SetupMotionPID { 
                kp: Some((motion_pid_angle_kp_raw as f64) / 1000.0),
                ki: Some((motion_pid_angle_ki_raw as f64) / 1000.0),
                kd: Some((motion_pid_angle_kd_raw as f64) / 1000.0),
                cycle: Some((motion_pid_angle_cycle_raw  as f64) / 1000.0),
                direction: Some(motion_pid_angle_direction_raw),
                mv_min: Some((motion_pid_angle_mv_min_raw as f64) / 100.0),
                mv_max: Some((motion_pid_angle_mv_max_raw as f64) / 100.0),
            }),
        })
    }
    
    
    //=====================================================================================================
    fn GetEsp32LiveMotors( context: &ContextGraphQL) -> FieldResult<Esp32LiveMotors> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let motor_left_speed_raw: i32 = conn.get("ESP32.READ.LIVE.MOTOR_LEFT.SPEED_R")?;
        let motor_right_speed_raw: i32 = conn.get("ESP32.READ.LIVE.MOTOR_RIGHT.SPEED_R")?;

        Ok(Esp32LiveMotors { 
            motor_left_speed: (motor_left_speed_raw as f64) / 100.0,
            motor_right_speed: (motor_right_speed_raw as f64) / 100.0, 
        })
    }

    
    //=====================================================================================================
    fn GetEsp32LiveIMU( context: &ContextGraphQL) -> FieldResult<Esp32LiveIMU> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let pitch_raw: i32 = conn.get("ESP32.READ.LIVE.IMU.PITCH_R")?;
        let roll_raw: i32 = conn.get("ESP32.READ.LIVE.IMU.ROLL_R")?;
        let yaw_raw: i32 = conn.get("ESP32.READ.LIVE.IMU.YAW_R")?;

        Ok(Esp32LiveIMU { 
            pitch: (pitch_raw as f64) / 100.0,
            roll: (roll_raw as f64) / 100.0,
            yaw: (yaw_raw as f64) / 100.0, 
        })
    }

    
    //=====================================================================================================
    fn GetEsp32LiveEncoders( context: &ContextGraphQL) -> FieldResult<Esp32LiveEncoders> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let encoder_left_count_raw: i32 = conn.get("ESP32.READ.LIVE.ENCODER.LEFT_COUNT_R")?;
        let encoder_right_count_raw: i32 = conn.get("ESP32.READ.LIVE.ENCODER.RIGHT_COUNT_R")?;

        Ok(Esp32LiveEncoders { 
            encoder_left_count: (encoder_left_count_raw as f64),
            encoder_right_count: (encoder_right_count_raw as f64),
        })
    }

    
    //=====================================================================================================
    fn GetEsp32LiveOdometry( context: &ContextGraphQL) -> FieldResult<Esp32LiveOdometry> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let x_raw: i32 = conn.get("ESP32.READ.LIVE.ODOMETRY.X_R")?;
        let y_raw: i32 = conn.get("ESP32.READ.LIVE.ODOMETRY.Y_R")?;
        let angle_raw: i32 = conn.get("ESP32.READ.LIVE.ODOMETRY.ANGLE_R")?;
        let distance_raw: i32 = conn.get("ESP32.READ.LIVE.ODOMETRY.DISTANCE_R")?;

        Ok(Esp32LiveOdometry { 
            x: (x_raw as f64) / 1000.0,
            y: (y_raw as f64) / 1000.0,
            angle: (angle_raw as f64) / 100.0,
            distance: (distance_raw as f64) / 1000.0,
        })
    }

    
    //=====================================================================================================
    fn GetEsp32LiveMotion( context: &ContextGraphQL) -> FieldResult<Esp32LiveMotion> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let setpoint_angle_raw: i32 = conn.get("ESP32.READ.LIVE.MOTION.SP_ANGLE_R")?;
        let setpoint_position_raw: i32 = conn.get("ESP32.READ.LIVE.MOTION.SP_POSITION_R")?;

        Ok(Esp32LiveMotion { 
            setpoint_angle: (setpoint_angle_raw as f64) / 100.0,
            setpoint_position: (setpoint_position_raw as f64) / 1000.0,
        })
    }


    //=====================================================================================================
    async fn GetDbEsp32Setup(_context: &ContextGraphQL) -> FieldResult<Esp32Setup> {

        let setup: Esp32Setup = Esp32Setup{..Default::default()};

        let client = connect_postgres().await?;
        
        for row in client.query("SELECT * FROM SETUP_ESP32 ORDER BY name ASC", &[]).await? {
            let name: String = row.try_get("NAME")?;
            let value: f64 = row.try_get("VALUE")?;

            match name.as_str() {
                
                "motor_left_direction" => {
                    setup.motors.unwrap().motor_left_direction = if value == 1.0 {Some(true)} else {Some(false)};
                },

                "motor_left_offset" => {
                    setup.motors.unwrap().motor_left_offset = Some(value);
                },

                "motor_right_direction" => {
                    setup.motors.unwrap().motor_right_direction = if value == 1.0 {Some(true)} else {Some(false)};
                },

                "motor_right_offset" => {
                    setup.motors.unwrap().motor_right_offset = Some(value);
                },

                "encoder_left_direction" => {
                    setup.encoders.unwrap().encoder_left_direction = if value == 1.0 {Some(true)} else {Some(false)};
                },

                "encoder_right_direction" => {
                    setup.encoders.unwrap().encoder_right_direction = if value == 1.0 {Some(true)} else {Some(false)};
                },

                "imu_invert_pitch" => {
                    setup.imu.unwrap().invert_pitch = if value == 1.0 {Some(true)} else {Some(false)};
                },

                "imu_invert_roll" => {
                    setup.imu.unwrap().invert_roll = if value == 1.0 {Some(true)} else {Some(false)};
                },

                "imu_invert_yaw" => {
                    setup.imu.unwrap().invert_yaw = if value == 1.0 {Some(true)} else {Some(false)};
                },

                "imu_offset_pitch" => {
                    setup.imu.unwrap().offset_pitch = Some(value);
                },

                "odometry_distance_wheels" => {
                    setup.odometry.unwrap().distance_wheels = Some(value);
                },

                "odometry_wheel_radio" => {
                    setup.odometry.unwrap().wheel_radio = Some(value);
                },

                "motion_pid_pitch_kp" => {
                    setup.motion_pid_pitch.unwrap().kp = Some(value);
                },

                "motion_pid_pitch_ki" => {
                    setup.motion_pid_pitch.unwrap().ki = Some(value);
                },

                "motion_pid_pitch_kd" => {
                    setup.motion_pid_pitch.unwrap().kd = Some(value);
                },

                "motion_pid_pitch_direction" => {
                    setup.motion_pid_pitch.unwrap().direction = if value == 1.0 {Some(true)} else {Some(false)};
                },

                "motion_pid_pitch_mv_min" => {
                    setup.motion_pid_pitch.unwrap().mv_min = Some(value);
                },

                "motion_pid_pitch_mv_max" => {
                    setup.motion_pid_pitch.unwrap().mv_max = Some(value);
                },

                "motion_pid_position_kp" => {
                    setup.motion_pid_position.unwrap().kp = Some(value);
                },

                "motion_pid_position_ki" => {
                    setup.motion_pid_position.unwrap().ki = Some(value);
                },

                "motion_pid_position_kd" => {
                    setup.motion_pid_position.unwrap().kd = Some(value);
                },

                "motion_pid_position_direction" => {
                    setup.motion_pid_position.unwrap().direction = if value == 1.0 {Some(true)} else {Some(false)};
                },

                "motion_pid_position_mv_min" => {
                    setup.motion_pid_position.unwrap().mv_min = Some(value);
                },

                "motion_pid_position_mv_max" => {
                    setup.motion_pid_position.unwrap().mv_max = Some(value);
                },

                "motion_pid_angle_kp" => {
                    setup.motion_pid_angle.unwrap().kp = Some(value);
                },

                "motion_pid_angle_ki" => {
                    setup.motion_pid_angle.unwrap().ki = Some(value);
                },

                "motion_pid_angle_kd" => {
                    setup.motion_pid_angle.unwrap().kd = Some(value);
                },

                "motion_pid_angle_direction" => {
                    setup.motion_pid_angle.unwrap().direction = if value == 1.0 {Some(true)} else {Some(false)};
                },

                "motion_pid_angle_mv_min" => {
                    setup.motion_pid_angle.unwrap().mv_min = Some(value);
                },

                "motion_pid_angle_mv_max" => {
                    setup.motion_pid_angle.unwrap().mv_max = Some(value);
                },

                _ => {}
            }
        }

        Ok(setup)
    }

}
