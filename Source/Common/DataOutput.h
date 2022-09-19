#pragma once
#include "HeadDefine.h"

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
