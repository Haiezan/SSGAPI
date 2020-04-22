#pragma once
#include "HeadDefine.h"
//组合构件定义
class _SSG_DLLIMPEXP CCombineFrame
{
public:
	CCombineFrame(void);
	~CCombineFrame(void);

	CCombineFrame(const CCombineFrame &cf)
	{
		*this=cf;
	}

	CArray<int,int> m_aIDG; //一个组合构件的构件编码数组

	int iStory; //楼层
	int iAngle;  //方向角，0-360，度

	CCombineFrame &operator=(const CCombineFrame &cf)
	{
		if(this==&cf) return *this;
		iStory=cf.iStory;
		iAngle=iAngle;
		m_aIDG.RemoveAll();
		m_aIDG.Copy(cf.m_aIDG);
		return *this;
	};
};

class _SSG_DLLIMPEXP CCombineFrameCollection
{
public:
	CCombineFrameCollection(void)
	{

	};

	~CCombineFrameCollection(void)
	{
		Clear();
	};

	CArray<CCombineFrame*,CCombineFrame*> m_aCombineFramePtr; //组合构件指针数组

	CCombineFrameCollection& operator=(const CCombineFrameCollection& cfc)
	{
		if(this==&cfc) return *this;
		Clear();
		for (int i=0;i<cfc.m_aCombineFramePtr.GetCount();i++)
		{
			CCombineFrame *cf=new CCombineFrame;
			*cf=*(cfc.m_aCombineFramePtr[i]);
			m_aCombineFramePtr.Add(cf);
		}
		return *this;
	}

	void Clear(void)
	{
		if(m_aCombineFramePtr.GetCount()==0) return;

		for (int i=0;i<m_aCombineFramePtr.GetCount();i++)
		{
			delete m_aCombineFramePtr[i];
		}
		m_aCombineFramePtr.RemoveAll();
	}

	void Read(const CString &fname);  //读入网格时要调用
	void Write(const CString &fname);
};
