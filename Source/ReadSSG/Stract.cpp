#include "stdafx.h"
#include "Stract.h"


Stract::Stract(float fB, float fH, char cType, float fCover, float fBRatio, float fHRatio, float fBarD, float fElmSize)
{
	m_fB = fB;
	m_fH = fH;
	m_cType = cType;
	m_fCover = fCover;
	m_fBRatio = fBRatio;
	m_fHRatio = fHRatio;
	m_fBarD = fBarD;
	m_fElmSize = fElmSize;

	m_pConc = CMat::GetConcrete(30);
	m_pRebar = CMat::GetRebar(3);
}


Stract::~Stract()
{
	/*
	if (m_pConc != NULL)
	{
		delete m_pConc; m_pConc = NULL;
	}
	if (m_pRebar != NULL)
	{
		delete m_pRebar; m_pRebar = NULL;
	}
	*/
	if (m_pConc) delete[] m_pConc; m_pConc = NULL;
	if (m_pRebar) delete[] m_pRebar; m_pRebar = NULL;
}

bool Stract::SectionMesh()
{
	ConcFibreList.clear();
	RebarFibreList.clear();
	SteelFibreList.clear();

	float fB = m_fB;
	float fH = m_fH;
	float fElmSize = m_fElmSize;
	//划分混凝土纤维
	int NumX = fB / m_fElmSize;
	int NumY = fH / m_fElmSize;
	float fSizeX = fB / NumX;
	float fSizeY = fH / NumY;
	float fConcA = fSizeX * fSizeY;

	XYFibre xyfibre1 = { fSizeX / 2.f - fB / 2.f,  fSizeY / 2.f - fH / 2.f, fConcA, 1 };
	XYFibre xyfibre2 = { fSizeX / 2.f - fB / 2.f, -fSizeY / 2.f + fH / 2.f, fConcA, 1 };
	XYFibre xyfibre3 = { -fSizeX / 2.f + fB / 2.f, -fSizeY / 2.f + fH / 2.f, fConcA, 1 };
	XYFibre xyfibre4 = { -fSizeX / 2.f + fB / 2.f,  fSizeY / 2.f - fH / 2.f, fConcA, 1 };
	ConcFibreList.push_back(xyfibre1);
	ConcFibreList.push_back(xyfibre2);
	ConcFibreList.push_back(xyfibre3);
	ConcFibreList.push_back(xyfibre4);

	for (int i = 0; i < NumX; i++)
	{
		for (int j = 0; j < NumY; j++)
		{
			if ((i == 0 && j == 0) || (i == 0 && j == NumY - 1) || (i == NumX - 1 && j == 0) || (i == NumX - 1 && j == NumY - 1)) continue;
			XYFibre fibre;
			fibre.fX = (i + 1 / 2.f)*fSizeX - fB / 2.f;
			fibre.fY = (j + 1 / 2.f)*fSizeY - fH / 2.f;
			fibre.fA = fConcA;
			fibre.cMat = 1;
			ConcFibreList.push_back(fibre);
		}
	}

	//划分钢筋纤维
	float fCover = m_fCover;
	float fAs0 = 3.14f*m_fBarD*m_fBarD / 4.0f;
	int NumB = fB * fH*m_fBRatio / fAs0;
	int NumH = fB * fH*m_fHRatio / fAs0;

	float fSpaceB = (fB - 2.f*fCover) / (NumB - 1);
	float fSpaceH = (fH - 2.f*fCover) / (NumH - 1);

	XYFibre xyfibre5 = { fCover - fB / 2.f,  fCover - fH / 2.f ,fAs0,2 };
	XYFibre xyfibre6 = { fCover - fB / 2.f, -fCover + fH / 2.f ,fAs0,2 };
	XYFibre xyfibre7 = { -fCover + fB / 2.f,  fCover - fH / 2.f ,fAs0,2 };
	XYFibre xyfibre8 = { -fCover + fB / 2.f, -fCover + fH / 2.f ,fAs0,2 };
	RebarFibreList.push_back(xyfibre5);
	RebarFibreList.push_back(xyfibre6);
	RebarFibreList.push_back(xyfibre7);
	RebarFibreList.push_back(xyfibre8);
	for (int i = 1; i < NumB - 1; i++)
	{
		XYFibre fibre1, fibre2;

		fibre1.fX = i * fSpaceB - (fB / 2.f - fCover);
		fibre1.fY = fH / 2.f - fCover;
		fibre1.fA = fAs0;
		fibre1.cMat = 2;
		RebarFibreList.push_back(fibre1);

		fibre2.fX = fibre1.fX;
		fibre2.fY = fibre1.fY*(-1);
		fibre2.fA = fAs0;
		fibre2.cMat = 2;
		RebarFibreList.push_back(fibre2);
	}
	for (int i = 1; i < NumH - 1; i++)
	{
		XYFibre fibre1, fibre2;

		fibre1.fX = fB / 2.f - fCover;
		fibre1.fY = i * fSpaceH - (fH / 2.f - fCover);
		fibre1.fA = fAs0;
		fibre1.cMat = 2;
		RebarFibreList.push_back(fibre1);

		fibre2.fX = fibre1.fX*(-1);
		fibre2.fY = fibre1.fY;
		fibre2.fA = fAs0;
		fibre2.cMat = 2;
		RebarFibreList.push_back(fibre2);
	}

	return true;
}

bool Stract::CalcPMCurve(float fAngle, float fEtaCu, float fEtaSu, int iDataNum)
{
	if ((ConcFibreList.size() + RebarFibreList.size() + SteelFibreList.size()) < 1) return false;

	if (fEtaCu < SMALL) fEtaCu = 0.001472f;//m_pConc->m_Xmax;
	if (fEtaSu < SMALL) fEtaSu = 0.002f;// m_pRebar->m_Xmax;

	//定义角度
	float fAngleRad = fAngle * PI / 180.f;

	//定义中性轴位置数列
	vector<float> fRs = GetNeutralAxisList(iDataNum);

	m_PMCurve.clear();
	for (int i = 0; i < fRs.size(); i++)
	{
		float fR = fRs[i];
		float fai1, fai2, fai;

		//曲率为正
		fai1 = fEtaCu / (1.f * m_fH / 2.f - fR);
		fai2 = fEtaSu / (1.f * m_fH / 2.f + fR);
		fai = min(abs(fai1), abs(fai2));
		PM pm1=CalcPM(fR, fai, fAngleRad);
		m_PMCurve.push_back(pm1);

		//曲率为负
		fai1 = fEtaCu / (-1.f * m_fH / 2.f - fR);
		fai2 = fEtaSu / (-1.f * m_fH / 2.f + fR);
		fai = min(abs(fai1), abs(fai2));
		PM pm2 = CalcPM(fR, -1.f * fai, fAngleRad);
		m_PMCurve.push_back(pm2);
	}

	return true;
}

bool Stract::CalcPMMCurve(float fEtaCu, float fEtaSu, int iDataNum)
{
	if ((ConcFibreList.size() + RebarFibreList.size() + SteelFibreList.size()) < 1) return false;

	if (fEtaCu < SMALL) fEtaCu = 0.001472f;//m_pConc->m_Xmax;
	if (fEtaSu < SMALL) fEtaSu = 0.002f;// m_pRebar->m_Xmax;

	//定义中性轴位置数列
	vector<float> fRs = GetNeutralAxisList(iDataNum);

	m_PMMCurve.clear();

	int AngleNum = 6;
	for (int j = 0; j < AngleNum; j++)
	{
		//定义角度
		float fAngleRad = j * PI / AngleNum;

		//////////////////
		CString title;
		title.Format(_T("PMM%d.dat"), j + 1);

		USES_CONVERSION;
		std::string s(W2A(title));
		const char* cstr = s.c_str();
		FILE* fdOut = NULL;
		if ((fdOut = fopen(cstr, "wb")) == NULL)
		{
		}
		//////////////////


		for (int i = 0; i < fRs.size(); i++)
		{
			float fR = fRs[i];
			float fai1, fai2, fai;

			//曲率为正
			fai1 = fEtaCu / (1.f * m_fH / 2.f - fR);
			fai2 = fEtaSu / (1.f * m_fH / 2.f + fR);
			fai = min(abs(fai1), abs(fai2));
			PMM pm1 = CalcPMM(fR, fai, fAngleRad);
			m_PMMCurve.push_back(pm1);

			////////////////
			fprintf(fdOut, "%15.4f\t%15.4f\t%15.4f\n", pm1.fMx, pm1.fMy, pm1.fP);
			////////////////
		}
		for (int i = fRs.size() - 1; i >= 0; i--)
		{
			float fR = fRs[i];
			float fai1, fai2, fai;

			//曲率为负
			fai1 = fEtaCu / (-1.f * m_fH / 2.f - fR);
			fai2 = fEtaSu / (-1.f * m_fH / 2.f + fR);
			fai = min(abs(fai1), abs(fai2));
			PMM pm2 = CalcPMM(fR, -1.f * fai, fAngleRad);
			m_PMMCurve.push_back(pm2);

			////////////////
			fprintf(fdOut, "%15.4f\t%15.4f\t%15.4f\n", pm2.fMx, pm2.fMy, pm2.fP);
			////////////////
		}
		fclose(fdOut);
	}
	return true;
}

PM Stract::CalcPM(float fR, float fTheata, float fAngle)
{
	FILE* fdOut = NULL;
	if ((fdOut = fopen("FibreC.csv", "wb")) == NULL)
	{
	}

	float fSteelE = 2.00e5f;

	float fMx = 0.f;
	float fMy = 0.f;
	float fN = 0.f;
	for (int j = 0; j < ConcFibreList.size(); j++)
	{
		float fX = ConcFibreList[j].fX;
		float fY = ConcFibreList[j].fY;
		float fA = ConcFibreList[j].fA;

		float etac = (fTheata) * (fX*sin(fAngle) + fY * cos(fAngle) - fR);
		if (etac < 0) etac = 0.f;
		float sigmac = m_pConc->InterpolateOneD(etac);

		fMx += sigmac * fA*fY;
		fMy += sigmac * fA*fX;
		fN += sigmac * fA;

		fprintf(fdOut, "%4d,%15.4f,%15.4f,%15.4f,%15.4f,", j + 1, ConcFibreList[j].fX, ConcFibreList[j].fY, etac, sigmac);
		fprintf(fdOut, "\n");
	}
	fclose(fdOut);
	FILE* fdOut2 = NULL;
	if ((fdOut2 = fopen("FibreS.csv", "wb")) == NULL)
	{
	}

	for (int j = 0; j < RebarFibreList.size(); j++)
	{
		float fX = RebarFibreList[j].fX;
		float fY = RebarFibreList[j].fY;
		float fA = RebarFibreList[j].fA;

		float etas = -1 * (fTheata)*(fX*sin(fAngle) + fY * cos(fAngle) - fR);
		float sigmas = m_pRebar->InterpolateOneD(etas);

		fMx -= sigmas * fA*fY;
		fMy -= sigmas * fA*fX;
		fN -= sigmas * fA;

		fprintf(fdOut2, "%4d,%15.4f,%15.4f,%15.4f,%15.4f,", j + 1, fX, fY, etas, sigmas);
		fprintf(fdOut2, "\n");
	}

	fclose(fdOut2);
	PM pm = { fR,fTheata,fN,fMx };
	return pm;
}
PMM Stract::CalcPMM(float fR, float fTheata, float fAngle)
{
	FILE* fdOut = NULL;
	if ((fdOut = fopen("FibreC.csv", "wb")) == NULL)
	{
	}

	float fSteelE = 2.00e5f;

	float fMx = 0.f;
	float fMy = 0.f;
	float fN = 0.f;
	for (int j = 0; j < ConcFibreList.size(); j++)
	{
		float fX = ConcFibreList[j].fX;
		float fY = ConcFibreList[j].fY;
		float fA = ConcFibreList[j].fA;

		float etac = (fTheata) * (fX*sin(fAngle) + fY * cos(fAngle) - fR);
		if (etac < 0) etac = 0.f;
		float sigmac = m_pConc->InterpolateOneD(etac);

		fMx += sigmac * fA*fY;
		fMy += sigmac * fA*fX;
		fN += sigmac * fA;

		fprintf(fdOut, "%4d,%15.4f,%15.4f,%15.4f,%15.4f,", j + 1, ConcFibreList[j].fX, ConcFibreList[j].fY, etac, sigmac);
		fprintf(fdOut, "\n");
	}
	fclose(fdOut);
	FILE* fdOut2 = NULL;
	if ((fdOut2 = fopen("FibreS.csv", "wb")) == NULL)
	{
	}

	for (int j = 0; j < RebarFibreList.size(); j++)
	{
		float fX = RebarFibreList[j].fX;
		float fY = RebarFibreList[j].fY;
		float fA = RebarFibreList[j].fA;

		float etas = -1 * (fTheata)*(fX*sin(fAngle) + fY * cos(fAngle) - fR);
		float sigmas = m_pRebar->InterpolateOneD(etas);

		fMx -= sigmas * fA*fY;
		fMy -= sigmas * fA*fX;
		fN -= sigmas * fA;

		fprintf(fdOut2, "%4d,%15.4f,%15.4f,%15.4f,%15.4f,", j + 1, fX, fY, etas, sigmas);
		fprintf(fdOut2, "\n");
	}

	fclose(fdOut2);
	PMM pmm = { fAngle,fR,fTheata,fN,fMx,fMy };
	return pmm;
}

//定义中性轴位置数列, 分段控制
vector <float> Stract::GetNeutralAxisList(int DataNum)
{
	vector<float> fRs;
	fRs.clear();

	float MAX1 = 1.0e4f;
	float MAX2 = max(m_fB, m_fH);

	int DataNum1 = DataNum * 0.2f;
	for (int i = 0; i <= DataNum1; i++)
	{
		float fX = i * (MAX1 - MAX2) / DataNum1 - MAX1;
		fRs.push_back(fX);
	}

	int DataNum2 = DataNum - DataNum1 * 2;
	float fDx = (2 * MAX2) / (DataNum2 - 1);
	float fX = fDx - MAX2;
	while (fX <= MAX2 + 0.0001)
	{
		fRs.push_back(fX);
		fX += fDx;
	}

	for (int i = DataNum1; i >= 0; i--)
	{
		float fX = MAX1 - i * (MAX1 - MAX2) / DataNum1;
		fRs.push_back(fX);
	}

	return fRs;
}
