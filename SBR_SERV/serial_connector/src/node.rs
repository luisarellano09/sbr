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
            match self.m_serial.read_buffer(8){
                Ok(buffer) => {
                    self.serial_handler(buffer).unwrap();
                },
                Err(er) => eprintln!("{}", er)
            }
        }
    }


    fn write_request(&mut self) {

        match self.m_receiver_consumer_node.try_recv() {
            Ok(msg) =>{
                self.m_buffer_requests.push_back(create_request(msg.register_enum, msg.data));
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


    pub fn add_request(&mut self, reg_id: COM_REQUEST_REG_ID_e, data: i32) {
        self.m_buffer_requests.push_back(create_request(reg_id, data));
    }


    fn serial_handler(&mut self, buffer: Vec<u8>) -> Result<(), Box<dyn Error>> {
        if buffer.len() == 8 {
            let buffer_array: [u8;8] = [buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]];
    
            match buffer_to_request(buffer_array){
                Ok(request) => {
                    
                    // Check CRC
                    if check_crc(request).unwrap() == true {
                        // Handler
                        self.request_handler(&request).unwrap();

                        // Send to rabbitmq
                        self.m_sender_node_producer.send(MessageEsp32 { register_num: request.reg_id, data: request.data, register_enum: COM_REQUEST_REG_ID_e::NONE_REG_ID }).unwrap();
                    
                    } else {
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
            self.add_request(COM_REQUEST_REG_ID_e::STATUS_HEARTBEAT_LINUX_COUNTER_R, self.m_watchdog_current_token.clone() as i32);
        }
        Ok(())
    }


}


fn create_request(reg_id: COM_REQUEST_REG_ID_e, data: i32) -> Request{
    let mut request = Request { node_id: 4, req_type: 2, reg_id: (reg_id as u16), data: data, crc: 0 };
    request.crc = calculate_crc_from_request(request).unwrap();
    request
}







