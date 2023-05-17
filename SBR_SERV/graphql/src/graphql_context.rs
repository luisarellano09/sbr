
use crate::redis_connection::RedisConnection;

pub struct ContextGraphQL {
  pub redis_connection: RedisConnection,
}

// To make our Database usable by Juniper, we have to implement a marker trait.
impl juniper::Context for ContextGraphQL {}

impl ContextGraphQL{
    pub fn new() -> ContextGraphQL {
        ContextGraphQL { redis_connection: RedisConnection::new() }
    }
}