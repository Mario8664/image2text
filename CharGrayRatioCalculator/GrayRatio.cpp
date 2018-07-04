#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
/*	For the best compatibility with VS and CMake, make sure that include head file like this way
	#include "opencv/xxx.h" <- with "opencv/opencv2" prefix.
*/
#include <iostream>
#include <cstring>
#include<memory>
#include "GrayRatio.h"
using namespace cv;
IplImage* ImageHandle;
/*
This is a simple tool that can return gray ratio of a specified char graph.
Use together with GenerateCharGraph.py
*/
double CalcCharGraphGrayRatio(char base, std::string _symbol_path = "AllFontSymbol/")
{

	std::string path = _symbol_path + std::to_string(base) + ".jpg";
	if (!(33 <= base && base <= 126))
	{
		std::cerr << "Parsed char out of range" << std::endl;
		exit(1);
	}
	ImageHandle = cvLoadImage(path.c_str());
	if (ImageHandle == NULL)
	{
		std::cerr << "Can not open this image" << std::endl;
		exit(1);
	}
	unsigned long long black = 0, white = 0;
	for (int i = 0; i < ImageHandle->height; ++i)
		for (int j = 0; j < ImageHandle->width; j++)
		{
			CvScalar cvs = cvGet2D(ImageHandle, i, j);
			if (cvs.val[2] >= 128) white++;
			else black++;
		}

	return (double)(black) / (black + white);
}
cv::Mat ConvertPhotoToGray(std::string Photo_Path)
{
	Mat Original = imread(Photo_Path, -1);//flags <0 is to read the alpha infomation
	Mat Gray;
	if (Original.empty())
	{
		std::cerr << "Can not open image." << std::endl;
		exit(1);
	}
	if (Original.channels() > 3) //Need to remove alpha channel
	{
		RemoveAlphaChannel(Original);
	}
	cvtColor(Original, Gray, CV_BGRA2GRAY);
	/*
		This function will return a Mat, a useful image format in OpenCV.
		You can read the RGB of each pixel like below.
	*/
	//for (int i = 0; i < Original.rows; ++i)
	//{
	//	Vec4b *p = Original.ptr<Vec4b>(i);
	//	Vec3b *q = Gray.ptr<Vec3b>(i);
	//	for (int j = 0; j < Original.cols; ++j)
	//	{
	//		q[j][0] = p[j][0] * (bool)p[j][3]; //Blue
	//		q[j][1] = p[j][1] * (bool)p[j][3]; //Green
	//		q[j][2] = p[j][2] * (bool)p[j][3]; //Red
	//		std::cout << (int)p[j][3] << " ";//Alpha
	//	}
	//}
	//std::cout << Gray.channels() << std::endl;
	//Gray.channels[0] = Original.channels[0] * Original.channels[3];
	//Gray.channels[1] = Original.channels[1] * Original.channels[3];
	//Gray.channels[2] = Original.channels[2] * Original.channels[3];
	return Gray;
}

std::vector<std::vector<cv::Vec3b>> CalcPixelBlockAverageRGB(cv::Mat & ImageMatrix, PixelBlockSize _BlockSize)
{
	std::vector<std::vector<cv::Vec3b>> AveVec;//To save each rgb of "block" specified
	//Process edge
	int nRows = ImageMatrix.rows, nCols = ImageMatrix.cols;
	_BlockSize.Col = _BlockSize.Col > nCols ? nCols : _BlockSize.Col;
	_BlockSize.Row = _BlockSize.Row > nRows ? nRows : _BlockSize.Row;
	for (int i = 0; i < nRows; i += _BlockSize.Row)
	{
		std::vector<cv::Vec3b> vec;
		for (int j = 0; j < nCols; j += _BlockSize.Col)
		{
			//Each block is specified by left_up position (i,j) , right_down position (i+_BlockSize.Col,j+_BlockSize.Row)
			unsigned long long Rs = 0, Gs = 0, Bs = 0, Time = 0;
			for (int n = i; n < (i + _BlockSize.Row > nRows ? nRows : i + _BlockSize.Row); ++n) //Limit the edge
			{
				Vec3b * ptr = ImageMatrix.ptr<Vec3b>(n);
				for (int m = j; m < (j + _BlockSize.Col > nCols ? nCols : j + _BlockSize.Col); m++)
				{
					
					Rs += (int)ptr[m][2];
					Gs += (int)ptr[m][1];
					Bs += (int)ptr[m][0];
					Time++;
				}
			}
			if (Time > 0)
			{
				Rs /= Time;
				Gs /= Time;
				Bs /= Time;
				cv::Vec3b vc3b;
				vc3b[2] = Rs;
				vc3b[1] = Gs;
				vc3b[0] = Bs;
				vec.push_back(vc3b);
				//std::cout << Rs<<" " << Gs << " " << Bs << std::endl;
			}
		}
		AveVec.push_back(vec);
	}
	return AveVec;
}

bool RemoveAlphaChannel(cv::Mat & Source)
{
	if (Source.channels() < 4) return false;
	for (int i = 0; i < Source.rows; ++i)
	{
		Vec4b *p = Source.ptr<Vec4b>(i);
		for (int j = 0; j < Source.cols; ++j)
		{
			if ((int)p[j][3] < 255)
			{
				p[j][0] = 255;
				p[j][1] = 255;
				p[j][2] = 255;
			}
		}
	}
	return true;
}
