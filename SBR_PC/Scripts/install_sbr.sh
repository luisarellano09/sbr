#!/bin/bash

# Path to the script you want to add to the profile
SCRIPT_PATH="/home/ubuntu/Workspace/SBR/SBR_PC/Scripts/sbr.sh"

# Check if the script file exists
if [ -f "$SCRIPT_PATH" ]; then
  # Check if the script is already added to ~/.bashrc
  if grep -q "$SCRIPT_PATH" /home/ubuntu/.profile; then
    echo "The script is already added to /home/ubuntu/.profile."
  else
    echo "Adding the script to /home/ubuntu/.profile."
    echo "export PATH=\$PATH:$SCRIPT_PATH" | sudo tee -a ~/.profile
    sudo chmod +x $SCRIPT_PATH
    source /home/ubuntu/.profile
  fi
else
  echo "Error: The script file does not exist at $SCRIPT_PATH."
fi
