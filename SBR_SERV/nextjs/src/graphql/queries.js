import {gql} from  "@apollo/client";

export const GET_ESP32_LIVE_IMU = gql`
	query {
		GetEsp32LiveIMU {
			pitch
			roll
			yaw
		}
	}
`

export const GET_ESP32_LIVE_ODOMETRY = gql`
	query {
		GetEsp32LiveOdometry{
            x,
            y,
            angle,
            distance,
        }
	}
`

export const GET_ESP32_LIVE_MOTION = gql`
	query {
        GetEsp32LiveOdometry{
            angle,
            distance,
        },
        
        GetEsp32LiveMotion{
            setpointPosition,
            setpointAngle
        }
	}
`

export const POOLING_ESP32_LIVE_TIME = 600;