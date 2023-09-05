"use client"

import { useStoreWeb } from "@/store/store";

export default function Portainer() {

    const hostName = useStoreWeb((state) => state.hostName);

    return (
        <div>
            <iframe src={"https://" + hostName+ "/sbr_portainer/"} className="w-[100%] h-[100vh]"/>
        </div>
    );
}
