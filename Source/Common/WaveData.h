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

//˵��
//����Ӧ�ý����𲨶����뵽Access���ݿ��У�Ȼ���ٽ��в�����
//������Ժ�����

#ifdef _UNICODE
typedef std::wstring _tstring;
#else
typedef std::string _tstring;
#endif


//const long g_idWaveLib = 20170921;//20150501;	//<-- �޸�Ϊ�µĸ�ʽ
const int  g_iVersion = 11;

const int g_iComp = 3;		//�������� <--- ԭ��Ϊ2 �ָ�Ϊ 3
const int g_iTGS = 10;

const int g_charlen = 256;

const float AlphaData[3][6] =
{
	{ 0.04f, 0.08f, 0.12f, 0.16f, 0.24f, 0.32f},		// С��
	{ 0.12f, 0.23f, 0.34f, 0.45f, 0.68f, 0.90f},		// ����
	{ 0.28f, 0.50f, 0.72f, 0.90f, 1.20f, 1.40f}			// ����
};

const float AccData[3][6] =
{
	{ 0.18f, 0.35f, 0.55f, 0.70f, 1.10f, 1.40f},		// С��
	{ 0.50f, 1.00f, 1.50f, 2.00f, 3.00f, 4.00f},		// ����
	{ 1.25f, 2.20f, 3.10f, 4.00f, 5.10f, 6.20f}			// ����
};

const float TgData[3][5] =
{
	{ 0.20f, 0.25f, 0.35f, 0.45f, 0.65f},			// ��һ��
	{ 0.25f, 0.30f, 0.40f, 0.55f, 0.75f},			// �ڶ���
	{ 0.30f, 0.35f, 0.45f, 0.65f, 0.90f}			// ������
};


//�����ļ�ͷ
struct S_WaveHeader {
	S_WaveHeader() { uid = 0; iVersion = g_iVersion; iNum = 0; posRSP = 0l; iLengthRSP = 0;}
	long uid;			//global identifier
	int  iVersion;		//�汾��
	int  iNum;			//���������Ŀ
	long iNumRSP;		//�׵���

	long posRSP;		//��������ʼλ��,�Ա�һ�����		//�ⲿ��û��
	int  iLengthRSP;	//�����ݴ洢�󳤶�					//�ⲿ��û��
};

//�������ݽṹ��Ϣ
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

	int   idx;						//����id
	int   status;					//״̬ 0-���� 1-ɾ��  ��ʱû��
	char  sName[g_charlen];			//������
	int	  iYear;					//��
	int   iMonth;					//��
	int   iDay;						//��
	char  sStation[g_charlen];		//��վ��

	int	  type;								//�˹���������Ȼ�� 0-��Ȼ�� 1-�˹���
	int	  tag1;
	float tag2;

	int   nNumComp;					//������
	char  sComponent[g_iComp][g_charlen];	//����
	char  sFileName[g_charlen];			//�ļ��� ����ʱ����

	float dt;						//ʱ����
	float accMax[g_iComp];			//���ٶȷ�ֵ

	float Tg[g_iComp];				//������������

	int	  iNumAcc[g_iComp];			//���ٶȵ���
	int   iNumRSP;					//�׵ĵ���, ���� ���ǿ���ֱ�Ӷ�ȡÿ�����ݲ��ö�ȡ����

	long  iStartPos;				//���ݿ�ʼλ��
	int   iLenData;					//�洢���ݵ�ѹ���󳤶�

	//����:
	// i:=1 to nNumComp { ���ٶ����� }
	// ��ʱ������
	// i:=1 to iNumRSP { �׼��ٶ����С����ٶ����С���λ������ }
};

//struct S_Acc
//{
//	float t;
//	float acc;
//};

//��Ҫ���
//��ͳһ������   �� Tg
struct S_SpectrumOne {
	int idx;	//���������
	//	std::vector<float> m_vecTn;
	float Tg;

	//	std::vector<float> m_vecTn;						//Ƶ���������������(��)

	std::vector<std::vector<float>> vecRSPAcc;	//Ƶ������������ٶ�����  ����
	std::vector<std::vector<float>> vecRSPVel;
	std::vector<std::vector<float>> vecRSPDisp;

	//void SetTn(std::vector<float> vecTn) {	//���ò���������
	//	m_vecTn = vecTn;
	//}
	//float GetSpectrumAcc(int iComp, float fTerm);
	//float GetSpectrumVel(int iComp, float fTerm);
	//float GetSpectrumDisp(int iComp, float fTerm);
};

//�γɵ��𲨿���������
//������
struct WaveDataOne {
	WaveDataOne() : iYear(-1), iMonth(-1), iDay(-1) {}

	int idx;
	std::string sName;	//������
	int	iYear;
	int iMonth;
	int iDay;
	//int iHour;
	//int iMinute;
	std::string sStation;
	std::string sFileName;
	std::string sComponent;

	float dt;
	int iNumAcc;	//���ٶȵ���
	std::vector<float> vecAcc;
	//	int iNumRSP;	//�׵���
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