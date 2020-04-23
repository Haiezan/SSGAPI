#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "HeadDefine.h"

class _SSG_DLLIMPEXP CVisibleStruct
{
public:
	CVisibleStruct(void);

	//���ƹ��캯��
	CVisibleStruct(const CVisibleStruct &v) 
	{
		m_pVisibleVex=NULL;
		m_pVisibleLine=NULL;
		m_pVisibleBeam=NULL;
		m_pVisiblePlate=NULL;
		*this=v;
	}

	~CVisibleStruct(void);

	int m_iIndex; //��ǰ�ɼ���λ��ţ��ӵ�λ��ʼ�������л��ɼ���ѡ�񼯣���Χ-1,0--31,-1Ϊȫ�ɼ�

	int m_nVex;  //m_pVisibleVex�����е�Ԫ�ظ���
	int m_nLine; //m_pVisibleLine�����е�Ԫ�ظ���
	int m_nBeam;  //m_pVisibleBeam�����е�Ԫ�ظ���
	int m_nPlate; //m_pVisiblePlate�����е�Ԫ�ظ���
	CString m_pName[32];  //ѡ������

	//����ߵĿɼ��Բ��ý���ѡȡ�����Ǹ������Ͱ�Ŀɼ��Խ�������
	DWORD *m_pVisibleVex;   //��ܵ�ɼ��ԣ���λ�洢��ÿλ����һ��ѡ�񼯣�ÿ��Ԫ����m_aVexһһ��Ӧ��Ҫע��һ������
	DWORD *m_pVisibleLine;  //�ṹ�߿ɼ��ԣ���λ�洢��ÿλ����һ��ѡ�񼯣�ÿ��Ԫ����m_aLineһһ��Ӧ��Ҫע��һ������

	DWORD *m_pVisibleBeam;  //�߹����ɼ��ԣ���λ�洢��ÿλ����һ��ѡ�񼯣�ÿ��Ԫ����CFrame���߹���һһ��Ӧ��Ҫע��һ������
	DWORD *m_pVisiblePlate; //�湹���ɼ��ԣ���λ�洢��ÿλ����һ��ѡ�񼯣�ÿ��Ԫ����CFrame���湹��һһ��Ӧ��Ҫע��һ������

	//���ڼ�¼�༭ǰ�Ĺ�������
	int m_nVex0;
	int m_nLine0;
	int m_nBeam0;
	int m_nPlate0;

	//��¼�༭ǰ�Ĺ�������
	BOOL PrepareAppend(void);
	//��������ͼԪ��ӵ���ǰѡ���У���m_iIndex==-1��ֱ�ӷ���,���ӹ���ǰ�����ȵ���PrepareAppend()����
	BOOL AppendCollection(void);

	////�������ñ��Ϊm_iIndex��ѡ�񼯣�pSelΪ��ѡ��ͼԪ���飬��m_iIndex==-1�������ѡȡ�Ի���
	//BOOL SetCollection(int nNewVex,int nNewLine,int nNewBeam,int nNewPlate,int nSel,const int *pSel);

	int m_iNum; //0--29 ��ǰ���λ����������30��31λ
	static const int m_nCurrent=30;	// ��ǰ��ʾ �� 2016��7��6��
	static const int m_nBackup=31;   //�ϲ���ʾ �� 2016��7��6��
	//���ɶ���ѡ��  �� 2016��7��6��
	BOOL SetCollectionVisible(int nNewVex,int nNewLine,int nNewBeam,int nNewPlate,int nSel,const int *pSel,int nFlagVisible);
	//����ѡ��  �� 2016��7��6��
	BOOL CopyCollection(int nOrign,int nCopy);
	//���ĳ��ʾ������
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


