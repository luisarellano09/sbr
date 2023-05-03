#![allow(dead_code)]

use std::error::Error;

use std::collections::VecDeque;

#[path = "./serial.rs"] mod serial;
use serial::Serial;

#[path = "./request.rs"] mod request;
use request::{buffer_to_request, check_crc, calculate_crc_from_request, request_to_buffer, Request};

#[path = "./register_table.rs"] mod register_table;
pub use register_table::{COM_REQUEST_REG_ID_e};


pub struct Node {
    m_portname: String,
    m_baudrate: u32,
    m_serial: Serial,
    pub m_buffer_requests: VecDeque<Request>,
}


impl Node{

    pub fn new(portname: String, baudrate: u32) -> Self {
        Node{
            m_portname : portname.clone(),
            m_baudrate: baudrate,
            m_serial: Serial::new(portname, baudrate, 3000000).unwrap(),
            m_buffer_requests: VecDeque::new()
        }
    }


    pub fn run(&mut self) {
        self.read_request();
        self.write_request();
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
        match self.m_buffer_requests.pop_front(){
            Some(request) =>{
                self.m_serial.write_u8s(&request_to_buffer(request).unwrap()).unwrap();
            }, 
            None =>{}
        }

    }


    pub fn add_request(&mut self, reg_id: COM_REQUEST_REG_ID_e, data: i32) {
        let mut request = Request { node_id: 4, req_type: 2, reg_id: (reg_id as u16), data: data, crc: 0 };
        request.crc = calculate_crc_from_request(request).unwrap();
        self.m_buffer_requests.push_back(request);
    }


    fn request_handler(&mut self, request: Request) -> Result<(), Box<dyn Error>> {
    
        if request.reg_id == (COM_REQUEST_REG_ID_e::STATUS_HEARTBEAT_LINUX_COUNTER_R as u16){
            dbg!(request);
            self.add_request(COM_REQUEST_REG_ID_e::STATUS_HEARTBEAT_LINUX_COUNTER_R, request.data + 1);
        }
        Ok(())
    }


    fn serial_handler(&mut self, buffer: Vec<u8>) -> Result<(), Box<dyn Error>> {
        if buffer.len() == 8 {
            let buffer_array: [u8;8] = [buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]];
    
            match buffer_to_request(buffer_array){
                Ok(request) => {
                    
                    // Check CRC
                    if check_crc(request).unwrap() == true {
                        self.request_handler(request).unwrap();
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

}










