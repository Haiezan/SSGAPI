#pragma once
#include "HeadDefine.h"

#include "SysPara.h"
#include "..\Common\DataDamper.h"


class CASCFile;

class _SSG_DLLIMPEXP CSemiRigidSection : public CDamperSection
{
public:
	//��������������
	CSemiRigidSection(void):bReletiveStiffness(false){}
	CSemiRigidSection(const CSemiRigidSection& sec) { nUsedCount = 0; *this = sec; }
	~CSemiRigidSection(void) { Clear(); }

	int bReletiveStiffness; // 0 ��ʾ��Ըն� 1��ʾ���Ըն�
	CSemiRigidSection& operator=(const CSemiRigidSection& sec) ;

	void Clear(void);
	BOOL Read(CASCFile& fin);
	void Write(CASCFile& fout);

};


//�����༯��
class _SSG_DLLIMPEXP CSemiRigidSectionCollection
{
public:
	CSemiRigidSectionCollection(void) { ; }
	~CSemiRigidSectionCollection(void) { Clear(); }

	CSemiRigidSectionCollection(const CSemiRigidSectionCollection& sec)
	{
		*this = sec;
	}

	CArray<CSemiRigidSection*, CSemiRigidSection*> aSemiRigidSectionPtr;  //��������ָ��
	int iMaxID;  //��ǰ�õ������ID

	CSemiRigidSection* GetSemiRigidSection(int id) const;  //���ݸ�����������id���ؽ���ָ��
	int GetIndex(int id) const;  //���ݸ�����������id��������,�Ҳ�������-1
	int* CreateIndex(void);  //����ID-->��ŵ��������飬���ó�����Ҫɾ���������鳤��ΪiMaxID+1
	void AppendSection(CSemiRigidSection* psec);  //�����½��棬�Զ���ȡID
	int GetSecNumByType(LINK_SUBTYPE iStrucType);// �õ�ͬ���ͽ�������� �� 2016��3��24��


	CSemiRigidSectionCollection& operator=(const CSemiRigidSectionCollection& sec)
	{
		if (this == &sec) return *this; //����ֵʱֱ�ӷ���

		Clear();
		for (int i = 0; i < sec.aSemiRigidSectionPtr.GetCount(); i++)
		{
			CSemiRigidSection* s1 = new CSemiRigidSection(*(sec.aSemiRigidSectionPtr[i]));
			//*s1=*sec.aBeamSectionPtr[i];
			aSemiRigidSectionPtr.Add(s1);  //���ﲻ����AppendSection�����ı�ID
			iMaxID = max(iMaxID, s1->id);  //��¼���ID
		}

		return *this;
	}
	int GetID(const CString& sName);
	void Clear();
	void Read(CASCFile& fin);
	void Write(CASCFile& fout);
	void Write2020(CASCFile& fout);
	void LoadDefaultLib(void);  //����ϵͳ��
	BOOL ExportSecProperty(int iType, CArray<int, int>& SecArr, CString*& pContents, int& nRows, int& nCols);
};
