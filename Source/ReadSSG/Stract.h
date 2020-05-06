#pragma once
#include <vector>
#include "Fibre.h"
#include "Mat.h"
using namespace std;
#define PI 3.1415926
#define SMALL 1.0e-5
class Stract
{
public:
	Stract(float fB, float fH, char cType, float fCover, float fBRatio, float fHRatio, float fBarD = 6.f, float fElmSize = 50.f);
	~Stract();

public:
	float m_fB; //宽
	float m_fH;	//高
	char m_cType;	//构件类型
	
	float m_fCover; //保护层厚度
	
	float m_fElmSize; //网格尺寸

	float m_fBRatio; //B边配筋率
	float m_fHRatio; //H边配筋率
	float m_fBarD; //钢筋直径
	
public:
	bool SectionMesh();
	vector <XYFibre> ConcFibreList;
	vector <XYFibre> RebarFibreList;
	vector <XYFibre> SteelFibreList;

public:
	vector <PM> m_PMCurve;
	vector <PMM> m_PMMCurve;
	CInterpolation* m_pConc;
	CInterpolation* m_pRebar;
	PM CalcPM(float fR, float fTheata, float fAngle);
	PMM CalcPMM(float fR, float fTheata, float fAngle);
	bool CalcPMCurve(float fAngle = 0.f, float fEtaCu = 0.f, float fEtaSu = 0.f, int iDataNum = 1000);
	bool CalcPMMCurve(float fEtaCu = 0.f, float fEtaSu = 0.f, int iDataNum = 1000);

	vector <float> GetNeutralAxisList(int DataNum);
};



