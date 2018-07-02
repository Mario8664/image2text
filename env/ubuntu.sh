#!/bin/bash

echo "Auto configurae development environment for image2text"
sudo apt-get -y update
sudo apt-get -y install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
echo "Downloading source code of OpenCV"
curl -sL https://github.com/opencv/opencv/archive/3.4.1.zip > opencv.zip
unzip opencv.zip
cd opencv-3.4.1
mkdir build && cd build
cmake ..
make -j8
sudo make install
sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig
echo "OpenCV installed"

cd ../../..
mkdir bin && cd bin
cmake ..
make
