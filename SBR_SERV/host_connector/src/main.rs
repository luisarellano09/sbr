
use std::thread;

mod rabbitmq_consumer_host;
use rabbitmq_consumer_host::RabbitmqConsumerHost;


//=====================================================================================================
fn main() {

    let mut rabbitmq_consumer_host: RabbitmqConsumerHost = RabbitmqConsumerHost::new();

    let thread_rabbitmq_consumer = thread::spawn(move || {
        rabbitmq_consumer_host.run().expect("Error in rabbitmq consumer");
    });


    thread_rabbitmq_consumer.join().expect("Error in thread rabbitmq consumer");
    
}
