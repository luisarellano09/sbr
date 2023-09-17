"use client"

import { useStoreRobot, useStoreWeb } from "@/store/store";
import { BellIcon } from "@heroicons/react/24/outline";
import { Chip } from "@nextui-org/react";


export default function Titlebar() {

    const currentPage = useStoreWeb((state) => state.currentPage);
    const statusNodeEsp32 = useStoreRobot((state) => state.statusNodeEsp32);
    const statusNodeLinux = useStoreRobot((state) => state.statusNodeLinux);

    return (
        <div className="flex flex-grow">

            <div className="flex-initial font-bold text-xs">
                <div className="grid grid-cols-1 gap-1">
                    <Chip size="sm" variant="dot" color={statusNodeEsp32 ? "success": "danger"}><p className="w-[80px]">NodeEsp32</p></Chip>
                    <Chip size="sm" variant="dot" color={statusNodeLinux ? "success": "danger"}><p className="w-[80px]">NodeLinux</p></Chip>
                </div>
            </div>

            <div className="flex-auto text-center md:mr-[200px] mt-3 font-bold md:text-lg text-md text-[#e9eee9]">
                <p>{currentPage}</p>
            </div>

            <div className="flex-initial text-right mt-4">
                <BellIcon className="w-9 pr-4"/>
            </div>
            
        </div>
    );
};
