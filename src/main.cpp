#include<iostream>
#include<GrayRatio.h>
#include"opencv/cv.hpp"
using namespace std;
int main(int argc, char const *argv[])
{
	/*
		If it's your first time to open this solution in VS2017, you need to set the properties of
		this project.
		
		VC++ Directory -> Include Directory and Library Directory -> Set the OpenCV path in your computer.

		if you are coding in Linux, unless you had modified the install path of OpenCV, our cmake script
		had been configured all the lib path and include path correctly. Just tap your kb!
			
		This is a simple function that convert a colorful photo to gray.
		if it popups a window normally, means that you have configured all the environment
		successfully.
	*/
	auto Result = ConvertPhotoToGray("F:/CLJ.bmp");
	cv::imshow("Result", Result);
	cv::waitKey();
    return 0;
}
