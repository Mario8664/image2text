#include<iostream>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "GrayRatio.h"
using namespace std;
using namespace cv;
int main(int argc, char const *argv[])
{
	Mat res = ConvertPhotoToGray("hero-mario.png");
	PixelBlockSize pbs;
	pbs.Row = 3; pbs.Col = 2;
	auto r = CalcPixelBlockAverageRGB(res, pbs);
	uchar relex[208*186*3];
	long long i = 0;
	for (auto x : r)
	{
		for (auto y : x)
		{
			relex[i++] = y[0];
			relex[i++] = y[1];
			relex[i++] = y[2];
		}
	}
	Mat src = Mat(208,186, CV_8UC3, relex);
	imshow("r", src);
	waitKey(0);
    return 0;
}
