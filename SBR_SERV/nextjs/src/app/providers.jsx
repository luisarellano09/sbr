'use client'

import {NextUIProvider} from '@nextui-org/react'
import { ApolloClient, HttpLink, gql, InMemoryCache, ApolloProvider} from '@apollo/client';

const client = new ApolloClient({
    cache: new InMemoryCache(),
    link: new HttpLink({
        uri: process.env.GRAPHQL_URL || "http://sbrpi/graphql"
    })
});

console.log(process.env.GRAPHQL_URL);

export function Providers({children}) {
    return (
        <ApolloProvider client={client}>
            <NextUIProvider>
                {children}
            </NextUIProvider>
        </ApolloProvider>
    );
}
