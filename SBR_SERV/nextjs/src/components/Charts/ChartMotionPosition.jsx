"use client";

import { useState, useEffect } from "react";

import Highcharts from "highcharts/highstock";
import HighchartsReact from 'highcharts-react-official'

import { useQuery } from "@apollo/client";
import { GET_ESP32_LIVE_MOTION, POOLING_ESP32_LIVE_TIME } from "@/graphql/queries";

import { Button } from "@nextui-org/react";


const MIN_DATA_POINTS = 120;
let dataMotionPosition = {
    sp_position: [],
    position: [],
}

export default function ChartMotionPosition() {

    const [chartOptions, setChartOptions] = useState({
        chart: {
            zoomType: "xy",
            backgroundColor: "#18181B",
        },
        title: {
            text: "Motion Position",
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
                name: "SP Position",
                data: [],
                marker: {
                    enabled: false, // Disable markers (dots)
                },
                showInNavigator: true,
            },
            {
                name: "Position",
                data: [],
                marker: {
                    enabled: false, // Disable markers (dots)
                },
                showInNavigator: true,
            }
        ],
    });

	const { data, error, loading } = useQuery(GET_ESP32_LIVE_MOTION, {
		pollInterval:POOLING_ESP32_LIVE_TIME,
        fetchPolicy: "no-cache" 
	});

    const [showTooltip, setShowTooltip] = useState(false);

	useEffect(() => {
        if (data != undefined) {

            const timeStamp = Date.now();

            if (dataMotionPosition.sp_position.length == 0){
                for (let index = 0; index < MIN_DATA_POINTS; index++) {
                    dataMotionPosition.sp_position.push([timeStamp - (MIN_DATA_POINTS - index) * POOLING_ESP32_LIVE_TIME, data.GetEsp32LiveMotion.setpointPosition])
                    dataMotionPosition.position.push([timeStamp - (MIN_DATA_POINTS - index) * POOLING_ESP32_LIVE_TIME, data.GetEsp32LiveOdometry.distance])
                }
            }

            dataMotionPosition.sp_position = [...dataMotionPosition.sp_position, [timeStamp, data.GetEsp32LiveMotion.setpointPosition]];
            dataMotionPosition.position = [...dataMotionPosition.position, [timeStamp, data.GetEsp32LiveOdometry.distance]];  

            if (showTooltip === false){
                setChartOptions(prevOptions => ({
                    ...prevOptions,
                    series: [
                        {
                            ...prevOptions.series[0],
                            data: dataMotionPosition.sp_position,
                        }, 
                        {
                            ...prevOptions.series[1],
                            data: dataMotionPosition.position,
                        },
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
			<div className="p-5">
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
