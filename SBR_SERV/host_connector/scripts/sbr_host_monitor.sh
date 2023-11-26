#!/bin/bash

sleep 30 # Init Delay

# Init Variables
counter_timer=0
first_try=1
no_ip_found=0

# Get PC Name
hostname=$(hostname)

# Get User
if [ "$hostname" == "sbrpi" ]; then
    user="pi"
elif [[ "$hostname" == "sbrnx" ]]; then
    user="sbrnx"
fi

# Set the path to the file you want to monitor
directory="/home/$user/SBR/data/host_connector/requests"
echo $directory


# Task Monitor Files
task_monitor_files() {

    # Check if an IP address is assigned
    if [ -n "$ip_address" ]; then

        # Check if the directory exists
        if [ -d "$directory" ]; then
            # Iterate over the files in the directory
            for file in "$directory"/*; do
                filename=$(basename "$file")
                sudo rm -f "$file"

                if [ "$filename" != "*" ]; then
                    echo "File: $filename"

                    if [ "$filename" == "SHUTDOWN" ]; then
                        echo "Shutting Down"
                        sleep 10
                        sudo shutdown now

                    elif [ "$filename" == "RESTART" ]; then
                        echo "Restarting"
                        sleep 10
                        sudo reboot

                    elif [ "$filename" == "UPDATE" ]; then
                        echo "Updating"
                        sudo apt update -y
                        sudo apt upgrade -y
                        sudo apt dist-upgrade -y
                        sudo apt autoremove -y

                    elif [ "$filename" == "PRUNE" ]; then
                        echo "Docker Prune"
                        docker image prune -f

                    elif [ "$filename" == "STOP_RUNNER" ]; then
                        echo "Stop Runner"
                        cd /home/$user/SBR/actions-runner
                        sudo chmod +x svc.sh
                        sudo ./svc.sh stop

                    elif [ "$filename" == "START_RUNNER" ]; then
                        echo "Start Runner"
                        cd /home/$user/SBR/actions-runner
                        sudo chmod +x svc.sh
                        sudo ./svc.sh start

                    else
                        echo "Command not found"
                    fi

                fi

            done
        else
            echo "Directory does not exist: $directory"
        fi

    fi
}


# Task Monitor Network
task_monitor_network() {

    # Get the IP address of eth0
    ip_address=$(ip addr show eth0 | grep -oP 'inet \K[\d.]+')

    # Check if an IP address is assigned
    if [ -n "$ip_address" ]; then
        echo "IP address $ip_address is assigned to eth0."
        
        # Reset variables
        no_ip_found=0
        first_try=0

    else
        echo "No IP address is assigned to eth0."
        no_ip_found=1
        
        if [ $first_try == 1 ]; then

            if [ "$hostname" == "sbrpi" ]; then
                echo "Restarting NET"
                sudo systemctl restart dhcpcd
            #elif [[ "$hostname" == "sbrnx" ]]; then
            fi
            first_try=0
        fi

    fi
}


# Task Monitor Docker Compose
task_monitor_docker_compose() {
    
    # Check if an IP address is assigned
    if [ -n "$ip_address" ]; then
        # Docker compose Patrol
        if [ "$hostname" == "sbrpi" ]; then
            cd /home/$user/SBR/actions-runner/_work/sbr/sbr/SBR_PI/DevOps
            docker compose up -d
        elif [[ "$hostname" == "sbrnx" ]]; then
            cd /home/$user/SBR/actions-runner/_work/sbr/sbr/SBR_NX/DevOps
            docker compose up -d
        fi
    fi
}


# Infinite loop
while true; do

    task_monitor_network
    task_monitor_files
    task_monitor_docker_compose

    # Run every 15 seconds
    if (( counter_timer % 3 == 0 )); then
        task_monitor_docker_compose
    fi

    # Increase time and counter
    sleep 5
    ((counter_timer++))
done


# To monitor the Service:
# sudo journalctl -fu sbr_host_monitor.service