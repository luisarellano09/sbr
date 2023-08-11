/**
 * @file NodeLinuxHandler.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Handler of the Node
 * 
 */

#ifndef NODELINUXHANDLER_H
#define NODELINUXHANDLER_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "../../../Middleware/CommunicationBus/Request/Request.h"
#include "../../System/Tasks/Tasks.h"
#include <ArduinoLog.h>


/*******************************************************************************************************************************************
 *  												DEFINITION FUNCTIONS
 *******************************************************************************************************************************************/

RC_e ExtNodeLinuxHandler(Request* request){
    
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check if the pointer is null
    if (request == NULL){
        Log.fatalln("[NodeLinuxHandler::ExtNodeLinuxHandler] request ERROR_NULL_POINTER");
        return RC_e::ERROR_NULL_POINTER;
    }

    Log.traceln("[NodeLinuxHandler::ExtNodeLinuxHandler] Request received: nodeId=%d, reqType=%d, regId=%d, data=%d, CRC=%d", request->nodeId, request->reqType, request->regId, request->data, request->CRC);

    // Handle requests
    switch(request->regId){
        
        case COM_REQUEST_REG_ID_e::STATUS_HEARTBEAT_LINUX_COUNTER_R: {
            manager->m_nodeLinux->TokenCounter(request->data, COM_REQUEST_REG_ID_e::STATUS_HEARTBEAT_LINUX_COUNTER_R);
            break;
        }

        case COM_REQUEST_REG_ID_e::MODE_MANAGER_RESTART_W: {
            Serial.println("Restarting...");
            ESP.restart();
            break;
        }

        case COM_REQUEST_REG_ID_e::MODE_MANAGER_PROGRAM_W: {
            Serial.println("Program Mode.....");
            StartMode(Modes_e::Mode_Program);
            Log.infoln("[NodeLinuxHandler::MODE_MANAGER_PROGRAM_W] Mode Program started");
            break;
        }

        case COM_REQUEST_REG_ID_e::MODE_MANAGER_SYNC_DATA_RW: {
            // ToDo
            break;
        }

        case COM_REQUEST_REG_ID_e::MODE_LINUX_SYNC_DATA_RW: {
            // Todo
            break;
        }
       
    }

    return retCode;
}


#endif // NODELINUXHANDLER_H