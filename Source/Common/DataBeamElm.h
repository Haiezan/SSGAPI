#pragma once

#include "DataStrucProp.h"
#include "ASCFile.h"

#include "DataBeamStruc.h"

//����Ԫ����������
class _SSG_DLLIMPEXP CBeamElm : public CPrimitiveProp
{
public:
	CBeamElm(){	Clear();}

	union
	{
		struct
		{
			int VexIDM1,VexIDM2;  //�˵�IDM
		};
		int pVexIDM[2];
	};

	int BeamStrucIDM; //�����Ĺ���ID�����ڻ�������Ϣ
	//STRUCT_TYPE iStrucType;  //�������ͣ���Ҫ����opengl��ʾ�����Բ�ѯ

	//���������½ӵ����˻����ɴ����½ӵ�Ԫ���������Ҫ����һ�ݱ�ʶ��
	DWORD dwFlag;	//��λ���ƣ���0λ��0--������ʹ�ý����е���ά��1--����(�����ǽԼ����Ե������)����ʹ����ά��Ϣ��//��1λ:1-���쵽ǽ����ĵ�Ԫ
	BOOL bArtiNode1,bArtiNode2;  //false--�̽ӣ�true--�½�,��VexIDM1,VexIDM2��Ӧ

	//CFeaInterface���ɽӿ�����ʱ�Ų���������������ļ�
	int iBlock;  //�ֿ�ID,ע�ⲻ����ţ�������

	//int pVexIrr[2];

	DWORD dwHingeColor;  //���Խ���ɫ  ����ɫ����
	BOOL bHaveHinge;

	//�Ƿ������Ԫ
	BOOL IsSecendBeam(void) { return dwFlag&0x01; };

	//�Ƿ����������Ԫ
	BOOL IsExtendElm(void)const { return dwFlag&0x02; };

	const CBeamStruc &GetBeam(const CArray<CBeamStruc,CBeamStruc&>  &aBeam) const
	{
		if(BeamStrucIDM<0 || BeamStrucIDM>=aBeam.GetCount()) return *(CBeamStruc *)NULL;
		return aBeam[BeamStrucIDM];
	}

	const CBeamStruc *GetBeamP(const CBeamStruc *pBeam,int nBeamStruct) const
	{
		if(!pBeam) return NULL;
		if(BeamStrucIDM<0 || BeamStrucIDM>=nBeamStruct) return NULL;
		return pBeam+BeamStrucIDM;
	}


	float Length(const CVertex *pVex);  //���㵥Ԫ����,pVexΪ�����������

	//�õ����귶Χ
	void GetRange(Vector4 &rMin,Vector4 &rMax);

	//���չ�����������
	void CopyProp(const CBeamStruc &beam)
	{
		*(CPrimitiveProp *)this=beam;
		if(beam.IsSecondBeam())
			dwFlag |= 0x01;
		else
			dwFlag &= ~0x01;
	}

	void Clear(void)
	{
		iBlock=0;
		BeamStrucIDM=-1;
		dwFlag=0;
		bArtiNode1=bArtiNode2=FALSE;
		VexIDM1=VexIDM2=-1;
		bHaveHinge=FALSE;

		//		memset(pVexIrr,0,sizeof(pVexIrr));
	}

	//���´����ڴ棬����ԭ�����ݣ��ͷ�ԭ�����ڴ档���¾�ָ�벻��ͬһ������ʱ�����ó���Ӧ���þ�ָ��ΪNULL
	static CBeamElm *Renew(CBeamElm  *&oldp,int oldCount,int newCount)
	{
		if(oldCount==newCount) return oldp;

		CBeamElm *newp=new CBeamElm[newCount];
		if(!newp) return NULL;

		int k=min(oldCount,newCount);
		for(int i=0;i<k;i++)
		{
			newp[i]=oldp[i];
		}
		delete[] oldp;
		oldp=newp;
		return newp;
	}

	//�����߹����ֲ����굥λ��ʸ����������ת��
	void LocalCoorVector(Vector4 &u,Vector4 &v,Vector4 &w) const;

	virtual BOOL Read(CASCFile &fin);
	virtual BOOL Write(CASCFile &fout,int idf,int idf_Struct,STRUCT_TYPE itype);

	virtual inline void ReadBin(CFile &fin);
	virtual inline BOOL WriteBin(CFile &fout);
};