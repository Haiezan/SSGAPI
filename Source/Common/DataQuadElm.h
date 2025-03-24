#pragma once

#include <afxtempl.h>
#include <vector>
#include <map>

#include "HeadDefine.h"

using namespace std;

//�Ľ���ı����浥Ԫ����������
class _SSG_DLLIMPEXP CQuadElm : public CPrimitiveProp
{
public:
	CQuadElm(void)
		: PlateStrucIDM(-1)
		, pVexIDM()
		, iBlock(0)
	{}

	enum {VEXNUM=4}; //�߽���������غ�
	int pVexIDM[VEXNUM];  //�˵�ID����
	int PlateStrucIDM; //�����Ĺ���ID�����ڻ�������Ϣ
	//STRUCT_TYPE iStrucType;

	//CFeaInterface���ɽӿ�����ʱ�Ų���������������ļ�
	int iBlock;  //�ӿ��е�Ԫ����ID

	//	int pVexIrr[4];

	const CPlateStruc &GetPlate(const CArray<CPlateStruc,CPlateStruc&>  &aPlate) const
	{
		if(PlateStrucIDM<0 || PlateStrucIDM>=aPlate.GetCount()) return *(CPlateStruc *)NULL;
		return aPlate[PlateStrucIDM];
	}

	const CPlateStruc *GetPlateP(const CPlateStruc *pPlate,int nPlate) const
	{
		if(!pPlate) return NULL;
		if(PlateStrucIDM<0 || PlateStrucIDM>=nPlate) return NULL;
		return pPlate+PlateStrucIDM;
	}

	//���չ�����������
	void CopyProp(const CPlateStruc &plate) 
	{
		*(CPrimitiveProp *)this=plate;
		//iStrucType=plate.iStrucType;
	}

	float Area(const CVertex *pNode) const;  //�����ı������>0,pNodeΪ�����������
	float Area(const Vector4* pNode) const;
	float GetTcr() const; //���㵥Ԫ�ٽ粽��

	//�õ����귶Χ
	void GetRange(const CVertex* pVexArray, Vector4 &rMin,Vector4 &rMax);

	void Clear(void) {PlateStrucIDM=-1;iBlock=0; /*memset(pVexIrr,0,sizeof(pVexIrr))*/;}

	//���´����ڴ棬����ԭ�����ݣ��ͷ�ԭ�����ڴ档���¾�ָ�벻��ͬһ������ʱ�����ó���Ӧ���þ�ָ��ΪNULL
	static CQuadElm *Renew(CQuadElm  *&oldp,int oldCount,int newCount)
	{
		if(oldCount==newCount) return oldp;

		CQuadElm *newp=new CQuadElm[newCount];
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

	//wΪ���ߣ������ŷ������ֶ���u��v����������ϵû�й�ϵ
	BOOL LocalCoorVector(const CVertex *pVexArray,Vector4 &c00,Vector4 &u,Vector4 &v,Vector4 &w) const;

	//�������ĵ����꣬pVexΪȫ�ֽ�����飬�������Ҫ�ô���������������������м���
	Vector4 GetCenter(const CVertex *pVex) const;

	virtual BOOL Read(CASCFile &fin); //��������麯���ؼ���virtual��д�ɲ�д���������麯��
	virtual BOOL Write(CASCFile &fout,int idf,int idf_Struct,STRUCT_TYPE itype, float area);

	virtual void ReadBin(CFile &fin);
	virtual BOOL WriteBin(CFile &fout);
};
