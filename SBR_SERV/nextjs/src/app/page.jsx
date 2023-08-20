
import DashboardIMU from '@/components/Dashboards/DashboardIMU';
import ChartIMU from '@/components/Charts/ChartIMU';
import DashboardOdometry from '@/components/Dashboards/DashboardOdometry';
import DashboardMotionPosition from '@/components/Dashboards/DashboardMotionPosition';
import DashboardMotionAngle from '@/components/Dashboards/DashboardMotionAngle';
import ChartMotionPosition from '@/components/Charts/ChartMotionPosition';
import ChartMotionAngle from '@/components/Charts/ChartMotionAngle';

export default function Home() {
	return (
        <main>
            <DashboardIMU />
            <DashboardOdometry />
            <DashboardMotionPosition />
            <DashboardMotionAngle />
            <ChartIMU />
            <ChartMotionPosition />
            <ChartMotionAngle />
        </main>
    );
}
