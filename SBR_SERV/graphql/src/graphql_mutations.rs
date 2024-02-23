use juniper::{graphql_object, FieldResult};
use r2d2_redis::redis::Commands;
use crate::graphql_context::ContextGraphQL;
use crate::graphql_types::{RegisterCommand, Esp32SetupInput};
use crate::rabbitmq_connection::{publish_esp32_write, publish_host_connector, publish_command};
use crate::postgres_connection::connect_postgres;
use crate::type_command::Command;


//=====================================================================================================
pub struct Mutations;


//=====================================================================================================
// ESP32
#[graphql_object(Context = ContextGraphQL)]
impl Mutations {

    //=====================================================================================================
    fn SetEsp32ModeManagerRestart(_context: &ContextGraphQL) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.MANAGER.RESTART_W".to_string(), 1.0)?;
            
        Ok(true)
    }

    
    //=====================================================================================================
    fn SetEsp32ModeManagerProgram(_context: &ContextGraphQL) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.MANAGER.PROGRAM_W".to_string(), 1.0)?;
            
        Ok(true)
    }

    
    //=====================================================================================================
    fn SetEsp32ModeManagerSyncData(_context: &ContextGraphQL, sync_status: RegisterCommand) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.MANAGER.SYNC_DATA_RW".to_string(), (sync_status as i32) as f64)?;

        Ok(true)
    }
    
    
    //=====================================================================================================
    fn SetEsp32ModeLinuxSyncData(_context: &ContextGraphQL, sync_status: RegisterCommand) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.LINUX.SYNC_DATA_RW".to_string(), (sync_status as i32) as f64)?;

        Ok(true)
    }

    
    //=====================================================================================================
    fn SetEsp32ModeNode1Restart(_context: &ContextGraphQL) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.NODE1.RESTART_W".to_string(), 1.0)?;
            
        Ok(true)
    }
    
    
    //=====================================================================================================
    fn SetEsp32ModeNode1Program(_context: &ContextGraphQL) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.NODE1.PROGRAM_W".to_string(), 1.0)?;
            
        Ok(true)
    }
    
    
    //=====================================================================================================
    fn SetEsp32ModeNode1SyncData(_context: &ContextGraphQL, sync_status: RegisterCommand) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.NODE1.SYNC_DATA_RW".to_string(), (sync_status as i32) as f64)?;

        Ok(true)
    }
    
    
    //=====================================================================================================
    fn SetEsp32ModeNode1Start(_context: &ContextGraphQL) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.NODE1.START_W".to_string(), 1.0)?;
            
        Ok(true)
    }
    
    
    //=====================================================================================================
    fn SetEsp32ModeNode1Stop(_context: &ContextGraphQL) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE_NODE1.STOP_W".to_string(), 1.0)?;
            
        Ok(true)
    }
    

    //=====================================================================================================
    fn SetEsp32Setup(_context: &ContextGraphQL, setup: Esp32SetupInput) -> FieldResult<bool> {

        match setup.motor_left_offset {
            Some(offset) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTOR_LEFT.OFFSET_W".to_string(), offset)?;},
            None =>{}
        };

        match setup.motor_left_direction {
            Some(direction) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTOR_LEFT.DIRECTION_W".to_string(), (direction as i32) as f64)?;},
            None =>{}
        };

        match setup.motor_right_offset {
            Some(offset) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTOR_RIGHT.OFFSET_W".to_string(), offset)?;},
            None =>{}
        };

        match setup.motor_right_direction {
            Some(direction) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTOR_RIGHT.DIRECTION_W".to_string(), (direction as i32) as f64)?;},
            None =>{}
        };

        match setup.encoder_left_direction {
            Some(direction) => {publish_esp32_write("ESP32.WRITE.SETUP.ENCODER_LEFT.DIRECTION_W".to_string(), (direction as i32) as f64)?;},
            None =>{}
        };

        match setup.encoder_left_direction {
            Some(direction) => {publish_esp32_write("ESP32.WRITE.SETUP.ENCODER_RIGHT.DIRECTION_W".to_string(), (direction as i32) as f64)?;},
            None =>{}
        };

        match setup.imu_invert_pitch {
            Some(direction) => {publish_esp32_write("ESP32.WRITE.SETUP.IMU.INVERT_PITCH_W".to_string(), (direction as i32) as f64)?;},
            None =>{}
        };

        match setup.imu_invert_roll {
            Some(direction) => {publish_esp32_write("ESP32.WRITE.SETUP.IMU.INVERT_ROLL_W".to_string(), (direction as i32) as f64)?;},
            None =>{}
        };

        match setup.imu_invert_yaw {
            Some(direction) => {publish_esp32_write("ESP32.WRITE.SETUP.IMU.INVERT_YAW_W".to_string(), (direction as i32) as f64)?;},
            None =>{}
        };

        match setup.imu_offset_pitch {
            Some(offset) => {publish_esp32_write("ESP32.WRITE.SETUP.IMU.OFFSET_PITCH_W".to_string(), offset)?;},
            None =>{}
        };

        match setup.odometry_wheel_radio {
            Some(wheel_radio) => {publish_esp32_write("ESP32.WRITE.SETUP.ODOMETRY.WHEEL_RADIO_W".to_string(), wheel_radio)?;},
            None =>{}
        };

        match setup.odometry_distance_wheels {
            Some(distance_wheels) => {publish_esp32_write("ESP32.WRITE.SETUP.ODOMETRY.DISTANCE_WHEELS_W".to_string(), distance_wheels)?;},
            None =>{}
        };
 
        match setup.motion_pid_pitch_kp {
            Some(kp) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_PITCH.KP_W".to_string(), kp)?;},
            None =>{}
        };

        match setup.motion_pid_pitch_ki {
            Some(ki) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_PITCH.KI_W".to_string(), ki)?;},
            None =>{}
        };

        match setup.motion_pid_pitch_kd {
            Some(kd) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_PITCH.KD_W".to_string(), kd)?;},
            None =>{}
        };

        match setup.motion_pid_pitch_direction {
            Some(direction) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_PITCH.DIRECTION_W".to_string(), (direction as i32) as f64)?;},
            None =>{}
        };

        match setup.motion_pid_pitch_mv_min {
            Some(mv_min) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_PITCH.MV_MIN_W".to_string(), mv_min)?;},
            None =>{}
        };

        match setup.motion_pid_pitch_mv_max {
            Some(mv_max) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_PITCH.MV_MAX_W".to_string(), mv_max)?;},
            None =>{}
        };


        match setup.motion_pid_position_kp {
            Some(kp) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_POSITION.KP_W".to_string(), kp)?;},
            None =>{}
        };

        match setup.motion_pid_position_ki {
            Some(ki) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_POSITION.KI_W".to_string(), ki)?;},
            None =>{}
        };

        match setup.motion_pid_position_kd {
            Some(kd) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_POSITION.KD_W".to_string(), kd)?;},
            None =>{}
        };

        match setup.motion_pid_position_direction {
            Some(direction) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_POSITION.DIRECTION_W".to_string(), (direction as i32) as f64)?;},
            None =>{}
        };

        match setup.motion_pid_position_mv_min {
            Some(mv_min) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_POSITION.MV_MIN_W".to_string(), mv_min)?;},
            None =>{}
        };

        match setup.motion_pid_position_mv_max {
            Some(mv_max) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_POSITION.MV_MAX_W".to_string(), mv_max)?;},
            None =>{}
        };

        match setup.motion_pid_angle_kp {
            Some(kp) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_ANGLE.KP_W".to_string(), kp)?;},
            None =>{}
        };

        match setup.motion_pid_angle_ki {
            Some(ki) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_ANGLE.KI_W".to_string(), ki)?;},
            None =>{}
        };

        match setup.motion_pid_angle_kd {
            Some(kd) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_ANGLE.KD_W".to_string(), kd)?;},
            None =>{}
        };

        match setup.motion_pid_angle_direction {
            Some(direction) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_ANGLE.DIRECTION_W".to_string(), (direction as i32) as f64)?;},
            None =>{}
        };

        match setup.motion_pid_angle_mv_min {
            Some(mv_min) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_ANGLE.MV_MIN_W".to_string(), mv_min)?;},
            None =>{}
        };

        match setup.motion_pid_angle_mv_max {
            Some(mv_max) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_ANGLE.MV_MAX_W".to_string(), mv_max)?;},
            None =>{}
        };

        match setup.motion_falldown_offset {
            Some(offset) => {publish_esp32_write("ESP32.WRITE.SETUP.MOTION.FALLDOWN_OFFSET_W".to_string(), offset)?;},
            None =>{}
        };


        Ok(true)
    }

    
    //=====================================================================================================
    async fn SetDbEsp32Setup(_context: &ContextGraphQL, setup: Esp32SetupInput) -> FieldResult<bool> {

        let client = connect_postgres().await?;


        match setup.motor_left_offset {
            Some(offset) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motor_left_offset'", &[&offset]).await?;
            },
            None =>{}
        };

        match setup.motor_left_direction {
            Some(direction) => {
                let data:f64 = if direction == true {1.0} else {0.0};
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motor_left_direction'", &[&data]).await?;
            },
            None =>{}
        };

        match setup.motor_right_offset {
            Some(offset) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motor_right_offset'", &[&offset]).await?;
            },
            None =>{}
        };

        match setup.motor_right_direction {
            Some(direction) => {
                let data:f64 = if direction == true {1.0} else {0.0};
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motor_right_direction'", &[&data]).await?;
            },
            None =>{}
        };

        match setup.encoder_left_direction {
            Some(direction) => {
                let data:f64 = if direction == true {1.0} else {0.0};
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='encoder_left_direction'", &[&data]).await?;
            },
            None =>{}
        };

        match setup.encoder_left_direction {
            Some(direction) => {
                let data:f64 = if direction == true {1.0} else {0.0};
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='encoder_right_direction'", &[&data]).await?;
            },
            None =>{}
        };

        match setup.imu_invert_pitch {
            Some(direction) => {
                let data:f64 = if direction == true {1.0} else {0.0};
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='imu_invert_pitch'", &[&data]).await?;
            },
            None =>{}
        };

        match setup.imu_invert_roll {
            Some(direction) => {
                let data:f64 = if direction == true {1.0} else {0.0};
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='imu_invert_roll'", &[&data]).await?;
            },
            None =>{}
        };

        match setup.imu_invert_yaw {
            Some(direction) => {
                let data:f64 = if direction == true {1.0} else {0.0};
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='imu_invert_yaw'", &[&data]).await?;
            },
            None =>{}
        };

        match setup.imu_offset_pitch {
            Some(offset) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='imu_offset_pitch'", &[&offset]).await?;
            },
            None =>{}
        };

        match setup.odometry_wheel_radio {
            Some(wheel_radio) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='odometry_wheel_radio'", &[&wheel_radio]).await?;
            },
            None =>{}
        };

        match setup.odometry_distance_wheels {
            Some(distance_wheels) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='odometry_distance_wheels'", &[&distance_wheels]).await?;
            },
            None =>{}
        };

        match setup.motion_pid_pitch_kp {
            Some(kp) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_pid_pitch_kp'", &[&kp]).await?;
            },
            None =>{}
        };

        match setup.motion_pid_pitch_ki {
            Some(ki) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_pid_pitch_ki'", &[&ki]).await?;
            },
            None =>{}
        };

        match setup.motion_pid_pitch_kd {
            Some(kd) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_pid_pitch_kd'", &[&kd]).await?;
            },
            None =>{}
        };

        match setup.motion_pid_pitch_direction {
            Some(direction) => {
                let data:f64 = if direction == true {1.0} else {0.0};
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_pid_pitch_direction'", &[&data]).await?;
            },
            None =>{}
        };

        match setup.motion_pid_pitch_mv_min {
            Some(mv_min) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_pid_pitch_mv_min'", &[&mv_min]).await?;
            },
            None =>{}
        };

        match setup.motion_pid_pitch_mv_max {
            Some(mv_max) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_pid_pitch_mv_max'", &[&mv_max]).await?;
            },
            None =>{}
        };

        match setup.motion_pid_position_kp {
            Some(kp) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_pid_position_kp'", &[&kp]).await?;
            },
            None =>{}
        };

        match setup.motion_pid_position_ki {
            Some(ki) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_pid_position_ki'", &[&ki]).await?;
            },
            None =>{}
        };

        match setup.motion_pid_position_kd {
            Some(kd) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_pid_position_kd'", &[&kd]).await?;
            },
            None =>{}
        };

        match setup.motion_pid_position_direction {
            Some(direction) => {
                let data:f64 = if direction == true {1.0} else {0.0};
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_pid_position_direction'", &[&data]).await?;
            },
            None =>{}
        };

        match setup.motion_pid_position_mv_min {
            Some(mv_min) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_pid_position_mv_min'", &[&mv_min]).await?;
            },
            None =>{}
        };

        match setup.motion_pid_position_mv_max {
            Some(mv_max) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_pid_position_mv_max'", &[&mv_max]).await?;
            },
            None =>{}
        };

        match setup.motion_pid_angle_kp {
            Some(kp) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_pid_angle_kp'", &[&kp]).await?;
            },
            None =>{}
        };

        match setup.motion_pid_angle_ki {
            Some(ki) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_pid_angle_ki'", &[&ki]).await?;
            },
            None =>{}
        };

        match setup.motion_pid_angle_kd {
            Some(kd) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_pid_angle_kd'", &[&kd]).await?;
            },
            None =>{}
        };

        match setup.motion_pid_angle_direction {
            Some(direction) => {
                let data:f64 = if direction == true {1.0} else {0.0};
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_pid_angle_direction'", &[&data]).await?;
            },
            None =>{}
        };

        match setup.motion_pid_angle_mv_min {
            Some(mv_min) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_pid_angle_mv_min'", &[&mv_min]).await?;
            },
            None =>{}
        };

        match setup.motion_pid_angle_mv_max {
            Some(mv_max) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_pid_angle_mv_max'", &[&mv_max]).await?;
            },
            None =>{}
        };

        match setup.motion_falldown_offset {
            Some(offset) => {
                client.execute("UPDATE SETUP_ESP32 SET VALUE=$1 WHERE NAME='motion_falldown_offset'", &[&offset]).await?;
            },
            None =>{}
        };


        Ok(true)
    }


    //=====================================================================================================
    async fn LoadEsp32Setup(_context: &ContextGraphQL) -> FieldResult<bool> {

        let client = connect_postgres().await?;
        
        for row in client.query("SELECT * FROM SETUP_ESP32 ORDER BY name ASC", &[]).await? {
            let name: String = row.try_get("NAME")?;
            let value: f64 = row.try_get("VALUE")?;

            match name.as_str() {
                "motor_left_direction" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTOR_LEFT.DIRECTION_W".to_string(), value)?;
                },

                "motor_left_offset" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTOR_LEFT.OFFSET_W".to_string(), value)?;
                },

                "motor_right_direction" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTOR_RIGHT.DIRECTION_W".to_string(), value)?;
                },

                "motor_right_offset" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTOR_RIGHT.OFFSET_W".to_string(), value)?;
                },

                "encoder_left_direction" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.ENCODER_LEFT.DIRECTION_W".to_string(), value)?;
                },

                "encoder_right_direction" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.ENCODER_RIGHT.DIRECTION_W".to_string(), value)?;
                },

                "imu_invert_pitch" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.IMU.INVERT_PITCH_W".to_string(), value)?;
                },

                "imu_invert_roll" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.IMU.INVERT_ROLL_W".to_string(), value)?;
                },

                "imu_invert_yaw" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.IMU.INVERT_YAW_W".to_string(), value)?;
                },

                "imu_offset_pitch" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.IMU.OFFSET_PITCH_W".to_string(), value)?;
                },

                "odometry_distance_wheels" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.ODOMETRY.DISTANCE_WHEELS_W".to_string(), value)?;
                },

                "odometry_wheel_radio" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.ODOMETRY.WHEEL_RADIO_W".to_string(), value)?;
                },

                "motion_pid_pitch_kp" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_PITCH.KP_W".to_string(), value)?;
                },

                "motion_pid_pitch_ki" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_PITCH.KI_W".to_string(), value)?;
                },

                "motion_pid_pitch_kd" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_PITCH.KD_W".to_string(), value)?;
                },

                "motion_pid_pitch_direction" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_PITCH.DIRECTION_W".to_string(), value)?;
                },

                "motion_pid_pitch_mv_min" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_PITCH.MV_MIN_W".to_string(), value)?;
                },

                "motion_pid_pitch_mv_max" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_PITCH.MV_MAX_W".to_string(), value)?;
                },

                "motion_pid_position_kp" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_POSITION.KP_W".to_string(), value)?;
                },

                "motion_pid_position_ki" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_POSITION.KI_W".to_string(), value)?;
                },

                "motion_pid_position_kd" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_POSITION.KD_W".to_string(), value)?;
                },

                "motion_pid_position_direction" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_POSITION.DIRECTION_W".to_string(), value)?;
                },

                "motion_pid_position_mv_min" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_POSITION.MV_MIN_W".to_string(), value)?;
                },

                "motion_pid_position_mv_max" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_POSITION.MV_MAX_W".to_string(), value)?;
                },

                "motion_pid_angle_kp" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_ANGLE.KP_W".to_string(), value)?;
                },

                "motion_pid_angle_ki" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_ANGLE.KI_W".to_string(), value)?;
                },

                "motion_pid_angle_kd" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_ANGLE.KD_W".to_string(), value)?;
                },

                "motion_pid_angle_direction" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_ANGLE.DIRECTION_W".to_string(), value)?;
                },

                "motion_pid_angle_mv_min" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_ANGLE.MV_MIN_W".to_string(), value)?;
                },

                "motion_pid_angle_mv_max" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_ANGLE.MV_MAX_W".to_string(), value)?;
                },

                "motion_falldown_offset" => {
                    publish_esp32_write("ESP32.WRITE.SETUP.MOTION.FALLDOWN_OFFSET_W".to_string(), value)?;
                },

                _ => {}
            }
        }

        Ok(true)
    }
    

    //=====================================================================================================
    fn SetEsp32LiveMotorsSpeed(_context: &ContextGraphQL, new_motor_left_speed: Option<f64>, new_motor_right_speed: Option<f64>) -> FieldResult<bool> {

        match new_motor_left_speed {
            Some(speed) => {
                publish_esp32_write("ESP32.WRITE.LIVE.MOTOR_LEFT.SPEED_W".to_string(), speed)?;
            }, 
            None =>{ }
        }

        match new_motor_right_speed {
            Some(speed) => {
                publish_esp32_write("ESP32.WRITE.LIVE.MOTOR_RIGHT.SPEED_W".to_string(), speed)?;
            }, 
            None =>{ }
        }

        Ok(true)
    }
        
    
    //=====================================================================================================
    fn SetEsp32LiveOdometryX(_context: &ContextGraphQL, new_x: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.LIVE.ODOMETRY.X_W".to_string(), new_x)?;

        Ok(true)
    }
    
    
    //=====================================================================================================
    fn SetEsp32LiveOdometryY(_context: &ContextGraphQL, new_y: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.LIVE.ODOMETRY.Y_W".to_string(), new_y)?;

        Ok(true)
    }
    
    
    //=====================================================================================================
    fn SetEsp32LiveOdometryAngle(_context: &ContextGraphQL, new_angle: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.LIVE.ODOMETRY.ANGLE_W".to_string(), new_angle)?;
        
        Ok(true)
    }
    
    
    //=====================================================================================================
    fn SetEsp32LiveOdometryDistance(_context: &ContextGraphQL, new_distance: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.LIVE.ODOMETRY.DISTANCE_W".to_string(), new_distance)?;

        Ok(true)
    }
    
    
    //=====================================================================================================
    fn SetEsp32LiveOdometryReset(_context: &ContextGraphQL) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.LIVE.ODOMETRY.RESET_W".to_string(), 1.0)?;

        Ok(true)
    }
    
    
    //=====================================================================================================
    fn SetEsp32LiveMotionSpPosition(_context: &ContextGraphQL, sp: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.LIVE.MOTION.SP_POSITION_W".to_string(), sp)?;

        Ok(true)
    }
    
    
    //=====================================================================================================
    fn SetEsp32LiveMotionSpAngle(_context: &ContextGraphQL, sp: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.LIVE.MOTION.SP_ANGLE_W".to_string(), sp)?;

        Ok(true)
    }


    //=====================================================================================================
    fn SendHostRequest(_context: &ContextGraphQL, host: String, request: String) -> FieldResult<bool> {

        publish_host_connector(host, request)?;

        Ok(true)
    }


    //=====================================================================================================
    fn SendCommandBool(_context: &ContextGraphQL, endpoint: String, name: String, value: bool) -> FieldResult<bool> {

        let cmd = Command {
            name: name,
            value_bool: value,
            value_int: 0,
            value_float: 0.0,
            value_string: "".to_string(),
        };
        
        publish_command(endpoint, cmd)?;
            
        Ok(true)
    }


    //=====================================================================================================
    fn SendCommandInt(_context: &ContextGraphQL, endpoint: String, name: String, value: i32) -> FieldResult<bool> {

        let cmd = Command {
            name: name,
            value_bool: false,
            value_int: value,
            value_float: 0.0,
            value_string: "".to_string(),
        };
        
        publish_command(endpoint, cmd)?;
            
        Ok(true)
    }


    //=====================================================================================================
    fn SendCommandFloat(_context: &ContextGraphQL, endpoint: String, name: String, value: f64) -> FieldResult<bool> {

        let cmd = Command {
            name: name,
            value_bool: false,
            value_int: 0,
            value_float: value,
            value_string: "".to_string(),
        };
        
        publish_command(endpoint, cmd)?;
            
        Ok(true)
    }


    //=====================================================================================================
    fn SendCommandString(_context: &ContextGraphQL, endpoint: String, name: String, value: String) -> FieldResult<bool> {

        let cmd = Command {
            name: name,
            value_bool: false,
            value_int: 0,
            value_float: 0.0,
            value_string: value,
        };
        
        publish_command(endpoint, cmd)?;
            
        Ok(true)
    }


    //=====================================================================================================
    fn SetRobotStatus(context: &ContextGraphQL, endpoint: String, status: String, value: String) -> FieldResult<bool> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");
        let key: String = format!("{}.{}", endpoint, status);
        conn.set(key, value)?;

        Ok(true)
    }
    
}
