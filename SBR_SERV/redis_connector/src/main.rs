
use std::thread;

mod message_esp32;
mod rabbitmq_consumer_esp32;

use rabbitmq_consumer_esp32::RabbitmqConsumerESP32;


//=====================================================================================================
fn main() {

    let mut rabbitmq_consumer_esp32: RabbitmqConsumerESP32 = RabbitmqConsumerESP32::new();

    let thread_rabbitmq_consumer = thread::spawn(move || {
        rabbitmq_consumer_esp32.run().expect("Error in rabbitmq consumer");
    });


    thread_rabbitmq_consumer.join().expect("Error in thread rabbitmq consumer");
    
}
