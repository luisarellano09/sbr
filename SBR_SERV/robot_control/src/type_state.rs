use std::fmt;


//=====================================================================================================
// Enum for the steps on the sates of the RobotControl state machine.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum StateStep {
    Initialization,
    Processing,
    Termination,
}

//=====================================================================================================
// Enum for the states of the RobotControl state machine.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum RobotState {
    Init(StateStep),
    LoadDataEsp32(StateStep),
    ConfirmLoadDataEsp32(StateStep),
    ReadyToStart(StateStep),
    StandUp(StateStep),
    StartMotion(StateStep),
    OperationMode(StateStep),
    ConnectionErrorEsp32(StateStep),
}

//=====================================================================================================
impl fmt::Display for RobotState {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{:?}", self)
    }
}
