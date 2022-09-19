#pragma once
#include "HeadDefine.h"
#include <vector>

class CFrame;
class CMesh;
class CASCFile;

//分组类
class _SSG_DLLIMPEXP CGroup
{
public:
	CGroup(void){nPrimitive=0;bRelateOutput=true;pIDG=NULL;}
	~CGroup(void){if(pIDG) delete[] pIDG; nPrimitive=0; pIDG=NULL;}

	CString sName;  //组名
	int nPrimitive; //本组图元数目
	int *pIDG; //构件图元IDG
	bool bRelateOutput;

	CGroup &operator=(const CGroup &grp)
	{
		if(this==&grp) return *this;
		sName=grp.sName;
		nPrimitive=grp.nPrimitive;
		bRelateOutput=grp.bRelateOutput;
		delete[] pIDG;
		pIDG=new int[nPrimitive];
		for(int i=0;i<grp.nPrimitive;i++)
		{
			pIDG[i]=grp.pIDG[i];
		}
		return *this;
	}

	bool operator==(const CGroup& grp);

	//得到该组中梁单元和壳单元数组
	void CreateElmGroup(const CFrame &frame,const CMesh &mesh,int &nBeamElm,int *&pBeamElm,int &nShellElm, int *&pShellElm,int &nQuadElm, int *&pQuadElm);   

	//得到该组中一维构件和二维构件数组
	void CreateStructGroup(const CFrame &frame,int &nBeam,int *&pBeam,int &nPlate, int *&pPlate);   

	void Read(CASCFile &fin);
	void Write(CFile &fout);
	void Write2020(CFile &fout);

	//判断是否有效
	bool bValidGroup(const CFrame &frame);
	//清空无效成员
	bool ClearInvalid(CFrame &frame);
	//判断是否数据相同
	bool IsGroup(std::vector<int> &vId) const;
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

	void Write2020(CFile &fout) 
	{
		for(int i=0;i<aGroupPtr.GetCount();i++)
			aGroupPtr[i]->Write2020(fout);
	}

	void Rearrange();

	int Find(std::vector<int> &vId) const;
private:
	CArray<CGroup*,CGroup*> aGroupPtr; //分组信息，分组信息只包括框架，不包括网格
};
