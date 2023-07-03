
use crate::redis_connection::RedisConnection;


//=====================================================================================================
pub struct ContextGraphQL {
  pub redis_connection: RedisConnection,
}

//=====================================================================================================
impl juniper::Context for ContextGraphQL {}


//=====================================================================================================
impl ContextGraphQL{

    //=====================================================================================================
    pub fn new() -> ContextGraphQL {
        ContextGraphQL { 
            redis_connection: RedisConnection::new(),
        }
    }
}