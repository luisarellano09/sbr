use std::error::Error;
use ::reqwest::blocking::Client;
use graphql_client::{reqwest::post_graphql_blocking, GraphQLQuery};
use std::env;


//=====================================================================================================
const URL: &str = "http://GRAPHQL_HOST:4000/graphql";


//=====================================================================================================
#[derive(GraphQLQuery)]
#[graphql(
    schema_path = "src/graphql/schema.json",
    query_path = "src/graphql/queries.graphql",
    response_derives = "Serialize",
)]
pub struct GetEsp32Status;

pub fn query_get_esp32_status(graphql_client: &Client) -> Result<self::get_esp32_status::GetEsp32StatusGetEsp32Status, Box<dyn Error>>{
    let response_body = post_graphql_blocking::<GetEsp32Status, _>(
        graphql_client, 
        URL.replace("GRAPHQL_HOST", env::var("GRAPHQL_HOST")?.as_str()), 
        self::get_esp32_status::Variables 
    ).unwrap();

    Ok(response_body.data.unwrap().get_esp32_status)
}


//=====================================================================================================
#[derive(GraphQLQuery)]
#[graphql(
    schema_path = "src/graphql/schema.json",
    query_path = "src/graphql/queries.graphql",
    response_derives = "Serialize",
)]
pub struct GetEsp32ModeNode1SyncData;

pub fn query_get_esp32_mode_node1_sync_data(graphql_client: &Client) -> Result<self::get_esp32_mode_node1_sync_data::RegisterCommand, Box<dyn Error>>{
    let response_body = post_graphql_blocking::<GetEsp32ModeNode1SyncData, _>(
        graphql_client, 
        URL.replace("GRAPHQL_HOST", env::var("GRAPHQL_HOST")?.as_str()),
        self::get_esp32_mode_node1_sync_data::Variables 
    ).unwrap();

    Ok(response_body.data.unwrap().get_esp32_mode_node1_sync_data)
}


//=====================================================================================================
#[derive(GraphQLQuery)]
#[graphql(
    schema_path = "src/graphql/schema.json",
    query_path = "src/graphql/queries.graphql",
    response_derives = "Serialize",
)]
pub struct GetEsp32LiveIMU;

pub fn query_get_esp32_live_imu(graphql_client: &Client) -> Result<self::get_esp32_live_imu::GetEsp32LiveImuGetEsp32LiveImu, Box<dyn Error>>{
    let response_body = post_graphql_blocking::<GetEsp32LiveIMU, _>(
        graphql_client, 
        URL.replace("GRAPHQL_HOST", env::var("GRAPHQL_HOST")?.as_str()),
        self::get_esp32_live_imu::Variables 
    ).unwrap();

    Ok(response_body.data.unwrap().get_esp32_live_imu)
}

//==========================================================================================================================================
//==========================================================================================================================================


//=====================================================================================================
#[derive(GraphQLQuery)]
#[graphql(
    schema_path = "src/graphql/schema.json",
    query_path = "src/graphql/mutations.graphql",
    response_derives = "Serialize",
)]
pub struct LoadEsp32Setup;

pub fn mutation_load_esp32_setup(graphql_client: &Client) -> Result<bool, Box<dyn Error>>{
    let response_body = post_graphql_blocking::<LoadEsp32Setup, _>(
        graphql_client, 
        URL.replace("GRAPHQL_HOST", env::var("GRAPHQL_HOST")?.as_str()),
        self::load_esp32_setup::Variables 
    ).unwrap();

    Ok(response_body.data.unwrap().load_esp32_setup)
}


//=====================================================================================================
#[derive(GraphQLQuery)]
#[graphql(
    schema_path = "src/graphql/schema.json",
    query_path = "src/graphql/mutations.graphql",
    response_derives = "Serialize",
)]
pub struct SetEsp32ModeNode1Start;

pub fn mutation_set_esp32_mode_node1_start(graphql_client: &Client) -> Result<bool, Box<dyn Error>>{
    let response_body = post_graphql_blocking::<SetEsp32ModeNode1Start, _>(
        graphql_client, 
        URL.replace("GRAPHQL_HOST", env::var("GRAPHQL_HOST")?.as_str()),
        self::set_esp32_mode_node1_start::Variables 
    ).unwrap();

    Ok(response_body.data.unwrap().set_esp32_mode_node1_start)
}


//=====================================================================================================
#[derive(GraphQLQuery)]
#[graphql(
    schema_path = "src/graphql/schema.json",
    query_path = "src/graphql/mutations.graphql",
    response_derives = "Serialize",
)]
pub struct SetEsp32ModeNode1Stop;

pub fn mutation_set_esp32_mode_node1_stop(graphql_client: &Client) -> Result<bool, Box<dyn Error>>{
    let response_body = post_graphql_blocking::<SetEsp32ModeNode1Stop, _>(
        graphql_client, 
        URL.replace("GRAPHQL_HOST", env::var("GRAPHQL_HOST")?.as_str()),
        self::set_esp32_mode_node1_stop::Variables 
    ).unwrap();

    Ok(response_body.data.unwrap().set_esp32_mode_node1_stop)
}


//=====================================================================================================
#[derive(GraphQLQuery)]
#[graphql(
    schema_path = "src/graphql/schema.json",
    query_path = "src/graphql/mutations.graphql",
    response_derives = "Serialize",
)]
pub struct SetEsp32ModeNode1SyncData;

pub fn mutation_set_esp32_mode_node1_sync_data(graphql_client: &Client, cmd: self::set_esp32_mode_node1_sync_data::RegisterCommand) -> Result<bool, Box<dyn Error>>{
    let response_body = post_graphql_blocking::<SetEsp32ModeNode1SyncData, _>(
        graphql_client, 
        URL.replace("GRAPHQL_HOST", env::var("GRAPHQL_HOST")?.as_str()),
        self::set_esp32_mode_node1_sync_data::Variables {
            sync_status: cmd
        }
    ).unwrap();

    Ok(response_body.data.unwrap().set_esp32_mode_node1_sync_data)
}