"use client"

import DashboardMotionPosition from "@/components/Dashboards/DashboardMotionPosition";
import DashboardMotionAngle from "@/components/Dashboards/DashboardMotionAngle";
import ControlSpPidPosition from "@/components/Controls/ControlSpPidPosition";
import ControlSpPidAngle from "@/components/Controls/ControlSpPidAngle";
import TablePidTunningAngle from "@/components/Tables/TablePidTunningAngle";
import ChartMotionAngle from "@/components/Charts/ChartMotionAngle";
import { useStoreWeb } from "@/store/store";

export default function Angle() {

    const SetCurrentPage = useStoreWeb((state) => state.SetCurrentPage);

    return (
		<div onLoad={SetCurrentPage("Tunning - Angle")} className="md:h-[calc(100vh-74px)]">
            <div className="flex justify-start flex-wrap">
                <div className="py-7">
                    <ControlSpPidPosition />
                    <DashboardMotionPosition />
                    <ControlSpPidAngle />
                    <DashboardMotionAngle />
                </div>
                <TablePidTunningAngle />
            </div>
            <div>
                <ChartMotionAngle />
            </div>
		</div>
    );
}
