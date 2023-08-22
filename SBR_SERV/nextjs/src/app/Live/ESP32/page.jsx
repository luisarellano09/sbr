import DashboardIMU from '@/components/Dashboards/DashboardIMU';
import ChartIMU from '@/components/Charts/ChartIMU';
import DashboardOdometry from '@/components/Dashboards/DashboardOdometry';
import DashboardMotionPosition from '@/components/Dashboards/DashboardMotionPosition';
import DashboardMotionAngle from '@/components/Dashboards/DashboardMotionAngle';
import ChartMotionPosition from '@/components/Charts/ChartMotionPosition';
import ChartMotionAngle from '@/components/Charts/ChartMotionAngle';

export default function ESP32() {
    return (
        <div>
            <div className="flex justify-start flex-wrap">
                <DashboardIMU />
                <DashboardOdometry />
                <DashboardMotionPosition />
                <DashboardMotionAngle />
            </div>
            <ChartIMU />
            <ChartMotionPosition />
            <ChartMotionAngle />
        </div>
    );
}
