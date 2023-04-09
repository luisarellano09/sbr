/**
 * @file DatalogConfig.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Declarations of the Datalog
 * 
 */

#ifndef DATALOGCONFIG_H
#define DATALOGCONFIG_H

/*******************************************************************************************************************************************
 *  												INCLUDES
 *******************************************************************************************************************************************/
#include <Arduino.h>


/*******************************************************************************************************************************************
 *  												STRUCTURES
 *******************************************************************************************************************************************/

/**
 * @brief Struct of a Dataset
 * 
 */
struct Dataset_t{
    String Name = "";                   /**@brief Name of the Dataset */
    bool active = false;                /**@brief Status of the dataset 0=inactive; 1=active */
    void (*Callback)(void) = NULL;      /**@brief Function callback of the Dataset */
};


/*******************************************************************************************************************************************
 *  												ENUMERATIONS
 *******************************************************************************************************************************************/

/**
 * @brief Enumeration of the Datasets
 * 
 */
enum Datasets_e {
    DATASET_NONE = 0,
    DATASET_MOTOR,
	DATASET_IMU,
    DATASET_ODOMETRY,
    DATASET_MOTION_CONTROL,
    LENGTH_DATASETS
};


/*******************************************************************************************************************************************
 *  												DECLARATION VARIABLES
 *******************************************************************************************************************************************/

Dataset_t datalogDatasets[Datasets_e::LENGTH_DATASETS];     /**@brief Array of Datasets */


/*******************************************************************************************************************************************
 *  												DECLARATION
 *******************************************************************************************************************************************/

void InitDatalog();
void ActivateDataset(Datasets_e select);
void DeactivateDataset(Datasets_e select);
void Datalog();
void DatalogDatasetMotor();
void DatalogDatasetIMU();
void DatalogDatasetOdometry();
void DatalogDatasetMotionControl();


#endif // DATALOGCONFIG_H