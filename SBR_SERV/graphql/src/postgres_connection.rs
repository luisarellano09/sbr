use std::error::Error;
use async_std::task::spawn;
use async_postgres::connect;
use tokio_postgres::Client;
use std::env;


//=====================================================================================================
const URL: &str = "host=POSTGRES_HOST user=POSTGRES_USER password=POSTGRES_PASSWORD";


//=====================================================================================================
pub async fn connect_postgres() -> Result<Client, Box<dyn Error>> {

    let postgres_user = env::var("POSTGRES_USER")?;
    let postgres_password = env::var("POSTGRES_PASSWORD")?;
    let postgres_host = env::var("POSTGRES_HOST")?;

    let url = URL.replace("POSTGRES_HOST", &postgres_host);
    let url = url.replace("POSTGRES_USER", &postgres_user);
    let url = url.replace("POSTGRES_PASSWORD", &postgres_password);

    let (client, conn) = connect(url.parse()?).await?;
    spawn(conn);

    Ok(client)
}
