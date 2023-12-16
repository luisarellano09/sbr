use std::error::Error;
use ::reqwest::blocking::Client;
use graphql_client::{reqwest::post_graphql_blocking, GraphQLQuery};
use std::env;


//=====================================================================================================
const URL: &str = "http://GRAPHQL_HOST:4000/graphql";


//=====================================================================================================
fn get_graphql_url() -> Result<String, Box<dyn Error>> {
    let graphql_url = URL.replace("GRAPHQL_HOST", env::var("GRAPHQL_HOST")?.as_str());
    Ok(graphql_url)    
}


//================================================================================================================================================================================================================
// Queries
//================================================================================================================================================================================================================


//================================================================================================================================================================================================================
// Mutations
//================================================================================================================================================================================================================

//=====================================================================================================
#[derive(GraphQLQuery)]
#[graphql(
    schema_path = "src/graphql/schema.json",
    query_path = "src/graphql/mutations.graphql",
    response_derives = "Serialize",
)]
pub struct LoadEsp32Setup;

pub fn mutation_load_esp32_setup(graphql_client: &Client) -> Result<bool, Box<dyn Error>>{
    let response_body = post_graphql_blocking::<LoadEsp32Setup, _>(graphql_client, get_graphql_url()?, self::load_esp32_setup::Variables)?;

    if let Some(errors) = response_body.errors {
        if let Some(first_error) = errors.first() {
            panic!("{}",first_error.message);
        }
    }

    Ok(response_body.data.expect("Error in feching data from GraphQL").load_esp32_setup)
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
    let response_body = post_graphql_blocking::<SetEsp32ModeNode1Start, _>(graphql_client, get_graphql_url()?, self::set_esp32_mode_node1_start::Variables)?;

    if let Some(errors) = response_body.errors {
        if let Some(first_error) = errors.first() {
            panic!("{}",first_error.message);
        }
    }

    Ok(response_body.data.expect("Error in feching data from GraphQL").set_esp32_mode_node1_start)
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
    let response_body = post_graphql_blocking::<SetEsp32ModeNode1Stop, _>(graphql_client, get_graphql_url()?, self::set_esp32_mode_node1_stop::Variables)?;

    if let Some(errors) = response_body.errors {
        if let Some(first_error) = errors.first() {
            panic!("{}",first_error.message);
        }
    }

    Ok(response_body.data.expect("Error in feching data from GraphQL").set_esp32_mode_node1_stop)
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
    let response_body = post_graphql_blocking::<SetEsp32ModeNode1SyncData, _>(graphql_client, get_graphql_url()?, self::set_esp32_mode_node1_sync_data::Variables {sync_status: cmd})?;

    if let Some(errors) = response_body.errors {
        if let Some(first_error) = errors.first() {
            panic!("{}",first_error.message);
        }
    }

    Ok(response_body.data.expect("Error in feching data from GraphQL").set_esp32_mode_node1_sync_data)
}