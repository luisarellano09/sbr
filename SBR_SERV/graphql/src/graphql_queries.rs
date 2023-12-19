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

        let heartbeat_raw: f64 = conn.get("ESP32.READ.STATUS.HEARTBEAT")?;
        let node_linux_raw: f64 = conn.get("ESP32.READ.STATUS.NODE_LINUX_R")?;
        let node_esp32_raw: f64 = conn.get("ESP32.READ.STATUS.NODE_ESP32_R")?;

        Ok(Esp32Status { 
            heartbeat: heartbeat_raw as i32,
            node_linux: if node_linux_raw == 1.0 {true} else {false} ,
            node_esp32: if node_esp32_raw == 1.0 {true} else {false} ,
        })
    }


    //=====================================================================================================
    fn GetEsp32ModeManagerSyncData( context: &ContextGraphQL) -> FieldResult<RegisterCommand> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let res_cmd: RedisResult<f64> = conn.get("ESP32.READ.MODE.MANAGER.SYNC_DATA_RW");

        match res_cmd {
            Ok(cmd) => {
                match cmd as i32{
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

        let res_cmd: RedisResult<f64> = conn.get("ESP32.READ.MODE.LINUX.SYNC_DATA_RW");

        match res_cmd {
            Ok(cmd) => {
                match cmd as i32{
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

        let res_cmd: RedisResult<f64> = conn.get("ESP32.READ.MODE.NODE1.SYNC_DATA_RW");

        match res_cmd {
            Ok(cmd) => {
                match cmd as i32{
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

        let manager_sync_data_raw: f64 = conn.get("ESP32.READ.MODE.MANAGER.SYNC_DATA_RW")?;
        let linux_sync_data_raw: f64 = conn.get("ESP32.READ.MODE.LINUX.SYNC_DATA_RW")?;

        Ok(Esp32Mode { 
            manager_sync_data: manager_sync_data_raw as i32,
            linux_sync_data: linux_sync_data_raw as i32,
        })
    }

    
    //=====================================================================================================
    fn GetEsp32SetupMotors( context: &ContextGraphQL) -> FieldResult<Esp32SetupMotors> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let motor_left_offset_raw: f64 = conn.get("ESP32.READ.SETUP.MOTOR_LEFT.OFFSET_R")?;
        let motor_right_offset_raw: f64 = conn.get("ESP32.READ.SETUP.MOTOR_RIGHT.OFFSET_R")?;
        let motor_left_direction_raw: f64 = conn.get("ESP32.READ.SETUP.MOTOR_LEFT.DIRECTION_R")?;
        let motor_right_direction_raw: f64 = conn.get("ESP32.READ.SETUP.MOTOR_RIGHT.DIRECTION_R")?;

        Ok(Esp32SetupMotors { 
            motor_left_offset: motor_left_offset_raw,
            motor_right_offset: motor_right_offset_raw,
            motor_left_direction: if motor_left_direction_raw == 1.0 {true} else {false} ,
            motor_right_direction: if motor_right_direction_raw == 1.0 {true} else {false},
        })
    }


    //=====================================================================================================
    fn GetEsp32SetupEncoders( context: &ContextGraphQL) -> FieldResult<Esp32SetupEncoders> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let encoder_left_direction_raw: f64 = conn.get("ESP32.READ.SETUP.ENCODER_LEFT.DIRECTION_R")?;
        let encoder_right_direction_raw: f64 = conn.get("ESP32.READ.SETUP.ENCODER_RIGHT.DIRECTION_R")?;

        Ok(Esp32SetupEncoders { 
            encoder_left_direction: if encoder_left_direction_raw == 1.0 {true} else {false},
            encoder_right_direction: if encoder_right_direction_raw == 1.0 {true} else {false},
        })
    }
    
    
    //=====================================================================================================
    fn GetEsp32SetupIMU( context: &ContextGraphQL) -> FieldResult<Esp32SetupIMU> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let invert_pitch_raw: f64 = conn.get("ESP32.READ.SETUP.IMU.INVERT_PITCH_R")?;
        let invert_roll_raw: f64 = conn.get("ESP32.READ.SETUP.IMU.INVERT_ROLL_R")?;
        let invert_yaw_raw: f64 = conn.get("ESP32.READ.SETUP.IMU.INVERT_YAW_R")?;
        let offset_pitch_raw: f64 = conn.get("ESP32.READ.SETUP.IMU.OFFSET_PITCH_R")?;

        Ok(Esp32SetupIMU { 
            invert_pitch: if invert_pitch_raw == 1.0 {true} else {false},
            invert_roll: if invert_roll_raw == 1.0 {true} else {false},
            invert_yaw: if invert_yaw_raw == 1.0 {true} else {false},
            offset_pitch: offset_pitch_raw,
        })
    }


    //=====================================================================================================
    fn GetEsp32SetupOdometry( context: &ContextGraphQL) -> FieldResult<Esp32SetupOdometry> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let wheel_radio_raw: f64 = conn.get("ESP32.READ.SETUP.ODOMETRY.DISTANCE_WHEELS_R")?;
        let distance_wheels_raw: f64 = conn.get("ESP32.READ.SETUP.ODOMETRY.WHEEL_RADIO_R")?;

        Ok(Esp32SetupOdometry { 
            wheel_radio: wheel_radio_raw,
            distance_wheels: distance_wheels_raw,
        })
    }

    
    //=====================================================================================================
    fn GetEsp32SetupMotionPidPitch( context: &ContextGraphQL) -> FieldResult<Esp32SetupMotionPID> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let kp_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.KP_R")?;
        let ki_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.KI_R")?;
        let kd_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.KD_R")?;
        let cycle_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.CYCLE_R")?;
        let direction_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.DIRECTION_R")?;
        let mv_min_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.MV_MIN_R")?;
        let mv_max_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.MV_MAX_R")?;

        Ok(Esp32SetupMotionPID { 
            kp: kp_raw,
            ki: ki_raw,
            kd: kd_raw,
            cycle: cycle_raw,
            direction: if direction_raw == 1.0 {true} else {false},
            mv_min: mv_min_raw,
            mv_max: mv_max_raw,
        })
    }

    
    //=====================================================================================================
    fn GetEsp32SetupMotionPidPosition( context: &ContextGraphQL) -> FieldResult<Esp32SetupMotionPID> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let kp_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.KP_R")?;
        let ki_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.KI_R")?;
        let kd_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.KD_R")?;
        let cycle_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.CYCLE_R")?;
        let direction_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.DIRECTION_R")?;
        let mv_min_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.MV_MIN_R")?;
        let mv_max_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.MV_MAX_R")?;

        Ok(Esp32SetupMotionPID { 
            kp: kp_raw,
            ki: ki_raw,
            kd: kd_raw,
            cycle: cycle_raw,
            direction: if direction_raw == 1.0 {true} else {false},
            mv_min: mv_min_raw,
            mv_max: mv_max_raw,
        })
    }

    
    //=====================================================================================================
    fn GetEsp32SetupMotionPidAngle( context: &ContextGraphQL) -> FieldResult<Esp32SetupMotionPID> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let kp_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.KP_R")?;
        let ki_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.KI_R")?;
        let kd_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.KD_R")?;
        let cycle_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.CYCLE_R")?;
        let direction_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.DIRECTION_R")?;
        let mv_min_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.MV_MIN_R")?;
        let mv_max_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.MV_MAX_R")?;

        Ok(Esp32SetupMotionPID { 
            kp: kp_raw,
            ki: ki_raw,
            kd: kd_raw,
            cycle: cycle_raw,
            direction: if direction_raw == 1.0 {true} else {false},
            mv_min: mv_min_raw,
            mv_max: mv_max_raw,
        })
    }

    //=====================================================================================================
    fn GetEsp32SetupMotionFalldownOffset( context: &ContextGraphQL) -> FieldResult<f64> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let offset: f64 = conn.get("ESP32.READ.SETUP.MOTION.FALLDOWN_OFFSET")?;

        Ok(offset)
    }


    //=====================================================================================================
    fn GetEsp32Setup( context: &ContextGraphQL) -> FieldResult<Esp32Setup> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let motor_left_offset_raw: f64 = conn.get("ESP32.READ.SETUP.MOTOR_LEFT.OFFSET_R")?;
        let motor_right_offset_raw: f64 = conn.get("ESP32.READ.SETUP.MOTOR_RIGHT.OFFSET_R")?;
        let motor_left_direction_raw: f64 = conn.get("ESP32.READ.SETUP.MOTOR_LEFT.DIRECTION_R")?;
        let motor_right_direction_raw: f64 = conn.get("ESP32.READ.SETUP.MOTOR_RIGHT.DIRECTION_R")?;

        let encoder_left_direction_raw: f64 = conn.get("ESP32.READ.SETUP.ENCODER_LEFT.DIRECTION_R")?;
        let encoder_right_direction_raw: f64 = conn.get("ESP32.READ.SETUP.ENCODER_RIGHT.DIRECTION_R")?;

        let invert_pitch_raw: f64 = conn.get("ESP32.READ.SETUP.IMU.INVERT_PITCH_R")?;
        let invert_roll_raw: f64 = conn.get("ESP32.READ.SETUP.IMU.INVERT_ROLL_R")?;
        let invert_yaw_raw: f64 = conn.get("ESP32.READ.SETUP.IMU.INVERT_YAW_R")?;
        let offset_pitch_raw: f64 = conn.get("ESP32.READ.SETUP.IMU.OFFSET_PITCH_R")?;

        let wheel_radio_raw: f64 = conn.get("ESP32.READ.SETUP.ODOMETRY.WHEEL_RADIO_R")?;
        let distance_wheels_raw: f64 = conn.get("ESP32.READ.SETUP.ODOMETRY.DISTANCE_WHEELS_R")?;

        let motion_pid_pitch_kp_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.KP_R")?;
        let motion_pid_pitch_ki_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.KI_R")?;
        let motion_pid_pitch_kd_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.KD_R")?;
        let motion_pid_pitch_cycle_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.CYCLE_R")?;
        let motion_pid_pitch_direction_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.DIRECTION_R")?;
        let motion_pid_pitch_mv_min_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.MV_MIN_R")?;
        let motion_pid_pitch_mv_max_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_PITCH.MV_MAX_R")?;

        let motion_pid_position_kp_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.KP_R")?;
        let motion_pid_position_ki_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.KI_R")?;
        let motion_pid_position_kd_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.KD_R")?;
        let motion_pid_position_cycle_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.CYCLE_R")?;
        let motion_pid_position_direction_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.DIRECTION_R")?;
        let motion_pid_position_mv_min_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.MV_MIN_R")?;
        let motion_pid_position_mv_max_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_POSITION.MV_MAX_R")?;

        let motion_pid_angle_kp_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.KP_R")?;
        let motion_pid_angle_ki_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.KI_R")?;
        let motion_pid_angle_kd_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.KD_R")?;
        let motion_pid_angle_cycle_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.CYCLE_R")?;
        let motion_pid_angle_direction_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.DIRECTION_R")?;
        let motion_pid_angle_mv_min_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.MV_MIN_R")?;
        let motion_pid_angle_mv_max_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.PID_ANGLE.MV_MAX_R")?;

        let motion_falldown_offset_raw: f64 = conn.get("ESP32.READ.SETUP.MOTION.FALLDOWN_OFFSET")?;

        Ok( Esp32Setup{
            motors: Esp32SetupMotors { 
                motor_left_offset: motor_left_offset_raw,
                motor_right_offset: motor_right_offset_raw,
                motor_left_direction: if motor_left_direction_raw == 1.0 {true} else {false},
                motor_right_direction: if motor_right_direction_raw == 1.0 {true} else {false},
            }, 
            encoders: Esp32SetupEncoders { 
                encoder_left_direction: if encoder_left_direction_raw == 1.0 {true} else {false},
                encoder_right_direction: if encoder_right_direction_raw == 1.0 {true} else {false},
            },
            imu: Esp32SetupIMU { 
                invert_pitch: if invert_pitch_raw == 1.0 {true} else {false},
                invert_roll: if invert_roll_raw == 1.0 {true} else {false},
                invert_yaw: if invert_yaw_raw == 1.0 {true} else {false},
                offset_pitch: offset_pitch_raw,
            },
            odometry: Esp32SetupOdometry { 
                wheel_radio: wheel_radio_raw,
                distance_wheels: distance_wheels_raw,
            },
            motion_pid_pitch: Esp32SetupMotionPID { 
                kp: motion_pid_pitch_kp_raw,
                ki: motion_pid_pitch_ki_raw,
                kd: motion_pid_pitch_kd_raw,
                cycle: motion_pid_pitch_cycle_raw,
                direction: if motion_pid_pitch_direction_raw == 1.0 {true} else {false},
                mv_min: motion_pid_pitch_mv_min_raw,
                mv_max: motion_pid_pitch_mv_max_raw,
            },
            motion_pid_position: Esp32SetupMotionPID { 
                kp: motion_pid_position_kp_raw,
                ki: motion_pid_position_ki_raw,
                kd: motion_pid_position_kd_raw,
                cycle: motion_pid_position_cycle_raw,
                direction: if motion_pid_position_direction_raw == 1.0 {true} else {false},
                mv_min: motion_pid_position_mv_min_raw,
                mv_max: motion_pid_position_mv_max_raw,
            },
            motion_pid_angle: Esp32SetupMotionPID { 
                kp: motion_pid_angle_kp_raw,
                ki: motion_pid_angle_ki_raw,
                kd: motion_pid_angle_kd_raw,
                cycle: motion_pid_angle_cycle_raw,
                direction: if motion_pid_angle_direction_raw == 1.0 {true} else {false},
                mv_min: motion_pid_angle_mv_min_raw,
                mv_max: motion_pid_angle_mv_max_raw,
            },
            motion_falldown_offset: motion_falldown_offset_raw,
        })
    }
    
    
    //=====================================================================================================
    fn GetEsp32LiveMotors( context: &ContextGraphQL) -> FieldResult<Esp32LiveMotors> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let motor_left_speed_raw: f64 = conn.get("ESP32.READ.LIVE.MOTOR_LEFT.SPEED_R")?;
        let motor_right_speed_raw: f64 = conn.get("ESP32.READ.LIVE.MOTOR_RIGHT.SPEED_R")?;

        Ok(Esp32LiveMotors { 
            motor_left_speed: motor_left_speed_raw,
            motor_right_speed: motor_right_speed_raw, 
        })
    }

    
    //=====================================================================================================
    fn GetEsp32LiveIMU( context: &ContextGraphQL) -> FieldResult<Esp32LiveIMU> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let pitch_raw: f64 = conn.get("ESP32.READ.LIVE.IMU.PITCH_R")?;
        let roll_raw: f64 = conn.get("ESP32.READ.LIVE.IMU.ROLL_R")?;
        let yaw_raw: f64 = conn.get("ESP32.READ.LIVE.IMU.YAW_R")?;

        Ok(Esp32LiveIMU { 
            pitch: pitch_raw,
            roll:roll_raw,
            yaw: yaw_raw, 
        })
    }

    
    //=====================================================================================================
    fn GetEsp32LiveEncoders( context: &ContextGraphQL) -> FieldResult<Esp32LiveEncoders> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let encoder_left_count_raw: f64 = conn.get("ESP32.READ.LIVE.ENCODER.LEFT_COUNT_R")?;
        let encoder_right_count_raw: f64 = conn.get("ESP32.READ.LIVE.ENCODER.RIGHT_COUNT_R")?;

        Ok(Esp32LiveEncoders { 
            encoder_left_count: encoder_left_count_raw,
            encoder_right_count: encoder_right_count_raw,
        })
    }

    
    //=====================================================================================================
    fn GetEsp32LiveOdometry( context: &ContextGraphQL) -> FieldResult<Esp32LiveOdometry> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let x_raw: f64 = conn.get("ESP32.READ.LIVE.ODOMETRY.X_R")?;
        let y_raw: f64 = conn.get("ESP32.READ.LIVE.ODOMETRY.Y_R")?;
        let angle_raw: f64 = conn.get("ESP32.READ.LIVE.ODOMETRY.ANGLE_R")?;
        let distance_raw: f64 = conn.get("ESP32.READ.LIVE.ODOMETRY.DISTANCE_R")?;

        Ok(Esp32LiveOdometry { 
            x: x_raw,
            y: y_raw,
            angle: angle_raw,
            distance: distance_raw,
        })
    }

    
    //=====================================================================================================
    fn GetEsp32LiveMotion( context: &ContextGraphQL) -> FieldResult<Esp32LiveMotion> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let setpoint_angle_raw: f64 = conn.get("ESP32.READ.LIVE.MOTION.SP_ANGLE_R")?;
        let setpoint_position_raw: f64 = conn.get("ESP32.READ.LIVE.MOTION.SP_POSITION_R")?;

        Ok(Esp32LiveMotion { 
            setpoint_angle: setpoint_angle_raw,
            setpoint_position: setpoint_position_raw,
        })
    }


    //=====================================================================================================
    async fn GetDbEsp32Setup(_context: &ContextGraphQL) -> FieldResult<Esp32Setup> {

        let mut setup: Esp32Setup = Esp32Setup{..Default::default()};

        let client = connect_postgres().await?;
        
        for row in client.query("SELECT * FROM SETUP_ESP32 ORDER BY name ASC", &[]).await? {
            let name: String = row.try_get("NAME")?;
            let value: f64 = row.try_get("VALUE")?;

            match name.as_str() {
                
                "motor_left_direction" => {
                    setup.motors.motor_left_direction = if value == 1.0 {true} else {false};
                },

                "motor_left_offset" => {
                    setup.motors.motor_left_offset = value;
                },

                "motor_right_direction" => {
                    setup.motors.motor_right_direction = if value == 1.0 {true} else {false};
                },

                "motor_right_offset" => {
                    setup.motors.motor_right_offset = value;
                },

                "encoder_left_direction" => {
                    setup.encoders.encoder_left_direction = if value == 1.0 {true} else {false};
                },

                "encoder_right_direction" => {
                    setup.encoders.encoder_right_direction = if value == 1.0 {true} else {false};
                },

                "imu_invert_pitch" => {
                    setup.imu.invert_pitch = if value == 1.0 {true} else {false};
                },

                "imu_invert_roll" => {
                    setup.imu.invert_roll = if value == 1.0 {true} else {false};
                },

                "imu_invert_yaw" => {
                    setup.imu.invert_yaw = if value == 1.0 {true} else {false};
                },

                "imu_offset_pitch" => {
                    setup.imu.offset_pitch = value;
                },

                "odometry_distance_wheels" => {
                    setup.odometry.distance_wheels = value;
                },

                "odometry_wheel_radio" => {
                    setup.odometry.wheel_radio = value;
                },

                "motion_pid_pitch_kp" => {
                    setup.motion_pid_pitch.kp = value;
                },

                "motion_pid_pitch_ki" => {
                    setup.motion_pid_pitch.ki = value;
                },

                "motion_pid_pitch_kd" => {
                    setup.motion_pid_pitch.kd = value;
                },

                "motion_pid_pitch_direction" => {
                    setup.motion_pid_pitch.direction = if value == 1.0 {true} else {false};
                },

                "motion_pid_pitch_mv_min" => {
                    setup.motion_pid_pitch.mv_min = value;
                },

                "motion_pid_pitch_mv_max" => {
                    setup.motion_pid_pitch.mv_max = value;
                },

                "motion_pid_position_kp" => {
                    setup.motion_pid_position.kp = value;
                },

                "motion_pid_position_ki" => {
                    setup.motion_pid_position.ki = value;
                },

                "motion_pid_position_kd" => {
                    setup.motion_pid_position.kd = value;
                },

                "motion_pid_position_direction" => {
                    setup.motion_pid_position.direction = if value == 1.0 {true} else {false};
                },

                "motion_pid_position_mv_min" => {
                    setup.motion_pid_position.mv_min = value;
                },

                "motion_pid_position_mv_max" => {
                    setup.motion_pid_position.mv_max = value;
                },

                "motion_pid_angle_kp" => {
                    setup.motion_pid_angle.kp = value;
                },

                "motion_pid_angle_ki" => {
                    setup.motion_pid_angle.ki = value;
                },

                "motion_pid_angle_kd" => {
                    setup.motion_pid_angle.kd = value;
                },

                "motion_pid_angle_direction" => {
                    setup.motion_pid_angle.direction = if value == 1.0 {true} else {false};
                },

                "motion_pid_angle_mv_min" => {
                    setup.motion_pid_angle.mv_min = value;
                },

                "motion_pid_angle_mv_max" => {
                    setup.motion_pid_angle.mv_max = value;
                },

                "motion_falldown_offset" => {
                    setup.motion_falldown_offset = value;
                },

                _ => {}
            }
        }

        Ok(setup)
    }


     //=====================================================================================================
     fn GetRobotStatus(context: &ContextGraphQL, endpoint: String, status: String) -> FieldResult<String> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");
        let key: String = format!("{}.{}", endpoint, status);
        let value: String = conn.get(key)?;

        Ok(value)
    }

}
