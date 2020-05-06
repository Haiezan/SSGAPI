#pragma once
#include <vector>
using namespace std;

#ifndef _INTERPOLATION_
#define _INTERPOLATION_

enum INTERPOLATINGTYPE {//插值类型
	eInterpolationOneD,//一维插值
	eInterpolationTwoD //二维插值
};
class CInterpolation
{
	vector<float> m_Xs, m_Ys, m_Zs;//x,y,z表
public:
	float m_Xmax;
	CInterpolation(const char* Xs, const char* Ys);
	CInterpolation(const char* Xs, const char* Ys, const char* Zs);
	CInterpolation(const INTERPOLATINGTYPE eType, const char* szFileName);
	virtual ~CInterpolation();

private:
	void Init(vector<float>& var, const char* string);//初始化var
	BOOL  ReadOneD(const char* szFileName);//从文件中读取x,y
	BOOL  ReadTwoD(const char* szFileName);//从文件中读取x,y,z
public:
	const vector<float>& GetXs() const { return m_Xs; };
	const vector<float>& GetYs() const { return m_Ys; };
	const vector<float>& GetZs() const { return m_Zs; };
	float InterpolateOneD(float x);//根据x值插值得到y
	float InterpolateTwoD(float x, float y);//根据x,y值插值得到z
};

#endif // _INTERPOLATION_
