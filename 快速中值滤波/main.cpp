/*
*  ʵ����ֵ�˲�(�㷨��Դ��A Fast Two-Dimensional Median Filtering Algorithm)
*  ������opencv4.4   debug  x64
*  �������ӣ�
*  ����ѧϰ
*/


#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\imgproc\types_c.h>


using namespace std;
using namespace cv;

void QuickMedianFluter(Mat OriImage, Mat& ResImage, int size);
int FindMedian(int H[], int n,int size,int &mNum);



int main()
{
	Mat image1 = imread("salt_pepper_Image.jpg",IMREAD_GRAYSCALE);
	if (image1.empty())
	{
		cout << "��ȡͼƬʧ�ܡ�" << endl;
	}
	imshow("Origin Image", image1);



	//��ֵ�˲�,����opencv�Դ��ĺ��� 
	Mat result1;
	medianBlur(image1, result1, 3);
	imshow("Result1 Image(after median fluter,opencv�Դ�)", result1);

	//������ֵ�˲��������Լ���д�ĺ���
	Mat result2;

	//ֱ��clone��ȥ���ɣ��м䲿�ֻ������˲����̵Ľ�����֮�ı�
	result2 = image1.clone();
	//ResImage = OriImage.clone();
	QuickMedianFluter(image1, result2, 3);
	imshow("Result2 Image(���ұ�д����)", result2);


	waitKey(0);
	return 0;
}



/***********************************************************
* �������ܣ���ֵ�˲�(����ֱ��ͼ������ʵ��)
* �������ܣ�OriInage:ԭͼ    ResImage:�˲����ͼ
*			size:�˲���(��������)�߳�����СΪsize x size(��3x3) 
***********************************************************/



void QuickMedianFluter(Mat OriImage, Mat& ResImage, int size)
{
	int m = OriImage.rows;   //m���У���Ӧ�����x
	int n = OriImage.cols;   //n���У���Ӧ�����n
	int *Histogram = new int[256];
	memset(Histogram, 0, 256 * sizeof(int));
	int radius = size / 2;    //�뾶
	int th = size * size / 2 + 1;    //�㷨�е�th
	int median = 0;     //����ֱ��ͼ�е���ֵ��Ӧ������
	int mNum = 0;       //����С����ֵ����median���ܸ���
	int left = 0;       //�����н�Ҫ�Ƴ���
	int right = 0;      //���ұ߽�Ҫ�����

	cout << "�У�" << m << endl;
	cout << "�У�" << n << endl;


	//����߽磬�߽�û��������ֵ�˲�����˽��߽��������ظ�ֵ��ResImage
	for (int i = radius; i < m - radius; i++)  //m���У���Ӧx��������
	{
		//��ʼ��Histogram
		memset(Histogram, 0, 256 * sizeof(int));
		for (int k = i-radius; k <= i+radius; k++)
		{
			for (int h = 0; h < size; h++)
			{
				Histogram[OriImage.at<uchar>(k, h)]++;
			}
		}
		median= FindMedian(Histogram, 256, size,mNum);
		ResImage.at<uchar>(i,radius) = median;


		for (int j = radius; j < n - radius; j++)   //n���У���Ӧy��������
		{
			//j��radius����ֱ��ͼ��������
			if (j == radius) continue;   
			//�����㷨�����������ƶ�һλ���������е����Ƴ�ֱ��ͼ��
			for (int k = i-radius; k <= i + radius; k++)
			{
				left = OriImage.at<uchar>(k, j - 1 - radius);
				Histogram[left]--;
				if (left <= median) mNum = mNum - 1;
			}
			
			//�����㷨�����������ƶ�һλ�������Ҳ��������ֱ��ͼ��
			for (int k = i-radius; k <= i + radius; k++)
			{
				right = OriImage.at<uchar>(k, j + radius);
				Histogram[right]++;
				if (right <= median) mNum = mNum + 1;
			}

			if (mNum == th)
			{
				ResImage.at<uchar>(i, j) = median;
				continue;

			}
			//����ǰһ��ֵ������С�ڵ�����ֵmedian����mNum,��ǰ��ֵ
			if (mNum < th)
			{
				//С��th(��th����Ϊ��ֵ)���ڵ�ǰmedian�ұߣ������ң����ؼ�һѰ�ң�
				while (mNum < th) {
					median = median + 1;
					mNum = mNum + Histogram[median];
				}
			}
			else {
				//����th(��th����Ϊ��ֵ)���ڵ�ǰmedian��ߣ������ң����ؼ�һѰ�ң�
				while (mNum > th)
				{
					mNum = mNum - Histogram[median];
					median = median - 1;
				}
			}
			ResImage.at<uchar>(i, j) = median;
			
		}
	}

	delete[] Histogram;
}

/**************************************************************
* �������ܣ�ͨ��ֱ��ͼ������ֵ
* �������ܣ�H[]:ֱ��ͼ����  n:ֱ��ͼά��
*			size:�˲����Ĵ�С
****************************************************************/



int FindMedian(int H[], int n,int size,int &mNum)
{
	int median = 0;   //��ʼ����ֵΪ0
	int sum_cout = 0;  //���
	int median_flag = size * size / 2;  //��ֵ��־
	for (int i = 0; i < 256; i++)
	{
		sum_cout += H[i];
		if (sum_cout > median_flag)
		{
			median = i;
			break;
		}
	}
	mNum = sum_cout;
	return median;
}

