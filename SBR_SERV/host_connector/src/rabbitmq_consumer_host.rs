#![allow(dead_code)]

use std::error::Error;
use amiquip::{Connection, ExchangeDeclareOptions, ExchangeType, QueueDeclareOptions, FieldTable, ConsumerOptions, ConsumerMessage};


//=====================================================================================================
//const URL: &str = "amqp://rabbitmq:La123456.@sbr_rabbitmq:5672/";
const URL: &str = "amqp://rabbitmq:La123456.@sbrpi.local:5672/";


//=====================================================================================================
pub struct RabbitmqConsumerHost {}


//=====================================================================================================
impl RabbitmqConsumerHost {

    //=====================================================================================================
    pub fn new() -> Self {
        RabbitmqConsumerHost {
            
        }
    }

    
    //=====================================================================================================
    pub fn run(&self)  -> Result<(), Box<dyn Error>> {
        // Open connection.
        let mut connection = Connection::insecure_open(URL)?;

        // Open a channel - None says let the library choose the channel ID.
        let channel = connection.open_channel(None)?;

        // Declare the exchange we will bind to.
        let exchange = channel.exchange_declare(
            ExchangeType::Topic,
            "SBR_EXCH_HOST_INTERFACE",
            ExchangeDeclareOptions{
                durable: false,
                auto_delete: false,
                internal: false,
                ..Default::default()
            },
        )?;

        // Declare the exclusive, server-named queue we will use to consume.
        let queue = channel.queue_declare(
            "Q_SBR_TO_HOST_CONNECTOR",
            QueueDeclareOptions {
                exclusive: true,
                ..QueueDeclareOptions::default()
            },
        )?;

        //Binding
        //ToDo: Set PI as env Variable in docker compose
        queue.bind(&exchange, "HOST.PI.#", FieldTable::new())?;

        let consumer = queue.consume(ConsumerOptions {
            no_ack: true,
            ..ConsumerOptions::default()
        })?;

        println!("Rabbitmq config done");


        // Loop wait for messages
        println!("Listening for messages");
        for (_, message) in consumer.receiver().iter().enumerate() {
            match message {
                ConsumerMessage::Delivery(delivery) => {
                    let body = String::from_utf8_lossy(&delivery.body).to_string();
                    self.handle_request(body)?;
                }
                other => {
                    println!("Consumer ended: {:?}", other);
                    break;
                }
            }
        }
        
        Ok(())
    }


    //=====================================================================================================
    fn handle_request(&self, request: String)  -> Result<(), Box<dyn Error>> {

        match request.as_str() {
            "SHUTDOWN"=> {
                dbg!("Shutting Down");
            }

            "RESTART"=> {
                dbg!("Shutting Down");
            }

            other =>{
                dbg!(String::from("Command not found: ") + other);
            }
        }


        Ok(())
    }
}
