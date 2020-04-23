
#pragma once
#include "HeadDefine.h"
#include "Vector4.h"
#include "Matrix4x4.h"
//#include "SysPara.h"
#include "PublicFunc.h"
#include "PublicFunc_MFC.h"


#include "ASCFile.h"
#include "UserDefine.h"
#include "BeamSection.h"
#include "Material.h"
#include "EdgeStruct.h"


#include <afxtempl.h>
#include <vector>
//#include <algorithm>
//#include <functional>

using namespace std;


struct DATA_SEQUENCE2
{
	float t,v;
};



//����ϵ���࣬2������
class _SSG_DLLIMPEXP CDataSequence2
{
public:
	CDataSequence2(void){fname=L"";iWaveLibIndex=-1; iWaveLib=0; pData=NULL; nPoints=0; 
	fMinValue=fMaxValue=0;fMinValueTime=fMaxValueTime=0;fMaxFileTime=0;}

	CDataSequence2(const CDataSequence2 &ds)
	{
		*this=ds;
	}

	~CDataSequence2()
	{
		Clear();
	}

	CString fname; //�ļ���
	int iWaveLibIndex; //�Ǳ��� 2015.6.11
	int iWaveLib;	//0----SSG���𲨿⣬ 1-----�û��Զ��岨
	int nPoints;  //���ݵ���

	//����Ϊ��ʱ����
	float fMinValue,fMaxValue;  //�����Сֵ�������ļ�ʱͳ�Ƶõ�
	float fMinValueTime,fMaxValueTime;  //�����Сֵʱ�̣������ļ�ʱͳ�Ƶõ� //2016.3.16
	float fMaxFileTime;  //�����ļ��е����ʱ��

	DATA_SEQUENCE2	*pData;

	void Clear(void) 
	{
		if (pData){delete[] pData;	pData=NULL;}

		nPoints=0;
		//fMinValue=fMaxValue=0;
		//fname=L"";
	}
	BOOL IsValid(){return nPoints>0 && pData;}

	//��ֵ���������
	CDataSequence2 & operator=(const CDataSequence2& data)
	{
		if(this==&data) return *this;
		Clear();
		fname=data.fname;
		iWaveLibIndex = data.iWaveLibIndex;
		iWaveLib =data.iWaveLib;
		nPoints=data.nPoints;
		pData=new DATA_SEQUENCE2[nPoints];
		ASSERT(pData);
		for(int i=0;i<nPoints;i++)
		{
			pData[i]=data.pData[i]; 
		}
		fMinValue=data.fMinValue;
		fMaxValue=data.fMaxValue;
		fMinValueTime=data.fMinValueTime;
		fMaxValueTime=data.fMaxValueTime;
		fMaxFileTime=data.fMaxFileTime;
		return *this;
	}

	//2017�汾����
	void ReadAcc2017(void); //ֻ��ȡ����nPoints��pData

};

//������ص�һ����������
class _SSG_DLLIMPEXP CEarthQuake
{
public:
	CEarthQuake(void);
	CEarthQuake(CEarthQuake &eq) {*this=eq;}
	~CEarthQuake(){;}

	int iEarthQuakeProbility;
	int iAccDefineMethod;
	float fMainAmpEffect,f2ndAmpEffect,f3rdAmpEffect;  //��Ч��ֵ��������ٶȷ�ֵ���η����ֵ���ٶȣ���ֱ�����ֵ���ٶ� 
	float fMainAmp,f2ndAmp,f3rdAmp; // ʵ�ʷ�ֵ��������ٶȷ�ֵ���η����ֵ���ٶȣ���ֱ�����ֵ���ٶ�
	float fTimeInterval;	//���ݵ�ʱ����
	float fStartComputeTime;//ʱ�̷�����ʼʱ��
	float fEndComputeTime;  //ʱ�̷�����ֹʱ��
	float fMaxFileTime;		//�������ʱ��=max(X-�ļ����ʱ��, Y-�ļ����ʱ��, Z-�ļ����ʱ��)
	int iMainDir;			//������0--X��1--Y


	CDataSequence2 cAX,cAY,cAZ;  //�����ļ��е�ԭֵ

	void GetRatio(float &fRatioX,float &fRatioY,float &fRatioZ);  //����fMainAmp,fRatio1,fRatio2����fRatioX,fRatioY,fRatioZ
	void ReadData();  //��ȡ��������ĵ�������
	int CreateData(float *&ax,float *&ay,float *&az);  //�������飬��ֵ���㵱ǰ������е�����ص�
	void  GetRealPeakAccValue(); //��fMainAmp
	CEarthQuake & operator=(const CEarthQuake &eq);
	BOOL  operator==(const CEarthQuake &eq);//�� 2018��3��2��

	void Read10(CASCFile &fin);  //ֻ��ȡ������Ϣ������ϵ����ʹ��ʱ��ȡ
	void Read(CASCFile &fin);  //ֻ��ȡ������Ϣ������ϵ����ʹ��ʱ��ȡ
	void Write(CFile &fout); //ֻ����������Ϣ
};



class CLoadCase;

//�������
class _SSG_DLLIMPEXP CLoadCase
{
public:
	CLoadCase(void);
	CLoadCase(CString sVer);
	CLoadCase(CLoadCase &lc)
	{
		*this=lc;
	}

	~CLoadCase() {}

	CString sCaseName;  //�����������
	CString sMemo;  //˵��
 	int iLoadComb;		//�������

	//��ʽ�������ز���
	BOOL  bCloseNonLinear; //�Ƿ�رռ��η����ԣ�1-�ر�
	BOOL  bCalIsolatorBeta; 
	float fMassDamp;	//��������ϵ����
	float fStiffDamp; //�ն�����ϵ��
	float fTerm1;  	//��������1
	float fTerm2;  	//��������2
	float fKsi1;   	//���������1
	float fKsi2;   	//���������2
	BOOL bInputAlpha;	//�Ƿ�ֱ������ //ver32
	float fTimeStep;  //����ʱ�䲽��
	int iCrtCons;  //��������ά����ģ��,0���ԡ�1�������ˡ�2-���ܻ����
	int iRebarCons;  //�ֽ��ģ��,0���ԡ�1�����ԡ�2-���ܻ����
	int	iStirrupCons;  //��������ͣ�ȡֵΪ0--���ԡ�1--�淶ģ�͡�2---Լ��������ģ��
	int iSlabElastic; //�Ƿ���¥�嵯��
	int m_bShearNonLinear; //�Ƿ��Ǽ��з�����
	float fShearGama; //��������Ӧ��
	float fShearRatio; //����������նȱ�
	float fWallShear; //����ǽ�ֲ��ֽ������ϵ��
	int	iDamage;  //���˶��巽ʽ
	int	iMethod;  //��������

	float fWaveAngle; //����������������ϵ�н�
	BOOL bStiffDamp;  //�Ƿ����ն�����
	int	iDampType;  //�������ͣ�0-Rayleigh���ᣬ1-��������
	int nModeNum;  //���͸��������ڼ����������ᣬm_iDampType=1ʱ��Ч
	int iModalDampType;  //�����������ͣ�0-ȫ¥ͳһ��1-����������
	int iSimpleModalDamp;  //����������
	float fModeDamp[Sys_MaxModeNum];  //��Ӧ��m_iModeNum�ĸ������͵�����ȣ�m_iDampType=1ʱ��Ч
	float fModeDampSteel[Sys_MaxModeNum];  //��Ӧ��m_iModeNum�ĸ������͵�����ȣ�m_iDampType=1ʱ��Ч//2017.8.26
	int m_iIsoBndType;		//0-����֧���϶�����ƽ��λ�ơ�����ת��λ�ƶ��̶���1-����֧���϶�����ƽ��λ�ƹ̶�������ת��λ���ͷ�
	BOOL m_bConcRatioEffect;
	BOOL m_bSteelRatioEffect;
	BOOL m_bRebarBuckling;

	BOOL bStaticExp;	//������ʽ��������������ؼ��� 1-�ǣ�0-��
	BOOL bStaticResult;
	float fStaticTime;//���������Լ���ʱ��
	float fStaticAmpCoef;//���������Ժ��طŴ�ϵ��
	BOOL m_bOverallDefect;
	BOOL m_bMemberDefect;	
	float m_fConLoadCoef[Sys_MaxLoadcase]; //����������ϵ��
	float m_fVarLoadCoef[Sys_MaxLoadcase]; //�ɱ�������
	float fStaticExpTime;//��ʼ�������Ƿ�����ʱ�� �� bStaticExp ��bStaticResult ��Ӧ
	BOOL bInitAnaly;//�Ƿ���г�ʼ�������羲��������ֱ��������ص����

	CEarthQuake cEarchQuake;  //������Ϣ



	CLoadCase& operator=(const CLoadCase& lc);
	BOOL operator==(const CLoadCase& lc);//ISO��������ã���2018��3��6��
	BOOL isIsoParaEqual(const CLoadCase& lc);//ISO��������ã��жϹ��������Ƿ�ı� ��2018��3��6�� ������������Ϣ�͹�����

	BOOL isElasticPlasticPair(const CLoadCase&);

	void Read10(CASCFile &fin);
	void Read20(CASCFile &fin);
	void Read(CASCFile &fin);
	void Write(CFile &fout);

	float GetProgress();
};

class _SSG_DLLIMPEXP CLoadCollection
{
public:
	CLoadCollection(){sOutputFile=L"EarthQuakeResult\\";}
	CLoadCollection(const CLoadCollection &load) 
	{
		*this=load;
	};
	~CLoadCollection(){RemoveAll();}

	int Append(CLoadCase *load);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return aLoadCasePtr.GetCount();}

	CLoadCase *GetAt(int i) {return aLoadCasePtr.GetAt(i);}

	CLoadCase *operator[](int i) {return aLoadCasePtr[i];}

	void SetAt(int i,CLoadCase *load) {aLoadCasePtr[i]=load;}

	CLoadCollection& operator=(const CLoadCollection&load);

	void Write(CFile &fout) 
	{
		for(int i=0;i<aLoadCasePtr.GetCount();i++)
			aLoadCasePtr[i]->Write(fout);
	}
	void	SetOutputfile(CString sOut){sOutputFile=sOut;}
	CString	Outputfile(){return sOutputFile;}
private:
	CArray<CLoadCase*,CLoadCase*> aLoadCasePtr; //���ع�����ϼ���
	CString sOutputFile;
};

//��ѡ����
class _SSG_DLLIMPEXP CWaveCollection
{
public:
	CWaveCollection(){;}
	CWaveCollection(const CWaveCollection &wave) 
	{
		*this=wave;
	};
	~CWaveCollection(){RemoveAll();}

	int Append(CEarthQuake *wave);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return awavePtr.GetCount();}

	CEarthQuake *GetAt(int i) {return awavePtr.GetAt(i);}

	CEarthQuake *operator[](int i) {return awavePtr[i];}

	void SetAt(int i,CEarthQuake *wave) {awavePtr[i]=wave;}

	CWaveCollection& operator=(const CWaveCollection&wave);

	void Write(CFile &fout) 
	{
		for(int i=0;i<awavePtr.GetCount();i++)
			awavePtr[i]->Write(fout);
	}

private:
	CArray<CEarthQuake*,CEarthQuake*> awavePtr; //���ع�����ϼ���
};
