#![allow(dead_code)]

use amiquip::{Connection, ExchangeDeclareOptions, ExchangeType, Publish};

use std::thread;
use std::time::Duration;
use std::sync::mpsc::Sender;

use crate::message_esp32::MessageEsp32;

pub struct RabbitmqConsumer {
    m_sender_consumer_node: Sender<MessageEsp32>,
}


impl RabbitmqConsumer {

    pub fn new(sender_consumer_node: Sender<MessageEsp32>) -> Self {

        RabbitmqConsumer {
            m_sender_consumer_node: sender_consumer_node,
        }
    }


    pub fn run(&mut self) {
        // Open connection.
        let mut connection = Connection::insecure_open("amqp://rabbitmq:La123456.@sbr_rabbitmq:5672/").unwrap();

        // Open a channel - None says let the library choose the channel ID.
        let channel = connection.open_channel(None).unwrap();

        // Declare the exchange we will bind to.
        let exchange = channel.exchange_declare(
            ExchangeType::Topic,
            "SBR_EX_ESP32",
            ExchangeDeclareOptions{
                durable: false,
                auto_delete: false,
                internal: false,
                ..Default::default()
            },
        ).unwrap();

      
        loop{
            
        }
    }
}
