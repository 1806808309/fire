#pragma once
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\imgproc\types_c.h>

using namespace std;
using namespace cv;

Mat FireDetection(Mat& image);  //����R>=G>=B����R>=R_mean�����л�����
Mat FireDetectionHSV(Mat& image);	//����HSV������ֵ���л�����
