#pragma once
#include "HeadDefine.h"
#include "ASCFile.h"
#include "SysPara.h"
#include "Load.h"
#include <map>

using namespace std;

//�ṹ���湤������������
class _SSG_DLLIMPEXP PARASSIGN
{
public:
	PARASSIGN()
	{
		loadData = NULL;
		numLoad = 0;
	}
	~PARASSIGN()
	{
		clear();
	}
	void clear();
	BOOL  inline IsEmpty()const { return numLoad == 0 || loadData == NULL; };
	PARASSIGN& operator=(const PARASSIGN& lm);
	bool operator!=(const PARASSIGN& lm) const;

	int inline GetLoadCount() const { return numLoad; };

	BOOL DeleteLoad(int iLC);
	BOOL AppendLoad(int iLC, const float* pData);
	BOOL ReorderLoad(int iLC, int iNew);
	BOOL RemoveLoad(int iLC);
	BOOL SetLoad(int iLC, float* pData);
	float* GetLoad(int iLC);
	BOOL AddLoad(float* pData);
	BOOL AddLoad(float DynLoad, float Type);

	CString GetShowText(int iLC);
	int GetBlastType(int iLC);

	void Read(CASCFile& fin);
	void Write(CASCFile& fout, int& index, int id);
private:
	int numLoad;  //��������
	float** loadData; //����������
	static int nData; //ÿ���������ݸ���
};

