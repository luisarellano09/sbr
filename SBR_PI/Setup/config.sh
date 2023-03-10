#################################################################
#                                                               #
#   config.sh                                                   #
#                                                               #
#   This script install all the dependencies of the system      #
#                                                               #
#   sh config.sh                                                #
#                                                               #
#################################################################

# Previous Steps
#   sudo raspi-config
#       System Options
#           Wireless LAN: sbrap / La123456
#           Password: La1123.
#           Hostname: SBRPI
#           Boot/Auto Login: B2 Console Autologin
#       Interface Options
#           Camera: disable
#           SSH: enable
#           VNC: disable
#           SPI: disable
#           I2C: disable
#           Serial Port: No Shell / enable
#           Wire: disable
#           Remote GPIO: disable
#
#   copy the config.sh in the root and execute.
#

# In Host
# ssh-copy-id pi@sbrpi.local


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


echo "****** Installing Docker ******"
sudo apt-get install \
    apt-transport-https \
    ca-certificates \
    curl \
    gnupg \
    lsb-release

curl -sSL https://get.docker.com | sh

sudo usermod -aG docker $USER

sudo apt-get install -y libffi-dev libssl-dev
sudo apt-get install -y python3 python3-pip
sudo apt-get remove python-configparser
sudo pip3 -v install docker-compose

echo "****** Installing Serial lib ******"
sudo apt install libudev-dev

echo "****** Installing Rust ******"
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh


exit 0