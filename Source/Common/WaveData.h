#pragma once
#include <vector>
#include <string>
#include <map>
//#include <unordered_map>
#include <sstream>
#include <utility>
#include <algorithm>
#include <valarray>
#include <iostream>
#include <fstream>
#include <iterator>
#include <functional> 
#include <cctype>

//#include <boost/algorithm/string.hpp>
//#include <boost/regex.hpp> 
//#include <boost/lexical_cast.hpp>
#include <regex>
#include <locale> 

//说明
//当初应该将地震波都导入到Access数据库中，然后再进行操作。
//这项工作以后再做

#ifdef _UNICODE
typedef std::wstring _tstring;
#else
typedef std::string _tstring;
#endif


//const long g_idWaveLib = 20170921;//20150501;	//<-- 修改为新的格式
const int  g_iVersion = 11;

const int g_iComp = 3;		//分量个数 <--- 原来为2 现改为 3
const int g_iTGS = 10;

const int g_charlen = 256;

const float AlphaData[3][6] =
{
	{ 0.04f, 0.08f, 0.12f, 0.16f, 0.24f, 0.32f},		// 小震
	{ 0.12f, 0.23f, 0.34f, 0.45f, 0.68f, 0.90f},		// 中震
	{ 0.28f, 0.50f, 0.72f, 0.90f, 1.20f, 1.40f}			// 大震
};

const float AccData[3][6] =
{
	{ 0.18f, 0.35f, 0.55f, 0.70f, 1.10f, 1.40f},		// 小震
	{ 0.50f, 1.00f, 1.50f, 2.00f, 3.00f, 4.00f},		// 中震
	{ 1.25f, 2.20f, 3.10f, 4.00f, 5.10f, 6.20f}			// 大震
};

const float TgData[3][5] =
{
	{ 0.20f, 0.25f, 0.35f, 0.45f, 0.65f},			// 第一组
	{ 0.25f, 0.30f, 0.40f, 0.55f, 0.75f},			// 第二组
	{ 0.30f, 0.35f, 0.45f, 0.65f, 0.90f}			// 第三组
};


//波库文件头
struct S_WaveHeader {
	S_WaveHeader() { uid = 0; iVersion = g_iVersion; iNum = 0; posRSP = 0l; iLengthRSP = 0;}
	long uid;			//global identifier
	int  iVersion;		//版本号
	int  iNum;			//波库地震波数目
	long iNumRSP;		//谱点数

	long posRSP;		//谱数据起始位置,以便一起读入		//这部分没用
	int  iLengthRSP;	//谱数据存储后长度					//这部分没用
};

//波库数据结构信息
struct S_WaveIndex {
	S_WaveIndex() { 
		status=0; dt = 0.0f; iYear=0; iMonth=0; 
		iDay = 0; 
		memset(sName, 0, g_charlen);
		memset(sStation, 0, g_charlen);
		memset(sFileName, 0, g_charlen);
		for(int i=0;i<g_iComp;i++)
			memset(sComponent[i], 0, g_charlen);
	}

	int   idx;						//地震波id
	int   status;					//状态 0-正常 1-删除  暂时没用
	char  sName[g_charlen];			//地震波名
	int	  iYear;					//年
	int   iMonth;					//月
	int   iDay;						//日
	char  sStation[g_charlen];		//测站名

	int	  type;								//人工波还是天然波 0-天然波 1-人工波
	int	  tag1;
	float tag2;

	int   nNumComp;					//分量数
	char  sComponent[g_iComp][g_charlen];	//分量
	char  sFileName[g_charlen];			//文件名 调试时候用

	float dt;						//时间间隔
	float accMax[g_iComp];			//加速度峰值

	float Tg[g_iComp];				//场地特征周期

	int	  iNumAcc[g_iComp];			//加速度点数
	int   iNumRSP;					//谱的点数, 冗余 但是可以直接读取每个数据不用读取整体

	long  iStartPos;				//数据开始位置
	int   iLenData;					//存储数据的压缩后长度

	//数据:
	// i:=1 to nNumComp { 加速度序列 }
	// 谱时间序列
	// i:=1 to iNumRSP { 谱加速度序列、谱速度序列、谱位移序列 }
};

//struct S_Acc
//{
//	float t;
//	float acc;
//};

//需要解决
//谱统一单独存   算 Tg
struct S_SpectrumOne {
	int idx;	//波库中序号
	//	std::vector<float> m_vecTn;
	float Tg;

	//	std::vector<float> m_vecTn;						//频域采样点周期数组(秒)

	std::vector<std::vector<float>> vecRSPAcc;	//频域采样点最大加速度数组  分量
	std::vector<std::vector<float>> vecRSPVel;
	std::vector<std::vector<float>> vecRSPDisp;

	//void SetTn(std::vector<float> vecTn) {	//设置采样点序列
	//	m_vecTn = vecTn;
	//}
	//float GetSpectrumAcc(int iComp, float fTerm);
	//float GetSpectrumVel(int iComp, float fTerm);
	//float GetSpectrumDisp(int iComp, float fTerm);
};

//形成地震波库所用数据
//单分量
struct WaveDataOne {
	WaveDataOne() : iYear(-1), iMonth(-1), iDay(-1) {}

	int idx;
	std::string sName;	//地震名
	int	iYear;
	int iMonth;
	int iDay;
	//int iHour;
	//int iMinute;
	std::string sStation;
	std::string sFileName;
	std::string sComponent;

	float dt;
	int iNumAcc;	//加速度点数
	std::vector<float> vecAcc;
	//	int iNumRSP;	//谱点数
};

typedef int (__stdcall *DLL_fnReadHeader)(const wchar_t* filename, S_WaveHeader& waveHeader, std::vector<S_WaveIndex>& vecWaveIndex, std::vector<float>& vecTn);
typedef int (__stdcall *DLL_fnReadAccFromLib)(int idxWave, std::vector<std::vector<float>>& vecTime, std::vector<std::vector<float>>& vecAcc);
typedef int (__stdcall *DLL_fnReadSpectrumFromLib)(int idxWave, S_SpectrumOne& specOne);
typedef int (__stdcall *DLL_fnSelectEarthquake)(int, float, int, int, int, const char* , float , float , float , std::vector<int>& , std::vector<int>& );
typedef int (__stdcall *DLL_fnWriteWaveLib)(std::vector<WaveDataOne> &vecData, const wchar_t *filename);
typedef int (__stdcall *DLL_fnDeleteWave)(const wchar_t* libname, std::vector<int>& vecIdx);
typedef int (__stdcall *DLL_fnAppendWave)(const wchar_t* libname, float dt, const char* sname, std::vector<std::vector<float>>& vecAcc);


typedef int (__stdcall *DLL_SelectEarthquake)(int code, int iScale, float fDamp, int iSI, int iGroup, int iSite, 
	const char* path, const char* title, 
	float fBetaMin, float fBetaMax, float fLambdaMin, float fLambdaMax, 
	std::vector<float> vecEtaMin, std::vector<float> vecEtaMax, 
	std::vector<float> vecPeriod, 
	int nOpt1, int nOpt2, std::vector<int> vecOption,
	std::vector<std::vector<int>>& vecSelectedCombo);