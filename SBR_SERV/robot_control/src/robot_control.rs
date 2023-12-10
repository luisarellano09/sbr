use std::sync::mpsc::Receiver;
use std::{error::Error, thread, time};

use ::reqwest::blocking::Client;

use crate::graphql::{query_get_esp32_status, mutation_load_esp32_setup, mutation_set_esp32_mode_node1_start, mutation_set_esp32_mode_node1_sync_data, query_get_esp32_mode_node1_sync_data, query_get_esp32_live_imu, mutation_set_esp32_mode_node1_stop};
use crate::collect_events::{RobotEvent, RobotCommand};


//=====================================================================================================
// Struct for the RobotControl state machine.
#[derive(Debug)]
pub struct RobotControl {
    state: RobotState,
    prev_event: RobotEvent,
    graphql_client: Client,
    receiver_collect_events: Receiver<RobotEvent>,
}

//=====================================================================================================
// Enum for the steps on the sates of the RobotControl state machine.
#[derive(Debug, Clone, PartialEq, Eq)]
enum StateStep {
    Initialization,
    Processing,
    Termination,
}

//=====================================================================================================
// Enum for the states of the RobotControl state machine.
#[derive(Debug, Clone, PartialEq, Eq)]
enum RobotState {
    Init(StateStep),
    CheckSystem(StateStep),
    LoadDataEsp32(StateStep),
    ConfirmLoadDataEsp32(StateStep),
    ReadyToStart(StateStep),
    StandUp(StateStep),
    StartMotion(StateStep),
    OperationMode(StateStep),
}


//===================================================================================================================================
// RobotControl
//===================================================================================================================================
impl RobotControl {
    
    //=====================================================================================================
    // Constructor for the RobotControl struct.
    pub fn new(receiver_collect_events: Receiver<RobotEvent>) -> Self {
        Self { 
            state: RobotState::Init(StateStep::Initialization),
            prev_event: RobotEvent::None,
            graphql_client: Client::new(),
            receiver_collect_events: receiver_collect_events,
        }
    }


    //=====================================================================================================
    // Main function for the robot control state machine.
    pub fn run(&mut self) -> Result<(), Box<dyn Error>> {

        //dbg!(&self.state);

        // Get the current event from the event collector.
        let event = self.get_events()?;
    
        // Match the current state and event to the appropriate function.
        match (&self.state, event) {
            (RobotState::Init(state_step), RobotEvent::None) => self.robot_state_init(state_step.clone())?,
            (RobotState::CheckSystem(state_step), RobotEvent::None) => self.robot_state_check_system(state_step.clone())?,
            (RobotState::LoadDataEsp32(state_step), RobotEvent::None) => self.robot_state_load_data_esp32(state_step.clone())?,
            (RobotState::ConfirmLoadDataEsp32(state_step), RobotEvent::None) => self.robot_state_confirm_load_data_esp32(state_step.clone())?,
            (RobotState::ReadyToStart(state_step), RobotEvent::None) => self.robot_state_ready_to_start(state_step.clone())?,
            (RobotState::StandUp(state_step), RobotEvent::None) => self.robot_state_standup(state_step.clone())?,
            (RobotState::StartMotion(state_step), RobotEvent::None) => self.robot_state_start_motion(state_step.clone())?,
            (RobotState::OperationMode(state_step), RobotEvent::None) => self.robot_state_operation_mode(state_step.clone())?,
            (_, RobotEvent::HeartbeatError) => self.robot_event_heartbeat_error()?,
            (_, RobotEvent::NodeLinuxError) => self.robot_event_node_linux_error()?,
            (_, RobotEvent::NodeEsp32Error) => self.robot_event_node_esp32_error()?,
            (_, RobotEvent::RequestLoadDataEsp32) => self.robot_event_request_load_data_esp32()?,
            (_, RobotEvent::RobotFall) => self.robot_event_robot_fall()?,
            (_, RobotEvent::Command(cmd)) => self.robot_event_command(cmd)?,
            //_ => todo!()
        }
        
        Ok(())
    }


    //=====================================================================================================
    // Get the current event from the event collector.
    fn get_events(&mut self) -> Result<RobotEvent, Box<dyn Error>> {

        match self.receiver_collect_events.try_recv() {
            Ok(event) =>{
                self.prev_event = event.clone();
                dbg!(&event);
                return Ok(event); 
            }, 
            Err(_)=>{}
        }

        return Ok(self.prev_event.clone())
    }


    //=====================================================================================================
    // State machine function: Init
    fn robot_state_init(&mut self, state_step: StateStep) -> Result<(), Box<dyn Error>> {

        match state_step {
            StateStep::Initialization => {
                mutation_set_esp32_mode_node1_sync_data(&self.graphql_client, crate::graphql::set_esp32_mode_node1_sync_data::RegisterCommand::None)?;
                self.state = RobotState::Init(StateStep::Processing);
            },
            StateStep::Processing => {
                self.state = RobotState::Init(StateStep::Termination);                
            },
            StateStep::Termination => {
                self.state = RobotState::CheckSystem(StateStep::Initialization);
            }            
        }

        Ok(())
    }


    //=====================================================================================================
    // State machine function: CheckSystem
    fn robot_state_check_system(&mut self, state_step: StateStep) -> Result<(), Box<dyn Error>> {

        match state_step {
            StateStep::Initialization => {
                self.state = RobotState::CheckSystem(StateStep::Processing);
            },
            StateStep::Processing => {

                let res = query_get_esp32_status(&self.graphql_client)?;
                let heartbeat_1 = res.heartbeat;
                let node_esp32_1 = res.node_esp32;
                let node_linux_1 = res.node_linux;

                thread::sleep(time::Duration::from_millis(2000));

                let res = query_get_esp32_status(&self.graphql_client)?;
                let heartbeat_2 = res.heartbeat;
                let node_esp32_2 = res.node_esp32;
                let node_linux_2 = res.node_linux;
                
                if node_esp32_1 == true && node_linux_1 == true && node_esp32_2 == true && node_linux_2 == true && heartbeat_1 < heartbeat_2 {
                    self.state = RobotState::CheckSystem(StateStep::Termination);
                }
            },
            StateStep::Termination => {
                self.state = RobotState::LoadDataEsp32(StateStep::Initialization);
            }
        }

        Ok(())
    }


    //=====================================================================================================
    // State machine function: LoadDataEsp32
    fn robot_state_load_data_esp32(&mut self, state_step: StateStep) -> Result<(), Box<dyn Error>> {

        match state_step {
            StateStep::Initialization => {
                self.state = RobotState::LoadDataEsp32(StateStep::Processing);
            },
            StateStep::Processing => {
                mutation_set_esp32_mode_node1_sync_data(&self.graphql_client, crate::graphql::set_esp32_mode_node1_sync_data::RegisterCommand::InProgress)?;
                mutation_load_esp32_setup(&self.graphql_client)?;
                mutation_set_esp32_mode_node1_sync_data(&self.graphql_client, crate::graphql::set_esp32_mode_node1_sync_data::RegisterCommand::ReadyToComplete)?;
                self.state = RobotState::LoadDataEsp32(StateStep::Termination);
            },
            StateStep::Termination => {
                self.state = RobotState::ConfirmLoadDataEsp32(StateStep::Initialization);
            }
        }

        Ok(())
    }


    //=====================================================================================================
    // State machine function: ConfirmLoadDataEsp32
    fn robot_state_confirm_load_data_esp32(&mut self, state_step: StateStep) -> Result<(), Box<dyn Error>> {

        match state_step {
            StateStep::Initialization => {
                self.state = RobotState::ConfirmLoadDataEsp32(StateStep::Processing);
            },
            StateStep::Processing => {
                let res = query_get_esp32_mode_node1_sync_data(&self.graphql_client)?;
                if matches!(res, crate::graphql::get_esp32_mode_node1_sync_data::RegisterCommand::Completed) {
                    self.state = RobotState::ConfirmLoadDataEsp32(StateStep::Termination);
                }
            },
            StateStep::Termination => {
                self.state = RobotState::ReadyToStart(StateStep::Initialization);
            }
        }

        Ok(())
    }

    
    //=====================================================================================================
    // State machine function: ReadyToStart
    fn robot_state_ready_to_start(&mut self, state_step: StateStep) -> Result<(), Box<dyn Error>> {

        match state_step {
            StateStep::Initialization => {
                self.state = RobotState::ReadyToStart(StateStep::Processing);
            },
            StateStep::Processing => {
                self.state = RobotState::ReadyToStart(StateStep::Termination);
            },
            StateStep::Termination => {
                self.state = RobotState::StandUp(StateStep::Initialization);
            }
        }

        Ok(())
    }


    //=====================================================================================================
    // State machine function: StandUp
    fn robot_state_standup(&mut self, state_step: StateStep) -> Result<(), Box<dyn Error>> {

        match state_step {
            StateStep::Initialization => {
                self.state = RobotState::StandUp(StateStep::Processing);
            },
            StateStep::Processing => {
                let res = query_get_esp32_live_imu(&self.graphql_client)?;
                let pitch = res.pitch;

                thread::sleep(time::Duration::from_millis(100));

                if pitch < 15.0 && pitch > -15.0 {
                    thread::sleep(time::Duration::from_millis(1000));
                    self.state = RobotState::StandUp(StateStep::Termination);
                }
            },
            StateStep::Termination => {
                self.state = RobotState::StartMotion(StateStep::Initialization);
            }
        }

        Ok(())
    }


    //=====================================================================================================
    // State machine function: StartMotion
    fn robot_state_start_motion(&mut self, state_step: StateStep) -> Result<(), Box<dyn Error>> {

        match state_step {
            StateStep::Initialization => {
                self.state = RobotState::StartMotion(StateStep::Processing);
            },
            StateStep::Processing => {
                mutation_set_esp32_mode_node1_start(&self.graphql_client)?;
                self.state = RobotState::StartMotion(StateStep::Termination);
            },
            StateStep::Termination => {
                self.state = RobotState::OperationMode(StateStep::Initialization);
            }
        }

        Ok(())
    }


    //=====================================================================================================
    // State machine function: OperationMode
    fn robot_state_operation_mode(&mut self, state_step: StateStep) -> Result<(), Box<dyn Error>> {

        match state_step {
            StateStep::Initialization => {
                self.state = RobotState::OperationMode(StateStep::Processing);
            },
            StateStep::Processing => {
                self.state = RobotState::OperationMode(StateStep::Termination);
            },
            StateStep::Termination => {
                
            }
        }
        
        Ok(())
    }


    //=====================================================================================================
    // Event function: HeartbeatError
    fn robot_event_heartbeat_error(&mut self) -> Result<(), Box<dyn Error>> {
        self.state = RobotState::Init(StateStep::Initialization);

        Ok(())
    }


    //=====================================================================================================
    // Event function: NodeLinuxError
    fn robot_event_node_linux_error(&mut self) -> Result<(), Box<dyn Error>> {
        self.state = RobotState::Init(StateStep::Initialization);

        Ok(())
    }


    //=====================================================================================================
    // Event function: NodeEsp32Error
    fn robot_event_node_esp32_error(&mut self) -> Result<(), Box<dyn Error>> {
        self.state = RobotState::Init(StateStep::Initialization);

        Ok(())
    }


    //=====================================================================================================
    // Event function: RequestLoadDataEsp32
    fn robot_event_request_load_data_esp32(&mut self) -> Result<(), Box<dyn Error>> {
        self.state = RobotState::Init(StateStep::Initialization);

        Ok(())
    }


    //=====================================================================================================
    // Event function: RobotFall
    fn robot_event_robot_fall(&mut self) -> Result<(), Box<dyn Error>> {
        mutation_set_esp32_mode_node1_stop(&self.graphql_client)?;
        self.state = RobotState::StandUp(StateStep::Initialization);

        Ok(())
    }


    //=====================================================================================================
    // Event function: Command
    fn robot_event_command(&mut self, command: RobotCommand) -> Result<(), Box<dyn Error>> {

        dbg!(command);

        Ok(())
    }

}