use std::{error::Error, thread, time};

use ::reqwest::blocking::Client;

use crate::graphql::{query_get_esp32_status, mutation_load_esp32_setup, mutation_set_esp32_mode_node1_start, mutation_set_esp32_mode_node1_sync_data, query_get_esp32_mode_node1_sync_data};


//=====================================================================================================
#[derive(Debug)]
pub struct RobotControl {
    state: RobotState,
    mode_option: RobotModeOptions,
    graphql_client: Client,
}

//=====================================================================================================
#[derive(Debug)]
enum RobotState {
    Init,
    CheckSystem,
    LoadDataEsp32,
    ConfirmLoadDataEsp32,
    ReadyToStart,
    StartMotion,
    IdleMode,
    Move,
}

//=====================================================================================================
#[derive(Debug)]
enum RobotEvent {
    None,
    Command(RobotCommand),
    ChangeMode(RobotModeOptions),
    HeartbeatError,
    NodeLinuxError,
    NodeEsp32Error,
    RobotFall,
}

//=====================================================================================================
#[derive(Debug, Clone)]
struct RobotModeOptions {
    move_type: RobotMoveType,
}

//=====================================================================================================
#[derive(Debug, Clone)]
enum RobotMoveType {
    Polar,
}


//=====================================================================================================
#[derive(Debug)]
enum RobotCommand {
    Start,
    Stop,
    Pause,
}



//=====================================================================================================
impl RobotControl {
    pub fn new() -> Self {
        Self { 
            state: RobotState::Init,
            mode_option: RobotModeOptions { 
                move_type: RobotMoveType::Polar
            },
            graphql_client: Client::new(),
        }
    }

    //=====================================================================================================
    pub fn run(&mut self) -> Result<(), Box<dyn Error>> {

        let event = self.get_events()?;
        
        match (&self.state, event) {
            (RobotState::Init, RobotEvent::None) => self.robot_state_init()?,
            (RobotState::CheckSystem, RobotEvent::None) => self.robot_state_check_system()?,
            (RobotState::LoadDataEsp32, RobotEvent::None) => self.robot_state_load_data_esp32()?,
            (RobotState::ConfirmLoadDataEsp32, RobotEvent::None) => self.robot_state_confirm_load_data_esp32()?,
            (RobotState::ReadyToStart, RobotEvent::None) => self.robot_state_ready_to_start()?,
            (RobotState::StartMotion, RobotEvent::None) => self.robot_state_start_motion()?,
            (RobotState::IdleMode, RobotEvent::None) => self.robot_state_idle_mode()?,
            (RobotState::Move, RobotEvent::None) => self.robot_state_move()?,
            (_, RobotEvent::Command(cmd)) => self.robot_event_command(cmd)?,
            (_, RobotEvent::ChangeMode(_mode)) => {},
            (_, RobotEvent::HeartbeatError) => self.robot_event_heartbeat_error()?,
            (_, RobotEvent::NodeLinuxError) => self.robot_event_node_linux_error()?,
            (_, RobotEvent::NodeEsp32Error) => self.robot_event_node_esp32_error()?,
            (_, RobotEvent::RobotFall) => self.robot_event_robot_fall()?,
            //_ => todo!()
        }

        Ok(())
    }

    //=====================================================================================================
    fn get_events(&mut self) -> Result<RobotEvent, Box<dyn Error>> {

        Ok(RobotEvent::None)
    }


    //=====================================================================================================
    fn robot_state_init(&mut self) -> Result<(), Box<dyn Error>> {

        dbg!(&self.state);

        mutation_set_esp32_mode_node1_sync_data(&self.graphql_client, crate::graphql::set_esp32_mode_node1_sync_data::RegisterCommand::None)?;

        self.state = RobotState::CheckSystem;

        Ok(())
    }


    //=====================================================================================================
    fn robot_state_check_system(&mut self) -> Result<(), Box<dyn Error>> {

        dbg!(&self.state);

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
            self.state = RobotState::LoadDataEsp32;
        }

        Ok(())
    }


    //=====================================================================================================
    fn robot_state_load_data_esp32(&mut self) -> Result<(), Box<dyn Error>> {

        dbg!(&self.state);

        mutation_set_esp32_mode_node1_sync_data(&self.graphql_client, crate::graphql::set_esp32_mode_node1_sync_data::RegisterCommand::InProgress)?;
        mutation_load_esp32_setup(&self.graphql_client)?;
        mutation_set_esp32_mode_node1_sync_data(&self.graphql_client, crate::graphql::set_esp32_mode_node1_sync_data::RegisterCommand::ReadyToComplete)?;

        self.state = RobotState::ConfirmLoadDataEsp32;

        Ok(())
    }


    //=====================================================================================================
    fn robot_state_confirm_load_data_esp32(&mut self) -> Result<(), Box<dyn Error>> {

        dbg!(&self.state);

        let res = query_get_esp32_mode_node1_sync_data(&self.graphql_client)?;

        if matches!(res, crate::graphql::get_esp32_mode_node1_sync_data::RegisterCommand::Completed) {
            self.state = RobotState::ReadyToStart;
        } 

        Ok(())
    }

    
    //=====================================================================================================
    fn robot_state_ready_to_start(&mut self) -> Result<(), Box<dyn Error>> {

        dbg!(&self.state);

        self.state = RobotState::StartMotion;

        Ok(())
    }


    //=====================================================================================================
    fn robot_state_start_motion(&mut self) -> Result<(), Box<dyn Error>> {

        dbg!(&self.state);

        mutation_set_esp32_mode_node1_start(&self.graphql_client)?;

        self.state = RobotState::IdleMode;

        Ok(())
    }


    //=====================================================================================================
    fn robot_state_idle_mode(&mut self) -> Result<(), Box<dyn Error>> {

        dbg!(&self.state);

        self.state = RobotState::Move;
        
        Ok(())
    }


    //=====================================================================================================
    fn robot_state_move(&mut self) -> Result<(), Box<dyn Error>> {

        if matches!(self.mode_option.move_type, RobotMoveType::Polar) {
            
        }

        Ok(())
    }
    

    //=====================================================================================================
    fn robot_event_command(&mut self, command: RobotCommand) -> Result<(), Box<dyn Error>> {

        dbg!(&self.state);

        dbg!(command);

        Ok(())
    }


    //=====================================================================================================
    fn robot_event_heartbeat_error(&mut self) -> Result<(), Box<dyn Error>> {
        self.state = RobotState::Init;

        Ok(())
    }


    //=====================================================================================================
    fn robot_event_node_linux_error(&mut self) -> Result<(), Box<dyn Error>> {
        self.state = RobotState::Init;

        Ok(())
    }


    //=====================================================================================================
    fn robot_event_node_esp32_error(&mut self) -> Result<(), Box<dyn Error>> {
        self.state = RobotState::Init;

        Ok(())
    }


    //=====================================================================================================
    fn robot_event_robot_fall(&mut self) -> Result<(), Box<dyn Error>> {
        self.state = RobotState::IdleMode;

        Ok(())
    }


}