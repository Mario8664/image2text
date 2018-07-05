#include<iostream>
#include<io.h>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "GrayRatio.h"
using namespace std;
using namespace cv;
int main(int argc, char const *argv[])
{
	//Prepare for the next steps.
	Mat Original = imread("hero-mario.png", -1);//flags <0 is to read the alpha infomation
	if (Original.empty())
	{
		std::cerr << "Can not open image." << std::endl;
		exit(1);
	}
	if (Original.channels() > 3) //Need to remove alpha channel
	{
		RemoveAlphaChannel(Original);
	}
	PixelBlockSize pbs;
	pbs.Row = 2; pbs.Col = 1 ;
	auto r = CalcPixelBlockAverageRGB(Original, pbs);
	ToText(r);
	imshow("pyt", Original);
	waitKey(0);
	cin.get();
	return 0;
}
