#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "HeadDefine.h"

class _SSG_DLLIMPEXP CVisibleStruct
{
public:
	CVisibleStruct(void);

	//复制构造函数
	CVisibleStruct(const CVisibleStruct &v) 
	{
		m_pVisibleVex=NULL;
		m_pVisibleLine=NULL;
		m_pVisibleBeam=NULL;
		m_pVisiblePlate=NULL;
		*this=v;
	}

	~CVisibleStruct(void);

	int m_iIndex; //当前可见的位序号，从低位开始，用于切换可见的选择集，范围-1,0--31,-1为全可见

	int m_nVex;  //m_pVisibleVex数组中的元素个数
	int m_nLine; //m_pVisibleLine数组中的元素个数
	int m_nBeam;  //m_pVisibleBeam数组中的元素个数
	int m_nPlate; //m_pVisiblePlate数组中的元素个数
	CString m_pName[32];  //选择集名称

	//点和线的可见性不用交互选取，而是根据梁和板的可见性进行设置
	DWORD *m_pVisibleVex;   //框架点可见性，按位存储，每位代表一个选择集，每个元素与m_aVex一一对应，要注意一起清理
	DWORD *m_pVisibleLine;  //结构线可见性，按位存储，每位代表一个选择集，每个元素与m_aLine一一对应，要注意一起清理

	DWORD *m_pVisibleBeam;  //线构件可见性，按位存储，每位代表一个选择集，每个元素与CFrame的线构件一一对应，要注意一起清理
	DWORD *m_pVisiblePlate; //面构件可见性，按位存储，每位代表一个选择集，每个元素与CFrame的面构件一一对应，要注意一起清理

	//用于记录编辑前的构件数量
	int m_nVex0;
	int m_nLine0;
	int m_nBeam0;
	int m_nPlate0;

	//记录编辑前的构件数量
	BOOL PrepareAppend(void);
	//将新增的图元添加到当前选择集中，若m_iIndex==-1则直接返回,增加构件前必须先调用PrepareAppend()函数
	BOOL AppendCollection(void);

	////重新设置编号为m_iIndex的选择集，pSel为所选的图元数组，若m_iIndex==-1则打开索引选取对话框
	//BOOL SetCollection(int nNewVex,int nNewLine,int nNewBeam,int nNewPlate,int nSel,const int *pSel);

	int m_iNum; //0--29 当前最大位数，不包括30和31位
	static const int m_nCurrent=30;	// 当前显示 邱海 2016年7月6日
	static const int m_nBackup=31;   //上步显示 邱海 2016年7月6日
	//自由定义选择集  邱海 2016年7月6日
	BOOL SetCollectionVisible(int nNewVex,int nNewLine,int nNewBeam,int nNewPlate,int nSel,const int *pSel,int nFlagVisible);
	//复制选择集  邱海 2016年7月6日
	BOOL CopyCollection(int nOrign,int nCopy);
	//清空某显示集数据
	void ClearCollection(int iIndex);

	BOOL IsVexVisible(int idm) const
	{
		if(m_iIndex==-1 || !m_pVisibleVex) return TRUE; 
		if(idm>=m_nVex) return FALSE;
		return m_pVisibleVex[idm] & (1<<m_iIndex);
	}

	BOOL IsLineVisible(int idm) const
	{
		if(m_iIndex==-1 || !m_pVisibleLine) return TRUE;
		if(idm>=m_nLine) return FALSE;
		return m_pVisibleLine[idm] & (1<<m_iIndex);
	}

	BOOL IsBeamVisible(int idm) const
	{
		if(m_iIndex==-1 || !m_pVisibleBeam) return TRUE;
		if(idm>=m_nBeam) return FALSE;
		return m_pVisibleBeam[idm] & (1<<m_iIndex);
	}

	BOOL IsPlateVisible(int idm) const
	{
		if(m_iIndex==-1 || !m_pVisiblePlate) return TRUE;
		if(idm>=m_nPlate) return FALSE;
		return m_pVisiblePlate[idm] & (1<<m_iIndex);
	}

	CVisibleStruct &operator=(const CVisibleStruct &vs)
	{
		if(this==&vs) return *this;

		Clear();

		m_iIndex=vs.m_iIndex; 

		m_nVex=vs.m_nVex;
		m_nLine=vs.m_nLine;
		m_nBeam=vs.m_nBeam;
		m_nPlate=vs.m_nPlate;
		for(int i=0;i<32;i++)
		{
			m_pName[i]=vs.m_pName[i]; 
		}

		m_pVisibleVex=new DWORD[m_nVex];
		m_pVisibleLine=new DWORD[m_nLine];
		m_pVisibleBeam=new DWORD[m_nBeam];
		m_pVisiblePlate=new DWORD[m_nPlate];

		if(!m_pVisibleVex || !m_pVisibleLine || !m_pVisibleBeam || !m_pVisiblePlate)
		{
			Clear();
			return *this;
		}

		for (int i=0;i<m_nVex;i++)
		{
			m_pVisibleVex[i]=vs.m_pVisibleVex[i];
		}

		for (int i=0;i<m_nLine;i++)
		{
			m_pVisibleLine[i]=vs.m_pVisibleLine[i];
		}

		for (int i=0;i<m_nBeam;i++)
		{
			m_pVisibleBeam[i]=vs.m_pVisibleBeam[i];
		}

		for (int i=0;i<m_nPlate;i++)
		{
			m_pVisiblePlate[i]=vs.m_pVisiblePlate[i];
		}

		return *this;
	}

	void Clear(void);

	BOOL Read(void);
	BOOL Write(void);
};


