#pragma once

#include "HeadDefine.h"
#include <afxtempl.h>
#include "SSGAppInterface.h"

//������ڼ�����λ�Ƶ����Ӳ�߳��Ͻ����Ϣ���������ӡ���Ե������������б��
//�ļ���ʽ��
//����  ������
//���  ����1����(��1��ʼ)  ����2����(��1��ʼ)  ...
extern "C" _SSG_FEADLL void WriteColumnInfo(const CString & fname, int Sty_Col_Num, const int* Sty_Col_id, const int* Sty_Col_Type, BOOL bUser = FALSE, float fAngle = 0); // bUser ��float �����Զ���
extern "C" _SSG_FEADLL void SetDriftElm();

class CSSGFeaInterface/* : public CCmdTarget*/
{
public:
	virtual void InitialApp(ISSGApp* theExeApp) = 0;
	virtual void SetMultiGPU(bool bMultiGPU) = 0;
	virtual int Run(BOOL bShutdown = FALSE) = 0;
	virtual void SetISORun(CArray<int, int>& runCase) = 0;//��������Ǹ���Ǽ���ģ�ͼ���
	virtual ~CSSGFeaInterface() = 0;
public:
	BOOL m_bShutdown;  //����ʱ�ػ�
	BOOL m_bSilence;
	BOOL m_bExpShape;
	BOOL m_bSecondCalIsoBeta;
	BOOL m_bSecondCalElastic;
	RUN_CASE iRunCase;

	CLoadCollection m_cLoad;
	CArray<int, int> m_aRunCase;//2016.1.28
};

extern "C" _SSG_FEADLL CSSGFeaInterface* GetFeaInterface();