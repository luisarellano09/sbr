#![allow(dead_code)]

use std::error::Error;
use amiquip::{Connection, ExchangeDeclareOptions, ExchangeType, QueueDeclareOptions, FieldTable, ConsumerOptions, ConsumerMessage};
use std::fs::File;


//=====================================================================================================
const URL: &str = "amqp://rabbitmq:La123456.@sbr_rabbitmq:5672/";
//const URL: &str = "amqp://rabbitmq:La123456.@sbrpi.local:5672/";
//const HOST: &str = "UBUNTU";
const HOST: &str = "PI";


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
            "SBR_EXCH_HOST_CONNECTOR",
            ExchangeDeclareOptions{
                durable: false,
                auto_delete: false,
                internal: false,
                ..Default::default()
            },
        )?;

        let mut queue_name: String = String::from("Q_SBR_");
        queue_name.push_str(HOST);
        queue_name.push_str("_TO_HOST_CONNECTOR");

        // Declare the exclusive, server-named queue we will use to consume.
        let queue = channel.queue_declare(
            queue_name,
            QueueDeclareOptions {
                exclusive: true,
                ..QueueDeclareOptions::default()
            },
        )?;

        //Binding

        let mut key: String = String::from("HOST.");
        key.push_str(HOST);
        key.push_str(".#");

        //ToDo: Set PI as env Variable in docker compose
        queue.bind(&exchange, key, FieldTable::new())?;

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
                self.create_file("SHUTDOWN")?;
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


    //=====================================================================================================
    fn create_file(&self, file: &str)  -> Result<(), Box<dyn Error>> {

        let mut path: String = String::from("/app/");
        path.push_str(file);

        File::create(path)?;

        Ok(())
    }

}
