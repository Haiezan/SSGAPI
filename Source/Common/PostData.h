#pragma once
#include "..\Common\data.h"

//某时刻的物理场,先调用Create创建内存空间，里面含动态数组，类数组删除时要先调用Clear()  //结点、单元、楼层、构件都用
class _SSG_DLLIMPEXP CFieldOneStep
{
public:
	CFieldOneStep(){pData=NULL;nRealNode=0;nDataNum=0;}
	~CFieldOneStep() 
	{
		Clear();
	}

	//实际结点数或单元数，超过的数据为0，主要用于标识分阶段加载的数据截止点
	int nRealNode;

	//物理量数组，对于动力分析，第一个数为时刻；对于静力加载，第一个数为该阶段序号；对于模态分析，第一个数为频率
	//不包括ID，按列存储，下标=列号*nItems+项目序号+1,nItems在调用函数中定义
	float *pData; //不要直接创建内存，应使用CreateBuf，保证nDataNum与pData同步
	int nDataNum; //pData长度,单位：float

public:

	float *CreateBuf(int DataNum)
	{
		nDataNum=DataNum;
		delete[] pData;
		pData=new float[nDataNum];
		return pData;
	}

	CFieldOneStep & operator=(const CFieldOneStep &v);
	void Clear(void);

	//得到时刻,单位秒,对于动力分析数据，pBuf的第一个数据就是fTime
	float GetTime()
	{
		if(!pData) return 0;
		return pData[0];
	}

	//得到时刻,单位秒,对于静力加载数据，pBuf的第一个数据就是阶段号
	int GetStage()
	{
		if(!pData) return 0;
		return (int)pData[0];
	}

	//得到频率,单位Hz,对于模态分析数据，pBuf的第一个数据就是频率，适用于模态振型文件
	float GetFreq()
	{
		if(!pData) return 0;
		return pData[0];
	}
	//得到模态周期，单位:s
	float GetPeriod() 
	{
		float fr=GetFreq();
		if(fr==0) return 10000.0f;
		return 1.0f/fr;
	}

	//得到静力加载时该阶段结点数
	int GetRealNodeNum()
	{
		if(!pData) return 0;
		return nRealNode;
	}

	float *GetColPtr(int iCol,int nItems) {return pData+iCol*nItems+1;}  //得到列数组地址，col列号，nItems项目数，对float操作偏移不用*4
	float GetItemData(int iItem,int iCol,int nItems) {return pData[iCol*nItems+iItem+1];}  //得到一个数据项，iItem项目号,col分量号，nItems项目总数
	float &GetItemDataRef(int iItem,int iCol,int nItems) {return pData[iCol*nItems+iItem+1];}  //得到一个数据项的地址，iItem项目号,col分量号，nItems项目总数

	BOOL ReadStepBin(CFile &fin,int nItems,int nCols);  //F-3文件，从当前位置读二进制文件，读入所有分量，nNode结点数，nCol要读的分量数(从第0列开始)
	BOOL ReadColBin(CFile &fin,int nItems,int iCol);  //从当前位置读二进制文件，读入单个分量，nNode结点数，iCol要读入的分量号
};

//结点位移数据，适应分阶段静力加载，不存在的数据清零
class _SSG_DLLIMPEXP CNodeFieldSet
{
public:
	CNodeFieldSet()
	{
		iGroupID=-1;
		nMaxSteps=0;
	}

	~CNodeFieldSet() {Clear();}

	int iGroupID;  //对应的分组序号，-1表示全部结点,事先直接赋值,-2代表内置分组

	//以下数据在读文件时赋值
	int nItems;        //读取的结点数,静力加载文件不使用此数据，应使用aFieldsPtr中的GetRealNodeNum()获取
	int nComponents;  //内存分量数,Read前赋值，超过此数值的分量读取后被丢掉
	int nFileComponents;  //文件中的实际分量数,Read前赋值，
	CString sTitle;  //物理场标题,Read前赋值
	CString pComponentName[Sys_Max_Node_Components];  //分量名称,Read前赋值，前三个分量必须是dx,dy,dz
	float fMin[Sys_Max_Node_Components],fMax[Sys_Max_Node_Components];  //最大最小值,读入后即赋值
	int nMaxSteps;  //文件中最大时间步数，读入文件时赋值

	CArray<CFieldOneStep*,CFieldOneStep*> aFieldsPtr; //场函数数组，下标为时间步序号，Read中赋值


	CNodeFieldSet &operator=(const CNodeFieldSet &ns)
	{
		if(this==&ns) return *this;

		Clear();

		iGroupID=ns.iGroupID;
		nItems=ns.nItems;
		nComponents=ns.nComponents;
		nFileComponents=ns.nFileComponents;
		sTitle=ns.sTitle;
		for (int i=0;i<Sys_Max_Node_Components;i++)
		{
			pComponentName[i]=ns.pComponentName[i];
			fMin[i]=ns.fMin[i];
			fMax[i]=ns.fMax[i];
		}
		nMaxSteps=ns.nMaxSteps;
		for (int i=0;i<ns.aFieldsPtr.GetCount();i++)
		{
			CFieldOneStep *p=new CFieldOneStep;
			*p=*(ns.aFieldsPtr[i]);
			aFieldsPtr.Add(p);
		}
		return *this;
	}

	//方法
	BOOL IsValid(void) {return aFieldsPtr.GetSize()>0?TRUE:FALSE;}

	//得到时间分辨率
	float GetDTime(void) 
	{
		if(aFieldsPtr.GetCount()==0) return 0;
		if(aFieldsPtr.GetCount()==1) return aFieldsPtr[0]->GetTime();
		return aFieldsPtr[1]->GetTime()-aFieldsPtr[0]->GetTime();
	}

	inline int GetStepNumber() const {return (int)aFieldsPtr.GetSize();}  //已经读入的时间步或加载步
	void Clear();  //清除所有数据，释放所有内存
	void GetMaxMin();  //计算最大最小值点

	//读入二进制结点位移，bSelectCol=TRUE时选择一个分量读取，FALSE时读取所有分量
	BOOL ReadBinNodeField_AllStep(const CString &fname,bool bSelectCol=false); 
	//读入二进制结点位移;iTime--读取的时刻(-1时全读),只读一步，因此GetStepNumber会返回1
	BOOL ReadBinNodeField_OneStep(const CString &fname,int iTime);

	//读入二进制结点位移，并做order阶微分;iTime--读取的时刻(-1时全读),实际读取3步，微分后保留1步，因此GetStepNumber会返回1
	BOOL ReadBinNodeField_OneStep_Diff(const CString &fname,int iTime,int order);

	//读入二进制分阶段加载结点位移，bSelectCol=TRUE时选择一个分量读取，FALSE时读取所有分量
	BOOL ReadBinStaticNodeField_AllStage(const CString &fname,bool bSelectCol=false); 
	//读入二进制分阶段加载结点位移;iTime--读取的时刻(-1时全读),只读一步，因此GetStepNumber会返回1
	BOOL ReadBinStaticNodeField_OneStage(const CString &fname,int iStage);

	BOOL Disp2Speed(); //由位移计算速度
	BOOL Disp2Acce();  //由位移计算加速度

private:
	BOOL DispDiff(int order); //对位移进行微分,order=1得到速度，order=2得到加速度

};



//楼层文件数据F-7
class _SSG_DLLIMPEXP CStoryDataSet
{
public:
	CStoryDataSet()
	{
		nMaxSteps=0;
		fStoryMax = NULL;
	}

	~CStoryDataSet() {Clear();}

	int nItems;			//数据项数，应该等于楼层数+1，包括地基数据
	int nComponents;	//分量数
	CString sTitle;		//标题
	CString pComponentName[Sys_Max_Story_Components];  //分量名称,Read前赋值
	float fMin[Sys_Max_Story_Components],fMax[Sys_Max_Story_Components];  //最大最小值,读入后即赋值
	int nMaxSteps;		//文件中最大时间步数，读入文件时赋值

	//cmliu 2016/2/16 增加每个楼层所有分量的最大值
	float *fStoryMax; // 每个楼层所有分量的最大值，一个分量序列一个分量序列的排,应该是nTotalStory*nComponents数


	CArray<CFieldOneStep*,CFieldOneStep*> aFieldsPtr; //场函数数组，下标为时间步序号，按楼层从高到底排列数据

	CStoryDataSet &operator=(const CStoryDataSet &s)
	{
		if(this==&s) return *this;

		ASSERT(FALSE);

		return *this;
	}

	//方法

	BOOL IsValid(void) {return aFieldsPtr.GetSize()>0?TRUE:FALSE;}

	//得到时间
	float GetDTime(void) 
	{
		if(aFieldsPtr.GetCount()==0) return 0;
		if(aFieldsPtr.GetCount()==1) return aFieldsPtr[0]->GetTime();
		return aFieldsPtr[1]->GetTime()-aFieldsPtr[0]->GetTime();
	}

	int GetStepNumber(){return (int)aFieldsPtr.GetSize();}  //已经读入的时间步
	void Clear();  //清除所有数据，释放所有内存
	void GetMaxMin();  //计算最大最小值点

	//cmliu 2016/2/16 增加每个楼层所有分量的最大值
	void GetStoryMax();
	float *GetStoryMaxPtr(int iComponent);	// 得到某个分量的所有楼层最大值序列   

	//读入全部时刻楼层物理场F-7
	BOOL ReadBinStoryField_AllStep(const CString &fname); 
	//读入时间步数
	int ReadStep(const CString &fname,float& dtime);
	//读入单个时刻楼层物理场F-7
	BOOL ReadBinStoryField_OneStep(const CString &fname,int iTime); 
};

//层间位移和层间位移角文件数据
class _SSG_DLLIMPEXP CStoryDriftDataSet : public CStoryDataSet
{
public:
	//得到层间位移dx起始地址
	float *GetDXPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(0,nItems);}
	//得到层间位移角ax起始地址
	float *GetAXPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(1,nItems);}
	//得到层间位移dy起始地址
	float *GetDYPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(2,nItems);}
	//得到层间位移角ay起始地址
	float *GetAYPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(3,nItems);}
};

//层间剪力文件数据
class CStoryShearDataSet : public CStoryDataSet
{
public:
	//得到柱子层间剪力Qx起始地址
	float *GetPillarQxPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(0,nItems);}
	//得到斜撑层间剪力Qx起始地址
	float *GetBraceQxPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(2,nItems);}
	//得到剪力墙层间剪力Qx起始地址
	float *GetWallQxPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(4,nItems);}
	//得到楼层总剪力Qx起始地址
	float *GetStoryQxPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(6,nItems);}

	//得到柱子层间剪力Qy起始地址
	float *GetPillarQyPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(7,nItems);}
	//得到斜撑层间剪力Qy起始地址
	float *GetBraceQyPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(9,nItems);}
	//得到剪力墙层间剪力Qy起始地址
	float *GetWallQyPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(11,nItems);}
	//得到楼层总剪力Qy起始地址
	float *GetStoryQyPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(13,nItems);}
};



