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
////˵��
////����Ӧ�ý����𲨶����뵽Access���ݿ��У�Ȼ���ٽ��в�����
////������Ժ�����
//
////#ifdef _UNICODE
////typedef std::wstring _mstring;
////#else
////typedef std::string _mstring;
////#endif
//
//const float AlphaData[3][6] =
//{
//	{ 0.04f, 0.08f, 0.12f, 0.16f, 0.24f, 0.32f},		// С��
//	{ 0.12f, 0.23f, 0.34f, 0.45f, 0.68f, 0.90f},		// ����
//	{ 0.28f, 0.50f, 0.72f, 0.90f, 1.20f, 1.40f}		// ����
//};
//
//const float AccData[3][6] =
//{
//	{ 0.18f, 0.35f, 0.55f, 0.70f, 1.10f, 1.40f},		// С��
//	{ 0.50f, 1.00f, 1.50f, 2.00f, 3.00f, 4.00f},		// ����
//	{ 1.25f, 2.20f, 3.10f, 4.00f, 5.10f, 6.20f}		// ����
//};
//
//const float TgData[3][5] =
//{
//	{ 0.20f, 0.25f, 0.35f, 0.45f, 0.65f},		// ��һ��
//	{ 0.25f, 0.30f, 0.40f, 0.55f, 0.75f},		// �ڶ���
//	{ 0.30f, 0.35f, 0.45f, 0.65f, 0.90f}		// ������
//};
//
//
//const long g_idWaveLib = 20170921;//20150501;	//<-- �޸�Ϊ�µĸ�ʽ
//const int  g_iVersion = 11;
//
//const int g_iComp = 3;		//�������� <--- ԭ��Ϊ2 �ָ�Ϊ 3
//const int g_iTGS = 10;
//
//const int g_charlen = 256;
//
////�����ļ�ͷ
//struct S_WaveHeader {
//	S_WaveHeader() { uid = 0; iVersion = g_iVersion; iNum = 0; posRSP = 0l; iLengthRSP = 0;}
//	long uid;			//global identifier
//	int  iVersion;		//�汾��
//	int  iNum;			//���������Ŀ
//	long iNumRSP;		//�׵���
//
//	long posRSP;		//��������ʼλ��,�Ա�һ�����		//�ⲿ��û��
//	int  iLengthRSP;	//�����ݴ洢�󳤶�					//�ⲿ��û��
//};
//
////�������ݽṹ��Ϣ
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
//	int   idx;						//����id
//	int   status;					//״̬ 0-���� 1-ɾ��  ��ʱû��
//	char  sName[g_charlen];				//������
//	int	  iYear;					//��
//	int   iMonth;					//��
//	int   iDay;						//��
//	char  sStation[g_charlen];				//��վ��
//
//	int   nNumComp;					//������
//	char  sComponent[g_iComp][g_charlen];	//����
//	char  sFileName[g_charlen];			//�ļ��� ����ʱ����
//
//	float dt;						//ʱ����
//	float accMax[g_iComp];			//���ٶȷ�ֵ
//
//	float Tg[g_iComp];				//������������
//
//	int	  iNumAcc[g_iComp];			//���ٶȵ���
//	int   iNumRSP;					//�׵ĵ���, ���� ���ǿ���ֱ�Ӷ�ȡÿ�����ݲ��ö�ȡ����
//
//	long  iStartPos;				//���ݿ�ʼλ��
//	int   iLenData;					//�洢���ݵ�ѹ���󳤶�
//
//	//����:
//	// i:=1 to nNumComp { ���ٶ����� }
//	// ��ʱ������
//	// i:=1 to iNumRSP { �׼��ٶ����С����ٶ����С���λ������ }
//};
//
////struct S_Acc
////{
////	float t;
////	float acc;
////};
//
////��Ҫ���
////��ͳһ������   �� Tg
//struct S_SpectrumOne {
//	int idx;	//���������
//	//	std::vector<float> m_vecTn;
//	float Tg;
//
//	//	std::vector<float> m_vecTn;						//Ƶ���������������(��)
//
//	std::vector<std::vector<float>> m_vecRSPAcc;	//Ƶ������������ٶ�����  ����
//	std::vector<std::vector<float>> m_vecRSPVel;
//	std::vector<std::vector<float>> m_vecRSPDisp;
//
//	//void SetTn(std::vector<float> vecTn) {	//���ò���������
//	//	m_vecTn = vecTn;
//	//}
//	//float GetSpectrumAcc(int iComp, float fTerm);
//	//float GetSpectrumVel(int iComp, float fTerm);
//	//float GetSpectrumDisp(int iComp, float fTerm);
//};
//
////�γɵ��𲨿���������
////������
//struct WaveDataOne {
//	WaveDataOne() : iYear(-1), iMonth(-1), iDay(-1) {}
//
//	int idx;
//	std::string sName;	//������
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
//	int iNumAcc;	//���ٶȵ���
//	std::vector<float> vecAcc;
//	//	int iNumRSP;	//�׵���
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
//	//int iNumCompData;				//������Ŀ
//	//	CStringA csComp[3];			//--->�����������  [2] -> [3]
//	std::vector<std::string> vecComp;
//
//	float dt;
//	//	std::vector<int> vecNumAcc;  //���ٶȵ���	//������Բ���Ҫ
//	std::vector<std::vector<float>> vecAcc;
//
//	std::vector<float> vecTg;		//������ Tg
//	//int iNumRSP;	//�׵���
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
////С���������Ӧ�����Ӳ���
////void GenerateCodeSpectrum(float fDamp, int iSI, int iGroup, int iSite, std::vector<float> vecTn, std::vector<float>& vecSpec);
//
////int ReadWaveIndex(_mstring sWaveFileName, S_WaveHeader& waveHeader, std::vector<S_WaveIndex>& vecWaveIndex, std::vector<float>& vecTn);
//
////void ReadOneWave(_mstring sWaveFileName, int idx, S_WaveIndex& waveIdx,
////	std::vector<std::vector<float>>& vecTime, std::vector<std::vector<float>>& vecAcc,
////	S_SpectrumOne& spec);
//
////���⹤�� ����ѡ��
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
//	FILE *m_hFile;	//���ļ������һֱ���Ա���ٶ�ȡ
//
//	//������
//	std::wstring m_fileName;
//	//����ͷ
//	S_WaveHeader m_waveHeader;
//	//������������
//	std::vector<S_WaveIndex> m_vecWaveIndex;
//
//	//�ײ���������, �Ӳ����ж�ȡ
//	std::vector<float> m_vecTn;
//
//	//�淶������  ���ٶ�
//	std::vector<float> m_vecCodeRSA;
//
//	//�������
//	float m_fDamp;	// = 0.05f;
//	int m_iSI;		// = 2;
//	int m_iGroup;	// = 2;
//	int m_iSite;	// = 2;
//
//	float m_fGravityAcce;
//
//	int m_numNode;		//ģ�ͽڵ���
//	int m_numEigen;		//����ֵ��
//	std::vector<float> m_vecPeriod;		//����	
//	std::vector<float> m_vecTempMass;	//��������
//	std::vector<float> m_vecGamma;		//��������ϵ��
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
//	//�򿪲����ļ�
//	bool OpenWaveFile();
//	bool ReadHeader();
//	bool ReadVecTn();
//
//	//��ȡ��������
//	bool ReadAllWaveIndex();
//
//	bool ReadWaveIndex(int idx, S_WaveIndex& waveIdx);
//
//
//	//��ȡһ�������ٶ�����
//	bool ReadAccFromLib(S_WaveIndex waveIdx, std::vector<std::vector<float>>& vecTime, std::vector<std::vector<float>>& vecAcc);
//
//	//��ȡһ��������
//	bool ReadSpectrumFromLib(S_WaveIndex waveIdx, S_SpectrumOne& specOne, float factor = 1.0f);
//
//	//���ù淶�ײ���
//	void SetCodePara(float fDamp, int iSI, int iGroup, int iSite);
//
//	void GenerateTn();
//
//	//���ɹ淶��Ӧ��
//	void GenerateCodeSpectrum();
//
//	//ѡ��
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
//	void RemoveOne(int idx);	//ɾ��һ����
//};
//
//std::string itostring(int value);
//std::string stringToUpper(std::string strToConvert);
//
//float Interpolation(float fX, std::vector<float> vecX, std::vector<float> vecFX);
//void GenerateTimeSeries(float fMaxTerm, float fTermDist, std::vector<float>& vTn);
//float CodeSpectrum(float Tn, float fDamp, int iSI, int iGroup, int iSite);