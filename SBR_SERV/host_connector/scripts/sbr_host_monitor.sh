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
                    docker image prune

                else
                    echo "Command not found"

                fi

                sudo rm -f "$file"
            fi

        done
    else
        echo "Directory does not exist: $directory"
    fi
    sleep 5 # Adjust the sleep duration (in seconds) as needed
done
