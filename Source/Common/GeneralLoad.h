
#pragma once
#include "HeadDefine.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "PublicFunc.h"
#include "PublicFunc_MFC.h"
#include "ASCFile.h"
#include "UserDefine.h"

#include <afxtempl.h>
#include <vector>
//#include <algorithm>
//#include <functional>
#include <map>

using namespace std;



//�������
class _SSG_DLLIMPEXP CGeneralLoad
{
public:
	CGeneralLoad(void);
	CGeneralLoad(CASE_TYPE nType,bool bNewCode=true);
	CGeneralLoad(CGeneralLoad &lc)
	{
		*this=lc;
	}
	~CGeneralLoad() {}
	
	CASE_TYPE m_iCaseType;//��������
	CString m_sCaseName;  //���ع�������
	CString m_sMemo;
	float m_fMassCoef;//�������ش���ֵ���ֵϵ��
	//����ϵ����	�㣺2018�ɿ��Ա�׼���������ء�������0��2008�ɿ��Ա�׼�������ء�����������������
	//						�����ϵ�������ϵ����0
	//						�磺����ϵ�����������ϵ�����������ϵ��
	//					�������ء������ء�0
	float m_fPartCoef[3];
	float m_fLcComb[Sys_MaxLoadcaseComb];//�������
	float m_fBucklingComb; //���������������
	CGeneralLoad& operator=(const CGeneralLoad& lc);
	BOOL operator==(const CGeneralLoad& lc);
	
	void Read(CASCFile &fin);
	void Write(CFile &fout);
};

class _SSG_DLLIMPEXP CGeneralCollection
{
public:
	CGeneralCollection(){
	m_iCode=1;
	m_fGravPart=1.2f;
	}
	CGeneralCollection(const CGeneralCollection &load) 
	{
		*this=load;
	};
	~CGeneralCollection(){RemoveAll();}

	int Append(CGeneralLoad *load);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return aGenLoadPtr.GetCount();}

	CGeneralLoad *GetAt(int i) {return aGenLoadPtr.GetAt(i);}

	CGeneralLoad *operator[](int i) {return aGenLoadPtr[i];}

	void SetAt(int i,CGeneralLoad *load) {aGenLoadPtr[i]=load;}

	CGeneralCollection& operator=(const CGeneralCollection&load);

	void Write(CFile &fout) 
	{
		for(int i=0;i<aGenLoadPtr.GetCount();i++)
			aGenLoadPtr[i]->Write(fout);
	}
	
	int m_iCode;//1:Code2018 0:Code2008
	float m_fGravPart;//�������ط���ϵ��
private:
	CArray<CGeneralLoad*,CGeneralLoad*> aGenLoadPtr; //���ع�����ϼ���
};
