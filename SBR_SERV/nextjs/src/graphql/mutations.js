import { gql } from "@apollo/client";

export const SET_ESP32_SETUP = gql`
	mutation SetEsp32Setup($setup: Esp32SetupInput!){
        SetEsp32Setup(setup: $setup)
    }
`;

export const SET_DB_ESP32_SETUP = gql`
	mutation SetDbEsp32Setup($setup: Esp32SetupInput!){
        SetDbEsp32Setup(setup: $setup)
    }
`;

export const SET_ESP32_MOTION_SP_POSITION = gql`
	mutation SetEsp32LiveMotionSpPosition($sp: Float!){
        SetEsp32LiveMotionSpPosition(sp: $sp)
    }
`;

export const SET_ESP32_MOTION_SP_ANGLE = gql`
	mutation SetEsp32LiveMotionSpAngle($sp: Float!){
        SetEsp32LiveMotionSpAngle(sp: $sp)
    }
`;