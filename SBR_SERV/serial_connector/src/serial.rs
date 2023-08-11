
 #![allow(dead_code)]

use std::{str, collections::VecDeque};
use std::error::Error;
use serialport::{available_ports, SerialPort, SerialPortType, StopBits, Parity, DataBits, ClearBuffer};
use std::time::Duration;


/*******************************************************************************************************************************************
 *  												ENUMS
 *******************************************************************************************************************************************/

/// Enumeration for Port visibility 
pub enum PortVisibility {
    Found,
    NotFound,
}


/*******************************************************************************************************************************************
 *  												Serial
 *******************************************************************************************************************************************/

//=====================================================================================================
/// Serial 
pub struct Serial {
    m_portname: String,
    m_baudrate: u32,
    m_timeout: u64,
    pub m_port: Box<dyn SerialPort>,
    m_buffer: VecDeque<u8>,
}


//=====================================================================================================
impl Serial {

    //=====================================================================================================
    pub fn new(portname: String, baudrate: u32, timeout: u64) -> Result<Self,Box<dyn Error>> {

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

        let mut temp_port = match serialport::new(&portname, baudrate)
            .timeout(Duration::from_millis(timeout))
            .stop_bits(StopBits::One)
            .parity(Parity::None)
            .data_bits(DataBits::Eight)
            .open(){
                Ok(port) => port,
                Err(er) => {
                    let e = format!("Error: {:?} <- open() <- new()", er);
                    eprintln!("{}",e);
                    return Err(e.into());
                }
        };

        temp_port.write_request_to_send(false)?;
        temp_port.clear(ClearBuffer::All)?;
                  
        Ok(Serial{
            m_portname : portname.clone(),
            m_baudrate: baudrate,
            m_timeout: timeout,
            m_port: temp_port,
            m_buffer: VecDeque::new(),
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
    pub fn read_buffer_crc(&mut self, len: usize, crc_error: bool) -> Result<Option<VecDeque<u8>>, Box<dyn Error>> {

        let mut buffer: [u8; 1] = [0];

        match self.m_port.read(&mut buffer) {
            Ok(n) => {
                if crc_error == true {
                    self.m_buffer.pop_front();
                } else if self.m_buffer.len() >= len {
                    self.m_buffer.clear();
                }
                if n ==1 {
                    self.m_buffer.push_back(buffer[0]);
                }

                if self.m_buffer.len() == len {
                    Ok(Some(self.m_buffer.clone()))
                } else {
                    Ok(None)
                }
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

                    match p.port_type {
                        SerialPortType::UsbPort(info) => {
                            println!("    Type: USB");
                            println!("    VID:{:04x} PID:{:04x}", info.vid, info.pid);
                            println!("    Serial Number: {}", info.serial_number.as_ref().map_or("", String::as_str));
                            println!("    Manufacturer: {}", info.manufacturer.as_ref().map_or("", String::as_str));
                            println!("    Product: {}", info.product.as_ref().map_or("", String::as_str));
                        }
                        SerialPortType::BluetoothPort => {
                            println!("    Type: Bluetooth");
                        }
                        SerialPortType::PciPort => {
                            println!("    Type: PCI");
                        }
                        SerialPortType::Unknown => {
                            println!("    Type: Unknown");
                        }
                    }
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
    pub fn get_ports() -> Result<Vec<String>, Box<dyn Error>> {
        match available_ports() {
            Ok(ports) => {
                
                let mut res_ports: Vec<String> = vec![];

                for p in ports {
                    res_ports.push(p.port_name);
                }

                Ok(res_ports)
            },
            Err(er) => {
                let e = format!("Error: {:?}, available_ports() <- list_ports()", er);
                eprintln!("{}",e);
                return Err(e.into());
            }
        }
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


}


