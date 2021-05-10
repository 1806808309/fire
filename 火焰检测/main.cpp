#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\imgproc\types_c.h>
#include"FireDetection.h"

using namespace std;
using namespace cv;
void ShowHistogram(Mat& Orimage);   //��ʾֱ��ͼ


int main()
{
	Mat image = imread("E:\\ѧϰ����\\��һ��\\��Ƶͼ����_é\\homework3\\������\\image6.jpg");
	if (image.empty()) {
		cout << "ͼƬ��ȡʧ�ܣ�" << endl;
	}
	imshow("Original Image", image);
	//imshow("firedetection", FireDetection(image));
	ShowHistogram(image);
	waitKey(0);
	return 0;
}

void ShowHistogram(Mat& Orimage) 
{
	int* redHistogram = new int[256];
	int* greenHistogram = new int[256];
	int* blueHistogram = new int[256];
	memset(redHistogram, 0, 256 * sizeof(int));
	memset(greenHistogram, 0, 256 * sizeof(int));
	memset(blueHistogram, 0, 256 * sizeof(int));

	Mat image = Orimage.clone();
	uchar* p;
	//����������Ԫ�ط����ֱ��������������
	for (int n = 0; n <= 2; n++)
	{
		for (int i = 0; i < image.rows; i++)
		{
			for (int j = 0; j < image.cols; j++)
			{
				switch (n) {
				case 0:redHistogram[(int)image.at<Vec3b>(i, j)[0]]++; break;
				case 1:greenHistogram[(int)image.at<Vec3b>(i, j)[1]]++; break;
				case 2:blueHistogram[(int)image.at<Vec3b>(i, j)[2]]++; break;
				}
			}
		}
		
	}

	for (int i = 0; i <= 255; i++)
	{
		cout << "��ɫ����Ϊ�� " << i << "  �ĸ����� " << redHistogram[i] << endl;
	}

	for (int i = 0; i <= 255; i++)
	{
		cout << "��ɫ����Ϊ�� " << i << "  �ĸ����� " << greenHistogram[i] << endl;
	}

	for (int i = 0; i <= 255; i++)
	{
		cout << "��ɫ����Ϊ�� " << i << "  �ĸ����� " << blueHistogram[i] << endl;
	}

	//�ҵ�ÿһ��ֱ��ͼͳ�ƾ�������ֵ
	int Max_redhi = 0;
	int Max_greenhi = 0;
	int Max_bluehi = 0;
	for (int i = 0; i < 256; i++)
	{
		if (redHistogram[i] >= Max_redhi) Max_redhi = redHistogram[i];
		if (greenHistogram[i] >= Max_greenhi) Max_greenhi = greenHistogram[i];
		if (blueHistogram[i] >= Max_bluehi)Max_bluehi = blueHistogram[i];
	}
	
	Mat redhi_image =Mat::zeros(256, 256, CV_8UC3);
	Mat greenhi_image = Mat::zeros(266, 256, CV_8UC3);
	Mat bluehi_image = Mat::zeros(256, 256, CV_8UC3);

	//���ƺ�������Ԫ�ص�ֱ��ͼ
	//����ֱ��ͼ��Ҫ�õ�������rectangle(Mat& image,Point pt1,Point pt2,Scalar &color,int thickness=1,int lineType=8,intshift=0)
	/****     rectangle(cv::InputOutputArrar img  ������Mat���ͣ���ʾֱ��ͼͼƬ����ֱ��ͼ�洢�ڱ���img��
	*					Point pt1   Point�������ͣ���ʾ������������Ͻ����꣬��ͼƬΪ����x��ΪͼƬ������һ���߼���=0����(����Ϊ��������)
	*					Point pt2   ����һ�㣨�����Խǵ�ȷ��һ������
	*					Scalar &color  ��ɫ��0��0��0��Ϊ��ɫ��255��255��255��Ϊ��ɫ
	*					������������˼����
	* ��Ҫע��������������Ķ��壬x��Ϊ������һ���ߣ����򣺴�����
	)
	*     
	*************/
	for (int i = 0; i < 256; i++)
	{
		int RedValue = redHistogram[i] / Max_redhi * 256;
		rectangle(redhi_image, Point(i, 255), Point(i + 1, 255 - RedValue), Scalar(255, 0, 0));

		int GreenValue = greenHistogram[i] / Max_greenhi * 256;
		rectangle(greenhi_image, Point(i, 255), Point(i + 1, 255 - GreenValue), Scalar(0, 255, 0));

		int blueValue = blueHistogram[i] / Max_bluehi * 256;
		rectangle(bluehi_image, Point(i, 255), Point(i + 1, 255 - blueValue), Scalar(0, 0, 255));

	}

	imshow("redHistogram", redhi_image);
	imshow("greenHistogram", greenhi_image);
	imshow("blueHistogram", bluehi_image);

	delete[] redHistogram;
	delete[] greenHistogram;
	delete[] blueHistogram;


}