#pragma once

#include "HeadDefine.h"
#include "SysPara.h"

class CASCFile;
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

	void Release(int idof) //释放位移约束
	{
		ASSERT(idof<Sys_DOF && idof>=0); 
		Type&=~(1<<(idof<<1)); Value[idof]=0;
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

	BOOL HasConstraint() const //1--位移约束，0-没有约束
	{
		for(int i=0;i<Sys_DOF;i++) 
		{
			if((Type&(1<<(i<<1)))>0)
				return TRUE;
		}
		return FALSE;
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
	BOOL Write2020(CASCFile &fout);
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

	CBoundary operator[](int i) {return aBoundary[i];}

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
