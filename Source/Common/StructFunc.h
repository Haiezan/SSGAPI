#pragma once

extern _PUB_DLLIMPEXP CString GetStructName(int iStructType,BOOL b2ndBeam=FALSE);  
extern _PUB_DLLIMPEXP CString GetLinkName(int iSubType);
extern _PUB_DLLIMPEXP void SaveGDIImage(CWnd *pWnd,RECT *rect=NULL);  //±£´æGDIÍ¼Ïñ

//extern CString theAppVersion;

//BOOL theAppIsZY();
//BOOL theAppIsDog();

//BOOL theAppIsPD();
//BOOL theAppIsSteel();
//BOOL theAppIsCheck();
//CString theAppCaseShowName(CString sCase);

//BOOL theAppIsPI();
//extern "C" _PUB_DLLIMPEXP void SetAppVersion(CString version);

extern "C" _PUB_DLLIMPEXP void  MySetPaneText(int pos, LPCTSTR str);
extern "C" _PUB_DLLIMPEXP void  MySetOutputText(LPCTSTR str);

extern _PUB_DLLIMPEXP void SplitCString(CString sInput, CString sDelim, CString& sLeft, CString& sRight);
extern "C" _PUB_DLLIMPEXP BOOL DivideCmdLine(CString strCmd,CString& sPath,CString& sProName,CString& sType,CString& sEvent);
int DivideCmd(CStringArray &arCmd);

#include <vector>
#include <string>

extern _PUB_DLLIMPEXP std::vector<std::wstring> TokenString(wchar_t* string1, wchar_t *seps=L" ,");//\t\n");

extern "C" _PUB_DLLIMPEXP void BeginWaitCursor();
extern "C"_PUB_DLLIMPEXP void EndWaitCursor();