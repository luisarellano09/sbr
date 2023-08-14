"use client";

import {Chip} from "@nextui-org/react";
import {Spinner} from "@nextui-org/react";
import {gql, useQuery} from  "@apollo/client";

const GET_ESP32_LIVE_IMU = gql`
query{
    GetEsp32LiveIMU{
    pitch,
    roll,
    yaw
  }
}
`

export default function IMU() {
    const {data, error, loading} = useQuery(GET_ESP32_LIVE_IMU, {
        pollInterval:500
    });
    console.log(data);
    return(
        <main>
            {loading && <Spinner className="p-3" label="Loading..." size="sm" color="primary" labelColor="primary" />}
            {error && <div className="flex p-5"> <Chip color="danger">Error</Chip> </div>}
            {data && <div className="flex flex-col gap-3 p-5">
                <Chip size="md" variant="bordered" color="success" startContent={<p>Pitch: </p>}> {data.GetEsp32LiveIMU.pitch.toFixed(2)}</Chip>
                <Chip variant="bordered" color="success" startContent={<p>Roll: </p>}> {data.GetEsp32LiveIMU.roll.toFixed(2)}</Chip>
                <Chip variant="bordered" color="success" startContent={<p>Yaw: </p>}> {data.GetEsp32LiveIMU.yaw.toFixed(2)}</Chip>
            </div>
            }
            
            
        </main>
    );
}
