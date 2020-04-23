
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



//�����
class _SSG_DLLIMPEXP CWindLoad
{
public:
	CWindLoad(void);
	CWindLoad(CWindLoad &lc)
	{
		*this=lc;
	}
	~CWindLoad() {}

	
	CString sCaseName;  //����ع�������
	BOOL m_bUserDefine;   //�Ƿ��û��Զ���,0-�������,1-�û��Զ���
		

	//�����
	int m_iRough;  //�ֲڶ����0-A��1-B��2-C��3-D�� 
    float m_fWindPressure; //������ѹ��
	float m_fXPeriod; //X��������ڣ�
	float m_fYPeriod; //Y��������ڣ�
	float m_fDamp;    //����ؼ���������ȣ�
	float m_fAmp;     //�����ЧӦ�Ŵ�ϵ����
	int m_iGroup;     //��������ͷֶ�����
	int m_iHighStory[3]; //�������¥��ţ�
	float m_fShapeCoefGroup[3][2]; //����X������ϵ����Y������ϵ���� 
	int m_iAlongWind; //�Ƿ���˳�������0-�����ǣ�1-���ǣ�
	int m_iAcrossWind;//�Ƿ��Ǻ�������0-�����ǣ�1-���ǣ�
	int m_iTorWind;   //�Ƿ���Ťת�����0-�����ǣ�1-���ǣ�
	int m_iAngleType; //�н����ͣ�0-���ǣ�1-���ǣ�
	float m_fbBratio; //b/B
	float m_fFirstTorPeriod; //��һŤת����
	float m_fLevel; //���������


	float fWindAngle;	//��������÷�����X��н�
	float fCoefAlong;	//˳�������ϵ��
	float fCoefAcross;	//��������ϵ��
	float fCoefTortion;	//Ťת�����ϵ��
	float m_AlongWind[Sys_Max_Stories][Sys_Max_Towers]; //˳�������
	float m_AcrossWind[Sys_Max_Stories][Sys_Max_Towers]; //���������
	float m_TorsionalWind[Sys_Max_Stories][Sys_Max_Towers]; //Ťת�����
	float m_fLcComb[Sys_MaxLoadcaseComb];//�������
	float m_fBucklingComb; //���������������

	CWindLoad& operator=(const CWindLoad& lc);
	BOOL operator==(const CWindLoad& lc);

	void Read(CASCFile &fin);
	void Write(CFile &fout);
};

class _SSG_DLLIMPEXP CWindCollection
{
public:
	CWindCollection(){;}
	CWindCollection(const CWindCollection &load) 
	{
		*this=load;
	};
	~CWindCollection(){RemoveAll();}

	int Append(CWindLoad *load);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return aWindLoadPtr.GetCount();}

	CWindLoad *GetAt(int i) {return aWindLoadPtr.GetAt(i);}

	CWindLoad *operator[](int i) {return aWindLoadPtr[i];}

	void SetAt(int i,CWindLoad *load) {aWindLoadPtr[i]=load;}

	CWindCollection& operator=(const CWindCollection&load);

	void Write(CFile &fout) 
	{
		for(int i=0;i<aWindLoadPtr.GetCount();i++)
			aWindLoadPtr[i]->Write(fout);
	}

private:
	CArray<CWindLoad*,CWindLoad*> aWindLoadPtr; //���ع�����ϼ���
};
