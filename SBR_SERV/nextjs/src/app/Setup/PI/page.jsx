"use client"

import { useStoreWeb } from "@/store/store";
import { useEffect } from "react";

export default function PI() {

    const SetCurrentPage = useStoreWeb((state) => state.SetCurrentPage);

    useEffect(()=>{
        SetCurrentPage("Setup - PI");
    },[]);

    return (
        <div className="h-[calc(100vh-74px)]">
            Setup PI
            
        </div>
    );
}
