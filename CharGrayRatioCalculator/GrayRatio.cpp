#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
/*	For the best compatibility with VS and CMake, make sure that include head file like this way
	#include "opencv/xxx.h" <- with "opencv/opencv2" prefix.
*/
#include <iostream>
#include <vector>
#include <cstring>
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

char ToChar(Vec3b Color)
{
	struct CharAndLevel
	{
		int a;
		int b;
	};
	CharAndLevel TextColor[95]=
	{ {' ', 0}, { '`',0 },
	{ '.',1 }, { '\'',1 }, { ',',1 },
	{ ':',2 }, { ';',2 }, { '-',2 },
	{ '"',3 }, { '~',3 }, { '^',3 },
	{ '_',4 }, { '!',4 }, { '|',4 },
	{ '\\',5 }, { '/',5 }, { '(',5 }, { ')',5 }, { '{',5 }, { '*',5 },
	{ '+',6 }, { '}',6 }, { '?',6 }, { 'i',6 }, { '7',6 }, { ']',6 }, { '[',6 }, { '>',6 }, { '<',6 }, { 'l',6 },
	{ '=',7 }, { '1',7 }, { 'r',7 }, { '%',7 }, { 't',7 }, { 'v',7 }, { 'I',7 }, { 'c',7 },
	{ 'j',8 }, { 'o',8 }, { 'z',8 }, { 'u',8 }, { 'J',8 }, { 'n',8 }, { 'L',8 }, { 's',8 },
	{ 'Y',9 }, { '3',9 }, { 'C',9 }, { '&',9 }, { 'f',9 }, { '2',9 }, { '0',9 }, { 'x',9 }, { 'a',9 }, { 'V',9 }, { '@',9 }, { '4',9 }, { '5',9 }, { 'w',9 },
	{ 'O',10 }, { 'y',10 }, { 'e',10 }, { 'k',10 }, { 'T',10 }, { 'h',10 }, { '6',10 }, { '9',10 }, { 'P',10 }, { 'Z',10 }, { 'U',10 }, { 'S',10 }, { '$',10 }, { 'D',10 },
	{ 'F',11 }, { 'b',11 }, { 'G',11 }, { '8',11 }, { 'd',11 }, { 'm',11 }, { 'X',11 }, { 'A',11 },
	{ 'p',12 }, { 'q',12 }, { 'g',12 }, { 'R',12 }, { 'K',12 }, { 'H',12 }, { 'E',12 }, { 'B',12 },
	{ '#',13 }, { 'N',13 }, { 'Q',13 },
	{ 'W',14 },
	{ 'M',15 }};
	double Base = ((double)Color[0]* 0.114 + (double)Color[1]* 0.587 + (double)Color[2]* 0.299) / 255 * 15;
	Base = 15 - Base;
	//If cmd output, Base=15-Base;
	//Choose the level of char
	int Begin, End, Detail;
	for (int i = 0; i < 95; i++)
	{
		if (TextColor[i].b <= (int)(Base))
		{
			Begin = i;
			End = Begin;
		}
		else
		{
			End = i;
			break;
		}
	}
	//Divide the color in the same level to different level
	//For more details
	if (Begin == End)
		Detail = Begin;
	else
	{
		Detail = Begin + (int)(Base - 95.0 / 15.0*(int)(Base)) / (95.0 / 15);
	}

	return TextColor[Detail].a;
}

void ToText(std::vector<std::vector<cv::Vec3b>> CalcPixelBlockAverageRGB)
{
	for (auto X : CalcPixelBlockAverageRGB)
	{
		for (auto Y : X)
		{
			char a = ToChar(Y);
			std::cout<<a;
		}
		std::cout << std::endl;
	}
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

cv::Mat ReadFile(std::string File_Path)
{
	Mat Original = imread(File_Path, -1);//flags <0 is to read the alpha infomation
	if (Original.empty())
	{
		std::cerr << "Can not open image." << std::endl;
		exit(1);
	}
	if (Original.channels() > 3) //Need to remove alpha channel
	{
		RemoveAlphaChannel(Original);
	}
	return Original;
}

void RemoveAlphaChannel(cv::Mat & Source)
{
	Mat ch[4];
	split(Source, ch);
	merge(ch, 3, Source);
	Source.setTo(Scalar::all(255),ch[3]<255);
}

