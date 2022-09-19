#pragma once
#include "..\common\PubDefs.h"

//char* _CHS(const char* chs, const char* eng="");
//wchar_t* _CHSL(const wchar_t* chs, const wchar_t* eng=L"");

extern "C" _PUB_DLLIMPEXP  char* _CHS(const char* chs, const char* eng="");
extern "C" _PUB_DLLIMPEXP  wchar_t* _CHSL(const wchar_t* chs, const wchar_t* eng=L"");