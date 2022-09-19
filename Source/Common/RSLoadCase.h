
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



//��Ӧ�׺���
class _SSG_DLLIMPEXP CRSLoadCase
{
public:
	CRSLoadCase(void);
	CRSLoadCase(CRSLoadCase &Rs)
	{
		*this=Rs;
	}
	~CRSLoadCase() {}	

	//��Ӧ�׺���
	CString m_sRSLCName;         //��Ӧ�׹�������
	int m_iRSFuntion;     //��Ӧ�׺������
	int m_iDir;       //����
	float m_fAngle;   //�Ƕ�
	BOOL m_bAutoSearch; //�Զ���������Ƕ�
	int m_iCombType;    //��Ϸ�ʽ
	int m_iDampType;    //��������
	float m_fUniDampRatio;   //ͳһ�����
	float m_fSteelDampRatio; //�ֲ������
	float m_fConDampRatio;   //�����������
	float m_fTReduCoef;      //�����ۼ�ϵ��


	CRSLoadCase& operator=(const CRSLoadCase& Rs);
	BOOL operator==(const CRSLoadCase& Rs);

	void Read(CASCFile &fin);
	void Write(CFile &fout);
};

class _SSG_DLLIMPEXP CRSLoadCaseCollection
{
public:
	CRSLoadCaseCollection(){;}
	CRSLoadCaseCollection(const CRSLoadCaseCollection &RS) 
	{
		*this=RS;
	};
	~CRSLoadCaseCollection(){RemoveAll();}

	int Append(CRSLoadCase *RS);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return aRSPtr.GetCount();}

	CRSLoadCase *GetAt(int i) {return aRSPtr.GetAt(i);}

	CRSLoadCase *operator[](int i) {return aRSPtr[i];}

	void SetAt(int i,CRSLoadCase *RS) {aRSPtr[i]=RS;}

	CRSLoadCaseCollection& operator=(const CRSLoadCaseCollection&RS);

	void Write(CFile &fout) 
	{
		for(int i=0;i<aRSPtr.GetCount();i++)
			aRSPtr[i]->Write(fout);
	}

private:
	CArray<CRSLoadCase*,CRSLoadCase*> aRSPtr; //��Ӧ�׺�������
};
