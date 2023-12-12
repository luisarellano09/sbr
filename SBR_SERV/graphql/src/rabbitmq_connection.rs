use std::error::Error;
use amiquip::{Connection, ExchangeDeclareOptions, ExchangeType, Publish};
use serde_json::json;
use crate::{type_message_esp32::MessageEsp32, type_command::Command};
use std::env;


//=====================================================================================================
const URL: &str = "amqp://RABBITMQ_USER:RABBITMQ_PASS@RABBITMQ_HOST:5672/";


//=====================================================================================================
pub fn publish_esp32_write(key: String, data: i32) -> Result<(), Box<dyn Error>> {

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


//=====================================================================================================
pub fn publish_host_connector(host: String, request: String) -> Result<(), Box<dyn Error>> {

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
        "SBR_EXCH_HOST_CONNECTOR",
        ExchangeDeclareOptions{
            durable: false,
            auto_delete: false,
            internal: false,
            ..Default::default()
        },
    )?;

    let mut key = String::from("HOST.");
    key.push_str(host.as_str());
    key.push_str(".");

    
    exchange.publish(Publish::new(request.as_bytes(), key))?;

    Ok(())
}


//=====================================================================================================
pub fn publish_command(endpoint: String, cmd: Command) -> Result<(), Box<dyn Error>> {

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

    let mut key = String::from("COMMAND.");
    key.push_str(endpoint.as_str());
    key.push_str(".");
    key.push_str(cmd.name.as_str());
    
    exchange.publish(Publish::new(json!(cmd).to_string().as_bytes(), key))?;

    Ok(())
}
