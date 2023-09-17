"use client"

import { useStoreWeb } from "@/store/store";

export default function PI() {

    const SetCurrentPage = useStoreWeb((state) => state.SetCurrentPage);

    return (
        <div onLoad={SetCurrentPage("Setup - PI")} className="h-[calc(100vh-74px)]">
            Setup PI
            
        </div>
    );
}
