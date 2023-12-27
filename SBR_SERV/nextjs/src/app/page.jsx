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
        <div className="h-[calc(100vh-74px)]">
            <DashboardRobotStatus />
            <ControlRobotCcommand />
            

        </div>
    );
}
