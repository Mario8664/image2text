#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <cstring>
using namespace cv;
IplImage* ImageHandle;
/*
This is a simple tool that can return gray ratio of a specified char graph.
Use together with GenerateCharGraph.py
*/
double CalcGrayRatio(char base,std::string _symbol_path="AllFontSymbol/")
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