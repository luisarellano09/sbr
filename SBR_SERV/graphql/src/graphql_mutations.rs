
use juniper::{graphql_object, FieldResult};
use crate::graphql_context::ContextGraphQL;
use crate::graphql_types::Esp32LiveMotors;
use crate::rabbitmq_connection::publish_esp32_write;

pub struct Mutations;

#[graphql_object(Context = ContextGraphQL)]
impl Mutations {

    fn RestartEsp32Manager(_context: &ContextGraphQL) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.MANAGER.RESTART_W".to_string(), 1)?;
            
        Ok(true)
    }


    fn ProgramEsp32Manager(_context: &ContextGraphQL) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.MANAGER.PROGRAM_W".to_string(), 1)?;
            
        Ok(true)
    }


    fn SyncDataManager(_context: &ContextGraphQL, new_motor_left_speed: Option<f64>, new_motor_right_speed: Option<f64>) -> FieldResult<Esp32LiveMotors> {

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

        Ok(Esp32LiveMotors { 
            motor_left_speed: new_motor_left_speed.unwrap_or_default(),
            motor_right_speed: new_motor_right_speed.unwrap_or_default(),
        })
    }


    fn RestartEsp32Node01(_context: &ContextGraphQL) -> FieldResult<bool> {

        publish_esp32_write("ESP32.WRITE.MODE.MANAGER.RESTART_W".to_string(), 1)?;
            
        Ok(true)
    }
    

    fn SetMotorsSpeed(_context: &ContextGraphQL, new_motor_left_speed: Option<f64>, new_motor_right_speed: Option<f64>) -> FieldResult<Esp32LiveMotors> {

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

        Ok(Esp32LiveMotors { 
            motor_left_speed: new_motor_left_speed.unwrap_or_default(),
            motor_right_speed: new_motor_right_speed.unwrap_or_default(),
        })
    }
    
    //todo


    

}