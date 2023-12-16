use std::error::Error;
use amiquip::{Connection, ExchangeDeclareOptions, ExchangeType, QueueDeclareOptions, FieldTable, ConsumerOptions, ConsumerMessage};
use std::env;

use crate::type_message_esp32::MessageEsp32;


//=====================================================================================================
const URL: &str = "amqp://RABBITMQ_USER:RABBITMQ_PASS@RABBITMQ_HOST:5672/";


//=====================================================================================================
pub struct RabbitmqConsumerEsp32 {}


//=====================================================================================================
impl RabbitmqConsumerEsp32 {

    //=====================================================================================================
    pub fn new() -> Self {
        RabbitmqConsumerEsp32 {}
    }

    
    //=====================================================================================================
    pub fn run(&self)  -> Result<(), Box<dyn Error>> {

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

        // Queue name
        let queue_name = "Q_SBR_ESP32_TO_ROBOT_CONTROL";

        // Declare the exclusive, server-named queue we will use to consume.
        let queue = channel.queue_declare(
            queue_name,
            QueueDeclareOptions {
                exclusive: true,
                ..QueueDeclareOptions::default()
            },
        )?;

        //Bindings
        //queue.bind(&exchange, "ESP32.READ.LIVE.IMU.#", FieldTable::new())?;
        //queue.bind(&exchange, "ESP32.READ.STATUS.#", FieldTable::new())?;
        queue.bind(&exchange, "ESP32.READ.MODE.NODE1.SYNC_DATA_RW", FieldTable::new())?;

        let consumer = queue.consume(ConsumerOptions {
            no_ack: true,
            ..ConsumerOptions::default()
        })?;


        // Loop wait for messages
        for (_, message) in consumer.receiver().iter().enumerate() {
            match message {
                ConsumerMessage::Delivery(delivery) => {
                    let body = String::from_utf8_lossy(&delivery.body).to_string();
                    match serde_json::from_str::<MessageEsp32>(&body){
                        Ok(json) =>{
                            dbg!(json);
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
        
        Ok(())
    }

}
