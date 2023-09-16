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

export const SEND_HOST_REQUEST = gql`
    mutation SendHostRequest($host: String!, $request: String!){
        SendHostRequest(host: $host, request: $request)
    }
`;

export const SET_ESP32_MODE_MANAGER_RESTART = gql`
    mutation{
        SetEsp32ModeManagerRestart
    }
`;

export const SET_ESP32_MODE_MANAGER_PROGRAM = gql`
    mutation{
        SetEsp32ModeManagerProgram
    }
`;

export const SET_ESP32_MODE_NODE1_RESTART = gql`
    mutation{
        SetEsp32ModeNode1Restart
    }
`;

export const SET_ESP32_MODE_NODE1_PROGRAM = gql`
    mutation{
        SetEsp32ModeNode1Program
    }
`;