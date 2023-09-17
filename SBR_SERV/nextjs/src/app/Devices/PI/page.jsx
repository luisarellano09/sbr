"use client"

import ControlHost from "@/components/Controls/ControlHost";
import { useStoreWeb } from "@/store/store";
import { useEffect } from "react";

export default function PI() {

    const hostName = useStoreWeb((state) => state.hostName);
    const SetCurrentPage = useStoreWeb((state) => state.SetCurrentPage);

    useEffect(()=>{
        SetCurrentPage("Devices - PI");
    },[]);

    return (
        <div className="h-[calc(100vh-74px)] md:flex justify-start">
            <div className="pl-5 pt-5 pb-5">
                <ControlHost host="PI"/>
            </div>
            <iframe src={"https://" + hostName + ":8182"} className="p-5 w-[100%] h-[90%] max-w-7xl"/>
        </div>
    );
}
