#pragma once

// 获取所有相关信息类，考虑外部均为静态库，所以这里单独提取一个类来处理各种信息

#include "IGenerateText.h"
#include "HeadDefine.h"
#include <string>
#include <vector>
#include <map>

using namespace std;
using namespace sd;

const int CHART_DEFAULT = 0;			//type	= 0 -- 默认散点图
const int CHART_WAVE = 1;			// -- 地震波
const int CHART_SPECTRUM = 2;		// -- 反应谱
const int CHART_SHEARSTORY= 3;			// -- 层剪力
const int CHART_TIMESHEAR= 4;			// -- 层剪力
const int CHART_OVERTURNSTORY = 5;		//-- 倾覆力矩
const int CHART_DISPSTORY = 6;			// -- 位移
const int CHART_DRIFTSTORY = 7;			// -- 位移角
const int CHART_TIMEDISP = 8;			// -- 顶点位移时程
const int CHART_SHEARHYSTERISSTORY = 9;		// -- 楼层剪力滞回
const int CHART_ENERGY = 10;					// -- 能量图
const int CHART_PFBAR = 11;					// -- 
const int CHART_PFPIE = 12;					// -- 
const int CHART_SHEARCHECK = 13;					// 竖向构架抗剪验算-- 

#define SAFE_DELETE(p) if(p){delete p; p=NULL;}
namespace sd{
	class _POST_DLLIMPEXP CExhibition
	{
	public:
		CExhibition(void);
		~CExhibition(void);

		static CExhibition* getInstance();
		void testDocxEx(IGenerateText *pGenerateTxt);

		string m_sFileName;	//保存图文件名
//		void SetName(string sName) { m_sName = sName; }
		bool BeginChart(string sName, IGenerateText *pGenerateText);
		bool EndChart(IGenerateText *pGenerateText);

	bool InsertChart(IGenerateText *pGenerateText, CString sFileName, string sTitle, string sXTitle, string sYTitle, 
		int nWidth, int nHeight, vector<string>& sNames, vector<vector<float>> &xSeries, vector<vector<float>> &ySeries, 
		SdChartType type, SdChartSubType subtype, int option = 0, int nSpace = 5, float fLineWidth = 0.75f); 
		//bool bXInteger=false, bool bYInteger=false, 
		//int type=0, int subtype=0, int gridStyle=0, int legendPosition=0, int nSpace=0);

	private:
		PPAGE_FORMAT m_pPageFormat;  //页面格式
		PPARAGRAPH_FORMAT m_pParaghFormat;  //段落格式
		PTEXT_FORMAT m_pTextFormat;  //文本格式
		PGRAPHIC_FORMAT m_pPicFormat; //普通图片格式
		PGRAPHIC_EMBED_FORMAT m_pPicEmbedFormat; //嵌入型图片格式
		PTABLE_FORMAT m_pTableFormat; //表格格式
		PCELL_FORMAT m_pCellFormat;  //单元格格式
		PCHART_FORMAT m_pChartFormat;//图表格式(柱状图等)
	};
}

IGenerateText * getTextGenerater();
void ReleaseTextGenerator(IGenerateText *pGenerateText);

void ReportAllWeight(float& fSumDead, float& fSumLive, float& fSumTotal);

#define IS_ZERO(a) ((abs(a)< 1.0e-8))
#define IS_EQUAL(a,b) ((abs((a)-(b))< 1.0e-8))


int FindDigitNum(float fValue, int iMaxDigit=5);


