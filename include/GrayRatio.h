#ifndef GRAYRATIO_H_
#define GRAYRATIO_H_
#include"opencv/cv.h"
#include<cstring>
#include<vector>
typedef struct {
	int Col;
	int Row;
} PixelBlockSize;
double CalcCharGraphGrayRatio(char base, std::string _symbol_path);
char ToChar(cv::Vec3b Color);
void ToText(std::vector<std::vector<cv::Vec3b>> CalcPixelBlockAverageRGB);
cv::Mat ConvertPhotoToGray(std::string Photo_Path);
std::vector<std::vector<cv::Vec3b>> CalcPixelBlockAverageRGB(cv::Mat &ImageMatrix, PixelBlockSize _BlockSize);
bool RemoveAlphaChannel(cv::Mat& Source);
#endif // !GRAYRATIO_H