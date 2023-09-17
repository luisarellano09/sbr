"use client"

import { useStoreWeb } from "@/store/store";
import { BellIcon } from "@heroicons/react/24/outline";
import { Chip } from "@nextui-org/react";


export default function Titlebar() {

    const hostName = useStoreWeb((state) => state.hostName);
    const currentPage = useStoreWeb((state) => state.currentPage);

    return (
        <div className="flex flex-grow">

            <div className="flex-initial font-bold text-xs">
                <Chip size="sm" color="success">{hostName}</Chip>
            </div>

            <div className="flex-auto text-center md:mr-[200px] font-bold md:text-lg text-md text-[#e9eee9]">
                <p>{currentPage}</p>
            </div>

            <div className="flex-initial text-right">
                <BellIcon className="w-9 pr-4"/>
            </div>
            
        </div>
    );
};
