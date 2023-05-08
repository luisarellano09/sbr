#![allow(dead_code)]

use std::error::Error;
use std::time::{Instant};
use std::collections::VecDeque;
use std::sync::mpsc::{Sender, Receiver};

use crate::request::{buffer_to_request, check_crc, calculate_crc_from_request, request_to_buffer, Request};
use crate::register_table::{COM_REQUEST_REG_ID_e};
use crate::message_esp32::MessageEsp32;
use crate::serial::Serial;


pub struct Node {
    m_portname: String,
    m_baudrate: u32,
    m_serial: Serial,
    m_watchdow_timeout_ms: u32,
    m_watchdow_instant: Instant, 
    m_watchdog_current_token: u32,
    m_watchdog_prev_token: u32,
    pub m_buffer_requests: VecDeque<Request>,
    m_sender_node_producer: Sender<MessageEsp32>,
    m_receiver_consumer_node: Receiver<MessageEsp32>,
    m_error: bool,
    m_crc_error: bool,
}


impl Node{

    pub fn new(portname: String, baudrate: u32, watchdow_timeout_ms: u32, sender_node_producer:Sender<MessageEsp32> , receiver_consumer_node: Receiver<MessageEsp32>,) -> Self {
        Node{
            m_portname : portname.clone(),
            m_baudrate: baudrate,
            m_serial: Serial::new(portname, baudrate, 3000000).unwrap(),
            m_watchdow_timeout_ms: watchdow_timeout_ms,
            m_watchdow_instant: Instant::now(),
            m_watchdog_current_token: 0,
            m_watchdog_prev_token: 0,
            m_buffer_requests: VecDeque::new(),
            m_sender_node_producer: sender_node_producer,
            m_receiver_consumer_node: receiver_consumer_node,
            m_error: false,
            m_crc_error: false,
        }
    }


    pub fn run(&mut self) {
        loop {
            self.watchdog();
            self.read_request();
            self.write_request();
        }
    }


    fn read_request(&mut self) {
        if self.m_serial.m_port.bytes_to_read().unwrap() > 0 {
            match self.m_serial.read_buffer_crc(8, self.m_crc_error){
                Ok(buffer) => {
                    self.serial_read_handler(buffer).unwrap();
                },
                Err(er) => eprintln!("{}", er)
            }
        }
    }


    fn write_request(&mut self) {

        match self.m_receiver_consumer_node.try_recv() {
            Ok(msg) =>{
                self.serial_write_handler(msg).unwrap();
            }, 
            Err(_)=>{}
        }

        match self.m_buffer_requests.pop_front(){
            Some(request) =>{
                self.m_serial.write_u8s(&request_to_buffer(request).unwrap()).unwrap();
            }, 
            None =>{}
        }

    }


    fn watchdog(&mut self){
        if self.m_watchdow_instant.elapsed().as_millis() >= (self.m_watchdow_timeout_ms as u128) {
            self.m_watchdow_instant = Instant::now();
            if self.m_watchdog_current_token == self.m_watchdog_prev_token {
                self.m_error = true;
                dbg!(&self.m_error);
            } else if self.m_watchdog_current_token != self.m_watchdog_prev_token && self.m_error == true  {
                self.m_error = false;
                dbg!(&self.m_error);
            }

            self.m_watchdog_prev_token = self.m_watchdog_current_token;

        }
    }


    pub fn add_request(&mut self, reg_id: u16, data: i32) {
        self.m_buffer_requests.push_back(create_request(reg_id, data));
    }


    fn serial_read_handler(&mut self, buffer: VecDeque<u8>) -> Result<(), Box<dyn Error>> {
        if buffer.len() == 8 {
            let buffer_array: [u8;8] = [buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]];
    
            match buffer_to_request(buffer_array){
                Ok(request) => {
                    
                    // Check CRC
                    if check_crc(request).unwrap() == true {
                        // Handler
                        self.request_handler(&request).unwrap();    
                        self.m_crc_error = false;                  
                    
                    } else {
                        self.m_crc_error = true;
                        eprintln!("Wrong CRC");
                    }
                }, 
                Err(er) =>{
                    eprintln!("{}",er);
                }
            }
        }
    
        Ok(())
    }


    fn request_handler(&mut self, request: &Request) -> Result<(), Box<dyn Error>> {
    
        if request.reg_id == (COM_REQUEST_REG_ID_e::STATUS_HEARTBEAT_LINUX_COUNTER_R as u16){
            self.m_watchdog_current_token = request.data as u32 + 1;
            self.add_request(request.reg_id, self.m_watchdog_current_token.clone() as i32);

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::STATUS_NODE_LINUX_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.STATUS.NODE_LINUX_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::STATUS_NODE_ESP32_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.STATUS.NODE_ESP32_R".to_string(), data: request.data}).unwrap();
            
        } else if request.reg_id == (COM_REQUEST_REG_ID_e::MODE_MANAGER_SYNC_DATA_RW as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.MODE.MANAGER.SYNC_DATA_RW".to_string(), data: request.data}).unwrap();
            
        } else if request.reg_id == (COM_REQUEST_REG_ID_e::MODE_LINUX_SYNC_DATA_RW as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.MODE.LINUX.SYNC_DATA_RW".to_string(), data: request.data}).unwrap();
            
        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTOR_LEFT_OFFSET_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTOR.LEFT_OFFSET_R".to_string(), data: request.data}).unwrap();
            
        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTOR_RIGHT_OFFSET_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTOR.RIGHT_OFFSET_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTOR_RIGHT_DIRECTION_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTOR.RIGHT_DIRECTION_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_IMU_INVERT_PITCH_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.IMU.INVERT_PITCH_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_IMU_INVERT_ROLL_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.IMU.INVERT_ROLL_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_IMU_INVERT_YAW_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.IMU.INVERT_YAW_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_IMU_OFFSET_PITCH_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.IMU.OFFSET_PITCH_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_ENCODER_LEFT_DIRECTION_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.ENCODER.LEFT_DIRECTION_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_ENCODER_RIGHT_DIRECTION_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.ENCODER.RIGHT_DIRECTION_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_ODOMETRY_WHEEL_RADIO_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.ODOMETRY.WHEEL_RADIO_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_ODOMETRY_DISTANCE_WHEELS_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.ODOMETRY.DISTANCE_WHEELS_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_KP_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_PITCH.KP_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_KI_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_PITCH.KI_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_KD_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_PITCH.KD_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_CYCLE_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_PITCH.CYCLE_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_DIRECTION_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_PITCH.DIRECTION_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_MV_MIN_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_PITCH.MV_MIN_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_PITCH_MV_MAX_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_PITCH.MV_MAX_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_KP_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_POSITION.KP_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_KI_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_POSITION.KI_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_KD_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID.POSITION_KD_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_CYCLE_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_POSITION.CYCLE_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_DIRECTION_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_POSITION.DIRECTION_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_MV_MIN_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_POSITION.MV_MIN_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_POSITION_MV_MAX_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION_PID_POSITION.MV_MAX_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_KP_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_ANGLE.KP_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_KI_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_ANGLE.KI_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_KD_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_ANGLE.KD_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_CYCLE_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_ANGLE.CYCLE_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_DIRECTION_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_ANGLE.DIRECTION_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_MV_MIN_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_ANGLE.MV_MIN_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::SETUP_MOTION_PID_ANGLE_MV_MAX_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.SETUP.MOTION.PID_ANGLE.MV_MAX_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::LIVE_MOTOR_LEFT_SPEED_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.LIVE.MOTOR.LEFT_SPEED_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::LIVE_MOTOR_RIGHT_SPEED_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.LIVE.MOTOR_RIGHT_SPEED_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::LIVE_IMU_PITCH_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.LIVE.IMU.PITCH_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::LIVE_IMU_ROLL_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.LIVE.IMU.ROLL_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::LIVE_IMU_YAW_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.LIVE.IMU.YAW_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::LIVE_ENCODER_LEFT_COUNT_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.LIVE.ENCODER.LEFT_COUNT_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::LIVE_ENCODER_RIGHT_COUNT_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.LIVE.ENCODER.RIGHT_COUNT_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_X_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.LIVE.ODOMETRY.X_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_Y_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.LIVE.ODOMETRY.Y_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_ANGLE_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.LIVE.ODOMETRY.ANGLE_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::LIVE_ODOMETRY_DISTANCE_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.LIVE.ODOMETRY.DISTANCE_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::LIVE_MOTION_SP_POSITION_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.LIVE.MOTION.SP_POSITION_R".to_string(), data: request.data}).unwrap();

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::LIVE_MOTION_SP_ANGLE_R as u16){
            self.m_sender_node_producer.send(MessageEsp32 { name: "ESP32.READ.LIVE.MOTION.SP_ANGLE_R".to_string(), data: request.data}).unwrap();
        
        }

        Ok(())
    }

    fn serial_write_handler(&mut self, msg: MessageEsp32) -> Result<(), Box<dyn Error>> {
    /*
        if request.reg_id == (COM_REQUEST_REG_ID_e::STATUS_HEARTBEAT_LINUX_COUNTER_R as u16){
            self.m_buffer_requests.push_back(create_request(COM_REQUEST_REG_ID_e::STATUS_HEARTBEAT_LINUX_COUNTER_R as u16, msg.data));

        } else if request.reg_id == (COM_REQUEST_REG_ID_e::STATUS_HEARTBEAT_LINUX_COUNTER_R as u16){
            self.m_buffer_requests.push_back(create_request(COM_REQUEST_REG_ID_e::STATUS_HEARTBEAT_LINUX_COUNTER_R as u16, msg.data));

      
*/


        Ok(())
    }



}


fn create_request(reg_id: u16, data: i32) -> Request{
    let mut request = Request { node_id: 4, req_type: 2, reg_id: reg_id, data: data, crc: 0 };
    request.crc = calculate_crc_from_request(request).unwrap();
    request
}







