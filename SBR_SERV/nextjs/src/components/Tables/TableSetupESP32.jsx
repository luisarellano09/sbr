"use client"

import {Button, Chip, Input, Spinner, Switch} from "@nextui-org/react";

import { GET_DB_ESP32_SETUP, GET_ESP32_SETUP } from "@/graphql/queries";
import {Table, TableHeader, TableColumn, TableBody, TableRow, TableCell} from "@nextui-org/react";

import { useMutation, useQuery} from  "@apollo/client";
import { useEffect, useState } from "react";

import { ArrowPathIcon, ArrowDownCircleIcon, ArrowLeftCircleIcon, ArrowRightCircleIcon } from "@heroicons/react/24/outline";
import { SET_DB_ESP32_SETUP, SET_ESP32_SETUP } from "@/graphql/mutations";

import { toast } from "react-hot-toast";

export default function TableSetupESP32() {

    const queryDB = useQuery(GET_DB_ESP32_SETUP, {fetchPolicy: "no-cache"});
    const queryRT = useQuery(GET_ESP32_SETUP, {fetchPolicy: "no-cache"});

    const [render, setRender] = useState(false);

    const [dbMotorLeftDirection, setDbMotorLeftDirection] = useState(false);
    const [rtMotorLeftDirection, setRtMotorLeftDirection] = useState(false);

    const [dbMotorLeftOffset, setDbMotorLeftOffset] = useState(0);
    const [rtMotorLeftOffset, setRtMotorLeftOffset] = useState(0);

    const [dbMotorRightDirection, setDbMotorRightDirection] = useState(false);
    const [rtMotorRightDirection, setRtMotorRightDirection] = useState(false);

    const [dbMotorRightOffset, setDbMotorRightOffset] = useState(0);
    const [rtMotorRightOffset, setRtMotorRightOffset] = useState(0);

    const [dbImuInvertPitch, setDbImuInvertPitch] = useState(false);
    const [rtImuInvertPitch, setRtImuInvertPitch] = useState(false);

    const [dbEncoderLeftDirection, setDbEncoderLeftDirection] = useState(false);
    const [rtEncoderLeftDirection, setRtEncoderLeftDirection] = useState(false);

    const [dbEncoderRightDirection, setDbEncoderRightDirection] = useState(false);
    const [rtEncoderRightDirection, setRtEncoderRightDirection] = useState(false);

    const [dbImuInvertRoll, setDbImuInvertRoll] = useState(false);
    const [rtImuInvertRoll, setRtImuInvertRoll] = useState(false);

    const [dbImuInvertYaw, setDbImuInvertYaw] = useState(false);
    const [rtImuInvertYaw, setRtImuInvertYaw] = useState(false);

    const [dbImuOffsetPitch, setDbImuOffsetPitch] = useState(0);
    const [rtImuOffsetPitch, setRtImuOffsetPitch] = useState(0);

    const [dbOdometryWheelRadio, setDbOdometryWheelRadio] = useState(0);
    const [rtOdometryWheelRadio, setRtOdometryWheelRadio] = useState(0);

    const [dbOdometryDistanceWheels, setDbOdometryDistanceWheels] = useState(0);
    const [rtOdometryDistanceWheels, setRtOdometryDistanceWheels] = useState(0);

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
            setDbMotorLeftDirection(queryDB.data.GetDbEsp32Setup.motors.motorLeftDirection);
            setDbMotorLeftOffset(queryDB.data.GetDbEsp32Setup.motors.motorLeftOffset);
            setDbMotorRightDirection(queryDB.data.GetDbEsp32Setup.motors.motorRightDirection);
            setDbMotorRightOffset(queryDB.data.GetDbEsp32Setup.motors.motorRightOffset);
            setDbEncoderLeftDirection(queryDB.data.GetDbEsp32Setup.encoders.encoderLeftDirection);
            setDbEncoderRightDirection(queryDB.data.GetDbEsp32Setup.encoders.encoderRightDirection);
            setDbImuInvertPitch(queryDB.data.GetDbEsp32Setup.imu.invertPitch);
            setDbImuInvertRoll(queryDB.data.GetDbEsp32Setup.imu.invertRoll);
            setDbImuInvertYaw(queryDB.data.GetDbEsp32Setup.imu.invertYaw);
            setDbImuOffsetPitch(queryDB.data.GetDbEsp32Setup.imu.offsetPitch);
            setDbOdometryWheelRadio(queryDB.data.GetDbEsp32Setup.odometry.wheelRadio);
            setDbOdometryDistanceWheels(queryDB.data.GetDbEsp32Setup.odometry.distanceWheels);
            setDbMotionPidPitchKp(queryDB.data.GetDbEsp32Setup.motionPidPitch.kp);
            setDbMotionPidPitchKi(queryDB.data.GetDbEsp32Setup.motionPidPitch.ki);
            setDbMotionPidPitchKd(queryDB.data.GetDbEsp32Setup.motionPidPitch.kd);
            setDbMotionPidPitchDirection(queryDB.data.GetDbEsp32Setup.motionPidPitch.direction);
            setDbMotionPidPitchMvMin(queryDB.data.GetDbEsp32Setup.motionPidPitch.mvMin);
            setDbMotionPidPitchMvMax(queryDB.data.GetDbEsp32Setup.motionPidPitch.mvMax);
            setDbMotionPidPositionKp(queryDB.data.GetDbEsp32Setup.motionPidPosition.kp);
            setDbMotionPidPositionKi(queryDB.data.GetDbEsp32Setup.motionPidPosition.ki);
            setDbMotionPidPositionKd(queryDB.data.GetDbEsp32Setup.motionPidPosition.kd);
            setDbMotionPidPositionDirection(queryDB.data.GetDbEsp32Setup.motionPidPosition.direction);
            setDbMotionPidPositionMvMin(queryDB.data.GetDbEsp32Setup.motionPidPosition.mvMin);
            setDbMotionPidPositionMvMax(queryDB.data.GetDbEsp32Setup.motionPidPosition.mvMax);
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
            setRtMotorLeftDirection(queryRT.data.GetEsp32Setup.motors.motorLeftDirection);
            setRtMotorLeftOffset(queryRT.data.GetEsp32Setup.motors.motorLeftOffset);
            setRtMotorRightDirection(queryRT.data.GetEsp32Setup.motors.motorRightDirection);
            setRtMotorRightOffset(queryRT.data.GetEsp32Setup.motors.motorRightOffset);
            setRtEncoderLeftDirection(queryRT.data.GetEsp32Setup.encoders.encoderLeftDirection);
            setRtEncoderRightDirection(queryRT.data.GetEsp32Setup.encoders.encoderRightDirection);
            setRtImuInvertPitch(queryRT.data.GetEsp32Setup.imu.invertPitch);
            setRtImuInvertRoll(queryRT.data.GetEsp32Setup.imu.invertRoll);
            setRtImuInvertYaw(queryRT.data.GetEsp32Setup.imu.invertYaw);
            setRtImuOffsetPitch(queryRT.data.GetEsp32Setup.imu.offsetPitch);
            setRtOdometryWheelRadio(queryRT.data.GetEsp32Setup.odometry.wheelRadio);
            setRtOdometryDistanceWheels(queryRT.data.GetEsp32Setup.odometry.distanceWheels);
            setRtMotionPidPitchKp(queryRT.data.GetEsp32Setup.motionPidPitch.kp);
            setRtMotionPidPitchKi(queryRT.data.GetEsp32Setup.motionPidPitch.ki);
            setRtMotionPidPitchKd(queryRT.data.GetEsp32Setup.motionPidPitch.kd);
            setRtMotionPidPitchDirection(queryRT.data.GetEsp32Setup.motionPidPitch.direction);
            setRtMotionPidPitchMvMin(queryRT.data.GetEsp32Setup.motionPidPitch.mvMin);
            setRtMotionPidPitchMvMax(queryRT.data.GetEsp32Setup.motionPidPitch.mvMax);
            setRtMotionPidPositionKp(queryRT.data.GetEsp32Setup.motionPidPosition.kp);
            setRtMotionPidPositionKi(queryRT.data.GetEsp32Setup.motionPidPosition.ki);
            setRtMotionPidPositionKd(queryRT.data.GetEsp32Setup.motionPidPosition.kd);
            setRtMotionPidPositionDirection(queryRT.data.GetEsp32Setup.motionPidPosition.direction);
            setRtMotionPidPositionMvMin(queryRT.data.GetEsp32Setup.motionPidPosition.mvMin);
            setRtMotionPidPositionMvMax(queryRT.data.GetEsp32Setup.motionPidPosition.mvMax);
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
		<div className="md:max-w-2xl max-w-[410px] md:p-5 p-1">
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
                            <TableCell>Motor Left Direction</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={dbMotorLeftDirection} onValueChange={setDbMotorLeftDirection}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motorLeftDirection: dbMotorLeftDirection}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotorLeftDirection(dbMotorLeftDirection); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={rtMotorLeftDirection} onValueChange={setRtMotorLeftDirection}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motorLeftDirection: rtMotorLeftDirection}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotorLeftDirection(rtMotorLeftDirection); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>Motor Left Offset</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbMotorLeftOffset} onValueChange={setDbMotorLeftOffset}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motorLeftOffset: Number(dbMotorLeftOffset)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotorLeftOffset(dbMotorLeftOffset); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtMotorLeftOffset} onValueChange={setRtMotorLeftOffset}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motorLeftOffset: Number(rtMotorLeftOffset)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotorLeftOffset(rtMotorLeftOffset); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>Motor Right Direction</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={dbMotorRightDirection} onValueChange={setDbMotorRightDirection}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motorRightDirection: dbMotorRightDirection}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotorRightDirection(dbMotorRightDirection); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={rtMotorRightDirection} onValueChange={setRtMotorRightDirection}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motorRightDirection: rtMotorRightDirection}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotorRightDirection(rtMotorRightDirection); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>
                        
                        <TableRow>
                            <TableCell>Motor Right Offset</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbMotorRightOffset} onValueChange={setDbMotorRightOffset}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({motorRightOffset: Number(dbMotorRightOffset)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtMotorRightOffset(dbMotorRightOffset); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtMotorRightOffset} onValueChange={setRtMotorRightOffset}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({motorRightOffset: Number(rtMotorRightOffset)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbMotorRightOffset(rtMotorRightOffset); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>Encoder Left Direction</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={dbEncoderLeftDirection} onValueChange={setDbEncoderLeftDirection}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({encoderLeftDirection: dbEncoderLeftDirection}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtEncoderLeftDirection(dbEncoderLeftDirection); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={rtEncoderLeftDirection} onValueChange={setRtEncoderLeftDirection}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({encoderLeftDirection: rtEncoderLeftDirection}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbEncoderLeftDirection(rtEncoderLeftDirection); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>Encoder Right Direction</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={dbEncoderRightDirection} onValueChange={setDbEncoderRightDirection}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({encoderRightDirection: dbEncoderRightDirection}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtEncoderRightDirection(dbEncoderRightDirection); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={rtEncoderRightDirection} onValueChange={setRtEncoderRightDirection}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({encoderRightDirection: rtEncoderRightDirection}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbEncoderRightDirection(rtEncoderRightDirection); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>IMU Invert Pitch</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={dbImuInvertPitch} onValueChange={setDbImuInvertPitch}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({imuInvertPitch: dbImuInvertPitch}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtImuInvertPitch(dbImuInvertPitch); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={rtImuInvertPitch} onValueChange={setRtImuInvertPitch}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({imuInvertPitch: rtImuInvertPitch}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbImuInvertPitch(rtImuInvertPitch); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>IMU Invert Roll</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={dbImuInvertRoll} onValueChange={setDbImuInvertRoll}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({imuInvertRoll: dbImuInvertRoll}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtImuInvertRoll(dbImuInvertRoll); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={rtImuInvertRoll} onValueChange={setRtImuInvertRoll}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({imuInvertRoll: rtImuInvertRoll}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbImuInvertRoll(rtImuInvertRoll); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>IMU Invert Yaw</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={dbImuInvertYaw} onValueChange={setDbImuInvertYaw}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({imuInvertYaw: dbImuInvertYaw}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtImuInvertYaw(dbImuInvertYaw); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Switch size="sm" type="bolean" variant="faded" color="success" isSelected={rtImuInvertYaw} onValueChange={setRtImuInvertYaw}/>
                                    <div className="w-[30px]"/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({imuInvertYaw: rtImuInvertYaw}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbImuInvertYaw(rtImuInvertYaw); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>IMU Pitch Offset</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbImuOffsetPitch} onValueChange={setDbImuOffsetPitch}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({imuOffsetPitch: Number(dbImuOffsetPitch)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtImuOffsetPitch(dbImuOffsetPitch); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtImuOffsetPitch} onValueChange={setRtImuOffsetPitch}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({imuOffsetPitch: Number(rtImuOffsetPitch)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbImuOffsetPitch(rtImuOffsetPitch); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>Odometry Wheel Radio</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbOdometryWheelRadio} onValueChange={setDbOdometryWheelRadio}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({odometryWheelRadio: Number(dbOdometryWheelRadio)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtOdometryWheelRadio(dbOdometryWheelRadio); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtOdometryWheelRadio} onValueChange={setRtOdometryWheelRadio}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({odometryWheelRadio: Number(rtOdometryWheelRadio)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbOdometryWheelRadio(rtOdometryWheelRadio); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>Odometry Distance Wheels</TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={dbOdometryDistanceWheels} onValueChange={setDbOdometryDistanceWheels}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetDbESP32Setup({odometryDistanceWheels: Number(dbOdometryDistanceWheels)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowRightCircleIcon className="w-6" onClick={()=>{ setRtOdometryDistanceWheels(dbOdometryDistanceWheels); }}/></Button>
                                </div>
                            </TableCell>
                            <TableCell>
                                <div className="flex justify-start">
                                    <Input size="sm" type="number" variant="faded" className="w-[80px]" value={rtOdometryDistanceWheels} onValueChange={setRtOdometryDistanceWheels}/>
                                    <Button size="sm" variant="light" isIconOnly><ArrowDownCircleIcon className="w-6" onClick={()=>{ HandleSetRtESP32Setup({odometryDistanceWheels: Number(rtOdometryDistanceWheels)}); }}/></Button>
                                    <Button size="sm" variant="light" isIconOnly><ArrowLeftCircleIcon className="w-6" onClick={()=>{ setDbOdometryDistanceWheels(rtOdometryDistanceWheels); }}/></Button>
                                </div>
                            </TableCell>
                        </TableRow>

                        <TableRow>
                            <TableCell>Motion PID Pitch Kp</TableCell>
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
                            <TableCell>Motion PID Pitch Ki</TableCell>
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
                            <TableCell>Motion PID Pitch Kd</TableCell>
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
                            <TableCell>Motion PID Pitch Direction</TableCell>
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
                            <TableCell>Motion PID Pitch MV min</TableCell>
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
                            <TableCell>Motion PID Pitch MV max</TableCell>
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

                        <TableRow>
                            <TableCell>Motion PID Position Kp</TableCell>
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
                            <TableCell>Motion PID Position Ki</TableCell>
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
                            <TableCell>Motion PID Position Kd</TableCell>
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
                            <TableCell>Motion PID Position Direction</TableCell>
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
                            <TableCell>Motion PID Position MV min</TableCell>
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
                            <TableCell>Motion PID Position MV max</TableCell>
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

                        <TableRow>
                            <TableCell>Motion PID Angle Kp</TableCell>
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
                            <TableCell>Motion PID Angle Ki</TableCell>
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
                            <TableCell>Motion PID Angle Kd</TableCell>
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
                            <TableCell>Motion PID Angle Direction</TableCell>
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
                            <TableCell>Motion PID Angle MV min</TableCell>
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
                            <TableCell>Motion PID Angle MV max</TableCell>
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
