#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "HeadDefine.h"

class _SSG_DLLIMPEXP CVisibleMesh
{
public:
	CVisibleMesh(void);

	//���ƹ��캯��
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

	int m_iIndex; //��ǰ�ɼ���λ��ţ��ӵ�λ��ʼ�������л��ɼ���ѡ�񼯣���Χ-1,0--31,-1Ϊȫ�ɼ�

	int m_nNode;
	int m_nBeamElm;
	int m_nTriElm;
	int m_nQuadElm;
	int m_nTetElm;

	//����
	int m_nNode0;
	int m_nBeamElm0;
	int m_nTriElm0;
	int m_nQuadElm0;
	//int m_nTetElm0;

	CString m_pName[32];  //ѡ������

	//����ߵĿɼ��Բ��ý���ѡȡ�����Ǹ������Ͱ�Ŀɼ��Խ�������
	DWORD *m_pVisibleNode;   //��ܵ�ɼ��ԣ���λ�洢��ÿλ����һ��ѡ�񼯣�ÿ��Ԫ����m_aVexһһ��Ӧ��Ҫע��һ������

	DWORD *m_pVisibleBeamElm;  //�ṹ�߿ɼ��ԣ���λ�洢��ÿλ����һ��ѡ�񼯣�ÿ��Ԫ����m_aLineһһ��Ӧ��Ҫע��һ������

	DWORD *m_pVisibleTriElm;  //�߹����ɼ��ԣ���λ�洢��ÿλ����һ��ѡ�񼯣�ÿ��Ԫ����CFrame���߹���һһ��Ӧ��Ҫע��һ������
	DWORD *m_pVisibleQuadElm; //�湹���ɼ��ԣ���λ�洢��ÿλ����һ��ѡ�񼯣�ÿ��Ԫ����CFrame���湹��һһ��Ӧ��Ҫע��һ������

	DWORD *m_pVisibleTetElm;

	//��¼�༭ǰ�Ĺ�������
	BOOL PrepareAppend(void);
	//��������ͼԪ��ӵ���ǰѡ���У���m_iIndex==-1��ֱ�ӷ���,���ӹ���ǰ�����ȵ���PrepareAppend()����
	BOOL AppendCollection(void);

	int m_iNum; //0--29 ��ǰ���λ����������30��31λ
	static const int m_nCurrent=30;	// ��ǰ��ʾ �� 2016��7��6��
	static const int m_nBackup=31;   //�ϲ���ʾ �� 2016��7��6��
	//���ɶ���ѡ��  �� 2016��7��6��
	BOOL SetCollectionVisible(int nNewVex,int nNewLine,int nNewBeam,int nNewPlate,int nNewSolid,int nSel,const int *pSel,int nFlagVisible);
	//����ѡ��  �� 2016��7��6��
	BOOL CopyCollection(int nOrign,int nCopy);
	//���ĳ��ʾ������
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


