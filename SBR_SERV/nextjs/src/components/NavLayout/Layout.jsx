"use client";

import classNames from "classnames";
import { useState } from "react";
import Navbar from "./Navbar";
import Sidebar from "./Sidebar";

const Layout = ({ children }) => {
	const [collapsed, setSidebarCollapsed] = useState(false);
	const [showSidebar, setShowSidebar] = useState(false);
	return (
		<div
			className={classNames({
				"grid min-h-screen bg-gradient-to-b from-[#1d2f46] to-[#132b25]": true,
				"grid-cols-sidebar": !collapsed,
				"grid-cols-sidebar-collapsed": collapsed,
				"transition-[grid-template-columns] duration-300 ease-in-out": true,
				"grid md:grid-cols-[200px_auto]": true,
			})}
		>	
            <Sidebar
                collapsed={collapsed}
                setCollapsed={setSidebarCollapsed}
                shown={showSidebar}
            />
		
			<div>
				<Navbar
					onMenuButtonClick={() => setShowSidebar((prev) => !prev)}
				/>
				{children}
			</div>
		</div>
	);
};

export default Layout;
