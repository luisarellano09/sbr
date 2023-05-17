
use juniper::{graphql_object, FieldResult};
use crate::graphql_context::ContextGraphQL;
use crate::graphql_types::Esp32LiveMotors;
use r2d2_redis::redis::Commands;

pub struct Queries;


#[graphql_object(context = ContextGraphQL)]
impl Queries {

    fn api_version() -> String {
        "1.0".to_string()
    }

    pub fn get_esp32_live_motors( context: &ContextGraphQL) -> FieldResult<Esp32LiveMotors> {

        let mut conn = context.redis_connection.redis_pool.get().expect("Failed");

        let motor_left_speed_raw: i32 = conn.get("ESP32.READ.LIVE.MOTOR_LEFT.SPEED_R")?;
        let motor_right_speed_raw: i32 = conn.get("ESP32.READ.LIVE.MOTOR_RIGHT.SPEED_R")?;

        Ok(Esp32LiveMotors { 
            motor_left_speed: (motor_left_speed_raw as f64) / 100.0,
            motor_right_speed: (motor_right_speed_raw as f64) / 100.0, 
        })
    }
}
