#pragma once
#include "HeadDefine.h"
#include "ASCFile.h"
#include "SectionBase.h"
#include "..\Common\SysPara.h"

#define gPlateSectionMethodNum 5 // ǽ��ӹ̷����ĸ�������3����ǽ2��
#define Sys_PlateReinForcedSectionShapeNum 5 //ǽ��ӹ̷���������״����


//�ɼӹ̷���תΪ����������ϣ���ȡ����Ӧ����&����
extern "C" _SSG_DLLIMPEXP int GetStructTypeByPlateMethod(PLATE_REINFORCED_METHOD iMethod);


//�湹��������
class _SSG_DLLIMPEXP CPlateSectionReinforced
{
public:
	//��������������
	CPlateSectionReinforced(void)
		: id(0)
		, sName(L"")
		, iPlateMatType(PALTESECTION_REINFORCED_MAT_TYPE_CONC)
		, dwColor(0)
		, nUsedCount(0)
	{
	}
	CPlateSectionReinforced(const CPlateSectionReinforced &sec)	{nUsedCount=0; *this=sec; }
	~CPlateSectionReinforced(void) { Clear(); }

	//��������
	int id;  //����ID
	CString sName;  //��������,���������ý����������ԣ�һ���������Ʊ��Ķ�������ݸĶ�ǰ��Ķ�Ӧ��ϵ�滻������

	PALTESECTION_REINFORCED_MAT_TYPE iPlateMatType;

	COLORREF dwColor; //��ʾ��ɫ, ���ڿ���Ѱ��
	int nUsedCount;  //������ʹ�õĴ�����һ��Ҫ�ȼ�����ʹ��,��ʱ����

	void Clear(void);

	CPlateSectionReinforced & operator=(const CPlateSectionReinforced &sec);
	BOOL operator==(const CPlateSectionReinforced &sec) const;
	BOOL operator!=(const CPlateSectionReinforced &sec) const;

	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);


	//���¼������ߴ�fWidth,fHeight�����ڻ�ͼ
	void GetMaxSize(); // bDiagram��Ҫ���������� �ӹ̽�����Ϣ������������ͼ
	float DrawPlateSection(CDC *pDC,BOOL bGrid,BOOL bFibre,const CRect &re);  //������Ͻ���,���ػ��Ʊ���
	STRUCT_TYPE GetPlateStructType();
	int GetPlateSecType();
	int IsUsable(STRUCT_TYPE iType);

	CString &AutoName(void);


public:
	float fWidth, fHeight; //��ȷ�Χ,�߶ȷ�Χ������������ʾ����Χ�ⶨ��δ����ת�ǣ���Ϊת���ǹ������ԣ����ǽ�������

	//��ʱ����
	float Temp_Original_B;  // ���ڼӹ̽���Ի���ߴ���ʾ����
	float Temp_Original_H;  // ���ڼӹ̽���Ի���ĳߴ���ʾ����


public:
	PLATE_REINFORCED_METHOD iReinForcedMethod;	//�ӹ̷���,ģ��ID

	CString sConcGrade; //�������ȼ�
	CString sRebarGrade; //�ֽ�ȼ�
	CString sSteelModel; //�ֲ��ͺ�



	float fRatioB, fRatioH;  //����ʣ��ӹ̰壺���׽�ӹ�ǽ��B ˮƽ�����,��λ���ٷ���

	//�ӹ̷����ļ��β���
	union
	{
		// ��ӹ̷���
		struct PLATE_ENLARGED_SECTION plate_enlarge_section;
		struct PLATE_PASTE_STELL_PLATE plate_paste_steel_plate;
		struct PLATE_PASTE_FIBER plate_paste_fiber;

		// ǽ�ӹ̷���
		struct WALL_ENLARGED_SECTION wall_enlarge_section;
		struct WALL_PASTE_STELL_PLATE wall_paste_steel_plate;


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

	//����ģ�崴�����棬���ԭ������
	BOOL CreatePlateSectionByTemplete(PLATE_REINFORCED_METHOD iMethod);
	void CreatPlateSectionReinForcedParameter(PLATE_REINFORCED_METHOD imethod);

public:
	//��������ֵ����,�־����ݣ����浽�ļ����û���������������޸ģ��޸Ľ���ʱ����GetFeatures���м���
	enum { BEAMSECTION_PARA = 12 };	//����������������
	float ConcArea, SteelArea;			//���������,�ֲ����(������������ʼ���ĸֽ��ͬ)
	float ConcShearArea2, SteelShearArea2;	//2���򿹼����
	float ConcShearArea3, SteelShearArea3;	//3���򿹼����
	float ConcI2, SteelI2;			//2����ת����������Ӧ����M2����
	float ConcI3, SteelI3;			//3����ת����������Ӧ����M3����
	float ConcJ1, SteelJ1;			//1����ת�������������Ծأ���ӦŤ��M1

};

//�����༯��
class _SSG_DLLIMPEXP CPlateSectionReinforcedCollection
{
public:
	CPlateSectionReinforcedCollection(void){;}
	~CPlateSectionReinforcedCollection(void){Clear();}

	CPlateSectionReinforcedCollection(const CPlateSectionReinforcedCollection &sec)
	{
		*this=sec;
	}

	CArray<CPlateSectionReinforced*,CPlateSectionReinforced*> aPlateSectionReinForcedPtr;  //�������ָ��
	int iMaxID;  //��ǰ�õ������ID

	int GetID(int iStrucType,const CString &sName,bool bIndep=false);  //���ݽṹ���ͺͽ������ƻ�ý���ID,�Ҳ�������-1 bIndep�Ƿ񰴹����������
	int GetShowId(int iStrucType,int id);//���ݽṹ���ͺͽ����ŵõ������Ͷ�����ţ������ŷֱ��1��ʼ���ֻ������ʾ
	int GetIDByShowId(int iStrucType,int id);//���ݽṹ���ͺͽ��������ŵõ�����ID
	int GetIndex(int id) const;  //���ݸ�����������id��������,�Ҳ�������-1
	CPlateSectionReinforced *GetPlateSectionReinforced(int id) const;  //���ݸ����İ����id���ؽ���ָ��
	int *CreateIndex(void);  //����ID-->��ŵ��������飬���ó�����Ҫɾ���������鳤��ΪiMaxID+1
	void AppendSection(CPlateSectionReinforced *psec);  //�����½��棬�Զ���ȡID

	CPlateSectionReinforcedCollection & operator=(const CPlateSectionReinforcedCollection &sec)
	{
		if(this==&sec) return *this; //����ֵʱֱ�ӷ���

		Clear();
		for(int i=0;i<sec.aPlateSectionReinForcedPtr.GetCount();i++) 
		{
			CPlateSectionReinforced *s1=new CPlateSectionReinforced(*(sec.aPlateSectionReinForcedPtr[i]));

			aPlateSectionReinForcedPtr.Add(s1);  //���ﲻ����AppendSection�����ı�ID
			iMaxID=max(iMaxID,s1->id);  //��¼���ID
		}

		return *this;
	}

	void Clear();

	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);
	void LoadDefaultLib(void);  //����ϵͳ��
};


struct  PLATE_SECTION_REINFORCED_METHOD_PROP_TABLE
{
	PLATE_REINFORCED_METHOD iMethod;  //�ӹ̷���ģ��ID
	CString sName;   //��״ģ������
	PALTESECTION_REINFORCED_MAT_TYPE iType;  //��������
	
};

static  PLATE_SECTION_REINFORCED_METHOD_PROP_TABLE PlateSectReinForcedTable[gPlateSectionMethodNum] =
{
	PLATE_METHOD_ENLARGED_SECTION	,	L"��������淨",PALTESECTION_REINFORCED_MAT_TYPE_CONC,
	PLATE_METHOD_PASTE_STELL_PLATE	,	L"�������ְ巨",PALTESECTION_REINFORCED_MAT_TYPE_ST,
	PLATE_METHOD_PASTE_FIBER		,	L"��������ά��",PALTESECTION_REINFORCED_MAT_TYPE_FIBER,

	WALL_METHOD_ENLARGED_SECTION	,	L"ǽ������淨",PALTESECTION_REINFORCED_MAT_TYPE_CONC,
	WALL_METHOD_PASTE_STELL_PLATE	,	L"ǽ�����ְ巨",PALTESECTION_REINFORCED_MAT_TYPE_ST,
};

struct _SSG_DLLIMPEXP PLATE_SECTION_REINFORCED_METHOD_PARA
{
	PLATE_REINFORCED_METHOD iMethod;	//�ӹ̷���
	CString sName;				//��������
	int nPara;					//��������
	CString sParaName[Sys_SubSectionParaNum]; //��������
};

extern "C" _SSG_DLLIMPEXP PLATE_SECTION_REINFORCED_METHOD_PARA PlateSectionReinForcedMethodParaTable[Sys_PlateReinForcedSectionShapeNum];
extern "C" _SSG_DLLIMPEXP PLATE_SECTION_REINFORCED_METHOD_PARA * FindPlateSectionReinForcedMethodPropByID(PLATE_REINFORCED_METHOD id);
