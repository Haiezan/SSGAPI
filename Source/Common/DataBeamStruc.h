#pragma once

#include "DataStrucProp.h"
#include "ASCFile.h"

class CSectionCollection;
class CDamperSectionCollection;

class CVertex;
class CLine;

//线状构件，由一个线段组成
class _SSG_DLLIMPEXP CBeamStruc : public CStrucProp
{
public:
	CBeamStruc(void);
	//复制构造函数
	CBeamStruc(const CBeamStruc &beam) 
	{
		*this=beam;
	};

	CBeamStruc(STRUCT_TYPE istructype,int lineid,int istory,DWORD color);
	~CBeamStruc()
	{

	};

	//int id; //本构件的id，从1开始编号，各类线构件独立编号
	int LineIDM; //结构线编号
	int iSectionID;  //截面ID

	/*
	线构件子类型
	┏━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━━┓
	┃  ┃  Bit7┃ Bit6 ┃ Bit5 ┃ Bit4 ┃ Bit3 ┃ Bit2 ┃ Bit1 ┃ Bit0   ┃
	┣━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━━┫
	┃梁┃  0   ┃ 0    ┃0     ┃ 虚梁 ┃刚性梁┃转换梁┃ 连梁 ┃ 次梁   ┃
	┣━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━━┫
	┃柱┃  0   ┃ 0    ┃0     ┃ 0    ┃0     ┃0     ┃ 0    ┃框支柱  ┃
	┣━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━━┫
	┃撑┃  0   ┃ 0    ┃0     ┃ 0    ┃0     ┃0     ┃ 0    ┃耗能支撑┃
	┗━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━━┛
	*/
	int iSubType;	//子类型，可以记录一般连接的子类型 

	BOOL bArtiNode1,bArtiNode2;	//对应的端点是否铰接，FALSE为固接,点选某个梁构件，靠近的端点为铰接，主梁和次梁均可铰接，可以两端或一端铰接
	int iBottomStory; //底点楼层号，柱和斜撑有效，暂时不用
	//截面绕梁轴线的方向角，单位：度，2->3方向为正,fAng提供给用户修改,修改后立即调用CalRefPoint计算参考点
	float fRotateAng;  //修改转角时需要更新局部坐标
	float fOffsetX1,fOffsetY1,fOffsetZ1;  //首点偏移距离（m）,局部坐标系，轴向为X
	float fOffsetX2,fOffsetY2,fOffsetZ2;  //末点偏移距离（m）
	float fRatio1,fRatio2;  //配筋率，梁：面筋、底筋。柱和斜撑：B、H方向的单边配筋率（包含角筋）,单位：百分数
	float fCornerArea;  //一根角筋的面积(m^2)，柱和斜撑有效
	float f_StirArea_D,f_StirArea_UD;  //加密区箍筋面积, 非加密区箍筋面积，梁、柱、斜撑有效
	float fDefectY;// 局部坐标y轴对应初始缺陷倒数
	float fDefectZ;// 局部坐标z轴对应初始缺陷倒数
	float fEffectStiff[6];//等效刚度  一般连接用
	float fEffectDamp[6];//等效阻尼  一般连接用
	CString sAppendMat;		//附加材料  柱子有效

	//临时数据，不保存文件,u.x>1不合法，初始化u.x=10.0f表示未计算，读入、增加、移动端点和修改转角时需要调用BeamLocalCoorVector重新计算
	Vector4 u,v,w;  //局部坐标系基矢量及坐标原点，w为法线方向,

	BOOL IsSecondBeam(void) const {return iStrucType==STRUCT_BEAM && iSubType&0x01;}	 //FALSE--主梁，使用截面中的纤维，TRUE-次梁，不使用纤维信息，只对梁构件有效
	void SetSecondBeam(BOOL bSecondBeam) 
	{
		if(iStrucType!=STRUCT_BEAM) return;
		if(bSecondBeam)
			iSubType |= 0x01; 
		else
			iSubType &= ~0x01; 
	}

	BOOL IsPropEqual(const CBeamStruc &beam) const;  //具有可合并的属性

	//是否虚梁或暗梁,虚梁只传导荷载，不提供刚度单元和自重
	BOOL IsVirtualBeam(void) const 
	{
		return (iStrucType==STRUCT_BEAM && (iSubType&0x10)) || iStrucType==STRUCT_HIDEBEAM;
	} 

	float GetWidth(const CSectionCollection *pSecCollection,const CDamperSectionCollection *pDamperSecCollection) const; //截面宽度
	float GetHeight(const CSectionCollection *pSecCollection,const CDamperSectionCollection *pDamperSecCollection) const; //高度范围

	//得到坐标范围
	void GetRange(Vector4 &rMin,Vector4 &rMax);

	void Clear(void);

	//赋值运算符重载
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

		fDefectY=beam.fDefectY;// 局部坐标y轴对应初始缺陷倒数
		fDefectZ=beam.fDefectZ;// 局部坐标z轴对应初始缺陷倒数

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

	//计算线构件局部坐标单位基矢量，考虑了转角
	//水平构件：e1为轴线方向，e2、e3为截面局部坐标方向
	//竖向构件：e1=eZ为轴线方向，e2、e3为截面局部坐标方向
	void BeamLocalCoorVector(CArray<CVertex,CVertex&>&aVex,CArray<CLine,CLine&> &aLine);

	//根据首尾点坐标计算参考点，垂直构件和非垂直构件定义方式不同，ang为方向角，单位：度
	CVertex CalRefPoint(const CVertex &v1,const CVertex &v2,float ang); 
	//根据首尾点坐标和类型计算参考点，柱子和边缘构件按绕整体X轴转角，其他构件按照局部初始Z轴转角定义，ang为方向角，单位：度
	CVertex CalRefPoint(const CVertex &v1,const CVertex &v2,STRUCT_TYPE type,float ang);

	//int GetSectionIDM(){return SectionIDM;} //获得截面ID
	inline float GetRatioUpper(){return fRatio1;}  //梁截面面筋配筋率
	inline float GetRatioLower(){return fRatio2;}  //梁截面底筋配筋率
	inline float GetRatioB(){return fRatio1;}    //柱、斜撑截面B方向单边配筋率
	inline float GetRatioH(){return fRatio2;}    //柱、斜撑截面H方向单边配筋率

	float Length(const CLine *pLine,const CVertex *pVex) const;  //计算构件长度， pLine为结构线数组，pVex为顶点坐标数组
	BOOL Weight(float fConcArea, float fSteelArea, float fRebarArea, float &wConc, float &wSt, float &wRebar); //计算重力，单位kN


	//要求事先读入截面和材料数据
	virtual BOOL Read(CASCFile &fin,STRUCT_TYPE iType,CDamperSectionCollection &cDamperSection,
		CSectionCollection &cSection,CProjectPara &cPrjPara,CArray<CLine,CLine&> &aLine,CArray<CVertex,CVertex&>&aVex);
	virtual BOOL Write(CASCFile &fout,int idf);
	virtual BOOL Write2020(CASCFile &fout,int idf);
	//设计信息读写
	virtual BOOL ReadDesignInfo(CASCFile &fin,STRUCT_TYPE iType,int idf);
	virtual BOOL WriteDesignInfo(CASCFile &fout,int idf);
	virtual BOOL WriteDesignInfo2020(CASCFile &fout,int idf);

	void GenLoadId(bool bRewrite=true);//由	float fDeadLoad 和float fLiveLoad生成Load加入mapload 供2020之后版本读取
	void GenLoadVal();//由mapload生成fDeadLoad和fLiveLoad 供2020之前版本读取

	void GetInitialImperfection(bool bRewrite=false);
	//梁柱撑互转
	BOOL ChangeStrucType(STRUCT_TYPE iType);
	//一般连接转梁柱撑
	BOOL Link2Beam(const CBeamStruc &beam);
	//梁柱撑转一般连接
	BOOL Beam2Link(const CBeamStruc &Link);
};
