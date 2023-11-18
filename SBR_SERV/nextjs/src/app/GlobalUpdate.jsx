"use client";

import { useEffect } from "react";
import { GET_ESP32_STATUS } from "@/graphql/queries";
import { useQuery } from "@apollo/client";
import { useStoreRobot } from "@/store/store";

export default function GlobalUpdate() {

    CheckNodeStatus();

    return (
        <span>
        </span>
    ); 
                     
}

// Function that is called every 3 seconds to update the status of the nodes
function CheckNodeStatus(){

    const getESP32Status = useQuery(GET_ESP32_STATUS, {
		pollInterval:3000,
        fetchPolicy: "no-cache",
	});

    const UpdateStatusNode = useStoreRobot((state) => state.UpdateStatusNode);
    const CheckHeartbeat = useStoreRobot((state) => state.CheckHeartbeat);
    
    useEffect(() => {
        if (getESP32Status.data != undefined) {
            UpdateStatusNode(
                getESP32Status.data.GetEsp32Status.nodeEsp32, 
                getESP32Status.data.GetEsp32Status.nodeLinux, 
                getESP32Status.data.GetEsp32Status.heartbeat
            );
        }
	}, [getESP32Status.data]);

    useEffect(() => {
        const interval = setInterval(() => {
            CheckHeartbeat();
        }, 6000);
      
        return () => clearInterval(interval);
      }, []);

}
