"use client"

import { useStoreWeb } from "@/store/store";

export default function NX() {

    const SetCurrentPage = useStoreWeb((state) => state.SetCurrentPage);

    return (
        <div onLoad={SetCurrentPage("Setup - NX")} className="h-[calc(100vh-74px)]">
            Setup NX
            
        </div>
    );
}
