// VideoLib.h : VideoLib DLL 的主头文件
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
	RECT m_rc; //录制窗口的屏幕坐标

public:

	//将视频流追加到szFile文件
	int StartSaveAVI(HWND hwnd,LPCTSTR szFile,BOOL bCapCursor,int iRate,BOOL bOpenGL,HWND hwndTimerProc);
	void EndSaveAvi(void);

	int GetFrameCount(void) {return m_iFrameCount;}
	int GetFrameTime(void) {return m_iFrameCount*m_iRate;}

	BOOL AVItoBmp(const wchar_t *strAVIFileName, const wchar_t *strBmpDir,int iStartFrame,
		int iEndFrame,int iFrameInc);
private:
	//清除中间数据，被StartSaveAVI调用
	void Clear();

};

//由计时器触发
VOID CALLBACK SaveOneFrame(HWND hwnd,UINT message,UINT idTimer,DWORD dwTime);
