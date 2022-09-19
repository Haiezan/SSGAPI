#pragma once
#include "HeadDefine.h"
#include "SectionBaseHead.h"
#include "DataStrucProp.h"

class CVertex;
class CLine;
class CPlateSectionCollection;
class CProjectPara;

//面状构件，由多个线段组成多边形，里面含动态数组，类数组删除时要先调用CPlateStruc::Clear()
class _SSG_DLLIMPEXP CPlateStruc: public CStrucProp
{
public:
	CPlateStruc(void);

	CPlateStruc(const CPlateStruc &plate)
	{
		pLineIDM=NULL;
		*this=plate;
	}

	CPlateStruc(STRUCT_TYPE istructype,int istory,DWORD color);

	~CPlateStruc(void){
		if(pLineIDM)
		{
			delete[] pLineIDM; 
			pLineIDM=NULL;
		}
	}

	//int id; //本构件的id，从1开始编号，各类面构件独立编号
	//边界线段数
	int nLine; 
	//边界线段数组
	int *pLineIDM;
	int iSectionID;  //截面ID

	float fThickness;  //板的总厚度，包括混凝土和钢材
	int iSubType;  //子类型 0-墙柱，1-墙梁
	int nRebarLayer; //钢筋网层数(每层网两个方向)，0表示无钢筋
	int iBottomStory;  //底部点楼层号，只对墙柱有效，暂时不用
	float fOffset; //偏心距，沿着3方向（法线方向）
	float fRatio[2];  //配筋率，板：面筋、底筋,单方向配筋率；墙：水平筋，竖筋,所有层单向配筋率之和，百分数
	float Angle[2];  //板内钢筋方向与整体XZ平面交线的夹角，单位：度，剪力墙：与整体XY平面夹角
	float fRebarArea;  //纵筋总面积(m^2), 只对墙梁有效

	SECTION_MAT_TYPE SecType; //截面类型,可选类型定义在 全局数组gPlateSectionTypeTable[] 中,CFeaInterface::GetPlateTypeSpecValue中根据材料类型对钢筋数和钢板数进行修正
	int nSteelLayer;   //钢板层数，0表示无钢板
	float fSteelThick;  //钢板总厚度

	//以下参数保存在附加属性字段
	float fAs; //边缘构件配筋量(单位：m2)计算值，只对墙有效

	//仅在PKPM接口函数OnImportpkpm中使用的临时变量，不保存文件，只对墙有效
	float fAs_top;
	float fLine_Dead_load;
	float fLine_Live_load;
	float fAs_bot;

	//临时数据，不保存文件,u.x>1不合法，初始化u.x=10.0f表示未计算，读入、增加、移动点和线时需要调用PlateLocalCoorVector重新计算
	Vector4 u,v,w,c0;  //工程局部坐标系基矢量及坐标原点，w为法线方向,

	//重载赋值运算符
	CPlateStruc & operator=(const CPlateStruc &plate);

	void Clear();

	//设置边数，并调整数组大小原数据被清除
	void SetLineNum(int nline) 
	{
		nLine=nline;
		if(pLineIDM) delete[] pLineIDM; 
		pLineIDM=new int[nLine];
		ASSERT(pLineIDM);
	}

	//返回顶点个数，及按顺序排列的顶点编码PointID，首尾点不重合，外部程序维护内存PointID，pLine为系统线段编码数组，
	//假设给定的结点坐标不重合，即没有坐标相同但编码不同的点
	int GetVexID(int *PointID,const CLine *pLine) const; 

	//返回点到线ID的关联表
	BOOL GetPt2Line(PT2LINE *pPt2Line,const CLine *pLine);


	//按几何关系计算局部坐标矢量：w为法线，顶点编号符合右手定则
	BOOL PlateLocalCoorVector(const CVertex *pVexArray,const CLine *pLineArray);

	//重新排列线段ID，从第j个线段开始，way>0，正方向排列，way<0，反方向排列
	void RenewLineID(int j,int way);

	//混凝土分层,nLayer--分层数，fThick--每层厚度，均匀分层，pos--每层位置数组，iMaxLayers--pos的最大个数
	//void GetConcLayer(int &nLayer,double &fThick,double *pos,int iMaxLayers);

	//配筋,返回分层数，pThick--每层厚度，iMaxLayers--最大层数
	int GetRebarLayer(double *pThick,int iMaxLayers);
	int GetRebarLayer(float *pThick,int iMaxLayers);
	// 邱海 2020年10月28日
	int GetRebarLayer(float *pThick);

	//得到坐标范围
	void GetRange(Vector4 &rMin,Vector4 &rMax);

	//计算墙的高度和宽度，内包矩形
	void GetWallSize(float &fWidth,float &fHeight);

	//计算墙的规定间距范围内配筋面积
	void GetWallRebarUnitArea(float &fHorzArea,float &fVertArea);

	//计算板或墙钢筋重量，单位：kN
	float GetRebarWeight();

	virtual BOOL Read(CASCFile &fin,STRUCT_TYPE iType,int &idf,CPlateSectionCollection &cPlateSection,CProjectPara &cPrjPara);   //自动释放原有pLineIDM内存，并创建新内存,iType支持墙梁
	virtual BOOL Write(CASCFile &fout,int idf);
	virtual BOOL Write2020(CASCFile &fout,int idf);

	//设计信息读写
	virtual BOOL ReadDesignInfo(CASCFile &fin,int idf);   //自动释放原有pLineIDM内存，并创建新内存,iType支持墙梁
	virtual BOOL WriteDesignInfo(CASCFile &fout,int idf);
	virtual BOOL WriteDesignInfo2020(CASCFile &fout,int idf);

	//根据截面信息刷新构件信息
	void RenewPlate();

	void GenLoadId(bool bRewrite=true);//由	float fDeadLoad 和float fLiveLoad生成Load加入mapload 供2020之后版本读取
	void GenLoadVal();//由mapload生成fDeadLoad和fLiveLoad 供2020之前版本读取

	//按边界顺序返回四个角点ID，左下、右下、右上、左上
	BOOL GetCornerPoint(int &left_bottom,int &right_bottom,int &right_top,int &left_top)const;

	//根据墙截面和划分参数划分成柱纤维
	void GetWall2BeamFibre(float fUnitWidth, int nDiv, BEAM_FIBRE_GEO* &pConcFibre, int &nConcFibre, BEAM_FIBRE_GEO* &pRebarFibre, 
		int &nRebarFibre, BEAM_FIBRE_GEO* &pSteelFibre, int &nSteelFibre);

	//板蒙皮判断
	BOOL IsShin() const;
};
