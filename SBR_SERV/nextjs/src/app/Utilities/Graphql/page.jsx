"use client"

import { useStoreWeb } from "@/store/store";

export default function Graphql() {

    const hostName = useStoreWeb((state) => state.hostName);
    const SetCurrentPage = useStoreWeb((state) => state.SetCurrentPage);

    return (
        <div onLoad={SetCurrentPage("Utilities - GraphQL")}>
            <iframe src={"https://" + hostName + "/sbr_serv_graphql_playground/"} className="w-[100%] h-[100vh]"/>
        </div>
    );
}
