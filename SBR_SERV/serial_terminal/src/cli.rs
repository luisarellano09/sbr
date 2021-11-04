use std::thread;
#[path = "./serial.rs"] mod serial;
use serial::Serial;

use std::io;
use std::io::Read;
use std::io::Write;
use termios::{Termios, TCSANOW, ECHO, ICANON, tcsetattr};


pub fn run(){
    let mut serial1_read: Serial = Serial::new(String::from("/dev/ttyUSB0"), 115200, 3000).unwrap();
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
