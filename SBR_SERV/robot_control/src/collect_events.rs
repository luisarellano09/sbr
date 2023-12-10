use std::error::Error;
use std::time::{SystemTime, UNIX_EPOCH};
use std::sync::mpsc::Sender;
use ::reqwest::blocking::Client;

use crate::graphql::{query_get_esp32_status, query_get_esp32_mode_node1_sync_data, query_get_esp32_live_imu};


//=====================================================================================================
// Struct for CollectEvents
pub struct CollectEvents{
    graphql_client: Client,
    sender_robot_control: Sender<RobotEvent>,
    prev_heartbeat: (u64, i64),
    heartbeat_error: bool,
    prev_event: RobotEvent,
    robot_up: bool,
}

//=====================================================================================================
// Events
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum RobotEvent {
    None,
    HeartbeatError,
    NodeLinuxError,
    NodeEsp32Error,
    RequestLoadDataEsp32,
    RobotFall,
    Command(RobotCommand),
}

//=====================================================================================================
// Commands
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum RobotCommand {
    Start,
    Stop,
    Pause,
}


//===================================================================================================================================
//===================================================================================================================================
impl CollectEvents {

    //=====================================================================================================
    // Constructor for CollectEvents
    pub fn new(sender_robot_control: Sender<RobotEvent>) -> Self {
        Self {
            graphql_client: Client::new(),
            sender_robot_control: sender_robot_control,
            prev_heartbeat: (0,0),
            heartbeat_error: false,
            prev_event: RobotEvent::None,
            robot_up: false,
        }
    }


    //=====================================================================================================
    // Main loop for CollectEvents
    pub fn run(&mut self) -> Result<(), Box<dyn Error>> {
        
        let new_event = self.collect_events()?;

        if new_event != self.prev_event {
            self.sender_robot_control.send(new_event.clone())?;
        }

        self.prev_event = new_event;

        Ok(())
    }


    //=====================================================================================================
    pub fn collect_events(&mut self) -> Result<RobotEvent, Box<dyn Error>> {
        
        let new_event = self.collect_event_esp32()?;
        if new_event != RobotEvent::None {
            return Ok(new_event);
        }

        let new_event = self.collect_request_load_data_esp32()?;
        if new_event != RobotEvent::None {
            return Ok(new_event);
        }

        let new_event = self.collect_robot_fall()?;
        if new_event != RobotEvent::None {
            return Ok(new_event);
        }

        return Ok(RobotEvent::None);
    }


    //=====================================================================================================
    fn collect_event_esp32(&mut self) -> Result<RobotEvent, Box<dyn Error>> {

        let res = query_get_esp32_status(&self.graphql_client)?;
        let heartbeat = res.heartbeat;
        let node_esp32 = res.node_esp32;
        let node_linux = res.node_linux;
        let secs = SystemTime::now().duration_since(UNIX_EPOCH).unwrap().as_secs();

        if self.prev_heartbeat.0 + 2 < secs {
            if self.prev_heartbeat.1 == heartbeat {
                self.heartbeat_error = true;
            }
            else {
                self.heartbeat_error = false;
            }
            self.prev_heartbeat = (secs, heartbeat);
        }

        if self.heartbeat_error == true {
            return Ok(RobotEvent::HeartbeatError);
        }

        if node_linux == false {
            return Ok(RobotEvent::NodeLinuxError);
        }

        if node_esp32 == false {
            return Ok(RobotEvent::NodeEsp32Error);
        }

        Ok(RobotEvent::None)
    }


    //=====================================================================================================
    fn collect_request_load_data_esp32(&mut self) -> Result<RobotEvent, Box<dyn Error>> {

        let res = query_get_esp32_mode_node1_sync_data(&self.graphql_client)?;
        if matches!(res, crate::graphql::get_esp32_mode_node1_sync_data::RegisterCommand::Requested) {
            return Ok(RobotEvent::RequestLoadDataEsp32);
        }

        Ok(RobotEvent::None)
    }


    //=====================================================================================================
    fn collect_robot_fall(&mut self) -> Result<RobotEvent, Box<dyn Error>> {
        
        let res = query_get_esp32_live_imu(&self.graphql_client)?;
        let pitch = res.pitch;

        if pitch < 15.0 && pitch > -15.0 {
            self.robot_up = true;
        }

        if self.robot_up == true && (pitch > 60.0 || pitch < -60.0) {
            self.robot_up = false;
            return Ok(RobotEvent::RobotFall);
        }

        Ok(RobotEvent::None)
    }

}