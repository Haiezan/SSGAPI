#pragma once

#include "DataPrimitive.h"


//LOADASSIGN 
#include "Loadmap.h"

//结构属性
class _SSG_DLLIMPEXP CStrucProp : public CPrimitiveProp
{
public:
	CStrucProp(void);
	//复制构造函数
	CStrucProp(const CStrucProp &prop) 
	{
		aload.clear();
		*this=prop;
	}

	~CStrucProp()
	{
		aElms.RemoveAll();
		aload.clear();
	};
	int PmID;
	STRUCT_TYPE iStrucType;

	CString ConcMat;         //砼材料
	CString RebarMat;        //钢筋材料,边缘构件或连梁纵筋材料放在RebarMat里，质量也放在钢筋变量里
	CString StirrupMat;      //箍筋材料	//乔保娟 2015.6.5
	CString SteelMat;		 //型钢材料

	float fDeadLoad; //恒荷载，单位面积或单位长度,板KN/m2，梁KN/m,向下为正，斜板按实际面积计算，斜梁按实际长度计算
	float fLiveLoad; //活荷载，单位面积或单位长度,板KN/m2，梁KN/m,向下为正，斜板按实际面积计算，斜梁按实际长度计算

	int iMidSeismContstiType;//中震性能目标 0弹塑性1弹性
	int iRareSeismContstiType;//大震性能目标 0弹塑性1弹性
	int iVipType;//构件类型：0-未分类，1-关键构件，2-普通竖向构件，3-耗能构件
	int iSeismicGrade;//抗震等级
	int iDatailsGrade;//抗震构造等级
	CString sMemberName;//构件名称
	LOADASSIGN aload;//对应荷载工况的荷载
	float fAxisFactor;			//轴力调整系数
	float fMomentFactor;	//弯矩调整系数
	float fShearFactor;		//剪力调整系数

	//临时数据
	CArray<int,int> aElms;  //单元集合,梁单元和三角形单元编号为原始序号，四边形单元编号=m_nTriangle+i,生成全部网格以及读入网格后形成


	CStrucProp & operator=(const CStrucProp &prop)
	{
		if(this==&prop) return *this;

		*(CPrimitiveProp *)this=(CPrimitiveProp &)prop;
		PmID=prop.PmID;
		iStrucType=prop.iStrucType;

		ConcMat=prop.ConcMat;        
		RebarMat=prop.RebarMat;   
		StirrupMat=prop.StirrupMat;  
		SteelMat=prop.SteelMat; 

		fDeadLoad=prop.fDeadLoad;
		fLiveLoad=prop.fLiveLoad;

		iMidSeismContstiType=prop.iMidSeismContstiType;
		iRareSeismContstiType=prop.iRareSeismContstiType;
		iVipType=prop.iVipType;

		iSeismicGrade=prop.iSeismicGrade;
		iDatailsGrade=prop.iDatailsGrade;
		sMemberName=prop.sMemberName;

		aload=prop.aload;

		fAxisFactor = prop.fAxisFactor;			//轴力调整系数
		fMomentFactor = prop.fMomentFactor;	//弯矩调整系数
		fShearFactor = prop.fShearFactor;		//剪力调整系数

		//由于框架复制时不存在单元数据，因此不需要复制
		aElms.RemoveAll();

		return *this;
	}
	//virtual BOOL Read(CASCFile &fin);   
	//virtual BOOL Write(CASCFile &fout);

	//virtual void ReadBin(CFile &fin);   
	//virtual BOOL WriteBin(CFile &fout);
};

