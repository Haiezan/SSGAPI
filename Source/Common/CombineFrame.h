#pragma once
#include "HeadDefine.h"
//��Ϲ�������
class _SSG_DLLIMPEXP CCombineFrame
{
public:
	CCombineFrame(void);
	~CCombineFrame(void);

	CCombineFrame(const CCombineFrame &cf)
	{
		*this=cf;
	}

	CArray<int,int> m_aIDG; //һ����Ϲ����Ĺ�����������

	int iStory; //¥��
	int iAngle;  //����ǣ�0-360����

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

	CArray<CCombineFrame*,CCombineFrame*> m_aCombineFramePtr; //��Ϲ���ָ������

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

	void Read(const CString &fname);  //��������ʱҪ����
	void Write(const CString &fname);
};
