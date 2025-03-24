#pragma once

#include "DataStrucProp.h"
#include "ASCFile.h"

#include "DataBeamStruc.h"

//梁单元，用于网格
class _SSG_DLLIMPEXP CBeamElm : public CPrimitiveProp
{
public:
	CBeamElm()
		: iBlock(0)
		, BeamStrucIDM(-1)
		, dwFlag(0)
		, iArtiNode1(0)
		, iArtiNode2(0)
		, VexIDM1(-1)
		, VexIDM2(-1)
		, bHaveHinge(FALSE)
		, offset1()
		, offset2()
	{
	};


	union
	{
		struct
		{
			int VexIDM1,VexIDM2;  //端点IDM
		};
		int pVexIDM[2];
	};

	int BeamStrucIDM; //关联的构件ID，用于获得配筋信息
	//STRUCT_TYPE iStrucType;  //构件类型，主要用于opengl显示和属性查询

	//主梁构件铰接的两端会生成次梁铰接单元，因此这里要复制一份标识。
	DWORD dwFlag;	//按位控制，第0位：0--主梁，使用截面中的纤维，1--次梁(或剪力墙约束边缘构造柱)，不使用纤维信息。//第1位:1-延伸到墙里面的单元//2位1-1端半刚性3位1-2端半刚性
	int iArtiNode1,iArtiNode2;  //false--固接，true--铰接,与VexIDM1,VexIDM2对应 //铰接标识，0~6位代表U1~U11自由度是否铰接，1代表铰接

	//CFeaInterface生成接口数据时才产生，保存二进制文件
	int iBlock;  //分块ID,注意不是序号，不连续

	//int pVexIrr[2];

	DWORD dwHingeColor;  //塑性铰颜色  深蓝色不画
	BOOL bHaveHinge;

	Vector4 offset1;
	Vector4 offset2;

	//是否次梁单元
	BOOL IsSecendBeam(void) { return dwFlag&0x01; };

	//是否延伸的梁单元
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


	float Length(const CVertex *pVex)const;  //计算单元长度,pVex为结点坐标数组
	float GetTcr() const; //计算单元临界步长

	//得到坐标范围
	void GetRange(const CVertex* pVexArray, Vector4 &rMin,Vector4 &rMax);

	//按照构件设置属性
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
		iArtiNode1=iArtiNode2=0;
		VexIDM1=VexIDM2=-1;
		bHaveHinge=FALSE;

		//		memset(pVexIrr,0,sizeof(pVexIrr));
	}

	//重新创建内存，复制原来数据，释放原来的内存。若新旧指针不是同一个变量时，调用程序应设置旧指针为NULL
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

	//计算线构件局部坐标单位基矢量，考虑了转角
	void LocalCoorVector(const CVertex* pNode, const CBeamStruc* pBeam, const CLine* pLine, const CVertex* pVexArray, Vector4 &u,Vector4 &v,Vector4 &w) const;

	virtual BOOL Read(CASCFile &fin);
	virtual BOOL Write(CASCFile &fout,int idf,int idf_Struct,STRUCT_TYPE itype);

	virtual inline void ReadBin(CFile &fin);
	virtual inline BOOL WriteBin(CFile &fout);
};
