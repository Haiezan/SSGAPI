#pragma once

#include <comutil.h>
#include <string>
#include <vector>

using namespace std;

typedef IDispatch EXCEL_APP;
typedef IDispatch EXCEL_WORKBOOKS;
typedef IDispatch EXCEL_WORKBOOK;
typedef IDispatch EXCEL_SHEETS;
typedef IDispatch EXCEL_SHEET;

typedef IDispatch WORD_APP;
typedef IDispatch WORD_DOCUMENTS;
typedef IDispatch WORD_DOCUMENT;
typedef IDispatch WORD_TABLE;
typedef IDispatch WORD_RANGE;


enum WORD_LINE_STYLE
{
	wdUnderlineDash=7,                          //Dashes.
	wdUnderlineDashHeavy=23,					//Heavy dashes.
	wdUnderlineDashLong=39,						//Long dashes.
	wdUnderlineDashLongHeavy=55,				//Long heavy dashes.
	wdUnderlineDotDash=9,						//Alternating dots and dashes.
	wdUnderlineDotDashHeavy=25,					//Alternating heavy dots and heavy dashes.
	wdUnderlineDotDotDash=10,					//An alternating dot-dot-dash pattern.
	wdUnderlineDotDotDashHeavy=26,				//An alternating heavy dot-dot-dash pattern.
	wdUnderlineDotted=4,						//Dots.
	wdUnderlineDottedHeavy=20,					//Heavy dots.
	wdUnderlineDouble=3,						//A double line.
	wdUnderlineNone=0,							//No underline.
	wdUnderlineSingle=1,						//A single line. default.
	wdUnderlineThick=6,							//A single thick line.
	wdUnderlineWavy=11,							//A single wavy line.
	wdUnderlineWavyDouble=43,					//A double wavy line.
	wdUnderlineWavyHeavy=27,					//A heavy wavy line.
	wdUnderlineWords=2,							//Underline individual words only.
};

enum WORD_BACK_COLOR
{
	wdAuto=0,                    //Automatic color. Default; usually black.
	wdBlack=1,					 //Black color.
	wdBlue=2,					 //Blue color.
	wdBrightGreen=4,			 //Bright green color.
	wdByAuthor=-1,				 //Color defined by document author.
	wdDarkBlue=9,				 //Dark blue color.
	wdDarkRed=13,				 //Dark red color.
	wdDarkYellow=14,			 //Dark yellow color.
	wdGray25=16,				 //Shade 25 of gray color.
	wdGray50=15,				 //Shade 50 of gray color.
	wdGreen=11,					 //Green color.
	wdNoHighlight=0,			 //Removes highlighting that has been applied.
	wdPink=5,					 //Pink color.
	wdRed=6,					 //Red color.
	wdTeal=10,					 //Teal color.
	wdTurquoise=3,				 //Turquoise color.
	wdViolet=12,				 //Violet color.
	wdWhite=8,					 //White color.
	wdYellow=7,                  //Yellow color.
};

enum WORD_ALIGN
{
	wdAlignParagraphCenter=1,		//Center-aligned. 
	wdAlignParagraphDistribute=4,	//Paragraph characters are distributed to fill the entire width of the paragraph. 
	wdAlignParagraphJustify=3,		//Fully justified. 
	wdAlignParagraphJustifyHi=7,	//Justified with a high character compression ratio. 
	wdAlignParagraphJustifyLow=8,	//Justified with a low character compression ratio. 
	wdAlignParagraphJustifyMed=5,	//Justified with a medium character compression ratio. 
	wdAlignParagraphLeft=0,			//Left-aligned. 
	wdAlignParagraphRight=2,		//Right-aligned. 
	wdAlignParagraphThaiJustify=9,	//Justified according to Thai formatting layout. 

};

enum WORD_NUMBER_STYLE
{
	//0--阿拉伯数字，1-大写罗马数字，2--小写罗马数字，3-大写英文字母，4--小写英文字母，
	//5--英文简写序号1st,2nd,...,  6--英文数字,  7--英文序号，
	//18、28--阿拉伯数字带圆圈，26--阿拉伯数字后带点,27--阿拉伯数字带左右括号, 29--汉字数字带圆圈
	//30-天干，31-地支，32-干支组合，33-汉字小写数字，34-汉字大写数字，
	//255-空
	//23--项目符号，不适用于数字编号
	wdListNumberStyleArabic=0,
	wdListNumberStyleUppercaseRoman=1,
	wdListNumberStyleLowercaseRoman=2,
	wdListNumberStyleUppercaseLetter=3,
	wdListNumberStyleLowercaseLetter=4,
	wdListNumberStyleOrdinal=5,
	wdListNumberStyleCardinalText=6,
	wdListNumberStyleOrdinalText=7,
	wdListNumberStyleNumberInCircle=18,
	wdListNumberStyleArabicLZ=22,
	wdListNumberStyleBullet=23,
	wdListNumberStyleGBNum1=26,
	wdListNumberStyleGBNum2=27,
	wdListNumberStyleGBNum4=29,
	wdListNumberStyleZodiac1=30,
	wdListNumberStyleZodiac2=31,
	wdListNumberStyleZodiac3=32,
	wdListNumberStyleSimpChinNum1=33,
	wdListNumberStyleSimpChinNum2=34,
	wdListNumberStyleNone=255,
};

enum WORD_STYLE
{
	wdStyleNormal = -1,
	wdStyleHeading1 = -2,
	wdStyleHeading2 = -3,
	wdStyleHeading3 = -4,
	wdStyleHeading4 = -5,
	wdStyleHeading5 = -6,
	ChartHeading = -20,
};


enum WORD_MOVE_UNIT
{
	wdCell=12,			// 单元格。 
	wdCharacter= 1,		// 字符。 
	wdCharacterFormatting= 13,		// 字符格式。 
	wdColumn= 9,		// 列。 
	wdItem= 16 ,		//所选项。 
	wdLine= 5,			// 一个线段。 
	wdParagraph= 4,		// 段落。 
	wdParagraphFormatting= 14, //段落格式。 
	wdRow= 10,			// 行。 
	wdScreen= 7,		// 屏幕尺寸。 
	wdSection= 8,		// 一节。 
	wdSentence =3,		// 句子。 
	wdStory=6,			// 部分。 
	wdTable=15,			// 一个表格。 
	wdWindow=11,		// 窗口。 
	wdWord 
};

enum WORD_VAR_EXTEND
{
	wdMove=0,
	wdExtend=1
};

enum WORD_MOVE_DIRECTION
{
	wdMoveUp=0,
	wdMoveDown=1,
	wdMoveLeft=2,
	wdMoveRight=3
};

// for paragraph distance lhp
enum WORD_LINE_SPACE_RULE
{
	wdLineSpace1pt5 = 1,	// 1.5 倍行距。该行距相当于当前字号加 6 磅。 
	wdLineSpaceAtLeast = 3,	// 行距至少为一个指定值。该值需要单独指定。 
	wdLineSpaceDouble = 2,	// 双倍行距。 
	wdLineSpaceExactly = 4,	// 行距只能是所需的最大行距。此设置所使用的行距通常小于单倍行距。 
	wdLineSpaceMultiple = 5,// 由指定的行数确定的行距。 
	wdLineSpaceSingle = 0,	// 单倍行距，默认值。 
};

enum WORD_BREAK_TYPE
{
	wdColumnBreak=8,
	wdLineBreak=6,
	wdSectionBreakNextPage=2,
	wdPageBreak=7
};

enum VBA_CMD_TYPE
{
	VBA_PUT=1,
	VBA_GET=2,
	VBA_METHOD=4,
};


//通用VBA命令，命令字符串中可以用%1、%2指定变量，分别对应pparam1、pparam2
//举例：ActiveChart.SeriesCollection(%1).Name=%2
void ExeVBACmd(VBA_CMD_TYPE cmdType,VARIANT *pObj,const CString &sCmd,VARIANT *retVal,VARIANT *pparam1,VARIANT *pparam2);

//VBA命令
void VBA_Get(VARIANT *retVal,VARIANT *pObj,const CString &sCmd,VARIANT *pparam1=NULL,VARIANT *pparam2=NULL);
void VBA_Put(VARIANT *pObj,const CString &sCmd,VARIANT *pparam1=NULL,VARIANT *pparam2=NULL);
void VBA_Method(VARIANT *pObj,const CString &sCmd,VARIANT *pparam1=NULL,VARIANT *pparam2=NULL);

//复制字符串到VARIANT变量
void SetStrValue(VARIANT *pVal,LPCTSTR pwstr);

//sArray[iRow*nCols+iCol]--内容
void ToExcel(int nRows,int nCols,const CString *sArray,BOOL bChart,int ChartType,const CString &sTitle,
	const CString *pLegend,BOOL bTitleRow,BOOL bScaleLine=TRUE,int xFormat=0,int yFormat=0);
//20240227 涂天驰 构件应变能生成excel
void ToExcelS(int nRows, int nCols, const CString* sArray, BOOL bChart, int ChartType, const CString& sTitle,
	const CString* pLegend, BOOL bTitleRow, BOOL bScaleLine = TRUE, int xFormat = 0, int yFormat = 0);
//psArray按逐行存储，每个psArray[i]对应一个sheet
void ToExcelM(int nRows,int nCols,const CString **psArray,const CString *pSheetName,int nSheet);

void ToExcelCSV(int nRows, int nCols, string *sArray, CString sPathFile, int nTotalCols=0);

void ToExcelM(int *pRows,int *pCols,const CString **psArray,const CString *pSheetName,int nSheet);

//Excel接口类
class CExcel
{
public:
	CExcel(void) ;
	
	~CExcel(void);

	int m_iError; //错误码：0--成功

	void Show(BOOL bShow=TRUE);  //显示
	EXCEL_WORKBOOKS *GetWorkBooks(void);					//获得文件集合
	EXCEL_WORKBOOK *AddBook(EXCEL_WORKBOOKS *pBooks);		//增加一个文件
	EXCEL_SHEETS *GetSheets(EXCEL_WORKBOOK *pBook);							//获得数据表集合
	EXCEL_SHEET *GetActiveSheet(EXCEL_WORKBOOK *pBook);		//获得当前表单
	EXCEL_WORKBOOK *AddSheet(EXCEL_WORKBOOK *pBook, const CString &sName=L"");
	int GetSheetsCount(EXCEL_SHEETS *pSheets);
	void RemoveSheet(EXCEL_WORKBOOK *pBook, int index);
	//增加图表
	void AddChart(EXCEL_SHEET *pSheet,int nRows,int nCols,const CString sTitle,
		const CString *pLegend,BOOL bTitleRow,BOOL bScaleLine,int xFormat,int yFormat,int ChartType=0);

	int GetCols(EXCEL_SHEET *pSheet); //自动获取列数

	//设置数据Array[iRow*nCols+iCol]
	void SetItemData(EXCEL_WORKBOOK *pXlBook,EXCEL_SHEET *pXlSheet,int nRows,int nCols,const int *iArray);
	void SetItemData(EXCEL_WORKBOOK *pXlBook,EXCEL_SHEET *pXlSheet,int nRows,int nCols,const float *fArray);
	void SetItemData(EXCEL_WORKBOOK *pXlBook,EXCEL_SHEET *pXlSheet,int nRows,int nCols,const CString *sArray);
	void Rename(VARIANT *pSheet,const CString &sSheetName);

	//退出Excel
	void Quit(void);

	HRESULT NewExcelBook(bool bVisible=true);
	HRESULT OpenExcelBook(LPCTSTR szFilename, bool bVisible=true);
//	HRESULT SaveAs(LPCTSTR szFilename, int nSaveAs=40);
	HRESULT SaveAs(LPCTSTR szFilename, bool bQuite = true);//int nSaveAs=40);

	IDispatch *GetActiveBook() { return m_pActiveBook; };
	IDispatch* GetSheet(int idx);
//	void SetItemData(EXCEL_SHEET *pXlSheet, vector<vector<float>> &xSeries, vector<vector<float>> &ySeries);

	HRESULT AddChart(LPCTSTR szTitle, int nLeft, int nTop, int nWidth, int nHeight, int nChartSheet,
		vector<wstring>& sNames, vector<vector<float>> &xSeries, vector<vector<float>> &ySeries);

	//HRESULT AddChartsheet(LPCTSTR szTitle, vector<wstring>& sNames, vector<vector<float>> &xSeries, vector<vector<float>> &ySeries);

	void InsertChart(wstring& sTitle, vector<wstring>& sNames, vector<vector<float>> &xSeries, vector<vector<float>> &ySeries);

	HRESULT SetVisible(bool bVisible);
	HRESULT Initialize(bool bVisible);


protected:
	int Init(void);

	CLSID m_clsid;
	EXCEL_APP *m_pApp;

	IDispatch*  m_pBooks;
	IDispatch*	m_pActiveBook;

};

//CWord接口类
class CWord
{
public:
	CWord(void) ;

	~CWord(void);

	int m_iError; //错误码：0--成功

	void Show(BOOL bShow=TRUE);  //显示
	WORD_DOCUMENTS *GetDocuments(void);					//获得文件集合
	WORD_DOCUMENT *AddDocument(const WORD_DOCUMENTS *pDocuments);		//增加一个文件
	WORD_DOCUMENT *OpenDocument(const WORD_DOCUMENTS *pDocuments, LPCTSTR filename);		// 打开一个文件
	WORD_DOCUMENT *GetActiveDocument(void);	//获得当前活动文档

	//通用参数设置，sVar为变量字符串，例如：wdApp.Selection.Font.Subscript = 1
	void SetValue(const CString &sVar,int iValue);
	void SetValue(const CString &sVar,CString &sValue);
	void SetValue(CString sVar,const VARIANT &Value);

	void SetFontName(const wchar_t *fontName);
	/*
	设置字号大小，fontSize--磅
	1磅≈0.35毫米
	1英寸＝72磅

	编号 字号	磅数
	1	大特号	63
	2	特号	54
	3	初号	42
	4	小初	36
	5	大一	31.5
	6	一号	28
	7	小一	24
	8	二号	21
	9	小二	18
	10	三号	16
	11	小三	15
	12	四号	14
	13	小四	12
	14	五号	10.5
	15	小五	9
	16	六号	8
	17	小六	6.875
	18	七号	5.25
	19	八号	4.5
	*/
	void SetFontSize(int fontSize);
	void SetFontBold(BOOL bBold);
	void SetFontItalic(BOOL bItalic);
	void SetFontUnderline(WORD_LINE_STYLE LineStyle);
	//删除线
	void SetFontStrikeThrough(BOOL bStrikeThrough);
	//下标
	void SetFontSubscript(BOOL bSubscript);
	//上标
	void SetFontSuperscript(BOOL bSuperscript);
	//背景色
	void SetBackColor(WORD_BACK_COLOR Color);
	//前景色
	void SetFontColor(COLORREF Color);
	//对齐
	void SetAlign(WORD_ALIGN ALignType);

	// 设置段落行距
	void SetLineSpaceRule(WORD_LINE_SPACE_RULE linespaceRule);

	//设置选中行的样式,stylename为样式名称
	void SetStyle(int style);
	void SetStyle(const wchar_t *stylename);
	//设置编号,pFormat--格式字符串，例如：L"%1)", L"(%1)",  L"<%1>"等，%1为变量，左右可任意添加符号
	void SetNumberFormat(WORD_NUMBER_STYLE  NumberStyle,const wchar_t *pFormat);
	//设置项目符号,bullet--字符
	void SetBulletFormat(const wchar_t *bullet);
	//清除项目符号或编号
	void RemoveListFormat(void);

	void Text(const wchar_t *str);

	void AddTable(int nRows,int nCols,const CString *sArray); //增加表格及数据

	void AddTableSTL(int nRows,int nCols,const wstring *sArray);	// cstring那个不能用
	void AddTableSTL(int nRows,int nCols, vector<std::wstring> sArray);

	//------------------
	// 回车
	void EnterCut(int nRow=1);
	// 移动光标,默认移动方向为向下
	void MoveCursor(WORD_MOVE_DIRECTION dire,WORD_MOVE_UNIT unit,int nCount,WORD_VAR_EXTEND eExtend=wdMove);
	void Move(WORD_MOVE_UNIT unit,int nCount);

	/*插入图片*/
	void InsertPic(const wchar_t *sFilePath, int width=-1, int height=-1);
	void InsertPic(const char *sFilePath);
	/*插入新页*/
	void NewPage();
	void NewColumn();
	/*分隔符*/
	void BreakNextPage();
	/*分栏*/
	void SetColumns(int nCol);
	// 行\文件等的位置最前面\末尾
	void Begin(WORD_MOVE_UNIT Unit=wdLine,WORD_VAR_EXTEND extend=wdMove);
	void End(WORD_MOVE_UNIT Unit=wdLine,WORD_VAR_EXTEND extend=wdMove);
	// delete 当前所选的（通过find来选）
	void Delete(WORD_MOVE_UNIT Unit=wdCharacter,int nCount=1);
	void Backspace(int nCount); // 往前删除
	// find f找到后处于选中状态
//	void Find(const char* sText,int pos=0);
	void Find(LPCTSTR sText,int pos=0);

//cmliu 0.1
//    ActiveWindow.ActivePane.View.Zoom.Percentage = 200
	void Zoom(long lPercentage);
	void PutCellValue(IDispatch* pWorksheet, int iRow, int iCol, float value);
	void InsertChart(LPCTSTR sTitle, int nWidth, int nHeight, vector<wstring> &sNames, vector<vector<float>> &xSeries, vector<vector<float>> &ySeries);
	void InsertFile(LPCTSTR sFilePath);
	void SetTextStyle(int nStyle);

	void InsertExcelFile(LPCTSTR sFilePath, int iWidth, int iHeight);
	void InsertExcelChart(LPCTSTR sTitle, int nWidth, int nHeight, vector<wstring>& sNames, vector<vector<float>> &xSeries, vector<vector<float>> &ySeries);

	void Activate();
	//保存文件
	void Save(void);
	//另存为文件，finaname--可以包含全路径
	void SaveAs(wchar_t *finaname);
	//关闭当前文档
	void Close(void);
	//退出Excel
	void Quit(void);

	//邱海 2018年3月12日
	// 设置段落段前
	void SetSpaceBefore(float fLinespace);
	// 设置段落段后
	void SetSpaceAfter(float fLinespace);
	//选中表格，一定紧跟在AddTable后
	void SelectTable();
	//设置表格格式
	void SetTableStyle();
	//将光标移动到指定位置的下一行
	BOOL InsertAt(const wchar_t *text,bool bForwardFind);
	//合并表格中相同内容单元格
	void MergeTable(int irow1,int icol1,int irow2,int icol2);
	//设置表格颜色
	void SetTableColor(int iRow1, int iCol1, int iRow2, int iCol2,COLORREF Color);
	//表头斜线格式
	void TableDiagonal();
protected:
	int Init(void);

	CLSID clsid;
	WORD_APP *pApp;

};
