#################################################################
#                                                               #
#   config.sh                                                   #
#                                                               #
#   This script install all the dependencies of the system      #
#                                                               #
#   sudo sh config.sh                                           #
#                                                               #
#################################################################

# Previous Steps
#
#   copy the config.sh in the root and execute.
#



clear

echo "This script install all the dependencies of the system"

echo "****** Updating ******"
sudo apt update
sudo apt upgrade
sudo apt dist-upgrade

echo "****** Creating Folders ******"
mkdir SBR
cd SBR
mkdir Data



exit 0