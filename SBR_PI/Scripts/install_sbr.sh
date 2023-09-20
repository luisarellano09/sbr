#!/bin/bash

# Path to the script folder
SCRIPT_PATH="/home/pi/SBR/actions-runner/_work/sbr/sbr/SBR_PI/Scripts/"

# Check if the script folder exists
if [ -d "$SCRIPT_PATH" ]; then

    # Permissions
    sudo chmod +x $SCRIPT_PATH/sbr.sh

    # Check if the script folder is already added to ~/.profile
    if grep -q "$SCRIPT_PATH" /home/pi/.profile; then
        echo "The script folder is already added to /home/pi/.profile."
    else
        echo "Adding the script folder to /home/pi/.profile."
        echo "export PATH=\$PATH:$SCRIPT_PATH" | sudo tee -a /home/pi/.profile
        source /home/pi/.profile
    fi
else
    echo "Error: The script folder does not exist at $SCRIPT_PATH."
fi
