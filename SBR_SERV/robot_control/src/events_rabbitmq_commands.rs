use std::{error::Error, sync::mpsc::Sender};
use amiquip::{Connection, ExchangeDeclareOptions, ExchangeType, QueueDeclareOptions, FieldTable, ConsumerOptions, ConsumerMessage};
use std::env;

use crate::{type_command::Command, type_event::{RobotEvent, RobotCommand}};


//=====================================================================================================
const URL: &str = "amqp://RABBITMQ_USER:RABBITMQ_PASS@RABBITMQ_HOST:5672/";


//=====================================================================================================
pub struct EventsRabbitmqCommands {
    sender_events: Sender<RobotEvent>,
}


//=====================================================================================================
impl EventsRabbitmqCommands {

    //=====================================================================================================
    pub fn new(sender_events: Sender<RobotEvent>) -> Self {
        EventsRabbitmqCommands {
            sender_events: sender_events,
        }
    }

    
    //=====================================================================================================
    pub fn run(&mut self) -> Result<(), Box<dyn Error>> {

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
            "SBR_EXCH_ROBOT_COMMANDS",
            ExchangeDeclareOptions{
                durable: false,
                auto_delete: false,
                internal: false,
                ..Default::default()
            },
        )?;

        // Queue name
        let queue_name = "Q_SBR_COMMANDS_TO_ROBOT_CONTROL";

        // Declare the exclusive, server-named queue 
        let queue = channel.queue_declare(
            queue_name,
            QueueDeclareOptions {
                exclusive: true,
                ..QueueDeclareOptions::default()
            },
        )?;

        //Binding
        queue.bind(&exchange, "COMMAND.ROBOT_CONTROL.#", FieldTable::new())?;

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
                    match serde_json::from_str::<Command>(&body){
                        Ok(cmd) =>{
                            self.handle_command(cmd)?;
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
    pub fn handle_command(&mut self, cmd: Command) -> Result<(), Box<dyn Error>> {
        match cmd.name.as_str(){
            "ROBOT_START" => {
               self.sender_events.send(RobotEvent::Command(RobotCommand::RobotStart))?;
            },
            "ROBOT_STOP" => {
                self.sender_events.send(RobotEvent::Command(RobotCommand::RobotStop))?;
            },
            "ROBOT_PAUSE" => {
                self.sender_events.send(RobotEvent::Command(RobotCommand::RobotPause))?;
            },
            _ => {}
        }

        Ok(())
    }

}
