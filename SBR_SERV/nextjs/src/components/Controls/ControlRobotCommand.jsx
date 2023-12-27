"use client"

import { SEND_COMMAND_BOOL } from "@/graphql/mutations";
import { useMutation } from "@apollo/client";
import { StopIcon, RocketLaunchIcon} from "@heroicons/react/24/outline";
import {Listbox, ListboxItem, ListboxSection} from "@nextui-org/react";

import { toast } from "react-hot-toast";

export default function ControlRobotCcommand() {

    const [sendRobotCommand] = useMutation(SEND_COMMAND_BOOL);

    const HandleSendRobotCommand= (name)=>{
        sendRobotCommand({
            variables: {endpoint: "ROBOT_CONTROL", name: name, value: true},
            onCompleted: ()=> toast.success("Command in ROBOT_CONTROL: " + name),
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
		<div className="w-full max-w-[100px] border-medium px-1 py-2 rounded-small border-[#afacaf]">
            <Listbox variant="faded" aria-label="Robot Command" onAction={(key)=> HandleSendRobotCommand(key)}>
                <ListboxSection title="General" showDivider className="text-[#3fe470]">
                    <ListboxItem key="ROBOT_START" startContent={ <RocketLaunchIcon className="w-5"/>}> Start </ListboxItem>
                    <ListboxItem key="ROBOT_STOP" startContent={ <StopIcon className="w-5"/>}> Stop </ListboxItem>
                </ListboxSection>
                <ListboxSection title="System" showDivider className="text-[#2d9659]">

                </ListboxSection>
            </Listbox>
		</div>
	);
}
