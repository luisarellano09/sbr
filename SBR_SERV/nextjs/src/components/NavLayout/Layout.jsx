"use client";

import classNames from "classnames";
import { useState } from "react";
import Navbar from "./Navbar";
import Sidebar from "./Sidebar";

const Layout = ({ children }) => {
	const [showSidebar, setShowSidebar] = useState(false);
	return (
		<div
			className={classNames({
				"grid bg-gradient-to-b from-[#1d2f46] to-[#132b25]": true,
				"grid md:grid-cols-[200px_auto]": true,
			})}
		>	
            <Sidebar
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
