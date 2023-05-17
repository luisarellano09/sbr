
use juniper::GraphQLObject;

#[derive(Debug, Clone, GraphQLObject)]
pub struct Esp32LiveMotors {
    pub motor_left_speed: f64,
    pub motor_right_speed: f64,
}