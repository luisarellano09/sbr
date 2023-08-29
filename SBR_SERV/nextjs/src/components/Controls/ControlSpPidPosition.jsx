"use client"

import { SET_ESP32_MOTION_SP_POSITION } from "@/graphql/mutations";
import { useMutation } from "@apollo/client";
import { ArrowDownCircleIcon } from "@heroicons/react/24/outline";
import { Button, Input, Table, TableHeader, TableColumn, TableBody, TableRow, TableCell } from "@nextui-org/react";
import { useState } from "react";

import { toast } from "react-hot-toast";

export default function ControlSpPidPosition() {

    const [sp, setSp] = useState(0.1);

    const [mutateSP] = useMutation(SET_ESP32_MOTION_SP_POSITION);

    const HandleSetSp= ()=>{
        mutateSP({
            variables: {sp: Number(sp)}, 
            onCompleted: ()=> toast.success("Delta Position SP loaded: " + sp + " m"),
            onError: (e)=> toast.error(e.message + ": " + e.networkError.result.errors[0].message),
        });
    }

    return (
        <div>
            <div className="pl-2 pt-2">
                <Table hideHeader isCompact aria-label="Position SP" className="w-[220px] text-left">
                    <TableHeader>
                        <TableColumn></TableColumn>
                        <TableColumn></TableColumn>
                    </TableHeader>
                        <TableBody>
                            <TableRow key="1">
                                <TableCell>Δ_SP Pos</TableCell>
                                <TableCell>
                                    <div className="flex justify-start">
                                        <Input size="sm" type="number" variant="faded" className="w-[70px]" value={sp} onValueChange={setSp}/>
                                        <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={HandleSetSp}/></Button>
                                    </div>
                                </TableCell>
                            </TableRow>
                        </TableBody>
                </Table>
            </div>
        </div>
    );
}
