#pragma once
#include "HeadDefine.h"
#include "ASCFile.h"
#include "SysPara.h"
#include "Load.h"
#include <map>

using namespace std;

/*
//���ر� ������������ ��Ҫ��Ϻ��ر� theData.m_cFrame.m_cLoadSet
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
	unsigned short inline SetLcData(unsigned short Lc,unsigned short nLoad){return Lc<<10|nLoad;}//����λLc,��ʮλnLoad
	unsigned short inline GetNum(unsigned short val) const{return val&(0x3FF);}//��ʮλ
	unsigned short inline GetLcId(unsigned short val) const{return (val&(0xFC00))>>10;}//����λ
	BOOL GetLcIndex(unsigned short iLC,unsigned short &index) const;//�ҵ���Ӧ�������ݵ��ڲ����
};

*/
//�������ݣ�����Ҫ���ر�
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
		BOOL AppendLoad(int iLC,const CLoad &load);//ָ���������Ӻ���
		BOOL SetLoad(int index,const CLoad &load);//�滻ָ��λ�ú���
		BOOL ReplaceLoad(int iLC, const CLoad &load, vector<int>& vType);
		BOOL RemoveLc(int iLC);
		void Read(CASCFile &fin);
		void Write(CASCFile &fout,int &index,int id,int iStructType=-1);
		void Write2020(CASCFile &fout,int &index,int id,int iStructType=-1);
		void ReadBin(CFile &fin);
		void WriteBin(CFile &fout);
		CString GetShowText(int nCaseId, bool bGloabal = true);
		//�õ�Ҫ�޸����ݵĵ�ַֻ�������Խ����޸ģ�����
		float *GetDataDirect(int index,int iData);
		//�����Ч����
		void ClearInvalidData();
		//�������ݲ����Ǿ��غ�������
		void ReadDyna(CASCFile &fin);
		void WriteDyna(CASCFile &fout,int &index,int id);
		void ClearInvalidDynaData();
		//���ع����ر��
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
