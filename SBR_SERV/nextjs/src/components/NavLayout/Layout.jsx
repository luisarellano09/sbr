"use client";

import { useState } from "react";
import Navbar from "./Navbar";
import Sidebar from "./Sidebar";

export default function Layout ({ children }) {

	const [showSidebar, setShowSidebar] = useState(false);

	return (
		<div className="grid bg-gradient-to-b from-[#1d2f46] to-[#132b25] md:grid-cols-[170px_auto]">	
            <Sidebar shown={showSidebar} />
			<div> 
				<Navbar onMenuButtonClick={() => setShowSidebar((prev) => !prev)} />
                <div>
                    {children}
                </div>
			</div>
		</div>
	);
};
