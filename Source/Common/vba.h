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
	//0--���������֣�1-��д�������֣�2--Сд�������֣�3-��дӢ����ĸ��4--СдӢ����ĸ��
	//5--Ӣ�ļ�д���1st,2nd,...,  6--Ӣ������,  7--Ӣ����ţ�
	//18��28--���������ִ�ԲȦ��26--���������ֺ����,27--���������ִ���������, 29--�������ִ�ԲȦ
	//30-��ɣ�31-��֧��32-��֧��ϣ�33-����Сд���֣�34-���ִ�д���֣�
	//255-��
	//23--��Ŀ���ţ������������ֱ��
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
	wdCell=12,			// ��Ԫ�� 
	wdCharacter= 1,		// �ַ��� 
	wdCharacterFormatting= 13,		// �ַ���ʽ�� 
	wdColumn= 9,		// �С� 
	wdItem= 16 ,		//��ѡ� 
	wdLine= 5,			// һ���߶Ρ� 
	wdParagraph= 4,		// ���䡣 
	wdParagraphFormatting= 14, //�����ʽ�� 
	wdRow= 10,			// �С� 
	wdScreen= 7,		// ��Ļ�ߴ硣 
	wdSection= 8,		// һ�ڡ� 
	wdSentence =3,		// ���ӡ� 
	wdStory=6,			// ���֡� 
	wdTable=15,			// һ����� 
	wdWindow=11,		// ���ڡ� 
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
	wdLineSpace1pt5 = 1,	// 1.5 ���оࡣ���о��൱�ڵ�ǰ�ֺż� 6 ���� 
	wdLineSpaceAtLeast = 3,	// �о�����Ϊһ��ָ��ֵ����ֵ��Ҫ����ָ���� 
	wdLineSpaceDouble = 2,	// ˫���оࡣ 
	wdLineSpaceExactly = 4,	// �о�ֻ�������������оࡣ��������ʹ�õ��о�ͨ��С�ڵ����оࡣ 
	wdLineSpaceMultiple = 5,// ��ָ��������ȷ�����оࡣ 
	wdLineSpaceSingle = 0,	// �����о࣬Ĭ��ֵ�� 
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


//ͨ��VBA��������ַ����п�����%1��%2ָ���������ֱ��Ӧpparam1��pparam2
//������ActiveChart.SeriesCollection(%1).Name=%2
void ExeVBACmd(VBA_CMD_TYPE cmdType,VARIANT *pObj,const CString &sCmd,VARIANT *retVal,VARIANT *pparam1,VARIANT *pparam2);

//VBA����
void VBA_Get(VARIANT *retVal,VARIANT *pObj,const CString &sCmd,VARIANT *pparam1=NULL,VARIANT *pparam2=NULL);
void VBA_Put(VARIANT *pObj,const CString &sCmd,VARIANT *pparam1=NULL,VARIANT *pparam2=NULL);
void VBA_Method(VARIANT *pObj,const CString &sCmd,VARIANT *pparam1=NULL,VARIANT *pparam2=NULL);

//�����ַ�����VARIANT����
void SetStrValue(VARIANT *pVal,LPCTSTR pwstr);

//sArray[iRow*nCols+iCol]--����
void ToExcel(int nRows,int nCols,const CString *sArray,BOOL bChart,int ChartType,const CString &sTitle,
	const CString *pLegend,BOOL bTitleRow,BOOL bScaleLine=TRUE,int xFormat=0,int yFormat=0);
//20240227 Ϳ��� ����Ӧ��������excel
void ToExcelS(int nRows, int nCols, const CString* sArray, BOOL bChart, int ChartType, const CString& sTitle,
	const CString* pLegend, BOOL bTitleRow, BOOL bScaleLine = TRUE, int xFormat = 0, int yFormat = 0);
//psArray�����д洢��ÿ��psArray[i]��Ӧһ��sheet
void ToExcelM(int nRows,int nCols,const CString **psArray,const CString *pSheetName,int nSheet);

void ToExcelCSV(int nRows, int nCols, string *sArray, CString sPathFile, int nTotalCols=0);

void ToExcelM(int *pRows,int *pCols,const CString **psArray,const CString *pSheetName,int nSheet);

//Excel�ӿ���
class CExcel
{
public:
	CExcel(void) ;
	
	~CExcel(void);

	int m_iError; //�����룺0--�ɹ�

	void Show(BOOL bShow=TRUE);  //��ʾ
	EXCEL_WORKBOOKS *GetWorkBooks(void);					//����ļ�����
	EXCEL_WORKBOOK *AddBook(EXCEL_WORKBOOKS *pBooks);		//����һ���ļ�
	EXCEL_SHEETS *GetSheets(EXCEL_WORKBOOK *pBook);							//������ݱ���
	EXCEL_SHEET *GetActiveSheet(EXCEL_WORKBOOK *pBook);		//��õ�ǰ��
	EXCEL_WORKBOOK *AddSheet(EXCEL_WORKBOOK *pBook, const CString &sName=L"");
	int GetSheetsCount(EXCEL_SHEETS *pSheets);
	void RemoveSheet(EXCEL_WORKBOOK *pBook, int index);
	//����ͼ��
	void AddChart(EXCEL_SHEET *pSheet,int nRows,int nCols,const CString sTitle,
		const CString *pLegend,BOOL bTitleRow,BOOL bScaleLine,int xFormat,int yFormat,int ChartType=0);

	int GetCols(EXCEL_SHEET *pSheet); //�Զ���ȡ����

	//��������Array[iRow*nCols+iCol]
	void SetItemData(EXCEL_WORKBOOK *pXlBook,EXCEL_SHEET *pXlSheet,int nRows,int nCols,const int *iArray);
	void SetItemData(EXCEL_WORKBOOK *pXlBook,EXCEL_SHEET *pXlSheet,int nRows,int nCols,const float *fArray);
	void SetItemData(EXCEL_WORKBOOK *pXlBook,EXCEL_SHEET *pXlSheet,int nRows,int nCols,const CString *sArray);
	void Rename(VARIANT *pSheet,const CString &sSheetName);

	//�˳�Excel
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

//CWord�ӿ���
class CWord
{
public:
	CWord(void) ;

	~CWord(void);

	int m_iError; //�����룺0--�ɹ�

	void Show(BOOL bShow=TRUE);  //��ʾ
	WORD_DOCUMENTS *GetDocuments(void);					//����ļ�����
	WORD_DOCUMENT *AddDocument(const WORD_DOCUMENTS *pDocuments);		//����һ���ļ�
	WORD_DOCUMENT *OpenDocument(const WORD_DOCUMENTS *pDocuments, LPCTSTR filename);		// ��һ���ļ�
	WORD_DOCUMENT *GetActiveDocument(void);	//��õ�ǰ��ĵ�

	//ͨ�ò������ã�sVarΪ�����ַ��������磺wdApp.Selection.Font.Subscript = 1
	void SetValue(const CString &sVar,int iValue);
	void SetValue(const CString &sVar,CString &sValue);
	void SetValue(CString sVar,const VARIANT &Value);

	void SetFontName(const wchar_t *fontName);
	/*
	�����ֺŴ�С��fontSize--��
	1����0.35����
	1Ӣ�磽72��

	��� �ֺ�	����
	1	���غ�	63
	2	�غ�	54
	3	����	42
	4	С��	36
	5	��һ	31.5
	6	һ��	28
	7	Сһ	24
	8	����	21
	9	С��	18
	10	����	16
	11	С��	15
	12	�ĺ�	14
	13	С��	12
	14	���	10.5
	15	С��	9
	16	����	8
	17	С��	6.875
	18	�ߺ�	5.25
	19	�˺�	4.5
	*/
	void SetFontSize(int fontSize);
	void SetFontBold(BOOL bBold);
	void SetFontItalic(BOOL bItalic);
	void SetFontUnderline(WORD_LINE_STYLE LineStyle);
	//ɾ����
	void SetFontStrikeThrough(BOOL bStrikeThrough);
	//�±�
	void SetFontSubscript(BOOL bSubscript);
	//�ϱ�
	void SetFontSuperscript(BOOL bSuperscript);
	//����ɫ
	void SetBackColor(WORD_BACK_COLOR Color);
	//ǰ��ɫ
	void SetFontColor(COLORREF Color);
	//����
	void SetAlign(WORD_ALIGN ALignType);

	// ���ö����о�
	void SetLineSpaceRule(WORD_LINE_SPACE_RULE linespaceRule);

	//����ѡ���е���ʽ,stylenameΪ��ʽ����
	void SetStyle(int style);
	void SetStyle(const wchar_t *stylename);
	//���ñ��,pFormat--��ʽ�ַ��������磺L"%1)", L"(%1)",  L"<%1>"�ȣ�%1Ϊ���������ҿ�������ӷ���
	void SetNumberFormat(WORD_NUMBER_STYLE  NumberStyle,const wchar_t *pFormat);
	//������Ŀ����,bullet--�ַ�
	void SetBulletFormat(const wchar_t *bullet);
	//�����Ŀ���Ż���
	void RemoveListFormat(void);

	void Text(const wchar_t *str);

	void AddTable(int nRows,int nCols,const CString *sArray); //���ӱ������

	void AddTableSTL(int nRows,int nCols,const wstring *sArray);	// cstring�Ǹ�������
	void AddTableSTL(int nRows,int nCols, vector<std::wstring> sArray);

	//------------------
	// �س�
	void EnterCut(int nRow=1);
	// �ƶ����,Ĭ���ƶ�����Ϊ����
	void MoveCursor(WORD_MOVE_DIRECTION dire,WORD_MOVE_UNIT unit,int nCount,WORD_VAR_EXTEND eExtend=wdMove);
	void Move(WORD_MOVE_UNIT unit,int nCount);

	/*����ͼƬ*/
	void InsertPic(const wchar_t *sFilePath, int width=-1, int height=-1);
	void InsertPic(const char *sFilePath);
	/*������ҳ*/
	void NewPage();
	void NewColumn();
	/*�ָ���*/
	void BreakNextPage();
	/*����*/
	void SetColumns(int nCol);
	// ��\�ļ��ȵ�λ����ǰ��\ĩβ
	void Begin(WORD_MOVE_UNIT Unit=wdLine,WORD_VAR_EXTEND extend=wdMove);
	void End(WORD_MOVE_UNIT Unit=wdLine,WORD_VAR_EXTEND extend=wdMove);
	// delete ��ǰ��ѡ�ģ�ͨ��find��ѡ��
	void Delete(WORD_MOVE_UNIT Unit=wdCharacter,int nCount=1);
	void Backspace(int nCount); // ��ǰɾ��
	// find f�ҵ�����ѡ��״̬
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
	//�����ļ�
	void Save(void);
	//���Ϊ�ļ���finaname--���԰���ȫ·��
	void SaveAs(wchar_t *finaname);
	//�رյ�ǰ�ĵ�
	void Close(void);
	//�˳�Excel
	void Quit(void);

	//�� 2018��3��12��
	// ���ö����ǰ
	void SetSpaceBefore(float fLinespace);
	// ���ö���κ�
	void SetSpaceAfter(float fLinespace);
	//ѡ�б��һ��������AddTable��
	void SelectTable();
	//���ñ���ʽ
	void SetTableStyle();
	//������ƶ���ָ��λ�õ���һ��
	BOOL InsertAt(const wchar_t *text,bool bForwardFind);
	//�ϲ��������ͬ���ݵ�Ԫ��
	void MergeTable(int irow1,int icol1,int irow2,int icol2);
	//���ñ����ɫ
	void SetTableColor(int iRow1, int iCol1, int iRow2, int iCol2,COLORREF Color);
	//��ͷб�߸�ʽ
	void TableDiagonal();
protected:
	int Init(void);

	CLSID clsid;
	WORD_APP *pApp;

};
