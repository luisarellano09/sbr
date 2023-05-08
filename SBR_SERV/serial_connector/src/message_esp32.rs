
use crate::register_table::COM_REQUEST_REG_ID_e;

#[derive(Debug, Clone, Copy)]
pub struct MessageEsp32 {
    pub register_enum: COM_REQUEST_REG_ID_e,
    pub register_num: u16,
    pub data: i32,
}