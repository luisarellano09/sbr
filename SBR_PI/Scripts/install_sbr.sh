#!/bin/bash

# Path to the script you want to add to the profile
SCRIPT_PATH="/home/pi/SBR/actions-runner/_work/sbr/sbr/SBR_PI/Scripts/sbr.sh"

# Check if the script file exists
if [ -f "$SCRIPT_PATH" ]; then
  # Check if the script is already added to ~/.bashrc
  if grep -q "$SCRIPT_PATH" /home/pi/.profile; then
    echo "The script is already added to /home/pi/.profile."
  else
    echo "Adding the script to /home/pi/.profile."
    echo "export PATH=\$PATH:$SCRIPT_PATH" | sudo tee -a ~/.profile
    sudo chmod +x $SCRIPT_PATH
    source /home/pi/.profile
  fi
else
  echo "Error: The script file does not exist at $SCRIPT_PATH."
fi
