use std::{error::Error, sync::mpsc::Sender};
use amiquip::{Connection, ExchangeDeclareOptions, ExchangeType, QueueDeclareOptions, FieldTable, ConsumerOptions, ConsumerMessage};
use std::env;

use crate::type_heartbeat_message::HeartbeatMessage;


//=====================================================================================================
const URL: &str = "amqp://RABBITMQ_USER:RABBITMQ_PASS@RABBITMQ_HOST:5672/";


//=====================================================================================================
pub struct RabbitmqHeartbeats {
    sender_hearbeats: Sender<HeartbeatMessage>,
}


//=====================================================================================================
impl RabbitmqHeartbeats {

    //=====================================================================================================
    pub fn new(sender_hearbeats: Sender<HeartbeatMessage>) -> Self {
        RabbitmqHeartbeats {
            sender_hearbeats: sender_hearbeats,
        }
    }

    
    //=====================================================================================================
    pub fn run(&self) -> Result<(), Box<dyn Error>> {

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
        let exchange_esp32 = channel.exchange_declare(
            ExchangeType::Topic,
            "SBR_EXCH_READ_ESP32",
            ExchangeDeclareOptions{
                durable: false,
                auto_delete: false,
                internal: false,
                ..Default::default()
            },
        )?;

        // Declare the queue
        let queue = channel.queue_declare(
            "Q_HEARTBEATS_TO_ROBOT_CONTROL",
            QueueDeclareOptions {
                exclusive: true,
                ..QueueDeclareOptions::default()
            },
        )?;

        // Bindings
        queue.bind(&exchange_esp32, "ESP32.READ.STATUS.HEARTBEAT", FieldTable::new())?;

        // Start a consumer
        let consumer = queue.consume(ConsumerOptions {
            no_ack: true,
            ..ConsumerOptions::default()
        })?;

        // Loop wait for messages
        for (_, message) in consumer.receiver().iter().enumerate() {
            match message {
                ConsumerMessage::Delivery(delivery) => {
                    let body = String::from_utf8_lossy(&delivery.body).to_string();
                    match serde_json::from_str::<HeartbeatMessage>(&body){
                        Ok(msg) =>{
                            self.handle_message(msg)?;
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
        
        Ok(())
    }


    //=====================================================================================================
    pub fn handle_message(&self, msg: HeartbeatMessage) -> Result<(), Box<dyn Error>> {

        self.sender_hearbeats.send(msg)?;

        Ok(())
    }

}
