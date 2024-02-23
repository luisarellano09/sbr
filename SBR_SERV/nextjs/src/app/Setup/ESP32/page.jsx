"use client"

import TableSetupESP32 from "@/components/Tables/TableSetupESP32";
import { useStoreWeb } from "@/store/store";
import { useEffect } from "react";

export default function ESP32() {

    const SetCurrentPage = useStoreWeb((state) => state.SetCurrentPage);

    useEffect(()=>{
        SetCurrentPage("Setup - ESP32");
    },[]);

    return (
        <div className="h-[calc(100vh-74px)]">
            <TableSetupESP32 />   
        </div>
    );
}
