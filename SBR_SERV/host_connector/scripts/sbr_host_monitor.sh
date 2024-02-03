#!/bin/bash

sleep 30 # Init Delay

# Init Variables
counter_timer=0
stop_docker_monitor=0

# Get PC Name
hostname=$(hostname)

# Get User
if [ "$hostname" == "sbrpi" ]; then
    user="sbrpi"
elif [[ "$hostname" == "sbrnx" ]]; then
    user="sbrnx"
fi

# Set the path to the file you want to monitor
directory="/home/$user/SBR/data/host_connector/requests"
echo $directory

# Start Runner: Create a file named START_RUNNER in the directory
sudo touch /home/$user/SBR/data/host_connector/requests/START_RUNNER

# Activate jetson_clocks
if [ "$hostname" == "sbrnx" ]; then
    sudo jetson_clocks
fi

# Task Monitor Files
task_monitor_files() {

    # Check if an IP address is assigned
    if [ -n "$ip_address" ]; then

        # Check if the directory exists
        if [ -d "$directory" ]; then

            # Iterate over the files in the directory
            for file in "$directory"/*; do

                # Get the filename
                filename=$(basename "$file")

                # Check if the filename exists
                if [ "$filename" != "*" ]; then

                    echo "File: $filename"

                    # Delete the file
                    sudo rm -f "$file"

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

                    elif [ "$filename" == "STOP_DOCKER_MONITOR" ]; then
                        echo "Stop Docker Monitor"
                        stop_docker_monitor=1
                    
                    elif [ "$filename" == "START_DOCKER_MONITOR" ]; then
                        echo "Start Docker Monitor"
                        stop_docker_monitor=0

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



# Task Monitor Docker Compose
task_monitor_docker_compose() {
    
    if [ $stop_docker_monitor == 0 ]; then

        # Docker compose Patrol
        if [ "$hostname" == "sbrpi" ]; then
            cd /home/$user/SBR/actions-runner/_work/sbr/sbr/SBR_PI/DevOps
        elif [[ "$hostname" == "sbrnx" ]]; then
            cd /home/$user/SBR/actions-runner/_work/sbr/sbr/SBR_NX/DevOps
        fi

        docker compose up -d

    fi
}


# Infinite loop
while true; do

    echo "."
    echo "======================= HOST MONITORING ======================="

    echo "============== FILES MONITORING =============="
    task_monitor_files

    # Run every 15 seconds
    if (( counter_timer % 3 == 0 )); then
        echo "=========  DOCKER COMPOSE MONITORING ========="
        task_monitor_docker_compose
    fi

    # Increase time and counter
    sleep 5
    ((counter_timer++))
done


# To monitor the Service:
# sudo journalctl -fu sbr_host_monitor.service