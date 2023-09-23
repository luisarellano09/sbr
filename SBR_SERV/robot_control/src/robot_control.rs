use std::sync::mpsc::Receiver;
use std::{error::Error, thread, time};

use ::reqwest::blocking::Client;

use crate::graphql::{query_get_esp32_status, mutation_load_esp32_setup, mutation_set_esp32_mode_node1_start, mutation_set_esp32_mode_node1_sync_data, query_get_esp32_mode_node1_sync_data, query_get_esp32_live_imu, mutation_set_esp32_mode_node1_stop};
use crate::collect_events::{RobotEvent, RobotCommand};

//=====================================================================================================
#[derive(Debug)]
pub struct RobotControl {
    state: RobotState,
    mode_option: RobotModeOptions,
    prev_event: RobotEvent,
    graphql_client: Client,
    receiver_collect_events: Receiver<RobotEvent>,
}

//=====================================================================================================
#[derive(Debug)]
enum RobotState {
    Init,
    CheckSystem,
    LoadDataEsp32,
    ConfirmLoadDataEsp32,
    ReadyToStart,
    StandUp,
    StartMotion,
    IdleMode,
    Move,
}

//=====================================================================================================
#[derive(Debug, Clone)]
struct RobotModeOptions {
    move_type: RobotMoveType,
}

//=====================================================================================================
#[derive(Debug, Clone, PartialEq, Eq)]
enum RobotMoveType {
    Polar,
}

//=====================================================================================================
impl RobotControl {
    pub fn new(receiver_collect_events: Receiver<RobotEvent>) -> Self {
        Self { 
            state: RobotState::Init,
            mode_option: RobotModeOptions { 
                move_type: RobotMoveType::Polar
            },
            prev_event: RobotEvent::None,
            graphql_client: Client::new(),
            receiver_collect_events: receiver_collect_events,
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
            (RobotState::StandUp, RobotEvent::None) => self.robot_state_standup()?,
            (RobotState::StartMotion, RobotEvent::None) => self.robot_state_start_motion()?,
            (RobotState::IdleMode, RobotEvent::None) => self.robot_state_idle_mode()?,
            (RobotState::Move, RobotEvent::None) => self.robot_state_move()?,
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

        self.state = RobotState::StandUp;

        Ok(())
    }


    //=====================================================================================================
    fn robot_state_standup(&mut self) -> Result<(), Box<dyn Error>> {

        dbg!(&self.state);

        let res = query_get_esp32_live_imu(&self.graphql_client)?;
        let pitch = res.pitch;

        thread::sleep(time::Duration::from_millis(100));

        if pitch < 15.0 && pitch > -15.0 {
            thread::sleep(time::Duration::from_millis(1000));
            self.state = RobotState::StartMotion;
        }

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

        //dbg!(&self.state);

        if self.mode_option.move_type == RobotMoveType::Polar {
            
        }


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
    fn robot_event_request_load_data_esp32(&mut self) -> Result<(), Box<dyn Error>> {
        self.state = RobotState::Init;

        Ok(())
    }


    //=====================================================================================================
    fn robot_event_robot_fall(&mut self) -> Result<(), Box<dyn Error>> {
        mutation_set_esp32_mode_node1_stop(&self.graphql_client)?;
        self.state = RobotState::StandUp;

        Ok(())
    }


    //=====================================================================================================
    fn robot_event_command(&mut self, command: RobotCommand) -> Result<(), Box<dyn Error>> {

        dbg!(&self.state);

        dbg!(command);

        Ok(())
    }



}