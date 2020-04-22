#pragma once

#include "..\common\vba.h"

//-----------------------------------
//AutoWrap的调用参数是倒序的，例如：
//VARIANT parm[3];
//parm[0].vt = VT_I4; parm[0].lVal = 1;
//parm[1].vt = VT_I4; parm[1].lVal = 2;
//parm[2].vt = VT_I4; parm[2].lVal = 3;
//AutoWrap(DISPATCH_METHOD, NULL, pDisp, L"call", 3, parm[2], parm[1], parm[0]);
HRESULT AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs...);

//pPara数据要倒序，即parm3、parm2、parm1、parm0
HRESULT AutoWrap1(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs,VARIANT *pPara);

//自动解析并执行宏命令
class CCmdPara
{
public:
	CCmdPara(void)
	{
		nObj=0;
	};

	~CCmdPara()
	{
		Clear();
	};

	void Clear(void)
	{
		for (int i=0;i<nObj;i++)
		{
			CArray<VARIANT,VARIANT> *pPara=pParaArray[i];
			//for (int j=0;j<pParaArray[i]->GetCount();j++)
			//{
			//	VariantClear(&(pPara->GetAt(j)));
			//}
			pPara->RemoveAll();
			delete pPara;
			pParaArray[i]=NULL;
		}
		nObj=0;
	};

	CArray<VARIANT,VARIANT> *GetParaPtr(int index)
	{
		if(nObj==0) return NULL;
		if(index<0) index=0;
		if(index>=nObj) index=nObj-1;
		return pParaArray[index];
	}

	CArray<VARIANT,VARIANT> *GetLastParaPtr(void)
	{
		return GetParaPtr(nObj-1);
	}


	void AddPara(CArray<VARIANT,VARIANT> *p)
	{
		pParaArray[nObj]=p;
		nObj++;
	}

private:
	int nObj;
	CArray<VARIANT,VARIANT> *pParaArray[64];
};


//通用VBA命令
void ParseVBACmd(CString sCmd,CStringArray &aObj,CCmdPara &cPara,VARIANT *pparam1,VARIANT *pparam2);

double GetDouble(const VARIANT &v1);
double operator-(const VARIANT &v1,const VARIANT &v2);  //两个variant变量值相减得到double值

void SetExcelItemData(EXCEL_WORKBOOK *pXlBook, EXCEL_SHEET *pXlSheet, vector<vector<float>> &xSeries, vector<vector<float>> &ySeries);
HRESULT AddChartsheet(IDispatch *pBook, IDispatch *pSheet, LPCTSTR szTitle, vector<wstring>& sNames, vector<vector<float>> &xSeries, vector<vector<float>> &ySeries);

