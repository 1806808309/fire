#pragma once
#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>
#include<vector>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<fstream>
using namespace std;
using namespace cv;
typedef vector<vector<uchar>> VecGLCM;
void VecGLCMCount0(VecGLCM& GM_VecGLCM, cv::Mat PriImage, int nCols, int nRows);  //0�ȹ�������
void VecGLCMCount45(VecGLCM& GM_VecGLCM, cv::Mat PriImage, int nCols, int nRows); //45��
void VecGLCMCount90(VecGLCM& GM_VecGLCM, cv::Mat PriImage, int nCols, int nRows); //90��
void VecGLCMCount135(VecGLCM& GM_VecGLCM, cv::Mat PriImage, int nCols, int nRows); //135��
double ComputeEntropy(VecGLCM& GM_VecGLCM, int size);       //������ֵ
double ComputeEnergy(VecGLCM& GM_VecGLCM, int size);        //��������
double ComputeContrast(VecGLCM& GM_VecGLCM, int size);      //����Աȶ� 
double ComputeUniformity(VecGLCM& GM_VecGLCM, int size);    //������ȶ�
double ComputeCorrelation(VecGLCM& GM_VecGLCM, int size);   //���������
vector<vector<double>> ImageFileRead(string PatternJPG, VecGLCM& GM_VecGLCM, int size);     //������ȡͼƬ����
void ValueWrite(vector<vector<double>> Matrix, string FileName,int n);     //д����
void InitVecGLCM(VecGLCM& GM_VecGLCM, int size);     //��ʼ��VecGLCM

