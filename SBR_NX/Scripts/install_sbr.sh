#!/bin/bash

# Path to the script folder
SCRIPT_PATH="/home/sbrnx/SBR/actions-runner/_work/sbr/sbr/SBR_NX/Scripts/"

# Check if the script folder exists
if [ -d "$SCRIPT_PATH" ]; then
  # Check if the script is already added to ~/.profile
  if grep -q "$SCRIPT_PATH" /home/sbrnx/.profile; then
    echo "The script folder is already added to /home/sbrnx/.profile."
  else
    echo "Adding the script folder to /home/sbrnx/.profile."
    echo "export PATH=\$PATH:$SCRIPT_PATH" | sudo tee -a /home/sbrnx/.profile
    sudo chmod +x $SCRIPT_PATH/sbr.sh
    source /home/sbrnx/.profile
  fi
else
  echo "Error: The script folder does not exist at $SCRIPT_PATH."
fi
