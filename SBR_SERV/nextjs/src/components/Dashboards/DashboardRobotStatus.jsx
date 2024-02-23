"use client";

import {Chip} from "@nextui-org/react";
import {Spinner} from "@nextui-org/react";
import {Table, TableHeader, TableColumn, TableBody, TableRow, TableCell} from "@nextui-org/react";

import {useQuery} from  "@apollo/client";
import {GET_ROBOT_STATUS} from "@/graphql/queries";

export default function DashboardRobotStatus() {

    const queryRobotState = useQuery(GET_ROBOT_STATUS, {
        variables: {endpoint: "ROBOT_CONTROL", status: "STATE"},
        pollInterval: 1000,
        fetchPolicy: "no-cache"
    });

    const queryRobotEvent = useQuery(GET_ROBOT_STATUS, {
        variables: {endpoint: "ROBOT_CONTROL", status: "EVENT"},
        pollInterval: 1000,
        fetchPolicy: "no-cache"
    });

    return(
        <main>
            <div className="pl-2 pt-2">
                <Table hideHeader isCompact aria-label="ROBOT_STATUS" className="w-[400px] text-left">
                    <TableHeader>
                        <TableColumn></TableColumn>
                        <TableColumn></TableColumn>
                    </TableHeader>
                    {(queryRobotState.loading || queryRobotEvent.loading) && <TableBody emptyContent={<Spinner className="p-3" label="Loading..." size="sm" color="primary" labelColor="primary" />}>{[]}</TableBody>}
                    {(queryRobotState.error || queryRobotEvent.error) && <TableBody emptyContent={<div className="content-center"> <Chip variant="flat" color="danger">Error</Chip> </div>}>{[]}</TableBody>}
                    {(queryRobotState.data && queryRobotEvent.data) && 
                        <TableBody>
                            <TableRow key="1">
                                <TableCell>State</TableCell>
                                <TableCell className="text-right">
                                    <Chip variant="flat" color="success"> <p className="w-[250px] text-right">{queryRobotState.data.GetRobotStatus}</p></Chip>
                                </TableCell>
                            </TableRow>
                            <TableRow key="2">
                                <TableCell>Event</TableCell>
                                <TableCell className="text-right">
                                    <Chip variant="flat" color="warning"> <p className="w-[250px] text-right">{queryRobotEvent.data.GetRobotStatus}</p></Chip>
                                </TableCell>
                            </TableRow>
                        </TableBody>
                    }
                </Table>
            </div>
        </main>
    );
}
