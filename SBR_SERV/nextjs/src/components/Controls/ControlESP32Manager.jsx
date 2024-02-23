"use client"

import { SET_ESP32_MODE_MANAGER_PROGRAM, SET_ESP32_MODE_MANAGER_RESTART } from "@/graphql/mutations";
import { useMutation } from "@apollo/client";
import { ArrowPathRoundedSquareIcon, ArrowsRightLeftIcon, WifiIcon } from "@heroicons/react/24/outline";
import {Listbox, ListboxItem, ListboxSection} from "@nextui-org/react";

import { toast } from "react-hot-toast";

export default function ControlESP32Manager() {

    const [nodeRestart] = useMutation(SET_ESP32_MODE_MANAGER_RESTART);
    const [nodeProgram] = useMutation(SET_ESP32_MODE_MANAGER_PROGRAM);

    const HandleSendHostRequest= (request)=>{

        switch(request){
            case "RESTART": 
                nodeRestart({
                    onCompleted: ()=> toast.success("Command ESP32 Manager: Restart"),
                    onError: (e)=> {
                        let networkErrorMessage = "";
                        try{
                            networkErrorMessage = e.networkError.result.errors[0].message;
                        }
                        catch{}
        
                        toast.error(e.message + ": " + networkErrorMessage);
                    }
                });
                break;

            case "PROGRAM": 
                nodeProgram({
                    onCompleted: ()=> toast.success("Command ESP32 Manager: Program"),
                    onError: (e)=> {
                        let networkErrorMessage = "";
                        try{
                            networkErrorMessage = e.networkError.result.errors[0].message;
                        }
                        catch{}
        
                        toast.error(e.message + ": " + networkErrorMessage);
                    }
                });
                break;
        }
    }

	return (
		<div className="w-full max-w-[260px] border-medium px-1 py-2 rounded-small border-[#646364]">
            <Listbox variant="faded" aria-label="Host Request" onAction={(key)=> HandleSendHostRequest(key)}>
                <ListboxSection title="ESP32 Manager" showDivider className="text-[#e43f3f]">
                    <ListboxItem key="RESTART" startContent={	<ArrowPathRoundedSquareIcon className="w-5"/>}> Restart </ListboxItem>
                    <ListboxItem key="PROGRAM" startContent={	<WifiIcon className="w-5"/>}> Program </ListboxItem>
                </ListboxSection>
                <ListboxSection title="Data" showDivider className="text-[#2d9659]">
                    <ListboxItem key="SYNC" startContent={ <ArrowsRightLeftIcon className="w-5"/>}> Sync </ListboxItem>
                </ListboxSection>
            </Listbox>
		</div>
	);
}
