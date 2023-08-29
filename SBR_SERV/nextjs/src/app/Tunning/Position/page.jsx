import ChartMotionPosition from "@/components/Charts/ChartMotionPosition";
import TablePidTunningPitch from "@/components/Tables/TablePidTunningPitch";
import DashboardMotionPosition from "@/components/Dashboards/DashboardMotionPosition";
import TablePidTunningPosition from "@/components/Tables/TablePidTunningPosition";
import DashboardMotionAngle from "@/components/Dashboards/DashboardMotionAngle";
import ControlSpPidPosition from "@/components/Controls/ControlSpPidPosition";
import ControlSpPidAngle from "@/components/Controls/ControlSpPidAngle";

export default function Position() {
	return (
		<div className="md:h-[calc(100vh-74px)]">
            <div className="flex justify-start flex-wrap">
                <div className="py-7">
                    <ControlSpPidPosition />
                    <DashboardMotionPosition />
                    <ControlSpPidAngle />
                    <DashboardMotionAngle />
                </div>
                <TablePidTunningPitch />
                <TablePidTunningPosition />
            </div>
            <div>
                <ChartMotionPosition />
            </div>
		</div>
	);
}
