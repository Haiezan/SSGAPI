#pragma once
#include "HeadDefine.h"
#include "DataPrimitive.h"
#include "DataPlateStruc.h"

//三角形面单元，用于网格
class _SSG_DLLIMPEXP CTriangleElm : public CPrimitiveProp
{
public:
	CTriangleElm(void)
		: PlateStrucIDM(-1)
		, pVexIDM()
		, iBlock(0)
	{}

	//enum {nVex=3}; //边界点数，不重合
	int pVexIDM[3];  //端点ID数组
	int PlateStrucIDM; //关联的构件ID，用于获得配筋信息
	//STRUCT_TYPE iStrucType;

	//CFeaInterface生成接口数据时才产生，保存二进制文件
	int iBlock;  //分块ID

	//	int pVexIrr[3];

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

	//按照构件设置属性
	void CopyProp(const CPlateStruc &plate) 
	{
		*(CPrimitiveProp *)this=plate;
		//iStrucType=plate.iStrucType;
	}

	float Area(const CVertex *pNode) const;  //计算三角形面积>0,pNode为结点坐标数组
	float Area(const Vector4* pNode) const;
	float GetTcr() const; //计算单元临界步长

	void Clear(void) {PlateStrucIDM=-1;iBlock=0; /*memset(pVexIrr,0,sizeof(pVexIrr))*/;}

	//重新创建内存，复制原来数据，释放原来的内存。若新旧指针不是同一个变量时，调用程序应设置旧指针为NULL
	static CTriangleElm *Renew(CTriangleElm  *&oldp,int oldCount,int newCount)
	{
		if(oldCount==newCount) return oldp;

		CTriangleElm *newp=new CTriangleElm[newCount];
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

	BOOL LocalCoorVector(const CVertex *pVexArray,Vector4 &c00,Vector4 &u,Vector4 &v,Vector4 &w) const;

	//计算中心点坐标，pVex为全局结点数组,由于坐标会变形，因此这里要用传进来的坐标数组参数进行计算
	Vector4 GetCenter(const CVertex *pVex) const;

	//得到坐标范围
	void GetRange(const CVertex* pVexArray, Vector4 &rMin,Vector4 &rMax);

	virtual BOOL Read(CASCFile &fin); //派生类的虚函数关键字virtual可写可不写，但总是虚函数
	virtual BOOL Write(CASCFile &fout,int idf,int idf_Struct,STRUCT_TYPE itype, float area);

	virtual inline void ReadBin(CFile &fin);
	virtual inline BOOL WriteBin(CFile &fout);
};
