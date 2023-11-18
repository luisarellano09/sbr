#!/bin/bash

# Define menu options
OPTIONS=(
    "Update" "Update/Upgrade System"
    "Host Monitor" "Monitor the service: sbr_host_monitor.service"
    "Start Runner" "Start the GitHub Actions Runner"
)

# Show the menu using whiptail
CHOICE=$(whiptail --title "SBR Menu" --menu "Choose an option:" 15 80 5 "${OPTIONS[@]}" 3>&1 1>&2 2>&3)

# Check the exit status to see if the user pressed Cancel or OK
if [ $? -eq 0 ]; then
    # User made a selection
    case "$CHOICE" in
        "Update")
            sudo apt update -y
            sudo apt upgrade -y
            sudo apt dist-upgrade -y
            sudo apt autoremove -y
            ;;
        "Host Monitor")
            sudo journalctl -fu sbr_host_monitor.service
            ;;
        "Start Runner")
            cd /home/sbrnx/SBR/actions-runner
            sudo chmod +x svc.sh
            sudo ./svc.sh start
            ;;
    esac
else
    # User pressed Cancel or closed the menu
    echo "Menu canceled."
fi
