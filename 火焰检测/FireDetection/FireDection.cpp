#include"FireDetection.h"

/*�����㷨���£�
	R>=G>=B����R>=R_mean
	�Ľ��㷨������������ɫ�����Ļ�������������������
	������Ƶ�Ļ������㷨��������ɫ����̬������ѡ���̽�ⷽ��

*/


Mat FireDetection(Mat& image)
{
	Mat BinImage = Mat::zeros(image.rows, image.cols, CV_8UC1);
	int RedValue;
	int GreenValue;
	int BlueValue;
	int RedMean=0;
	int RedCount = 0;


	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			RedCount += image.at<Vec3b>(i, j)[0];
		}
		RedMean += RedCount / image.cols;
		RedCount = 0;
	}
	RedMean = RedMean / image.rows;
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			//��ͨ������˳����B,G,R
			RedValue = image.at<Vec3b>(i, j)[2];
			GreenValue = image.at<Vec3b>(i, j)[1];
			BlueValue = image.at<Vec3b>(i, j)[0];
			//cout << "(" << RedValue << "," << GreenValue << "," << BlueValue << ")";
			BinImage.at<uchar>(i, j) = (RedValue >= GreenValue && GreenValue >= BlueValue && RedValue >= RedMean) ? 255 : 0;
		}
		//cout << endl;
	}
	return BinImage;
}

Mat FireDetectionHSV(Mat& image)	//����HSV������ֵ���л�����
{
	Mat imageHSV;
	cvtColor(image, imageHSV, CV_BGR2HSV);
	Mat BinaryImage = Mat::zeros(image.rows, image.cols, CV_8UC1);
	for (int i = 0; i < imageHSV.rows; i++)
	{
		for (int j = 0; j < imageHSV.cols; j++)
		{
			int value_h = imageHSV.at<cv::Vec3b>(i, j)[0];
			int value_s = imageHSV.at<cv::Vec3b>(i, j)[1];
			int value_v = imageHSV.at<cv::Vec3b>(i, j)[2];
			if ((value_h >= 0 && value_h <= 60) && (value_s <= 255 && value_s >= 160) && (value_v <= 255 && value_v >= 160))
			{
				BinaryImage.at<uchar>(i, j) = 255;
				image.at<cv::Vec3b>(i, j)[0] = 0;
				image.at<cv::Vec3b>(i, j)[1] = 255;
				image.at<cv::Vec3b>(i, j)[2] = 0;
			}
		}
	}

	return BinaryImage;

}