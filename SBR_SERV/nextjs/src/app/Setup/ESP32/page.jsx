"use client"

import TableSetupESP32 from "@/components/Tables/TableSetupESP32";
import { useStoreWeb } from "@/store/store";

export default function ESP32() {

    const SetCurrentPage = useStoreWeb((state) => state.SetCurrentPage);

    return (
        <div onLoad={SetCurrentPage("Setup - ESP32")} className="h-[calc(100vh-74px)]">
            <TableSetupESP32 />   
        </div>
    );
}
