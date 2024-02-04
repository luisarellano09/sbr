https://www.freva.com/assign-fixed-usb-port-names-to-your-raspberry-pi/


sudo nano /etc/udev/rules.d/10-usb-serial.rules

KERNEL=="ttyAMA0" SUBSYSTEM=="tty", SYMLINK+="ttyUSB_ESP32_NODE_LINUX"
SUBSYSTEM=="tty", ATTRS{idProduct}=="ea60", ATTRS{idVendor}=="10c4", ATTRS{busnum}=="1", ATTRS{devpath}=="1", SYMLINK+="ttyUSB_ESP32_NODE_MANAGER"
SUBSYSTEM=="tty", ATTRS{idProduct}=="ea60", ATTRS{idVendor}=="10c4", ATTRS{busnum}=="3", ATTRS{devpath}=="1", SYMLINK+="ttyUSB_ESP32_NODE_01"

sudo udevadm trigger
