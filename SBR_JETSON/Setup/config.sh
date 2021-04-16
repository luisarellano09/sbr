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
#       Wireless LAN: sbrapp / La123456
#
#   copy the config.sh in the root and execute.


if [ ! -f exec01 ]; then
    # run your scripts here

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

    echo "****** Uninstall unsed apps ******"
    uninstall all non use apps

    echo "****** Installing Applications ******"
    sudo apt install htop
    sudo apt install nano

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
    sudo apt-get remove python-configparser
    sudo pip3 install setuptools_rust
    pip install --upgrade pip
    sudo pip3 -v install docker-compose

    echo "****** Setup NVMe ******"
    sudo mkfs.ext4 /dev/nvme0n1
    sudo mkdir /home/nx/nvme
    sudo mount /dev/nvme0n1 /home/nx/nvme
    echo "/dev/nvme0n1 /home/nx/nvme ext4 defaults 0 1" | sudo tee -a /etc/fstab

    # create a flag file to check if we are resuming from reboot.
    cd
    touch exec01
    sudo reboot
fi

if [ ! -f exec02 ]; then
    # run your scripts here

    echo "****** Setup Docker in NVMe ******"
    sudo mv /var/lib/docker /home/nx/nvme
    sudo ln -s /home/nx/nvme/docker /var/lib/docker

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