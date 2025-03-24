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
	TYPE_S0 = -1, //未计算
	TYPE_S1 = 0, 
	TYPE_S2,
	TYPE_S3,
	TYPE_S4,
	TYPE_S5,
	TYPE_EX, //超限
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
	┃梁┃  0   ┃ 0    ┃加固梁┃ 虚梁 ┃刚性梁┃转换梁┃ 连梁 ┃ 次梁   ┃
	┣━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━━┫
	┃柱┃  0   ┃ 0    ┃加固柱┃ 0    ┃0     ┃0     ┃ 0    ┃框支柱  ┃
	┣━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━━┫
	┃撑┃  0   ┃ 0    ┃加固撑┃ 0    ┃0     ┃0     ┃ 0    ┃耗能支撑┃
	┗━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━━┛
	*/
	int iSubType;	//子类型，可以记录一般连接的子类型 
	//铰接标识，0~6位代表U1~U11自由度是否铰接，1代表铰接
	int iArtiNode1, iArtiNode2;	//对应的端点是否铰接，FALSE为固接,点选某个梁构件，靠近的端点为铰接，主梁和次梁均可铰接，可以两端或一端铰接
	int iBottomStory; //底点楼层号，柱和斜撑有效，暂时不用
	//截面绕梁轴线的方向角，单位：度，2->3方向为正,fAng提供给用户修改,修改后立即调用CalRefPoint计算参考点
	float fRotateAng;  //修改转角时需要更新局部坐标
	float fOffsetX1,fOffsetY1,fOffsetZ1;  //首点偏移距离（m）,局部坐标系，轴向为X
	float fOffsetX2,fOffsetY2,fOffsetZ2;  //末点偏移距离（m）
	float fRatio1,fRatio2;  //配筋率，梁：面筋、底筋。柱和斜撑：B、H方向的单边配筋率（包含角筋）,单位：百分数
	float fCornerArea;  //一根角筋的面积(m^2)，柱和斜撑有效
	float f_StirArea_D,f_StirArea_UD;  //加密区箍筋面积, 非加密区箍筋面积，梁、柱、斜撑有效

	//修改构件初始缺陷定义方式 20221109贾苏修改
	float fDefect; //初始缺陷代表值的倒数
	float fDefectAngle; //初始缺陷反向
	//float fDefectY;// 局部坐标y轴对应初始缺陷倒数
	//float fDefectZ;// 局部坐标z轴对应初始缺陷倒数	

	float fEffectStiff[6];//等效刚度  一般连接用；刚度放大系数 梁构件用 贾苏
	float fEffectDamp[6];//等效阻尼  一般连接用
	BOOL GetEffectPara(); //一般连接用，刷新构件等效刚度 贾苏
	CString sAppendMat;		//附加材料  柱子有效
	int iNode1Sec;//一端截面	
	int iNode2Sec;//二端截面
	int iShearNonlinear; //是否考虑剪切铰弹塑性，0为弹性，1为弹塑性 周璋鑫 20230110
	float fBeamSpan; //构件跨度(仅针对剪切铰弹塑性的构件，其余构件为0) 周璋鑫 20230112
	int iReinforcedSec;//加固方法截面id
	//int iPin;        //铰接标识，0~11位代表U1~U11自由度是否铰接，1代表铰接
	CPinData aPin;
	//reinforcement
	CReinforcement aRein;

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

	// 新增加固梁 辛业文 辛业文 2023年4月14日
	BOOL IsReinForcedBeam(void) const
	{
		return   (iStrucType == STRUCT_BEAM && (iSubType & 0x20));
	}

	// 新增加固构件
	BOOL IsReinForcedPillar(void) const
	{
		return   (iStrucType == STRUCT_PILLAR && (iSubType & 0x20));
	}

	// 新增加固斜撑
	BOOL IsReinForcedBracing(void) const
	{
		return   (iStrucType == STRUCT_BRACING && (iSubType & 0x20));
	}

	BOOL IsReinForced()const;

	BOOL IsReinForcedConc()const;
	BOOL IsReinForcedFiber()const;

	BOOL IsPropEqual(const CBeamStruc &beam) const;  //具有可合并的属性

	//是否虚梁或暗梁,虚梁只传导荷载，不提供刚度单元和自重
	BOOL IsVirtualBeam(void) const 
	{
		return (iStrucType==STRUCT_BEAM && (iSubType&0x10)) || iStrucType==STRUCT_HIDEBEAM;
	} 

	float GetWidth(const CSectionCollection *pSecCollection,const CDamperSectionCollection *pDamperSecCollection) const; //截面宽度
	float GetHeight(const CSectionCollection *pSecCollection,const CDamperSectionCollection *pDamperSecCollection) const; //高度范围
	void GetBeamStiffness(float* fStiff, bool bForSemiRigid = false);

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

		fDefect = beam.fDefect; //初始缺陷代表值倒数
		fDefectAngle = beam.fDefectAngle; //初始缺陷方向

		memcpy(fEffectStiff, beam.fEffectStiff, sizeof(float) * 6);
		memcpy(fEffectDamp, beam.fEffectDamp, sizeof(float) * 6);

		sAppendMat = beam.sAppendMat;
		iNode1Sec = beam.iNode1Sec;
		iNode2Sec = beam.iNode2Sec;
		iShearNonlinear = beam.iShearNonlinear; //周璋鑫 20230110
		fBeamSpan = beam.fBeamSpan; //周璋鑫 20230112
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

	//计算构件重量，单位：kN
	float GetWeight();


	//要求事先读入截面和材料数据
	virtual BOOL Read(CASCFile &fin,STRUCT_TYPE iType,CDamperSectionCollection &cDamperSection,
		CSectionCollection &cSection,const CProjectPara &cPrjPara,CArray<CLine,CLine&> &aLine,CArray<CVertex,CVertex&>&aVex);
	virtual BOOL Write(CASCFile &fout,int idf);
	virtual BOOL Write2020(CASCFile &fout,int idf);
	//设计信息读写
	virtual BOOL ReadDesignInfo(CASCFile &fin,STRUCT_TYPE iType, const CSectionCollection& cSection, int idf);
	virtual BOOL WriteDesignInfo(CASCFile &fout,int idf);
	virtual BOOL WriteDesignInfo2020(CASCFile &fout,int idf);

	void GenLoadId(bool bRewrite=true);//由	float fDeadLoad 和float fLiveLoad生成Load加入mapload 供2020之后版本读取
	void GenLoadVal();//由mapload生成fDeadLoad和fLiveLoad 供2020之前版本读取

	//获取构件初始缺陷 Direction初始缺陷方向0-Y,1-Z
	void GetInitialImperfection(bool bRewrite = false, int Direction = 0);
	void GetDefect(float& fDefect2, float& fDefect3);
	//梁柱撑互转
	BOOL ChangeStrucType(STRUCT_TYPE iType);
	//一般连接转梁柱撑
	BOOL Link2Beam(const CBeamStruc &beam);
	//梁柱撑转一般连接
	BOOL Beam2Link(const CBeamStruc &Link);

	BOOL GetEndElmId(int& iID1, int& iID2); //获取构件端点的单元节点号

	//加固
	//梁构件钢筋纤维,给定配筋率和钢筋直径，只对混凝土截面进行配筋，截面中最多只有一个混凝土截面，返回纤维坐标动态内存及纤维个数，不保存到类成员临时数组
	//配筋，ratioUpper面筋配筋率,ratioLower底筋配筋率,单位1
	void* CreateReinForcedBeamRebar();
	//柱构件钢筋纤维,给定配筋率和钢筋直径，只对混凝土截面进行配筋，截面中最多只有一个混凝土截面，返回纤维坐标动态内存及纤维个数，不保存到类成员临时数组
	//配筋，ratioB--B方向配筋率,ratioH--H方向配筋率，圆截面只用第一个配筋率,单位1
	void* CreateReinForcedPillarRebar();

	void* CreateReinForcedSteel();

	void SetPin(int iPin, bool bFirst, int iBC = -1);
	void SetPin(int iBC, int iPin1, int iPin2);
	int GetPinCount() const;
	void GetPinAt(int index, int& iBC, int*& pin1, int*& pin2);
	bool GetPinCountAt(int iBC)const;
	void GetPinByBCId(int iBC, int& pin1, int& pin2)const;
	void RemovePinAt(int iBC);

	inline float GetRatioRealB() { return aRein.GetRatio1(); }    //柱、斜撑截面B方向单边配筋率 实配
	inline float GetRatioRealH() { return aRein.GetRatio2(); }    //柱、斜撑截面H方向单边配筋率 实配

	//判断构件是不是纯钢构件
	BOOL IsSteel();
	//计算压弯和受弯构件的截面板件宽厚比等级及限值《钢标》表3.5.1
	//fKHB-截面宽厚比 fGHB-截面高厚比
	STEEL_SEC_S GetSecSlender(float* fKHB,float* fGHB);
	CString GetSecSlenderStr();

	//计算构件屈服位移角
	BOOL GetThetaYield(float* f2, float* f3, float fPPy = 0.f);

	//计算中梁刚度放大系数，iType-构件相连楼板数量 ，l0-梁跨度，sn-梁净距
	float GetStiffnessCoe(int* iType, float l0 = -1.f, float sn = -1.f);
	// 梁柱加固截面的尺寸，B1：左侧宽度；  B2：右侧宽度； H1：顶部高度； H2：底部高度  
	void GetReinforcedWidthAndHeight(const CSectionCollection* pSecCollection, float &B1, float &B2, float &H1, float &H2, float& T1, float& T2, REINFORCED_METHOD & iReinforcedMethod) const; // 梁、柱加固的截面宽度、高度和加固方法 辛业文 2024年3月19日
};
