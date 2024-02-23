use std::fmt;


//=====================================================================================================
// Commands
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum RobotCommand {
    RobotStart,
    RobotStop,
    RobotPause,
}

//=====================================================================================================
// Events
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum RobotEvent {
    None,
    ConnectionErrorEsp32,
    ConnectionOkEsp32,
    RequestLoadDataEsp32,
    ConfirmLoadDataEsp32,
    RobotFallDown,
    RobotStandUp,
    Command(RobotCommand),
}

//=====================================================================================================
impl fmt::Display for RobotEvent {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{:?}", self)
    }
}