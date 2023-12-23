#![allow(dead_code)]

use amiquip::{Connection, ExchangeDeclareOptions, ExchangeType, QueueDeclareOptions, FieldTable, ConsumerOptions, ConsumerMessage};
use std::{sync::mpsc::Sender, error::Error};
use crate::type_message_esp32::MessageEsp32;
use std::env;


//=====================================================================================================
const URL: &str = "amqp://RABBITMQ_USER:RABBITMQ_PASS@RABBITMQ_HOST:5672/";


//=====================================================================================================
pub struct RabbitmqConsumer {
    m_sender_consumer_node: Sender<MessageEsp32>,
}


//=====================================================================================================
impl RabbitmqConsumer {

    //=====================================================================================================
    pub fn new(sender_consumer_node: Sender<MessageEsp32>) -> Self {
        RabbitmqConsumer {
            m_sender_consumer_node: sender_consumer_node,
        }
    }

    
    //=====================================================================================================
    pub fn run(&mut self)  -> Result<(), Box<dyn Error>> {
        
        let rabbitmq_user = env::var("RABBITMQ_USER")?;
        let rabbitmq_password = env::var("RABBITMQ_PASS")?;
        let rabbitmq_host = env::var("RABBITMQ_HOST")?;

        let url = URL.replace("RABBITMQ_HOST", &rabbitmq_host);
        let url = url.replace("RABBITMQ_USER", &rabbitmq_user);
        let url = url.replace("RABBITMQ_PASS", &rabbitmq_password);

        // Open connection.
        let mut connection = Connection::insecure_open(url.as_str())?;

        // Open a channel - None says let the library choose the channel ID.
        let channel = connection.open_channel(None)?;

        // Declare the exchange
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

        // Declare the queue
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
                    panic!("Consumer ended: {:?}", other);
                }
            }
        }
    }
}
