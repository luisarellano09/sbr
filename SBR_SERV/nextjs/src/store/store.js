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


export const useStoreRobot = create((set, get) => ({

	statusNodeEsp32: true,
    statusNodeLinux: true,
    nodeHeartbeat: 0,
    prevNodeHeartbeat: -1,

    UpdateStatusNode: (statusNodeEsp32, statusNodeLinux, nodeHeartbeat) => {
        const prevNodeHeartbeat = get().nodeHeartbeat;
        const statusHeatbeat = nodeHeartbeat > prevNodeHeartbeat;
        set({
            statusNodeEsp32: statusHeatbeat & statusNodeEsp32, 
            statusNodeLinux: statusHeatbeat & statusNodeLinux, 
            nodeHeartbeat: nodeHeartbeat,
            prevNodeHeartbeat: prevNodeHeartbeat,
        });

    },

}));
