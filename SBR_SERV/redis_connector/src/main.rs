
use std::thread;

mod type_message_esp32;
mod rabbitmq_consumer_esp32;

use rabbitmq_consumer_esp32::RabbitmqConsumerESP32;


//=====================================================================================================
fn main() {

    let mut rabbitmq_consumer_esp32: RabbitmqConsumerESP32 = RabbitmqConsumerESP32::new();

    let thread_rabbitmq_consumer = thread::spawn(move || {
        match rabbitmq_consumer_esp32.run() {
            Ok(_) => {},
            Err(er) => {
                println!("Error in RabbitMQ Consumer ESP32 Thread");
                println!("{}", er);
                std::process::exit(1);
            }
        }
    });


    thread_rabbitmq_consumer.join().expect("Error in thread rabbitmq consumer");
}
