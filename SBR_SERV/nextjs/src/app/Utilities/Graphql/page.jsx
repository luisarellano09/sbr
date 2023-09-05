"use client"

import { useStoreWeb } from "@/store/store";

export default function Graphql() {

    const hostName = useStoreWeb((state) => state.hostName);

    return (
        <div>
            <iframe src={"https://" + hostName + "/sbr_serv_graphql_playground/"} className="w-[100%] h-[100vh]"/>
        </div>
    );
}
