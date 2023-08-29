"use client";

import { useState, useEffect } from "react";

import Highcharts from "highcharts/highstock";
import HighchartsReact from 'highcharts-react-official'

import { useQuery } from "@apollo/client";
import { GET_ESP32_LIVE_IMU, POOLING_ESP32_LIVE_TIME } from "@/graphql/queries";

import { Button } from "@nextui-org/react";


const MIN_DATA_POINTS = 120;
let dataIMU = {
    pitch: [],
    roll: [],
    yaw : [],
}

export default function ChartIMU() {

    const [chartOptions, setChartOptions] = useState({
        chart: {
            zoomType: "xy",
            backgroundColor: "#18181B",
            zooming:{
                mouseWheel: false,
            },
        },
        title: {
            text: "IMU",
            align: "center",
            style: {
                color: "#f1f5f9",
            },
            margin: 2,
        },
        accessibility: {
            enabled: false,
        },
        xAxis: {
            type: "datetime",
            title: {
                style: {
                    color: "#f1f5f9",
                },
            },
            labels: {
                style: {
                    color: "#D4D4D8",
                },
            },
            gridLineColor: "#ffffff80",
            gridLineWidth: 0.2,

        },
        yAxis: {
            title: {
                style: {
                    color: "#f1f5f9",
                },
            },
            labels: {
                style: {
                    color: "#D4D4D8",
                },
            },
            opposite: false,
            gridLineColor: "#ffffff80",
            gridLineWidth: 0.2,
        },
        legend: {
            enabled: true,
            itemStyle: {
                color: "#D4D4D8",
            },
            margin: 2,
        },
        tooltip: {
            enabled: true, // Disable tooltipscad
            hideDelay: 100,
            followPointer: true,
            distance: 80,
            stickOnContact: true,
            backgroundColor: "#f5f4f4",
        },
        rangeSelector: {
            enabled: false,
        },
        navigator: {
            height: 40,
            enabled: true,
            margin: 2,
        },   
        scrollbar: {
            enabled: false, // Disable the scrollbar
        },
        time: {
            useUTC: false,
        },
        plotOptions: {
            series: {
                lineWidth: 2, // Set the line width (thickness) of the chart line
                enableMouseTracking: false, // Disable line reaction with the cursor
            },
        },
        series: [
            {
                name: "Pitch",
                data: [],
                marker: {
                    enabled: false, // Disable markers (dots)
                },
                showInNavigator: true,
            },
            {
                name: "Roll",
                data: [],
                marker: {
                    enabled: false, // Disable markers (dots)
                },
                showInNavigator: true,
            },
            {
                name: "Yaw",
                data: [],
                marker: {
                    enabled: false, // Disable markers (dots)
                },
                showInNavigator: true,
            },
        ],
    });

	const { data, error, loading } = useQuery(GET_ESP32_LIVE_IMU, {
		pollInterval:POOLING_ESP32_LIVE_TIME,
        fetchPolicy: "no-cache" 
	});

    const [showTooltip, setShowTooltip] = useState(false);

	useEffect(() => {
        if (data != undefined) {

            const timeStamp = Date.now();

            if (dataIMU.pitch.length == 0){
                for (let index = 0; index < MIN_DATA_POINTS; index++) {
                    dataIMU.pitch.push([timeStamp - (MIN_DATA_POINTS - index) * POOLING_ESP32_LIVE_TIME, data.GetEsp32LiveIMU.pitch])
                    dataIMU.roll.push([timeStamp - (MIN_DATA_POINTS - index) * POOLING_ESP32_LIVE_TIME, data.GetEsp32LiveIMU.roll])
                    dataIMU.yaw.push([timeStamp - (MIN_DATA_POINTS - index) * POOLING_ESP32_LIVE_TIME, data.GetEsp32LiveIMU.yaw])
                }
            }

            dataIMU.pitch = [...dataIMU.pitch, [timeStamp, data.GetEsp32LiveIMU.pitch]];
            dataIMU.roll = [...dataIMU.roll, [timeStamp, data.GetEsp32LiveIMU.roll]];  
            dataIMU.yaw = [...dataIMU.yaw, [timeStamp, data.GetEsp32LiveIMU.yaw]];

            if (showTooltip === false){
                setChartOptions(prevOptions => ({
                    ...prevOptions,
                    series: [
                        {
                            ...prevOptions.series[0],
                            data: dataIMU.pitch,
                        }, 
                        {
                            ...prevOptions.series[1],
                            data: dataIMU.roll,
                        },
                        {
                            ...prevOptions.series[2],
                            data: dataIMU.yaw,
                        }
                    ],
                }));
            }
        }
	}, [data]);


    const tooltipHandle = ()=>{

        setChartOptions(prevOptions => ({
            ...prevOptions,
            tooltip: {
                enabled: !showTooltip,
            },
            plotOptions: {
                series: {
                enableMouseTracking: !showTooltip, // line reaction with the cursor
                },
            },
        }));

        setShowTooltip(!showTooltip);
    }

	return (
		<main>
			<div className="p-2">
                <div>
                    <Button onClick={tooltipHandle} color={showTooltip ? "success": "default"} size="sm" radius="md" variant="faded">Show Tooltip</Button>
                </div>
				<HighchartsReact
					highcharts={Highcharts}
                    constructorType={'stockChart'}
					options={chartOptions}
				/>
			</div>
		</main>
	);
}
