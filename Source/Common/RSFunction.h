
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



//反应谱函数
class _SSG_DLLIMPEXP CRSFunction
{
public:
	CRSFunction(void);
	CRSFunction(CRSFunction &Rs)
	{
		*this=Rs;
	}
	~CRSFunction() {}	

	//反应谱函数
	CString sRSName;  //反应谱函数名称
	BOOL m_bUserDefine;   //是否用户自定义,0-规范,1-用户自定义
	int m_iCode;  //，0-抗规，1-隔规； 
    float m_fIntensity; //设防烈度；
	int m_iEqLevel; //地震水平；
	float m_fAlphaMax; //地震影响系数最大值；
	int m_iEqGroup;    //设计地震分组；
	int m_iSiteType;     //场地类别；
	float m_fTg; //特征周期；
	float m_fDampRatio; //阻尼比； 
	float m_fMaxT; //最大周期
	

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
	CArray<CRSFunction*,CRSFunction*> aRSPtr; //反应谱函数集合
};
