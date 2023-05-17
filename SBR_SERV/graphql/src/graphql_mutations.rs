
use juniper::{graphql_object, FieldResult};
use crate::graphql_context::ContextGraphQL;
use crate::graphql_types::Esp32LiveMotors;
use r2d2_redis::redis::Commands;

pub struct Mutations;

#[graphql_object(Context = ContextGraphQL)]
impl Mutations {

  fn SetMotorsSpeed(context: &ContextGraphQL, new_motor_left_speed: f64, new_motor_right_speed: f64) -> FieldResult<Esp32LiveMotors> {

    let mut conn = context.redis_connection.redis_pool.get().expect("Failed");

    conn.set("ESP32.READ.LIVE.MOTOR_LEFT.SPEED_R", (new_motor_left_speed * 100.0) as i32)?;
    conn.set("ESP32.READ.LIVE.MOTOR_RIGHT.SPEED_R", (new_motor_left_speed * 100.0) as i32)?;


    let motor_left_speed_raw: i32 = conn.get("ESP32.READ.LIVE.MOTOR_LEFT.SPEED_R")?;
    let motor_right_speed_raw: i32 = conn.get("ESP32.READ.LIVE.MOTOR_RIGHT.SPEED_R")?;

    Ok(Esp32LiveMotors { 
        motor_left_speed: (motor_left_speed_raw as f64) / 100.0,
        motor_right_speed: (motor_right_speed_raw as f64) / 100.0, 
    })

  }

}