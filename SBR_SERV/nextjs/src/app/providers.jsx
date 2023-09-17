'use client'

import {NextUIProvider} from '@nextui-org/react'
import { ApolloClient, HttpLink, InMemoryCache, ApolloProvider} from '@apollo/client';
import { useStoreWeb } from '@/store/store';
import GlobalUpdate, { UpdateESP32Status } from './GlobalUpdate';


export function Providers({children}) {

    const hostName = useStoreWeb((state) => state.hostName);
    const UpdateHost = useStoreWeb((state) => state.UpdateHost);

    UpdateHost();

    const client = new ApolloClient({
        cache: new InMemoryCache(),
        link: new HttpLink({
            uri: "https://" + hostName + "/graphql"
        })
    });

    return (
        <ApolloProvider client={client}>
            <GlobalUpdate />
            <NextUIProvider>
                {children}
            </NextUIProvider>
        </ApolloProvider>
    );
}

