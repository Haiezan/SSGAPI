#pragma once
#include "HeadDefine.h"
#include <vector>

using namespace std;
struct OPTDATA
{
	int iter;
	int iNode; //�ڵ��-1
	float fMassScale;

	OPTDATA()
	{
		OPTDATA(-1, -1, 0.f);
	};
	OPTDATA(int i,int node,float MS)
	{
		iter = i;
		iNode = node;
		fMassScale = MS;
	};
};

struct ITERDATA
{
	int iter; //������
	float fStep; //����
	float fMassRatio; //����ģ�������仯��
	vector<OPTDATA> vNodeMass;

	ITERDATA()
	{
		ITERDATA(-1, 0.f, 0.f);
	};
	ITERDATA(int i, float Step, float Ratio)
	{
		iter = i;
		fStep = Step;
		fMassRatio = Ratio;
		vNodeMass.clear();
	};
	~ITERDATA()
	{
		Clear();
	};
	void Clear()
	{
		iter = -1;
		fStep = 0.f;
		fMassRatio = 0.f;
		vNodeMass.clear();
	};
};

#define NPARA 10
//��㵽��Ԫ��ӳ���ϵ
class _SSG_DLLIMPEXP CMeshOpt
{
public:
	CMeshOpt(void)
	{
		Clear();
	};
	~CMeshOpt(void)
	{
		Clear();
	};
	void Clear()
	{
		//vNode.clear();
		//vMassScale.clear();
		vNodeMass.clear();
		vTmpNodeMass.clear();

		vIter.clear();
	};

	//�����Ż�
	float fOptStep = 5e-5f;
	int nMaxNum = 20;
	float fMassScale = 16.f;
	float fPar[NPARA] = {
		0.8f, //0-���Ƶ�ʿ��Ƶ������ֵ 0~1
		1.1f, //1-��С�����Ŵ�ϵ�� >1.0
		0.001f, //2-ģ������������ֵ >0
		0.f,
		0.f,
		0.f,
		0.f,
		0.f,
		0.f,
		0.f,
	}; 
									
	vector<OPTDATA> vNodeMass; //�����Ŵ�ڵ��
	vector<OPTDATA> vTmpNodeMass; //����(��ʱ���ݣ���¼��Ч�Ľڵ㣬��ֹ��Щ��Чѭ��������Ч�����Ŵ�)
	vector<ITERDATA> vIter; //��������Ϣ

	float fMassRatio;

	//���ݸ����߼���ÿ�������������Ż����ݺ����BackUp��������֤��Ч�����Update
	//�������ݲ��������
	void BackUp() //�����Ż�����
	{
		vTmpNodeMass.clear();
		vTmpNodeMass.assign(vNodeMass.begin(), vNodeMass.end());
	};
	void Update() //�����Ż�����
	{
		vNodeMass.clear();
		vNodeMass.assign(vTmpNodeMass.begin(), vTmpNodeMass.end());
	};

	//���������Ŵ�
	BOOL RunMassScale(float*& mass, float AllMass,BOOL bAutoMass)
	{
		fMassRatio = 0.f;

		if (bAutoMass)
		{
			for (int i = 0; i < vAutoNodeMass.size(); i++)
			{
				int iNode = vAutoNodeMass[i].iNode;
				float fMassScale = vAutoNodeMass[i].fMassScale;
				if (iNode > -1 && fMassScale > 0.f)
				{
					fMassRatio += mass[iNode] * (fMassScale - 1);
					mass[iNode] *= fMassScale;
				}
			}
		}
		
		for (int i = 0; i < vNodeMass.size(); i++)
		{
			int iNode = vNodeMass[i].iNode;
			float fMassScale = vNodeMass[i].fMassScale;
			if (iNode > -1 && fMassScale > 0.f)
			{
				fMassRatio += mass[iNode] * (fMassScale - 1);
				mass[iNode] *= fMassScale;
			}
		}
		fMassRatio /= AllMass;

		return TRUE;
	};
	
	//��ȡ�ļ�
	BOOL ReadFile(CString fname1, CString fname2)
	{
		Clear();
		ClearAutoData();

		CASCFile fin;
		CString fname;

		//��ȡOPTA�ļ�
		fname = fname1;
		if (IsFileExists(fname) && fin.Open(fname, CFile::modeRead | CFile::shareDenyWrite))
		{
			fin.FindKey("Tmax =");
			fTmax = fin.GetFloat();
			fin.FindKey("ElmMassRatio =");
			fElmMassRatio = fin.GetFloat();

			if (fin.FindKey("*Auto Result"))
			{
				int count = fin.GetKeyValueInt("NUMBER=");
				for (int i = 0; i < count; i++)
				{
					int iter = fin.GetInt();
					int iNode = fin.GetInt() - 1;
					float fMassScale = fin.GetFloat();

					//�������
					if (iNode < 0 || fMassScale < 0.f || fMassScale>999.f) continue;

					vAutoNodeMass.push_back(OPTDATA(iter, iNode, fMassScale));
				}
			}

			fin.Close();
		}

		//��ȡOPTE�ļ�
		 fname = fname2;
		if (IsFileExists(fname) && fin.Open(fname, CFile::modeRead | CFile::shareDenyWrite))
		{
			fin.FindKey("OptStep =");
			fOptStep = fin.GetFloat();
			fin.FindKey("MaxOpt =");
			nMaxNum = fin.GetInt();
			fin.FindKey("MS =");
			fMassScale = fin.GetFloat();
			fin.FindKey("Control Para:");
			for (int i = 0; i < NPARA; i++)
			{
				float value = fin.GetFloat();
				fPar[i] = (value > 0.f) ? value : fPar[i];
			}

			Read(fin);

			fin.Close();
		}
		return TRUE;
	}
	BOOL Read(CASCFile& fin)
	{
		while (fin.FindKeyNext("iter ="))
		{
			int iter = fin.GetInt();
			fin.FindKeyNext("Step =");
			float fStep = fin.GetFloat();
			fin.FindKeyNext("MassRatio =");
			float fMassRatio = fin.GetFloat();
			ITERDATA data = ITERDATA(iter, fStep, fMassRatio);

			fin.FindKeyNext("nNode =");
			int nNode = fin.GetInt();
			for (int i = 0; i < nNode; i++)
			{
				fin.FindKeyNext("ID =");
				int iNode = fin.GetInt() - 1;
				fin.FindKeyNext("MS =");
				float fMS = fin.GetFloat();

				data.vNodeMass.push_back(OPTDATA(iter, iNode, fMS));
			}
			vIter.push_back(data);
		}

		if (fin.FindKey("*Optimization Result"))
		{
			int count = fin.GetKeyValueInt("NUMBER=");
			for (int i = 0; i < count; i++)
			{
				int iter = fin.GetInt();
				int iNode = fin.GetInt() - 1;
				float fMassScale = fin.GetFloat();

				//�������
				if (iNode < 0/* || iNode >= theData.m_cMesh.m_nNode*/ || fMassScale < 0.f || fMassScale>999.f) continue;

				vNodeMass.push_back(OPTDATA(iter, iNode, fMassScale));
			}

			BackUp();
			return TRUE;
		}

		return FALSE;
	}
	//д�ļ�
	BOOL WritePara(CASCFile& fout)
	{
		char buf[512];
		sprintf_s(buf, sizeof(buf), "OptStep = %e MaxOpt = %d MS = %g\r\n", fOptStep, nMaxNum, fMassScale);
		fout.Write(buf, strlen(buf));
		sprintf_s(buf, sizeof(buf), "Control Para:");
		fout.Write(buf, strlen(buf));
		for (int i = 0; i < NPARA; i++)
		{
			sprintf_s(buf, sizeof(buf), " %g", fPar[i]);
			fout.Write(buf, strlen(buf));
		}
		sprintf_s(buf, sizeof(buf), "\r\n\r\n");
		fout.Write(buf, strlen(buf));

		return TRUE;
	}
	BOOL Write(CASCFile& fout)
	{
		char buf[512];
		sprintf_s(buf, sizeof(buf), "*Optimization Result NUMBER=%d\r\n", vNodeMass.size());
		fout.Write(buf, strlen(buf));
		for (int i = 0; i < vNodeMass.size(); i++)
		{
			OPTDATA data = vNodeMass.at(i);
			sprintf_s(buf, sizeof(buf), " %d %d %f\r\n", data.iter, data.iNode + 1, data.fMassScale);
			fout.Write(buf, strlen(buf));
		}
		return TRUE;
	}

	//�Զ������Ŵ�
	float fTmax = 10e-5f; //��Ԫ��󲽳�
	float fElmMassRatio = 4.f; //��Ԫ�����Ŵ�ϵ��
	vector<OPTDATA> vAutoNodeMass;

	//int nBeamElm, nTriElm, nQuadElm, nNode; //���ε�Ԫ��ڵ�����
	//float fBeamElm, fTriElm, fQuadElm, fNode; //���ε�Ԫ��ڵ����
	//float fMassModify, fMass; //����������ԭ������
	float fTotalMassRatio; //����������ֵ

	BOOL ClearAutoData()
	{
		//nBeamElm = nTriElm = nQuadElm = nNode = 0;
		//fBeamElm = fTriElm = fQuadElm = fNode = fMassModify = fMass = 0.f;
		vAutoNodeMass.clear();

		return TRUE;
	}
	BOOL WriteAutoData(CASCFile& fout)
	{
		char buf[512];
		sprintf_s(buf, sizeof(buf), "Auto mass scale parameters:\r\n");
		fout.Write(buf, strlen(buf));
		sprintf_s(buf, sizeof(buf), "Tmax = %e ElmMassRatio = %g\r\n", fTmax, fElmMassRatio);
		fout.Write(buf, strlen(buf));
		sprintf_s(buf, sizeof(buf), "*Auto Result NUMBER=%d\r\n", vAutoNodeMass.size());
		fout.Write(buf, strlen(buf));
		for (int i = 0; i < vAutoNodeMass.size(); i++)
		{
			OPTDATA data = vAutoNodeMass.at(i);
			sprintf_s(buf, sizeof(buf), " %d %d %f\r\n", data.iter, data.iNode + 1, data.fMassScale);
			fout.Write(buf, strlen(buf));
		}

		sprintf_s(buf, sizeof(buf), "\r\n");
		fout.Write(buf, strlen(buf));

		return TRUE;
	}

};
