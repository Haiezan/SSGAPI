#pragma once
#include "HeadDefine.h"
#include "ASCFile.h"
#include "SysPara.h"
#include "Load.h"
#include <map>

using namespace std;

/*
//荷载表 留作设计软件用 需要配合荷载表 theData.m_cFrame.m_cLoadSet
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

	LOADASSIGN(){
		loadData=NULL;
		numLoad=0;
	};
	~LOADASSIGN(){
		clear();};

		void clear();
		BOOL  inline IsEmpty()const{return numLoad==0 || loadData==NULL;};
		LOADASSIGN & operator=(const LOADASSIGN &lm);
		bool operator!=(const LOADASSIGN &lm) const;
		int inline GetLoadCount() const{return numLoad;};
		int GetLcLoadNum(int iLC) const;
		int inline GetLoadLcId(int index) const{return (int)loadData[index][0];};
		int* GetLcLoads(int iLC) const;
		BOOL GetLoad(int index,CLoad *load)const;
		BOOL AddLoad(int iLC,const CLoad &load,bool bAdd=true);
		BOOL DeleteLoad(int iLC, vector<int>& vType);
		BOOL AppendLoad(int iLC,const CLoad &load);//指定工况增加荷载
		BOOL SetLoad(int index,const CLoad &load);//替换指定位置荷载
		BOOL ReplaceLoad(int iLC, const CLoad &load, vector<int>& vType);
		BOOL RemoveLc(int iLC);
		void Read(CASCFile &fin);
		void Write(CASCFile &fout,int &index,int id,int iStructType=-1);
		void Write2020(CASCFile &fout,int &index,int id,int iStructType=-1);
		void ReadBin(CFile &fin);
		void WriteBin(CFile &fout);
		CString GetShowText(int nCaseId, bool bGloabal = true);
		//得到要修改数据的地址只用于属性交互修改，慎用
		float *GetDataDirect(int index,int iData);
		//清除无效荷载
		void ClearInvalidData();
		//动荷载暂不考虑静载荷载数据
		void ReadDyna(CASCFile &fin);
		void WriteDyna(CASCFile &fout,int &index,int id);
		void ClearInvalidDynaData();
		//荷载工况重编号
		void ReorderLC(int nId, int nNew);
		//
		void ReorderLCs(map<int, int> &LCs);
private:
	// loadcaseid1 forceType1 bPrj1 bDisGlobal1 nData1 pData1[0] pData1[1] ... pData1[nData1-1] 0 0 0
	// loadcaseid2 forceType2 bPrj2 bDisGlobal2 nData2 pData2[0] pData2[1] ... pData2[nData2-1] 0 0 0
	float **loadData; 
	int numLoad;
	int GetDataNum(int index) const;
static	 int nDataAdd;
};
