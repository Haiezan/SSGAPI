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

//����Ӱ��ϵ�����ֵ
const float AlphaData[3][6] = //����
{
	{ 0.04f, 0.08f, 0.12f, 0.16f, 0.24f, 0.32f},		// С��
	{ 0.12f, 0.23f, 0.34f, 0.45f, 0.68f, 0.90f},		// ����
	{ 0.28f, 0.50f, 0.72f, 0.90f, 1.20f, 1.40f}			// ����
};
const float AlphaData_GuangDong[5][3][6] = //�㶫���ܻ���׼
{
	//I0 �ೡ����                       //�淶����Ӧ���ݰ��չ���ȡֵ
	{
		{0.04f, 0.07f, 0.11f, 0.14f,    0.24f, 0.32f},		// С��
		{0.11f, 0.20f, 0.31f, 0.41f,    0.68f, 0.90f},		// ����
		{0.26f, 0.45f, 0.63f, 0.82f,    1.20f, 1.40f},		// ����
	},
	//I1 �ೡ���� ͬ��
	{
		{0.04f, 0.07f, 0.11f, 0.14f,    0.24f, 0.32f},		// С��
		{0.11f, 0.20f, 0.31f, 0.41f,    0.68f, 0.90f},		// ����
		{0.26f, 0.45f, 0.63f, 0.82f,    1.20f, 1.40f},		// ����
	},
	//II�ೡ����
	{
		{0.04f, 0.08f, 0.12f, 0.16f,    0.24f, 0.32f},		// С��
		{0.12f, 0.23f, 0.34f, 0.45f,    0.68f, 0.90f},		// ����
		{0.28f, 0.50f, 0.72f, 0.90f,    1.20f, 1.40f},		// ����.
	},
	//III�ೡ����
	{
		{0.05f, 0.09f, 0.14f, 0.18f,    0.24f, 0.32f},		// С��
		{0.13f, 0.26f, 0.38f, 0.51f,    0.68f, 0.90f},		// ����
		{0.32f, 0.56f, 0.79f, 1.02f,    1.20f, 1.40f},		// ����
	},
	//IV�ೡ���� ͬ��
	{
		{0.05f, 0.10f, 0.15f, 0.20f,    0.24f, 0.32f},		// С��
		{0.14f, 0.28f, 0.42f, 0.56f,    0.68f, 0.90f},		// ����
		{0.35f, 0.62f, 0.87f, 1.12f,    1.20f, 1.40f},		// ����
	}
};
const float AlphaData_ISO[4][6] = //����
{
		{ 0.04f, 0.08f, 0.12f, 0.16f, 0.24f, 0.32f},		// С��
		{ 0.12f, 0.23f, 0.34f, 0.45f, 0.68f, 0.90f},		// ����
		{ 0.28f, 0.50f, 0.72f, 0.90f, 1.20f, 1.40f},		// ����
		{ 0.36f, 0.72f, 1.00f, 1.35f, 2.00f, 2.43f}			// ������
};
const float AlphaData_GD[5][2][6] = //�㶫�߹�
{
	//I0 �ೡ���� 
	{
		{0.11f, 0.20f, 0.30f, 0.40f, 0.60, 0.80},		// ����
		{0.25f, 0.45f, 0.65f, 0.80f, 1.08, 1.26},		// ����
	},
	//I1 �ೡ���� ͬ��
	{
		{0.11f, 0.20f, 0.30f, 0.40f, 0.60, 0.80},		// ����
		{0.25f, 0.45f, 0.65f, 0.80f, 1.08, 1.26},		// ����
	},
	//II�ೡ����
	{
		{0.12f, 0.23f, 0.34f, 0.45f, 0.68, 0.90},		// ����
		{0.28f, 0.50f, 0.72f, 0.90f, 1.20, 1.40},		// ����
	},
	//III�ೡ����
	{
		{0.13f, 0.25f, 0.37f, 0.50f, 0.75, 1.00},		// ����
		{0.31f, 0.55f, 0.79f, 1.00f, 1.32, 1.54},		// ����
	},
	//IV�ೡ���� ͬ��
	{
		{0.13f, 0.25f, 0.37f, 0.50f, 0.75, 1.00},		// ����
		{0.31f, 0.55f, 0.79f, 1.00f, 1.32, 1.54},		// ����
	},
};
const float AlphaData_SH[3][6] = //�Ϻ���
{
	{ 0.04f, 0.08f, 0.08f, 0.16f, 0.16f, 0.16f},		// С��
	{ 0.12f, 0.23f, 0.23f, 0.45f, 0.45f, 0.45f},		// ����
	{ 0.26f, 0.45f, 0.45f, 0.81f, 0.81f, 0.81f}			// ����
};

//��ֵ���ٶ�
const float AccData[3][6] = //����
{
	{ 0.18f, 0.35f, 0.55f, 0.70f, 1.10f, 1.40f},		// С��
	{ 0.50f, 1.00f, 1.50f, 2.00f, 3.00f, 4.00f},		// ����
	{ 1.25f, 2.20f, 3.10f, 4.00f, 5.10f, 6.20f}			// ����
};
const float AccData_GuangDong[3][6] = //�㶫���ܻ���׼
{
	{ 0.18f, 0.35f, 0.55f, 0.70f,    1.10f, 1.40f},			// С��
	{ 0.50f, 1.00f, 1.50f, 2.00f,    3.00f, 4.00f},			// ����
	{ 1.25f, 2.20f, 3.10f, 4.00f,    5.10f, 6.20f}			// ����
};
const float AccData_ISO[4][6] = //����
{
		{ 0.18f, 0.35f, 0.55f, 0.70f, 1.10f, 1.40f},		// С��
		{ 0.50f, 1.00f, 1.50f, 2.00f, 3.00f, 4.00f},		// ����
		{ 1.25f, 2.20f, 3.10f, 4.00f, 5.10f, 6.20f},		// ����
		{ 1.60f, 3.20f, 4.60f, 6.00f, 8.40f, 10.80f}		// ������
};
const float AccData_GD[5][2][6] = //�㶫�߹�
{
	//I0�ೡ��
	{
		{ 0.45f, 0.90f, 1.35f, 1.80f, 2.70f, 3.60f},		// ����
		{ 1.13f, 1.98f, 2.79f, 3.60f, 4.59f, 5.58f},		// ����
	},
	//I1�ೡ�� ͬ��
	{
		{ 0.45f, 0.90f, 1.35f, 1.80f, 2.70f, 3.60f},		// ����
		{ 1.13f, 1.98f, 2.79f, 3.60f, 4.59f, 5.58f},		// ����
	},
	//II�ೡ��
	{
		{ 0.50f, 1.00f, 1.50f, 2.00f, 3.00f, 4.00f},		// ����
		{ 1.25f, 2.20f, 3.10f, 4.00f, 5.10f, 6.20f},		// ����
	},
	//III�ೡ��
	{
		{ 0.55f, 1.10f, 1.65f, 2.20f, 3.30f, 4.40f},		// ����
		{ 1.38f, 2.42f, 3.41f, 4.40f, 5.61f, 6.82f},		// ����
	},
	//IV�ೡ�� ͬ��
	{
		{ 0.55f, 1.10f, 1.65f, 2.20f, 3.30f, 4.40f},		// ����
		{ 1.38f, 2.42f, 3.41f, 4.40f, 5.61f, 6.82f},		// ����
	},
};

const float AccData_JG[4][3][6] = //���ܼ��������
{
	//A��
	{
		{ 0.14f, 0.26f, 0.41f, 0.53f, 0.83f, 1.05f},		// С��
		{ 0.46f, 0.81f, 1.22f, 1.62f, 2.43f, 3.24f},		// ����
		{ 1.06f, 1.87f, 2.64f, 3.40f, 4.34f, 5.27f}			// ����
	},
	//B��
	{
		{ 0.16f, 0.31f, 0.48f, 0.62f, 0.97f, 1.23f},		// С��
		{ 0.46f, 0.91f, 1.37f, 1.82f, 2.73f, 3.64f},		// ����
		{ 1.16f, 2.04f, 2.88f, 3.72f, 4.74f, 5.77f}			// ����
	},
	//��C��
	{
		{ 0.18f, 0.35f, 0.55f, 0.70f, 1.10f, 1.40f},		// С��
		{ 0.50f, 1.00f, 1.50f, 2.00f, 3.00f, 4.00f},		// ����
		{ 1.25f, 2.20f, 3.10f, 4.00f, 5.10f, 6.20f}			// ����
	},
	//C��
	{
		{ 0.18f, 0.35f, 0.55f, 0.70f, 1.10f, 1.40f},		// С��
		{ 0.50f, 1.00f, 1.50f, 2.00f, 3.00f, 4.00f},		// ����
		{ 1.25f, 2.20f, 3.10f, 4.00f, 5.10f, 6.20f}			// ����
	}
};

const float Acc_JG_Scale[2][3] = { //�ӹ̵��������ۼ�ϵ��
		{ 0.75f, 0.81f, 0.85f},	//A��	 С�� ���� ����
		{ 0.88f, 0.91f, 0.93f}	//B�� 	 С�� ���� ����
};

//��������
const float TgData[3][5] = //����
{
	{ 0.20f, 0.25f, 0.35f, 0.45f, 0.65f},			// ��һ��
	{ 0.25f, 0.30f, 0.40f, 0.55f, 0.75f},			// �ڶ���
	{ 0.30f, 0.35f, 0.45f, 0.65f, 0.90f}			// ������
};
const float TgData_GuangDong[3][5] = //�㶫���ܻ���׼
{
	{ 0.20f, 0.25f, 0.35f, 0.45f, 0.65f},			// ��һ��
	{ 0.25f, 0.35f, 0.50f, 0.65f, 0.85f},			// �ڶ���
	{ 0.35f, 0.50f, 0.70f, 0.90f, 1.10f}			// ������
};
const float TgData_ISO[3][5] = //���� Tg �뿹��һ��
{
	{ 0.20f, 0.25f, 0.35f, 0.45f, 0.65f},			// ��һ��
	{ 0.25f, 0.30f, 0.40f, 0.55f, 0.75f},			// �ڶ���
	{ 0.30f, 0.35f, 0.45f, 0.65f, 0.90f}			// ������
};
const float TgData_GD[3][5] = //�㶫�߹�
{
	{ 0.20f, 0.25f, 0.35f, 0.45f, 0.65f},			// ��һ��
	{ 0.25f, 0.35f, 0.50f, 0.65f, 0.85f},			// �ڶ���
	{ 0.35f, 0.50f, 0.70f, 0.90f, 1.10f}			// ������
};
const float TgData_SH[3][5] = //�Ϻ���׼
{
	{ 0.65f, 0.65f, 0.65f, 0.65f, 0.90f},			// С��
	{ 0.65f, 0.65f, 0.65f, 0.65f, 0.90f},		// ����
	{ 1.10f, 1.10f, 1.10f, 1.10f, 1.10f}			// ����
};
//const float Betamax_GuangDong[5] =
//{
//	2.00f, 2.00f, 2.25f, 2.50f, 2.75f			// ��һ��
//};

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