
// ReadSSG.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CReadSSGApp:
// �йش����ʵ�֣������ ReadSSG.cpp
//

class CReadSSGApp : public CWinApp
{
public:
	CReadSSGApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CReadSSGApp theApp;