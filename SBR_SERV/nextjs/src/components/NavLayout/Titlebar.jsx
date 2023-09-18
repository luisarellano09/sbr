"use client"

import { SEND_HOST_REQUEST } from "@/graphql/mutations";
import { useStoreRobot, useStoreWeb } from "@/store/store";
import { useMutation } from "@apollo/client";
import { BoltIcon, PowerIcon } from "@heroicons/react/24/outline";
import { Chip, Dropdown, DropdownTrigger, DropdownMenu, DropdownItem, Button, DropdownSection } from "@nextui-org/react";
import { toast } from "react-hot-toast";


export default function Titlebar() {

    const currentPage = useStoreWeb((state) => state.currentPage);
    const statusNodeEsp32 = useStoreRobot((state) => state.statusNodeEsp32);
    const statusNodeLinux = useStoreRobot((state) => state.statusNodeLinux);

    const [sendHostRequest] = useMutation(SEND_HOST_REQUEST);

    const HandlerDropdownMenu = (key)=>{
        switch(key){
            case "SHUTDOWN": 
                sendHostRequest({
                    variables: {host: "NX", request: "SHUTDOWN"}, 
                    onCompleted: ()=> toast.success("NX Shutdown"),
                    onError: (e)=> {
                        let networkErrorMessage = "";
                        try{
                            networkErrorMessage = e.networkError.result.errors[0].message;
                        }
                        catch{}
        
                        toast.error(e.message + ": " + networkErrorMessage);
                    }
                });

                sendHostRequest({
                    variables: {host: "PI", request: "SHUTDOWN"}, 
                    onCompleted: ()=> toast.success("PI Shutdown"),
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
        <div className="flex flex-grow">

            <div className="flex-initial font-bold text-xs">
                <div className="grid grid-cols-1 gap-1">
                    <Chip size="sm" variant="dot" color={statusNodeEsp32 ? "success": "danger"}><p className="w-[80px]">NodeESP32</p></Chip>
                    <Chip size="sm" variant="dot" color={statusNodeLinux ? "success": "danger"}><p className="w-[80px]">NodeLinux</p></Chip>
                </div>
            </div>

            <div className="flex-auto text-center md:mr-[200px] mt-3 font-bold md:text-lg text-md text-[#e9eee9]">
                <p>{currentPage}</p>
            </div>

            <div className="flex-initial text-right mt-2 md:mr-0 mr-2">
                <div className="flex gap-2">
                    <Dropdown>
                        <DropdownTrigger>
                            <Button isIconOnly variant="light"> <BoltIcon className="w-5"/> </Button>
                        </DropdownTrigger>
                        <DropdownMenu aria-label="Menu" onAction={(key) => HandlerDropdownMenu(key)}>
                            <DropdownSection title="Actions" showDivider>  
                                <DropdownItem key="RESERVE">Reserve</DropdownItem>
                            </DropdownSection>
                            <DropdownSection title="System" showDivider>  
                                <DropdownItem key="SHUTDOWN" className="text-danger" color="danger" startContent={<PowerIcon className="w-5"></PowerIcon>} >ShutDown</DropdownItem>
                            </DropdownSection>
                        </DropdownMenu>
                    </Dropdown>
                </div>
            </div>
            
        </div>
    );
};
