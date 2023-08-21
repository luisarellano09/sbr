"use client";

import {Chip} from "@nextui-org/react";
import {Spinner} from "@nextui-org/react";
import {Table, TableHeader, TableColumn, TableBody, TableRow, TableCell} from "@nextui-org/react";

import {useQuery} from  "@apollo/client";
import { GET_ESP32_LIVE_MOTION, POOLING_ESP32_LIVE_TIME } from "@/graphql/queries";

export default function DashboardMotionPosition() {
    const {data, error, loading} = useQuery(GET_ESP32_LIVE_MOTION, {
        pollInterval:POOLING_ESP32_LIVE_TIME,
        fetchPolicy: "no-cache" 
    });
    return(
        <main>
            <div className="grid grid-cols-1 gap-3 p-5">
                <Table hideHeader aria-label="IMU Table" className="w-[220px] text-left">
                    <TableHeader>
                        <TableColumn></TableColumn>
                        <TableColumn></TableColumn>
                    </TableHeader>
                    {loading && <TableBody emptyContent={<Spinner className="p-3" label="Loading..." size="sm" color="primary" labelColor="primary" />}>{[]}</TableBody>}
                    {error && <TableBody emptyContent={<div className="content-center"> <Chip variant="flat" color="danger">Error</Chip> </div>}>{[]}</TableBody>}
                    {data && 
                        <TableBody>
                            <TableRow key="1">
                                <TableCell>SP Position</TableCell>
                                <TableCell className="text-right">
                                    <Chip variant="flat" color="success"> <p className="w-[56px] text-right">{data.GetEsp32LiveMotion.setpointPosition.toFixed(2)} m</p></Chip>
                                </TableCell>
                            </TableRow>
                            <TableRow key="2">
                                <TableCell>Position</TableCell>
                                <TableCell className="text-right">
                                    <Chip variant="flat" color="success"> <p className="w-[56px] text-right">{data.GetEsp32LiveOdometry.distance.toFixed(2)} m</p></Chip>
                                </TableCell>
                            </TableRow>
                        </TableBody>
                    }
                </Table>
            </div>
        </main>
    );
}
