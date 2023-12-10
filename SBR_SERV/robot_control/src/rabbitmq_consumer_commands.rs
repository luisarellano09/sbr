use std::error::Error;
use amiquip::{Connection, ExchangeDeclareOptions, ExchangeType, QueueDeclareOptions, FieldTable, ConsumerOptions, ConsumerMessage};
use std::env;


//=====================================================================================================
const URL: &str = "amqp://RABBITMQ_USER:RABBITMQ_PASS@RABBITMQ_HOST:5672/";


//=====================================================================================================
pub struct RabbitmqConsumerCommands {}


//=====================================================================================================
impl RabbitmqConsumerCommands {

    //=====================================================================================================
    pub fn new() -> Self {
        RabbitmqConsumerCommands {
            
        }
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
            "SBR_EXCH_ROBOT_COMMANDS",
            ExchangeDeclareOptions{
                durable: false,
                auto_delete: false,
                internal: false,
                ..Default::default()
            },
        )?;

        // Queue name
        let queue_name = "Q_SBR_TO_ROBOT_CONTROL";

        // Declare the exclusive, server-named queue we will use to consume.
        let queue = channel.queue_declare(
            queue_name,
            QueueDeclareOptions {
                exclusive: true,
                ..QueueDeclareOptions::default()
            },
        )?;

        //Binding
        let key: String = String::from("COMMAND.#");
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
                    dbg!(&body);
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
