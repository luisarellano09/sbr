"use client"

import { useStoreWeb } from "@/store/store";

export default function PortainerPI() {

    const hostName = useStoreWeb((state) => state.hostName);

    return (
        <div>
            <iframe src={"https://" + hostName+ "/sbr_portainer_pi/"} className="w-[100%] h-[100vh]"/>
        </div>
    );
}
