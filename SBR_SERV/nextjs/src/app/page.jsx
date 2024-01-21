"use client"

import ControlRobotCcommand from "@/components/Controls/ControlRobotCommand";
import DashboardRobotStatus from "@/components/Dashboards/DashboardRobotStatus";
import { useStoreWeb } from "@/store/store";
import { useEffect } from "react";

export default function Home() {

    const SetCurrentPage = useStoreWeb((state) => state.SetCurrentPage);

    useEffect(()=>{
        SetCurrentPage("Home");
    },[]);

	return (
        <div className="h-[calc(100vh-74px)] md:flex justify-start">
            <div className="pl-5 pt-5 pb-5">
                <DashboardRobotStatus />
                <ControlRobotCcommand />
            </div>
            <iframe src={"http://sbrnx.local:8554"} className="p-5 w-full h-[70%] max-w-[1350px]"/>
        </div>
    );
}
