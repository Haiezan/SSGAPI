#pragma once

#include "DataStrucProp.h"
#include "ASCFile.h"

class CSectionCollection;
class CDamperSectionCollection;

class CVertex;
class CLine;


//
struct BEAM_REIN
{
	float AST;	
	float ASB;
	float ASVE;
	float ASVM;
	float ify0;
	float ifyv0;
	float isbbo;
};

struct PILLAR_REIN
{
	float ASX0;	//mm2
	float ASY0;	//mm2
	float ASC0;	//mm2
	float ASVX0;	//mm2
	float ASVY0;	//mm2
	float IFYO;	//N/mm2
	float IFYV0; //N/mm2
	float ISCC0;	// mm
};

enum STEEL_SEC_S
{
	TYPE_S0 = -1, //δ����
	TYPE_S1 = 0, 
	TYPE_S2,
	TYPE_S3,
	TYPE_S4,
	TYPE_S5,
	TYPE_EX, //����
};

class _SSG_DLLIMPEXP CReinforcement
{
public:
	CReinforcement();
	~CReinforcement();
	CReinforcement(const CReinforcement& aRein)
	{
		*this = aRein;
	};
	CReinforcement& operator =(const CReinforcement & aRein);

	void ReadPDBBeamRein(const float* bjg);
	void ReadPDBColumnRein(const float* cjg);
	void CalRatioBeam(float fArea);
	void CalRatioPillar(float fArea);
	float GetRatio1() const { return Ratio1; }
	float GetRatio2() const { return Ratio2; }
public:
	union
	{
		BEAM_REIN beam_rein;
		PILLAR_REIN pillar_rein;
		float fRein[8];
	};
private:
	float Ratio1;
	float Ratio2;
};


//��״��������һ���߶����
class _SSG_DLLIMPEXP CBeamStruc : public CStrucProp
{
public:
	CBeamStruc(void);
	//���ƹ��캯��
	CBeamStruc(const CBeamStruc &beam) 
	{
		*this=beam;
	};

	CBeamStruc(STRUCT_TYPE istructype,int lineid,int istory,DWORD color);
	~CBeamStruc()
	{

	};

	//int id; //��������id����1��ʼ��ţ������߹����������
	int LineIDM; //�ṹ�߱��
	int iSectionID;  //����ID

	/*
	�߹���������
	�����ש������ש������ש������ש������ש������ש������ש������ש���������
	��  ��  Bit7�� Bit6 �� Bit5 �� Bit4 �� Bit3 �� Bit2 �� Bit1 �� Bit0   ��
	�ǩ��贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈��������
	������  0   �� 0    ���ӹ����� ���� ����������ת������ ���� �� ����   ��
	�ǩ��贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈��������
	������  0   �� 0    ���ӹ����� 0    ��0     ��0     �� 0    ����֧��  ��
	�ǩ��贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈��������
	���ũ�  0   �� 0    ���ӹ̳ũ� 0    ��0     ��0     �� 0    ������֧�ũ�
	�����ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ���������
	*/
	int iSubType;	//�����ͣ����Լ�¼һ�����ӵ������� 
	//�½ӱ�ʶ��0~6λ����U1~U11���ɶ��Ƿ�½ӣ�1����½�
	int iArtiNode1, iArtiNode2;	//��Ӧ�Ķ˵��Ƿ�½ӣ�FALSEΪ�̽�,��ѡĳ���������������Ķ˵�Ϊ�½ӣ������ʹ������ɽ½ӣ��������˻�һ�˽½�
	int iBottomStory; //�׵�¥��ţ�����б����Ч����ʱ����
	//�����������ߵķ���ǣ���λ���ȣ�2->3����Ϊ��,fAng�ṩ���û��޸�,�޸ĺ���������CalRefPoint����ο���
	float fRotateAng;  //�޸�ת��ʱ��Ҫ���¾ֲ�����
	float fOffsetX1,fOffsetY1,fOffsetZ1;  //�׵�ƫ�ƾ��루m��,�ֲ�����ϵ������ΪX
	float fOffsetX2,fOffsetY2,fOffsetZ2;  //ĩ��ƫ�ƾ��루m��
	float fRatio1,fRatio2;  //����ʣ��������׽����б�ţ�B��H����ĵ�������ʣ������ǽ,��λ���ٷ���
	float fCornerArea;  //һ���ǽ�����(m^2)������б����Ч
	float f_StirArea_D,f_StirArea_UD;  //�������������, �Ǽ����������������������б����Ч

	//�޸Ĺ�����ʼȱ�ݶ��巽ʽ 20221109�����޸�
	float fDefect; //��ʼȱ�ݴ���ֵ�ĵ���
	float fDefectAngle; //��ʼȱ�ݷ���
	//float fDefectY;// �ֲ�����y���Ӧ��ʼȱ�ݵ���
	//float fDefectZ;// �ֲ�����z���Ӧ��ʼȱ�ݵ���	

	float fEffectStiff[6];//��Ч�ն�  һ�������ã��նȷŴ�ϵ�� �������� ����
	float fEffectDamp[6];//��Ч����  һ��������
	BOOL GetEffectPara(); //һ�������ã�ˢ�¹�����Ч�ն� ����
	CString sAppendMat;		//���Ӳ���  ������Ч
	int iNode1Sec;//һ�˽���	
	int iNode2Sec;//���˽���
	int iShearNonlinear; //�Ƿ��Ǽ��нµ����ԣ�0Ϊ���ԣ�1Ϊ������ ����� 20230110
	float fBeamSpan; //�������(����Լ��нµ����ԵĹ��������๹��Ϊ0) ����� 20230112
	int iReinforcedSec;//�ӹ̷�������id
	//int iPin;        //�½ӱ�ʶ��0~11λ����U1~U11���ɶ��Ƿ�½ӣ�1����½�
	CPinData aPin;
	//reinforcement
	CReinforcement aRein;

	//��ʱ���ݣ��������ļ�,u.x>1���Ϸ�����ʼ��u.x=10.0f��ʾδ���㣬���롢���ӡ��ƶ��˵���޸�ת��ʱ��Ҫ����BeamLocalCoorVector���¼���
	Vector4 u,v,w;  //�ֲ�����ϵ��ʸ��������ԭ�㣬wΪ���߷���,

	BOOL IsSecondBeam(void) const {return iStrucType==STRUCT_BEAM && iSubType&0x01;}	 //FALSE--������ʹ�ý����е���ά��TRUE-��������ʹ����ά��Ϣ��ֻ����������Ч
	void SetSecondBeam(BOOL bSecondBeam) 
	{
		if(iStrucType!=STRUCT_BEAM) return;
		if(bSecondBeam)
			iSubType |= 0x01; 
		else
			iSubType &= ~0x01; 
	}

	// �����ӹ��� ��ҵ�� ��ҵ�� 2023��4��14��
	BOOL IsReinForcedBeam(void) const
	{
		return   (iStrucType == STRUCT_BEAM && (iSubType & 0x20));
	}

	// �����ӹ̹���
	BOOL IsReinForcedPillar(void) const
	{
		return   (iStrucType == STRUCT_PILLAR && (iSubType & 0x20));
	}

	// �����ӹ�б��
	BOOL IsReinForcedBracing(void) const
	{
		return   (iStrucType == STRUCT_BRACING && (iSubType & 0x20));
	}

	BOOL IsReinForced()const;

	BOOL IsReinForcedConc()const;
	BOOL IsReinForcedFiber()const;

	BOOL IsPropEqual(const CBeamStruc &beam) const;  //���пɺϲ�������

	//�Ƿ���������,����ֻ�������أ����ṩ�նȵ�Ԫ������
	BOOL IsVirtualBeam(void) const 
	{
		return (iStrucType==STRUCT_BEAM && (iSubType&0x10)) || iStrucType==STRUCT_HIDEBEAM;
	} 

	float GetWidth(const CSectionCollection *pSecCollection,const CDamperSectionCollection *pDamperSecCollection) const; //������
	float GetHeight(const CSectionCollection *pSecCollection,const CDamperSectionCollection *pDamperSecCollection) const; //�߶ȷ�Χ
	void GetBeamStiffness(float* fStiff, bool bForSemiRigid = false);

	//�õ����귶Χ
	void GetRange(Vector4 &rMin,Vector4 &rMax);

	void Clear(void);

	//��ֵ���������
	CBeamStruc & operator=(const CBeamStruc& beam)
	{
		if(this==&beam) return *this;

		*(CStrucProp *)this=(CStrucProp &)beam;

		LineIDM=beam.LineIDM;
		iSectionID=beam.iSectionID;
		iSubType=beam.iSubType;
		iArtiNode1=beam.iArtiNode1;
		iArtiNode2=beam.iArtiNode2;
		iBottomStory=beam.iBottomStory;
		fRotateAng=beam.fRotateAng;
		fOffsetX1=beam.fOffsetX1;
		fOffsetY1=beam.fOffsetY1;
		fOffsetZ1=beam.fOffsetZ1;
		fOffsetX2=beam.fOffsetX2;
		fOffsetY2=beam.fOffsetY2;
		fOffsetZ2=beam.fOffsetZ2;
		fRatio1=beam.fRatio1;
		fRatio2=beam.fRatio2;
		fCornerArea=beam.fCornerArea;
		f_StirArea_D=beam.f_StirArea_D;
		f_StirArea_UD=beam.f_StirArea_UD;

		u=beam.u;
		v=beam.v;
		w=beam.w;

		fDefect = beam.fDefect; //��ʼȱ�ݴ���ֵ����
		fDefectAngle = beam.fDefectAngle; //��ʼȱ�ݷ���

		memcpy(fEffectStiff, beam.fEffectStiff, sizeof(float) * 6);
		memcpy(fEffectDamp, beam.fEffectDamp, sizeof(float) * 6);

		sAppendMat = beam.sAppendMat;
		iNode1Sec = beam.iNode1Sec;
		iNode2Sec = beam.iNode2Sec;
		iShearNonlinear = beam.iShearNonlinear; //����� 20230110
		fBeamSpan = beam.fBeamSpan; //����� 20230112
		iReinforcedSec = beam.iReinforcedSec;
		aPin = beam.aPin;
		aRein = beam.aRein;

		return *this;
	}
	
	void SetRebarRatio(float Ratio1,float Ratio2)
	{
		fRatio1=Ratio1;
		fRatio2=Ratio2;
	}

	//�����߹����ֲ����굥λ��ʸ����������ת��
	//ˮƽ������e1Ϊ���߷���e2��e3Ϊ����ֲ����귽��
	//���򹹼���e1=eZΪ���߷���e2��e3Ϊ����ֲ����귽��
	void BeamLocalCoorVector(CArray<CVertex,CVertex&>&aVex,CArray<CLine,CLine&> &aLine);

	//������β���������ο��㣬��ֱ�����ͷǴ�ֱ�������巽ʽ��ͬ��angΪ����ǣ���λ����
	CVertex CalRefPoint(const CVertex &v1,const CVertex &v2,float ang); 
	//������β����������ͼ���ο��㣬���Ӻͱ�Ե������������X��ת�ǣ������������վֲ���ʼZ��ת�Ƕ��壬angΪ����ǣ���λ����
	CVertex CalRefPoint(const CVertex &v1,const CVertex &v2,STRUCT_TYPE type,float ang);

	//int GetSectionIDM(){return SectionIDM;} //��ý���ID
	inline float GetRatioUpper(){return fRatio1;}  //��������������
	inline float GetRatioLower(){return fRatio2;}  //������׽������
	inline float GetRatioB(){return fRatio1;}    //����б�Ž���B���򵥱������
	inline float GetRatioH(){return fRatio2;}    //����б�Ž���H���򵥱������

	float Length(const CLine *pLine,const CVertex *pVex) const;  //���㹹�����ȣ� pLineΪ�ṹ�����飬pVexΪ������������
	BOOL Weight(float fConcArea, float fSteelArea, float fRebarArea, float &wConc, float &wSt, float &wRebar); //������������λkN

	//���㹹����������λ��kN
	float GetWeight();


	//Ҫ�����ȶ������Ͳ�������
	virtual BOOL Read(CASCFile &fin,STRUCT_TYPE iType,CDamperSectionCollection &cDamperSection,
		CSectionCollection &cSection,const CProjectPara &cPrjPara,CArray<CLine,CLine&> &aLine,CArray<CVertex,CVertex&>&aVex);
	virtual BOOL Write(CASCFile &fout,int idf);
	virtual BOOL Write2020(CASCFile &fout,int idf);
	//�����Ϣ��д
	virtual BOOL ReadDesignInfo(CASCFile &fin,STRUCT_TYPE iType, const CSectionCollection& cSection, int idf);
	virtual BOOL WriteDesignInfo(CASCFile &fout,int idf);
	virtual BOOL WriteDesignInfo2020(CASCFile &fout,int idf);

	void GenLoadId(bool bRewrite=true);//��	float fDeadLoad ��float fLiveLoad����Load����mapload ��2020֮��汾��ȡ
	void GenLoadVal();//��mapload����fDeadLoad��fLiveLoad ��2020֮ǰ�汾��ȡ

	//��ȡ������ʼȱ�� Direction��ʼȱ�ݷ���0-Y,1-Z
	void GetInitialImperfection(bool bRewrite = false, int Direction = 0);
	void GetDefect(float& fDefect2, float& fDefect3);
	//�����Ż�ת
	BOOL ChangeStrucType(STRUCT_TYPE iType);
	//һ������ת������
	BOOL Link2Beam(const CBeamStruc &beam);
	//������תһ������
	BOOL Beam2Link(const CBeamStruc &Link);

	BOOL GetEndElmId(int& iID1, int& iID2); //��ȡ�����˵�ĵ�Ԫ�ڵ��

	//�ӹ�
	//�������ֽ���ά,��������ʺ͸ֽ�ֱ����ֻ�Ի�����������������������ֻ��һ�����������棬������ά���궯̬�ڴ漰��ά�����������浽���Ա��ʱ����
	//��ratioUpper��������,ratioLower�׽������,��λ1
	void* CreateReinForcedBeamRebar();
	//�������ֽ���ά,��������ʺ͸ֽ�ֱ����ֻ�Ի�����������������������ֻ��һ�����������棬������ά���궯̬�ڴ漰��ά�����������浽���Ա��ʱ����
	//��ratioB--B���������,ratioH--H��������ʣ�Բ����ֻ�õ�һ�������,��λ1
	void* CreateReinForcedPillarRebar();

	void* CreateReinForcedSteel();

	void SetPin(int iPin, bool bFirst, int iBC = -1);
	void SetPin(int iBC, int iPin1, int iPin2);
	int GetPinCount() const;
	void GetPinAt(int index, int& iBC, int*& pin1, int*& pin2);
	bool GetPinCountAt(int iBC)const;
	void GetPinByBCId(int iBC, int& pin1, int& pin2)const;
	void RemovePinAt(int iBC);

	inline float GetRatioRealB() { return aRein.GetRatio1(); }    //����б�Ž���B���򵥱������ ʵ��
	inline float GetRatioRealH() { return aRein.GetRatio2(); }    //����б�Ž���H���򵥱������ ʵ��

	//�жϹ����ǲ��Ǵ��ֹ���
	BOOL IsSteel();
	//����ѹ������乹���Ľ��������ȵȼ�����ֵ���ֱ꡷��3.5.1
	//fKHB-������� fGHB-����ߺ��
	STEEL_SEC_S GetSecSlender(float* fKHB,float* fGHB);
	CString GetSecSlenderStr();

	//���㹹������λ�ƽ�
	BOOL GetThetaYield(float* f2, float* f3, float fPPy = 0.f);

	//���������նȷŴ�ϵ����iType-��������¥������ ��l0-����ȣ�sn-������
	float GetStiffnessCoe(int* iType, float l0 = -1.f, float sn = -1.f);
	// �����ӹ̽���ĳߴ磬B1������ȣ�  B2���Ҳ��ȣ� H1�������߶ȣ� H2���ײ��߶�  
	void GetReinforcedWidthAndHeight(const CSectionCollection* pSecCollection, float &B1, float &B2, float &H1, float &H2, float& T1, float& T2, REINFORCED_METHOD & iReinforcedMethod) const; // �������ӹ̵Ľ����ȡ��߶Ⱥͼӹ̷��� ��ҵ�� 2024��3��19��
};
