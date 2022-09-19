// VideoLib.h : VideoLib DLL ����ͷ�ļ�
//

#pragma once

#include <VFW.h>


class __declspec (dllexport) CVideoLib
{
public:
	CVideoLib();
	~CVideoLib();

public:
	wchar_t m_szFile[MAX_PATH];
	BOOL m_bOpenGL;
	HWND m_hwnd,m_hwndTimerProc;
	PAVISTREAM m_pavi;
	int m_iFrameCount;
	BYTE *m_pBmpBits;
	int m_iWidth;
	int m_iHeight;
	int m_nSize;
	HDC m_hMemDC;
	HDC m_hSrcDC;
	int m_iRate;
	BOOL m_bCapCursor;

	PAVIFILE m_pfile;
	PAVISTREAM m_psCompressed;
	HBITMAP m_hOldBmp,m_hBmp;
	RECT m_rc; //¼�ƴ��ڵ���Ļ����

public:

	//����Ƶ��׷�ӵ�szFile�ļ�
	int StartSaveAVI(HWND hwnd,LPCTSTR szFile,BOOL bCapCursor,int iRate,BOOL bOpenGL,HWND hwndTimerProc);
	void EndSaveAvi(void);

	int GetFrameCount(void) {return m_iFrameCount;}
	int GetFrameTime(void) {return m_iFrameCount*m_iRate;}

	BOOL AVItoBmp(const wchar_t *strAVIFileName, const wchar_t *strBmpDir,int iStartFrame,
		int iEndFrame,int iFrameInc);
private:
	//����м����ݣ���StartSaveAVI����
	void Clear();

};

//�ɼ�ʱ������
VOID CALLBACK SaveOneFrame(HWND hwnd,UINT message,UINT idTimer,DWORD dwTime);
