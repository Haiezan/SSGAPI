#pragma once
#include "HeadDefine.h"
#include <vector>

using namespace std;
struct OPTDATA
{
	int iter;
	int iNode; //节点号-1
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
	int iter; //迭代步
	float fStep; //步长
	float fMassRatio; //整体模型质量变化率
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
//结点到单元的映射关系
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

	//步长优化
	float fOptStep = 5e-5f;
	int nMaxNum = 20;
	float fMassScale = 16.f;
	float fPar[NPARA] = {
		0.8f, //0-最大频率控制点变形阈值 0~1
		1.1f, //1-最小质量放大系数 >1.0
		0.001f, //2-模型质量增加限值 >0
		0.f,
		0.f,
		0.f,
		0.f,
		0.f,
		0.f,
		0.f,
	}; 
									
	vector<OPTDATA> vNodeMass; //质量放大节点号
	vector<OPTDATA> vTmpNodeMass; //备份(临时数据，记录有效的节点，防止有些无效循环导致无效质量放大)
	vector<ITERDATA> vIter; //迭代步信息

	float fMassRatio;

	//备份更新逻辑：每个迭代步增加优化数据后进行BackUp，数据验证有效后进行Update
	//备份数据不参与计算
	void BackUp() //备份优化数据
	{
		vTmpNodeMass.clear();
		vTmpNodeMass.assign(vNodeMass.begin(), vNodeMass.end());
	};
	void Update() //更新优化数据
	{
		vNodeMass.clear();
		vNodeMass.assign(vTmpNodeMass.begin(), vTmpNodeMass.end());
	};

	//进行质量放大
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
	
	//读取文件
	BOOL ReadFile(CString fname1, CString fname2)
	{
		Clear();
		ClearAutoData();

		CASCFile fin;
		CString fname;

		//读取OPTA文件
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

					//检查数据
					if (iNode < 0 || fMassScale < 0.f || fMassScale>999.f) continue;

					vAutoNodeMass.push_back(OPTDATA(iter, iNode, fMassScale));
				}
			}

			fin.Close();
		}

		//读取OPTE文件
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

				//检查数据
				if (iNode < 0/* || iNode >= theData.m_cMesh.m_nNode*/ || fMassScale < 0.f || fMassScale>999.f) continue;

				vNodeMass.push_back(OPTDATA(iter, iNode, fMassScale));
			}

			BackUp();
			return TRUE;
		}

		return FALSE;
	}
	//写文件
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

	//自动质量放大
	float fTmax = 10e-5f; //单元最大步长
	float fElmMassRatio = 4.f; //单元质量放大系数
	vector<OPTDATA> vAutoNodeMass;

	//int nBeamElm, nTriElm, nQuadElm, nNode; //畸形单元或节点数量
	//float fBeamElm, fTriElm, fQuadElm, fNode; //畸形单元或节点比例
	//float fMassModify, fMass; //增加质量和原总质量
	float fTotalMassRatio; //质量缩放限值

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
