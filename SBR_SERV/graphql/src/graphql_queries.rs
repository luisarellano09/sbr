
use juniper::{graphql_object};
use crate::graphql_context::ContextGraphQL;
use crate::graphql_types::User;


// Queries represent the callable funcitons
pub struct Queries;


#[graphql_object(context = ContextGraphQL)]
impl Queries {

    fn api_version() -> String {
        println!("call for aapi version");
        "1.0".to_string()
    }

    fn user(
        context: &ContextGraphQL,
        #[graphql(description = "id of the user")] id: i32,
    ) -> Option<&User> {
        context.db.get_user(&id)
    }

}

