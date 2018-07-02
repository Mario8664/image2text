#ifndef GRAYRATIO_H_
#define GRAYRATIO_H_
#include<cv.h>
#include<cstring>

double CalcCharGraphGrayRatio(char base, std::string _symbol_path);
cv::Mat ConvertPhotoToGray(std::string Photo_Path);
#endif // !GRAYRATIO_H