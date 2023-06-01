
use r2d2_postgres::{postgres::NoTls, PostgresConnectionManager};

//=====================================================================================================
pub type PostgresPool = Pool<PostgresConnectionManager>;


//=====================================================================================================
pub struct RedisConnection {
    pub redis_pool: PostgresPool,
}


//=====================================================================================================
impl RedisConnection {

    //=====================================================================================================
    pub fn new() -> RedisConnection {
        
        let manager = PostgresConnectionManager::new(
            "postgres://username:password@localhost/database",
            NoTls,
        );
        
        let pool = Pool::new(manager)?;

        pool.get()
    }
}
