#pragma once
#include<stdio.h>
//用于储存包络数据
struct SEnvStep
{
	CString sLoadCase;

	int iStep;

	float fStressI;
	float fStressJ;

	float ff;

	float Ni;
	float Vyi;
	float Vzi;
	float Myi;
	float Mzi;

	float Nj;
	float Vyj;
	float Vzj;
	float Myj;
	float Mzj;

	SEnvStep() :iStep(-1), fStressI(0.f), fStressJ(0.f), ff(0.f), Ni(0.f), Vyi(0.f), Vzi(0.f), Myi(0.f), Mzi(0.f), Nj(0.f), Vyj(0.f), Vzj(0.f), Myj(0.f), Mzj(0.f) {}
	SEnvStep(CString sLoadCase, int iStep, float fStressI, float fStressJ, float ff, float Ni, float Vyi, float Vzi, float Myi, float Mzi, float Nj, float Vyj, float Vzj, float Myj, float Mzj) :sLoadCase(sLoadCase), iStep(iStep), fStressI(fStressI), fStressJ(fStressJ), ff(ff), Ni(Ni), Vyi(Vyi), Vzi(Vzi), Myi(Myi), Mzi(Mzi), Nj(Nj), Vyj(Vyj), Vzj(Vzj), Myj(Myj), Mzj(Mzj) {}
	void ReNewData(SEnvStep sEnv)
	{
		sLoadCase = sEnv.sLoadCase;

		iStep = sEnv.iStep;

		fStressI = sEnv.fStressI;
		fStressJ = sEnv.fStressJ;

		ff = sEnv.ff;

		Ni = sEnv.Ni;
		Vyi = sEnv.Vyi;
		Vzi = sEnv.Vzi;
		Myi = sEnv.Myi;
		Mzi = sEnv.Mzi;

		Nj = sEnv.Nj;
		Vyj = sEnv.Vyj;
		Vzj = sEnv.Vzj;
		Myj = sEnv.Myj;
		Mzj = sEnv.Mzj;
	};
	void PrintI(char* buf, int Size)
	{
		if (iStep < 0)
		{
			sprintf_s(buf, Size, "未计算");
		}
		else
		{
			sprintf_s(buf, Size, "%S\t%d\t%0.2f\t(%0.3f)\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f", sLoadCase, iStep + 1, fStressI, fStressI / ff, Ni, Vyi, Vzi, Myi, Mzi);
		}

		if (fStressI / ff > 1.f)
		{
			sprintf_s(buf, Size, "%s\t*超限*\n", buf);
		}
		else
		{
			sprintf_s(buf, Size, "%s\n", buf);
		}
	}
	void PrintJ(char* buf, int Size)
	{
		if (iStep < 0)
		{
			sprintf_s(buf, Size, "未计算");
		}
		else
		{
			sprintf_s(buf, Size, "%S\t%d\t%0.2f\t(%0.3f)\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f", sLoadCase, iStep + 1, fStressJ, fStressJ / ff, Nj, Vyj, Vzj, Myj, Mzj);
		}

		if (fStressJ / ff > 1.f)
		{
			sprintf_s(buf, Size, "%s\t*超限*\n", buf);
		}
		else
		{
			sprintf_s(buf, Size, "%s\n", buf);
		}
	}
};

class CPostContainer
{
public:
	CPostContainer()
	{
		pBeam = NULL;
		EnvStep.clear();
	}
	~CPostContainer()
	{
		pBeam = NULL;
		EnvStep.clear();
	}
	CBeamStruc* pBeam;
	vector<SEnvStep> EnvStep;

	void Pushdata(SEnvStep sEnvData)
	{
		EnvStep.push_back(sEnvData);
	}
};