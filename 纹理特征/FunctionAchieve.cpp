#include"GLCM_GM.h"

//==============================================================================
// ��������: VecGLCMCount0
// ����˵��: PriImageΪ��ʼ��ͼƬ��nColsΪ�У�nRowsΪ����
// ��������: ����0�ȷ���Ĺ���������� 
//==============================================================================

void VecGLCMCount0(VecGLCM& GM_VecGLCM, cv::Mat PriImage, int nCols, int nRows)
{
	int VecGLCM_Col;
	int VecGLCM_Row;
	uchar* p;
	for (int i = 0; i < nRows; i++)
	{
		p = PriImage.ptr<uchar>(i);//��ȡÿ���׵�ַ
		for (int j = 0; j < nCols - 1; ++j)
		{
			VecGLCM_Col = p[j];
			VecGLCM_Row = p[j + 1];
			GM_VecGLCM[VecGLCM_Col][VecGLCM_Row]++;
		}
	}
}


//��1����Ϊ45�ȷ���ǰ��Ĳ�0�ȷ���
/*
void VecGLCMCount45(VecGLCM& GM_VecGLCM, cv::Mat PriImage, int nCols, int nRows)
{
	int VecGLCM_Col;
	int VecGLCM_Row;
	for (int i = 0; i < nRows-1; i++)
	{
		for (int j = 0; j < nCols-1; j++)
		{
			VecGLCM_Col = PriImage.at<uchar>(i, j);
			VecGLCM_Row = PriImage.at<uchar>(i + 1, j + 1);
			GM_VecGLCM[VecGLCM_Col][VecGLCM_Row]++;
		}
	}
}
*/

void VecGLCMCount45(VecGLCM& GM_VecGLCM, cv::Mat PriImage, int nCols, int nRows)
{
	int VecGLCM_Col;
	int VecGLCM_Row;
	uchar* p;
	uchar* p1;
	for (int i = 0; i < nRows-1; i++)
	{
		p = PriImage.ptr<uchar>(i);//��ȡÿ���׵�ַ
		for (int j = 0; j < nCols - 1; ++j)
		{
			VecGLCM_Col = p[j];
			p1 = PriImage.ptr<uchar>(i + 1);
			VecGLCM_Row = p1[j + 1];
			GM_VecGLCM[VecGLCM_Col][VecGLCM_Row]++;
		}
	}
}

void VecGLCMCount90(VecGLCM& GM_VecGLCM, cv::Mat PriImage, int nCols, int nRows)
{
	int VecGLCM_Col;
	int VecGLCM_Row;
	uchar* p;
	uchar* p1;
	for (int i = 0; i < nRows - 1; i++)
	{
		p = PriImage.ptr<uchar>(i);//��ȡÿ���׵�ַ
		for (int j = 0; j < nCols; ++j)
		{
			VecGLCM_Col = p[j];
			p1 = PriImage.ptr<uchar>(i + 1);
			VecGLCM_Row = p1[j];
			GM_VecGLCM[VecGLCM_Col][VecGLCM_Row]++;
		}
	}
}

void VecGLCMCount135(VecGLCM& GM_VecGLCM, cv::Mat PriImage, int nCols, int nRows)
{
	int VecGLCM_Col;
	int VecGLCM_Row;
	uchar* p;
	uchar* p1;
	for (int i = 1; i < nRows ; i++)
	{
		p = PriImage.ptr<uchar>(i);//��ȡÿ���׵�ַ
		for (int j = 0; j < nCols - 1; ++j)
		{
			VecGLCM_Col = p[j];
			p1 = PriImage.ptr<uchar>(i - 1);
			VecGLCM_Row = p1[j + 1];
			GM_VecGLCM[VecGLCM_Col][VecGLCM_Row]++;
		}
	}
}
//==============================================================================
// ��������: ComputeEntropy
// ����˵��: GM_VecGLCMΪ��������sizeΪ����Ĵ�С��size X size��
// ��������: �����������
//==============================================================================
double ComputeEntropy(VecGLCM& GM_VecGLCM, int size)
{
	double sum = 0;
	vector<vector<uchar>>::iterator IE;

	vector<uchar>::iterator it;
	for (IE = GM_VecGLCM.begin(); IE < GM_VecGLCM.end(); IE++)
	{
		for (it = (*IE).begin(); it < (*IE).end(); it++)
		{
			if ((*it) != 0)  sum += -(*it) * log(*it);
			//cout << *it << " ";
		}
	}
	return sum;
}

//�����õ���������ȫ
/*
double ComputeEntropy(VecGLCM& GM_VecGLCM, int size)
{
	double sum = 0;
	for(int i=0;i<size;i++)
		for (int j = 0; j < size ; j++)
		{
			if (GM_VecGLCM[i][j] != 0)
			{
				sum += -GM_VecGLCM[i][j] * log(GM_VecGLCM[i][j]);
			}
		}
	return sum;
}
*/

//==============================================================================
// ��������: ComputeEnergy
// ����˵��: GM_VecGLCMΪ��������sizeΪ����Ĵ�С��size X size��
// ��������: �������������
//==============================================================================
double ComputeEnergy(VecGLCM& GM_VecGLCM, int size)
{
	double sum = 0;
	vector<vector<uchar>>::iterator IE;
	vector<uchar>::iterator it;
	for (IE = GM_VecGLCM.begin(); IE < GM_VecGLCM.end(); IE++)
	{
		for (it = (*IE).begin(); it < (*IE).end(); it++)
		{
			sum += (*it) ^ 2;
		}
	}
	return sum;
}

//==============================================================================
// ��������: ComputeContrast
// ����˵��: GM_VecGLCMΪ��������sizeΪ����Ĵ�С��size X size��
// ��������: ��������ĶԱȶ�
//==============================================================================
double ComputeContrast(VecGLCM& GM_VecGLCM, int size)
{
	double sum = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			sum += (i - j) ^ 2 * GM_VecGLCM[i][j];
		}
	}
	return sum;
}

//==============================================================================
// ��������: ComputeUniformity
// ����˵��: GM_VecGLCMΪ��������sizeΪ����Ĵ�С��size X size��
// ��������: ��������ľ��ȶ�
//==============================================================================
double ComputeUniformity(VecGLCM& GM_VecGLCM, int size)
{
	double sum = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			sum += GM_VecGLCM[i][j] / (1 + abs(i - j));
		}
	}
	return sum;
}

//==============================================================================
// ��������: ComputeCorrelation
// ����˵��: GM_VecGLCMΪ��������sizeΪ����Ĵ�С��size X size��
// ��������: ��������������
//==============================================================================
double ComputeCorrelation(VecGLCM& GM_VecGLCM, int size)
{
	double Ui = 0;
	double Uj = 0;
	double Si = 0;
	double Sj = 0;
	double Si_Square = 0;    //Si��ƽ��ΪSi_Square
	double Sj_Square = 0;    //Sj��ƽ��ΪSj_Square
	double COR = 0;  //�����
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			Ui += (i+1) * GM_VecGLCM[i][j];
			Uj += (j+1) * GM_VecGLCM[i][j];
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			Si_Square += GM_VecGLCM[i][j] * (i+1 - Ui) * (i+1 - Ui);
			Sj_Square += GM_VecGLCM[i][j] * (j+1 - Uj) * (j+1 - Uj);
		}
	}
	Si = sqrt(Si_Square);
	Sj = sqrt(Sj_Square);
	for (int i=0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			COR += (((i + 1) * (j + 1)) * GM_VecGLCM[i][j] - Ui * Uj)/(Si*Sj);
		}
	}
	return COR;
}

//==============================================================================
// ��������: ImageFileRead
// ����˵��: PatternJPGΪ�ļ���������"E:\\ͼƬ\\*.jpg",GM_VecGLCMΪ��������sizeΪ����Ĵ�С
// ��������: ��������ͼƬ�ļ��������㹲��������ء��������ԱȶȺ;��ȶȷ���һ��num X 4�ľ���numΪͼƬ��������
//==============================================================================
vector<vector<double>> ImageFileRead(string PatternJPG, VecGLCM& GM_VecGLCM, int size)
{
	vector<string> ImageFile;
	glob(PatternJPG, ImageFile);    //��PatternJPG·���µ������ļ������ImageFile��
	if (ImageFile.size() == 0) {
		cout << "NO image file[jpg]" << endl;
	}

	//��ά���󴴽���ValueVec�б������ͼƬ�Ĺ���������ĸ�������Ϣ
	vector<vector<double>> ValueVec;
	int num = ImageFile.size();
	ValueVec.resize(num);
	for (int i = 0; i < num  ; i++)
	{
		ValueVec[i].resize(1);
	}

	for (unsigned int frame = 0; frame < ImageFile.size(); ++frame)
	{
		Mat image = cv::imread(ImageFile[frame], IMREAD_GRAYSCALE);
		cout << ImageFile[frame] << "��ȡ�ɹ���" << endl;
		int nRows = image.rows;
		int nCols = image.cols;
		VecGLCMCount0(GM_VecGLCM, image, nCols, nRows);
		//ValueVec[frame][0] = ComputeEntropy(GM_VecGLCM, size);       //������ֵ
		//ValueVec[frame][1] = ComputeEnergy(GM_VecGLCM, size);       //��������
		//ValueVec[frame][2] = ComputeContrast(GM_VecGLCM, size);       //����Աȶ�
		//ValueVec[frame][3] = ComputeUniformity(GM_VecGLCM, size);     //������ȶ�
		ValueVec[frame][0] = ComputeCorrelation(GM_VecGLCM, size);
		InitVecGLCM(GM_VecGLCM, size);  //���½�GM_VecGLCM��Ϊȫ0�ľ���
	}
	return ValueVec;
}

//==============================================================================
// ��������: ValueWrite
// ����˵��: MatrixΪ��������FileNameΪ��Ҫд����ļ�������"B2F.txt"
// ��������: �ļ�д��������Matrix�е�����д���ļ�FileName��
//==============================================================================
void ValueWrite(vector<vector<double>> Matrix, string FileName,int n)
{
	ofstream in;
	in.open(FileName, ios::trunc);  //ios::tuunc��ʾ�ڴ��ļ�ǰ���ļ���գ�������д�룬�ļ��������򴴽�
	for (int i = 0; i < Matrix.size(); i++)
	{
		for (int j = 0; j < Matrix[i].size(); j++)
		{
			in << Matrix[i][j] << "\t";
		}
		in << n << "\t";
		in << "\n";
	}
}

void InitVecGLCM(VecGLCM& GM_VecGLCM, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			GM_VecGLCM[i][j] = 0;
		}
	}
}