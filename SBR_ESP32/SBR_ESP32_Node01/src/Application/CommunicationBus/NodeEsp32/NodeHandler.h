/**
 * @file NodeHandler.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Handler of the Node
 * @version 1.0
 * @date 13.02.2023
 * 
 */

#ifndef NODEHANDLER_H
#define NODEHANDLER_H

/*******************************************************************************************************************************************
 *  												INCLUDE
 *******************************************************************************************************************************************/
#include "../../../Middleware/CommunicationBus/Request/Request.h"
#include "../../Tasks/Tasks.h"
#include <ArduinoLog.h>


RC_e ExtHandler(Request* request){
    
    // Result code
    RC_e retCode = RC_e::SUCCESS;

    // Check if the pointer is null
    if (request == NULL){
        Log.fatalln("[NodeHandler::ExtHandler] request ERROR_NULL_POINTER");
        return RC_e::ERROR_NULL_POINTER;
    }

    Log.traceln("[NodeHandler::ExtHandler] Request received: nodeId=%d, reqType=%d, regId=%d, data=%d, CRC=%d", request->nodeId, request->reqType, request->regId, request->data, request->CRC);

    switch(request->regId){
        case COM_REQUEST_REG_ID_e::REGISTER_10:{
            double data_Register10 = (double)request->data;
            xQueueSend(queue_Register10, &data_Register10, 0);
            break;
        }
     
    }


    return retCode;
}


#endif // NODEHANDLER_H