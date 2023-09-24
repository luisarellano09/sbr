"use client";

import { useEffect } from "react";
import { GET_ESP32_STATUS } from "@/graphql/queries";
import { useQuery } from "@apollo/client";
import { useStoreRobot } from "@/store/store";

export default function GlobalUpdate() {

    const UpdateStatusNode = useStoreRobot((state) => state.UpdateStatusNode);

    const getESP32Status = useQuery(GET_ESP32_STATUS, {
		pollInterval:3000,
        fetchPolicy: "no-cache",
	});

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
        console.log(getESP32Status);
        if (getESP32Status.error != undefined) {
            UpdateStatusNode(false,false,0);
        }
	}, [getESP32Status.error]);


    return (
        <snap>
        </snap>
    ); 
    
}
