"use client";

import {Chip} from "@nextui-org/react";
import {Spinner} from "@nextui-org/react";
import {Table, TableHeader, TableColumn, TableBody, TableRow, TableCell} from "@nextui-org/react";

import {useQuery} from  "@apollo/client";
import { GET_ESP32_LIVE_IMU, POOLING_ESP32_LIVE_TIME } from "@/graphql/queries";

export default function DashboardIMU() {
    const {data, error, loading} = useQuery(GET_ESP32_LIVE_IMU, {
        pollInterval:POOLING_ESP32_LIVE_TIME,
        fetchPolicy: "no-cache" 
    });
    return(
        <main>
            <div className="grid grid-cols-1 gap-3 p-5">
                <Table aria-label="IMU Table" className="w-[190px] text-left">
                    <TableHeader>
                        <TableColumn><p className="font-bold text-xl text-[#2e8335]">IMU</p></TableColumn>
                        <TableColumn></TableColumn>
                    </TableHeader>
                    {loading && <TableBody emptyContent={<Spinner className="p-3" label="Loading..." size="sm" color="primary" labelColor="primary" />}>{[]}</TableBody>}
                    {error && <TableBody emptyContent={<div className="content-center"> <Chip variant="flat" color="danger">Error</Chip> </div>}>{[]}</TableBody>}
                    {data && 
                        <TableBody>
                            <TableRow key="1">
                                <TableCell>Pitch</TableCell>
                                <TableCell>
                                    <Chip variant="flat" color="success"> <p className="w-[45px] text-center"> {data.GetEsp32LiveIMU.pitch.toFixed(2)}° </p></Chip>
                                </TableCell>
                            </TableRow>
                            <TableRow key="2">
                                <TableCell>Roll</TableCell>
                                <TableCell>
                                    <Chip variant="flat" color="success"> <p className="w-[45px] text-center"> {data.GetEsp32LiveIMU.roll.toFixed(2)}° </p></Chip>
                                </TableCell>
                            </TableRow>
                            <TableRow key="3">
                                <TableCell>Yaw</TableCell>
                                <TableCell>
                                    <Chip variant="flat" color="success"> <p className="w-[45px] text-center"> {data.GetEsp32LiveIMU.yaw.toFixed(2)}° </p></Chip>
                                </TableCell>
                            </TableRow>
                        </TableBody>
                    }
                </Table>
            </div>
        </main>
    );
}
