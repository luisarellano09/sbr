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
export const POOLING_ESP32_LIVE_TIME = 600;