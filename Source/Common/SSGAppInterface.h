#pragma once
#include "stdafx.h"
#include "HeadDefine.h"

//#define interface struct

interface ISSGApp
{
public:
	virtual BOOL IsZY() = 0;
	virtual BOOL IsCheck() = 0; 
	virtual BOOL IsDog() = 0; 
	virtual BOOL IsPI() = 0; 
	virtual BOOL IsPD() = 0; 
	virtual BOOL IsSteel() = 0; 
	virtual BOOL IsOpen() = 0; 
	virtual void OutputText(LPCTSTR str) = 0;
	virtual void Outputmsgfile(LPCTSTR fname) = 0;
	virtual CString CaseShowName(CString sCase) = 0;
	virtual BOOL IsBatch() = 0;
};

extern "C" 
{
	__declspec(dllexport) ISSGApp* GetIterface();
};