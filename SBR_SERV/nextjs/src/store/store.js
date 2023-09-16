import { create } from "zustand";

export const useStoreWeb = create((set, get) => ({

	hostName: "sbrpi.local",
    currentPage: "",

	UpdateHost: () => {
        if (typeof window !== 'undefined') {
            let host = location.hostname;
            if (!host.includes("ubuntudev") && !host.includes("localhost")) {
                set({hostName: host});
            } 
        }
    },

    SetCurrentPage: (page) => {
        set({currentPage: page})
    }

}));
