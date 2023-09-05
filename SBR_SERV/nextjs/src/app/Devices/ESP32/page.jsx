"use client"

import { useStoreWeb } from "@/store/store";

export default function ESP32() {

    const hostName = useStoreWeb((state) => state.hostName);

    return (
        <div>
            <iframe src={"https://" + hostName + ":8182"} className="w-[100%] h-[100vh]"/>
        </div>
    );
}
