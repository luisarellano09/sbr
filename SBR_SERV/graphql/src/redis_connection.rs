
use r2d2::Pool;
use r2d2_redis::{RedisConnectionManager};

pub type RedisPool = Pool<RedisConnectionManager>;


pub struct RedisConnection {
    pub redis_pool: RedisPool,
}

impl RedisConnection {
    pub fn new() -> RedisConnection {
        
        //Redis connection
        //let redis_client = redis::Client::open("redis://sbrpi.local:6379").expect("Failed connecting to Redis DB");
        //let mut connection = redis_client.get_connection().unwrap();
        //println!("Redis config done");

        let manager = RedisConnectionManager::new("redis://sbrpi.local:6379").unwrap();
        
        RedisConnection { redis_pool:  Pool::builder()
            .build(manager)
            .expect("Failed to create Redis connection pool.")}
    }
}
