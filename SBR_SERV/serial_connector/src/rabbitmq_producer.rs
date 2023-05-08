#![allow(dead_code)]

use amiquip::{Connection, ExchangeDeclareOptions, ExchangeType, Publish};

use std::thread;
use std::time::Duration;
use std::sync::mpsc::Receiver;

use crate::message_esp32::MessageEsp32;
use serde_json::{Result, Value, json};

pub struct RabbitmqProducer {
    m_receiver_node_producer: Receiver<MessageEsp32>,
}


impl RabbitmqProducer {

    pub fn new(receiver_node_producer: Receiver<MessageEsp32>) -> Self {

        RabbitmqProducer {
            m_receiver_node_producer: receiver_node_producer
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

            match self.m_receiver_node_producer.try_recv() {
                Ok(msg) =>{
                    let message = json!({
                        "register": msg.register_num,
                        "data": msg.data
                    });
                    let routing_key = "ESP32.RAW".to_string();
                    exchange.publish(Publish::new(message.to_string().as_bytes(), routing_key.clone())).unwrap();
                }, 
                Err(_)=>{}
            }
        }
    }
}
