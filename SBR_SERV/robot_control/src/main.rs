
use std::{thread, process};
use std::sync::mpsc::channel;
use dotenv::dotenv;

mod graphql;
mod robot_control;
mod events_rabbitmq_commands;
mod events_rabbitmq_esp32;
mod events_heartbeats;
mod rabbitmq_heartbeats;
mod type_message_esp32;
mod type_state;
mod type_command;
mod type_event;
mod type_heartbeat_message;

use robot_control::RobotControl;
use events_rabbitmq_commands::EventsRabbitmqCommands;
use events_rabbitmq_esp32::EventsRabbitmqEsp32;
use events_heartbeats::EventsHeartbeats;
use rabbitmq_heartbeats::RabbitmqHeartbeats;


fn main() {

    dotenv().ok();

    let (sender_events, receiver_events) = channel();
    let (sender_heartbeats, receiver_heartbeats) = channel();

    let mut robot_control = RobotControl::new(receiver_events);
    let mut events_rabbitmq_commands = EventsRabbitmqCommands::new(sender_events.clone());
    let mut events_rabbitmq_esp32 = EventsRabbitmqEsp32::new(sender_events.clone());
    let rabbitmq_heartbeats = RabbitmqHeartbeats::new(sender_heartbeats.clone());
    let mut events_heartbeats = EventsHeartbeats::new(receiver_heartbeats, sender_events.clone());

    let thread_robot_control = thread::spawn(move || {
        loop {
            match robot_control.run() {
                Ok(_) => {},
                Err(er) => {
                    println!("Error in Robot Control Thread");
                    println!("{}", er);
                    process::exit(1);
                }
            }
        }
    });

    let thread_events_rabbitmq_commands = thread::spawn(move || {
        loop {
            match events_rabbitmq_commands.run() {
                Ok(_) => {},
                Err(er) => {
                    println!("Error in RabbitMQ Consumer Commands Thread");
                    println!("{}", er);
                    process::exit(1);
                }
            }
        }
    });

    let thread_events_rabbitmq_esp32 = thread::spawn(move || {
        loop {
            match events_rabbitmq_esp32.run() {
                Ok(_) => {},
                Err(er) => {
                    println!("Error in RabbitMQ Consumer ESP32 Thread");
                    println!("{}", er);
                    process::exit(1);
                }
            }
        }
    });

    let thread_rabbitmq_heartbeats = thread::spawn(move || {
        loop {
            match rabbitmq_heartbeats.run() {
                Ok(_) => {},
                Err(er) => {
                    println!("Error in RabbitMQ Heartbeats Thread");
                    println!("{}", er);
                    process::exit(1);
                }
            }
        }
    });

    let thread_events_heartbeats = thread::spawn(move || {
        loop {
            match events_heartbeats.run() {
                Ok(_) => {},
                Err(er) => {
                    println!("Error in Events Heartbeats Thread");
                    println!("{}", er);
                    process::exit(1);
                }
            }
        }
    });

    thread_robot_control.join().expect("Error in thread robot control");
    thread_events_rabbitmq_commands.join().expect("Error in thread listen commands");
    thread_events_rabbitmq_esp32.join().expect("Error in thread listen esp32");
    thread_rabbitmq_heartbeats.join().expect("Error in thread rabbitmq heartbeats");
    thread_events_heartbeats.join().expect("Error in thread events heartbeats");

}
