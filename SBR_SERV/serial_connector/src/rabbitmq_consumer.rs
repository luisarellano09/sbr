#![allow(dead_code)]

use amiquip::{Connection, ExchangeDeclareOptions, ExchangeType, QueueDeclareOptions, FieldTable, ConsumerOptions, ConsumerMessage};

use std::{sync::mpsc::Sender, error::Error};

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


    pub fn run(&mut self)  -> Result<(), Box<dyn Error>> {
        // Open connection.
        let mut connection = Connection::insecure_open("amqp://rabbitmq:La123456.@sbr_rabbitmq:5672/")?;

        // Open a channel - None says let the library choose the channel ID.
        let channel = connection.open_channel(None)?;

        // Declare the exchange we will bind to.
        let exchange = channel.exchange_declare(
            ExchangeType::Topic,
            "SBR_EXCH_WRITE_ESP32",
            ExchangeDeclareOptions{
                durable: false,
                auto_delete: false,
                internal: false,
                ..Default::default()
            },
        )?;

        // Declare the exclusive, server-named queue we will use to consume.
        let queue = channel.queue_declare(
            "Q_SBR_WRITE_ESP32",
            QueueDeclareOptions {
                exclusive: true,
                ..QueueDeclareOptions::default()
            },
        )?;

        //Bindiing
        queue.bind(&exchange, "ESP32.WRITE.#", FieldTable::new())?;

        let consumer = queue.consume(ConsumerOptions {
            no_ack: true,
            ..ConsumerOptions::default()
        })?;

        loop{
            for (_, message) in consumer.receiver().iter().enumerate() {
                match message {
                    ConsumerMessage::Delivery(delivery) => {
                        let body = String::from_utf8_lossy(&delivery.body).to_string();
                        match serde_json::from_str::<MessageEsp32>(&body){
                            Ok(json) =>{
                                self.m_sender_consumer_node.send(MessageEsp32 { name: json.name, data: json.data})?;                                
                            }, 
                            Err(er) => {
                                eprintln!("{}", er);
                            }
                        }
                    }
                    other => {
                        println!("Consumer ended: {:?}", other);
                        break;
                    }
                }
            }
        }
    }
}
