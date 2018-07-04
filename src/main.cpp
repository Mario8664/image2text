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
	Mat p = ConvertPhotoToGray("hero-mario.png");
	RemoveAlphaChannel(p);
	imwrite("remove.png", p);
	Mat res = imread("remove.png");
	PixelBlockSize pbs;
	pbs.Row = 6; pbs.Col = 3;
	auto r = CalcPixelBlockAverageRGB(res, pbs);
	ToText(r);
	/*uchar* relex=new uchar[(int)(r.size())*(int)r[0].size() * 3];
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
	Mat src((int)(r.size()), (int)r[0].size(), CV_8UC3,relex);*/
	imshow("src", p);
	waitKey(0);
    return 0;
}
