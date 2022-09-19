#pragma once

#include "DataPrimitive.h"


//LOADASSIGN 
#include "Loadmap.h"

//�ṹ����
class _SSG_DLLIMPEXP CStrucProp : public CPrimitiveProp
{
public:
	CStrucProp(void);
	//���ƹ��캯��
	CStrucProp(const CStrucProp &prop) 
	{
		aload.clear();
		*this=prop;
	}

	~CStrucProp()
	{
		aElms.RemoveAll();
		aload.clear();
	};
	int PmID;
	STRUCT_TYPE iStrucType;

	CString ConcMat;         //�Ų���
	CString RebarMat;        //�ֽ����,��Ե�����������ݽ���Ϸ���RebarMat�����Ҳ���ڸֽ������
	CString StirrupMat;      //�������	//�Ǳ��� 2015.6.5
	CString SteelMat;		 //�͸ֲ���

	float fDeadLoad; //����أ���λ�����λ����,��KN/m2����KN/m,����Ϊ����б�尴ʵ��������㣬б����ʵ�ʳ��ȼ���
	float fLiveLoad; //����أ���λ�����λ����,��KN/m2����KN/m,����Ϊ����б�尴ʵ��������㣬б����ʵ�ʳ��ȼ���

	int iMidSeismContstiType;//��������Ŀ�� 0������1����
	int iRareSeismContstiType;//��������Ŀ�� 0������1����
	int iVipType;//�������ͣ�0-δ���࣬1-�ؼ�������2-��ͨ���򹹼���3-���ܹ���
	int iSeismicGrade;//����ȼ�
	int iDatailsGrade;//������ȼ�
	CString sMemberName;//��������
	LOADASSIGN aload;//��Ӧ���ع����ĺ���
	float fAxisFactor;			//��������ϵ��
	float fMomentFactor;	//��ص���ϵ��
	float fShearFactor;		//��������ϵ��

	//��ʱ����
	CArray<int,int> aElms;  //��Ԫ����,����Ԫ�������ε�Ԫ���Ϊԭʼ��ţ��ı��ε�Ԫ���=m_nTriangle+i,����ȫ�������Լ�����������γ�


	CStrucProp & operator=(const CStrucProp &prop)
	{
		if(this==&prop) return *this;

		*(CPrimitiveProp *)this=(CPrimitiveProp &)prop;
		PmID=prop.PmID;
		iStrucType=prop.iStrucType;

		ConcMat=prop.ConcMat;        
		RebarMat=prop.RebarMat;   
		StirrupMat=prop.StirrupMat;  
		SteelMat=prop.SteelMat; 

		fDeadLoad=prop.fDeadLoad;
		fLiveLoad=prop.fLiveLoad;

		iMidSeismContstiType=prop.iMidSeismContstiType;
		iRareSeismContstiType=prop.iRareSeismContstiType;
		iVipType=prop.iVipType;

		iSeismicGrade=prop.iSeismicGrade;
		iDatailsGrade=prop.iDatailsGrade;
		sMemberName=prop.sMemberName;

		aload=prop.aload;

		fAxisFactor = prop.fAxisFactor;			//��������ϵ��
		fMomentFactor = prop.fMomentFactor;	//��ص���ϵ��
		fShearFactor = prop.fShearFactor;		//��������ϵ��

		//���ڿ�ܸ���ʱ�����ڵ�Ԫ���ݣ���˲���Ҫ����
		aElms.RemoveAll();

		return *this;
	}
	//virtual BOOL Read(CASCFile &fin);   
	//virtual BOOL Write(CASCFile &fout);

	//virtual void ReadBin(CFile &fin);   
	//virtual BOOL WriteBin(CFile &fout);
};

