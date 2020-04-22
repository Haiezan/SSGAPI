
#pragma once


#ifndef DLLEXPORT_MY  
#define DLLAPI  __declspec(dllimport)
#else
#define DLLAPI __declspec(dllexport)
#endif 
//#include "afxwin.h"


/*
sPath为工程工作路径
sProName为工程名（SSG文件名，不含扩展名）
*/
int  DLLAPI WriteReport(const char* sPath,const char* sProName);
