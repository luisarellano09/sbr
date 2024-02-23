"use client"

import { useStoreWeb } from "@/store/store";
import { useEffect } from "react";

export default function Graphql() {

    const hostName = useStoreWeb((state) => state.hostName);
    const SetCurrentPage = useStoreWeb((state) => state.SetCurrentPage);

    useEffect(()=>{
        SetCurrentPage("Utilities - GraphQL");
    },[]);

    return (
        <div>
            <iframe src={"https://" + hostName + "/sbr_serv_graphql_playground/"} className="w-[100%] h-[100vh]"/>
        </div>
    );
}
