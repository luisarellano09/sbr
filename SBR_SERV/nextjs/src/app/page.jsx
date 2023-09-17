"use client"

import { useStoreWeb } from "@/store/store";

export default function Home() {

    const SetCurrentPage = useStoreWeb((state) => state.SetCurrentPage);

	return (
        <div onLoad={SetCurrentPage("Home")} className="h-[calc(100vh-74px)]">

        </div>
    );
}
