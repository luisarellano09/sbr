"use client"

import { useStoreWeb } from "@/store/store";
import { useEffect } from "react";

export default function PortainerPI() {

    const hostName = useStoreWeb((state) => state.hostName);
    const SetCurrentPage = useStoreWeb((state) => state.SetCurrentPage);

    useEffect(()=>{
        SetCurrentPage("Utilities - Portainer PI");
    },[]);

    return (
        <div>
            <iframe src={"http://" + hostName+ ":9000"} className="w-[100%] h-[100vh]"/>
        </div>
    );
}
