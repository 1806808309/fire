#include"GLCM_GM.h"

int main()
{
	VecGLCM VecGlcm(256);
	for (int i = 0; i < 256; i++)
	{
		VecGlcm[i].resize(256);
	}
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			VecGlcm[i][j] = 0;
		}
	}
	ValueWrite(ImageFileRead("E:\\ѧϰ����\\2020ͼ�������������ʾ�μ�\\��Ҷ�ּ�����ҵ\\��Ҷʶ����ҵ\\��Ҷʶ����ҵ\\test_351\\B2F\\*.jpg", VecGlcm, 256), "test_B2F.txt",1);     //д����
	InitVecGLCM(VecGlcm, 256);
	ValueWrite(ImageFileRead("E:\\ѧϰ����\\2020ͼ�������������ʾ�μ�\\��Ҷ�ּ�����ҵ\\��Ҷʶ����ҵ\\��Ҷʶ����ҵ\\test_351\\B3F\\*.jpg", VecGlcm, 256), "test_B3F.txt",2);     //д����
	InitVecGLCM(VecGlcm, 256);
	ValueWrite(ImageFileRead("E:\\ѧϰ����\\2020ͼ�������������ʾ�μ�\\��Ҷ�ּ�����ҵ\\��Ҷʶ����ҵ\\��Ҷʶ����ҵ\\test_351\\C2F\\*.jpg", VecGlcm, 256), "test_C2F.txt",3);     //д����
	InitVecGLCM(VecGlcm, 256);
	ValueWrite(ImageFileRead("E:\\ѧϰ����\\2020ͼ�������������ʾ�μ�\\��Ҷ�ּ�����ҵ\\��Ҷʶ����ҵ\\��Ҷʶ����ҵ\\test_351\\C3F\\*.jpg", VecGlcm, 256), "test_C3F.txt",4);     //д����
	InitVecGLCM(VecGlcm, 256);
	ValueWrite(ImageFileRead("E:\\ѧϰ����\\2020ͼ�������������ʾ�μ�\\��Ҷ�ּ�����ҵ\\��Ҷʶ����ҵ\\��Ҷʶ����ҵ\\test_351\\C4F\\*.jpg", VecGlcm, 256), "test_C4F.txt",5);     //д����
	return 0;
}
