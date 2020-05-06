#pragma once
#include <vector>
using namespace std;

#ifndef _INTERPOLATION_
#define _INTERPOLATION_

enum INTERPOLATINGTYPE {//��ֵ����
	eInterpolationOneD,//һά��ֵ
	eInterpolationTwoD //��ά��ֵ
};
class CInterpolation
{
	vector<float> m_Xs, m_Ys, m_Zs;//x,y,z��
public:
	float m_Xmax;
	CInterpolation(const char* Xs, const char* Ys);
	CInterpolation(const char* Xs, const char* Ys, const char* Zs);
	CInterpolation(const INTERPOLATINGTYPE eType, const char* szFileName);
	virtual ~CInterpolation();

private:
	void Init(vector<float>& var, const char* string);//��ʼ��var
	BOOL  ReadOneD(const char* szFileName);//���ļ��ж�ȡx,y
	BOOL  ReadTwoD(const char* szFileName);//���ļ��ж�ȡx,y,z
public:
	const vector<float>& GetXs() const { return m_Xs; };
	const vector<float>& GetYs() const { return m_Ys; };
	const vector<float>& GetZs() const { return m_Zs; };
	float InterpolateOneD(float x);//����xֵ��ֵ�õ�y
	float InterpolateTwoD(float x, float y);//����x,yֵ��ֵ�õ�z
};

#endif // _INTERPOLATION_
