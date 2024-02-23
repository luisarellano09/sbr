"use client"

import classNames from "classnames";
import SidebarItems from "./SidebarItems";

export default function Sidebar({shown}) {

	return (
		<div
			className={classNames({
				"bg-gradient-to-b from-[#272b46] to-[#1e5c54] text-[#a0e4ab]": true,
				"transition-all duration-300 ease-in-out": true,
                "fixed": true,
                "md:w-full md:sticky md:z-10 md:shadow-sm md:h-[73px] md:top-0 md:translate-x-0 z-20": true,
                "-translate-x-full": !shown,
			})}
		>
			<div className="flex flex-col justify-between h-screen sticky">

				<div className="flex items-center p-4 bg-gradient-to-r from-[#0e1730] to-[#272b46]">
                    <p className="font-mono font-bold text-4xl ml-10 text-[#39ac89]">SBR</p>
				</div>

                <div className="flex-grow border-r-1 border-t-1 border-[#181933]">
                    <SidebarItems />
                </div>
				
			</div>
		</div>
	);
};
