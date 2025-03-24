#pragma once

#include "DataPrimitive.h"

//LOADASSIGN 
#include "Loadmap.h"
#include "DefectCaseMbr.h"

//结构属性
class _SSG_DLLIMPEXP CStrucProp : public CPrimitiveProp
{
public:
	CStrucProp(void);
	//复制构造函数
	CStrucProp(const CStrucProp &prop) 
	{
		*this=prop;
	}

	~CStrucProp()
	{
		aElms.RemoveAll();
		aload.clear();
		aDefect.clear();
	};

	void Clear();

	int PmID;
	STRUCT_TYPE iStrucType;

	CString ConcMat;         //砼材料
	CString RebarMat;        //钢筋材料,边缘构件或连梁纵筋材料放在RebarMat里，质量也放在钢筋变量里
	CString StirrupMat;      //箍筋材料	//乔保娟 2015.6.5
	CString SteelMat;		 //型钢材料
	CString sComments2;  //用于显示的说明文字,由程序随时更新//显示第二个节点力 

	float fDeadLoad; //恒荷载，单位面积或单位长度,板KN/m2，梁KN/m,向下为正，斜板按实际面积计算，斜梁按实际长度计算
	float fLiveLoad; //活荷载，单位面积或单位长度,板KN/m2，梁KN/m,向下为正，斜板按实际面积计算，斜梁按实际长度计算

	int iMidSeismContstiType;//中震性能目标 0弹塑性1弹性
	int iRareSeismContstiType;//大震性能目标 0弹塑性1弹性
	int iRareNormSectPerformObject;  //大震正截面性能目标 0不考虑 1弹性 2不屈服 3极限承载力
	int iRareDiagSectPerformObject;  //大震斜截面性能目标 0不考虑 1弹性 2不屈服 3极限承载力
	int iMidNormSectPerformObject;  //大震正截面性能目标 0不考虑 1弹性 2不屈服 3极限承载力
	int iMidDiagSectPerformObject;  //大震斜截面性能目标 0不考虑 1弹性 2不屈服 3极限承载力
	int iVipType;//构件类型：0-未分类，1-关键构件，2-普通竖向构件，3-耗能构件
	int iSeismicGrade;//抗震等级
	int iDatailsGrade;//抗震构造等级
	CString sMemberName;//构件名称
	LOADASSIGN aload;//对应荷载工况的荷载
	LOADASSIGN aDyload;//对应荷载工况的动荷载 贾苏20230412

	float fAxisFactor;			//轴力调整系数
	float fMomentFactor;	//弯矩调整系数
	float fShearFactor;		//剪力调整系数
	float fAxisFactorR;		//轴向承载力调整系数
	float fMomentFactorR;	//抗弯承载力调整系数	
	float fShearFactorR;	//抗剪承载力调整系数	
	float fMeshRatio; //网格加密系数，>1加密，保存在单独数据段

	//构件初始缺陷 20221114贾苏增加
	DEFECTASSIGN aDefect; //对应缺陷工况的缺陷值

	//临时数据
	CArray<int,int> aElms;  //单元集合,梁单元和三角形单元编号为原始序号，四边形单元编号=m_nTriangle+i,生成全部网格以及读入网格后形成
	unsigned int tmp_Msg; //临时构件信息传递,注意使用后恢复,0x01-存在非协调网格


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
		sComments2 = prop.sComments2;

		fDeadLoad=prop.fDeadLoad;
		fLiveLoad=prop.fLiveLoad;

		iMidSeismContstiType=prop.iMidSeismContstiType;
		iRareSeismContstiType=prop.iRareSeismContstiType;
		iMidNormSectPerformObject = prop.iMidNormSectPerformObject;
		iMidDiagSectPerformObject = prop.iMidDiagSectPerformObject;
		iRareNormSectPerformObject = prop.iRareNormSectPerformObject;
		iRareDiagSectPerformObject = prop.iRareDiagSectPerformObject;

		iVipType=prop.iVipType;

		iSeismicGrade=prop.iSeismicGrade;
		iDatailsGrade=prop.iDatailsGrade;
		sMemberName=prop.sMemberName;

		aload=prop.aload;
		aDyload = prop.aDyload;

		fAxisFactor = prop.fAxisFactor;			//轴力调整系数
		fMomentFactor = prop.fMomentFactor;	//弯矩调整系数
		fShearFactor = prop.fShearFactor;		//剪力调整系数

		fAxisFactorR = prop.fAxisFactorR;			//轴力调整系数
		fMomentFactorR = prop.fMomentFactorR;	//弯矩调整系数
		fShearFactorR = prop.fShearFactorR;		//剪力调整系数
		fMeshRatio = prop.fMeshRatio;

		//由于框架复制时不存在单元数据，因此不需要复制
		aElms.RemoveAll();
		tmp_Msg = 0;

		return *this;
	}
	//virtual BOOL Read(CASCFile &fin);   
	//virtual BOOL Write(CASCFile &fout);

	//virtual void ReadBin(CFile &fin);   
	//virtual BOOL WriteBin(CFile &fout);
	float GetC(); //计算波速
};

struct PIN
{
	int IdBC;
	int Pin1;
	int Pin2;
	PIN() :IdBC(-1), Pin1(0), Pin2(0) {}
	PIN(int bc, int ip1, int ip2) :IdBC(bc), Pin1(ip1), Pin2(ip2) {};
	PIN& operator=(const PIN& Pin)
	{
		if (this == &Pin)
			return *this;

		IdBC = Pin.IdBC;
		Pin1 = Pin.Pin1;
		Pin2 = Pin.Pin2;
		return *this;
	}
};

class _SSG_DLLIMPEXP CPinData
{
public:
	CPinData();
	~CPinData();
	CPinData(const CPinData& aPin)
	{
		*this = aPin;
	};
	CPinData& operator=(const CPinData& aPin);

	void clear();
	int Find(int iBC) const;
	void SetPin(int iBC, int iPin1, int iPin2);
	void SetPin(int iBC, bool bFirst, int iPin);
	bool GetPin(int iBC, int& iPin1, int& iPin2)const;
	void GetPinAt(int index, int& iBC, int& iPin1, int& iPin2);
	void GetPinAt(int index, int& iBC, int*& iPin1, int*& iPin2);
	void RemoveAt(int iBC);
	void CopyPin(int iCurBC, int iAimBC, bool bTrans = false);
public:
	PIN* pPin;
	int nPin;
};