#pragma once

// ��ȡ���������Ϣ�࣬�����ⲿ��Ϊ��̬�⣬�������ﵥ����ȡһ���������������Ϣ

#include "IGenerateText.h"
#include "HeadDefine.h"
#include <string>
#include <vector>
#include <map>

using namespace std;
using namespace sd;

const int CHART_DEFAULT = 0;			//type	= 0 -- Ĭ��ɢ��ͼ
const int CHART_WAVE = 1;			// -- ����
const int CHART_SPECTRUM = 2;		// -- ��Ӧ��
const int CHART_SHEARSTORY= 3;			// -- �����
const int CHART_TIMESHEAR= 4;			// -- �����
const int CHART_OVERTURNSTORY = 5;		//-- �㸲����
const int CHART_DISPSTORY = 6;			// -- λ��
const int CHART_DRIFTSTORY = 7;			// -- λ�ƽ�
const int CHART_TIMEDISP = 8;			// -- ����λ��ʱ��
const int CHART_SHEARHYSTERISSTORY = 9;		// -- ¥������ͻ�
const int CHART_ENERGY = 10;					// -- ����ͼ
const int CHART_PFBAR = 11;					// -- 
const int CHART_PFPIE = 12;					// -- 
const int CHART_SHEARCHECK = 13;					// ���򹹼ܿ�������-- 

#define SAFE_DELETE(p) if(p){delete p; p=NULL;}
namespace sd{
	class _POST_DLLIMPEXP CExhibition
	{
	public:
		CExhibition(void);
		~CExhibition(void);

		static CExhibition* getInstance();
		void testDocxEx(IGenerateText *pGenerateTxt);

		string m_sFileName;	//����ͼ�ļ���
//		void SetName(string sName) { m_sName = sName; }
		bool BeginChart(string sName, IGenerateText *pGenerateText);
		bool EndChart(IGenerateText *pGenerateText);

	bool InsertChart(IGenerateText *pGenerateText, CString sFileName, string sTitle, string sXTitle, string sYTitle, 
		int nWidth, int nHeight, vector<string>& sNames, vector<vector<float>> &xSeries, vector<vector<float>> &ySeries, 
		SdChartType type, SdChartSubType subtype, int option = 0, int nSpace = 5, float fLineWidth = 0.75f); 
		//bool bXInteger=false, bool bYInteger=false, 
		//int type=0, int subtype=0, int gridStyle=0, int legendPosition=0, int nSpace=0);

	private:
		PPAGE_FORMAT m_pPageFormat;  //ҳ���ʽ
		PPARAGRAPH_FORMAT m_pParaghFormat;  //�����ʽ
		PTEXT_FORMAT m_pTextFormat;  //�ı���ʽ
		PGRAPHIC_FORMAT m_pPicFormat; //��ͨͼƬ��ʽ
		PGRAPHIC_EMBED_FORMAT m_pPicEmbedFormat; //Ƕ����ͼƬ��ʽ
		PTABLE_FORMAT m_pTableFormat; //����ʽ
		PCELL_FORMAT m_pCellFormat;  //��Ԫ���ʽ
		PCHART_FORMAT m_pChartFormat;//ͼ���ʽ(��״ͼ��)
	};
}

IGenerateText * getTextGenerater();
void ReleaseTextGenerator(IGenerateText *pGenerateText);

void ReportAllWeight(float& fSumDead, float& fSumLive, float& fSumTotal);

#define IS_ZERO(a) ((abs(a)< 1.0e-8))
#define IS_EQUAL(a,b) ((abs((a)-(b))< 1.0e-8))


int FindDigitNum(float fValue, int iMaxDigit=5);


