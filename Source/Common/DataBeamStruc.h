#pragma once

#include "DataStrucProp.h"
#include "ASCFile.h"

class CSectionCollection;
class CDamperSectionCollection;

class CVertex;
class CLine;

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
	������  0   �� 0    ��0     �� ���� ����������ת������ ���� �� ����   ��
	�ǩ��贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈��������
	������  0   �� 0    ��0     �� 0    ��0     ��0     �� 0    ����֧��  ��
	�ǩ��贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈��������
	���ũ�  0   �� 0    ��0     �� 0    ��0     ��0     �� 0    ������֧�ũ�
	�����ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ���������
	*/
	int iSubType;	//�����ͣ����Լ�¼һ�����ӵ������� 

	BOOL bArtiNode1,bArtiNode2;	//��Ӧ�Ķ˵��Ƿ�½ӣ�FALSEΪ�̽�,��ѡĳ���������������Ķ˵�Ϊ�½ӣ������ʹ������ɽ½ӣ��������˻�һ�˽½�
	int iBottomStory; //�׵�¥��ţ�����б����Ч����ʱ����
	//�����������ߵķ���ǣ���λ���ȣ�2->3����Ϊ��,fAng�ṩ���û��޸�,�޸ĺ���������CalRefPoint����ο���
	float fRotateAng;  //�޸�ת��ʱ��Ҫ���¾ֲ�����
	float fOffsetX1,fOffsetY1,fOffsetZ1;  //�׵�ƫ�ƾ��루m��,�ֲ�����ϵ������ΪX
	float fOffsetX2,fOffsetY2,fOffsetZ2;  //ĩ��ƫ�ƾ��루m��
	float fRatio1,fRatio2;  //����ʣ��������׽����б�ţ�B��H����ĵ�������ʣ������ǽ,��λ���ٷ���
	float fCornerArea;  //һ���ǽ�����(m^2)������б����Ч
	float f_StirArea_D,f_StirArea_UD;  //�������������, �Ǽ����������������������б����Ч
	float fDefectY;// �ֲ�����y���Ӧ��ʼȱ�ݵ���
	float fDefectZ;// �ֲ�����z���Ӧ��ʼȱ�ݵ���
	float fEffectStiff[6];//��Ч�ն�  һ��������
	float fEffectDamp[6];//��Ч����  һ��������
	CString sAppendMat;		//���Ӳ���  ������Ч

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

	BOOL IsPropEqual(const CBeamStruc &beam) const;  //���пɺϲ�������

	//�Ƿ���������,����ֻ�������أ����ṩ�նȵ�Ԫ������
	BOOL IsVirtualBeam(void) const 
	{
		return (iStrucType==STRUCT_BEAM && (iSubType&0x10)) || iStrucType==STRUCT_HIDEBEAM;
	} 

	float GetWidth(const CSectionCollection *pSecCollection,const CDamperSectionCollection *pDamperSecCollection) const; //������
	float GetHeight(const CSectionCollection *pSecCollection,const CDamperSectionCollection *pDamperSecCollection) const; //�߶ȷ�Χ

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
		bArtiNode1=beam.bArtiNode1;
		bArtiNode2=beam.bArtiNode2;
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

		fDefectY=beam.fDefectY;// �ֲ�����y���Ӧ��ʼȱ�ݵ���
		fDefectZ=beam.fDefectZ;// �ֲ�����z���Ӧ��ʼȱ�ݵ���

		for(int i=0;i<6;i++)
		{
			fEffectStiff[i]=beam.fEffectStiff[i];
			fEffectDamp[i]=beam.fEffectDamp[i];
		}
		sAppendMat = beam.sAppendMat;

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


	//Ҫ�����ȶ������Ͳ�������
	virtual BOOL Read(CASCFile &fin,STRUCT_TYPE iType,CDamperSectionCollection &cDamperSection,
		CSectionCollection &cSection,CProjectPara &cPrjPara,CArray<CLine,CLine&> &aLine,CArray<CVertex,CVertex&>&aVex);
	virtual BOOL Write(CASCFile &fout,int idf);
	virtual BOOL Write2020(CASCFile &fout,int idf);
	//�����Ϣ��д
	virtual BOOL ReadDesignInfo(CASCFile &fin,STRUCT_TYPE iType,int idf);
	virtual BOOL WriteDesignInfo(CASCFile &fout,int idf);
	virtual BOOL WriteDesignInfo2020(CASCFile &fout,int idf);

	void GenLoadId(bool bRewrite=true);//��	float fDeadLoad ��float fLiveLoad����Load����mapload ��2020֮��汾��ȡ
	void GenLoadVal();//��mapload����fDeadLoad��fLiveLoad ��2020֮ǰ�汾��ȡ

	void GetInitialImperfection(bool bRewrite=false);
	//�����Ż�ת
	BOOL ChangeStrucType(STRUCT_TYPE iType);
	//һ������ת������
	BOOL Link2Beam(const CBeamStruc &beam);
	//������תһ������
	BOOL Beam2Link(const CBeamStruc &Link);
};
