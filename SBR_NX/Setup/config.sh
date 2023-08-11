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
#       User: sbrnx
#       Password: La1123.
#       Hostname: sbrnx
#       Wireless LAN: sbrap / La123456
#
#   copy the config.sh in the root and execute.

# In Host
# ssh-copy-id sbrnx@sbrnx.local

# NVMe SSD Boot
# https://www.jetsonhacks.com/2021/08/25/native-boot-for-jetson-xaviers/


if [ ! -f exec01 ]; then
    # run your scripts here

    clear

    echo "This script install all the dependencies of the system"

    echo "****** Updating ******"
    sudo apt update
    sudo apt upgrade
    sudo apt autoremove

    sudo usermod -a -G sudo sbrnx
    # sudo visudo
    # add at the last line
    # sbrnx ALL=(ALL) NOPASSWD: ALL

    echo "****** Creating Folders ******"
    mkdir SBR
    cd SBR
    mkdir data

    echo "****** Installing Applications ******"
    sudo apt install htop
    sudo apt install nano

    echo "****** Installing video******"
    sudo apt-get install xorg-dev libglu1-mesa-dev
    sudo apt-get install v4l-utils

    echo "****** Installing Serial lib ******"
    sudo apt install libudev-dev

    echo "****** Installing JTOP ******"
    sudo apt install python3-pip
    sudo pip3 install -U jetson-stats

    echo "****** Setup Docker ******"
    sudo apt-get update
    sudo apt-get install ca-certificates curl gnupg
    sudo install -m 0755 -d /etc/apt/keyrings
    curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
    echo \
    "deb [arch="$(dpkg --print-architecture)" signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
    "$(. /etc/os-release && echo "$VERSION_CODENAME")" stable" | \
    sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

    sudo apt-get update
    sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
    sudo groupadd docker
    sudo usermod -aG docker $USER
    sudo systemctl enable docker.service
    sudo systemctl enable containerd.service

    echo "****** Installing IntelRealSense ******"
    cd
    git clone https://github.com/JetsonHacksNano/installLibrealsense.git
    cd installLibrealsense
    ./installLibrealsense.sh 

    echo "****** Installing OpenCV with Cuda ******"
    cd
    git clone https://github.com/mdegans/nano_build_opencv.git
    cd nano_build_opencv
    ./build_opencv.sh 4.8.0

    echo "****** Installing Jetpack ******"
    sudo apt install nvidia-jetpack -y
    sudo apt update
    sudo apt dist-upgrade

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
    sudo fallocate -l 50G /home/sbrnx/nvme/swapfile
    sudo chmod 600 /home/sbrnx/nvme/swapfile
    sudo mkswap /home/sbrnx/nvme/swapfile
    sudo swapon /home/sbrnx/nvme/swapfile
    sudo swapon -s
    echo "/home/sbrnx/nvme/swapfile swap swap defaults 0 0" | sudo tee -a /etc/fstab
    
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
