#pragma once

#include "DataPrimitive.h"

//LOADASSIGN 
#include "Loadmap.h"
#include "DefectCaseMbr.h"

//�ṹ����
class _SSG_DLLIMPEXP CStrucProp : public CPrimitiveProp
{
public:
	CStrucProp(void);
	//���ƹ��캯��
	CStrucProp(const CStrucProp &prop) 
	{
		*this=prop;
	}

	~CStrucProp()
	{
		aElms.RemoveAll();
		aload.clear();
		aDefect.clear();
	};

	void Clear();

	int PmID;
	STRUCT_TYPE iStrucType;

	CString ConcMat;         //�Ų���
	CString RebarMat;        //�ֽ����,��Ե�����������ݽ���Ϸ���RebarMat�����Ҳ���ڸֽ������
	CString StirrupMat;      //�������	//�Ǳ��� 2015.6.5
	CString SteelMat;		 //�͸ֲ���
	CString sComments2;  //������ʾ��˵������,�ɳ�����ʱ����//��ʾ�ڶ����ڵ��� 

	float fDeadLoad; //����أ���λ�����λ����,��KN/m2����KN/m,����Ϊ����б�尴ʵ��������㣬б����ʵ�ʳ��ȼ���
	float fLiveLoad; //����أ���λ�����λ����,��KN/m2����KN/m,����Ϊ����б�尴ʵ��������㣬б����ʵ�ʳ��ȼ���

	int iMidSeismContstiType;//��������Ŀ�� 0������1����
	int iRareSeismContstiType;//��������Ŀ�� 0������1����
	int iRareNormSectPerformObject;  //��������������Ŀ�� 0������ 1���� 2������ 3���޳�����
	int iRareDiagSectPerformObject;  //����б��������Ŀ�� 0������ 1���� 2������ 3���޳�����
	int iMidNormSectPerformObject;  //��������������Ŀ�� 0������ 1���� 2������ 3���޳�����
	int iMidDiagSectPerformObject;  //����б��������Ŀ�� 0������ 1���� 2������ 3���޳�����
	int iVipType;//�������ͣ�0-δ���࣬1-�ؼ�������2-��ͨ���򹹼���3-���ܹ���
	int iSeismicGrade;//����ȼ�
	int iDatailsGrade;//������ȼ�
	CString sMemberName;//��������
	LOADASSIGN aload;//��Ӧ���ع����ĺ���
	LOADASSIGN aDyload;//��Ӧ���ع����Ķ����� ����20230412

	float fAxisFactor;			//��������ϵ��
	float fMomentFactor;	//��ص���ϵ��
	float fShearFactor;		//��������ϵ��
	float fAxisFactorR;		//�������������ϵ��
	float fMomentFactorR;	//�������������ϵ��	
	float fShearFactorR;	//��������������ϵ��	
	float fMeshRatio; //�������ϵ����>1���ܣ������ڵ������ݶ�

	//������ʼȱ�� 20221114��������
	DEFECTASSIGN aDefect; //��Ӧȱ�ݹ�����ȱ��ֵ

	//��ʱ����
	CArray<int,int> aElms;  //��Ԫ����,����Ԫ�������ε�Ԫ���Ϊԭʼ��ţ��ı��ε�Ԫ���=m_nTriangle+i,����ȫ�������Լ�����������γ�
	unsigned int tmp_Msg; //��ʱ������Ϣ����,ע��ʹ�ú�ָ�,0x01-���ڷ�Э������


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
		sComments2 = prop.sComments2;

		fDeadLoad=prop.fDeadLoad;
		fLiveLoad=prop.fLiveLoad;

		iMidSeismContstiType=prop.iMidSeismContstiType;
		iRareSeismContstiType=prop.iRareSeismContstiType;
		iMidNormSectPerformObject = prop.iMidNormSectPerformObject;
		iMidDiagSectPerformObject = prop.iMidDiagSectPerformObject;
		iRareNormSectPerformObject = prop.iRareNormSectPerformObject;
		iRareDiagSectPerformObject = prop.iRareDiagSectPerformObject;

		iVipType=prop.iVipType;

		iSeismicGrade=prop.iSeismicGrade;
		iDatailsGrade=prop.iDatailsGrade;
		sMemberName=prop.sMemberName;

		aload=prop.aload;
		aDyload = prop.aDyload;

		fAxisFactor = prop.fAxisFactor;			//��������ϵ��
		fMomentFactor = prop.fMomentFactor;	//��ص���ϵ��
		fShearFactor = prop.fShearFactor;		//��������ϵ��

		fAxisFactorR = prop.fAxisFactorR;			//��������ϵ��
		fMomentFactorR = prop.fMomentFactorR;	//��ص���ϵ��
		fShearFactorR = prop.fShearFactorR;		//��������ϵ��
		fMeshRatio = prop.fMeshRatio;

		//���ڿ�ܸ���ʱ�����ڵ�Ԫ���ݣ���˲���Ҫ����
		aElms.RemoveAll();
		tmp_Msg = 0;

		return *this;
	}
	//virtual BOOL Read(CASCFile &fin);   
	//virtual BOOL Write(CASCFile &fout);

	//virtual void ReadBin(CFile &fin);   
	//virtual BOOL WriteBin(CFile &fout);
	float GetC(); //���㲨��
};

struct PIN
{
	int IdBC;
	int Pin1;
	int Pin2;
	PIN() :IdBC(-1), Pin1(0), Pin2(0) {}
	PIN(int bc, int ip1, int ip2) :IdBC(bc), Pin1(ip1), Pin2(ip2) {};
	PIN& operator=(const PIN& Pin)
	{
		if (this == &Pin)
			return *this;

		IdBC = Pin.IdBC;
		Pin1 = Pin.Pin1;
		Pin2 = Pin.Pin2;
		return *this;
	}
};

class _SSG_DLLIMPEXP CPinData
{
public:
	CPinData();
	~CPinData();
	CPinData(const CPinData& aPin)
	{
		*this = aPin;
	};
	CPinData& operator=(const CPinData& aPin);

	void clear();
	int Find(int iBC) const;
	void SetPin(int iBC, int iPin1, int iPin2);
	void SetPin(int iBC, bool bFirst, int iPin);
	bool GetPin(int iBC, int& iPin1, int& iPin2)const;
	void GetPinAt(int index, int& iBC, int& iPin1, int& iPin2);
	void GetPinAt(int index, int& iBC, int*& iPin1, int*& iPin2);
	void RemoveAt(int iBC);
	void CopyPin(int iCurBC, int iAimBC, bool bTrans = false);
public:
	PIN* pPin;
	int nPin;
};