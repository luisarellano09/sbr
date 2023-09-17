"use client"

import { useStoreWeb } from "@/store/store";

export default function PortainerNX() {

    const hostName = useStoreWeb((state) => state.hostName);
    const SetCurrentPage = useStoreWeb((state) => state.SetCurrentPage);

    return (
        <div onLoad={SetCurrentPage("Utilities - Portainer NX")} >
            <iframe src={"https://" + hostName+ "/sbr_portainer_nx/"} className="w-[100%] h-[100vh]"/>
        </div>
    );
}
