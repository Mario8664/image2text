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
	imshow("Re", res);
	waitKey(0);
    return 0;
}
