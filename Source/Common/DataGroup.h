#pragma once
#include "HeadDefine.h"
#include <vector>

class CFrame;
class CMesh;
class CASCFile;

//������
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

	CString sName;  //����
	int nPrimitive; //����ͼԪ��Ŀ
	int *pIDG; //����ͼԪIDG
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

	//�õ�����������Ԫ�Ϳǵ�Ԫ����
	void CreateElmGroup(const CFrame &frame,const CMesh &mesh,int &nBeamElm,int *&pBeamElm,int &nShellElm, int *&pShellElm,int &nQuadElm, int *&pQuadElm);   

	//�õ�������һά�����Ͷ�ά��������
	void CreateStructGroup(const CFrame &frame,int &nBeam,int *&pBeam,int &nPlate, int *&pPlate);   

	void Read(CASCFile &fin);
	void Write(CFile &fout);
	void Write2020(CFile &fout);

	//�ж��Ƿ���Ч
	bool bValidGroup(const CFrame &frame);
	//�����Ч��Ա
	bool ClearInvalid(const CFrame &frame);
	//�ж��Ƿ�������ͬ
	bool IsGroup(std::vector<int> &vId) const;

	//Add 2024��12��16��
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
	float m_fAngle; //  �Զ��������������ĽǶ� ��ҵ��2023��2��20��
private:
	CArray<CGroup*,CGroup*> aGroupPtr; //������Ϣ��������Ϣֻ������ܣ�����������
};