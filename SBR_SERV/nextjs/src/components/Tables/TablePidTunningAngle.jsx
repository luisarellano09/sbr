"use client"

import {Button, Chip, Input, Spinner, Switch} from "@nextui-org/react";

import { GET_DB_ESP32_SETUP, GET_ESP32_SETUP } from "@/graphql/queries";
import {Table, TableHeader, TableColumn, TableBody, TableRow, TableCell} from "@nextui-org/react";

import { useMutation, useQuery} from  "@apollo/client";
import { useEffect, useState } from "react";

import { ArrowPathIcon, ArrowDownCircleIcon, ArrowLeftCircleIcon, ArrowRightCircleIcon } from "@heroicons/react/24/outline";
import { SET_DB_ESP32_SETUP, SET_ESP32_SETUP } from "@/graphql/mutations";

import { toast } from "react-hot-toast";

export default function TablePidTunningAngle() {

    const queryDB = useQuery(GET_DB_ESP32_SETUP, {fetchPolicy: "no-cache"});
    const queryRT = useQuery(GET_ESP32_SETUP, {fetchPolicy: "no-cache"});

    const [render, setRender] = useState(false);

    const [dbMotionPidAngleKp, setDbMotionPidAngleKp] = useState(0);
    const [rtMotionPidAngleKp, setRtMotionPidAngleKp] = useState(0);

    const [dbMotionPidAngleKi, setDbMotionPidAngleKi] = useState(0);
    const [rtMotionPidAngleKi, setRtMotionPidAngleKi] = useState(0);

    const [dbMotionPidAngleKd, setDbMotionPidAngleKd] = useState(0);
    const [rtMotionPidAngleKd, setRtMotionPidAngleKd] = useState(0);

    const [dbMotionPidAngleDirection, setDbMotionPidAngleDirection] = useState(false);
    const [rtMotionPidAngleDirection, setRtMotionPidAngleDirection] = useState(false);

    const [dbMotionPidAngleMvMin, setDbMotionPidAngleMvMin] = useState(0);
    const [rtMotionPidAngleMvMin, setRtMotionPidAngleMvMin] = useState(0);

    const [dbMotionPidAngleMvMax, setDbMotionPidAngleMvMax] = useState(0);
    const [rtMotionPidAngleMvMax, setRtMotionPidAngleMvMax] = useState(0);


    useEffect(()=>{
        if(queryDB.data != undefined){
            setDbMotionPidAngleKp(queryDB.data.GetDbEsp32Setup.motionPidAngle.kp);
            setDbMotionPidAngleKi(queryDB.data.GetDbEsp32Setup.motionPidAngle.ki);
            setDbMotionPidAngleKd(queryDB.data.GetDbEsp32Setup.motionPidAngle.kd);
            setDbMotionPidAngleDirection(queryDB.data.GetDbEsp32Setup.motionPidAngle.direction);
            setDbMotionPidAngleMvMin(queryDB.data.GetDbEsp32Setup.motionPidAngle.mvMin);
            setDbMotionPidAngleMvMax(queryDB.data.GetDbEsp32Setup.motionPidAngle.mvMax);
        }
    }, [queryDB, render]);


    useEffect(()=>{
        if(queryRT.data != undefined){
            setRtMotionPidAngleKp(queryRT.data.GetEsp32Setup.motionPidAngle.kp);
            setRtMotionPidAngleKi(queryRT.data.GetEsp32Setup.motionPidAngle.ki);
            setRtMotionPidAngleKd(queryRT.data.GetEsp32Setup.motionPidAngle.kd);
            setRtMotionPidAngleDirection(queryRT.data.GetEsp32Setup.motionPidAngle.direction);
            setRtMotionPidAngleMvMin(queryRT.data.GetEsp32Setup.motionPidAngle.mvMin);
            setRtMotionPidAngleMvMax(queryRT.data.GetEsp32Setup.motionPidAngle.mvMax);
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
		<div className="md:max-w-2xl max-w-[410px] md:pl-2 p-1">
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
                            <TableCell>PID Angle Kp</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbMotionPidAngleKp} onValueChange={setDbMotionPidAngleKp}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motionPidAngleKp: Number(dbMotionPidAngleKp)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotionPidAngleKp(dbMotionPidAngleKp); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtMotionPidAngleKp} onValueChange={setRtMotionPidAngleKp}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motionPidAngleKp: Number(rtMotionPidAngleKp)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotionPidAngleKp(rtMotionPidAngleKp); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>PID Angle Ki</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbMotionPidAngleKi} onValueChange={setDbMotionPidAngleKi}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motionPidAngleKi: Number(dbMotionPidAngleKi)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotionPidAngleKi(dbMotionPidAngleKi); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtMotionPidAngleKi} onValueChange={setRtMotionPidAngleKi}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motionPidAngleKi: Number(rtMotionPidAngleKi)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotionPidAngleKi(rtMotionPidAngleKi); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>PID Angle Kd</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbMotionPidAngleKd} onValueChange={setDbMotionPidAngleKd}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motionPidAngleKd: Number(dbMotionPidAngleKd)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotionPidAngleKd(dbMotionPidAngleKd); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtMotionPidAngleKd} onValueChange={setRtMotionPidAngleKd}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motionPidAngleKd: Number(rtMotionPidAngleKd)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotionPidAngleKd(rtMotionPidAngleKd); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>PID Angle Direction</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={dbMotionPidAngleDirection} onValueChange={setDbMotionPidAngleDirection}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motionPidAngleDirection: dbMotionPidAngleDirection}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotionPidAngleDirection(dbMotionPidAngleDirection); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={rtMotionPidAngleDirection} onValueChange={setRtMotionPidAngleDirection}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motionPidAngleDirection: rtMotionPidAngleDirection}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotionPidAngleDirection(rtMotionPidAngleDirection); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>PID Angle MV min</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbMotionPidAngleMvMin} onValueChange={setDbMotionPidAngleMvMin}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motionPidAngleMvMin: Number(dbMotionPidAngleMvMin)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotionPidAngleMvMin(dbMotionPidAngleMvMin); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtMotionPidAngleMvMin} onValueChange={setRtMotionPidAngleMvMin}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motionPidAngleMvMin: Number(rtMotionPidAngleMvMin)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotionPidAngleMvMin(rtMotionPidAngleMvMin); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>PID Angle MV max</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbMotionPidAngleMvMax} onValueChange={setDbMotionPidAngleMvMax}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motionPidAngleMvMax: Number(dbMotionPidAngleMvMax)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotionPidAngleMvMax(dbMotionPidAngleMvMax); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtMotionPidAngleMvMax} onValueChange={setRtMotionPidAngleMvMax}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motionPidAngleMvMax: Number(rtMotionPidAngleMvMax)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotionPidAngleMvMax(rtMotionPidAngleMvMax); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                    </TableBody>
                }
			</Table>
		</div>
	);
}
