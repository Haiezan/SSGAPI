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
const int g_iTGS = 66;
//const std::string Tgs[] = {"0.20", "0.25", "0.30", 

const std::string g_Tgs[]={
	"0.20", "0.25", "0.30", "0.35", "0.40", "0.45", "0.55", "0.65", "0.75", "0.90", "1.10", 
	"GD-I-0.20-T=0.20-0.50", "GD-I-0.20-T=0.50-3.00", "GD-I-0.20-T=3.00-6.00", "GD-I-0.20-T=6.00-10.0",
	"GD-I-0.25-T=0.25-0.75", "GD-I-0.25-T=0.75-3.00", "GD-I-0.25-T=3.00-6.00", "GD-I-0.25-T=6.00-10.0",
	"GD-I-0.35-T=0.35-1.25", "GD-I-0.35-T=1.25-3.00", "GD-I-0.35-T=3.00-6.00", "GD-I-0.35-T=6.00-10.0",
	"GD-I-0.50-T=0.50-1.50", "GD-I-0.50-T=1.50-3.00", "GD-I-0.50-T=3.00-6.00", "GD-I-0.50-T=6.00-10.0",

	"GD-II-0.35-T=0.35-1.25", "GD-II-0.35-T=1.25-3.00", "GD-II-0.35-T=3.00-6.00", "GD-II-0.35-T=6.00-10.0",
	"GD-II-0.50-T=0.50-1.50", "GD-II-0.50-T=1.50-3.00", "GD-II-0.50-T=3.00-6.00", "GD-II-0.50-T=6.00-10.0",
	"GD-II-0.70-T=0.70-1.50", "GD-II-0.70-T=1.50-3.00", "GD-II-0.70-T=3.00-6.00", "GD-II-0.70-T=6.00-10.0",

	"GD-III-0.45-T=0.45-1.50", "GD-III-0.45-T=1.50-3.00", "GD-III-0.45-T=3.00-6.00", "GD-III-0.45-T=6.00-10.0",
	"GD-III-0.65-T=0.65-1.50", "GD-III-0.50-T=1.50-3.00", "GD-III-0.50-T=3.00-6.00", "GD-III-0.50-T=6.00-10.0",
	"GD-III-0.90-T=0.90-1.50", "GD-III-0.50-T=1.50-3.00", "GD-III-0.50-T=3.00-6.00", "GD-III-0.50-T=6.00-10.0",

	"GD-IV-0.65-T=0.65-1.50", "GD-IV-0.65-T=1.50-3.00", "GD-IV-0.65-T=3.00-6.00", "GD-IV-0.65-T=6.00-10.0",
	"GD-IV-0.85-T=0.85-1.50", "GD-IV-0.85-T=1.50-3.00", "GD-IV-0.85-T=3.00-6.00", "GD-IV-0.85-T=6.00-10.0",
	"GD-IV-1.05-T=1.05-1.50", "GD-IV-1.05-T=1.50-3.00", "GD-IV-1.05-T=3.00-6.00", "GD-IV-1.05-T=6.00-10.0",
	"BeiJing-DB11_2075-2022",
	"ShangHai-DGTJ08-9-2023",
	"SiChuan-2023",
};

const int g_charlen = 256;

//地震影响系数最大值
const float AlphaData[3][6] = //国标
{
	{ 0.04f, 0.08f, 0.12f, 0.16f, 0.24f, 0.32f},		// 小震
	{ 0.12f, 0.23f, 0.34f, 0.45f, 0.68f, 0.90f},		// 中震
	{ 0.28f, 0.50f, 0.72f, 0.90f, 1.20f, 1.40f}			// 大震
};
const float AlphaData_GuangDong[5][3][6] = //广东性能化标准
{
	//I0 类场地土                       //规范无相应数据按照国标取值
	{
		{0.04f, 0.07f, 0.11f, 0.14f,    0.24f, 0.32f},		// 小震
		{0.11f, 0.20f, 0.31f, 0.41f,    0.68f, 0.90f},		// 中震
		{0.26f, 0.45f, 0.63f, 0.82f,    1.20f, 1.40f},		// 大震
	},
	//I1 类场地土 同上
	{
		{0.04f, 0.07f, 0.11f, 0.14f,    0.24f, 0.32f},		// 小震
		{0.11f, 0.20f, 0.31f, 0.41f,    0.68f, 0.90f},		// 中震
		{0.26f, 0.45f, 0.63f, 0.82f,    1.20f, 1.40f},		// 大震
	},
	//II类场地土
	{
		{0.04f, 0.08f, 0.12f, 0.16f,    0.24f, 0.32f},		// 小震
		{0.12f, 0.23f, 0.34f, 0.45f,    0.68f, 0.90f},		// 中震
		{0.28f, 0.50f, 0.72f, 0.90f,    1.20f, 1.40f},		// 大震.
	},
	//III类场地土
	{
		{0.05f, 0.09f, 0.14f, 0.18f,    0.24f, 0.32f},		// 小震
		{0.13f, 0.26f, 0.38f, 0.51f,    0.68f, 0.90f},		// 中震
		{0.32f, 0.56f, 0.79f, 1.02f,    1.20f, 1.40f},		// 大震
	},
	//IV类场地土 同上
	{
		{0.05f, 0.10f, 0.15f, 0.20f,    0.24f, 0.32f},		// 小震
		{0.14f, 0.28f, 0.42f, 0.56f,    0.68f, 0.90f},		// 中震
		{0.35f, 0.62f, 0.87f, 1.12f,    1.20f, 1.40f},		// 大震
	}
};
const float AlphaData_ISO[4][6] = //隔标
{
		{ 0.04f, 0.08f, 0.12f, 0.16f, 0.24f, 0.32f},		// 小震
		{ 0.12f, 0.23f, 0.34f, 0.45f, 0.68f, 0.90f},		// 中震
		{ 0.28f, 0.50f, 0.72f, 0.90f, 1.20f, 1.40f},		// 大震
		{ 0.36f, 0.72f, 1.00f, 1.35f, 2.00f, 2.43f}			// 极大震
};
const float AlphaData_GD[5][2][6] = //广东高规
{
	//I0 类场地土 
	{
		{0.11f, 0.20f, 0.30f, 0.40f, 0.60, 0.80},		// 中震
		{0.25f, 0.45f, 0.65f, 0.80f, 1.08, 1.26},		// 大震
	},
	//I1 类场地土 同上
	{
		{0.11f, 0.20f, 0.30f, 0.40f, 0.60, 0.80},		// 中震
		{0.25f, 0.45f, 0.65f, 0.80f, 1.08, 1.26},		// 大震
	},
	//II类场地土
	{
		{0.12f, 0.23f, 0.34f, 0.45f, 0.68, 0.90},		// 中震
		{0.28f, 0.50f, 0.72f, 0.90f, 1.20, 1.40},		// 大震
	},
	//III类场地土
	{
		{0.13f, 0.25f, 0.37f, 0.50f, 0.75, 1.00},		// 中震
		{0.31f, 0.55f, 0.79f, 1.00f, 1.32, 1.54},		// 大震
	},
	//IV类场地土 同上
	{
		{0.13f, 0.25f, 0.37f, 0.50f, 0.75, 1.00},		// 中震
		{0.31f, 0.55f, 0.79f, 1.00f, 1.32, 1.54},		// 大震
	},
};
const float AlphaData_SH[3][6] = //上海标
{
	{ 0.04f, 0.08f, 0.08f, 0.16f, 0.16f, 0.16f},		// 小震
	{ 0.12f, 0.23f, 0.23f, 0.45f, 0.45f, 0.45f},		// 中震
	{ 0.26f, 0.45f, 0.45f, 0.81f, 0.81f, 0.81f}			// 大震
};

//峰值加速度
const float AccData[3][6] = //国标
{
	{ 0.18f, 0.35f, 0.55f, 0.70f, 1.10f, 1.40f},		// 小震
	{ 0.50f, 1.00f, 1.50f, 2.00f, 3.00f, 4.00f},		// 中震
	{ 1.25f, 2.20f, 3.10f, 4.00f, 5.10f, 6.20f}			// 大震
};
const float AccData_GuangDong[3][6] = //广东性能化标准
{
	{ 0.18f, 0.35f, 0.55f, 0.70f,    1.10f, 1.40f},			// 小震
	{ 0.50f, 1.00f, 1.50f, 2.00f,    3.00f, 4.00f},			// 中震
	{ 1.25f, 2.20f, 3.10f, 4.00f,    5.10f, 6.20f}			// 大震
};
const float AccData_ISO[4][6] = //隔标
{
		{ 0.18f, 0.35f, 0.55f, 0.70f, 1.10f, 1.40f},		// 小震
		{ 0.50f, 1.00f, 1.50f, 2.00f, 3.00f, 4.00f},		// 中震
		{ 1.25f, 2.20f, 3.10f, 4.00f, 5.10f, 6.20f},		// 大震
		{ 1.60f, 3.20f, 4.60f, 6.00f, 8.40f, 10.80f}		// 极大震
};
const float AccData_GD[5][2][6] = //广东高规
{
	//I0类场地
	{
		{ 0.45f, 0.90f, 1.35f, 1.80f, 2.70f, 3.60f},		// 中震
		{ 1.13f, 1.98f, 2.79f, 3.60f, 4.59f, 5.58f},		// 大震
	},
	//I1类场地 同上
	{
		{ 0.45f, 0.90f, 1.35f, 1.80f, 2.70f, 3.60f},		// 中震
		{ 1.13f, 1.98f, 2.79f, 3.60f, 4.59f, 5.58f},		// 大震
	},
	//II类场地
	{
		{ 0.50f, 1.00f, 1.50f, 2.00f, 3.00f, 4.00f},		// 中震
		{ 1.25f, 2.20f, 3.10f, 4.00f, 5.10f, 6.20f},		// 大震
	},
	//III类场地
	{
		{ 0.55f, 1.10f, 1.65f, 2.20f, 3.30f, 4.40f},		// 中震
		{ 1.38f, 2.42f, 3.41f, 4.40f, 5.61f, 6.82f},		// 大震
	},
	//IV类场地 同上
	{
		{ 0.55f, 1.10f, 1.65f, 2.20f, 3.30f, 4.40f},		// 中震
		{ 1.38f, 2.42f, 3.41f, 4.40f, 5.61f, 6.82f},		// 大震
	},
};

const float AccData_JG[4][3][6] = //消能减震技术规程
{
	//A类
	{
		{ 0.14f, 0.26f, 0.41f, 0.53f, 0.83f, 1.05f},		// 小震
		{ 0.46f, 0.81f, 1.22f, 1.62f, 2.43f, 3.24f},		// 中震
		{ 1.06f, 1.87f, 2.64f, 3.40f, 4.34f, 5.27f}			// 大震
	},
	//B类
	{
		{ 0.16f, 0.31f, 0.48f, 0.62f, 0.97f, 1.23f},		// 小震
		{ 0.46f, 0.91f, 1.37f, 1.82f, 2.73f, 3.64f},		// 中震
		{ 1.16f, 2.04f, 2.88f, 3.72f, 4.74f, 5.77f}			// 大震
	},
	//旧C类
	{
		{ 0.18f, 0.35f, 0.55f, 0.70f, 1.10f, 1.40f},		// 小震
		{ 0.50f, 1.00f, 1.50f, 2.00f, 3.00f, 4.00f},		// 中震
		{ 1.25f, 2.20f, 3.10f, 4.00f, 5.10f, 6.20f}			// 大震
	},
	//C类
	{
		{ 0.18f, 0.35f, 0.55f, 0.70f, 1.10f, 1.40f},		// 小震
		{ 0.50f, 1.00f, 1.50f, 2.00f, 3.00f, 4.00f},		// 中震
		{ 1.25f, 2.20f, 3.10f, 4.00f, 5.10f, 6.20f}			// 大震
	}
};

const float Acc_JG_Scale[2][3] = { //加固地震作用折减系数
		{ 0.75f, 0.81f, 0.85f},	//A类	 小震 中震 大震
		{ 0.88f, 0.91f, 0.93f}	//B类 	 小震 中震 大震
};

//特征周期
const float TgData[3][5] = //国标
{
	{ 0.20f, 0.25f, 0.35f, 0.45f, 0.65f},			// 第一组
	{ 0.25f, 0.30f, 0.40f, 0.55f, 0.75f},			// 第二组
	{ 0.30f, 0.35f, 0.45f, 0.65f, 0.90f}			// 第三组
};
const float TgData_GuangDong[3][5] = //广东性能化标准
{
	{ 0.20f, 0.25f, 0.35f, 0.45f, 0.65f},			// 第一组
	{ 0.25f, 0.35f, 0.50f, 0.65f, 0.85f},			// 第二组
	{ 0.35f, 0.50f, 0.70f, 0.90f, 1.10f}			// 第三组
};
const float TgData_ISO[3][5] = //隔标 Tg 与抗规一样
{
	{ 0.20f, 0.25f, 0.35f, 0.45f, 0.65f},			// 第一组
	{ 0.25f, 0.30f, 0.40f, 0.55f, 0.75f},			// 第二组
	{ 0.30f, 0.35f, 0.45f, 0.65f, 0.90f}			// 第三组
};
const float TgData_GD[3][5] = //广东高规
{
	{ 0.20f, 0.25f, 0.35f, 0.45f, 0.65f},			// 第一组
	{ 0.25f, 0.35f, 0.50f, 0.65f, 0.85f},			// 第二组
	{ 0.35f, 0.50f, 0.70f, 0.90f, 1.10f}			// 第三组
};
const float TgData_SH[3][5] = //上海标准
{
	{ 0.65f, 0.65f, 0.65f, 0.65f, 0.90f},			// 小震
	{ 0.65f, 0.65f, 0.65f, 0.65f, 0.90f},		// 中震
	{ 1.10f, 1.10f, 1.10f, 1.10f, 1.10f}			// 大震
};
//const float Betamax_GuangDong[5] =
//{
//	2.00f, 2.00f, 2.25f, 2.50f, 2.75f			// 第一组
//};

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
//typedef int (__stdcall *DLL_fnSelectEarthquake)(int, float, int, int, int, const char* , float , float , float , std::vector<int>& , std::vector<int>& );
//typedef int (__stdcall *DLL_fnWriteWaveLib)(std::vector<WaveDataOne> &vecData, const wchar_t *filename);
typedef int (__stdcall *DLL_fnDeleteWave)(const wchar_t* libname, std::vector<int>& vecIdx);
typedef int (__stdcall *DLL_fnAppendWave)(const wchar_t* libname, float dt, const char* sname, std::vector<std::vector<float>>& vecAcc);
typedef int(__stdcall* DLL_fnAppendWave1)(const wchar_t* libname, int itype, float dt, const char* sname, std::vector<std::vector<float>>& vecAcc);

//typedef int (__stdcall *DLL_SelectEarthquake)(int code, int iScale, float fDamp, int iSI, int iGroup, int iSite, 
//	const char* path, const char* title, 
//	float fBetaMin, float fBetaMax, float fLambdaMin, float fLambdaMax, 
//	std::vector<float> vecEtaMin, std::vector<float> vecEtaMax, 
//	std::vector<float> vecPeriod, 
//	int nOpt1, int nOpt2, std::vector<int> vecOption,
//	std::vector<std::vector<int>>& vecSelectedCombo);