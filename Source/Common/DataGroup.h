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
	CGroup(void)
		: nPrimitive(0)
		, bRelateOutput(false)
		, pIDG(nullptr)
	{
	}

	~CGroup(void)
	{
		if (pIDG != nullptr)
			delete[] pIDG;

		nPrimitive = 0;
		pIDG = nullptr;
	}

	CString sName;  //组名
	int nPrimitive; //本组图元数目
	int *pIDG; //构件图元IDG
	bool bRelateOutput;

	CGroup &operator=(const CGroup &grp)
	{
		if(this==&grp) 
			return *this;

		sName = grp.sName;
		nPrimitive = grp.nPrimitive;
		bRelateOutput = grp.bRelateOutput;

		if(pIDG!=nullptr)
			delete[] pIDG;

		pIDG = new int[nPrimitive];
		memcpy(pIDG, grp.pIDG, sizeof(int) * grp.nPrimitive);

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
	bool ClearInvalid(const CFrame &frame);
	//判断是否数据相同
	bool IsGroup(std::vector<int> &vId) const;

	//Add 2024年12月16日
	void AddPrimitive(int IDG);

	void AddPrimitives(std::vector<int>& vId);
	//BC Group
	void ReadBC(int id, CASCFile& fin);
	void WriteBC(int id, CFile& fout);
	//Load Group
	void ReadLD(int id, CASCFile& fin);
	void WriteLD(int id, CFile& fout);
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

	CGroup *operator[](int i)const {return aGroupPtr[i];}

	CGroupCollection& operator=(const CGroupCollection& gc);

	bool operator!=(const CGroupCollection& gc);

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
	float m_fAngle; //  自定义层间剪力，组件的角度 辛业文2023年2月20日
private:
	CArray<CGroup*,CGroup*> aGroupPtr; //分组信息，分组信息只包括框架，不包括网格
};