use std::error::Error;
use async_std::task::spawn;
use async_postgres::connect;
use tokio_postgres::Client;

//=====================================================================================================
const URL: &str = "host=sbr_postgres user=sbr password=La123456.";
//const URL: &str = "host=sbrpi.local user=sbr password=La123456.";


//=====================================================================================================
pub async fn connect_postgres() -> Result<Client, Box<dyn Error>> {

    let (client, conn) = connect(URL.parse()?).await?;
    spawn(conn);

    Ok(client)
}
