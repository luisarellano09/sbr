"use client"

import { SEND_HOST_REQUEST } from "@/graphql/mutations";
import { useMutation } from "@apollo/client";
import { ArrowPathRoundedSquareIcon, BeakerIcon, PowerIcon, SignalIcon, SignalSlashIcon, TrashIcon } from "@heroicons/react/24/outline";
import {Listbox, ListboxItem, ListboxSection} from "@nextui-org/react";

import { toast } from "react-hot-toast";

export default function ControlHost(props) {

    const [sendHostRequest] = useMutation(SEND_HOST_REQUEST);

    const HandleSendHostRequest= (request)=>{
        sendHostRequest({
            variables: {host: props.host, request: request}, 
            onCompleted: ()=> toast.success(props.host + ": " + request),
            onError: (e)=> {
                let networkErrorMessage = "";
                try{
                    networkErrorMessage = e.networkError.result.errors[0].message;
                }
                catch{}

                toast.error(e.message + ": " + networkErrorMessage);
            }
        });
    }

	return (
		<div className="w-full max-w-[260px] border-medium px-1 py-2 rounded-small border-[#646364]">
            <Listbox variant="faded" aria-label="Host Request" onAction={(key)=> HandleSendHostRequest(key)}>
                <ListboxSection title="Station" showDivider className="text-[#e43f3f]">
                    <ListboxItem key="SHUTDOWN" startContent={	<PowerIcon className="w-5"/>}> Shutdown </ListboxItem>
                    <ListboxItem key="RESTART" startContent={	<ArrowPathRoundedSquareIcon className="w-5"/>}> Restart </ListboxItem>
                </ListboxSection>
                <ListboxSection title="System" showDivider className="text-[#2d9659]">
                    <ListboxItem key="UPDATE" startContent={ <BeakerIcon className="w-5"/>}> Update </ListboxItem>
                    <ListboxItem key="PRUNE" startContent={	<TrashIcon className="w-5"/>}> Prune </ListboxItem>
                    <ListboxItem key="START_RUNNER" startContent={ <SignalIcon className="w-5"/>}> Start Runner </ListboxItem>
                    <ListboxItem key="STOP_RUNNER" startContent={ <SignalSlashIcon className="w-5"/>}> Stop Runner </ListboxItem>
                </ListboxSection>
            </Listbox>
		</div>
	);
}
