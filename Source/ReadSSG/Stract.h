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
	float m_fB; //��
	float m_fH;	//��
	char m_cType;	//��������
	
	float m_fCover; //��������
	
	float m_fElmSize; //����ߴ�

	float m_fBRatio; //B�������
	float m_fHRatio; //H�������
	float m_fBarD; //�ֽ�ֱ��
	
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



