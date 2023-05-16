
use juniper::GraphQLObject;


#[derive(Debug, Clone, GraphQLObject)]
///a user
pub struct User {
    ///the id
    pub id: i32,
    ///the name
    pub name: String,
}