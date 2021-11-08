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
#   System
#       User: nx
#       Password: La1123.
#       Hostname: SBRNX
#       Wireless LAN: sbrapp / La12345678
#
#   copy the config.sh in the root and execute.

# In Host
# ssh-copy-id nx@sbrnx.local

# NVMe SSD Boot
# https://www.jetsonhacks.com/2021/08/25/native-boot-for-jetson-xaviers/


if [ ! -f exec01 ]; then
    # run your scripts here

    clear

    echo "This script install all the dependencies of the system"

    echo "****** Updating ******"
    sudo apt update
    sudo apt upgrade
    sudo apt dist-upgrade
    sudo apt autoremove

    echo "****** Creating Folders ******"
    mkdir SBR
    cd SBR
    mkdir Data

    echo "****** Uninstall unsed apps ******"
    uninstall all non use apps

    echo "****** Installing Applications ******"
    sudo apt install htop
    sudo apt install nano

    echo "****** Installing video******"
    sudo apt-get install xorg-dev libglu1-mesa-dev
    sudo apt-get install v4l-utils

    echo "****** Installing Serial lib ******"
    sudo apt install libudev-dev

    echo "****** Setup Docker ******"
    sudo apt-get install \
    apt-transport-https \
    ca-certificates \
    curl \
    gnupg \
    lsb-release

    sudo usermod -aG docker $USER

    sudo apt-get install -y libffi-dev libssl-dev
    sudo apt-get install -y python3 python3-pip
    sudo pip3 install --upgrade pip
    sudo pip3 install setuptools_rust
    sudo pip3 -v install docker-compose

    sudo systemctl enable docker.service
    sudo systemctl enable containerd.service

    echo "****** Installing IntelRealSense ******"
    cd
    git clone https://github.com/JetsonHacksNano/installLibrealsense.git
    cd installLibrealsense
    ./installLibrealsense.sh 


    # create a flag file to check if we are resuming from reboot.
    cd
    touch exec01
    sudo reboot
fi

if [ ! -f exec02 ]; then
    # run your scripts here

    echo "****** Turn off zram ******"
    cd /etc/systemd
    sudo mv nvzramconfig.sh nvzramconfig.sh.orig

    # create a flag file to check if we are resuming from reboot.
    cd
    touch exec02
    sudo reboot
fi


if [ ! -f exec03 ]; then
    # run your scripts here

    echo "****** Create swap file on NVMe ******"
    mkdir nvme
    sudo fallocate -l 100G /home/nx/nvme/swapfile
    sudo chmod 600 /home/nx/nvme/swapfile
    sudo mkswap /home/nx/nvme/swapfile
    sudo swapon /home/nx/nvme/swapfile
    sudo swapon -s
    echo "/home/nx/nvme/swapfile swap swap defaults 0 0" | sudo tee -a /etc/fstab
    
    # create a flag file to check if we are resuming from reboot.
    cd
    touch exec03
fi


echo "Cleaning"
cd
rm -f exec01
rm -f exec02
rm -f exec03

exit 0


# To disable GUI on boot
#   sudo systemctl set-default multi-user.target
# To enable GUI
#   sudo systemctl set-default graphical.target