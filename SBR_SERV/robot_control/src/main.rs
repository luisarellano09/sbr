
use std::{thread, time};
use std::sync::mpsc::channel;
use dotenv::dotenv;

mod graphql;
mod robot_control;
mod collect_events;
mod rabbitmq_consumer_commands;
mod type_command;
mod rabbitmq_consumer_esp32;
mod type_message_esp32;

use robot_control::RobotControl;
use collect_events::CollectEvents;
use rabbitmq_consumer_commands::RabbitmqConsumerCommands;
use rabbitmq_consumer_esp32::RabbitmqConsumerEsp32;


fn main() {

    dotenv().ok();

    let (sender_control_robot, receiver_collect_events) = channel();

    let mut robot_control = RobotControl::new(receiver_collect_events);
    let mut collect_events = CollectEvents::new(sender_control_robot);
    let mut rabbitmq_consumer_commands = RabbitmqConsumerCommands::new();
    let mut rabbitmq_consumer_esp32 = RabbitmqConsumerEsp32::new();

    let thread_robot_control = thread::spawn(move || {
        loop {
            robot_control.run().expect("Error in Run Robot Control");
        }
    });

    let thread_collect_events = thread::spawn(move || {
        loop {
            collect_events.run().expect("Error collecting events");
            thread::sleep(time::Duration::from_millis(50));
        }
    });

    let thread_listen_commands = thread::spawn(move || {
        loop {
            rabbitmq_consumer_commands.run().expect("Error in RabbitMQ Consumer Commands");
        }
    });

    let thread_listen_esp32 = thread::spawn(move || {
        loop {
            rabbitmq_consumer_esp32.run().expect("Error in RabbitMQ Consumer ESP32");
        }
    });

    thread_robot_control.join().expect("Error in thread robot control");
    thread_collect_events.join().expect("Error in thread collect events");
    thread_listen_commands.join().expect("Error in thread listen commands");
    thread_listen_esp32.join().expect("Error in thread listen esp32");

}
