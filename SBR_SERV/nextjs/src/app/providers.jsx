'use client'

import {NextUIProvider} from '@nextui-org/react'
import { ApolloClient, HttpLink, InMemoryCache, ApolloProvider} from '@apollo/client';

const client = new ApolloClient({
    cache: new InMemoryCache(),
    link: new HttpLink({
        uri: "http://sbrpi/_sbr_serv_graphql"
    })
});

export function Providers({children}) {
    return (
        <ApolloProvider client={client}>
            <NextUIProvider>
                {children}
            </NextUIProvider>
        </ApolloProvider>
    );
}
