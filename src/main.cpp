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
	auto Original = ReadFile("Miku.png");
	PixelBlockSize pbs;
	pbs.Row = 6; pbs.Col = 3 ;
	auto r = CalcPixelBlockAverageRGB(Original, pbs);
	ToText(r);
	imshow("pyt", Original);
	waitKey(0);
	cin.get();
	return 0;
}
