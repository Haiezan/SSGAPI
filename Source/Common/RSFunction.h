
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
class _SSG_DLLIMPEXP CRSFunction
{
public:
	CRSFunction(void);
	CRSFunction(CRSFunction &Rs)
	{
		*this=Rs;
	}
	~CRSFunction() {}	

	//��Ӧ�׺���
	CString sRSName;  //��Ӧ�׺�������
	BOOL m_bUserDefine;   //�Ƿ��û��Զ���,0-�淶,1-�û��Զ���
	int m_iCode;  //��0-���棬1-���棻 
    float m_fIntensity; //����Ҷȣ�
	int m_iEqLevel; //����ˮƽ��
	float m_fAlphaMax; //����Ӱ��ϵ�����ֵ��
	int m_iEqGroup;    //��Ƶ�����飻
	int m_iSiteType;     //�������
	float m_fTg; //�������ڣ�
	float m_fDampRatio; //����ȣ� 
	float m_fMaxT; //�������
	

	CRSFunction& operator=(const CRSFunction& Rs);
	BOOL operator==(const CRSFunction& Rs);

	void Read(CASCFile &fin);
	void Write(CFile &fout);
};

class _SSG_DLLIMPEXP CRSFunctionCollection
{
public:
	CRSFunctionCollection(){;}
	CRSFunctionCollection(const CRSFunctionCollection &RS) 
	{
		*this=RS;
	};
	~CRSFunctionCollection(){RemoveAll();}

	int Append(CRSFunction *RS);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return aRSPtr.GetCount();}

	CRSFunction *GetAt(int i) {return aRSPtr.GetAt(i);}

	CRSFunction *operator[](int i) {return aRSPtr[i];}

	void SetAt(int i,CRSFunction *RS) {aRSPtr[i]=RS;}

	CRSFunctionCollection& operator=(const CRSFunctionCollection&RS);

	void Write(CFile &fout) 
	{
		for(int i=0;i<aRSPtr.GetCount();i++)
			aRSPtr[i]->Write(fout);
	}

private:
	CArray<CRSFunction*,CRSFunction*> aRSPtr; //��Ӧ�׺�������
};
