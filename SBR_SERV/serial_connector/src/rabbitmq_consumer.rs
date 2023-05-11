#![allow(dead_code)]

use amiquip::{Connection, ExchangeDeclareOptions, ExchangeType, QueueDeclareOptions, FieldTable, ConsumerOptions, ConsumerMessage};
use serde_json::Value;

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
            "SBR_EXCH_WRITE_ESP32",
            ExchangeDeclareOptions{
                durable: false,
                auto_delete: false,
                internal: false,
                ..Default::default()
            },
        ).unwrap();

        // Declare the exclusive, server-named queue we will use to consume.
        let queue = channel.queue_declare(
            "Q_SBR_WRITE_ESP32",
            QueueDeclareOptions {
                exclusive: true,
                ..QueueDeclareOptions::default()
            },
        ).unwrap();

        //Bindiing
        queue.bind(&exchange, "ESP32.WRITE.#", FieldTable::new()).unwrap();

        let consumer = queue.consume(ConsumerOptions {
            no_ack: false,
            ..ConsumerOptions::default()
        }).unwrap();

        loop{

            for (_, message) in consumer.receiver().iter().enumerate() {
                match message {
                    ConsumerMessage::Delivery(delivery) => {
                        let body = String::from_utf8_lossy(&delivery.body).to_string();
                        let json: Value = serde_json::from_str(&body).unwrap();
                        self.m_sender_consumer_node.send(MessageEsp32 { name: json["name"].as_str().unwrap().to_string(), data: json["data"].as_i64().unwrap() as i32}).unwrap();
                        consumer.ack(delivery).unwrap();
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
