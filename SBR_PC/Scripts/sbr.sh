#!/bin/bash

# Define menu options
OPTIONS=(
    "Update" "Update/Upgrade System"
    "Host Monitor" "Monitor the service: sbr_host_monitor.service"
    "Serial Node Manager" "Serial connection with Manager"
    "Serial Node01" "Serial connection with Node01"
)

# Show the menu using whiptail
CHOICE=$(whiptail --title "SBR Menu" --menu "Choose an option:" 15 90 5 "${OPTIONS[@]}" 3>&1 1>&2 2>&3)

# Check the exit status to see if the user pressed Cancel or OK
if [ $? -eq 0 ]; then
    # User made a selection
    case "$CHOICE" in
        "Update")
            sudo apt update
            sudo apt upgrade
            sudo apt dist-upgrade
            sudo apt autoremove
            ;;
        "Host Monitor")
            sudo journalctl -fu sbr_host_monitor.service
            ;;
        "Serial Node Manager")
            sudo screen /dev/ttyUSB_ESP32_NODE_MANAGER 115200 
            ;;
        "Serial Node01")
            sudo screen /dev/ttyUSB_ESP32_NODE_01 115200
            ;;
    esac
else
    # User pressed Cancel or closed the menu
    echo "Menu canceled."
fi
