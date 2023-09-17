"use client"

import { useStoreWeb } from "@/store/store";
import { useEffect } from "react";

export default function PortainerNX() {

    const hostName = useStoreWeb((state) => state.hostName);
    const SetCurrentPage = useStoreWeb((state) => state.SetCurrentPage);

    useEffect(()=>{
        SetCurrentPage("Utilities - Portainer NX");
    },[]);

    return (
        <div>
            <iframe src={"https://" + hostName+ "/sbr_portainer_nx/"} className="w-[100%] h-[100vh]"/>
        </div>
    );
}
