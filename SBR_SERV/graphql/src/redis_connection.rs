
use r2d2::Pool;
use r2d2_redis::{RedisConnectionManager};


//=====================================================================================================
const URL: &str = "redis://sbr_redis:6379";
//const URL: &str = "redis://sbrpi.local:6379";


//=====================================================================================================
pub type RedisPool = Pool<RedisConnectionManager>;


//=====================================================================================================
pub struct RedisConnection {
    pub redis_pool: RedisPool,
}


//=====================================================================================================
impl RedisConnection {

    //=====================================================================================================
    pub fn new() -> RedisConnection {
        
        //let manager = RedisConnectionManager::new("redis://sbr_redis:6379").unwrap();
        let manager = RedisConnectionManager::new(URL).unwrap();
        
        RedisConnection { redis_pool:  Pool::builder()
            .build(manager)
            .expect("Failed to create Redis connection pool.")}
    }
}
