#pragma once
#include "HeadDefine.h"

class _SSG_DLLIMPEXP CStoryItem
{
public:
	CStoryItem(void) {pStory=NULL;}

	CStoryItem(CStoryItem &item)
	{
		*this=item;
	}

	~CStoryItem() {delete[] pStory;pStory=NULL;}

	int nStory;
	CStory *pStory;
	int iStoryMin;//显示的最低楼层 邱海 2016年12月13日
	int iStoryMax;//显示的最高楼层

	CStoryItem & operator=(CStoryItem &item)
	{
		if(this==&item) return *this;

		Clear();

		nStory=item.nStory;
		if(nStory>0)
		{
			pStory=new CStory[nStory];
			if(!pStory)
			{
				Clear();
				return *this;
			}

			for(int i=0;i<=nStory;i++)
				pStory[i]=item.pStory[i];
		}
		iStoryMin=item.iStoryMin;
		iStoryMax=item.iStoryMax;

		return *this;
	}

	void Clear(void)
	{
		nStory=0;
		delete[] pStory;
		pStory=NULL;
		iStoryMin=0;
		iStoryMax=0;
	}
};
