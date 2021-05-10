
#include<opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>  
//#include <opencv2/imgproc/imgproc.hpp>  
//#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/highgui/highgui_c.h>
using namespace std;

void onMouse(int event, int x, int y, int flags, void* param)
{
	cv::Mat* im = reinterpret_cast<cv::Mat*>(param);
	switch (event) {
	case CV_EVENT_LBUTTONDOWN:
		cout << "at(" << x << "," << y << ")pixs value is:(R,G,B)=(" << static_cast<int>
			(im->at<cv::Vec3b>(cv::Point(x, y))[2]) <<","<< static_cast<int>
			(im->at<cv::Vec3b>(cv::Point(x, y))[1]) <<","<< static_cast<int>
			(im->at<cv::Vec3b>(cv::Point(x, y))[0]) <<")"<< endl;

		break;
	}
}

int main()
{
	cv::Mat image = cv::imread("E:\\ѧϰ����\\��һ��\\��Ƶͼ����_é\\homework_NeedHandIn\\������\\image6.jpg");//��ȡͼƬ
	if (image.empty())
	{
		cout << "��ȡͼƬʧ��" << endl;
	}
	
	cv::namedWindow("ԭʼͼ��");
	cv::setMouseCallback("ԭʼͼ��", onMouse, reinterpret_cast<void*>(&image));
	cv::imshow("ԭʼͼ��", image);
	cv::waitKey(0);
	return 0;
}

