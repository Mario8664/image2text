#!/bin/bash
echo "Auto configure compile environment..."
 sudo apt-get install -y build-essential
 sudo apt-get install -y cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
 sudo apt-get install -y python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
 curl -sL https://github.com/opencv/opencv/archive/3.4.1.zip > opencv.zip
 unzip opencv.zip
 cd opencv-3.4.1
 mkdir build
 cd build
 cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_OPENGL=ON ..

 make -j4
  
  # Install to OS.
 sudo make install
  # Add configuration to OpenCV to tell it where the library files are located on the file system (/usr/local/lib)
 sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
 sudo ldconfig
 echo "OpenCV installed."
 cd ../../..

 mkdir bin && cd bin
 cmake ..
 make

 echo "Image2Text build successfully."