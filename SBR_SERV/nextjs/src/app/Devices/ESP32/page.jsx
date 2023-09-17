"use client"

import ControlESP32Manager from "@/components/Controls/ControlESP32Manager";
import ControlESP32Node01 from "@/components/Controls/ControlESP32Node01";
import { useStoreWeb } from "@/store/store";
import { useEffect } from "react";

export default function ESP32() {

    const SetCurrentPage = useStoreWeb((state) => state.SetCurrentPage);

    useEffect(()=>{
        SetCurrentPage("Devices - ESP32");
    },[]);

    return (
        <div className="flex justify-start flex-wrap h-[calc(100vh-74px)]">
           
            <div className="pl-5 pt-5 pb-5 w-[150px]">
                <ControlESP32Manager />
            </div>
        
            <div className="pl-5 pt-5 pb-5 w-[150px]">
                <ControlESP32Node01 />
            </div>
            
        </div>
    );
}
