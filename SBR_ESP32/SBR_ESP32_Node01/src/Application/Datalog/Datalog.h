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
    Serial.printf("ML,%.2f, MR,%.2f, ", manager->m_motorLeft->GetSpeed(), manager->m_motorRight->GetSpeed());
}


//=====================================================================================================

void DatalogDatasetIMU(){
    Serial.printf("Pitch,%.2f, Yaw,%.2f, Roll,%.2f, ", manager->m_IMU->GetPitch(), manager->m_IMU->GetYaw(), manager->m_IMU->GetRoll());
}


//=====================================================================================================

void DatalogDatasetOdometry(){
    Serial.printf("Distance,%.5f , X,%.5f, Y,%.5f, Angle,%.2f, ", manager->m_odometry->GetDistance(), manager->m_odometry->GetX(), manager->m_odometry->GetY(), manager->m_odometry->GetAngle());
}


//=====================================================================================================

void DatalogDatasetMotionControl(){
    Serial.printf("PoSP,%.5f, PoPV,%.5f, PoMV,%.1f, ", manager->m_motionControl->m_PIDPosition->m_SP, manager->m_motionControl->m_PIDPosition->m_PV, manager->m_motionControl->m_PIDPosition->m_MV);
    Serial.printf("PiSP,%.1f, PiPV,%.1f, PiMV,%.1f, ", manager->m_motionControl->m_PIDPitch->m_SP, manager->m_motionControl->m_PIDPitch->m_PV, manager->m_motionControl->m_PIDPitch->m_MV);
    Serial.printf("AnSP,%.1f, AnPV,%.1f, AnMV,%.1f, ", manager->m_motionControl->m_PIDAngle->m_SP, manager->m_motionControl->m_PIDAngle->m_PV, manager->m_motionControl->m_PIDAngle->m_MV);
}



#endif // DATALOG_H