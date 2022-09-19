
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
#include "StaticLoadCase.h"

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
	void Write2020(CFile &fout); //ֻ����������Ϣ
};

enum PUSHLOAD_TYPE
{
	PUSHLOAD_TRI,   //������
	PUSHLOAD_RECT,//����
	PUSHLOAD_PARA,	 //������
	PUSHLOAD_MODE,//ģ̬
	PUSHLOAD_LC,	 //���ع���
};

struct PUSH_TRI
{
	float fAngle;			//���ýǶ�
	float fShearRatio;	//���׼�����
};
struct PUSH_MODE
{
	int nMode;			//ģ̬����
	float fAmp; //�Ŵ���
};
struct PUSH_LC
{
	int nStload;			//�������ع���id
	float fAmp;			//�Ŵ���
};

class CPushLoad
{
public:
	CPushLoad();
	CPushLoad(CPushLoad &push) {*this=push;}
	~CPushLoad(){;}
public:

	PUSHLOAD_TYPE iType;	//����ģʽ
	union
	{
		PUSH_TRI TriLoad;
		PUSH_TRI RectLoad;
		PUSH_TRI ExpLoad;
		PUSH_MODE ModeLoad;
		PUSH_LC LcLoad;
	};
public:
	CPushLoad & operator=(const CPushLoad &push);
	BOOL  operator==(const CPushLoad &push);
	void Read(CASCFile &fin); 
	void Write(CFile &fout);
	void Write2020(CFile &fout);
};

class CMultiPtExcited
{
public:
	CMultiPtExcited();
	CMultiPtExcited(CMultiPtExcited &multipt) {*this=multipt;}
	~CMultiPtExcited(){;}
public:
	float fAngle;//�����Ƕ�
	float fVelo;//�Ӳ���
public:
	CMultiPtExcited & operator=(const CMultiPtExcited &multipt);
	BOOL  operator==(const CMultiPtExcited &multipt);
	void Read(CASCFile &fin); 
	void Write(CFile &fout);
	void Write2020(CFile &fout);
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
	char m_iCaseType; //��������
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
	int iLinkCons;  //һ�����ӱ���ģ��,0���ԡ�1�������ˡ�2-���ܻ����
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
	float fDynaTime;//ʱ��������ʱ�������������Լ���ʱ�������𶯡���㼤������
	float fVarLoadAmpCoef;//���������Ժ��طŴ�ϵ��
	BOOL m_bOverallDefect;
	BOOL m_bMemberDefect;	
	float fStaticExpTime;//��ʼ�������Ƿ�����ʱ�� �� bStaticExp ��bStaticResult ��Ӧ
	BOOL bInitAnaly;//�Ƿ���г�ʼ�������羲��������ֱ��������ص����
	float fHorzEarthquakeCoef;//ˮƽ����ϵ�� ��ʱ���� 2021��1��7��
	float fVertEarthquakeCoef;//�������ϵ�� ��ʱ���� 2021��1��7��
	int iVarLoadFunc;			//ʱ����غ���id
	int iDynaCase; // �������ع�����ţ���ǰ�汾������ʱ����أ�ֻ�ж�㼤����
	BOOL bAllNode; //�Ƿ�ȫ¥���нڵ������ֹ
	int iControlNode;	//λ�����ýڵ���
	int iNodeDof;			//DX-0 DY-1 DZ-2 3-ȫ��
	float fStopDisp;		//���λ��
	BOOL bRelativeVelo;//�Ƿ��������ٶȼ���������
	int iRelativeNode;//����ٶȼ���ο���
	//
	CPushLoad cPushLoad;//�����Ƹ�����
	CEarthQuake cEarchQuake;  //������Ϣ
	CMultiPtExcited cMultiPt;//��㼤������

	vector<CombData> vConLoadComb;
	vector<CombData> vVarLoadComb;

	CLoadCase& operator=(const CLoadCase& lc);
	BOOL operator==(const CLoadCase& lc);//ISO��������ã���2018��3��6��
	BOOL isIsoParaEqual(const CLoadCase& lc);//ISO��������ã��жϹ��������Ƿ�ı� ��2018��3��6�� ������������Ϣ�͹�����

	BOOL isElasticPlasticPair(const CLoadCase&);

	void Read10(CASCFile &fin);
	void Read20(CASCFile &fin);
	void Read(CASCFile &fin);
	void Write(CFile &fout);
	void Write2020(CFile &fout);

	float GetProgress();
	void SetLoadCoef(int iComb);
	float GetStep(BOOL bNoIso =FALSE);
	//�Զ�ʩ��1��+0.5��
	void AutoAddGravity();
	//ֱ�ӷ�������Ƿ��е���
	BOOL bSeismic();
	//ֻ����ƹ�����0����1��2���� 
	int GetLoadCaseType();
	//�Ƿ���1D+0.5L
	BOOL bAutoAddGravity();
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
	void WriteAnnotation(int iType, CFile &fout);
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

enum HISTYPE
{
	HIS_FROMFILE,		//�ļ���ȡ
	HIS_USER,		//�û�����
	HIS_SINE,		//��������
	HIS_COSINE,	//��������
	HIS_STEP,		//���к���
	HIS_RAMP		//б��
	
};

struct FUN_SINE
{
	float fT;
	int nPoint;
	int nCycles;
	float fAmp;
};

struct FUN_STEP{
	float fG;
	float fs;
	float fInter;
	int nCycles;
	int nOrder;
	int nPeople;
	int iMoveType;
	int iCoord;
	int iStyle;
	
};

struct FUN_FILE
{
	char sFile[MAX_PATH]; 
	int iFirstLine;
	int iLastLine;
	int nPtPerLine;
	int iFormat;//0-ʱ�����ֵ 1�ȼ��
	float	fDtime;
};



class _SSG_DLLIMPEXP CTimeFunction
{
public:
	CTimeFunction(void)
	{
		sName = L"";
		iFuncType = 0;
		iHisType = HIS_USER;
		iScale = 0;
		fScale = 0;
		nPoints = 0;
		pData = NULL;
	}
	CTimeFunction(const CTimeFunction &func) {pData=NULL;*this=func;}
	CTimeFunction(int iHisType);
	~CTimeFunction(){Clear();}

	CString sName;
	int iFuncType; //0 ʱ�� 1 ��Ӧ��
	HISTYPE iHisType;
	union
	{
		FUN_SINE cSine;
		FUN_STEP cStep;
		FUN_FILE cFile;
	}cData;
	//����
	int iScale;
	float fScale;
	float fAmp;
	//�洢����
	int nPoints;  //���ݵ���
	DATA_SEQUENCE2	*pData;

	//����Ϊ��ʱ����
	float fMinValue,fMaxValue;  //�����Сֵ
	float fMinValueTime,fMaxValueTime;  //�����Сֵʱ��
	float fStartTime;//��ʼʱ��
	float fEndTime;  //��ֹʱ��

	void Clear(void) 
	{
		sName = L"";
		iFuncType = 0;
		iHisType = HIS_USER;
		iScale = 0;
		fScale = 0;
		fAmp = 0;
		if (pData)
		{
			delete[] pData;	
			pData=NULL;
		}
		nPoints=0;
	}
	BOOL IsValid(){return nPoints>0 && pData;}

	//��ֵ���������
	CTimeFunction & operator=(const CTimeFunction& data)
	{
		if(this==&data) return *this;
		Clear();
		sName = data.sName;
		iFuncType = data.iFuncType; 
		iHisType = data.iHisType; 
		iScale = data.iScale ;
		fScale = data.fScale ;
		fAmp = data.fAmp;
		nPoints = data.nPoints; 
		pData=new DATA_SEQUENCE2[nPoints];
		ASSERT(pData);
		for(int i=0; i<nPoints; i++)
		{
			pData[i] = data.pData[i]; 
		}
		if(iHisType != HIS_USER)
			cData = data.cData;
		fMinValue = data.fMinValue;
		fMaxValue = data.fMaxValue;
		fMinValueTime = data.fMinValueTime;
		fMaxValueTime = data.fMaxValueTime;
		fStartTime = data.fStartTime;
		fEndTime = data.fEndTime;

		return *this;
	}
	BOOL  operator==(const CTimeFunction &func);
	void GetFuncData();
	void GetShowData(float *pTime,float *pVal);
	float inline GetFuncTime(){return fEndTime - fStartTime;}
	void GetEqualStepData(unsigned int &nPts, float *&pVal, float fStep=0.01f);
	void IntegralData(const unsigned int nPts, float *&pVal, float fStep=0.01f);
	void ConvertToUser();

	void Read(CASCFile &fin);
	void Write(CFile &fout);
};

class _SSG_DLLIMPEXP CFunctionCollection
{
public:
	CFunctionCollection(){;}
	CFunctionCollection(const CFunctionCollection &funcs) 
	{
		*this=funcs;
	};
	~CFunctionCollection(){RemoveAll();}

	int Append(CTimeFunction *func);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return afuncPtr.GetCount();}

	CTimeFunction *GetAt(int i) {return afuncPtr.GetAt(i);}

	CTimeFunction *operator[](int i) {return afuncPtr[i];}

	void SetAt(int i,CTimeFunction *func) {afuncPtr[i]=func;}

	CFunctionCollection& operator=(const CFunctionCollection&funcs);

	void Write(CFile &fout) 
	{
		for(int i=0;i<afuncPtr.GetCount();i++)
			afuncPtr[i]->Write(fout);
	}

private:
	CArray<CTimeFunction*,CTimeFunction*> afuncPtr;
};
