#pragma once
#include "Interpolation.h"
class CMat
{
public:
	CMat();
	~CMat();

	static CInterpolation* GetConcrete(char chConcrete);
	static CInterpolation* GetRebar(char chRebar);
};

