import { create } from "zustand";

export const useStoreWeb = create((set, get) => ({

	hostName: "sbrpi.local",

	UpdateHost: () => {
        if (typeof window !== 'undefined') {
            let host = location.hostname;
            if (!host.includes("ubuntudev") && !host.includes("localhost")) {
                set({hostName: host});
            } 
        }
    },

}));
