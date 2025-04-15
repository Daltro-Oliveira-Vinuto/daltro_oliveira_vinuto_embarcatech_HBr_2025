#!/bin/bash
# Author: Daltro Oliveira Vinuto

clear
sudo apt install cmake python3 build-essential gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
cd /home/${USER}
rm -rf $(pwd)/pico-sdk
git clone https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init 
cd ..
export PICO_SDK_PATH=/home/${USER}/pico-sdk
export PICO_BOARD=pico_w
export PICOTOOL_FETCH_FROM_GIT_PATH=https://github.com/raspberrypi/pico-sdk.git
echo "PICO_SDK_PATH=/home/${USER}/pico-sdk" >> ~/.bashrc
echo "PICO_BOARD=pico_w" >> ~/.bashrc
echo "PICOTOOL_FETCH_FROM_GIT_PATH=https://github.com/raspberrypi/pico-sdk.git" >> ~/.bashrc
source ~/.bashrc

rm -rf $(pwd)/picotool
git clone https://github.com/raspberrypi/picotool.git
cd picotool
sudo cp $(pwd)/udev/99-picotool.rules /etc/udev/rules.d/
mkdir build
cd build
cmake ..
make
sudo ln -fs $(pwd)/picotool /usr/local/bin/picotool





