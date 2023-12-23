use std::sync::mpsc::Receiver;
use std::error::Error;
use ::reqwest::blocking::Client;
use crate::type_state::{RobotState, StateStep};
use crate::{graphql::{mutation_load_esp32_setup, mutation_set_esp32_mode_node1_start, mutation_set_esp32_mode_node1_sync_data, mutation_set_esp32_mode_node1_stop, mutation_set_robot_status}, type_event::{RobotEvent, RobotCommand}};


//=====================================================================================================
// Struct for the RobotControl state machine.
#[derive(Debug)]
pub struct RobotControl {
    state: RobotState,
    prev_state: RobotState,
    current_event: RobotEvent,
    graphql_client: Client,
    receiver_events: Receiver<RobotEvent>,
}


//===================================================================================================================================
// RobotControl
//===================================================================================================================================
impl RobotControl {
    
    //=====================================================================================================
    // Constructor for the RobotControl struct.
    pub fn new(receiver_events: Receiver<RobotEvent>) -> Self {
        Self { 
            state: RobotState::Init(StateStep::Initialization),
            prev_state: RobotState::Init(StateStep::Initialization),
            current_event: RobotEvent::None,
            graphql_client: Client::new(),
            receiver_events: receiver_events,
        }
    }


    //=====================================================================================================
    // Main function for the robot control state machine.
    pub fn run(&mut self) -> Result<(), Box<dyn Error>> {

        // Get the current event from the event collector.
        self.current_event = self.get_events()?;

        // Log the current state and event.
        self.log()?;
    
        // Match the current state and event to the appropriate function.
        match (self.state.clone(), self.current_event.clone()) {
            (RobotState::Init(state_step), RobotEvent::None) => self.robot_state_init(state_step.clone())?,
            (RobotState::LoadDataEsp32(state_step), RobotEvent::None) => self.robot_state_load_data_esp32(state_step.clone())?,
            (RobotState::ConfirmLoadDataEsp32(_state_step), RobotEvent::ConfirmLoadDataEsp32) => self.robot_transition_out_confirm_load_data_esp32()?,
            (RobotState::ReadyToStart(_state_step), RobotEvent::Command(cmd)) => self.robot_transition_out_ready_to_start(cmd)?,
            (RobotState::StandUp(_state_step), RobotEvent::RobotStandUp) => self.robot_transition_out_standup()?,
            (RobotState::StandUp(_state_step), RobotEvent::Command(cmd)) => self.robot_transition_out_standup_stop(cmd)?,
            (RobotState::StartMotion(state_step), RobotEvent::None) => self.robot_state_start_motion(state_step.clone())?,
            (RobotState::OperationMode(state_step), RobotEvent::None) => self.robot_state_operation_mode(state_step.clone())?,
            (_, RobotEvent::ConnectionErrorEsp32) => self.robot_transition_in_connection_error_esp32()?,
            (RobotState::ConnectionErrorEsp32(_state_state), RobotEvent::ConnectionOkEsp32) => self.robot_transition_out_connection_error_esp32()?, 
            (_, RobotEvent::RequestLoadDataEsp32) => self.robot_event_request_load_data_esp32()?,
            (RobotState::OperationMode(_state_state), RobotEvent::RobotFallDown) => self.robot_event_robot_falldown()?,
            (RobotState::OperationMode(_state_state), RobotEvent::Command(cmd)) => self.robot_event_command(cmd)?,
            _ => {}
        }
        
        Ok(())
    }


    //=====================================================================================================
    // Get the current event from the event collector.
    fn get_events(&mut self) -> Result<RobotEvent, Box<dyn Error>> {

        match self.receiver_events.try_recv() {
            Ok(event) =>{
                //dbg!(&event);
                return Ok(event); 
            }, 
            Err(_)=>{}
        }

        return Ok(RobotEvent::None)
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
    // State machine function: Transition OUT ConfirmLoadDataEsp32
    fn robot_transition_out_confirm_load_data_esp32(&mut self) -> Result<(), Box<dyn Error>> {

        self.state = RobotState::ReadyToStart(StateStep::Initialization);

        Ok(())
    }

    
    //=====================================================================================================
    // State machine function: Transition OUT ReadyToStart
    fn robot_transition_out_ready_to_start(&mut self, cmd: RobotCommand) -> Result<(), Box<dyn Error>> {

        if cmd == RobotCommand::RobotStart {
            self.state = RobotState::StandUp(StateStep::Initialization);
        }

        Ok(())
    }


    //=====================================================================================================
    // State machine function: Transition OUT StandUp
    fn robot_transition_out_standup(&mut self) -> Result<(), Box<dyn Error>> {

        self.state = RobotState::StartMotion(StateStep::Initialization);

        Ok(())
    }

    
    //=====================================================================================================
    // State machine function: Transition OUT StandUp
    fn robot_transition_out_standup_stop(&mut self, cmd: RobotCommand) -> Result<(), Box<dyn Error>> {

        if cmd == RobotCommand::RobotStop {
            self.state = RobotState::ReadyToStart(StateStep::Initialization);
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
                
            },
            StateStep::Termination => {
                
            }
        }
        
        Ok(())
    }


    //=====================================================================================================
    // State machine function: Transition IN ConnectionErrorEsp32
    fn robot_transition_in_connection_error_esp32(&mut self) -> Result<(), Box<dyn Error>> {
        self.state = RobotState::ConnectionErrorEsp32(StateStep::Initialization);

        Ok(())
    }


    //=====================================================================================================
    // State machine function: Transition OUT ConnectionErrorEsp32
    fn robot_transition_out_connection_error_esp32(&mut self) -> Result<(), Box<dyn Error>> {
        self.state = RobotState::Init(StateStep::Initialization);

        Ok(())
    }



    //=====================================================================================================
    // Event function: RequestLoadDataEsp32
    fn robot_event_request_load_data_esp32(&mut self) -> Result<(), Box<dyn Error>> {
        self.state = RobotState::LoadDataEsp32(StateStep::Initialization);

        Ok(())
    }


    //=====================================================================================================
    // Event function: RobotFallDown
    fn robot_event_robot_falldown(&mut self) -> Result<(), Box<dyn Error>> {
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


    //=====================================================================================================
    fn log(&mut self) -> Result<(), Box<dyn Error>> {

        if self.state != self.prev_state {
            println!("Robot State: {:?}", self.state);
            mutation_set_robot_status(&self.graphql_client, "ROBOT_CONTROL".to_string(), "STATE".to_string(), self.state.to_string())?;
        }

        if self.current_event != RobotEvent::None {
            println!("Robot Event: {:?}", self.current_event);
            mutation_set_robot_status(&self.graphql_client, "ROBOT_CONTROL".to_string(), "EVENT".to_string(), self.current_event.to_string())?;
        }

        self.prev_state = self.state.clone();

        Ok(())
    }

}

