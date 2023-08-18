
import classNames from "classnames";
import { ChevronDoubleLeftIcon, ChevronDoubleRightIcon } from "@heroicons/react/24/outline";
import SidebarItems from "./SidebarItems";

const Sidebar = ({
	collapsed,
	shown,
	setCollapsed,
}) => {
	const Icon = collapsed ? ChevronDoubleRightIcon : ChevronDoubleLeftIcon;
	return (
		<div
			className={classNames({
				"bg-gradient-to-b from-[#272b46] to-[#1e5c54] text-[#a0e4ab] fixed md:static md:translate-x-0 z-20": true,
				"transition-all duration-300 ease-in-out ": true,
				"w-[200px]": !collapsed,
				"w-16": collapsed,
				"-translate-x-full": !shown,
			})}
		>
			<div
				className="flex flex-col justify-between h-screen md:h-full sticky inset-0">
				{/* logo and collapse button */}
				<div
					className={classNames({
						"flex items-center border-b border-b-slate-500 transition-none": true,
						"p-4 justify-between": !collapsed,
						"py-4 justify-center": collapsed,
					})}
				>
					{!collapsed && (
						<p className="font-mono font-bold text-4xl ml-10 text-[#39ac89]">SBR</p>
					)}
				</div>

                <nav className="flex-grow">
                    <SidebarItems />
                </nav>
				

			</div>
		</div>
	);
};
export default Sidebar;
