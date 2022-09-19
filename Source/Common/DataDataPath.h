#pragma once
#include "HeadDefine.h"

class CASCFile;
//����·��
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

	CArray<int,int> aIDM; //IDM����

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