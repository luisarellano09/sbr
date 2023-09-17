import { gql } from "@apollo/client";

export const POOLING_ESP32_LIVE_TIME = 600;

export const GET_ESP32_LIVE_IMU = gql`
	query {
		GetEsp32LiveIMU {
			pitch
			roll
			yaw
		}
	}
`;

export const GET_ESP32_LIVE_ODOMETRY = gql`
	query {
		GetEsp32LiveOdometry {
			x
			y
			angle
			distance
		}
	}
`;

export const GET_ESP32_LIVE_MOTION = gql`
	query {
		GetEsp32LiveOdometry {
			angle
			distance
		}

		GetEsp32LiveMotion {
			setpointPosition
			setpointAngle
		}
	}
`;

export const GET_DB_ESP32_SETUP = gql`
	query {
		GetDbEsp32Setup {
			motors {
				motorLeftDirection
				motorLeftOffset
				motorRightDirection
				motorRightOffset
			}
			encoders {
				encoderLeftDirection
				encoderRightDirection
			}
			imu {
				invertPitch
				invertRoll
				invertYaw
				offsetPitch
			}
			odometry {
				wheelRadio
				distanceWheels
			}
			motionPidPitch {
				kp
				ki
				kd
				direction
				mvMin
				mvMax
			}
			motionPidPosition {
				kp
				ki
				kd
				direction
				mvMin
				mvMax
			}
			motionPidAngle {
				kp
				ki
				kd
				direction
				mvMin
				mvMax
			}
		}
	}
`;

export const GET_ESP32_SETUP = gql`
	query {
		GetEsp32Setup {
			motors {
				motorLeftDirection
				motorLeftOffset
				motorRightDirection
				motorRightOffset
			}
			encoders {
				encoderLeftDirection
				encoderRightDirection
			}
			imu {
				invertPitch
				invertRoll
				invertYaw
				offsetPitch
			}
			odometry {
				wheelRadio
				distanceWheels
			}
			motionPidPitch {
				kp
				ki
				kd
				direction
				mvMin
				mvMax
			}
			motionPidPosition {
				kp
				ki
				kd
				direction
				mvMin
				mvMax
			}
			motionPidAngle {
				kp
				ki
				kd
				direction
				mvMin
				mvMax
			}
		}
	}
`;

export const GET_ESP32_STATUS = gql`
	query{
        GetEsp32Status{
            nodeEsp32,
            nodeLinux,
            heartbeat
        }
    }
`;
