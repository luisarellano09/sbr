/*******************************************************************************************************************************************
 *  												USE
 *******************************************************************************************************************************************/
 #![allow(dead_code)]

use std::str;
use std::error::Error;
use serialport::{available_ports, SerialPort};
use std::time::Duration;

/*******************************************************************************************************************************************
 *  												ENUMS
 *******************************************************************************************************************************************/

pub enum PortVisibility {
    Found,
    NotFound,
}

/*******************************************************************************************************************************************
 *  												Serial
 *******************************************************************************************************************************************/

pub struct Serial {
    m_portname: String,
    m_baudrate: u32,
    m_timeout: u64,
    m_port: Box<dyn SerialPort>,
}


impl Serial {

//=====================================================================================================
    pub fn new(portname: String, baudrate: u32, timeout: u64) -> Result<Self,Box<dyn Error>> {

        if let Err(er) = Self::list_ports() {
            let e = format!("Error: {:?} <- new()", er);
            eprintln!("{}",e);
            return Err(e.into());
        }
    
        match Self::check_port(&portname){
            Ok(p) => {
                match p {
                    PortVisibility::Found => println!("Port {} found", portname),
                    PortVisibility::NotFound => {
                        let e = format!("Error: Port {} not found, new()", portname);
                        eprintln!("{}",e);
                        return Err(e.into());
                    }
                }
            },
            Err(er) => {
                let e = format!("Error: {:?} <- list_ports()", er);
                eprintln!("{}",e);
                return Err(e.into());
            }
        };

        let temp_port = match serialport::new(&portname, baudrate)
            .timeout(Duration::from_secs(timeout))
            .open(){
                Ok(port) => port,
                Err(er) => {
                    let e = format!("Error: {:?} <- open() <- new()", er);
                    eprintln!("{}",e);
                    return Err(e.into());
                }
        };
                            
        Ok(Serial{
            m_portname : portname.clone(),
            m_baudrate: baudrate,
            m_timeout: timeout,
            m_port: temp_port,
        })
    }

//=====================================================================================================
    pub fn write_char(&mut self, payload: char) -> Result<(), Box<dyn Error>> {

        let mut buf: [u8;1]= [0];
        payload.encode_utf8(&mut buf);

        if let Err(er) = self.write_u8s(&buf) {
            let e = format!("{:?} <- write_char()", er);
            eprintln!("{}",e);
            return Err(e.into());
        }

        Ok(())
    }

//=====================================================================================================
pub fn write_u8s(&mut self, payload: &[u8]) -> Result<(), Box<dyn Error>> {

    if let Err(er) = self.m_port.write(payload){
        let e = format!("Error: {:?} <- write() <- write_u8s()", er);
        eprintln!("{}",e);
        return Err(e.into());
    }

    Ok(())
}

//=====================================================================================================
    pub fn read_buffer(&mut self, len: usize) -> Result<Vec<u8>, Box<dyn Error>> {

        let mut buffer: Vec<u8> = vec![0; len];

        match self.m_port.read(buffer.as_mut_slice()) {
            Ok(n) => {
                Ok(buffer[0..n].to_vec())
            },
            Err(ref er) if er.kind() == std::io::ErrorKind::TimedOut => {
                let e = format!("Error: Timeout <- read() <- read_buffer()");
                eprintln!("{}",e);
                return Err(e.into());
            },
            Err(er) => {
                let e = format!("Error: {} <- read() <- read_buffer()", er);
                eprintln!("{}",e);
                return Err(e.into());
            }
        }
    }

//=====================================================================================================
    pub fn read_buffer_string(&mut self, len: usize) -> Result<String, Box<dyn Error>> {
        match self.read_buffer(len) {
            Ok(buffer) => {
                let buffer_str = match str::from_utf8(&buffer){
                    Ok(s) => s.to_string(),
                    Err(er) => {
                        let e = format!("Error: {}, read_buffer_string()", er);
                        eprintln!("{}",e);
                        return Err(e.into());
                    }
                };
                
                return Ok(buffer_str);
            },
            Err(er) => {
                let e = format!("{:?} <- read_buffer_string()", er);
                eprintln!("{}",e);
                return Err(e.into());
            }
        };
    }
}


impl Serial {

//=====================================================================================================
    pub fn list_ports() -> Result<(), Box<dyn Error>> {
        match available_ports() {
            Ok(ports) => {
                match ports.len() {
                    0 => println!("== 0 ports =="),
                    1 => println!("== 1 Port ==:"),
                    n => println!("== {} Ports ==:", n),
                }

                for p in ports {
                    println!("{}", p.port_name);
                }

                println!("=============");
            },
            Err(er) => {
                let e = format!("Error: {:?}, available_ports() <- list_ports()", er);
                eprintln!("{}",e);
                return Err(e.into());
            }
        }

        Ok(())
    }

//=====================================================================================================
    pub fn check_port(portname: &String) -> Result<PortVisibility, Box<dyn Error>> {
        match available_ports() {
            Ok(ports) => {
                for p in ports {
                    if p.port_name == *portname {
                        return Ok(PortVisibility::Found);
                    }
                }
            },
            Err(er) => {
                let e = format!("Error: {:?}, available_ports() <- check_port()", er);
                eprintln!("{}",e);
                return Err(e.into());
            }
        };

        Ok(PortVisibility::NotFound)
    }

//=====================================================================================================
    pub fn clone(source_port: &Serial) -> Result<Self, Box<dyn Error>> {
        let temp_port = match source_port.m_port.try_clone(){
            Ok(port) => port,
            Err(er) => {
                let e = format!("Error: {:?}, try_clone() <- close()", er);
                eprintln!("{}",e);
                return Err(e.into());
            }
        };

        Ok(
        Serial{
            m_portname : source_port.m_portname.clone(),
            m_baudrate: source_port.m_baudrate,
            m_timeout: source_port.m_timeout,
            m_port: temp_port,
        })
    }
}


