
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
pub struct Esp32SetupEncoders{
    pub encoder_left_direction: bool,
    pub encoder_right_direction: bool,
}


#[derive(Debug, Clone, GraphQLObject)]
pub struct Esp32SetupOdometry{
    pub wheel_radio: f64,
    pub distance_wheels: f64,
}


#[derive(Debug, Clone, GraphQLObject)]
pub struct Esp32SetupMotionPID{
    pub kp: f64,
    pub ki: f64,
    pub kd: f64,
    pub cycle: f64,
    pub direction: bool,
    pub mv_min: f64,
    pub mv_max: f64
}


#[derive(Debug, Clone, GraphQLObject)]
pub struct Esp32LiveMotors {
    pub motor_left_speed: f64,
    pub motor_right_speed: f64,
}


#[derive(Debug, Clone, GraphQLObject)]
pub struct Esp32LiveIMU {
    pub pitch: f64,
    pub roll: f64,
    pub yaw: f64,
}


#[derive(Debug, Clone, GraphQLObject)]
pub struct Esp32LiveEncoders {
    pub encoder_left_count: f64,
    pub encoder_right_count: f64,
}


#[derive(Debug, Clone, GraphQLObject)]
pub struct Esp32LiveOdometry {
    pub x: f64,
    pub y: f64,
    pub angle: f64,
    pub distance: f64,
}


#[derive(Debug, Clone, GraphQLObject)]
pub struct Esp32LiveMotion {
    pub setpoint_position: f64,
    pub setpoint_angle: f64,
}


