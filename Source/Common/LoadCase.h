
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



//数据系列类，2个分量
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

	CString fname; //文件名
	int iWaveLibIndex; //乔保娟 2015.6.11
	int iWaveLib;	//0----SSG地震波库， 1-----用户自定义波
	int nPoints;  //数据点数

	//以下为临时数据
	float fMinValue,fMaxValue;  //最大最小值，读入文件时统计得到
	float fMinValueTime,fMaxValueTime;  //最大最小值时刻，读入文件时统计得到 //2016.3.16
	float fMaxFileTime;  //数据文件中的最大时间

	DATA_SEQUENCE2	*pData;

	void Clear(void) 
	{
		if (pData){delete[] pData;	pData=NULL;}

		nPoints=0;
		//fMinValue=fMaxValue=0;
		//fname=L"";
	}
	BOOL IsValid(){return nPoints>0 && pData;}

	//赋值运算符重载
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

	//2017版本功能
	void ReadAcc2017(void); //只读取数据nPoints，pData

};

//地震荷载的一个工况数据
class _SSG_DLLIMPEXP CEarthQuake
{
public:
	CEarthQuake(void);
	CEarthQuake(CEarthQuake &eq) {*this=eq;}
	~CEarthQuake(){;}

	int iEarthQuakeProbility;
	int iAccDefineMethod;
	float fMainAmpEffect,f2ndAmpEffect,f3rdAmpEffect;  //有效峰值主方向加速度峰值，次方向峰值加速度，垂直方向峰值加速度 
	float fMainAmp,f2ndAmp,f3rdAmp; // 实际峰值主方向加速度峰值，次方向峰值加速度，垂直方向峰值加速度
	float fTimeInterval;	//数据点时间间隔
	float fStartComputeTime;//时程分析起始时间
	float fEndComputeTime;  //时程分析终止时间
	float fMaxFileTime;		//数据最大时间=max(X-文件最大时间, Y-文件最大时间, Z-文件最大时间)
	int iMainDir;			//主方向，0--X，1--Y


	CDataSequence2 cAX,cAY,cAZ;  //保存文件中的原值

	void GetRatio(float &fRatioX,float &fRatioY,float &fRatioZ);  //根据fMainAmp,fRatio1,fRatio2计算fRatioX,fRatioY,fRatioZ
	void ReadData();  //读取三个方向的地震波数据
	int CreateData(float *&ax,float *&ay,float *&az);  //创建数组，插值计算当前组的所有地震荷载点
	void  GetRealPeakAccValue(); //求fMainAmp
	CEarthQuake & operator=(const CEarthQuake &eq);
	BOOL  operator==(const CEarthQuake &eq);//邱海 2018年3月2日

	void Read10(CASCFile &fin);  //只读取配置信息，数据系列在使用时读取
	void Read(CASCFile &fin);  //只读取配置信息，数据系列在使用时读取
	void Write(CFile &fout); //只保存配置信息
	void Write2020(CFile &fout); //只保存配置信息
};

enum PUSHLOAD_TYPE
{
	PUSHLOAD_TRI,   //倒三角
	PUSHLOAD_RECT,//矩形
	PUSHLOAD_PARA,	 //抛物线
	PUSHLOAD_MODE,//模态
	PUSHLOAD_LC,	 //荷载工况
};

struct PUSH_TRI
{
	float fAngle;			//作用角度
	float fShearRatio;	//基底剪力比
};
struct PUSH_MODE
{
	int nMode;			//模态阶数
	float fAmp; //放大倍数
};
struct PUSH_LC
{
	int nStload;			//静力荷载工况id
	float fAmp;			//放大倍数
};

class CPushLoad
{
public:
	CPushLoad();
	CPushLoad(CPushLoad &push) {*this=push;}
	~CPushLoad(){;}
public:

	PUSHLOAD_TYPE iType;	//荷载模式
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
	float fAngle;//传播角度
	float fVelo;//视波速
public:
	CMultiPtExcited & operator=(const CMultiPtExcited &multipt);
	BOOL  operator==(const CMultiPtExcited &multipt);
	void Read(CASCFile &fin); 
	void Write(CFile &fout);
	void Write2020(CFile &fout);
};


class CLoadCase;

//工况组合
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

	CString sCaseName;  //工况组合名称
	CString sMemo;  //说明
	char m_iCaseType; //分析类型
 	int iLoadComb;		//荷载组合

	//显式动力加载参数
	BOOL  bCloseNonLinear; //是否关闭几何非线性，1-关闭
	BOOL  bCalIsolatorBeta; 
	float fMassDamp;	//质量阻尼系数，
	float fStiffDamp; //刚度阻尼系数
	float fTerm1;  	//振型周期1
	float fTerm2;  	//振型周期2
	float fKsi1;   	//振型阻尼比1
	float fKsi2;   	//振型阻尼比2
	BOOL bInputAlpha;	//是否直接输入 //ver32
	float fTimeStep;  //加载时间步长
	int iCrtCons;  //混凝土二维本构模型,0弹性、1塑性损伤、2-性能化设计
	int iLinkCons;  //一般连接本构模型,0弹性、1塑性损伤、2-性能化设计
	int	iStirrupCons;  //箍筋本构类型，取值为0--弹性、1--规范模型、2---约束混凝土模型
	int iSlabElastic; //是否考虑楼板弹性
	int m_bShearNonLinear; //是否考虑剪切非线性
	float fShearGama; //剪切屈服应变
	float fShearRatio; //剪切屈服后刚度比
	float fWallShear; //剪力墙分布钢筋抗剪调整系数
	int	iDamage;  //损伤定义方式
	int	iMethod;  //分析方法

	float fWaveAngle; //地震波主方向与坐标系夹角
	BOOL bStiffDamp;  //是否计入刚度阻尼
	int	iDampType;  //阻尼类型，0-Rayleigh阻尼，1-振型阻尼
	int nModeNum;  //振型个数，用于计算振型阻尼，m_iDampType=1时有效
	int iModalDampType;  //振型阻尼类型，0-全楼统一，1-按材料区分
	int iSimpleModalDamp;  //简化振型阻尼
	float fModeDamp[Sys_MaxModeNum];  //对应于m_iModeNum的各个振型的阻尼比，m_iDampType=1时有效
	float fModeDampSteel[Sys_MaxModeNum];  //对应于m_iModeNum的各个振型的阻尼比，m_iDampType=1时有效//2017.8.26
	int m_iIsoBndType;		//0-隔振支座上端三个平动位移、三个转动位移都固定，1-隔振支座上端三个平动位移固定，三个转动位移释放
	BOOL m_bConcRatioEffect;
	BOOL m_bSteelRatioEffect;
	BOOL m_bRebarBuckling;

	BOOL bStaticExp;	//采用显式分析进行竖向荷载加载 1-是，0-否
	BOOL bStaticResult;
	float fDynaTime;//时变力加载时长：静力非线性加载时长、地震动、多点激励共用
	float fVarLoadAmpCoef;//静力非线性荷载放大系数
	BOOL m_bOverallDefect;
	BOOL m_bMemberDefect;	
	float fStaticExpTime;//初始分析考虑非线性时长 与 bStaticExp 及bStaticResult 对应
	BOOL bInitAnaly;//是否进行初始分析：如静力非线性直接竖向加载的情况
	float fHorzEarthquakeCoef;//水平地震系数 暂时不用 2021年1月7日
	float fVertEarthquakeCoef;//竖向地震系数 暂时不用 2021年1月7日
	int iVarLoadFunc;			//时变荷载函数id
	int iDynaCase; // 动力荷载工况编号（当前版本不包括时变荷载，只有多点激励）
	BOOL bAllNode; //是否按全楼所有节点控制终止
	int iControlNode;	//位移作用节点编号
	int iNodeDof;			//DX-0 DY-1 DZ-2 3-全量
	float fStopDisp;		//最大位移
	BOOL bRelativeVelo;//是否采用相对速度计算阻尼力
	int iRelativeNode;//相对速度计算参考点
	//
	CPushLoad cPushLoad;//静力推覆荷载
	CEarthQuake cEarchQuake;  //地震波信息
	CMultiPtExcited cMultiPt;//多点激励荷载

	vector<CombData> vConLoadComb;
	vector<CombData> vVarLoadComb;

	CLoadCase& operator=(const CLoadCase& lc);
	BOOL operator==(const CLoadCase& lc);//ISO中震设计用，邱海2018年3月6日
	BOOL isIsoParaEqual(const CLoadCase& lc);//ISO中震设计用，判断工况参数是否改变 邱海2018年3月6日 不包括地震动信息和工况名

	BOOL isElasticPlasticPair(const CLoadCase&);

	void Read10(CASCFile &fin);
	void Read20(CASCFile &fin);
	void Read(CASCFile &fin);
	void Write(CFile &fout);
	void Write2020(CFile &fout);

	float GetProgress();
	void SetLoadCoef(int iComb);
	float GetStep(BOOL bNoIso =FALSE);
	//自动施加1恒+0.5活
	void AutoAddGravity();
	//直接分析设计是否有地震
	BOOL bSeismic();
	//只有设计工况用0静力1风2地震 
	int GetLoadCaseType();
	//是否是1D+0.5L
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
	CArray<CLoadCase*,CLoadCase*> aLoadCasePtr; //荷载工况组合集合
	CString sOutputFile;
};

//已选地震动
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
	CArray<CEarthQuake*,CEarthQuake*> awavePtr; //荷载工况组合集合
};

enum HISTYPE
{
	HIS_FROMFILE,		//文件读取
	HIS_USER,		//用户定义
	HIS_SINE,		//正弦曲线
	HIS_COSINE,	//余弦曲线
	HIS_STEP,		//步行荷载
	HIS_RAMP		//斜坡
	
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
	int iFormat;//0-时间和数值 1等间距
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
	int iFuncType; //0 时程 1 反应谱
	HISTYPE iHisType;
	union
	{
		FUN_SINE cSine;
		FUN_STEP cStep;
		FUN_FILE cFile;
	}cData;
	//缩放
	int iScale;
	float fScale;
	float fAmp;
	//存储数据
	int nPoints;  //数据点数
	DATA_SEQUENCE2	*pData;

	//以下为临时数据
	float fMinValue,fMaxValue;  //最大最小值
	float fMinValueTime,fMaxValueTime;  //最大最小值时刻
	float fStartTime;//起始时间
	float fEndTime;  //终止时间

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

	//赋值运算符重载
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
