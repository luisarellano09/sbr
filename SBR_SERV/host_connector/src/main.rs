use std::thread;

mod rabbitmq_consumer_host;

use rabbitmq_consumer_host::RabbitmqConsumerHost;


//=====================================================================================================
fn main() {

    // Create threads
    let rabbitmq_consumer_host: RabbitmqConsumerHost = RabbitmqConsumerHost::new();

    let thread_rabbitmq_consumer = thread::spawn(move || {
        match rabbitmq_consumer_host.run() {
            Ok(_) => {},
            Err(er) => {
                println!("Error in RabbitMQ Consumer Host Thread");
                println!("{}", er);
                std::process::exit(1);
            }
        }
    });

    thread_rabbitmq_consumer.join().expect("Error in thread rabbitmq consumer");
    
}
