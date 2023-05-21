
use juniper::{graphql_object, FieldResult};
use crate::graphql_context::ContextGraphQL;
use crate::graphql_types::{Esp32LiveMotors, Esp32Status, Esp32Mode, Esp32SetupMotor, Esp32SetupIMU, Esp32SetupEncoders};
use r2d2_redis::redis::Commands;

pub struct Queries;


#[graphql_object(context = ContextGraphQL)]
impl Queries {

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


    fn GetEsp32Mode( context: &ContextGraphQL) -> FieldResult<Esp32Mode> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let manager_sync_data_raw: i32 = conn.get("ESP32.READ.MODE.MANAGER.SYNC_DATA_RW")?;
        let linux_sync_data_raw: i32 = conn.get("ESP32.READ.MODE.LINUX.SYNC_DATA_RW")?;

        Ok(Esp32Mode { 
            manager_sync_data: manager_sync_data_raw,
            linux_sync_data: linux_sync_data_raw,
        })
    }


    fn GetEsp32SetupMotors( context: &ContextGraphQL) -> FieldResult<Esp32SetupMotor> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let motor_left_offset_raw: i32 = conn.get("ESP32.READ.SETUP.MOTOR_LEFT.OFFSET_R")?;
        let motor_right_offset_raw: i32 = conn.get("ESP32.READ.SETUP.MOTOR_RIGHT.OFFSET_R")?;
        let motor_left_direction_raw: bool = conn.get("ESP32.READ.SETUP.MOTOR_LEFT.DIRECTION_R")?;
        let motor_right_direction_raw: bool = conn.get("ESP32.READ.SETUP.MOTOR_RIGHT.DIRECTION_R")?;

        Ok(Esp32SetupMotor { 
            motor_left_offset: (motor_left_offset_raw as f64) / 100.0,
            motor_right_offset: (motor_right_offset_raw as f64) / 100.0,
            motor_left_direction: motor_left_direction_raw,
            motor_right_direction: motor_right_direction_raw,
        })
    }


    fn GetEsp32SetupIMU( context: &ContextGraphQL) -> FieldResult<Esp32SetupIMU> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let invert_pitch_raw: bool = conn.get("ESP32.READ.SETUP.IMU.INVERT_PITCH_R")?;
        let invert_roll_raw: bool = conn.get("ESP32.READ.SETUP.IMU.INVERT_ROLL_R")?;
        let invert_yaw_raw: bool = conn.get("ESP32.READ.SETUP.IMU.INVERT_YAW_R")?;
        let offset_pitch_raw: i32 = conn.get("ESP32.READ.SETUP.IMU.OFFSET_PITCH_R")?;

        Ok(Esp32SetupIMU { 
            invert_pitch: invert_pitch_raw,
            invert_roll: invert_roll_raw,
            invert_yaw: invert_yaw_raw,
            offset_pitch: (offset_pitch_raw as f64) / 100.0,
        })
    }


    fn GetEsp32SetupEncoders( context: &ContextGraphQL) -> FieldResult<Esp32SetupEncoders> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let encoder_left_direction_raw: bool = conn.get("ESP32.READ.SETUP.ENCODER_LEFT.DIRECTION_R")?;
        let encoder_right_direction_raw: bool = conn.get("ESP32.READ.SETUP.ENCODER_RIGHT.DIRECTION_R")?;

        Ok(Esp32SetupEncoders { 
            encoder_left_direction: encoder_left_direction_raw,
            encoder_right_direction: encoder_right_direction_raw,
        })
    }





































    fn GetEsp32LiveMotors( context: &ContextGraphQL) -> FieldResult<Esp32LiveMotors> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed getting connection from pool");

        let motor_left_speed_raw: i32 = conn.get("ESP32.READ.LIVE.MOTOR_LEFT.SPEED_R")?;
        let motor_right_speed_raw: i32 = conn.get("ESP32.READ.LIVE.MOTOR_RIGHT.SPEED_R")?;

        Ok(Esp32LiveMotors { 
            motor_left_speed: (motor_left_speed_raw as f64) / 100.0,
            motor_right_speed: (motor_right_speed_raw as f64) / 100.0, 
        })
    }


}
