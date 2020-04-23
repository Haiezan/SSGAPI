//#pragma once
//#include "HeadDefine.h"
//
//#include <vector>
//#include <string>
//#include <map>
//#include <sstream>
//#include <utility>
//#include <algorithm>
//#include <valarray>
//#include <iostream>
//#include <fstream>
//#include <iterator>
//#include <functional> 
//#include <cctype>
//
////#include <boost/algorithm/string.hpp>
////#include <boost/regex.hpp> 
////#include <boost/lexical_cast.hpp>
//#include <regex>
//#include <locale> 
//
//
////说明
////当初应该将地震波都导入到Access数据库中，然后再进行操作。
////这项工作以后再做
//
////#ifdef _UNICODE
////typedef std::wstring _mstring;
////#else
////typedef std::string _mstring;
////#endif
//
//const float AlphaData[3][6] =
//{
//	{ 0.04f, 0.08f, 0.12f, 0.16f, 0.24f, 0.32f},		// 小震
//	{ 0.12f, 0.23f, 0.34f, 0.45f, 0.68f, 0.90f},		// 中震
//	{ 0.28f, 0.50f, 0.72f, 0.90f, 1.20f, 1.40f}		// 大震
//};
//
//const float AccData[3][6] =
//{
//	{ 0.18f, 0.35f, 0.55f, 0.70f, 1.10f, 1.40f},		// 小震
//	{ 0.50f, 1.00f, 1.50f, 2.00f, 3.00f, 4.00f},		// 中震
//	{ 1.25f, 2.20f, 3.10f, 4.00f, 5.10f, 6.20f}		// 大震
//};
//
//const float TgData[3][5] =
//{
//	{ 0.20f, 0.25f, 0.35f, 0.45f, 0.65f},		// 第一组
//	{ 0.25f, 0.30f, 0.40f, 0.55f, 0.75f},		// 第二组
//	{ 0.30f, 0.35f, 0.45f, 0.65f, 0.90f}		// 第三组
//};
//
//
//const long g_idWaveLib = 20170921;//20150501;	//<-- 修改为新的格式
//const int  g_iVersion = 11;
//
//const int g_iComp = 3;		//分量个数 <--- 原来为2 现改为 3
//const int g_iTGS = 10;
//
//const int g_charlen = 256;
//
////波库文件头
//struct S_WaveHeader {
//	S_WaveHeader() { uid = 0; iVersion = g_iVersion; iNum = 0; posRSP = 0l; iLengthRSP = 0;}
//	long uid;			//global identifier
//	int  iVersion;		//版本号
//	int  iNum;			//波库地震波数目
//	long iNumRSP;		//谱点数
//
//	long posRSP;		//谱数据起始位置,以便一起读入		//这部分没用
//	int  iLengthRSP;	//谱数据存储后长度					//这部分没用
//};
//
////波库数据结构信息
//struct S_WaveIndex {
//	S_WaveIndex() { 
//		status=0; dt = 0.0f; iYear=0; iMonth=0; 
//		iDay = 0; 
//		memset(sName, 0, g_charlen);
//		memset(sStation, 0, g_charlen);
//		memset(sFileName, 0, g_charlen);
//		for(int i=0;i<g_iComp;i++)
//			memset(sComponent[i], 0, g_charlen);
//	}
//
//	int   idx;						//地震波id
//	int   status;					//状态 0-正常 1-删除  暂时没用
//	char  sName[g_charlen];				//地震波名
//	int	  iYear;					//年
//	int   iMonth;					//月
//	int   iDay;						//日
//	char  sStation[g_charlen];				//测站名
//
//	int   nNumComp;					//分量数
//	char  sComponent[g_iComp][g_charlen];	//分量
//	char  sFileName[g_charlen];			//文件名 调试时候用
//
//	float dt;						//时间间隔
//	float accMax[g_iComp];			//加速度峰值
//
//	float Tg[g_iComp];				//场地特征周期
//
//	int	  iNumAcc[g_iComp];			//加速度点数
//	int   iNumRSP;					//谱的点数, 冗余 但是可以直接读取每个数据不用读取整体
//
//	long  iStartPos;				//数据开始位置
//	int   iLenData;					//存储数据的压缩后长度
//
//	//数据:
//	// i:=1 to nNumComp { 加速度序列 }
//	// 谱时间序列
//	// i:=1 to iNumRSP { 谱加速度序列、谱速度序列、谱位移序列 }
//};
//
////struct S_Acc
////{
////	float t;
////	float acc;
////};
//
////需要解决
////谱统一单独存   算 Tg
//struct S_SpectrumOne {
//	int idx;	//波库中序号
//	//	std::vector<float> m_vecTn;
//	float Tg;
//
//	//	std::vector<float> m_vecTn;						//频域采样点周期数组(秒)
//
//	std::vector<std::vector<float>> m_vecRSPAcc;	//频域采样点最大加速度数组  分量
//	std::vector<std::vector<float>> m_vecRSPVel;
//	std::vector<std::vector<float>> m_vecRSPDisp;
//
//	//void SetTn(std::vector<float> vecTn) {	//设置采样点序列
//	//	m_vecTn = vecTn;
//	//}
//	//float GetSpectrumAcc(int iComp, float fTerm);
//	//float GetSpectrumVel(int iComp, float fTerm);
//	//float GetSpectrumDisp(int iComp, float fTerm);
//};
//
////形成地震波库所用数据
////单分量
//struct WaveDataOne {
//	WaveDataOne() : iYear(-1), iMonth(-1), iDay(-1) {}
//
//	int idx;
//	std::string sName;	//地震名
//	int	iYear;
//	int iMonth;
//	int iDay;
//	//int iHour;
//	//int iMinute;
//	std::string sStation;
//	std::string sFileName;
//	std::string sComponent;
//
//	float dt;
//	int iNumAcc;	//加速度点数
//	std::vector<float> vecAcc;
//	//	int iNumRSP;	//谱点数
//};
//
//class WaveDataTmp {
//public:
//	WaveDataTmp() {iYear = -1; iMonth = -1; iDay = -1; dt = 0.02f; }
//	std::string sName;
//	int iYear;
//	int iMonth;
//	int iDay;
//	//int iHour;
//	//int iMinute;
//	std::string sStation;
//	std::string sFileName;
//
//	//int iNumCompData;				//分量数目
//	//	CStringA csComp[3];			//--->增加竖向分量  [2] -> [3]
//	std::vector<std::string> vecComp;
//
//	float dt;
//	//	std::vector<int> vecNumAcc;  //加速度点数	//这个可以不需要
//	std::vector<std::vector<float>> vecAcc;
//
//	std::vector<float> vecTg;		//新增的 Tg
//	//int iNumRSP;	//谱点数
//};
//
//float CalculateTg(float velT1, float velT2, float accT0, float accT1, const std::vector<float>& vTn, const std::vector<float>& vRSPAcc, const std::vector<float>& vRSPVel);
////void ReadWave(CStringA csFileName, int idx, S_WaveIndex& waveIdx, std::vector<std::vector<float>>& vecTime, std::vector<std::vector<float>>& vecAcc, S_SpectrumOne& specOne);
//
////void GenerateSpectrum(float fDamp, float fFactor, float fDt, 
////	const std::vector<float> vecAcc, 
////	std::vector<float>& vTn, std::vector<float>& vRSPAcc, 
////	std::vector<float>& vRSPVel, std::vector<float>& vRSPDisp);
////void GenerateTimeSeries(std::vector<float>& vTn);
////void GenerateWaveLib(std::vector<WaveDataOne>& vecWaveLib, CStringA sFileName);
//
//
////小震中震大震应该增加参数
////void GenerateCodeSpectrum(float fDamp, int iSI, int iGroup, int iSite, std::vector<float> vecTn, std::vector<float>& vecSpec);
//
////int ReadWaveIndex(_mstring sWaveFileName, S_WaveHeader& waveHeader, std::vector<S_WaveIndex>& vecWaveIndex, std::vector<float>& vecTn);
//
////void ReadOneWave(_mstring sWaveFileName, int idx, S_WaveIndex& waveIdx,
////	std::vector<std::vector<float>>& vecTime, std::vector<std::vector<float>>& vecAcc,
////	S_SpectrumOne& spec);
//
////波库工具 包括选波
//class _SSG_DLLIMPEXP CWaveTool
//{
//public:
//	CWaveTool() : m_hFile(0), m_fileName(L"wavefile.bin"), m_fDamp(0.05f), m_iSI(2), m_iGroup(2), m_iSite(2) {};
//
//	~CWaveTool() { 
//		if(m_hFile)
//			fclose(m_hFile);
//	}
//
//	FILE *m_hFile;	//库文件句柄，一直打开以便加速读取
//
//	//波库名
//	std::wstring m_fileName;
//	//波库头
//	S_WaveHeader m_waveHeader;
//	//波库索引序列
//	std::vector<S_WaveIndex> m_vecWaveIndex;
//
//	//谱采样点数据, 从波库中读取
//	std::vector<float> m_vecTn;
//
//	//规范谱序列  加速度
//	std::vector<float> m_vecCodeRSA;
//
//	//地震参数
//	float m_fDamp;	// = 0.05f;
//	int m_iSI;		// = 2;
//	int m_iGroup;	// = 2;
//	int m_iSite;	// = 2;
//
//	float m_fGravityAcce;
//
//	int m_numNode;		//模型节点数
//	int m_numEigen;		//特征值数
//	std::vector<float> m_vecPeriod;		//周期	
//	std::vector<float> m_vecTempMass;	//广义质量
//	std::vector<float> m_vecGamma;		//质量参与系数
//	std::vector<float> m_vecRho;
//
//public:
//	void SetWaveFile(std::wstring filename) {
//		m_fileName = filename;
//	}
//
//	void CloseWaveFile() {
//		if(m_hFile)
//			fclose(m_hFile);
//		m_hFile = 0;
//	}
//
//	//打开波库文件
//	bool OpenWaveFile();
//	bool ReadHeader();
//	bool ReadVecTn();
//
//	//读取波库索引
//	bool ReadAllWaveIndex();
//
//	bool ReadWaveIndex(int idx, S_WaveIndex& waveIdx);
//
//
//	//读取一条波加速度序列
//	bool ReadAccFromLib(S_WaveIndex waveIdx, std::vector<std::vector<float>>& vecTime, std::vector<std::vector<float>>& vecAcc);
//
//	//读取一条波的谱
//	bool ReadSpectrumFromLib(S_WaveIndex waveIdx, S_SpectrumOne& specOne, float factor = 1.0f);
//
//	//设置规范谱参数
//	void SetCodePara(float fDamp, int iSI, int iGroup, int iSite);
//
//	void GenerateTn();
//
//	//生成规范反应谱
//	void GenerateCodeSpectrum();
//
//	//选波
//	void SelectEarthquake(std::string path, float fBeta, float fLambda, float fEta, std::vector<int> vecOption, std::vector<int>& vecSelect);
//
//	bool CalcModelCoeff(std::string fpath);
//	void CalcBaseshearCode(float& fShearSpectrum, float& fSek);
//	void CalcBaseshearTH(int idxWave, float& fShearTH);
//
//	bool WaveExist(const WaveDataTmp& waveOne);
////	void MergeWave(const std::vector<WaveDataOne>& vecWave, std::map<std::string, WaveDataTmp> &mapWaveLib);
//	void MergeWave(const std::vector<WaveDataOne>& vecWaveOne, std::vector<WaveDataTmp> &vecWaveData, std::map<std::string, int>mapWave);
//	//bool WriteWaveLib(std::map<std::string, WaveDataTmp> mapWaveLib);//const std::vector<WaveDataOne>& vecWaveLib);
//	bool CWaveTool::WriteWaveLib(std::vector<WaveDataTmp> vecWaveData);
//
//	bool CWaveTool::ReadWaveData(S_WaveIndex waveIdx, WaveDataTmp &waveData);
//	//bool ReadWaveLib(std::map<std::string, WaveDataTmp> &mapWaveLib);
//	bool ReadWaveLib(std::vector<WaveDataTmp> &vecWaveLib);
//	//	bool WriteWaveLib(std::wstring sFileName, const std::vector<WaveDataOne>& vecWaveLib);
//
//	void RemoveOne(int idx);	//删除一条波
//};
//
//std::string itostring(int value);
//std::string stringToUpper(std::string strToConvert);
//
//float Interpolation(float fX, std::vector<float> vecX, std::vector<float> vecFX);
//void GenerateTimeSeries(float fMaxTerm, float fTermDist, std::vector<float>& vTn);
//float CodeSpectrum(float Tn, float fDamp, int iSI, int iGroup, int iSite);