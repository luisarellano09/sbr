"use client"

import { useStoreWeb } from "@/store/store";
import { useEffect } from "react";

export default function NX() {

    const SetCurrentPage = useStoreWeb((state) => state.SetCurrentPage);

    useEffect(()=>{
        SetCurrentPage("Setup - NX");
    },[]);

    return (
        <div className="h-[calc(100vh-74px)]">
            Setup NX
            
        </div>
    );
}
