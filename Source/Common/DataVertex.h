#pragma once
#include "HeadDefine.h"

#include "Vector4.h"
#include "Matrix4x4.h"
#include "DataPrimitive.h"

////#include "SysPara.h"
//#include "PublicFunc.h"
//#include "PublicFunc_MFC.h"
//#include "PublicFunc_Cpp.h"
//
//#include "ASCFile.h"
//#include "UserDefine.h"
//#include "BeamSection.h"
//#include "Material.h"
//#include "EdgeStruct.h"
//#include "PlateSection.h"
#include "Loadmap.h"

#include <afxtempl.h>
#include <vector>

#include <map>

class CLine;

using namespace std;

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
		//*this=v;
		*(CPrimitiveProp *)this=(CPrimitiveProp &)v;

		x=v.x;y=v.y;z=v.z;
		idRigidBody=v.idRigidBody;
		idmBoundary=v.idmBoundary;
		iGeoType=v.iGeoType;
		aload=v.aload;
		aDyload = v.aDyload;
		for (int i=0;i<6;i++)
		{
			fDeadLoad[i]=v.fDeadLoad[i];
			fLiveLoad[i]=v.fLiveLoad[i];
		}
	}

	CVertex & operator=(const CVertex &v)
	{
		if(this==&v && idmStory==v.idmBoundary) return *this;

		*(CPrimitiveProp *)this=(CPrimitiveProp &)v;

		x=v.x;y=v.y;z=v.z;
		idRigidBody=v.idRigidBody;
		idmBoundary=v.idmBoundary;
		iGeoType=v.iGeoType;
		aload=v.aload;
		aDyload = v.aDyload;
		for (int i=0;i<6;i++)
		{
			fDeadLoad[i]=v.fDeadLoad[i];
			fLiveLoad[i]=v.fLiveLoad[i];
		}
		return *this;
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
	//LOADMAP mapload;//对应荷载工况的荷载
	LOADASSIGN aload;//对应荷载工况的荷载
	LOADASSIGN aDyload;//对应荷载工况的动荷载

	CVertex & operator=(const Vector4 &v)
	{
		x=v.x;y=v.y;z=v.z;
		return *this;
	}

	BOOL IsCrossStory(void) const {return iGeoType & 0x01;}
	void SetCrossStory(BOOL bCrossStory=TRUE) {if(bCrossStory) iGeoType |= 0x01;else iGeoType &= ~0x01;}

	BOOL IsOnFloor(void);//在楼面

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
		aload.clear();
		aDyload.clear();
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
	virtual BOOL Write2020(CASCFile &fout,int idf); 
	virtual void ReadBin(CFile &fin);   
	virtual BOOL WriteBin(CFile &fout);
	virtual BOOL IsVisible(const CVertex &vMin,const CVertex &vMax) const;

	void GenLoadId(bool bReWrtie=true);//由	float fDeadLoad 和float fLiveLoad生成Load加入mapload 供2020之后版本读取
	void GenLoadVal();//由mapload生成fDeadLoad和fLiveLoad 供2020之前版本读取
	void ClearLoad();//清空荷载
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

//点积
inline float VexDistance(const CVertex &a,const CVertex &b)
{
	float x = a.x - b.x;
	float y = a.y - b.y;
	float z = a.z - b.z;
	return sqrtf(x*x+y*y+z*z);
}