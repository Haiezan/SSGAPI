#pragma once
#include "HeadDefine.h"

#include "SysPara.h"

//һ�����ӹ���������
struct SEC_KELVIN
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1K,fU1DmpC,fU1DmpE,fU1InvaidDatas[22];//U1����
	float fU2Linear,fU2NLinear,fU2InvaidData,fU2Ke,fU2De,fU2K,fU2DmpC,fU2DmpE,fU2InvaidDatas[22];//U2����
	float fU3Linear,fU3NLinear,fU3InvaidData,fU3Ke,fU3De,fU3K,fU3DmpC,fU3DmpE,fU3InvaidDatas[22];//U3����
	float fU4Linear,fU4NLinear,fU4InvaidData,fU4Ke,fU4De,fU4K,fU4DmpC,fU4DmpE,fU4InvaidDatas[22];//U4����
	float fU5Linear,fU5NLinear,fU5InvaidData,fU5Ke,fU5De,fU5K,fU5DmpC,fU5DmpE,fU5InvaidDatas[22];//U5����
	float fU6Linear,fU6NLinear,fU6InvaidData,fU6Ke,fU6De,fU6K,fU6DmpC,fU6DmpE,fU6InvaidDatas[22];//U6����
};
struct SEC_KELVINSPRING
{
	float fU1Linear, fU1NLinear, fU1InvaidData, fU1Ke, fU1De, fU1K, fU1DmpC, fU1DmpE, fU1ConnectK, fU1InvaidDatas[21];//U1����
	float fU2Linear, fU2NLinear, fU2InvaidData, fU2Ke, fU2De, fU2K, fU2DmpC, fU2DmpE, fU2ConnectK, fU2InvaidDatas[21];//U2����
	float fU3Linear, fU3NLinear, fU3InvaidData, fU3Ke, fU3De, fU3K, fU3DmpC, fU3DmpE, fU3ConnectK, fU3InvaidDatas[21];//U3����
	float fU4Linear, fU4NLinear, fU4InvaidData, fU4Ke, fU4De, fU4K, fU4DmpC, fU4DmpE, fU4ConnectK, fU4InvaidDatas[21];//U4����
	float fU5Linear, fU5NLinear, fU5InvaidData, fU5Ke, fU5De, fU5K, fU5DmpC, fU5DmpE, fU5ConnectK, fU5InvaidDatas[21];//U5����
	float fU6Linear, fU6NLinear, fU6InvaidData, fU6Ke, fU6De, fU6K, fU6DmpC, fU6DmpE, fU6ConnectK, fU6InvaidDatas[21];//U6����
};
struct SEC_MAXWELL
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1K,fU1DmpC,fU1DmpE,fU1InvaidDatas[22];//U1����
	float fU2Linear,fU2NLinear,fU2InvaidData,fU2Ke,fU2De,fU2K,fU2DmpC,fU2DmpE,fU2InvaidDatas[22];//U2����
	float fU3Linear,fU3NLinear,fU3InvaidData,fU3Ke,fU3De,fU3K,fU3DmpC,fU3DmpE,fU3InvaidDatas[22];//U3����
	float fU4Linear,fU4NLinear,fU4InvaidData,fU4Ke,fU4De,fU4K,fU4DmpC,fU4DmpE,fU4InvaidDatas[22];//U4����
	float fU5Linear,fU5NLinear,fU5InvaidData,fU5Ke,fU5De,fU5K,fU5DmpC,fU5DmpE,fU5InvaidDatas[22];//U5����
	float fU6Linear,fU6NLinear,fU6InvaidData,fU6Ke,fU6De,fU6K,fU6DmpC,fU6DmpE,fU6InvaidDatas[22];//U6����
};
struct SEC_DMPDISP
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1K0,fU1Fy,fU1Rst,fU1InvaidDatas[22];//U1����
	float fU2Linear,fU2NLinear,fU2InvaidData,fU2Ke,fU2De,fU2K0,fU2Fy,fU2Rst,fU2InvaidDatas[22];//U2����
	float fU3Linear,fU3NLinear,fU3InvaidData,fU3Ke,fU3De,fU3K0,fU3Fy,fU3Rst,fU3InvaidDatas[22];//U3����
	float fU4Linear,fU4NLinear,fU4InvaidData,fU4Ke,fU4De,fU4K0,fU4Fy,fU4Rst,fU4InvaidDatas[22];//U4����
	float fU5Linear,fU5NLinear,fU5InvaidData,fU5Ke,fU5De,fU5K0,fU5Fy,fU5Rst,fU5InvaidDatas[22];//U5����
	float fU6Linear,fU6NLinear,fU6InvaidData,fU6Ke,fU6De,fU6K0,fU6Fy,fU6Rst,fU6InvaidDatas[22];//U6����
};
struct SEC_USERDISP
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1Hystype,fU1Deftype,fU1TNum,fU1CNum,fU1PointData[21];//U1����
	float fU2Linear,fU2NLinear,fU2InvaidData,fU2Ke,fU2De,fU2Hystype,fU2Deftype,fU2TNum,fU2CNum,fU2PointData[21];//U2����
	float fU3Linear,fU3NLinear,fU3InvaidData,fU3Ke,fU3De,fU3Hystype,fU3Deftype,fU3TNum,fU3CNum,fU3PointData[21];//U3����
	float fU4Linear,fU4NLinear,fU4InvaidData,fU4Ke,fU4De,fU4Hystype,fU4Deftype,fU4TNum,fU4CNum,fU4PointData[21];//U4����
	float fU5Linear,fU5NLinear,fU5InvaidData,fU5Ke,fU5De,fU5Hystype,fU5Deftype,fU5TNum,fU5CNum,fU5PointData[21];//U5����
	float fU6Linear,fU6NLinear,fU6InvaidData,fU6Ke,fU6De,fU6Hystype,fU6Deftype,fU6TNum,fU6CNum,fU6PointData[21];//U6����
};
struct SEC_SPRING
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fKu1,fDu1,fU1InvaidDatas[25];//U1����
	float fU2Linear,fU2NLinear,fU2InvaidData,fKu2,fDu2,fU2InvaidDatas[25];//U2����
	float fU3Linear,fU3NLinear,fU3InvaidData,fKu3,fDu3,fU3InvaidDatas[25];//U3����
	float fU4Linear,fU4NLinear,fU4InvaidData,fKu4,fDu4,fU4InvaidDatas[25];//U4����
	float fU5Linear,fU5NLinear,fU5InvaidData,fKu5,fDu5,fU5InvaidDatas[25];//U5����
	float fU6Linear,fU6NLinear,fU6InvaidData,fKu6,fDu6,fU6InvaidDatas[25];//U6����
};
struct SEC_TMD
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fKu1,fDu1,fU1InvaidDatas[25];//U1����
	float fU2Linear,fU2NLinear,fU2InvaidData,fKu2,fDu2,fU2InvaidDatas[25];//U2����
	float fU3Linear,fU3NLinear,fU3InvaidData,fKu3,fDu3,fU3InvaidDatas[25];//U3����
	float fU4Linear,fU4NLinear,fU4InvaidData,fKu4,fDu4,fU4InvaidDatas[25];//U4����
	float fU5Linear,fU5NLinear,fU5InvaidData,fKu5,fDu5,fU5InvaidDatas[25];//U5����
	float fU6Linear,fU6NLinear,fU6InvaidData,fKu6,fDu6,fU6InvaidDatas[25];//U6����
};
struct SEC_BRB//BRB
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1K0,fU1Fy,fU1Rst;//U1����
};
struct SEC_LRB//����֧��
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1Kc,fU1Kt,fU1InvaidDatas[23];//U1����
	float fU2Linear,fU2NLinear,fU2InvaidData,fU2Ke,fU2De,fU2K0,fU2Fy,fU2Rst,fU2InvaidDatas[22];//U2����
	float fU3Linear,fU3NLinear,fU3InvaidData,fU3Ke,fU3De,fU3K0,fU3Fy,fU3Rst,fU3InvaidDatas[22];//U3����
	float fU4Linear,fU4NLinear,fU4InvaidData,fU4Ke,fU4De,fU4InvaidDatas[25];//U4����
	float fU5Linear,fU5NLinear,fU5InvaidData,fU5Ke,fU5De,fU5InvaidDatas[25];//U5����
	float fU6Linear,fU6NLinear,fU6InvaidData,fU6Ke,fU6De,fU6InvaidDatas[25];//U6����
};
struct SEC_LRBWEN//����֧��(Wen)
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1Kc,fU1Kt,fU1InvaidDatas[23];//U1����
	float fU2Linear,fU2NLinear,fU2InvaidData,fU2Ke,fU2De,fU2K0,fU2Fy,fU2Rst,fU2Ey,fU2InvaidDatas[21];//U2����
	float fU3Linear,fU3NLinear,fU3InvaidData,fU3Ke,fU3De,fU3K0,fU3Fy,fU3Rst,fU3Ey,fU3InvaidDatas[21];//U3����
	float fU4Linear,fU4NLinear,fU4InvaidData,fU4Ke,fU4De,fU4InvaidDatas[25];//U4����
	float fU5Linear,fU5NLinear,fU5InvaidData,fU5Ke,fU5De,fU5InvaidDatas[25];//U5����
	float fU6Linear,fU6NLinear,fU6InvaidData,fU6Ke,fU6De,fU6InvaidDatas[25];//U6����
};
struct SEC_ESB
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1InvaidDatas[25];//U1����
	float fU2Linear,fU2NLinear,fU2InvaidData,fU2Ke,fU2De,fU2K0,fU2Coef,fU2InvaidDatas[23];//U2����
	float fU3Linear,fU3NLinear,fU3InvaidData,fU3Ke,fU3De,fU3K0,fU3Coef,fU3InvaidDatas[23];//U3����
	float fU4Linear,fU4NLinear,fU4InvaidData,fU4Ke,fU4De,fU4InvaidDatas[25];//U4����
	float fU5Linear,fU5NLinear,fU5InvaidData,fU5Ke,fU5De,fU5InvaidDatas[25];//U5����
	float fU6Linear,fU6NLinear,fU6InvaidData,fU6Ke,fU6De,fU6InvaidDatas[25];//U6����
};
struct SEC_FPS
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1InvaidDatas[25];//U1����
	float fU2Linear,fU2NLinear,fU2InvaidData,fU2Ke,fU2De,fU2K,fU2Cslow,fU2Cfast,fU2CRatio,fU2Radius,fU2InvaidDatas[20];//U2����
	float fU3Linear,fU3NLinear,fU3InvaidData,fU3Ke,fU3De,fU3K,fU3Cslow,fU3Cfast,fU3CRatio,fU3Radius,fU3InvaidDatas[20];//U3����
	float fU4Linear,fU4NLinear,fU4InvaidData,fU4Ke,fU4De,fU4InvaidDatas[25];//U4����
	float fU5Linear,fU5NLinear,fU5InvaidData,fU5Ke,fU5De,fU5InvaidDatas[25];//U5����
	float fU6Linear,fU6NLinear,fU6InvaidData,fU6Ke,fU6De,fU6InvaidDatas[25];//U6����
};
struct SEC_WEN
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1K0,fU1Fy,fU1Rst,fU1Ey,fU1InvaidDatas[21];//U1����
	float fU2Linear,fU2NLinear,fU2InvaidData,fU2Ke,fU2De,fU2K0,fU2Fy,fU2Rst,fU2Ey,fU2InvaidDatas[21];//U2����
	float fU3Linear,fU3NLinear,fU3InvaidData,fU3Ke,fU3De,fU3K0,fU3Fy,fU3Rst,fU3Ey,fU3InvaidDatas[21];//U3����
	float fU4Linear,fU4NLinear,fU4InvaidData,fU4Ke,fU4De,fU4InvaidDatas[25];//U4����
	float fU5Linear,fU5NLinear,fU5InvaidData,fU5Ke,fU5De,fU5InvaidDatas[25];//U5����
	float fU6Linear,fU6NLinear,fU6InvaidData,fU6Ke,fU6De,fU6InvaidDatas[25];//U6����
};
struct SEC_CABLE
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1K0,fU1Fy,fU1Rst;//U1����
};
struct SEC_GAP
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1K,fU1D;//U1����
};
struct SEC_HOOK
{
	float fU1Linear,fU1NLinear,fU1InvaidData,fU1Ke,fU1De,fU1K,fU1D;//U1����
};
struct SEC_USER
{
	float fU1Linear, fU1NLinear, fU1InvaidData, fKu1, fDu1, fU1Datas[25];//U1����
	float fU2Linear, fU2NLinear, fU2InvaidData, fKu2, fDu2, fU2Datas[25];//U2����
	float fU3Linear, fU3NLinear, fU3InvaidData, fKu3, fDu3, fU3Datas[25];//U3����
	float fU4Linear, fU4NLinear, fU4InvaidData, fKu4, fDu4, fU4Datas[25];//U4����
	float fU5Linear, fU5NLinear, fU5InvaidData, fKu5, fDu5, fU5Datas[25];//U5����
	float fU6Linear, fU6NLinear, fU6InvaidData, fKu6, fDu6, fU6Datas[25];//U6����
};
struct SEC_TVMD
{
	float fU1Linear, fU1NLinear, fU1InvaidData, fU1Ke, fU1De, fU1K0, fU1DmpC, fU1DmpE, fU1Mass, fU1InvaidDatas[21];//U1����
	float fU2Linear, fU2NLinear, fU2InvaidData, fU2Ke, fU2De, fU2K0, fU2DmpC, fU2DmpE, fU2Mass, fU2InvaidDatas[21];//U2����
	float fU3Linear, fU3NLinear, fU3InvaidData, fU3Ke, fU3De, fU3K0, fU3DmpC, fU3DmpE, fU3Mass, fU3InvaidDatas[21];//U3����
	float fU4Linear, fU4NLinear, fU4InvaidData, fU4Ke, fU4De, fU4K0, fU4DmpC, fU4DmpE, fU4Mass, fU4InvaidDatas[21];//U4����
	float fU5Linear, fU5NLinear, fU5InvaidData, fU5Ke, fU5De, fU5K0, fU5DmpC, fU5DmpE, fU5Mass, fU5InvaidDatas[21];//U5����
	float fU6Linear, fU6NLinear, fU6InvaidData, fU6Ke, fU6De, fU6K0, fU6DmpC, fU6DmpE, fU6Mass, fU6InvaidDatas[21];//U6����
};

struct INFO_LRB
{
	float	fShearModule,fType,fDiameter,fHoleDia,fTireTh,fS1,fS2,fArea,fFlangeTh,fHeight,
		fAxialStiff,fInitStiff,fSecStiff,fYieldF,
		fEqStiffMid,fEqDmpMid,fEqStiffRare,fEqDmpRare,fEqStiffSmall,fEqDmpSmall;
};
struct INFO_ESB
{
	float	fShearModule,fDiameter,fTireTh,fS1,fS2,fArea, fCoef, fAxialStiff, fInitStiff, fDisMax;
};
struct INFO_FPS
{
	float	fType, fRaidus, fH, fDiameter, fDisMax, fCslow, fCfast, fCRatio, fArea, fAxialStiff, fInitStiff, fEqvStiff, fAxialF;
};
struct INFO_BRB
{
	float	fYieldF, fYieldDis, fInitStiff, fYieldExp, fSecStiffRatio, fUltimateF, fUltimateDis, fLen, fAxialLen;
};
struct INFO_VFD
{
	float	fDampCoef, fDampExp, fInitStiff, fDesignFLow, fDesignFUp, fDesignDisLow, fDesignDisUp, fMaxVelo, fLen;
};
struct INFO_MYD
{
	float	fYieldF, fYieldDis, fInitStiff, fYieldExp, fSecStiffRatio, fUltimateF, fUltimateDisLow, fUltimateDisUp;
};

class CASCFile;

class _SSG_DLLIMPEXP CDamperSection
{
public:
	//��������������
	CDamperSection(void)
		: id(-1)
		, sName(L"")
		, iSectionType(LINK_UNKNOWN)
		, iSubType(0)
		, fMass(0)
		, dwColor(0)
		, fDamperSecPara()
		, fDamperDesPara()
		, nUsedCount(0)
		, bPDelta(false)
		, nDamperGrade(0)
		, fDamperGrade_n()
		, fDamperGrade_t()
	{}
	CDamperSection(const CDamperSection &sec)	{ nUsedCount=0; *this=sec; }
	~CDamperSection(void) { Clear(); }

	//��������
	int id;  //����ID
	CString sName;  //��������,���������ý����������ԣ�һ���������Ʊ��Ķ�������ݸĶ�ǰ��Ķ�Ӧ��ϵ�滻������
	LINK_SUBTYPE iSectionType;	//
	int iSubType; //����
	COLORREF dwColor; //��ʾ��ɫ, ���ڿ���Ѱ��
	//��������ֵ����,�־����ݣ����浽�ļ����û���������������޸ģ��޸Ľ���ʱ����GetFeatures���м���
	enum {DAMPERSECTION_PARA=6*Sys_nLinkData};//ÿ�����ɶ� Sys_nLinkHead =30����6*30��
	union
	{
		struct SEC_KELVIN Kelvin;
		struct SEC_MAXWELL Maxwell;
		struct SEC_DMPDISP DmpDisp;
		struct SEC_TMD Tmd;
		struct SEC_BRB Brb;
		struct SEC_LRB Isolator;
		struct SEC_ESB Esb;
		struct SEC_FPS Fps;
		struct SEC_WEN Wen;
		struct SEC_SPRING Spring;
		struct SEC_CABLE Cable;
		struct SEC_GAP Gap;
		struct SEC_HOOK Hook;
		struct SEC_LRBWEN IoslatorWen;
		struct SEC_KELVINSPRING KelvinSpring;
		struct SEC_USER User;
		struct SEC_TVMD Tvmd;
		float fDamperSecPara[DAMPERSECTION_PARA];
	};
	float fMass;
	enum {DAMPERDESIGN_PARA=28};	//��Ʋ���
	union
	{
		struct INFO_LRB IsolatorInfo;
		struct INFO_ESB ESBInfo;
		struct INFO_FPS FPSInfo;
		struct INFO_BRB BRBInfo;
		struct INFO_MYD MYDInfo;
		struct INFO_VFD	VFDInfo;
		float fDamperDesPara[DAMPERDESIGN_PARA];
	};
	bool bPDelta;
	int nDamperGrade;//�������������۵ȼ�
	float fDamperGrade_n[6];//�������������ܵȼ�����
	float fDamperGrade_t[6];//�������������ܵȼ�����

	//��ʱ����,�����浽�ļ�,��ȡ���桢�޸Ľ���ʱ���޸���ά���Ʋ���ʱ����GetFibres����
	int nUsedCount;  //������ʹ�õĴ�����һ��Ҫ�ȼ�����ʹ��,��ʱ����
	//���ݽ������������Զ��������
	
	CDamperSection & operator=(const CDamperSection &sec);
	void Clear(void);
	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);
	CString sTypeName()const; //�õ������������� �� 2016��6��15��
	//�����Ϣ��д
	BOOL ReadDesignInfo(CASCFile &fin);
	void WriteDesignInfo(CASCFile &fout);
	void WriteDesignInfo2020(CASCFile &fout);
	//
	void GenerateDamperGradeOld();
	int GenerateDamperGrade(float* fDamperGrade_n = NULL, float* fDamperGrade_t = NULL);
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
	int GetSecNumByType(LINK_SUBTYPE iStrucType)const ;// �õ�ͬ���ͽ�������� �� 2016��3��24��


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
	int GetID(const CString &sName) const;
	void Clear();
	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);
	void LoadDefaultLib(void);  //����ϵͳ��
	BOOL ExportSecProperty(int iType,CArray<int,int>&SecArr,CString *&pContents,int &nRows,int &nCols);
};
