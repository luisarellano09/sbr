use serde::{Deserialize, Serialize};


//=====================================================================================================
#[derive(Debug, Clone, Deserialize, Serialize)]
pub struct Command {
    pub name: String,
    pub value_bool: bool,
    pub value_int: i32,
    pub value_float: f64,
    pub value_string: String,
}