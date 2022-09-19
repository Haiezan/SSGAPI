#pragma once
#include "ASCFile.h"

//生成非隔震模型
class _SSG_DLLIMPEXP CNonISOModel
{
public:
	CNonISOModel(void);
	CNonISOModel(CNonISOModel &data)
	{
		*this=data;
	}
	~CNonISOModel(){}
	CNonISOModel& operator=(const CNonISOModel& data);

	//非隔震模型
	BOOL m_bBaseStory; //底层隔震
	BOOL m_bOtherStory; //中间层隔震
	int m_iBndType1; //底层约束类型
	int m_iBndPos1; //底层约束位置
	int m_iBndType2; //中间层约束类型
	int m_iBndPos2; //中间层约束位置
	float m_fSpringStiff1[6];//底层大刚度弹簧刚度 
	float m_fSpringStiff2[6];//中间层大刚度弹簧刚度
	
	void Read(CASCFile &fin);
	void Write(CFile &fout);
};
