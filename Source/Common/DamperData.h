#pragma once
#include "HeadDefine.h"
#include "Vector4.h"
#include "Matrix4x4.h"
//#include "SysPara.h"
#include "PublicFunc.h"
#include "PublicFunc_MFC.h"


#include "ASCFile.h"
#include "UserDefine.h"


#include <afxtempl.h>
#include <vector>
//#include <algorithm>
//#include <functional>
#include "Data.h"

using namespace std;

//һ�����ӹ���������
class _SSG_DLLIMPEXP CDamperSection
{
public:
	//��������������
	CDamperSection(void) { Clear();}
	CDamperSection(const CDamperSection &sec)	{ nUsedCount=0; *this=sec; }
	~CDamperSection(void) { Clear(); }

	//��������
	int id;  //����ID
	CString sName;  //��������,���������ý����������ԣ�һ���������Ʊ��Ķ�������ݸĶ�ǰ��Ķ�Ӧ��ϵ�滻������
	LINK_SUBTYPE iSectionType;	//
	int iSubType; //����
	COLORREF dwColor; //��ʾ��ɫ, ���ڿ���Ѱ��
	//��������ֵ����,�־����ݣ����浽�ļ����û���������������޸ģ��޸Ľ���ʱ����GetFeatures���м���
	enum {DAMPERSECTION_PARA=48};	//�����������������޸� �� 2016��3��29��
	float fDamperSecPara[DAMPERSECTION_PARA];
	float fMass;
	enum {DAMPERDESIGN_PARA=28};	//��Ʋ���
	float fDamperDesPara[DAMPERDESIGN_PARA];


	//��ʱ����,�����浽�ļ�,��ȡ���桢�޸Ľ���ʱ���޸���ά���Ʋ���ʱ����GetFibres����
	int nUsedCount;  //������ʹ�õĴ�����һ��Ҫ�ȼ�����ʹ��,��ʱ����
	//���ݽ������������Զ��������
	
	CDamperSection & operator=(const CDamperSection &sec);
	void Clear(void);
	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
	CString sTypeName(); //�õ������������� �� 2016��6��15��
	void CheckParameter();//������������Բ��� �� 2017��1��12��
	//�����Ϣ��д
	BOOL ReadDesignInfo(CASCFile &fin);
	void WriteDesignInfo(CASCFile &fout);
};


//�����༯��
class _SSG_DLLIMPEXP CDamperSectionCollection
{
public:
	CDamperSectionCollection(void){;}
	~CDamperSectionCollection(void){Clear();}

	CDamperSectionCollection(const CDamperSectionCollection &sec)
	{
		*this=sec;
	}

	CArray<CDamperSection*,CDamperSection*> aDamperSectionPtr;  //��������ָ��
	int iMaxID;  //��ǰ�õ������ID

	CDamperSection *GetDamperSection(int id) const;  //���ݸ�����������id���ؽ���ָ��
	int GetIndex(int id) const;  //���ݸ�����������id��������,�Ҳ�������-1
	int *CreateIndex(void);  //����ID-->��ŵ��������飬���ó�����Ҫɾ���������鳤��ΪiMaxID+1
	void AppendSection(CDamperSection *psec);  //�����½��棬�Զ���ȡID
	int GetSecNumByType(LINK_SUBTYPE iStrucType);// �õ�ͬ���ͽ�������� �� 2016��3��24��


	CDamperSectionCollection & operator=(const CDamperSectionCollection &sec)
	{
		if(this==&sec) return *this; //����ֵʱֱ�ӷ���

		Clear();
		for(int i=0;i<sec.aDamperSectionPtr.GetCount();i++) 
		{
			CDamperSection *s1=new CDamperSection(*(sec.aDamperSectionPtr[i]));
			//*s1=*sec.aBeamSectionPtr[i];
			aDamperSectionPtr.Add(s1);  //���ﲻ����AppendSection�����ı�ID
			iMaxID=max(iMaxID,s1->id);  //��¼���ID
		}

		return *this;
	}
	int GetID(const CString &sName);
	void Clear();
	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void LoadDefaultLib(void);  //����ϵͳ��

};

