use r2d2::Pool;
use r2d2_redis::RedisConnectionManager;
use std::env;


//=====================================================================================================
const URL: &str = "redis://REDIS_HOST:6379";


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

        let rabbitmq_host = env::var("REDIS_HOST").expect("env variable missing");

        let url = URL.replace("REDIS_HOST", &rabbitmq_host);
        
        let manager = RedisConnectionManager::new(url).unwrap();
        
        RedisConnection { redis_pool:  Pool::builder()
            .build(manager)
            .expect("Failed to create Redis connection pool.")}
    }
}
