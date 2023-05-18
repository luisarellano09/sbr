
use juniper::GraphQLObject;


#[derive(Debug, Clone, GraphQLObject)]
pub struct Esp32Status {
    pub heartbeat: i32,
    pub node_linux: bool,
    pub node_esp32: bool,
}


#[derive(Debug, Clone, GraphQLObject)]
pub struct Esp32Mode{
    pub manager_sync_data: i32,
    pub linux_sync_data: i32,
}


#[derive(Debug, Clone, GraphQLObject)]
pub struct Esp32SetupMotor{
    pub motor_left_offset: f64,
    pub motor_right_offset: f64,
    pub motor_left_direction: bool,
    pub motor_right_direction: bool,
}


#[derive(Debug, Clone, GraphQLObject)]
pub struct Esp32SetupIMU{
    pub invert_pitch: bool,
    pub invert_roll: bool,
    pub invert_yaw: bool,
    pub offset_pitch: f64,
}


#[derive(Debug, Clone, GraphQLObject)]
pub struct Esp32LiveMotors {
    pub motor_left_speed: f64,
    pub motor_right_speed: f64,
}
