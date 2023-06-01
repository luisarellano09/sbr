#![allow(dead_code)]

use amiquip::{Connection, ExchangeDeclareOptions, ExchangeType, Publish};
use serde_json::json;
use std::{sync::mpsc::Receiver, error::Error};
use crate::message_esp32::MessageEsp32;


//=====================================================================================================
pub struct RabbitmqProducer {
    m_receiver_node_producer: Receiver<MessageEsp32>,
}


//=====================================================================================================
impl RabbitmqProducer {
    
    //=====================================================================================================
    pub fn new(receiver_node_producer: Receiver<MessageEsp32>) -> Self {

        RabbitmqProducer {
            m_receiver_node_producer: receiver_node_producer
        }
    }

    
    //=====================================================================================================
    pub fn run(&mut self) -> Result<(), Box<dyn Error>> {
        // Open connection.
        let mut connection = Connection::insecure_open("amqp://rabbitmq:La123456.@sbr_rabbitmq:5672/")?;

        // Open a channel - None says let the library choose the channel ID.
        let channel = connection.open_channel(None)?;

        // Declare the exchange we will bind to.
        let exchange = channel.exchange_declare(
            ExchangeType::Topic,
            "SBR_EXCH_READ_ESP32",
            ExchangeDeclareOptions{
                durable: false,
                auto_delete: false,
                internal: false,
                ..Default::default()
            },
        )?;

        loop{
            match self.m_receiver_node_producer.try_recv() {
                Ok(msg) =>{
                    let message = json!(msg);
                    let routing_key = msg.name;
                    exchange.publish(Publish::new(message.to_string().as_bytes(), routing_key.clone()))?;
                }, 
                Err(_)=>{}
            }
        }
    }
}
