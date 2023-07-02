
use std::{error::Error, time::Instant};
use async_std::task::spawn;
use async_postgres::connect;
use tokio_postgres::Row;

//=====================================================================================================
//const URL: &str = "host=sbr_postgres user=sbr password=La123456.";
const URL: &str = "host=sbrpi.local user=sbr password=La123456.";


//=====================================================================================================
pub async fn query(statement: &str) -> Result<Vec<Row>, Box<dyn Error>> {
    let start = Instant::now();

    let (client, conn) = connect(URL.parse()?).await?;
    spawn(conn);

    let duration = start.elapsed();

        dbg!(format!("Time connection is: {:?}", duration));

    Ok(client.query(statement, &[]).await?)
}
