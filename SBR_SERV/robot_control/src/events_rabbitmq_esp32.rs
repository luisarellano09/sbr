use std::{error::Error, sync::mpsc::Sender};
use amiquip::{Connection, ExchangeDeclareOptions, ExchangeType, QueueDeclareOptions, FieldTable, ConsumerOptions, ConsumerMessage};
use std::env;

use crate::{type_message_esp32::MessageEsp32, type_event::RobotEvent};


//=====================================================================================================
const URL: &str = "amqp://RABBITMQ_USER:RABBITMQ_PASS@RABBITMQ_HOST:5672/";


//=====================================================================================================
pub struct EventsRabbitmqEsp32 {
    sender_events: Sender<RobotEvent>,
    connection_esp32_error: bool,
    connection_linux_error: bool,
    robot_falldown: bool,
}


//=====================================================================================================
impl EventsRabbitmqEsp32 {

    //=====================================================================================================
    pub fn new(sender: Sender<RobotEvent>) -> Self {
        EventsRabbitmqEsp32 {
            sender_events: sender,
            connection_esp32_error: false,
            connection_linux_error: false,
            robot_falldown: false,
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

        // Declare the exclusive, server-named queue 
        let queue = channel.queue_declare(
            queue_name,
            QueueDeclareOptions {
                exclusive: true,
                ..QueueDeclareOptions::default()
            },
        )?;

        // Bindings
        queue.bind(&exchange, "ESP32.READ.LIVE.MOTION.FALLDOWN_R", FieldTable::new())?;
        queue.bind(&exchange, "ESP32.READ.STATUS.NODE_ESP32_R", FieldTable::new())?;
        queue.bind(&exchange, "ESP32.READ.STATUS.NODE_LINUX_R", FieldTable::new())?;
        queue.bind(&exchange, "ESP32.READ.MODE.NODE1.SYNC_DATA_RW", FieldTable::new())?;

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
                    match serde_json::from_str::<MessageEsp32>(&body){
                        Ok(msg) =>{
                            self.handle_message(msg)?;
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


    //=====================================================================================================
    pub fn handle_message(&mut self, msg: MessageEsp32) -> Result<(), Box<dyn Error>> {

        match msg.name.as_str(){
            "ESP32.READ.STATUS.NODE_ESP32_R" => {
                if msg.data == 0.0 {
                    if self.connection_esp32_error == false && self.connection_linux_error == false {
                        self.sender_events.send(RobotEvent::ConnectionErrorEsp32)?;
                    }
                    self.connection_esp32_error = true;
                } else if msg.data == 1.0 {
                    if self.connection_esp32_error == true && self.connection_linux_error == false {
                        self.sender_events.send(RobotEvent::ConnectionOkEsp32)?;
                    }
                    self.connection_esp32_error = false;
                }
            },
            "ESP32.READ.STATUS.NODE_LINUX_R" => {
                if msg.data == 0.0 {
                    if self.connection_linux_error == false && self.connection_esp32_error == false {
                        self.sender_events.send(RobotEvent::ConnectionErrorEsp32)?;
                    }
                    self.connection_linux_error = true;
                } else if msg.data == 1.0 {
                    if self.connection_linux_error == true && self.connection_esp32_error == false {
                        self.sender_events.send(RobotEvent::ConnectionOkEsp32)?;
                    }
                    self.connection_linux_error = false;
                }
            },
            "ESP32.READ.MODE.NODE1.SYNC_DATA_RW" => {
                if msg.data == 1.0 {
                    self.sender_events.send(RobotEvent::RequestLoadDataEsp32)?;
                } else if msg.data == 4.0 {
                    self.sender_events.send(RobotEvent::ConfirmLoadDataEsp32)?;
                }
            },
            "ESP32.READ.LIVE.MOTION.FALLDOWN_R" => {
                if msg.data == 1.0 {
                    if self.robot_falldown == false {
                        self.sender_events.send(RobotEvent::RobotFallDown)?;
                    }
                    self.robot_falldown = true;
                } else if msg.data == 0.0 {
                    if self.robot_falldown == true {
                        self.sender_events.send(RobotEvent::RobotStandUp)?;
                    }
                    self.robot_falldown = false;
                }
            },
            _ => {}
        }

        Ok(())
    }

}
