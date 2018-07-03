#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
/*	For the best compatibility with VS and CMake, make sure that include head file like this way
	#include "opencv/xxx.h" <- with "opencv/opencv2" prefix.
*/
#include <iostream>
#include <cstring>
using namespace cv;
IplImage* ImageHandle;
/*
This is a simple tool that can return gray ratio of a specified char graph.
Use together with GenerateCharGraph.py
*/
double CalcCharGraphGrayRatio(char base,std::string _symbol_path="AllFontSymbol/")
{
    std::string path=_symbol_path+std::to_string(base)+".jpg";
    if(!(33<=base && base <=126))
    {
        std::cerr<<"Parsed char out of range"<<std::endl;
        exit(1);
    }
    ImageHandle=cvLoadImage(path.c_str());
    if(ImageHandle==NULL)
    {
        std::cerr<<"Can not open this image"<<std::endl;
        exit(1);
    }
    unsigned long long black=0,white=0;
    for(int i=0;i<ImageHandle->height;++i)
        for(int j=0;j<ImageHandle->width;j++)
        {
            CvScalar cvs=cvGet2D(ImageHandle,i,j);
            if (cvs.val[2] >= 128) white++;
			else black++;
        }
    return (double)(black)/(black+white);
}


cv::Mat ConvertPhotoToGray(std::string Photo_Path)
{
	Mat Original = imread(Photo_Path,-1);//flags <0 is to read the alpha infomation
	Mat Gray(Original.size(),3);
	if (Original.empty())
	{
		std::cerr << "Can not open image." << std::endl;
		exit(1);
	}
	cvtColor(Original, Gray, COLOR_RGBA2RGB);
	//cvtColor(Original, Gray, CV_BGRA2RGB);
	/*
		This function will return a Mat, a useful image format in OpenCV.
		You can read the RGB of each pixel like below.
	*/
	//for (int i = 0; i < Gray.rows; ++i)
	//{
	//	Vec3b *p = Gray.ptr<Vec3b>(i);
	//	for (int j = 0; j < Gray.cols; ++j)
	//	{
	//		std::cout<<(int)p[j][0]<<" "; //Blue
	//		std::cout << (int)p[j][1] << " "; //Green
	//		std::cout << (int)p[j][2] << std::endl; //Red
	//	}
	//}
	for (int i = 0; i < Original.rows; ++i)
	{
		Vec4b *p = Original.ptr<Vec4b>(i);
		Vec3b *q = Gray.ptr<Vec3b>(i);
		for (int j = 0; j < Original.cols; ++j)
		{
			q[j][0] = p[j][0] * (bool)p[j][3]; //Blue
			q[j][1] = p[j][1] * (bool)p[j][3]; //Green
			q[j][2] = p[j][2] * (bool)p[j][3]; //Red
			//std::cout << (int)p[j][3] << " ";//Alpha
		}
	}
	std::cout << Gray.channels() << std::endl;
	//Gray.channels[0] = Original.channels[0] * Original.channels[3];
	//Gray.channels[1] = Original.channels[1] * Original.channels[3];
	//Gray.channels[2] = Original.channels[2] * Original.channels[3];

	
	return Gray;
}