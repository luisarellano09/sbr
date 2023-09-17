"use client"

import { useStoreWeb } from "@/store/store";
import { Bars3Icon } from "@heroicons/react/24/outline";
import classNames from "classnames";


export default function Navbar(props) {

    const hostName = useStoreWeb((state) => state.hostName);
    const currentPage = useStoreWeb((state) => state.currentPage);

    return (
        <nav
            className={classNames({
            "bg-gradient-to-r from-[#0e1730] to-[#272b46] text-indigo-100": true, // colors
            "flex items-center": true, // layout
            "w-screen md:w-full sticky z-10 px-4 shadow-sm h-[73px] top-0 ": true, //positioning & styling
            })}
        >
            <div className="font-bold text-lg">
                <p>{hostName}</p>
                <p>{currentPage}</p>
            </div>
            <div className="flex-grow"></div>
            <p>Notifications</p>
            <button className="md:hidden" onClick={props.onMenuButtonClick}>
                <Bars3Icon className="h-6 w-6" />
            </button>
        </nav>
    );
};
