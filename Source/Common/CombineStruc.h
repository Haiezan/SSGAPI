#pragma once
#include "../Common/Data.h"
class CCombineStruc
{
public:
	CCombineStruc();
	~CCombineStruc();

	int ID;

	vector< CPlateStruc*> m_pPlate;
	vector<int> m_iPlateID;
	vector<int> m_pElmID;

	vector< CBeamStruc*> m_pBeam;
	vector<int> m_iBeamID;

	bool IsBeamIn(CBeamStruc* pBeam);

	float Xmax, Xmin, Ymax, Ymin, Zmax, Zmin;

	//CArray<CPlateStruc, CPlateStruc&> m_aPlate;
	
	//CArray<int, int> m_iPlateID;
	//CArray<int, int> m_aElms;
	//vector<CPlateStruc> m_aPlate;
};

struct SShareLineStruc
{
	int iLineID;
	CArray<int, int> aStrus;
	CArray<int, int> aBeams;
};