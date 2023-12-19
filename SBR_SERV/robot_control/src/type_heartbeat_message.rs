use serde::{Deserialize, Serialize};


//=====================================================================================================
#[derive(Debug, Clone, Deserialize, Serialize)]
pub struct HeartbeatMessage {
    pub name: String,
    pub data: f64,
}