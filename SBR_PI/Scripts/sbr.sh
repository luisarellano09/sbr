#!/bin/bash

# Define menu options
OPTIONS=(
  "Option 1" "Description for Option 1"
  "Option 2" "Description for Option 2"
  "Option 3" "Description for Option 3"
  "Option 4" "Description for Option 4"
)

# Show the menu using whiptail
CHOICE=$(whiptail --title "SBR Menu" --menu "Choose an option:" 15 60 5 "${OPTIONS[@]}" 3>&1 1>&2 2>&3)

# Check the exit status to see if the user pressed Cancel or OK
if [ $? -eq 0 ]; then
  # User made a selection
  case "$CHOICE" in
    "Option 1")
      # Action for Option 1
      ;;
    "Option 2")
      # Action for Option 2
      ;;
    "Option 3")
      # Action for Option 3
      ;;
    "Option 4")
      # Action for Option 4
      ;;
  esac
else
  # User pressed Cancel or closed the menu
  echo "Menu canceled."
fi
