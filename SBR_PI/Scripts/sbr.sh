#!/bin/bash

# Define menu options
OPTIONS=(
    "Update" "Update/Upgrade System"
    "Host Monitor" "Monitor the service: sbr_host_monitor.service"
    "Start Runner" "Start the GitHub Actions Runner"
    "Serial Node Manager" "Serial connection with Manager (exit: Ctrl-A k)"
    "Serial Node01" "Serial connection with Node01 (exit: Ctrl-A k)"
    "Docker Compose" "cd into the docker-compose folder"
    "Restart" "Restart the system"
    "Shutdown" "Shutdown the system"
)

# Show the menu using whiptail
CHOICE=$(whiptail --title "SBR Menu" --menu "Choose an option:" 15 80 5 "${OPTIONS[@]}" 3>&1 1>&2 2>&3)

# cd to a directory outside of the current directory
external_cd() {
    if [ -z "$1" ]; then
        return 1
    fi
    
    cd "$1"
}

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
            cd /home/pi/SBR/actions-runner
            sudo chmod +x svc.sh
            sudo ./svc.sh start
            ;;
        "Serial Node Manager")
            sudo screen /dev/ttyUSB_ESP32_NODE_MANAGER 115200 
            ;;
        "Serial Node01")
            sudo screen /dev/ttyUSB_ESP32_NODE_01 115200
            ;;
        "Docker Compose")
            external_cd "/home/pi/SBR/actions-runner/_work/sbr/sbr/SBR_PI/DevOps"
            ;;
        "Restart")
            sudo reboot
            ;;
        "Shutdown")
            sudo shutdown -h now
            ;;
    esac
else
    # User pressed Cancel or closed the menu
    echo "Menu canceled."
fi
