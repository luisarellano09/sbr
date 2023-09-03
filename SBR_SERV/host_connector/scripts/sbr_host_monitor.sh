#!/bin/bash

# Get PC Name
hostname=$(hostname)

if [ "$hostname" == "sbrpi" ]; then
    user="pi"
elif [[ "$filename" == "sbrnx" ]]; then
    user="sbrnx"
fi


# Set the path to the file you want to monitor
directory="/home/$user/SBR/data/host_connector/requests"
echo $directory

# Infinite loop to continuously check if the file exists
while true; do
    # Check if the directory exists
    if [ -d "$directory" ]; then
        # Iterate over the files in the directory
        for file in "$directory"/*; do
            filename=$(basename "$file")
            sudo rm -f "$file"

            if [ "$filename" != "*" ]; then
                echo "File: $filename"

                if [[ "$filename" == "SHUTDOWN" ]]; then
                    echo "Shutting Down"
                    sleep 30
                    sudo shutdown now

                elif [[ "$filename" == "RESTART" ]]; then
                    echo "Restarting"
                    sleep 30
                    sudo reboot

                elif [[ "$filename" == "UPDATE" ]]; then
                    echo "Updating"
                    sudo apt update -y
                    sudo apt upgrade -y
                    sudo apt dist-upgrade -y
                    sudo apt autoremove -y

                elif [[ "$filename" == "PRUNE" ]]; then
                    echo "Docker Prune"
                    docker image prune -f

                elif [[ "$filename" == "STOP_RUNNER" ]]; then
                    echo "Stop Runner"
                    cd /home/$user/SBR/actions-runner
                    sudo chmod +x svc.sh
                    sudo ./svc.sh stop

                elif [[ "$filename" == "START_RUNNER" ]]; then
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
    sleep 5 # Adjust the sleep duration (in seconds) as needed
done
