
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
	int iRebarCons;  //钢筋本构模型,0弹性、1弹塑性、2-性能化设计
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
	float fStaticTime;//静力非线性加载时长
	float fStaticAmpCoef;//静力非线性荷载放大系数
	BOOL m_bOverallDefect;
	BOOL m_bMemberDefect;	
	float m_fConLoadCoef[Sys_MaxLoadcase]; //不变荷载组合系数
	float m_fVarLoadCoef[Sys_MaxLoadcase]; //可变荷载组合
	float fStaticExpTime;//初始分析考虑非线性时长 与 bStaticExp 及bStaticResult 对应
	BOOL bInitAnaly;//是否进行初始分析：如静力非线性直接竖向加载的情况

	CEarthQuake cEarchQuake;  //地震波信息



	CLoadCase& operator=(const CLoadCase& lc);
	BOOL operator==(const CLoadCase& lc);//ISO中震设计用，邱海2018年3月6日
	BOOL isIsoParaEqual(const CLoadCase& lc);//ISO中震设计用，判断工况参数是否改变 邱海2018年3月6日 不包括地震动信息和工况名

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
