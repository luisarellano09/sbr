
use juniper::{graphql_object};
use crate::graphql_context::ContextGraphQL;
use crate::graphql_types::User;

pub struct Mutations;

#[graphql_object(Context = ContextGraphQL)]
impl Mutations {

  fn CreateUser(context: &ContextGraphQL, key: i32, data: String) -> User {
    let new_user = User { id: key, name: data };
    println!("{}", context.db.users.get(&1).unwrap().name);
    new_user
  }

}