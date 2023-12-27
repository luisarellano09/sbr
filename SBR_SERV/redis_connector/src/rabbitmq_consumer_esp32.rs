use std::error::Error;
use amiquip::{Connection, ExchangeDeclareOptions, ExchangeType, QueueDeclareOptions, FieldTable, ConsumerOptions, ConsumerMessage};
use redis::Commands;
use crate::type_message_esp32::MessageEsp32;
use std::env;


//=====================================================================================================
const URL: &str = "amqp://RABBITMQ_USER:RABBITMQ_PASS@RABBITMQ_HOST:5672/";


//=====================================================================================================
pub struct RabbitmqConsumerESP32 {}


//=====================================================================================================
impl RabbitmqConsumerESP32 {

    //=====================================================================================================
    pub fn new() -> Self {
        RabbitmqConsumerESP32 {
            
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
            "Q_SBR_ESP32_TO_REDIS",
            QueueDeclareOptions {
                exclusive: true,
                ..QueueDeclareOptions::default()
            },
        )?;

        //Binding
        queue.bind(&exchange, "ESP32.READ.#", FieldTable::new())?;

        let consumer = queue.consume(ConsumerOptions {
            no_ack: true,
            ..ConsumerOptions::default()
        })?;

        println!("Rabbitmq config done");

        //Redis connection
        let redis_client = redis::Client::open("redis://sbr_redis:6379")?;
        let mut redis_connection = redis_client.get_connection()?;
        println!("Redis config done");

        // Loop wait for messages
        println!("Listening for messages");
        for (_, message) in consumer.receiver().iter().enumerate() {
            match message {
                ConsumerMessage::Delivery(delivery) => {
                    let body = String::from_utf8_lossy(&delivery.body).to_string();
                    match serde_json::from_str::<MessageEsp32>(&body){
                        Ok(json) =>{
                            redis_connection.set(json.name, json.data)?;
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
}
