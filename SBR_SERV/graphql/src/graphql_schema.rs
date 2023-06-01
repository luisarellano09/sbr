
use juniper::{EmptySubscription, RootNode};
use crate::graphql_queries::Queries;
use crate::graphql_mutations::Mutations;
use crate::graphql_context::ContextGraphQL;


//=====================================================================================================
pub type Schema = RootNode<'static, Queries, Mutations, EmptySubscription<ContextGraphQL>>;


//=====================================================================================================
pub fn create_schema() -> Schema {
    Schema::new(
        Queries,
        Mutations,
        EmptySubscription::<ContextGraphQL>::new(),
    )
}