#pragma once
#include "HeadDefine.h"
#include "ASCFile.h"
#include "SectionBase.h"

//�湹��������
class _SSG_DLLIMPEXP CPlateSection
{
public:
	//��������������
	CPlateSection(void) {pLayers=NULL; Clear();}
	CPlateSection(const CPlateSection &sec)	{ pLayers=NULL; nUsedCount=0; *this=sec; }
	~CPlateSection(void) { Clear(); }

	//��������
	int id;  //����ID
	CString sName;  //��������,���������ý����������ԣ�һ���������Ʊ��Ķ�������ݸĶ�ǰ��Ķ�Ӧ��ϵ�滻������
	int iStructType;  //�������ͣ�1-�壻2-ǽ
	PALTESECTION_MAT_TYPE iPlateMatType;		//����������ʹ���,1-��������2-����ְ��������3-˫��ְ��������4-���ְ�
	int nLayers; //������
	struct LAYER_INFO
	{
		float fLayerThick;				//���ȣ���λ����
		SUBSECTION_MAT_TYPE iLayerMatType;	//�����
		float fOffset;					//������λ��,��λ����
	} *pLayers; //����Ϣ
	
	float fThick; //�ܺ�ȣ��ɸ����ۼӵõ������뼰�޸�Ҫ����
	COLORREF dwColor; //��ʾ��ɫ, ���ڿ���Ѱ��
	int nUsedCount;  //������ʹ�õĴ�����һ��Ҫ�ȼ�����ʹ��,��ʱ����

	void Clear(void);
	//void GetThick(void);//������
	CPlateSection & operator=(const CPlateSection &sec);
	BOOL operator==(const CPlateSection &sec) const;
	BOOL operator!=(const CPlateSection &sec) const;

	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);
	CString sMatName();
	BOOL CheckPlateSect();//���������ͼ������Ƿ��Ӧ
	float DrawPlateSection(CDC *pDC,BOOL bGrid,BOOL bFibre,const CRect &re);  //������Ͻ���,���ػ��Ʊ���
	BOOL GetPlateSec(SECTION_MAT_TYPE &secType,float &fThickness,int &nSteelLayer,float &fSteelThick,float &fConcThick);
	int GetPlateStructType();
	int GetPlateSecType();

	//����������Ƿ�����
	BOOL CheckSectParameter(float fMin=0.f);
	//�������ݽ������ͳ�ʼ����������
	BOOL SetSectParameter(float fSteelThk);
	//���ݽ������������Զ��������
	CString &AutoName(void);
	//�õ�������
	float GetSecThickness(SUBSECTION_MAT_TYPE iType);
};

//�����༯��
class _SSG_DLLIMPEXP CPlateSectionCollection
{
public:
	CPlateSectionCollection(void){;}
	~CPlateSectionCollection(void){Clear();}

	CPlateSectionCollection(const CPlateSectionCollection &sec)
	{
		*this=sec;
	}

	CArray<CPlateSection*,CPlateSection*> aPlateSectionPtr;  //�������ָ��
	int iMaxID;  //��ǰ�õ������ID

	int GetID(int iStrucType,const CString &sName,bool bIndep=false);  //���ݽṹ���ͺͽ������ƻ�ý���ID,�Ҳ�������-1 bIndep�Ƿ񰴹����������
	int GetShowId(int iStrucType,int id);//���ݽṹ���ͺͽ����ŵõ������Ͷ�����ţ������ŷֱ��1��ʼ���ֻ������ʾ
	int GetIDByShowId(int iStrucType,int id);//���ݽṹ���ͺͽ��������ŵõ�����ID
	int GetIndex(int id) const;  //���ݸ�����������id��������,�Ҳ�������-1
	CPlateSection *GetPlateSection(int id) const;  //���ݸ����İ����id���ؽ���ָ��
	int *CreateIndex(void);  //����ID-->��ŵ��������飬���ó�����Ҫɾ���������鳤��ΪiMaxID+1
	void AppendSection(CPlateSection *psec);  //�����½��棬�Զ���ȡID

	CPlateSectionCollection & operator=(const CPlateSectionCollection &sec)
	{
		if(this==&sec) return *this; //����ֵʱֱ�ӷ���

		Clear();
		for(int i=0;i<sec.aPlateSectionPtr.GetCount();i++) 
		{
			CPlateSection *s1=new CPlateSection(*(sec.aPlateSectionPtr[i]));
			//*s1=*sec.aBeamSectionPtr[i];
			aPlateSectionPtr.Add(s1);  //���ﲻ����AppendSection�����ı�ID
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



