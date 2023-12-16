use serde::{Deserialize, Serialize};

#[derive(Debug, Clone, Deserialize, Serialize)]
pub struct MessageEsp32 {
    pub name: String,
    pub data: f64,
}