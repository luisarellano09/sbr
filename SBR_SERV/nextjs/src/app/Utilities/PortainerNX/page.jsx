"use client"

import { useStoreWeb } from "@/store/store";
import { useEffect } from "react";

export default function PortainerNX() {

    const hostName = "sbrnx.local";
    const SetCurrentPage = useStoreWeb((state) => state.SetCurrentPage);

    useEffect(()=>{
        SetCurrentPage("Utilities - Portainer NX");
    },[]);

    return (
        <div>
            <iframe src={"http://" + hostName+ ":9000"} className="w-[100%] h-[100vh]"/>
        </div>
    );
}
