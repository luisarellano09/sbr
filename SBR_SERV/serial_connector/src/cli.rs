#![allow(dead_code)]

use std::thread;
#[path = "./serial.rs"] mod serial;
use serial::Serial;

use std::io;
use std::io::Read;
use std::io::Write;
use termios::{Termios, TCSANOW, ECHO, ICANON, tcsetattr};


pub fn run(){
    let port = String::from("/dev/ttyUSB0");

    let mut serial1_read: Serial = Serial::new(port, 115200, 3000000).unwrap();
    let mut serial1_write: Serial = Serial::clone(&serial1_read).unwrap();

    // Send 
    thread::spawn(move || loop {
        serial1_write.write_char(read_char_terminal() as char).unwrap();
    });

    // Read
    loop {
        match serial1_read.read_buffer_string(1){
            Ok(str) => print!("{}", str),
            Err(er) => eprintln!("{}", er)
        }
    }
}

pub fn read_char_terminal() -> u8 {
    let stdin = 0;
    let termios = Termios::from_fd(stdin).unwrap();
    let mut new_termios = termios.clone();  // make a mutable copy of termios 
    new_termios.c_lflag &= !(ICANON | ECHO); // no echo and canonical mode
    tcsetattr(stdin, TCSANOW, &mut new_termios).unwrap();
    let stdout = io::stdout();
    let mut reader = io::stdin();
    let mut buffer = [0;1];  
    stdout.lock().flush().unwrap();
    reader.read_exact(&mut buffer).unwrap();
    tcsetattr(stdin, TCSANOW, & termios).unwrap();
    buffer[0]
}

fn select_port_terminal() -> String {

    let list_ports: Vec<String>;

    println!("\r\nSelect the serial port:");

    list_ports = Serial::get_ports().unwrap();

    if list_ports.len() < 1 {
        panic!("No ports detected");
    }

    let mut cnt = 0;
    for port in &list_ports{
        println!("{}: {}", cnt, port);
        cnt = cnt+1;
    }

    let mut input_text = String::new();
    io::stdin()
        .read_line(&mut input_text)
        .expect("failed to read from stdin");

    let trimmed = input_text.trim();
    match trimmed.parse::<usize>() {
        Ok(num) => {
            if num < list_ports.len() {
                return list_ports[num].clone();
            }
        },
        Err(..) => {
            
        },
    };

    eprintln!("Wrong option: {}", trimmed);
    String::from("")
}
