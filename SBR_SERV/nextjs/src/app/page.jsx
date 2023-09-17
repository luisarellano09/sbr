"use client"

import { useStoreWeb } from "@/store/store";
import { useEffect } from "react";

export default function Home() {

    const SetCurrentPage = useStoreWeb((state) => state.SetCurrentPage);

    useEffect(()=>{
        SetCurrentPage("Home");
    },[]);

	return (
        <div className="h-[calc(100vh-74px)]">

        </div>
    );
}
