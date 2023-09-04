use std::{error::Error, fs};
use amiquip::{Connection, ExchangeDeclareOptions, ExchangeType, QueueDeclareOptions, FieldTable, ConsumerOptions, ConsumerMessage};
use std::fs::File;
use std::env;

//=====================================================================================================
const URL: &str = "amqp://rabbitmq:La123456.@HOST:5672/";


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

        let rabbitmq_host = env::var("RABBITMQ_HOST").unwrap_or(String::from("sbrpi.local"));
        let host = env::var("HOST").unwrap_or(String::from("DEV"));

        let url = URL.replace("HOST", &rabbitmq_host);

        // Open connection.
        let mut connection = Connection::insecure_open(url.as_str())?;

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
        queue_name.push_str(&host);
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
        key.push_str(&host);
        key.push_str(".#");


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
                    self.handle_request(body.as_str())?;
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
    fn handle_request(&self, request: &str)  -> Result<(), Box<dyn Error>> {

        println!("Request: {}", request);
        self.create_file(request)?;
        
        Ok(())
    }


    //=====================================================================================================
    fn create_file(&self, file: &str)  -> Result<(), Box<dyn Error>> {

        match fs::create_dir("/app") {
            Ok(_) => {}
            Err(_)=> {}
        }

        let mut path: String = String::from("/app/");
        path.push_str(file);

        match File::create(path) {
            Ok(_) => {}
            Err(_)=> {}
        }

        Ok(())
    }

}
