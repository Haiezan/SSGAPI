#pragma once

#include "HeadDefine.h"
#include "..\Common\SysPara.h"
#include "ASCFile.h"
#include "..\Common\XYSect.h"
#include <afxtempl.h>
#include <afxwin.h>


////Ԥ����Ľ�����״����

#define gSectionMethodNum 10 // �ӹ̷����ĸ�����������5��
#define Sys_ReinForcedSubSectionShapeNum 10 //�ӹ̷������ӽ�����״����



//�ɼӹ̷���תΪ����������ϣ���ȡ����Ӧ����&����
extern "C" _SSG_DLLIMPEXP int GetStructTypeByMethod(REINFORCED_METHOD iReinForcedType);




//�߹��������� �ӹ�
class _SSG_DLLIMPEXP CBeamSectionReinForced
{
public:
	//��������������
	CBeamSectionReinForced(void) {
		pConcFibreBuf = pSteelFibreBuf = NULL;
		pConcFibre2Buf = NULL;
		Clear();
	}


	CBeamSectionReinForced(const CBeamSectionReinForced& sec)
	{
		pConcFibreBuf = pSteelFibreBuf = NULL; nUsedCount = 0;
		pConcFibre2Buf = NULL;
		*this = sec;
	}

	~CBeamSectionReinForced(void) { Clear(); }

	//��������
	int id;  //����ID
	CString sName;  //��������,���������ý����������ԣ�һ���������Ʊ��Ķ�������ݸĶ�ǰ��Ķ�Ӧ��ϵ�滻������
	SECTION_MAT_TYPE iMatType;		//����������ʹ���
	REINFORCED_METHOD iReinForcedMethod;	//�ӹ̷���,ģ��ID
	//CArray<CSubSectionReinForced,CSubSectionReinForced&> aSubSecReinForced; //�ӽ�������


	COLORREF dwColor; //��ʾ��ɫ, ���ڿ���Ѱ��



	//��������ֵ����,�־����ݣ����浽�ļ����û���������������޸ģ��޸Ľ���ʱ����GetFeatures���м���
	enum { BEAMSECTION_PARA = 12 };	//����������������
	float ConcArea, SteelArea;			//���������,�ֲ����(������������ʼ���ĸֽ��ͬ)
	float ConcShearArea2, SteelShearArea2;	//2���򿹼����
	float ConcShearArea3, SteelShearArea3;	//3���򿹼����
	float ConcI2, SteelI2;			//2����ת����������Ӧ����M2����
	float ConcI3, SteelI3;			//3����ת����������Ӧ����M3����
	float ConcJ1, SteelJ1;			//1����ת�������������Ծأ���ӦŤ��M1

	//��ʱ����,�����浽�ļ�,��ȡ���桢�޸Ľ���ʱ���޸���ά���Ʋ���ʱ����GetFibres����
	float fWidth, fHeight; //��ȷ�Χ,�߶ȷ�Χ������������ʾ����Χ�ⶨ��δ����ת�ǣ���Ϊת���ǹ������ԣ����ǽ�������
	int nConcFibre, nStructSteelFibre;  //��������ά����������ά�������������ֽ
	BEAM_FIBRE_GEO* pConcFibreBuf, * pSteelFibreBuf;   //��������ά���飬����ά���飨�������ֲ��ֽ��������Ե�����ĸֽ�����

	BEAM_FIBRE_GEO* pConcFibre2Buf;		//��ʱʹ�����ַ�ʽ��

	int nUsedCount;  //������ʹ�õĴ�����һ��Ҫ�ȼ�����ʹ��,��ʱ����

	//����ģ�崴�����棬���ԭ������
	BOOL CreateSectionByTemplete(REINFORCED_METHOD iMethod);

	//�����������ֵ�������޸ĺ���е���
	void GetFeaturesReinForced(void);


	//���¼������ߴ�fWidth,fHeight�����ڻ�ͼ
	void GetMaxSize(BOOL bDiagram); // bDiagram��Ҫ���������� �ӹ̽�����Ϣ������������ͼ

	//���ݽ������������Զ��������
	CString& AutoName(void);


	//�ж��ǲ���ĳ���ͽṹ�Ŀ��ý���
	int IsUsable(STRUCT_TYPE iType);
	STRUCT_TYPE GetType(); //�õ��ý���Ľṹ����

	CBeamSectionReinForced& operator=(const CBeamSectionReinForced& sec);
	BOOL operator==(const CBeamSectionReinForced& sec) const;
	BOOL operator!=(const CBeamSectionReinForced& sec) const;

	void Clear(void);

	float DrawSection(CDC* pDC, BOOL bGrid, BOOL bFibre, const CRect& re, BOOL bDiagram);  //������Ͻ���,���ػ��Ʊ���

	BOOL Read(CASCFile& fin);
	void Write(CASCFile& fout);


	float Original_p2; // �ӹ̽��������
	float Original_p3;  // �ӹ̽��������

	void GenerateReinforceSec(CBeamSection*& pSec, const CBeamSection* pSec0);
	BOOL bReinforceConc();
	BOOL bReinforceFiber();
	float GetSteelArea(float& areaB, float& areaT);
	float GetFiberThick(float& fwide, float& Dis);
	float GetConcArea(const CBeamSection* pSec);
	float GetBeamRebarArea(const CBeamSection* pSec0);
	float GetPillarRebarArea(const CBeamSection* pSec0, float& fCorner);//fCorner--�ǽ������������,��λ��m^2�����޷�ȷ���ǽ��0


public:
	//��Ա����--------------------
	SUBSECTION_REINFORCED_TYPE iMethod;	//�ӹ̷�������
	SUBSECTION_MAT_TYPE iSubMatType; //�ӽ���������ͣ����������͸ֵȵ�һ����,�����ǻ�ϲ��ϣ�

	CString sConcGrade; //�������ȼ�
	CString sRebarGrade; //�ֽ�ȼ�
	CString sSteelModel; //�ֲ��ͺ�
	float fRatioB, fRatioH;  //����ʣ��ӹ��������׽�ӹ�����б�ţ�B��H����ĵ�������ʣ������ǽ,��λ���ٷ���
	float fStirArea; // ���������


	//�ӹ̷����ļ��β���
	union
	{
		// ���ӹ̷���
		struct BEAM_ENLARGED_SECTION beam_enlarge_section;
		struct BEAM_DISPLACEMENT_CONCRETE beam_displacement_concrete;
		struct BEAM_WRAPPED_SECTION_STEEL beam_wrapped_section_steel;
		struct BEAM_PASTE_STELL_PLATE beam_paste_steel_plate;
		struct BEAM_PASTE_FIBER beam_paste_fiber;

		// ���ӹ̷���
		struct PILLAR_ENLARGED_SECTION pillar_enlarge_section;
		struct PILLAR_DISPLACEMENT_CONCRETE pillar_displacement_concrete;
		struct PILLAR_WRAPPED_SECTION_STEEL pillar_wrapped_section_steel;
		struct PILLAR_PASTE_STELL_PLATE pillar_paste_steel_plate;
		struct PILLAR_PASTE_FIBER pillar_paste_fiber;

		float fValue[Sys_SubSectionParaNum];  //��λ����
	};
	int nValue;		//2020�汾 ���� nPara��
	float p2, p3;	//�ӽ���2��3�����ƫ�ľࣨm�����ӽ������ĵ���Ͻ���ֲ�����ԭ��ľ��룬��Ͻ�������ԭ��ѡ��������ε����ĵ�

	float angle;

	//��ʱ����
	float m_Area;
	float m_shearArea2;
	float m_shearArea3;
	float m_I2;
	float m_I3;
	float m_J1;



	//����������γߴ�
	void GetRectSize(float& fWidth, float& fHeight);
	float Area(void); //����������
	float ShearArea2(void); //����2������Ч�������
	float ShearArea3(void); //����3������Ч�������

	void CalcI2I3(float& I2, float& I3);
	float J1(void);  //Ťת���Ծأ��������Ͻ���ľֲ�����ԭ�㣬����Ҫ��������ƫ�ľ�

	void RotateProperty(float Iy, float Iz, float Iyz, float alpha, float& Iy1, float& Iz1, float& Iyz1);


	float Original_B;  // �����ʼ���ĳߴ�
	float Original_H;  // �����ʼ���ĳߴ�

	//��ʱ����
	float Temp_Original_B;  // ���ڼӹ̽���Ի���ߴ���ʾ����
	float Temp_Original_H;  // ���ڼӹ̽���Ի���ĳߴ���ʾ����

	void CreatBeamSectionReinForcedParameter(SUBSECTION_REINFORCED_TYPE imethod, SUBSECTION_MAT_TYPE isectype);

};


//�����༯��
class _SSG_DLLIMPEXP CSectionCollectionReinForced
{
public:
	CSectionCollectionReinForced(void) { ; }
	~CSectionCollectionReinForced(void) { Clear(); }


	CSectionCollectionReinForced(const CSectionCollectionReinForced& sec)
	{
		*this = sec;
	}

	CArray<CBeamSectionReinForced*, CBeamSectionReinForced*> aBeamSectionReinForcedPtr;  //��������ָ��
	int iMaxID;  //��ǰ�õ������ID

	int GetID(int iStrucType, const CString& sName, bool bIndep = false);  //���ݽṹ���ͺͽ������ƻ�ý���ID,�Ҳ�������-1 bIndep�Ƿ񰴹����������
	int GetShowId(int iStrucType, int id);//���ݽṹ���ͺͽ����ŵõ������Ͷ�����ţ������ŷֱ��1��ʼ���ֻ������ʾ
	int GetIDByShowId(int iStrucType, int id);//���ݽṹ���ͺͽ��������ŵõ�����ID
	int GetIndex(int id) const;  //���ݸ�����������id��������,�Ҳ�������-1
	CBeamSectionReinForced* GetBeamSectionReinForced(int id) const;  //���ݸ�����������id���ؽ���ָ��

	int* CreateIndex(void);  //����ID-->��ŵ��������飬���ó�����Ҫɾ���������鳤��ΪiMaxID+1
	int GetSecID(const CBeamSectionReinForced* pSec);//���ҽ���ID �Ҳ�������-1

	void AppendSection(CBeamSectionReinForced* psec);  //�����½��棬�Զ���ȡID


	CSectionCollectionReinForced& operator=(const CSectionCollectionReinForced& sec)
	{
		if (this == &sec) return *this; //����ֵʱֱ�ӷ���

		Clear();
		for (int i = 0; i < sec.aBeamSectionReinForcedPtr.GetCount(); i++)
		{
			CBeamSectionReinForced* s1 = new CBeamSectionReinForced(*(sec.aBeamSectionReinForcedPtr[i]));
			aBeamSectionReinForcedPtr.Add(s1);  //���ﲻ����AppendSection�����ı�ID
			iMaxID = max(iMaxID, s1->id);  //��¼���ID
		}

		return *this;
	}

	void Clear();

	void Read(CASCFile& fin);
	void Write(CASCFile& fout);

};

//�ӹ̽�����״���Ա�
struct  SECTION_METHOD_PROP_TABLE
{
	REINFORCED_METHOD iMethod;  //�ӹ̷���ģ��ID
	CString sName;   //��״ģ������
	SECTION_MAT_TYPE iType;  //��������
	SUBSECTION_SHAPE subshape[2]; //��Ӧ���ӽ�����
};

static SECTION_METHOD_PROP_TABLE gSectionMethodTable[gSectionMethodNum] =
{
	BEAM_METHOD_ENLARGED_SECTION	,	L"��������淨",SECTION_MAT_TYPE_RC,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	BEAM_METHOD_DISPLACEMENT_CONCRETE,	L"���û���������",SECTION_MAT_TYPE_RC,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	BEAM_METHOD_WRAPPED_SECTION_STEEL,	L"������͸ַ�",SECTION_MAT_TYPE_ST,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	BEAM_METHOD_PASTE_STELL_PLATE	,	L"�������ְ巨",SECTION_MAT_TYPE_ST,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	BEAM_METHOD_PASTE_FIBER	,			L"��������ά��",SECTION_MAT_TYPE_ST,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,

	PILLAR_METHOD_ENLARGED_SECTION		,	L"��������淨",SECTION_MAT_TYPE_RC,			SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	PILLAR_METHOD_DISPLACEMENT_CONCRETE,	L"���û���������",SECTION_MAT_TYPE_RC,			SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	PILLAR_METHOD_WRAPPED_SECTION_STEEL,	L"������͸ַ�",SECTION_MAT_TYPE_ST,			SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	PILLAR_METHOD_PASTE_STELL_PLATE	,		L"�������ְ巨",SECTION_MAT_TYPE_ST,			SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	PILLAR_METHOD_PASTE_FIBER,				L"��������ά��",SECTION_MAT_TYPE_ST,			SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN
};

struct _SSG_DLLIMPEXP REINFORCED_SUBSECTION_METHOD_PROP_TABLE
{
	SUBSECTION_REINFORCED_TYPE iMethod;	//�ӹ̷���
	CString sName;				//��������
	int nPara;					//��������
	CString sParaName[Sys_SubSectionParaNum]; //��������
};


extern "C" _SSG_DLLIMPEXP REINFORCED_SUBSECTION_METHOD_PROP_TABLE aSubMethodPropTable[Sys_ReinForcedSubSectionShapeNum];
extern "C" _SSG_DLLIMPEXP REINFORCED_SUBSECTION_METHOD_PROP_TABLE * FindMethodPropByID(SUBSECTION_REINFORCED_TYPE id);




