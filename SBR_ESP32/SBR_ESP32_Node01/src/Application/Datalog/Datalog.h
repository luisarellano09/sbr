/**
 * @file Datalog.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Datalog
 * @version 1.0
 * @date 02.04.2023
 * 
 * 
 */

#ifndef DATALOG_H
#define DATALOG_H

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include "DatalogConfig.h"
#include <Arduino.h>
#include <ArduinoLog.h>
#include "../../Definition/Local/GlobalVar.h"


/*******************************************************************************************************************************************
 *  												DECLARATION
 *******************************************************************************************************************************************/

void InitDatalog(){
    datalogDatasets[Datasets_e::DATASET_MOTOR].Name = "Dataset Motor";
    datalogDatasets[Datasets_e::DATASET_MOTOR].Callback = DatalogDatasetMotor;

    datalogDatasets[Datasets_e::DATASET_IMU].Name = "Dataset IMU";
    datalogDatasets[Datasets_e::DATASET_IMU].Callback = DatalogDatasetIMU;

    datalogDatasets[Datasets_e::DATASET_ODOMETRY].Name = "Dataset Odometry";
    datalogDatasets[Datasets_e::DATASET_ODOMETRY].Callback = DatalogDatasetOdometry;

    datalogDatasets[Datasets_e::DATASET_MOTION_CONTROL].Name = "Dataset Motion Control";
    datalogDatasets[Datasets_e::DATASET_MOTION_CONTROL].Callback = DatalogDatasetMotionControl;
}


//=====================================================================================================

void ActivateDataset(Datasets_e select){
    if (select > Datasets_e::DATASET_NONE && select < Datasets_e::LENGTH_DATASETS){
        datalogDatasets[select].active = true;
    }
    Log.traceln("[Datalog::ActivateDataset] Dataset activated: %s", datalogDatasets[select].Name);
}


//=====================================================================================================

void DeactivateDataset(Datasets_e select){
    if (select > Datasets_e::DATASET_NONE && select < Datasets_e::LENGTH_DATASETS){
        datalogDatasets[select].active = false;
    }
    Log.traceln("[Datalog::DeactivateDataset] Dataset deactivated: %s", datalogDatasets[select].Name);
}


//=====================================================================================================

void Datalog(){
    for (uint8_t dataset = Datasets_e::DATASET_NONE; dataset < Datasets_e::LENGTH_DATASETS; dataset++){
        if (dataset > Datasets_e::DATASET_NONE && dataset < Datasets_e::LENGTH_DATASETS){
            if (datalogDatasets[dataset].active == true){
                datalogDatasets[dataset].Callback();
            }
        }
    }
    Serial.println("");
}


//=====================================================================================================

void DatalogDatasetMotor(){
    Serial.printf("ML,%.2f, MR,%.2f, ", manager->m_motorLeft->m_speed, manager->m_motorRight->m_speed);
}


//=====================================================================================================

void DatalogDatasetIMU(){
    Serial.printf("Pitch,%.2f, Yaw,%.2f, Roll,%.2f, ", manager->m_IMU->m_Pitch, manager->m_IMU->m_Yaw, manager->m_IMU->m_Roll);
}


//=====================================================================================================

void DatalogDatasetOdometry(){
    Serial.printf("X,%.5f, Y,%.5f, Angle,%.2f, ", manager->m_odometry->GetX(), manager->m_odometry->GetY(), manager->m_odometry->GetAngle());
}


//=====================================================================================================

void DatalogDatasetMotionControl(){
    Serial.printf("SP,%.2f, PV,%.2f, E,%.2f, MV,%.2f, Kp,%.4f, Ki,%.4f, Kd,%.4f, T,%.2f, ", manager->m_motionControl->m_PIDPitch->m_SP, manager->m_motionControl->m_PIDPitch->m_PV, manager->m_motionControl->m_PIDPitch->m_error, manager->m_motionControl->m_PIDPitch->m_MV, manager->m_motionControl->m_PIDPitch->m_kp, manager->m_motionControl->m_PIDPitch->m_ki, manager->m_motionControl->m_PIDPitch->m_kd, manager->m_motionControl->m_PIDPitch->m_cycleTime);
}



#endif // DATALOG_H