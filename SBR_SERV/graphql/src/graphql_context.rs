

use crate::database::Database;


#[derive(Clone)]
pub struct ContextGraphQL {
  pub db: Database,
}

// To make our Database usable by Juniper, we have to implement a marker trait.
impl juniper::Context for ContextGraphQL {}
