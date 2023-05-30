
use juniper::{graphql_object, FieldResult};
use crate::graphql_context::ContextGraphQL;
use crate::graphql_types::Esp32LiveMotors;
use crate::rabbitmq_connection::publish_esp32_write;

pub struct Mutations;

#[graphql_object(Context = ContextGraphQL)]
impl Mutations {

    fn SetEsp32ModeManagerRestart(_context: &ContextGraphQL) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.MANAGER.RESTART_W".to_string(), 1)?;
            
        Ok(true)
    }


    fn SetEsp32ModeManagerProgram(_context: &ContextGraphQL) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.MANAGER.PROGRAM_W".to_string(), 1)?;
            
        Ok(true)
    }


    fn SetEsp32ModeManagerSyncData(_context: &ContextGraphQL, sync_status: i32) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.MANAGER.SYNC_DATA_RW".to_string(), sync_status)?;

        Ok(true)
    }
    
    
    fn SetEsp32ModeLinuxSyncData(_context: &ContextGraphQL, sync_status: i32) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.LINUX.SYNC_DATA_RW".to_string(), sync_status)?;

        Ok(true)
    }


    fn SetEsp32ModeNode1Restart(_context: &ContextGraphQL) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.NODE1.RESTART_W".to_string(), 1)?;
            
        Ok(true)
    }
    
    
    fn SetEsp32ModeNode1Program(_context: &ContextGraphQL) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.NODE1.PROGRAM_W".to_string(), 1)?;
            
        Ok(true)
    }
    
    
    fn SetEsp32ModeNode1SyncData(_context: &ContextGraphQL, sync_status: i32) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.NODE1.SYNC_DATA_RW".to_string(), sync_status)?;

        Ok(true)
    }
    
    
    fn SetEsp32ModeNode1Start(_context: &ContextGraphQL) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.NODE1.START_W".to_string(), 1)?;
            
        Ok(true)
    }
    
    
    fn SetEsp32ModeNode1Stop(_context: &ContextGraphQL) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE_NODE1.STOP_W".to_string(), 1)?;
            
        Ok(true)
    }
    
    
    fn SetEsp32SetupMotorLeftOffset(_context: &ContextGraphQL, offset: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTOR.LEFT_OFFSET_W".to_string(), (offset * 100.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotorLeftDirection(_context: &ContextGraphQL, direction: bool) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTOR.LEFT_DIRECTION_W".to_string(), direction as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotorRightOffset(_context: &ContextGraphQL, offset: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTOR.RIGHT_OFFSET_W".to_string(), (offset * 100.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotorRightDirection(_context: &ContextGraphQL, direction: bool) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTOR.RIGHT_DIRECTION_W".to_string(), direction as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupIMUInvertPitch(_context: &ContextGraphQL, direction: bool) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.IMU.INVERT_PITCH_W".to_string(), direction as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupIMUInvertRoll(_context: &ContextGraphQL, direction: bool) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.IMU.INVERT_ROLL_W".to_string(), direction as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupIMUInvertYaw(_context: &ContextGraphQL, direction: bool) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.IMU.INVERT_YAW_W".to_string(), direction as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupIMUPitchOffset(_context: &ContextGraphQL, offset: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.IMU.OFFSET_PITCH_W".to_string(), (offset * 100.0) as i32)?;

        Ok(true)
    }

    
    fn SetEsp32SetupEncoderLeftDirection(_context: &ContextGraphQL, direction: bool) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.ENCODER_LEFT.DIRECTION_W".to_string(), direction as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupEncoderRightDirection(_context: &ContextGraphQL, direction: bool) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.ENCODER_RIGHT.DIRECTION_W".to_string(), direction as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupOdometryWheelRadio(_context: &ContextGraphQL, wheel_radio: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.ODOMETRY.WHEEL_RADIO_W".to_string(), (wheel_radio * 1000.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupOdometryDistanceWheels(_context: &ContextGraphQL, distance_wheels: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.ODOMETRY.DISTANCE_WHEELS_W".to_string(), (distance_wheels * 1000.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotionPidPitchKp(_context: &ContextGraphQL, kp: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_PITCH.KP_W".to_string(), (kp * 1000.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotionPidPitchKi(_context: &ContextGraphQL, ki: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_PITCH.KI_W".to_string(), (ki * 1000.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotionPidPitchKd(_context: &ContextGraphQL, kd: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_PITCH.KD_W".to_string(), (kd * 1000.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotionPidPitchDirection(_context: &ContextGraphQL, direction: bool) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_PITCH.DIRECTION_W".to_string(), direction as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotionPidPitchMVMin(_context: &ContextGraphQL, mv_min: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_PITCH.MV_MIN_W".to_string(), (mv_min * 100.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotionPidPitchMVMax(_context: &ContextGraphQL, mv_max: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_PITCH.MV_MAX_W".to_string(), (mv_max * 100.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotionPidPositionKp(_context: &ContextGraphQL, kp: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_POSITION.KP_W".to_string(), (kp * 1000.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotionPidPositionKi(_context: &ContextGraphQL, ki: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_POSITION.KI_W".to_string(), (ki * 1000.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotionPidPositionKd(_context: &ContextGraphQL, kd: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_POSITION.KD_W".to_string(), (kd * 1000.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotionPidPositionDirection(_context: &ContextGraphQL, direction: bool) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_POSITION.DIRECTION_W".to_string(), direction as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotionPidPositionMVMin(_context: &ContextGraphQL, mv_min: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_POSITION.MV_MIN_W".to_string(), (mv_min * 100.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotionPidPositionMVMax(_context: &ContextGraphQL, mv_max: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_POSITION.MV_MAX_W".to_string(), (mv_max * 100.0) as i32)?;

        Ok(true)
    }
    
    
    //
    
    fn SetEsp32SetupMotionPidAngleKp(_context: &ContextGraphQL, kp: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_ANGLE.KP_W".to_string(), (kp * 1000.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotionPidAngleKi(_context: &ContextGraphQL, ki: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_ANGLE.KI_W".to_string(), (ki * 1000.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotionPidAngleKd(_context: &ContextGraphQL, kd: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_ANGLE.KD_W".to_string(), (kd * 1000.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotionPidAngleDirection(_context: &ContextGraphQL, direction: bool) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_ANGLE.DIRECTION_W".to_string(), direction as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotionPidAngleMVMin(_context: &ContextGraphQL, mv_min: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_ANGLE.MV_MIN_W".to_string(), (mv_min * 100.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32SetupMotionPidAngleMVMax(_context: &ContextGraphQL, mv_max: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.SETUP.MOTION.PID_ANGLE.MV_MAX_W".to_string(), (mv_max * 100.0) as i32)?;

        Ok(true)
    }
    

    fn SetEsp32LiveMotorsSpeed(_context: &ContextGraphQL, new_motor_left_speed: Option<f64>, new_motor_right_speed: Option<f64>) -> FieldResult<bool> {

        match new_motor_left_speed {
            Some(speed) => {
                publish_esp32_write("ESP32.WRITE.LIVE.MOTOR_LEFT.SPEED_W".to_string(), (speed * 100.0) as i32)?;
            }, 
            None =>{ }
        }

        match new_motor_right_speed {
            Some(speed) => {
                publish_esp32_write("ESP32.WRITE.LIVE.MOTOR_RIGHT.SPEED_W".to_string(), (speed * 100.0) as i32)?;
            }, 
            None =>{ }
        }

        Ok(true)
    }
        
    
    fn SetEsp32LiveOdometryX(_context: &ContextGraphQL, new_x: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.LIVE.ODOMETRY.X_W".to_string(), (new_x * 1000.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32LiveOdometryY(_context: &ContextGraphQL, new_y: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.LIVE.ODOMETRY.Y_W".to_string(), (new_y * 1000.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32LiveOdometryX(_context: &ContextGraphQL, new_angle: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.LIVE.ODOMETRY.ANGLE_W".to_string(), (new_angle * 100.0) as i32)?;
        
        Ok(true)
    }
    
    
    fn SetEsp32LiveOdometryDistance(_context: &ContextGraphQL, new_distance: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.LIVE.ODOMETRY.DISTANCE_W".to_string(), (new_distance * 1000.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32LiveOdometryReset(_context: &ContextGraphQL) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.LIVE.ODOMETRY.RESET_W".to_string(), 1)?;

        Ok(true)
    }
    
    
    fn SetEsp32LiveMotionSpPosition(_context: &ContextGraphQL, sp: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.LIVE.MOTION.SP_POSITION_W".to_string(), (sp * 1000.0) as i32)?;

        Ok(true)
    }
    
    
    fn SetEsp32LiveMotionSpAngle(_context: &ContextGraphQL, sp: f64) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.LIVE.MOTION.SP_ANGLE_W".to_string(), (sp * 100.0) as i32)?;

        Ok(true)
    }

}