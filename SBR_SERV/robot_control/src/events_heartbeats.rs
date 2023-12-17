use std::{error::Error, sync::mpsc::{Receiver, Sender}, time::{SystemTime, UNIX_EPOCH}};

use crate::{type_heartbeat_message::HeartbeatMessage, type_event::RobotEvent};


//=====================================================================================================
pub struct EventsHeartbeats {
    receiver_heartbeats: Receiver<HeartbeatMessage>,
    sender_events: Sender<RobotEvent>,
    heartbeat_esp32: Heartbeat
}

//=====================================================================================================
#[derive(Debug, Clone, PartialEq, Eq)]
struct Heartbeat {
    value: i64,
    timestamp: u64,
    status: bool,
}


//=====================================================================================================
impl EventsHeartbeats {

    //=====================================================================================================
    pub fn new(receiver_heartbeats: Receiver<HeartbeatMessage>, sender_events: Sender<RobotEvent>) -> Self {
        let now = SystemTime::now().duration_since(UNIX_EPOCH).unwrap().as_secs();
        EventsHeartbeats {
            receiver_heartbeats: receiver_heartbeats,
            sender_events: sender_events,
            heartbeat_esp32: Heartbeat{ 
                value: 0, 
                timestamp: now,
                status: true,
            }
        }
    }

    
    //=====================================================================================================
    pub fn run(&mut self) -> Result<(), Box<dyn Error>> {

        self.get_heartbeats()?;
        self.check_heartbeats()?;
        
        Ok(())
    }


    //=====================================================================================================
    fn get_heartbeats(&mut self) -> Result<(), Box<dyn Error>> {

        match self.receiver_heartbeats.try_recv() {
            Ok(heartbeat) =>{
                self.handle_heartbeat(heartbeat)?;
            },
            Err(_)=>{}
        }

        return Ok(())
    }


    //=====================================================================================================
    pub fn handle_heartbeat(&mut self, msg: HeartbeatMessage) -> Result<(), Box<dyn Error>> {

        let now = SystemTime::now().duration_since(UNIX_EPOCH)?.as_secs();

        match msg.name.as_str(){
            "ESP32.READ.STATUS.HEARTBEAT" => {
                let value = msg.data as i64;
                if value != self.heartbeat_esp32.value {
                    self.heartbeat_esp32.value = value;
                    self.heartbeat_esp32.timestamp = now;
                }
            },
            _ => {}
        }

        Ok(())
    }


    //=====================================================================================================
    pub fn check_heartbeats(&mut self) -> Result<(), Box<dyn Error>> {

        let now = SystemTime::now().duration_since(UNIX_EPOCH)?.as_secs();

        if now - self.heartbeat_esp32.timestamp > 5 {
            if self.heartbeat_esp32.status == true {
                self.heartbeat_esp32.status = false;
                self.sender_events.send(RobotEvent::ConnectionErrorEsp32)?;
            }
        } else {
            if self.heartbeat_esp32.status == false {
                self.heartbeat_esp32.status = true;
                self.sender_events.send(RobotEvent::ConnectionOkEsp32)?;
            }
        }

        Ok(())
    }

}
