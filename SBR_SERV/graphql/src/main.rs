#[allow(warnings)]

use actix_cors::Cors;
use actix_web::{http::header, middleware, web::{self, Data}, App, Error, HttpResponse, HttpServer};
use juniper_actix::{graphiql_handler, graphql_handler, playground_handler};


mod graphql_schema;
mod graphql_context;
mod redis_connection;
mod rabbitmq_connection;
mod graphql_types;
mod graphql_queries;
mod graphql_mutations;
mod message_esp32;

use graphql_schema::{create_schema, Schema};
use graphql_context::ContextGraphQL;

async fn graphiql_route() -> Result<HttpResponse, Error> {
    graphiql_handler("/graphql", None).await
}

async fn playground_route() -> Result<HttpResponse, Error> {
    playground_handler("/graphql", None).await
}

async fn graphql_route(
    req: actix_web::HttpRequest,
    payload: actix_web::web::Payload,
    schema: web::Data<Schema>
) -> Result<HttpResponse, Error> {
    let _req = req.clone();
    let context = _req.app_data::<ContextGraphQL>().expect("Failed to load context");
    graphql_handler(&schema, &context, req, payload).await
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {

    let server = HttpServer::new(move || {
        App::new()
            .app_data(Data::new(create_schema()))
            .app_data(ContextGraphQL::new())
            .wrap(
                Cors::default()
                    .allow_any_origin()
                    .allowed_methods(vec!["POST", "GET"])
                    .allowed_headers(vec![header::AUTHORIZATION, header::ACCEPT])
                    .allowed_header(header::CONTENT_TYPE)
                    .supports_credentials()
                    .max_age(3600),
            )
            .wrap(middleware::Compress::default())
            .wrap(middleware::Logger::default())
            .service(
                web::resource("/graphql")
                    .route(web::post().to(graphql_route))
                    .route(web::get().to(graphql_route)),
            )
            .service(web::resource("/playground").route(web::get().to(playground_route)))
            .service(web::resource("/graphiql").route(web::get().to(graphiql_route)))
    });
    server.bind("0.0.0.0:4000")?.run().await
}
// now go to http://127.0.0.1:8080/playground or graphiql and execute
//{  apiVersion,  user(id: 2){id, name}}