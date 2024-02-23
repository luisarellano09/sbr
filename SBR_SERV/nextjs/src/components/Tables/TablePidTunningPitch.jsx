"use client"

import {Button, Chip, Input, Spinner, Switch} from "@nextui-org/react";

import { GET_DB_ESP32_SETUP, GET_ESP32_SETUP } from "@/graphql/queries";
import {Table, TableHeader, TableColumn, TableBody, TableRow, TableCell} from "@nextui-org/react";

import { useMutation, useQuery} from  "@apollo/client";
import { useEffect, useState } from "react";

import { ArrowPathIcon, ArrowDownCircleIcon, ArrowLeftCircleIcon, ArrowRightCircleIcon } from "@heroicons/react/24/outline";
import { SET_DB_ESP32_SETUP, SET_ESP32_SETUP } from "@/graphql/mutations";

import { toast } from "react-hot-toast";

export default function TablePidTunningPitch() {

    const queryDB = useQuery(GET_DB_ESP32_SETUP, {fetchPolicy: "no-cache"});
    const queryRT = useQuery(GET_ESP32_SETUP, {fetchPolicy: "no-cache"});

    const [render, setRender] = useState(false);

    const [dbMotionPidPitchKp, setDbMotionPidPitchKp] = useState(0);
    const [rtMotionPidPitchKp, setRtMotionPidPitchKp] = useState(0);

    const [dbMotionPidPitchKi, setDbMotionPidPitchKi] = useState(0);
    const [rtMotionPidPitchKi, setRtMotionPidPitchKi] = useState(0);

    const [dbMotionPidPitchKd, setDbMotionPidPitchKd] = useState(0);
    const [rtMotionPidPitchKd, setRtMotionPidPitchKd] = useState(0);

    const [dbMotionPidPitchDirection, setDbMotionPidPitchDirection] = useState(false);
    const [rtMotionPidPitchDirection, setRtMotionPidPitchDirection] = useState(false);

    const [dbMotionPidPitchMvMin, setDbMotionPidPitchMvMin] = useState(0);
    const [rtMotionPidPitchMvMin, setRtMotionPidPitchMvMin] = useState(0);

    const [dbMotionPidPitchMvMax, setDbMotionPidPitchMvMax] = useState(0);
    const [rtMotionPidPitchMvMax, setRtMotionPidPitchMvMax] = useState(0);


    useEffect(()=>{
        if(queryDB.data != undefined){
            setDbMotionPidPitchKp(queryDB.data.GetDbEsp32Setup.motionPidPitch.kp);
            setDbMotionPidPitchKi(queryDB.data.GetDbEsp32Setup.motionPidPitch.ki);
            setDbMotionPidPitchKd(queryDB.data.GetDbEsp32Setup.motionPidPitch.kd);
            setDbMotionPidPitchDirection(queryDB.data.GetDbEsp32Setup.motionPidPitch.direction);
            setDbMotionPidPitchMvMin(queryDB.data.GetDbEsp32Setup.motionPidPitch.mvMin);
            setDbMotionPidPitchMvMax(queryDB.data.GetDbEsp32Setup.motionPidPitch.mvMax);
        }
    }, [queryDB, render]);


    useEffect(()=>{
        if(queryRT.data != undefined){
            setRtMotionPidPitchKp(queryRT.data.GetEsp32Setup.motionPidPitch.kp);
            setRtMotionPidPitchKi(queryRT.data.GetEsp32Setup.motionPidPitch.ki);
            setRtMotionPidPitchKd(queryRT.data.GetEsp32Setup.motionPidPitch.kd);
            setRtMotionPidPitchDirection(queryRT.data.GetEsp32Setup.motionPidPitch.direction);
            setRtMotionPidPitchMvMin(queryRT.data.GetEsp32Setup.motionPidPitch.mvMin);
            setRtMotionPidPitchMvMax(queryRT.data.GetEsp32Setup.motionPidPitch.mvMax);
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
            onError: (e)=> {
                let networkErrorMessage = "";
                try{
                    networkErrorMessage = e.networkError.result.errors[0].message;
                }
                catch{}

                toast.error(e.message + ": " + networkErrorMessage);
            }
        });
        RefreshAfterLoading();
    }

    const HandleSetRtESP32Setup = (setup)=>{
        setESP32Setup({
            variables: {setup: setup}, 
            onCompleted: ()=> toast.success("Successfully loaded in RT: " + JSON.stringify(setup)),
            onError: (e)=> {
                let networkErrorMessage = "";
                try{
                    networkErrorMessage = e.networkError.result.errors[0].message;
                }
                catch{}

                toast.error(e.message + ": " + networkErrorMessage);
            }
        });
        RefreshAfterLoading();
    }

    const [setDbESP32Setup] = useMutation(SET_DB_ESP32_SETUP, {fetchPolicy: "no-cache"});
    const [setESP32Setup] = useMutation(SET_ESP32_SETUP, {fetchPolicy: "no-cache"});
    

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
                            <TableCell>PID Pitch Kp</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbMotionPidPitchKp} onValueChange={setDbMotionPidPitchKp}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motionPidPitchKp: Number(dbMotionPidPitchKp)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotionPidPitchKp(dbMotionPidPitchKp); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtMotionPidPitchKp} onValueChange={setRtMotionPidPitchKp}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motionPidPitchKp: Number(rtMotionPidPitchKp)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotionPidPitchKp(rtMotionPidPitchKp); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>PID Pitch Ki</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbMotionPidPitchKi} onValueChange={setDbMotionPidPitchKi}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motionPidPitchKi: Number(dbMotionPidPitchKi)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotionPidPitchKi(dbMotionPidPitchKi); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtMotionPidPitchKi} onValueChange={setRtMotionPidPitchKi}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motionPidPitchKi: Number(rtMotionPidPitchKi)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotionPidPitchKi(rtMotionPidPitchKi); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>PID Pitch Kd</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbMotionPidPitchKd} onValueChange={setDbMotionPidPitchKd}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motionPidPitchKd: Number(dbMotionPidPitchKd)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotionPidPitchKd(dbMotionPidPitchKd); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtMotionPidPitchKd} onValueChange={setRtMotionPidPitchKd}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motionPidPitchKd: Number(rtMotionPidPitchKd)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotionPidPitchKd(rtMotionPidPitchKd); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>PID Pitch Direction</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={dbMotionPidPitchDirection} onValueChange={setDbMotionPidPitchDirection}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motionPidPitchDirection: dbMotionPidPitchDirection}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotionPidPitchDirection(dbMotionPidPitchDirection); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={rtMotionPidPitchDirection} onValueChange={setRtMotionPidPitchDirection}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motionPidPitchDirection: rtMotionPidPitchDirection}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotionPidPitchDirection(rtMotionPidPitchDirection); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>PID Pitch MV min</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbMotionPidPitchMvMin} onValueChange={setDbMotionPidPitchMvMin}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motionPidPitchMvMin: Number(dbMotionPidPitchMvMin)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotionPidPitchMvMin(dbMotionPidPitchMvMin); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtMotionPidPitchMvMin} onValueChange={setRtMotionPidPitchMvMin}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motionPidPitchMvMin: Number(rtMotionPidPitchMvMin)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotionPidPitchMvMin(rtMotionPidPitchMvMin); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>PID Pitch MV max</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbMotionPidPitchMvMax} onValueChange={setDbMotionPidPitchMvMax}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motionPidPitchMvMax: Number(dbMotionPidPitchMvMax)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotionPidPitchMvMax(dbMotionPidPitchMvMax); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtMotionPidPitchMvMax} onValueChange={setRtMotionPidPitchMvMax}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motionPidPitchMvMax: Number(rtMotionPidPitchMvMax)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotionPidPitchMvMax(rtMotionPidPitchMvMax); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                    </TableBody>
                }
			</Table>
		</div>
	);
}
