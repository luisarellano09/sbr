#[allow(unused_variables)]
#[allow(dead_code)]

use std::collections::HashMap;

use crate::graphql_types::User;

#[derive(Clone, Default)]
pub struct Database {
    ///this could be a database connection
    pub users: HashMap<i32, User>,
}
impl Database {
    pub fn new() -> Database {
        println!("Database");
        let mut users = HashMap::new();
        users.insert(
            1,
            User {
                id: 1,
                name: "Aron".into(),
            },
        );
        users.insert(
            2,
            User {
                id: 2,
                name: "Bea".into(),
            },
        );
        users.insert(
            3,
            User {
                id: 3,
                name: "Carl".into(),
            },
        );
        users.insert(
            4,
            User {
                id: 4,
                name: "Dora".into(),
            },
        );
        Database { users }
    }
    pub fn get_user(&self, id: &i32) -> Option<&User> {
        self.users.get(id)
    }
}
