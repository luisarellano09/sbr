
use std::thread;
use std::sync::mpsc::channel;

mod serial;
mod node;
mod message_esp32;
mod rabbitmq_consumer;
mod rabbitmq_producer;
mod register_table;
mod request;

use node::Node;
use rabbitmq_consumer::RabbitmqConsumer;
use rabbitmq_producer::RabbitmqProducer;


fn main() {
    let (sender_node_producer, receiver_node_producer) = channel();
    let (sender_consumer_node, receiver_consumer_node)= channel();

    let mut node_linux: Node = Node::new(String::from("/dev/ttyAMA0"), 460800, 3000, sender_node_producer, receiver_consumer_node);
    let mut rabbitmq_consumer: RabbitmqConsumer = RabbitmqConsumer::new(sender_consumer_node);
    let mut rabbitmq_producer: RabbitmqProducer = RabbitmqProducer::new(receiver_node_producer);

    let thread_node_linux = thread::spawn(move || {
        node_linux.run().expect("Error in thread node linux");

    });

    let thread_rabbitmq_consumer = thread::spawn(move || {
        rabbitmq_consumer.run().expect("Error in rabbitmq consumer");
    });

    let thread_rabbitmq_producer = thread::spawn(move || {
        rabbitmq_producer.run().expect("Error in rabbitmq producer");
    });

    thread_node_linux.join().expect("Error in thread node linux");
    thread_rabbitmq_consumer.join().expect("Error in thread rabbitmq consumer");
    thread_rabbitmq_producer.join().expect("Error in thread rabbitmq producer");
    
}
