#pragma once
#include "PublicFunc_MFC.h"
#include "ASCFile.h"
#include <vector>

#include "StaticLoadCase.h"

//������ʼȱ�ݹ���
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

	CString m_sCaseName; //����
	CString m_sMemo; //˵��
	int m_nMode; //�ܽ���
	BOOL m_bOverallDefect; //�Ƿ�������ȱ��
	int m_iOverallDefect;
	BOOL m_bMemberDefect; //�Ƿ��ǹ���ȱ��
	int m_iMemberDefect;

	unsigned int m_iAnalysisPara; //������Ʋ��� 0x01 ���˸�����ֵ
	void SetIsRemoveEigen(BOOL bFlag) { if (bFlag) m_iAnalysisPara |= 0x01; else m_iAnalysisPara &= ~0x01; }
	BOOL IsRemoveEigen()	const { return m_iAnalysisPara & 0x01 ? TRUE : FALSE; }

	vector<CombData> m_vConstComb; //������ع���
	vector<CombData> m_vVaryComb; //�ɱ���ع���

	void Read(CASCFile& fin);
	void Write(CFile& fout);

	float GetProgress(); //�������
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
	CArray<CBucklingCase*, CBucklingCase*> aCasePtr; //��ʼȱ�ݹ�������
};