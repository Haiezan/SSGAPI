#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "HeadDefine.h"

class _SSG_DLLIMPEXP CVisibleMesh
{
public:
	CVisibleMesh(void);

	//复制构造函数
	CVisibleMesh(const CVisibleMesh &v) 
	{
		m_pVisibleNode = NULL;
		m_pVisibleBeamElm = NULL;
		m_pVisibleTriElm = NULL;
		m_pVisibleQuadElm = NULL;
		m_pVisibleTetElm = NULL;

		*this=v;
	}

	~CVisibleMesh(void);

	int m_iIndex; //当前可见的位序号，从低位开始，用于切换可见的选择集，范围-1,0--31,-1为全可见

	int m_nNode;
	int m_nBeamElm;
	int m_nTriElm;
	int m_nQuadElm;
	int m_nTetElm;

	//备用
	int m_nNode0;
	int m_nBeamElm0;
	int m_nTriElm0;
	int m_nQuadElm0;
	//int m_nTetElm0;

	CString m_pName[32];  //选择集名称

	//点和线的可见性不用交互选取，而是根据梁和板的可见性进行设置
	DWORD *m_pVisibleNode;   //框架点可见性，按位存储，每位代表一个选择集，每个元素与m_aVex一一对应，要注意一起清理

	DWORD *m_pVisibleBeamElm;  //结构线可见性，按位存储，每位代表一个选择集，每个元素与m_aLine一一对应，要注意一起清理

	DWORD *m_pVisibleTriElm;  //线构件可见性，按位存储，每位代表一个选择集，每个元素与CFrame的线构件一一对应，要注意一起清理
	DWORD *m_pVisibleQuadElm; //面构件可见性，按位存储，每位代表一个选择集，每个元素与CFrame的面构件一一对应，要注意一起清理

	DWORD *m_pVisibleTetElm;

	//记录编辑前的构件数量
	BOOL PrepareAppend(void);
	//将新增的图元添加到当前选择集中，若m_iIndex==-1则直接返回,增加构件前必须先调用PrepareAppend()函数
	BOOL AppendCollection(void);

	int m_iNum; //0--29 当前最大位数，不包括30和31位
	static const int m_nCurrent=30;	// 当前显示 邱海 2016年7月6日
	static const int m_nBackup=31;   //上步显示 邱海 2016年7月6日
	//自由定义选择集  邱海 2016年7月6日
	BOOL SetCollectionVisible(int nNewVex,int nNewLine,int nNewBeam,int nNewPlate,int nNewSolid,int nSel,const int *pSel,int nFlagVisible);
	//复制选择集  邱海 2016年7月6日
	BOOL CopyCollection(int nOrign,int nCopy);
	//清空某显示集数据
	void ClearCollection(int iIndex);

	BOOL IsNodeVisible(int idm) const
	{
		if(m_iIndex == -1 || !m_pVisibleNode)
			return TRUE; 

		if(idm >= m_nNode) 
			return FALSE;

		return m_pVisibleNode[idm] & (1<<m_iIndex);
	}

	BOOL IsBeamElmVisible(int idm) const
	{
		if(m_iIndex == -1 || !m_pVisibleBeamElm)
			return TRUE;

		if(idm >= m_nBeamElm)
			return FALSE;

		return m_pVisibleBeamElm[idm] & (1<<m_iIndex);
	}

	BOOL IsTriElmVisible(int idm) const
	{
		if(m_iIndex == -1 || !m_pVisibleTriElm)
			return TRUE;

		if(idm >= m_nTriElm)
			return FALSE;

		return m_pVisibleTriElm[idm] & (1<<m_iIndex);
	}

	BOOL IsQuadElmVisible(int idm) const
	{
		if(m_iIndex == -1 || !m_pVisibleQuadElm) 
			return TRUE;

		if(idm >= m_nQuadElm)
			return FALSE;

		return m_pVisibleQuadElm[idm] & (1<<m_iIndex);
	}

	//BOOL IsTetElmVisible(int idm) const
	//{
	//	if(m_iIndex == -1 || !m_pVisibleTetElm)
	//		return TRUE;

	//	if(idm >= m_nTetElm)
	//		return FALSE;

	//	return m_pVisibleTetElm[idm] & (1<<m_iIndex);
	//}

	CVisibleMesh &operator=(const CVisibleMesh &vs)
	{
		if(this==&vs) return *this;

		Clear();

		m_iIndex=vs.m_iIndex; 

		m_nNode = vs.m_nNode;
		m_nBeamElm = vs.m_nBeamElm;
		m_nTriElm = vs.m_nTriElm;
		m_nQuadElm = vs.m_nQuadElm;

		//m_nTetElm = vs.m_nTetElm;

		for(int i=0;i<32;i++)
		{
			m_pName[i]=vs.m_pName[i]; 
		}

		m_pVisibleNode = new DWORD[m_nNode];
		m_pVisibleBeamElm = new DWORD[m_nBeamElm];
		m_pVisibleTriElm = new DWORD[m_nTriElm];
		m_pVisibleQuadElm = new DWORD[m_nQuadElm];

		//m_pVisibleTetElm = new DWORD[m_nTetElm];

		if(!m_pVisibleNode || !m_pVisibleBeamElm || !m_pVisibleTriElm || !m_pVisibleQuadElm
			||!m_pVisibleTetElm)
		{
			Clear();
			return *this;
		}

		for (int i = 0; i < m_nNode; i++)
		{
			m_pVisibleNode[i] = vs.m_pVisibleNode[i];
		}

		for (int i = 0; i < m_nBeamElm; i++)
		{
			m_pVisibleBeamElm[i] = vs.m_pVisibleBeamElm[i];
		}

		for (int i = 0; i < m_nTriElm; i++)
		{
			m_pVisibleTriElm[i] = vs.m_pVisibleTriElm[i];
		}

		for (int i = 0; i < m_nQuadElm; i++)
		{
			m_pVisibleQuadElm[i] = vs.m_pVisibleQuadElm[i];
		}

		for (int i = 0; i < m_nTetElm; i++)
		{
			m_pVisibleTetElm[i] = vs.m_pVisibleTetElm[i];
		}

		return *this;
	}

	void Clear(void);
};


