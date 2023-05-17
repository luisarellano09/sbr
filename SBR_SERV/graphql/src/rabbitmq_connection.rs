use std::error::Error;
use amiquip::{Connection, ExchangeDeclareOptions, ExchangeType, Publish};
use serde_json::json;
use crate::message_esp32::MessageEsp32;


const URL: &str = "amqp://rabbitmq:La123456.@sbrpi.local:5672/";


pub fn publish_esp32_write(key: String, data: i32) -> Result<(), Box<dyn Error>> {

    // Open connection.
    let mut connection = Connection::insecure_open(URL)?;

    // Open a channel - None says let the library choose the channel ID.
    let channel = connection.open_channel(None)?;

    // Declare the exchange we will bind to.
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
    
    let message = json!(MessageEsp32 { name: key.clone(), data: data});
    exchange.publish(Publish::new(message.to_string().as_bytes(), key.clone()))?;

    Ok(())
}
