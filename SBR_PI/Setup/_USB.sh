https://www.freva.com/assign-fixed-usb-port-names-to-your-raspberry-pi/


sudo nano /etc/udev/rules.d/10-usb-serial.rules

SUBSYSTEM=="tty", ATTRS{idProduct}=="2303", ATTRS{idVendor}=="067b", SYMLINK+="ttyUSB_ESP32_NODE_LINUX"
SUBSYSTEM=="tty", ATTRS{idProduct}=="ea60", ATTRS{idVendor}=="10c4", ATTRS{devpath}=="1.1", SYMLINK+="ttyUSB_ESP32_NODE_01"
SUBSYSTEM=="tty", ATTRS{idProduct}=="ea60", ATTRS{idVendor}=="10c4", ATTRS{devpath}=="1.2", SYMLINK+="ttyUSB_ESP32_NODE_MANAGER"

sudo udevadm trigger
