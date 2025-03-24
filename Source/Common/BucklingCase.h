#pragma once
#include "PublicFunc_MFC.h"
#include "ASCFile.h"
#include <vector>

#include "StaticLoadCase.h"

//构件初始缺陷工况
class _SSG_DLLIMPEXP CBucklingCase
{
public:
	CBucklingCase(void);
	CBucklingCase(CBucklingCase& lc)
	{
		*this = lc;
	}
	~CBucklingCase() {};

	CBucklingCase& operator=(const CBucklingCase& lc);

	CString m_sCaseName; //名称
	CString m_sMemo; //说明
	int m_nMode; //总阶数
	BOOL m_bOverallDefect; //是否考虑整体缺陷
	int m_iOverallDefect;
	BOOL m_bMemberDefect; //是否考虑构件缺陷
	int m_iMemberDefect;

	unsigned int m_iAnalysisPara; //计算控制参数 0x01 过滤负特征值
	void SetIsRemoveEigen(BOOL bFlag) { if (bFlag) m_iAnalysisPara |= 0x01; else m_iAnalysisPara &= ~0x01; }
	BOOL IsRemoveEigen()	const { return m_iAnalysisPara & 0x01 ? TRUE : FALSE; }

	vector<CombData> m_vConstComb; //不变荷载工况
	vector<CombData> m_vVaryComb; //可变荷载工况

	void Read(CASCFile& fin);
	void Write(CFile& fout);

	float GetProgress(); //计算进度
};

class _SSG_DLLIMPEXP CBucklingCaseCollection
{
public:
	CBucklingCaseCollection() { ; };
	CBucklingCaseCollection(const CBucklingCaseCollection& lc)
	{
		*this = lc;
	};
	~CBucklingCaseCollection() { RemoveAll(); }

	int Append(CBucklingCase* load);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const { return aCasePtr.GetCount(); }

	CBucklingCase* GetAt(int i) { return aCasePtr.GetAt(i); }

	CBucklingCase* operator[](int i) { return aCasePtr[i]; }

	void SetAt(int i, CBucklingCase* load) { aCasePtr[i] = load; }

	CBucklingCaseCollection& operator=(const CBucklingCaseCollection& load);

	void Write(CFile& fout)
	{
		for (int i = 0; i < aCasePtr.GetCount(); i++)
			aCasePtr[i]->Write(fout);
	}

private:
	CArray<CBucklingCase*, CBucklingCase*> aCasePtr; //初始缺陷工况集合
};