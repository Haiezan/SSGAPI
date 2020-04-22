#pragma once
#include "HeadDefine.h"
#include "Vector4.h"
#include "Matrix4x4.h"
//#include "SysPara.h"
#include "PublicFunc.h"
#include "PublicFunc_MFC.h"


#include "ASCFile.h"
#include "UserDefine.h"
#include "BeamSection.h"
#include "Material.h"
#include "EdgeStruct.h"


#include <afxtempl.h>
#include <vector>
//#include <algorithm>
//#include <functional>

using namespace std;




class CLine;
class CFrame;
class CMesh;

//线与多边形相交结果
struct LINE_CROSS_POLY
{
	//type--相交类型：
	//-1 -- 其它错误
	//0--不相交，包括共面和不共面
	//1--线交于多边形1个顶点，包括共面和不共面
	//共面相交：2--线与多边形相交于2个点，3--线与多边形边线(部分)重合；6--线在多边形内
	//不共面相交：4--线与多边形边界线相交(由于在建立板构件之前就建立了结构线，并处理了线段之间的相交情况，因此该线段一般不可能交于边界线的中间点)，
	//			  5--线与多边形内部相交
	int type; 
	int pointid1;  //交点ID1，type=1,2有效
	int pointid2;  //交点ID2，type=2有效
	int plateid1,plateid2; //新的多边形ID
};

struct CROSS_POINT
{
	int id;
	float t;
	int iLine;
	CROSS_POINT *pPair;

	bool operator < (const CROSS_POINT& cp ) const //升序排序时必须写的函数
	{
		return t < cp.t;
	}
};

struct CROSS_PLATE
{
	int plateid;  //面构件ID
	int crossvexid;  //交叉点

	bool operator == (const CROSS_PLATE& cp)
	{
		return (plateid==cp.plateid) && (crossvexid==cp.crossvexid);
	};

	bool operator < (const CROSS_PLATE& cp) //升序排序时必须写的函数
	{
		if(plateid < cp.plateid) 
			return TRUE;
		else if(plateid == cp.plateid) 
			return crossvexid < cp.crossvexid;
		else
			return FALSE;
	};
};


//楼层范围结构
struct STORY_RANGE
{
	int iStoryMin;
	int iStoryMax; 
};

//层间过渡的竖向构件梁单元
struct BEAM_CONN_LAYER
{
	int idBeam;  //单元编号
	int idNode;  //局部结点序号，0-1
};

//层间过渡的壳单元
struct SHELL_CONN_LAYER
{
	int idShell;  //壳单元编号
	int idNode1;  //与楼层相连的局部编号,三角形0~2，四边形0~3
	int idNode2;  //与楼层相连的局部编号,三角形1~2，四边形1~3，-1表示不相连
};

//统计各类型数量
struct STRUCT_COUNT
{
	int nPoint   	;       //点
	int nLine    	;       //结构线
	int nBeam    	;       //梁
	int nPillar  	;       //柱
	int nBracing 	;       //斜撑
	int nEdge		;       //约束边缘构件
	int nHidebeam   ;       //虚梁
	int nLongirebar ;       //连梁纵筋
	int nLink ;       //阻尼器	//乔保娟 2015.5.21
	int nPlate 		;       //板
	int nWall  		;       //墙
	int nGuides    	;       //辅助线
};

//边界点和边界线关联关系
struct BND_NODE_LINE
{
	int nline;
	int line[2];  //线编号，最多2个
};

//结构名称及关键字
struct STRUCT_KEYWORD
{
	int iType;
	CString sTitle;
	CString sKeyword;

};

//得到g_StructKeyword中的的结构类型索引号
//int GetStructKeywordIndex(STRUCT_TYPE itype);
int _SSG_DLLIMPEXP GetStructKeywordIndex(STRUCT_TYPE itype);
extern "C" _SSG_DLLIMPEXP int GetStructKeywordIndex(const CString  &keyword);


//点到线构件(包括结构线、梁、柱等)的连接关系，二叉树
struct _SSG_DLLIMPEXP PT2LINESTRUCT
{
	PT2LINESTRUCT(void) {conn_vex1=conn_vex2=conn_beam1=conn_beam2=-1;}

	int conn_beam1,conn_vex1; //相连的第一个线构件的id和点号，以及线构件楼层号
	int conn_beam2,conn_vex2; //相连的第二个线构件的id和点号，以及线构件楼层号

	void Append(int beam, int vex)
	{
		if(conn_beam1==-1)
		{
			conn_beam1=beam;
			conn_vex1=vex;
		}
		else
		{
			conn_beam2=beam;
			conn_vex2=vex;
		}
	}
};

//一个点到两条线段的关联，-1为无效ID，用于多边形边界
struct _SSG_DLLIMPEXP PT2LINE
{
	PT2LINE(void) {iVexID=-1;iLeftLineID=iRightLineID=-1;}
	int iVexID; //点ID
	int iLeftLineID,iRightLineID;  //左边的线段ID，右边的线段ID
};

//组合构件
struct _SSG_DLLIMPEXP COMBO_STRUCT
{
	COMBO_STRUCT(void) {sName=L"";}
	~COMBO_STRUCT() {Clear();}
	void Clear(void) {vIDG.clear();sName=L"";}
	CString sName;
	vector<int> vIDG;
};

struct _SSG_DLLIMPEXP STRUCT_PROPERTY1
{
	int iCode;  //属性代码=数组元素序号，不可随意更改
	CString sName;  //属性名称
	CString sUnit;  //属性单位
	BOOL bBeam,bPillar,bBrace,bPlate,bWall,bBeamWall;  //是否允许某类构件使用
	int iDataType; //0-float,1-CString
};

//点和墙的索引关系，用于处理连梁
class _SSG_DLLIMPEXP CPointWallIndex
{
public:
	CPointWallIndex(void) {nWalls=0;}

	int nWalls;  //周围的墙数，不包括墙梁(即悬空墙)
	//int idPoint[Sys_Max_Connect_Wall];  //墙体中除该点外最近端点的IDM，-1表示无效
	int idWall[Sys_Max_Connect_Wall];  //墙体IDM
	float fAng[Sys_Max_Connect_Wall];    //此点与idPoint构成的射线与X轴夹角，弧度，0-2*PI

	BOOL Add(int id_wall,float Angle)
	{
		if(nWalls>=Sys_Max_Connect_Wall) 
		{
			TRACE("too namy walls:  id_wall=%d\r\n",id_wall);
			return FALSE;
		}
		idWall[nWalls]=id_wall;
		fAng[nWalls]=Angle;
		nWalls++;
		return TRUE;
	}
};

//类定义------------------------------------------------------------------------
//图元属性
class _SSG_DLLIMPEXP CPrimitiveProp
{
public:
	CPrimitiveProp(void);

	int idmStory;     //楼层IDF=IDM,从0开始编号,0为地面
	int iStage;        //施工阶段,从0开始编号
	int iTower;		//分块号，塔号，从0开始编号

	//临时数据,不保存文件
	union
	{
		DWORD dwColor;  //颜色
		unsigned char RGBA[4];
	};

	//cmliu 2016/3/22  增加一个 临时保存颜色用于恢复
	DWORD dwColor1;		

	unsigned char iStatus;  //状态标志，0无效，1-正常，2-选中，3-参考点(目前只对点有效)
	CString sComments;  //用于显示的说明文字,由程序随时更新
	CString sComments2;  //用于显示的说明文字,由程序随时更新//显示第二个节点力 

	float fMeshRatio; //网格加密系数，>1加密，保存在单独数据段

	CPrimitiveProp & operator=(const CPrimitiveProp &prop)
	{
		if(this==&prop) return *this;

		idmStory=prop.idmStory; 
		iStage=prop.iStage;
		iTower=prop.iTower;
		dwColor=prop.dwColor;
		iStatus=prop.iStatus;  
		//iStatus=1; //被复制的图元自动变成有效2012-10-25
		sComments=prop.sComments;
		sComments2=prop.sComments2;
		fMeshRatio=prop.fMeshRatio;

		return *this;
	}

	void Clear();

	virtual BOOL Read(CASCFile &fin);   
	virtual BOOL Write(CASCFile &fout);

	virtual void ReadBin(CFile &fin);   
	virtual BOOL WriteBin(CFile &fout);

	virtual BOOL IsValid(void) const;
};

enum LOAD_TYPE
{
	LOAD_DEAD=0,		//0-梁上分布附加恒载；
	LOAD_LIVE=1,		//1-梁上分布附加活载；
	LOAD_SLAB_DEAD=2,	//2-板附加恒载传导于梁上分布荷载；
	LOAD_SLAB_LIVE=3,	//3-板附加活载传导于梁上分布荷载；
	LOAD_SLAB_WEIGHT=4,	//4-板自重传导于梁上分布荷载
};

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
	};
	int PmID;
	STRUCT_TYPE iStrucType;

	CString ConcMat;         //砼材料
	CString RebarMat;        //钢筋材料,边缘构件或连梁纵筋材料放在RebarMat里，质量也放在钢筋变量里
	CString StirrupMat;        //箍筋材料	//乔保娟 2015.6.5
	CString SteelMat;  //型钢材料

	float fDeadLoad; //恒荷载，单位面积或单位长度,板KN/m2，梁KN/m,向下为正，斜板按实际面积计算，斜梁按实际长度计算
	float fLiveLoad; //活荷载，单位面积或单位长度,板KN/m2，梁KN/m,向下为正，斜板按实际面积计算，斜梁按实际长度计算

	int iMidSeismContstiType;//中震性能目标
	int iRareSeismContstiType;//大震性能目标
	//int iKill;//单元生死
	int iSeismicGrade;//抗震等级
	int iDatailsGrade;//抗震构造等级
	CString sMemberName;//构件名称

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

		iSeismicGrade=prop.iSeismicGrade;
		iDatailsGrade=prop.iDatailsGrade;
		sMemberName=prop.sMemberName;

		//由于框架复制时不存在单元数据，因此不需要复制
		aElms.RemoveAll();

		return *this;
	}

	//virtual BOOL Read(CASCFile &fin);   
	//virtual BOOL Write(CASCFile &fout);

	//virtual void ReadBin(CFile &fin);   
	//virtual BOOL WriteBin(CFile &fout);
};

//结点类
class _SSG_DLLIMPEXP CVertex : public CPrimitiveProp
{
public:
	CVertex(void){Clear();}

	//仅用作点计算
	CVertex(float x1,float y1,float z1)
	{
		Clear();
		x=x1;y=y1;z=z1;
	} 

	//仅用作点计算
	CVertex(const Vector4 &v)
	{
		Clear();
		x=v.x;y=v.y;z=v.z;
	} 

	CVertex(float x1,float y1,float z1,int istory,BOOL bCrossStory)
	{
		Clear();
		x=x1;y=y1;z=z1;
		idmStory=istory;
		SetCrossStory(bCrossStory);
		memset(fDeadLoad,0,sizeof(fDeadLoad));
		memset(fLiveLoad,0,sizeof(fLiveLoad));
		idRigidBody=-1;
		idmBoundary=-1;
	} //构造点图元

	//复制构造函数,该构造函数造成CVector使用不正常
	CVertex(const CVertex &v) 
	{
		*this=v;
	}

	union
	{
		struct
		{
			float x,y,z;  //坐标
		};
		float coor[3];
	};

	float fDeadLoad[6]; //恒荷载集中力,fx,fy,fz,mx,my,mz,KN,KN.M,按整体坐标方向定义
	float fLiveLoad[6]; //活荷载集中力
	int	  idRigidBody;	//刚性隔板编号,-1时无效

	int idmBoundary;	//边界条件ID。框架数据在*BOUNDARY中读写，不参与类读写；网格数据在类中读取ReadBin/WriteBin，并借此生成mesh.m_pBoundary
	int iGeoType;		//类型,按位定义，0x01--跨层。框架数据在*POINTPROP段中读取，不参与类读写；网格数据在类中读取ReadBin/WriteBin

	CVertex & operator=(const Vector4 &v)
	{
		x=v.x;y=v.y;z=v.z;
		return *this;
	}


	BOOL IsCrossStory(void) const {return iGeoType & 0x01;}
	void SetCrossStory(BOOL bCrossStory=TRUE) {if(bCrossStory) iGeoType |= 0x01;else iGeoType &= ~0x01;}

	BOOL IsCrossTower(void) const {return iGeoType & 0x02;}
	void SetCrossTower(BOOL bCrossTower=TRUE) {if(bCrossTower) iGeoType |= 0x02;else iGeoType &= ~0x02;}

	//按照线段设置属性
	void CopyProp(const CLine &line);

	//近似相等，允许微小误差
	BOOL operator==(const CVertex &v) const
	{
		return fabs(x-v.x)<g_cSysSizePara.Sys_PointError && fabs(y-v.y)<g_cSysSizePara.Sys_PointError && fabs(z-v.z)<g_cSysSizePara.Sys_PointError;
	}

	//不相等，允许微小误差
	BOOL operator!=(const CVertex &v) const
	{
		return fabs(x-v.x)>=g_cSysSizePara.Sys_PointError || fabs(y-v.y)>=g_cSysSizePara.Sys_PointError || fabs(z-v.z)>=g_cSysSizePara.Sys_PointError;
	}

	//精确相等
	BOOL Equal(const CVertex &v) const {return x==v.x && y==v.y && z==v.z;}  

	//+=
	void operator+=(const CVertex &v)
	{
		x+=v.x;
		y+=v.y;
		z+=v.z;
	}

	//-=
	void operator-=(const CVertex &v)
	{
		x-=v.x;
		y-=v.y;
		z-=v.z;
	}

	//  *=
	void operator*=(float f)
	{
		x*=f;
		y*=f;
		z*=f;
	}

	//  /=
	void operator/=(float f)
	{
		x/=f;
		y/=f;
		z/=f;
	}

	void Normalize(void)
	{
		float len = Length();
		if(len==0) return;
		x/=len;
		y/=len;
		z/=len;
	}

	//计算矢径长度
	float Length()
	{
		return sqrtf(x*x+y*y+z*z);
	}

	void Clear(void)
	{
		CPrimitiveProp::Clear();
		x=y=z=0.0f;
		for(int i=0;i<6;i++)
		{
			fDeadLoad[i]=fLiveLoad[i]=0;
		}
		idRigidBody=-1;
		idmBoundary=-1;
		iGeoType=0;
	}

	//重新创建内存，复制原来数据，释放原来的内存。若新旧指针不是同一个变量时，调用程序应设置旧指针为NULL
	static CVertex *Renew(CVertex  *&oldp,int oldCount,int newCount)
	{
		if(oldCount==newCount) return oldp;

		CVertex *newp=new CVertex[newCount];
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

	

	virtual BOOL Read(CASCFile &fin);
	virtual BOOL Write(CASCFile &fout,int idf); 
	virtual void ReadBin(CFile &fin);   
	virtual BOOL WriteBin(CFile &fout);
	virtual BOOL IsVisible(const CVertex &vMin,const CVertex &vMax) const;
};

//相加,其它属性与v1相同
inline CVertex operator+(const CVertex &v1,const CVertex &v2) 
{
	CVertex v0=v1;
	v0.x+=v2.x;
	v0.y+=v2.y;
	v0.z+=v2.z;
	return v0;
}

//相减,其它属性与v1相同
inline CVertex operator-(const CVertex &v1,const CVertex &v2) 
{
	CVertex v0=v1;
	v0.x-=v2.x;
	v0.y-=v2.y;
	v0.z-=v2.z;
	return v0;
}

//相减,其它属性与v1相同
inline CVertex operator-(const CVertex &v1) 
{
	CVertex v0=v1;
	v0.x=-v1.x;
	v0.y=-v1.y;
	v0.z=-v1.z;
	return v0;
}

//相乘,其它属性与v1相同
inline CVertex operator*(const CVertex &v1,float f)
{
	CVertex v0=v1;
	v0.x*=f;
	v0.y*=f;
	v0.z*=f;
	return v0;
}

//float * v,其它属性与v相同
inline CVertex operator*(float f,CVertex &v)
{
	CVertex v1=v;
	v1.x=f*v.x;
	v1.y=f*v.y;
	v1.z=f*v.z;
	return v1;
}

//除法/,其它属性与v1相同
inline CVertex operator/(const CVertex &v1,float f)
{
	CVertex v0=v1;
	v0.x/=f;
	v0.y/=f;
	v0.z/=f;
	return v0;
}

//叉积，,其它属性与a相同
inline CVertex CrossProduct(const CVertex &a,const CVertex &b)
{
	CVertex c=a;
	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return c;
}

//中间结果双精度叉积
inline CVertex CrossProductDouble(const CVertex &a,const CVertex &b)
{
	CVertex c=a;
	c.x = (float)((double)a.y * b.z - (double)a.z * b.y);
	c.y = (float)((double)a.z * b.x - (double)a.x * b.z);
	c.z = (float)((double)a.x * b.y - (double)a.y * b.x);
	return c;
}

//点积
inline float DotProduct(const CVertex &a,const CVertex &b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

//点积
inline float DotProduct(const CPoint &a,const CPoint &b)
{
	return (float)a.x * b.x + (float)a.y * b.y;
}

//双精度点积
inline double DotProductDouble(const CVertex &a,const CVertex &b)
{
	return (double)a.x * b.x + (double)a.y * b.y + (double)a.z * b.z;
}



//边界条件值：定义在一个点上
class _SSG_DLLIMPEXP CBoundary  
{
public:
	CBoundary(void)
	{
		Clear();
	}

	unsigned short Type;  //自由度类型,从低到高按位存储,每个自由度2bit,分别对应0-5自由度，0--非位移约束，1--位移约束，2--给定弹簧刚度
	float Value[Sys_DOF];  //6个自由度的值，位移值dx,dy,dz,ax,ay,az

	//所有自由度初始化为0
	void Clear(void)
	{
		Type=0;
		for(int i=0;i<Sys_DOF;i++) 
		{
			Value[i]=0;
		}
	}

	void SetFix(void)  //约束全部自由度
	{
		Type=0x555;
		for(int i=0;i<Sys_DOF;i++) 
			Value[i]=0;
	}

	void SetDisp(int idof,float fDisp) //设置位移约束
	{
		ASSERT(idof<Sys_DOF && idof>=0); 
		Type|=(1<<(idof<<1)); Value[idof]=fDisp;
	}

	void SetStiff(int idof,float fStiff) //设置弹簧约束
	{
		ASSERT(idof<Sys_DOF && idof>=0); 
		Type|=(2<<(idof<<1)); Value[idof]=fStiff;
	}

	BOOL IsConstraint(int idof) const //1--位移约束，0-非位移约束
	{
		ASSERT(idof<Sys_DOF && idof>=0); 
		return (Type&(1<<(idof<<1)))>0?1:0;
	}

	int GetType(int idof) const
	{
		ASSERT(idof<Sys_DOF && idof>=0); 
		return (Type>>(idof<<1))&0x03;

	}

	//将12位边界条件信息缩并为6位
	unsigned int Get6BitBnd(void)
	{
		unsigned int bnd=0;
		bnd|=(Type&0x01);
		bnd|=(Type&0x04)>>1;
		bnd|=(Type&0x10)>>2;
		bnd|=(Type&0x40)>>3;
		bnd|=(Type&0x100)>>4;
		bnd|=(Type&0x400)>>5;
		return bnd;
	}

	BOOL operator==(const CBoundary &bnd) const
	{
		if(Type!=bnd.Type) return FALSE;
		for (int i=0;i<Sys_DOF;i++)
		{
			if(Value[i]!=bnd.Value[i]) return FALSE;
		}
		return TRUE;
	}

	virtual void Read(CASCFile &fin);
	BOOL Write(CASCFile &fout);
	virtual BOOL Write(CASCFile &fout,int idf);  //两者格式不同

	virtual void ReadBin(CFile &fin);
	virtual BOOL WriteBin(CFile &fout);
};

//构件边界条件：可施加到构件点（对应线构件）和线段（对应面构件）上
//尽管施加到线和面上，实际要映射到该区域内的网格点上而不是单元
class _SSG_DLLIMPEXP CBoundaryCollection
{
public:
	CBoundaryCollection(void){;}
	~CBoundaryCollection() {Clear();}

	CArray<CBoundary,CBoundary&> aBoundary;

	void Clear(void) {aBoundary.RemoveAll();}

	CBoundaryCollection& operator=(const CBoundaryCollection& bnd)
	{
		if(this==&bnd) return *this;
		aBoundary.Copy(bnd.aBoundary);
		return *this;
	}

	//返回序号
	int Append(CBoundary &bnd)
	{
		for (int i=0;i<aBoundary.GetCount();i++)
		{
			if(aBoundary[i]==bnd) return i;
		}
		return (int)aBoundary.Add(bnd);
	}
};

//线段类
class _SSG_DLLIMPEXP CLine:public CPrimitiveProp
{
public:
	CLine(void);
	CLine(int i1,int i2,int istory);

	int VexIDM1,VexIDM2;  //端点IDM
	float fDeadLoad,fLiveLoad; //线载荷,本类中不读取，在应用时读写赋值，KN/m
	int idmBoundary;  //边界条件ID，不参与类读写，单独处理

	//判断编码相同
	BOOL operator==(const CLine &line) const
	{
		if(line.VexIDM1==VexIDM1 && line.VexIDM2==VexIDM2) return TRUE;
		if(line.VexIDM1==VexIDM2 && line.VexIDM2==VexIDM1) return TRUE;
		return FALSE;
	}

	BOOL IsCrossStory(void) const;
	//void SetCrossStory(BOOL bCrossStory=TRUE);  //实际上是设置线的端点，线数据被有跨层属性，应避免使用点属性带入

	BOOL IsCrossTower(void) const;
	//void SetCrossTower(BOOL bCrossTower=TRUE);  //实际上是设置线的端点，线数据被有跨塔属性，应避免使用点属性带入

	inline float Length(const CVertex *vex) const //vex为顶点坐标数组
	{
		return (vex[VexIDM1]-vex[VexIDM2]).Length();
	}
	inline float Angle(const CVertex *vex) const //vex为顶点坐标数组
	{
		float length= (vex[VexIDM1]-vex[VexIDM2]).Length();
		float high=abs(vex[VexIDM1].z-vex[VexIDM2].z);
		return acos(high/length);
	}
	inline BOOL InRectXY(const CVertex &vMin,const CVertex &vMax,const CVertex *vex)  //正选，线段是否完全在矩形范围内，包括边界重合
	{
		const CVertex &vex1=vex[VexIDM1];
		const CVertex &vex2=vex[VexIDM2];
		if((vex1.x-vMin.x)*(vex1.x-vMax.x)>0) return FALSE;
		if((vex1.y-vMin.y)*(vex1.y-vMax.y)>0) return FALSE;
		if((vex2.x-vMin.x)*(vex2.x-vMax.x)>0) return FALSE;
		if((vex2.y-vMin.y)*(vex2.y-vMax.y)>0) return FALSE;
		return TRUE;
	}

	inline BOOL CrossRectXY(const CVertex &vMin,const CVertex &vMax,const CVertex *vex)  //反选，线段是否与矩形重叠，包括边界重合
	{
		const CVertex &vex1=vex[VexIDM1];
		const CVertex &vex2=vex[VexIDM2];
		if((vex1.x-vMin.x)*(vex1.x-vMax.x)<0 && (vex1.y-vMin.y)*(vex1.y-vMax.y)<0) return TRUE;
		if((vex2.x-vMin.x)*(vex2.x-vMax.x)<0 && (vex2.y-vMin.y)*(vex2.y-vMax.y)<0) return TRUE;
		return FALSE;
	}

	void Clear(void);
	virtual BOOL Read(CASCFile &fin);
	virtual BOOL Write(CASCFile &fout,int idf);
};

//构件的构造面，用于显示绘制
class _SSG_DLLIMPEXP CSurface
{
public:
	CSurface(void) {nVertex=0;pVertex=NULL;color=0;}
	~CSurface() {delete[] pVertex;}

	CSurface(CSurface &surf)
	{
		pVertex=NULL;
		*this=surf;
	}

	//赋值运算符重载
	CSurface & operator=(const CSurface& surf)
	{
		if(this==&surf) return *this;

		delete[] pVertex;
		nVertex=surf.nVertex;
		pVertex=new Vector4[nVertex];
		for(int i=0;i<nVertex;i++)
		{
			pVertex[i]=surf.pVertex[i];
		}
		return *this;
	}

	int nVertex; //顶点数
	Vector4 *pVertex; //顶点坐标数组，相对于构件的局部坐标
	DWORD color; //实际绘制颜色
};

class _SSG_DLLIMPEXP CBeamFace
{
public:
	CBeamFace(void);
	~CBeamFace();

	Vector4 a1,b1,c1,d1; //第一个面的顶点
	Vector4 a2,b2,c2,d2; //第二个面的顶点
	float fColor1,fColor2,fColor3; //a1-a2光照系数，a1-b1光照系数，a1-d1光照系数
};

//线状构件，由一个线段组成
class _SSG_DLLIMPEXP CBeamStruc : public CStrucProp
{
public:
	CBeamStruc(void);
	//复制构造函数
	CBeamStruc(const CBeamStruc &beam) 
	{
		Clear();
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

	//临时数据，不保存文件,u.x>1不合法，初始化u.x=10.0f表示未计算，读入、增加、移动端点和修改转角时需要调用LocalCoorVector重新计算
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

	float GetWidth(const CSectionCollection *pSecCollection) const; //截面宽度
	float GetHeight(const CSectionCollection *pSecCollection) const; //高度范围

	//得到坐标范围
	void GetRange(Vector4 &rMin,Vector4 &rMax);

	void Clear(void);

	//赋值运算符重载
	CBeamStruc & operator=(const CBeamStruc& beam)
	{
		if(this==&beam) return *this;

		Clear();
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
	void LocalCoorVector(Vector4 &u,Vector4 &v,Vector4 &w);

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
	virtual BOOL Read(CASCFile &fin,STRUCT_TYPE iType);
	virtual BOOL Write(CASCFile &fout,int idf);
	//设计信息读写
	virtual BOOL ReadDesignInfo(CASCFile &fin,STRUCT_TYPE iType,int idf);
	virtual BOOL WriteDesignInfo(CASCFile &fout,int idf);
};


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

	~CPlateStruc(void){Clear();}

	//int id; //本构件的id，从1开始编号，各类面构件独立编号
	//边界线段数
	int nLine; 
	//边界线段数组
	int *pLineIDM;

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

	//临时数据，不保存文件,u.x>1不合法，初始化u.x=10.0f表示未计算，读入、增加、移动点和线时需要调用LocalCoorVector重新计算
	Vector4 u,v,w,c0;  //局部坐标系基矢量及坐标原点，w为法线方向,
	//对于墙，u在墙面内，与Z垂直，并与X夹角呈锐角；v与Z重合；w为法线。特例：当墙与X轴垂直时，u=Y。
	//对于板，u=X，v=Y，w=Z，w为法线。
	//其它面构件，u为过c0点的XZ面与构件平面的交线，并与X轴呈锐角；w为法线。暂时不用。

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

	//按建筑行业习惯计算局部坐标系基矢量及原点,pVexArray,pLineArray为全局的点和线数组
	BOOL LocalCoorVector_Standard(const CVertex *pVexArray,const CLine *pLineArray,Vector4 &c0,Vector4 &u,Vector4 &v,Vector4 &w);

	//按几何关系计算局部坐标矢量：w为法线，顶点编号符合右手定则，u、v与整体坐标系没有关系
	BOOL LocalCoorVector(const CVertex *pVexArray,const CLine *pLineArray,Vector4 &c0,Vector4 &u,Vector4 &v,Vector4 &w);

	//重新排列线段ID，从第j个线段开始，way>0，正方向排列，way<0，反方向排列
	void RenewLineID(int j,int way);

	//混凝土分层,nLayer--分层数，fThick--每层厚度，均匀分层，pos--每层位置数组，iMaxLayers--pos的最大个数
	//void GetConcLayer(int &nLayer,double &fThick,double *pos,int iMaxLayers);

	//配筋,返回分层数，pThick--每层厚度，iMaxLayers--最大层数
	int GetRebarLayer(double *pThick,int iMaxLayers);
	int GetRebarLayer(float *pThick,int iMaxLayers);

	//得到坐标范围
	void GetRange(Vector4 &rMin,Vector4 &rMax);

	//计算墙的高度和宽度，内包矩形
	void GetWallSize(float &fWidth,float &fHeight);

	//计算墙的规定间距范围内配筋面积
	void GetWallRebarUnitArea(float &fHorzArea,float &fVertArea);

	//计算板或墙钢筋重量，单位：kN
	float GetRebarWeight();

	virtual BOOL Read(CASCFile &fin,STRUCT_TYPE iType,int &idf);   //自动释放原有pLineIDM内存，并创建新内存,iType支持墙梁
	virtual BOOL Write(CASCFile &fout,int idf,int secid,STRUCT_TYPE iType);
	
	//设计信息读写
	virtual BOOL ReadDesignInfo(CASCFile &fin,int idf);   //自动释放原有pLineIDM内存，并创建新内存,iType支持墙梁
	virtual BOOL WriteDesignInfo(CASCFile &fout,int idf);
};

#define NUM_STORY_PROP 13  //楼层属性参数个数

//楼层类
class _SSG_DLLIMPEXP CStory
{
public:
	CStory(void)
	{
		Init();
	}

	~CStory(void){;}

	CStory(CStory &story)
	{
		*this=story;
	}

	float fHeight; //层高
	float zTop;  //屋顶标高
	int iStoryType;  //1-普通楼层；2-空间楼层

	float fStifCenterX;
	float fStifCenterY;
	float fMassCenterX;
	float fMassCenterY;
	//边缘构件类型
	//bit0-2: 按值定义，不按位，0--约束边缘构件，1-底部加强之内的构造边缘构件，2-底部加强之上的构造边缘构件
	//bit8-15:  按值定义，不按位，抗震构造等级,0-- 特一级，1 -- 一级(9度)，2 -- 一级(8度)，3 -- 二级， 4 -- 三级，5 -- 四级
	////bit3-5: 按值定义，不按位，抗震等级 0-特一级，1-一级，2 -- 二级， 3-- 三级,4- 四级，5-不抗震
	int iStoryProp;

	//楼层构件参数,作为附属数据读写,共9种构件
	float fPara[16][Sys_StructTypeNum];  //16个分量与STRUCT_PROPERTY1顺序保持一致(从3开始),0-12有用，数据单位与界面一致
	CString sRebar[Sys_StructTypeNum],/*sStirrup[Sys_StructTypeNum],*/sConc[Sys_StructTypeNum],sSteel[Sys_StructTypeNum]; //分量与g_StructKeyword一致
	float zBottom(void) const {return zTop-fHeight;} //层底标高

	int GetEarthQuakeClass(void)
	{
		int k=(iStoryProp>>8)&0xff;
		//if(k==0xff) k=-1;
		if(k>=Sys_EQ_Class_Num) k=Sys_EQ_Class_Num-1;
		if(k<0) k=0;
		return k;
	};
	void SetEarthQuakeClass(int k)
	{
		if(k>=Sys_EQ_Class_Num) k=Sys_EQ_Class_Num-1;
		if(k<0) k=0;
		//if(k==-1) k=0xff;
		k=k<<8;
		iStoryProp &= 0xffff00ff;
		iStoryProp |= k;
	};

	//邱海注释楼层抗震等级 2017年10月9日
	//int GetEarthQuakeGrade(void)
	//{
	//	int k=(iStoryProp>>3)&0x1f;
	//	if(k>=Sys_EQ_Class_Num) k=Sys_EQ_Class_Num-1;
	//	if(k<0) k=0;
	//	return k;
	//};
	//void SetEarthQuakeGrade(int k)
	//{
	//	if(k>=Sys_EQ_Class_Num) k=Sys_EQ_Class_Num-1;
	//	if(k<0) k=0;
	//	k=k<<3;
	//	iStoryProp &= 0xffffffe3;
	//	iStoryProp |= k;
	//};

	int GetEdgeType(void)
	{
		int k=iStoryProp&0x07;
		if(k<0) k=0;
		if(k>2) k=2;
		return k;
	}

	void SetEdgeType(int k)
	{
		iStoryProp &= 0xfffffff8;
		iStoryProp |= k;
		if(k<0) k=0;
		if(k>2) k=2;
	}

	void Init(void); //设置默认值

	void SetName(CString sname)
	{
		sname.Trim(); 
		if(sname==L"") 
		{
			AfxMessageBox(L"Story name is empty.");
			return;
		}
		sName=sname;
	}
	CString GetName(void) const {return sName;}
	void SetGroup(CString sgroup)
	{
		sgroup.Trim();
		if(sgroup==L"") 
		{
			AfxMessageBox(L"Group name is empty.");
			return;
		}
		sGroup=sgroup;
	}
	CString GetGroup(void) const {return sGroup;}

	CStory & operator=(const CStory &story)
	{
		if(this==&story) return *this;
		sName=story.sName;
		sGroup=story.sGroup;
		fHeight=story.fHeight;
		iStoryType=story.iStoryType;
		zTop=story.zTop;
		iStoryProp=story.iStoryProp;
		fStifCenterX		=story.fStifCenterX		;
		fStifCenterY		=story.fStifCenterY		;
		fMassCenterX	=story.fMassCenterX	;
		fMassCenterY	=story.fMassCenterY	;
		for(int j=0;j<Sys_StructTypeNum;j++) 
		{
			for(int i=0;i<16;i++) 
			{
				fPara[i][j]=story.fPara[i][j];
			}
			sRebar[j]=story.sRebar[j];
			//	sStirrup[j]=story.sStirrup[j];
			sConc[j] =story.sConc[j] ;
			sSteel[j]=story.sSteel[j];
		}
		return *this;
	}

	virtual void Read(CASCFile &fin);   
	virtual void Write(CASCFile &fout,int idf);
	//设计信息读写
	virtual void ReadDesignInfo(CASCFile &fin);   
	virtual void WriteDesignInfo(CASCFile &fout,int idf);

protected:
	//楼层控制参数
	CString sName;  //楼层标记
	CString sGroup; //分组名称


};



//梁单元，用于网格
class _SSG_DLLIMPEXP CBeamElm : public CPrimitiveProp
{
public:
	CBeamElm(){	Clear();}

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
	DWORD dwFlag;	//按位控制，第0位：0--主梁，使用截面中的纤维，1--次梁(或剪力墙约束边缘构造柱)，不使用纤维信息。//第1位:1-延伸到墙里面的单元
	BOOL bArtiNode1,bArtiNode2;  //false--固接，true--铰接,与VexIDM1,VexIDM2对应

	//CFeaInterface生成接口数据时才产生，保存二进制文件
	int iBlock;  //分块ID,注意不是序号，不连续

	DWORD dwHingeColor;  //塑性铰颜色  深蓝色不画
	BOOL bHaveHinge;

	//是否次梁单元
	BOOL IsSecendBeam(void) { return dwFlag&0x01; };

	//是否延伸的梁单元
	BOOL IsExtendElm(void) { return dwFlag&0x02; };

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


	float Length(const CVertex *pVex);  //计算单元长度,pVex为结点坐标数组

	//得到坐标范围
	void GetRange(Vector4 &rMin,Vector4 &rMax);

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
		bArtiNode1=bArtiNode2=FALSE;
		VexIDM1=VexIDM2=-1;
		bHaveHinge=FALSE;
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
	//水平构件：e1为轴线方向，e2、e3为截面局部坐标方向
	//竖向构件：e1=eZ为轴线方向，e2、e3为截面局部坐标方向
	void LocalCoorVector(Vector4 &u,Vector4 &v,Vector4 &w) const;


	virtual BOOL Read(CASCFile &fin);
	virtual BOOL Write(CASCFile &fout,int idf,int idf_Struct,STRUCT_TYPE itype);

	virtual inline void ReadBin(CFile &fin);
	virtual inline BOOL WriteBin(CFile &fout);

};

//三角形面单元，用于网格
class _SSG_DLLIMPEXP CTriangleElm : public CPrimitiveProp
{
public:
	CTriangleElm(void) {Clear();}

	//enum {nVex=3}; //边界点数，不重合
	int pVexIDM[3];  //端点ID数组
	int PlateStrucIDM; //关联的构件ID，用于获得配筋信息
	//STRUCT_TYPE iStrucType;

	//CFeaInterface生成接口数据时才产生，保存二进制文件
	int iBlock;  //分块ID

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

	void Clear(void) {PlateStrucIDM=-1;iBlock=0;}

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

	//计算局部坐标系基矢量(u,v,w)及原点c0，与构件规定相同
	//与构件的LocalCoorVector_Standard一致
	BOOL LocalCoorVector_Standard(Vector4 &c00,Vector4 &u,Vector4 &v,Vector4 &w) const;
	//w为法线，顶点编号符合右手定则，u、v与整体坐标系没有关系
	BOOL LocalCoorVector(const CVertex *pVexArray,Vector4 &c00,Vector4 &u,Vector4 &v,Vector4 &w) const;

	//计算中心点坐标，pVex为全局结点数组,由于坐标会变形，因此这里要用传进来的坐标数组参数进行计算
	CVertex GetCenter(const CVertex *pVex) const;

	//得到坐标范围
	void GetRange(Vector4 &rMin,Vector4 &rMax);

	virtual BOOL Read(CASCFile &fin); //派生类的虚函数关键字virtual可写可不写，但总是虚函数
	virtual BOOL Write(CASCFile &fout,int idf,int idf_Struct,STRUCT_TYPE itype);

	virtual inline void ReadBin(CFile &fin);
	virtual inline BOOL WriteBin(CFile &fout);
};


//四结点四边形面单元，用于网格
class _SSG_DLLIMPEXP CQuadElm : public CPrimitiveProp
{
public:
	CQuadElm(void) {Clear();}

	enum {VEXNUM=4}; //边界点数，不重合
	int pVexIDM[VEXNUM];  //端点ID数组
	int PlateStrucIDM; //关联的构件ID，用于获得配筋信息
	//STRUCT_TYPE iStrucType;

	//CFeaInterface生成接口数据时才产生，保存二进制文件
	int iBlock;  //接口中单元分类ID

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

	float Area(const CVertex *pNode) const;  //计算四边形面积>0,pNode为结点坐标数组

	//得到坐标范围
	void GetRange(Vector4 &rMin,Vector4 &rMax);

	void Clear(void) {PlateStrucIDM=-1;iBlock=0;}

	//重新创建内存，复制原来数据，释放原来的内存。若新旧指针不是同一个变量时，调用程序应设置旧指针为NULL
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

	//计算局部坐标系基矢量(u,v,w)及原点c0，与构件规定LocalCoorVector_Standard相同
	BOOL LocalCoorVector_Standard(Vector4 &c00,Vector4 &u,Vector4 &v,Vector4 &w) const;
	//w为法线，顶点编号符合右手定则，u、v与整体坐标系没有关系
	BOOL LocalCoorVector(const CVertex *pVexArray,Vector4 &c00,Vector4 &u,Vector4 &v,Vector4 &w) const;

	//计算中心点坐标，pVex为全局结点数组，因此这里要用传进来的坐标数组参数进行计算
	CVertex GetCenter(const CVertex *pVex) const;

	virtual BOOL Read(CASCFile &fin); //派生类的虚函数关键字virtual可写可不写，但总是虚函数
	virtual BOOL Write(CASCFile &fout,int idf,int idf_Struct,STRUCT_TYPE itype);

	virtual void ReadBin(CFile &fin);
	virtual BOOL WriteBin(CFile &fout);
};

struct DATA_SEQUENCE2
{
	float t,v;
};
//数据系列类，2个分量
class _SSG_DLLIMPEXP CDataSequence2
{
public:
	CDataSequence2(void){fname=L"";iWaveLibIndex=-1; iWaveLib=0; pData=NULL; nPoints=0; 
	fMinValue=fMaxValue=0;fMinValueTime=fMaxValueTime=0;fMaxFileTime=0;}

	CDataSequence2(const CDataSequence2 &ds)
	{
		*this=ds;
	}

	~CDataSequence2()
	{
		Clear();
	}

	CString fname; //文件名
	int iWaveLibIndex; //乔保娟 2015.6.11
	int iWaveLib;	//0----SSG地震波库， 1-----用户自定义波
	int nPoints;  //数据点数

	//以下为临时数据
	float fMinValue,fMaxValue;  //最大最小值，读入文件时统计得到
	float fMinValueTime,fMaxValueTime;  //最大最小值时刻，读入文件时统计得到 //2016.3.16
	float fMaxFileTime;  //数据文件中的最大时间

	DATA_SEQUENCE2	*pData;

	void Clear(void) 
	{
		if (pData){delete[] pData;	pData=NULL;}

		nPoints=0;
		//fMinValue=fMaxValue=0;
		//fname=L"";
	}
	BOOL IsValid(){return nPoints>0 && pData;}

	//赋值运算符重载
	CDataSequence2 & operator=(const CDataSequence2& data)
	{
		if(this==&data) return *this;
		Clear();
		fname=data.fname;
		iWaveLibIndex = data.iWaveLibIndex;
		iWaveLib =data.iWaveLib;
		nPoints=data.nPoints;
		pData=new DATA_SEQUENCE2[nPoints];
		ASSERT(pData);
		for(int i=0;i<nPoints;i++)
		{
			pData[i]=data.pData[i]; 
		}
		fMinValue=data.fMinValue;
		fMaxValue=data.fMaxValue;
		fMinValueTime=data.fMinValueTime;
		fMaxValueTime=data.fMaxValueTime;
		fMaxFileTime=data.fMaxFileTime;
		return *this;
	}

	//2017版本功能
	void ReadAcc2017(void); //只读取数据nPoints，pData

};

//地震荷载的一个工况数据
class _SSG_DLLIMPEXP CEarthQuake
{
public:
	CEarthQuake(void);
	CEarthQuake(CEarthQuake &eq) {*this=eq;}
	~CEarthQuake(){;}

	int iEarthQuakeProbility;
	int iAccDefineMethod;
	float fMainAmpEffect,f2ndAmpEffect,f3rdAmpEffect;  //有效峰值主方向加速度峰值，次方向峰值加速度，垂直方向峰值加速度 
	float fMainAmp,f2ndAmp,f3rdAmp; // 实际峰值主方向加速度峰值，次方向峰值加速度，垂直方向峰值加速度
	float fTimeInterval;	//数据点时间间隔
	float fStartComputeTime;//时程分析起始时间
	float fEndComputeTime;  //时程分析终止时间
	float fMaxFileTime;		//数据最大时间=max(X-文件最大时间, Y-文件最大时间, Z-文件最大时间)
	int iMainDir;			//主方向，0--X，1--Y


	CDataSequence2 cAX,cAY,cAZ;  //保存文件中的原值

	void GetRatio(float &fRatioX,float &fRatioY,float &fRatioZ);  //根据fMainAmp,fRatio1,fRatio2计算fRatioX,fRatioY,fRatioZ
	void ReadData();  //读取三个方向的地震波数据
	int CreateData(float *&ax,float *&ay,float *&az);  //创建数组，插值计算当前组的所有地震荷载点
	void  GetRealPeakAccValue(); //求fMainAmp
	CEarthQuake & operator=(const CEarthQuake &eq);
	BOOL  operator==(const CEarthQuake &eq);//邱海 2018年3月2日

	void Read10(CASCFile &fin);  //只读取配置信息，数据系列在使用时读取
	void Read(CASCFile &fin);  //只读取配置信息，数据系列在使用时读取
	void Write(CFile &fout); //只保存配置信息
};



class CLoadCase;
class _SSG_DLLIMPEXP COutput
{
public:
	//	COutput() {value=0;}
	COutput() {value=23;}	//乔保娟 2015.6.18
	COutput(const COutput &out) {*this=out;}
	~COutput() {;}

	void SetValue(int v) {value=v&0xff;}
	int GetValue() const {return value;}

	void SetOutputStrain(BOOL bOut) {bOut?value|=0x01:value&=~0x01;}
	void SetOutputStress(BOOL bOut) {bOut?value|=0x02:value&=~0x02;}
	void SetOutputForce(BOOL bOut) {bOut?value|=0x04:value&=~0x04;}
	void SetOutputDamage(BOOL bOut) {bOut?value|=0x08:value&=~0x08;}
	void SetOutputPlasticStrain(BOOL bOut) {bOut?value|=0x10:value&=~0x10;}

	BOOL IsOutputStrain() const {return (value&0x01)!=0?1:0;}
	BOOL IsOutputStress() const {return (value&0x02)!=0?1:0;}
	BOOL IsOutputForce() const {return (value&0x04)!=0?1:0;}
	BOOL IsOutputDamage() const {return (value&0x08)!=0?1:0;}
	BOOL IsOutputPlasticStrain() const {return (value&0x10)!=0?1:0;}

	COutput &operator=(const COutput &out)
	{
		if(this==&out) return *this;
		value=out.GetValue();
		return *this;
	}

private:
	// 0     1     2     3      4         5    6     7  
	//应变  应力  内力  损伤  塑性应变  保留  保留  保留
	int value;
};

//工况组合
class _SSG_DLLIMPEXP CLoadCase
{
public:
	CLoadCase(void);
	CLoadCase(CLoadCase &lc)
	{
		*this=lc;
	}

	~CLoadCase() {}

	CString sCaseName;  //工况组合名称
	CString sMemo;  //说明
	float fCoeffLiveLoad;		//活荷载质量加权系数
	float fCoeffDeadLoad;		//恒荷载质量加权系数

	//显式动力加载参数
	BOOL  bCloseNonLinear; //是否关闭几何非线性，1-关闭
	BOOL  bCalIsolatorBeta; //是否关闭几何非线性，1-关闭
	float fMassDamp;	//质量阻尼系数，
	float fStiffDamp; //刚度阻尼系数
	float fTerm1;  	//振型周期1
	float fTerm2;  	//振型周期2
	float fKsi1;   	//振型阻尼比1
	float fKsi2;   	//振型阻尼比2
	BOOL bInputAlpha;	//是否直接输入 //ver32
	float fTimeStep;  //加载时间步长
	int iCrtCons;  //混凝土二维本构模型,0弹性、1塑性损伤、2-性能化设计
	int iRebarCons;  //钢筋本构模型,0弹性、1弹塑性、2-性能化设计
	int	iStirrupCons;  //箍筋本构类型，取值为0--弹性、1--规范模型、2---约束混凝土模型
	int iSlabElastic; //是否考虑楼板弹性
	int iShearNonLinear; //是否考虑剪切非线性
	float fShearGama; //剪切屈服应变
	float fShearRatio; //剪切屈服后刚度比
	float fWallShear; //剪力墙分布钢筋抗剪调整系数
	int	iDamage;  //损伤定义方式
	int	iMethod;  //分析方法
	float fWaveAngle; //地震波主方向与坐标系夹角
	BOOL bStiffDamp;  //是否计入刚度阻尼
	int	iDampType;  //阻尼类型，0-Rayleigh阻尼，1-振型阻尼
	int nModeNum;  //振型个数，用于计算振型阻尼，m_iDampType=1时有效
	int iModalDampType;  //振型阻尼类型，0-全楼统一，1-按材料区分
	int iSimpleModalDamp;  //简化振型阻尼
	float fModeDamp[Sys_MaxModeNum];  //对应于m_iModeNum的各个振型的阻尼比，m_iDampType=1时有效
	float fModeDampSteel[Sys_MaxModeNum];  //对应于m_iModeNum的各个振型的阻尼比，m_iDampType=1时有效//2017.8.26

	CEarthQuake cEarchQuake;  //地震波信息

	CLoadCase& operator=(const CLoadCase& lc);
	BOOL operator==(const CLoadCase& lc);//ISO中震设计用，邱海2018年3月6日
	BOOL isIsoParaEqual(const CLoadCase& lc);//ISO中震设计用，判断工况参数是否改变 邱海2018年3月6日 不包括地震动信息和工况名


	void Read10(CASCFile &fin);
	void Read20(CASCFile &fin);
	void Read(CASCFile &fin);
	void Write(CFile &fout);


};

class _SSG_DLLIMPEXP CLoadCollection
{
public:
	CLoadCollection(){;}
	CLoadCollection(const CLoadCollection &load) 
	{
		*this=load;
	};
	~CLoadCollection(){RemoveAll();}

	int Append(CLoadCase *load);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return aLoadCasePtr.GetCount();}

	CLoadCase *GetAt(int i) {return aLoadCasePtr.GetAt(i);}

	CLoadCase *operator[](int i) {return aLoadCasePtr[i];}

	void SetAt(int i,CLoadCase *load) {aLoadCasePtr[i]=load;}

	CLoadCollection& operator=(const CLoadCollection&load);

	void Write(CFile &fout) 
	{
		for(int i=0;i<aLoadCasePtr.GetCount();i++)
			aLoadCasePtr[i]->Write(fout);
	}

private:
	CArray<CLoadCase*,CLoadCase*> aLoadCasePtr; //荷载工况组合集合
};

//已选地震动
class _SSG_DLLIMPEXP CWaveCollection
{
public:
	CWaveCollection(){;}
	CWaveCollection(const CWaveCollection &wave) 
	{
		*this=wave;
	};
	~CWaveCollection(){RemoveAll();}

	int Append(CEarthQuake *wave);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return awavePtr.GetCount();}

	CEarthQuake *GetAt(int i) {return awavePtr.GetAt(i);}

	CEarthQuake *operator[](int i) {return awavePtr[i];}

	void SetAt(int i,CEarthQuake *wave) {awavePtr[i]=wave;}

	CWaveCollection& operator=(const CWaveCollection&wave);

	void Write(CFile &fout) 
	{
		for(int i=0;i<awavePtr.GetCount();i++)
			awavePtr[i]->Write(fout);
	}

private:
	CArray<CEarthQuake*,CEarthQuake*> awavePtr; //荷载工况组合集合
};


//分组类
class _SSG_DLLIMPEXP CGroup
{
public:
	CGroup(void){nPrimitive=0; pIDG=NULL;}
	~CGroup(void){if(pIDG) delete[] pIDG; nPrimitive=0; pIDG=NULL;}

	CString sName;  //组名
	int nPrimitive; //本组图元数目
	int *pIDG; //构件图元IDG

	CGroup &operator=(const CGroup &grp)
	{
		if(this==&grp) return *this;
		sName=grp.sName;
		nPrimitive=grp.nPrimitive;
		delete[] pIDG;
		pIDG=new int[nPrimitive];
		for(int i=0;i<grp.nPrimitive;i++)
		{
			pIDG[i]=grp.pIDG[i];
		}
		return *this;
	}

	//得到该组中梁单元和壳单元数组
	void CreateElmGroup(const CFrame &frame,const CMesh &mesh,int &nBeamElm,int *&pBeamElm,int &nShellElm, int *&pShellElm,int &nQuadElm, int *&pQuadElm);   

	//得到该组中一维构件和二维构件数组
	void CreateStructGroup(const CFrame &frame,int &nBeam,int *&pBeam,int &nPlate, int *&pPlate);   

	void Read(CASCFile &fin);
	void Write(CFile &fout);
};

class _SSG_DLLIMPEXP CGroupCollection
{
public:
	CGroupCollection(){;}
	CGroupCollection(const CGroupCollection &gc) 
	{
		*this=gc;
	};
	~CGroupCollection(){RemoveAll();}

	int Append(CGroup *group);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return aGroupPtr.GetCount();}

	CGroup *GetAt(int i) {return aGroupPtr.GetAt(i);}

	CGroup *operator[](int i) {return aGroupPtr[i];}

	CGroupCollection& operator=(const CGroupCollection& gc);

	void Write(CFile &fout) 
	{
		for(int i=0;i<aGroupPtr.GetCount();i++)
			aGroupPtr[i]->Write(fout);
	}

private:
	CArray<CGroup*,CGroup*> aGroupPtr; //分组信息，分组信息只包括框架，不包括网格
};

//一个施工阶段信息
class _SSG_DLLIMPEXP CStage
{
public:
	CStage(void) {iStoryMin=iStoryMax=-1;}
	~CStage(void) {aGroupName.RemoveAll();}

	//成员变量
	int iStoryMin;  //楼层范围,不同的加载步楼层不能重复，如果本加载步独立于楼层之外，可以设楼层范围为（-1，-1）
	int iStoryMax;
	CArray<CString,CString&> aGroupName;   //属于本次加载步的分组名称数组

	//成员函数
	CStage & operator=(const CStage &stage)
	{
		if(this==&stage) return *this;
		iStoryMin=stage.iStoryMin;
		iStoryMax=stage.iStoryMax;
		aGroupName.RemoveAll();
		aGroupName.Copy(stage.aGroupName);
		//for(int i=0;i<stage.aGroupName.GetCount();i++)
		//{
		//	CString str=stage.aGroupName[i];
		//	aGroupName.Add(str);
		//}
		return *this;
	}


	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
};


//施工阶段数据集合
class _SSG_DLLIMPEXP CStageCollection
{
public:
	CStageCollection(void){;}

	~CStageCollection(void);
	//成员变量
	CArray<CStage*,CStage*> aStagePtr; //楼层施工阶段数组，其中的构件要排除前面其他组用过的数据

	//成员函数

	void Clear(void) ;

	CStageCollection & operator=(const CStageCollection &stage)
	{
		if(this==&stage) return *this;

		Clear();

		for(int i=0;i<stage.aStagePtr.GetCount();i++)
		{
			CStage *pstage=new CStage;
			*pstage=*(stage.aStagePtr[i]);
			aStagePtr.Add(pstage);
		}

		return *this;
	}

	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
};

class _SSG_DLLIMPEXP CStoryItem
{
public:
	CStoryItem(void) {pStory=NULL;}

	CStoryItem(CStoryItem &item)
	{
		*this=item;
	}

	~CStoryItem() {delete[] pStory;pStory=NULL;}

	int nStory;
	CStory *pStory;
	int iStoryMin;//显示的最低楼层 邱海 2016年12月13日
	int iStoryMax;//显示的最高楼层

	CStoryItem & operator=(CStoryItem &item)
	{
		if(this==&item) return *this;

		Clear();

		nStory=item.nStory;
		if(nStory>0)
		{
			pStory=new CStory[nStory];
			if(!pStory)
			{
				Clear();
				return *this;
			}

			for(int i=0;i<=nStory;i++)
				pStory[i]=item.pStory[i];
		}
		iStoryMin=item.iStoryMin;
		iStoryMax=item.iStoryMax;

		return *this;
	}

	void Clear(void)
	{
		nStory=0;
		delete[] pStory;
		pStory=NULL;
		iStoryMin=0;
		iStoryMax=0;
	}

};

STRUCT_TYPE GetStructType(const CBeamElm &elm);
STRUCT_TYPE GetStructType(const CTriangleElm &elm);
STRUCT_TYPE GetStructType(const CQuadElm &elm);


//项目群信息
struct MUL_PROJRCT
{
	MUL_PROJRCT(void)
	{
		sFile=L"";
		iFirstNode=0;
		iFirstBeamElm=0;
		iFirstTriElm=0;
		iFirstQuadElm=0;
		nNode=0;
		nBeamElm=0;
		nTriElm=0;
		nQuadElm=0;

		c0.x=0.0f;
		c0.y=0.0f;
		c0.z=0.0f;
		angle=0.0f;

		sName=L"";

		fRadium=0;
		fHalfHeight=0;
	};

	CString sFile;
	int iFirstNode;
	int iFirstBeamElm;
	int iFirstTriElm;
	int iFirstQuadElm;
	int nNode;
	int nBeamElm;
	int nTriElm;
	int nQuadElm;

	CVertex c0; //坐标原点偏移量
	Vector4 vMin,vMax; //实际坐标范围，考虑了坐标偏移和旋转
	float fRadium; //最大占地半径，米
	float fHalfHeight; //楼高的一半，米
	float angle; //绕z轴转角，单位度
	CString sName; //建筑物名称
};

class _SSG_DLLIMPEXP CRefPoint
{
public:
	CRefPoint(void){;}
	~CRefPoint() {aVex.RemoveAll();}

	void Clear(void) {aVex.RemoveAll();}


	//切换一个点,如果不存在则新增，返回TRUE；如果已经存在则删除，返回FALSE
	BOOL SetVex(int vexid)
	{
		for (int i=0;i<aVex.GetCount();i++)
		{
			if(aVex[i]==vexid)
			{
				aVex.RemoveAt(i);
				return FALSE;
			}
		}
		aVex.Add(vexid);
		return TRUE;
	}

	CArray<int,int> aVex; //计算虚拟交叉点用的参考点ID
};

//竖向构件是否位于用户选择的层间位移角输出位置的集合内，返回序号，不存在则返回-1
//如果用户未定义，则返回-2，表示缺省全部输出
extern "C" _SSG_DLLIMPEXP int DriftPosEle(const CBeamElm &elm);
extern "C" _SSG_DLLIMPEXP int DriftPos(const CBeamStruc &pillar);


//线单元是否全部都在矩形范围内
int IsInRect(const CBeamElm &elm,float xmin,float ymin,float xmax,float ymax);
int IsInRect(const CTriangleElm &elm,float xmin,float ymin,float xmax,float ymax);
int IsInRect(const CQuadElm &elm,float xmin,float ymin,float xmax,float ymax);
//线构件是否全部都在矩形范围内
BOOL IsInRect(const CBeamStruc &beam,float xmin,float ymin,float xmax,float ymax);
BOOL IsInRect(const CPlateStruc &plate,float xmin,float ymin,float xmax,float ymax);

//数据路径
class _SSG_DLLIMPEXP CDataPath
{
public:
	CDataPath(void) {;}
	~CDataPath() {aIDM.RemoveAll();}
	CDataPath(const CDataPath &path) 
	{
		*this=path;
	}

	CString sName;

	enum PATH_TYPE
	{
		PATHTYPE_ELEM=0,
		PATHTYPE_NODE=1,
	}iDataType;

	CArray<int,int> aIDM; //IDM数组

	CDataPath &operator=(const CDataPath &path)
	{
		if(this==&path) return *this;

		sName=path.sName;
		iDataType=path.iDataType;
		aIDM.RemoveAll();
		aIDM.Copy(path.aIDM);
		return *this;
	}

	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
};

class _SSG_DLLIMPEXP CDataPathCollection
{
public:
	CDataPathCollection(void){;}
	~CDataPathCollection()
	{
		Clear();
	}
	CArray<CDataPath*,CDataPath*> aPathPtrArray;

	void Clear();

	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
};

//全局函数---------------------------------------------------------------------


//获取构件的缺省颜色
extern "C" _SSG_DLLIMPEXP COLORREF GetStructDefaultColor(STRUCT_TYPE type,int iSubType);



//从内存ID(IDM)换成拾取ID(IDG),宏定义中必须加括号，否则结果不可预知
//#define GETIDG(IDM,ArrayType) ((IDM)+(ArrayType))  
extern "C" _SSG_DLLIMPEXP int GetIDG(int idm,STRUCT_TYPE iType); 

//从拾取ID(IDG)换成内存ID(IDM)
extern "C" _SSG_DLLIMPEXP int GetIDM(int IDG);
//从内存ID(IDM)换成拾取ID(IDG)
extern "C" _SSG_DLLIMPEXP STRUCT_TYPE GetPickedType(int IDG);

//从IDG换成类型起始特征值
extern "C" _SSG_DLLIMPEXP int GetBaseType(int IDG);



//对坐标相同的点进行合并,返回旧点编号到新点编号的索引index， 同时原结点坐标数组被更新，索引数组为函数创建的动态内存，调用程序用完后应释放
//失败则返回空指针
extern "C" _SSG_DLLIMPEXP int *Merge(CVertex *pVex,int nOldNPoint,int &nNewPoint);

//多个结点配对合并
//pVex2与pVex1进行匹配，若找到则返回pVex1对应的pID1编码，否则返回StartID开始的编码
//pID1、pVex2和pVex1数组下标均从0开始
//pID1为pVex1对应的结点编码
extern "C" _SSG_DLLIMPEXP int *MergeWithArray(const int *pID1,int nVex1,const Vector4 *pVex1,int nVex2,const Vector4 *pVex2,int StartID);

//返回多边形顶点编码数组,首尾点不重合,不成功则返回NULL
//假设给定的结点坐标不重合，即没有坐标相同但编码不同的点,调用程序应释放返回的指针内存
//输入: pPolygonLine--按顺序围成多边形的线段数组,线段必须按顺序给出，线段编号方向可以任意
extern "C" _SSG_DLLIMPEXP int *GetPolygonVexID(int nLine,const CLine *pPolygonLine);

//按阶段排序,vex--被按阶段从小到大排列,nData--数组大小
//返回动态创建的序号索引数组,外部程序必须释放
extern "C" _SSG_DLLIMPEXP int *StackSortNodeByStage(int nData,CVertex  *vex); 

//按阶段排序,beam--被按阶段从小到大排列,nData--数组大小
//返回动态创建的序号索引数组,外部程序必须释放
extern "C" _SSG_DLLIMPEXP int *StackSortBeamElmByStage(int nData,CBeamElm  *beam); 

//按阶段排序,tri--被按阶段从小到大排列,nData--数组大小
//返回动态创建的序号索引数组,外部程序必须释放
extern "C" _SSG_DLLIMPEXP int *StackSortTriElmByStage(int nData,CTriangleElm  *tri); 
extern "C" _SSG_DLLIMPEXP int *StackSortQuadElmByStage(int nData,CQuadElm  *quad); 


//计算XY面内的旋转角，单位：度，center--旋转中心，p1,p2--旋转的起点和终点，两个点可以不在同一圆弧上，只代表从center发出的射线上的点
//所有坐标只用x,y分量
extern "C" _SSG_DLLIMPEXP double RotateAngleDouble(const CVertex &center,const CVertex &p1,const CVertex &p2);



//结构线剖分网格所生成的子线段
struct _SSG_DLLIMPEXP SUB_LINE
{
	int		nSubLine;	//初始化为0，表示没有划分子线段
	CLine	*pSubLine;	//子线段数组，初始化为NULL
};

//结构线是否被梁和墙用到
struct _SSG_DLLIMPEXP LINE_USED
{
	LINE_USED(void) {bBeam=FALSE;bPillar=FALSE;bWall=FALSE;bBeamWall=FALSE;bAlong=TRUE;bLink=FALSE;bAnti=FALSE;}
	BOOL bBeam;    //是否被梁用到
	BOOL bPillar;  //是否被柱用到
	BOOL bWall;    //是否被墙用到，不管墙与结构线是否同楼层，墙梁不算墙
	BOOL bBeamWall;//是否被墙梁用到，不管墙梁与结构线是否同楼层
	BOOL bAlong;   //是否仅仅被两端铰接的线构件使用
	BOOL bLink;    //是否被一般连接使用
	BOOL bAnti;    //是否被两端铰接的线构件使用
	float	fWeight;	//加密累计权重
	float	fMeshRatio;	//网格累计加密系数
};


//清理无效图元
class _SSG_DLLIMPEXP CRemoveInvalidPrimitive
{
public:
	CRemoveInvalidPrimitive(void) {;}
	~CRemoveInvalidPrimitive(void) {;}

protected:
	virtual void RearrangeID()=0;  //重新编排ID，去掉无效图元
	void RemoveInvalidVex(int &nVex,CVertex *pVex,int *index1,CGroupCollection &aGroup);      //去掉无效框架点，被RearrengeID调用
	void RemoveInvalidNode(int &nVex,CVertex *pVex,int *index1);      //去掉无效网格结点，被RearrengeID调用
	void RemoveInvalidBeamElm(int &nElm,CBeamElm *pElm,CVertex *pVex);   //被RearrengeID调用
	void RemoveInvalidTriangleElm(int &nElm,CTriangleElm *pElm,CVertex *pVex);   //被RearrengeID调用
	void RemoveInvalidQuadElm(int &nElm,CQuadElm *pElm,CVertex *pVex);   //被RearrengeID调用
	void RemoveInvalidLine(int &nLine,CLine *pLine,CArray<CVertex,CVertex&> &aVex,int *index2,CGroupCollection &aGroup);   //被RearrengeID调用
	void RemoveInvalidGuides(int &nGuides,CVertex *pVex,CLine *pLine,CGroupCollection &aGroup);   //被RearrengeID调用
	void RemoveInvalidBeamStruc(int &nStruc,CArray<CLine,CLine&> &aLine,CBeamStruc *pStruc,int *index4,CGroupCollection &aGroup);   //被RearrengeID调用
	void RemoveInvalidPlateStruc(int &nStruc,CArray<CLine,CLine&> &aLine,CPlateStruc *pStruc,int *index3,CGroupCollection &aGroup);   //被RearrengeID调用

	void RemoveInvalidGroup(STRUCT_TYPE iPrimType,int nStruc,const int *index1,CGroupCollection &aGroup);  //被以上各图元函数调用
};

extern "C" _SSG_DLLIMPEXP STRUCT_KEYWORD g_StructKeyword[Sys_StructTypeNum];
extern "C" _SSG_DLLIMPEXP STRUCT_PROPERTY1 g_PropTable1[16];
