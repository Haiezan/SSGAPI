
#pragma once


#ifndef DLLEXPORT_MY  
#define DLLAPI  __declspec(dllimport)
#else
#define DLLAPI __declspec(dllexport)
#endif 
//#include "afxwin.h"


/*
sPathΪ���̹���·��
sProNameΪ��������SSG�ļ�����������չ����
*/
int  DLLAPI WriteReport(const char* sPath,const char* sProName);
