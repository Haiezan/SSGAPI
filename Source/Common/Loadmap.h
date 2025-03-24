#pragma once
#include "HeadDefine.h"
#include "ASCFile.h"
#include "SysPara.h"
#include "Load.h"
#include <map>

/*
//荷载表 留作设计软件用 需要配合荷载表 m_cFrame.m_cLoadSet
class _SSG_DLLIMPEXP LOADMAP
{
public:

	LOADMAP(){
		mapData=NULL;
		numLC=0;
	};
	~LOADMAP(){
		clear();};

	void clear();
	BOOL IsValidData(const LOADMAP &lm);
	BOOL  inline IsEmpty()const{return numLC==0 || mapData==NULL;};
	LOADMAP & operator=(const LOADMAP &lm);
	unsigned short inline GetLcNum() const{return numLC;}
	unsigned short GetLoadNum(unsigned short iLC) const;
	unsigned short *GetLoadData(unsigned short iLC) const;
	BOOL AddLoad(unsigned short iLC,unsigned short iLoad);
	BOOL RemoveLc(unsigned short iLC);
	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void ReadBin(CFile &fin);
	void WriteBin(CFile &fout);
	CString GetShowText();
private:
	unsigned short **mapData;
	unsigned short numLC;
	unsigned short inline SetLcData(unsigned short Lc,unsigned short nLoad){return Lc<<10|nLoad;}//高六位Lc,低十位nLoad
	unsigned short inline GetNum(unsigned short val) const{return val&(0x3FF);}//低十位
	unsigned short inline GetLcId(unsigned short val) const{return (val&(0xFC00))>>10;}//高六位
	BOOL GetLcIndex(unsigned short iLC,unsigned short &index) const;//找到对应工况数据的内部编号
};

*/
//荷载数据：不需要荷载表
class _SSG_DLLIMPEXP LOADASSIGN
{
public:
	LOADASSIGN()
		: loadData(nullptr)
		, numLoad(0)
	{
	};
	~LOADASSIGN()
	{
		clear();
	};

	enum
	{
		POS_LC = 0,
		POS_TYPE,
		POS_PROJ,
		POS_RELDIS,
		POS_NDATA,
		POS_NUM,
	};

	void clear();
	BOOL  inline IsEmpty()const { return numLoad == 0 || loadData == nullptr; };
	LOADASSIGN& operator=(const LOADASSIGN& lm);
	bool operator!=(const LOADASSIGN& lm) const;
	int inline GetLoadCount() const { return numLoad; };
	int GetLcLoadNum(int iLC) const;
	int inline GetLoadLcId(int index) const { return (int)loadData[index][POS_LC]; };
	int GetLoadLgId(int index) const;
	BOOL GetLoad(int index, CLoad* load)const;
	BOOL AddLoad(int iLC, const CLoad& load, bool bAdd = true, int iLgId = 0);
	BOOL DeleteLoad(int iLC, vector<int>& vType, int iLdGroup = 0);
	BOOL AppendLoad(int iLC, const CLoad& load, int iLdGroup = 0);//指定工况增加荷载
	BOOL SetLoad(int index, const CLoad& load);//替换指定位置荷载
	BOOL ReplaceLoad(int iLC, const CLoad& load, vector<int>& vType, int iLdGroup = 0);
	BOOL RemoveLc(int iLC);
	BOOL RemoveLg(int iLg);
	void Read(CASCFile& fin);
	void Write(CASCFile& fout, int& index, int id, int iStructType = 0);
	void Write2020(CASCFile& fout, int& index, int id, int iStructType = 0);
	void ReadBin(CFile& fin);
	void WriteBin(CFile& fout);
	CString GetShowText(int nCaseId, bool bGloabal = true);
	//得到要修改数据的地址只用于属性交互修改，慎用
	float* GetDataDirect(int index, int iData);
	//清除无效荷载
	void ClearInvalidData();
	//动荷载暂不考虑静载荷载数据
	void ReadDyna(CASCFile& fin);
	void WriteDyna(CASCFile& fout, int& index, int id);
	int GetFuncID(int iLC); //获取动荷载时程函数ID
	void ClearInvalidDynaData();
	//荷载工况重编号
	void ReorderLC(int nId, int nNew);
	//
	void ReorderLCs(map<int, int>& LCs);
	//工况间荷载复制
	void CopyLoad(int iCurLC, int iAimLC, float fRatio = 1.f, bool bTrans = false, int iCurLG = 0, int iAimLG = 0);
	void LoadScale(float* pLoad, float fRatio);
	bool bSimilarForce(float* pLoad1, float* pLoad2);
	void LoadAdd(int id, float* pLoad);
	int AppendLoad(float* pload);//直接增加荷载

	//获取抗爆墙体类型
	int GetBlastType(int iLC);
	CString GetBlastShowText(int iLC);
	void ReadBlastType(CASCFile& fin);
	void WriteBlastType(CASCFile& fout, int& index, int id);
	int GetBlastTypeNum(); //统计抗爆墙体类型数据数量

	//根据函数编号删除工况
	BOOL RemoveLcByFunc(int ID);
private:
	// loadcaseid1 forceType1 bPrj1 bDisGlobal1 nData1 pData1[0] pData1[1] ... pData1[nData1-1] 0 0 0
	// loadcaseid2 forceType2 bPrj2 bDisGlobal2 nData2 pData2[0] pData2[1] ... pData2[nData2-1] 0 0 0
	//2026 modify 
	// loadcaseid1 forceType1 bPrj1 bDisGlobal1 nData1 pData1[0] pData1[1] ... pData1[nData1-1] iLoadGroup 0 0
	float** loadData;
	int numLoad;
	int GetDataNum(int index) const;
	static int nDataAdd;
	static int iBegin;
};
