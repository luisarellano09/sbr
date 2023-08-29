"use client"

import {Button, Chip, Input, Spinner, Switch} from "@nextui-org/react";

import { GET_DB_ESP32_SETUP, GET_ESP32_SETUP } from "@/graphql/queries";
import {Table, TableHeader, TableColumn, TableBody, TableRow, TableCell} from "@nextui-org/react";

import { useMutation, useQuery} from  "@apollo/client";
import { useEffect, useState } from "react";

import { ArrowPathIcon, ArrowDownCircleIcon, ArrowLeftCircleIcon, ArrowRightCircleIcon } from "@heroicons/react/24/outline";
import { SET_DB_ESP32_SETUP, SET_ESP32_SETUP } from "@/graphql/mutations";

import { toast } from "react-hot-toast";

export default function TablePidTunningPosition() {

    const queryDB = useQuery(GET_DB_ESP32_SETUP);
    const queryRT = useQuery(GET_ESP32_SETUP);

    const [render, setRender] = useState(false);

    const [dbMotionPidPositionKp, setDbMotionPidPositionKp] = useState(0);
    const [rtMotionPidPositionKp, setRtMotionPidPositionKp] = useState(0);

    const [dbMotionPidPositionKi, setDbMotionPidPositionKi] = useState(0);
    const [rtMotionPidPositionKi, setRtMotionPidPositionKi] = useState(0);

    const [dbMotionPidPositionKd, setDbMotionPidPositionKd] = useState(0);
    const [rtMotionPidPositionKd, setRtMotionPidPositionKd] = useState(0);

    const [dbMotionPidPositionDirection, setDbMotionPidPositionDirection] = useState(false);
    const [rtMotionPidPositionDirection, setRtMotionPidPositionDirection] = useState(false);

    const [dbMotionPidPositionMvMin, setDbMotionPidPositionMvMin] = useState(0);
    const [rtMotionPidPositionMvMin, setRtMotionPidPositionMvMin] = useState(0);

    const [dbMotionPidPositionMvMax, setDbMotionPidPositionMvMax] = useState(0);
    const [rtMotionPidPositionMvMax, setRtMotionPidPositionMvMax] = useState(0);


    useEffect(()=>{
        if(queryDB.data != undefined){
            setDbMotionPidPositionKp(queryDB.data.GetDbEsp32Setup.motionPidPosition.kp);
            setDbMotionPidPositionKi(queryDB.data.GetDbEsp32Setup.motionPidPosition.ki);
            setDbMotionPidPositionKd(queryDB.data.GetDbEsp32Setup.motionPidPosition.kd);
            setDbMotionPidPositionDirection(queryDB.data.GetDbEsp32Setup.motionPidPosition.direction);
            setDbMotionPidPositionMvMin(queryDB.data.GetDbEsp32Setup.motionPidPosition.mvMin);
            setDbMotionPidPositionMvMax(queryDB.data.GetDbEsp32Setup.motionPidPosition.mvMax);
        }
    }, [queryDB, render]);


    useEffect(()=>{
        if(queryRT.data != undefined){
            setRtMotionPidPositionKp(queryRT.data.GetEsp32Setup.motionPidPosition.kp);
            setRtMotionPidPositionKi(queryRT.data.GetEsp32Setup.motionPidPosition.ki);
            setRtMotionPidPositionKd(queryRT.data.GetEsp32Setup.motionPidPosition.kd);
            setRtMotionPidPositionDirection(queryRT.data.GetEsp32Setup.motionPidPosition.direction);
            setRtMotionPidPositionMvMin(queryRT.data.GetEsp32Setup.motionPidPosition.mvMin);
            setRtMotionPidPositionMvMax(queryRT.data.GetEsp32Setup.motionPidPosition.mvMax);
        }
    }, [queryRT, render]);


    const Refresh = ()=>{
        queryDB.refetch();
        queryRT.refetch();
        setTimeout(()=>{
            setRender(!render);
        }, 300);
    }

    const RefreshAfterLoading = ()=>{
        setTimeout(()=>{
            Refresh();
        }, 300);
    }

    const HandleSetDbESP32Setup = (setup)=>{
        setDbESP32Setup({
            variables: {setup: setup}, 
            onCompleted: ()=> toast.success("Successfully loaded in DB: " + JSON.stringify(setup)),
            onError: (e)=> toast.error(e.message + ": " + e.networkError.result.errors[0].message),
        });
        RefreshAfterLoading();
    }

    const HandleSetRtESP32Setup = (setup)=>{
        setESP32Setup({
            variables: {setup: setup}, 
            onCompleted: ()=> toast.success("Successfully loaded in RT: " + JSON.stringify(setup)),
            onError: (e)=> toast.error(e.message + ": " + e.networkError.result.errors[0].message),
        });
        RefreshAfterLoading();
    }

    const [setDbESP32Setup] = useMutation(SET_DB_ESP32_SETUP);
    const [setESP32Setup] = useMutation(SET_ESP32_SETUP);
    

	return (
		<div className="md:max-w-xl max-w-[410px] md:pl-2 p-1">
            <Button size="sm" variant="light" isIconOnly onClick={Refresh}> <ArrowPathIcon className="w-5"/> </Button>
			<Table isHeaderSticky aria-label="Setup ESP32" className="max-h-[calc(100vh-230px)] overflow">
				<TableHeader>
					<TableColumn><p className="text-lg font-bold text-[#45a089]">PARAMETER</p></TableColumn>
					<TableColumn><p className="text-lg font-bold text-[#45a089]">DB VALUE</p></TableColumn>
					<TableColumn><p className="text-lg font-bold text-[#45a089]">RT VALUE</p></TableColumn>
				</TableHeader>
                {(queryDB.loading || queryRT.loading) && <TableBody emptyContent={<Spinner className="p-3" label="Loading..." size="sm" color="primary" labelColor="primary" />}>{[]}</TableBody>}
                {(queryDB.error || queryRT.error) && <TableBody emptyContent={<div className="content-center"> <Chip variant="flat" color="danger">Error</Chip> </div>}>{[]}</TableBody>}
                {queryDB.data && queryRT.data && 
                    <TableBody>

                        <TableRow>
                            <TableCell>PID Position Kp</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbMotionPidPositionKp} onValueChange={setDbMotionPidPositionKp}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motionPidPositionKp: Number(dbMotionPidPositionKp)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotionPidPositionKp(dbMotionPidPositionKp); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtMotionPidPositionKp} onValueChange={setRtMotionPidPositionKp}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motionPidPositionKp: Number(rtMotionPidPositionKp)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotionPidPositionKp(rtMotionPidPositionKp); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>PID Position Ki</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbMotionPidPositionKi} onValueChange={setDbMotionPidPositionKi}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motionPidPositionKi: Number(dbMotionPidPositionKi)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotionPidPositionKi(dbMotionPidPositionKi); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtMotionPidPositionKi} onValueChange={setRtMotionPidPositionKi}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motionPidPositionKi: Number(rtMotionPidPositionKi)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotionPidPositionKi(rtMotionPidPositionKi); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>PID Position Kd</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbMotionPidPositionKd} onValueChange={setDbMotionPidPositionKd}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motionPidPositionKd: Number(dbMotionPidPositionKd)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotionPidPositionKd(dbMotionPidPositionKd); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtMotionPidPositionKd} onValueChange={setRtMotionPidPositionKd}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motionPidPositionKd: Number(rtMotionPidPositionKd)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotionPidPositionKd(rtMotionPidPositionKd); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>PID Position Direction</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={dbMotionPidPositionDirection} onValueChange={setDbMotionPidPositionDirection}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motionPidPositionDirection: dbMotionPidPositionDirection}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotionPidPositionDirection(dbMotionPidPositionDirection); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={rtMotionPidPositionDirection} onValueChange={setRtMotionPidPositionDirection}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motionPidPositionDirection: rtMotionPidPositionDirection}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotionPidPositionDirection(rtMotionPidPositionDirection); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>PID Position MV min</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbMotionPidPositionMvMin} onValueChange={setDbMotionPidPositionMvMin}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motionPidPositionMvMin: Number(dbMotionPidPositionMvMin)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotionPidPositionMvMin(dbMotionPidPositionMvMin); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtMotionPidPositionMvMin} onValueChange={setRtMotionPidPositionMvMin}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motionPidPositionMvMin: Number(rtMotionPidPositionMvMin)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotionPidPositionMvMin(rtMotionPidPositionMvMin); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>PID Position MV max</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbMotionPidPositionMvMax} onValueChange={setDbMotionPidPositionMvMax}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motionPidPositionMvMax: Number(dbMotionPidPositionMvMax)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotionPidPositionMvMax(dbMotionPidPositionMvMax); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtMotionPidPositionMvMax} onValueChange={setRtMotionPidPositionMvMax}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motionPidPositionMvMax: Number(rtMotionPidPositionMvMax)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotionPidPositionMvMax(rtMotionPidPositionMvMax); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                    </TableBody>
                }
			</Table>
		</div>
	);
}
