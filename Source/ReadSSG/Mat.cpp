#include "stdafx.h"
#include "Mat.h"


CMat::CMat()
{
}


CMat::~CMat()
{
}
CInterpolation* CMat::GetConcrete(char chConcrete)
{
	CInterpolation* m_pConcreteFc = NULL;
	switch (chConcrete)
	{
	case 30:
		m_pConcreteFc = new CInterpolation(
			"0.0, 0.000469, 0.00097, 0.001472, 0.00368 ,0.005888, 10.0, 1000000.0",
			"0.0, 14.07, 18.696365, 20.100002, 12.021566, 7.50004, 3.606483, 3.6");
		break;
	default:
		break;
	}
	return m_pConcreteFc;
}
CInterpolation* CMat::GetRebar(char chRebar)
{
	CInterpolation* m_pRebar = NULL;
	switch (chRebar)
	{
	case 3:
		m_pRebar = new CInterpolation(
			"-0.025, -0.002, 0.0, 0.002, 0.025",
			"-487.0, -400.0, 0.0, 400.0, 487.0");
		break;
	default:
		break;
	}
	return m_pRebar;
}
