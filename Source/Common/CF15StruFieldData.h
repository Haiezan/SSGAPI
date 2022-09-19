#pragma once
#include "..\Common\data.h"
#include "..\Common\PostData.h"


//F-15文件头
class _SSG_DLLIMPEXP CF15Header
{
public:
	CF15Header(void){Clear();}
	~CF15Header(void){;}

	struct F15_PART1  //P1块的数据
	{
		int     flag;             //标识输出类型,  保留
		char	title[256];		//标题
		float	dtime;			 //显式计算步长,	  
		int		dsteps;		     //相邻时刻所间隔的步数,
		int		ntimes;		     //输出时刻的数量,  
		int     type_num;        //构件分类数,目前可包括：一维构件、二维构件，选择集中可能没有某种
		int		blk_size;	     //单个时刻各块数据长度之和,
	} FileInfo; 

	float GetTime(int istep) {return istep*FileInfo.dtime*FileInfo.dsteps;} //乔保娟 2018.5.2 

	void Clear(void) 
	{
	}

	 bool operator!=(const CF15Header &hdr)
	{
		//FileInfo 比较
		//标题不同无法取包络
		if(0!=strcmp(FileInfo.title,hdr.FileInfo.title)) return true;
		//最大时长的步数和时间步长不需要相同
		//单元类型
		if(FileInfo.type_num!=hdr.FileInfo.type_num)return true;
		//数据
		if(FileInfo.blk_size!=hdr.FileInfo.blk_size)return true;
		return false;
	}
	CF15Header &operator=(const CF15Header &hdr)
	{
		if(this==&hdr) return *this;

		Clear();

		FileInfo.flag =hdr.FileInfo.flag;
		strcpy_s(FileInfo.title,hdr.FileInfo.title);
		FileInfo.dtime=hdr.FileInfo.dtime;
		FileInfo.dsteps=hdr.FileInfo.dsteps;
		FileInfo.ntimes=hdr.FileInfo.ntimes;
		FileInfo.type_num=hdr.FileInfo.type_num;
		FileInfo.blk_size =hdr.FileInfo.blk_size;
		
		return *this;
	}
};

//F-15格式的一个单元块
class _SSG_DLLIMPEXP CF15StruBlock  //与CF5ElemBlock相同
{
public:
	CF15StruBlock(void) 
	{
		memset(pInfo,0,44);
		pColName=NULL;
		pStruID=NULL;
		pIndex=NULL;
	}

	~CF15StruBlock(void) 
	{
		Clear();
	}


	//文件数据
	union
	{
		struct
		{
			int		iOffset;	//各块起始位置,	  若设为-1，表示该块数据无效。各块起始位置，从文件头开始算起。
			int		nCol;		//分量数,		  若iOffset为-1，n=0
			int		nStru;		//构件数,		  若iOffset为-1，nElm=0
			char	pBlockName[32];    //块名称
		};
		char pInfo[44];  //块基本信息
	};

	char (*pColName)[16];   //Part4,分量名称数组,长度nCol，固定长度16，不能修改
	int	 *pStruID;			//Part5,构件总体编号集,长度nElm,下标为块内序号

	//由程序形成的数据
	int *pIndex; //构件在数据文件中的总体序号(所有块统一编号),长度nElm,下标为块内序号

	CF15StruBlock &operator=(const CF15StruBlock &blk)
	{
		if(this==&blk) return *this;

		Clear();

		memcpy(pInfo,blk.pInfo,sizeof(pInfo));

		pColName=new char[nCol][16];
		pStruID=new int[nStru];
		if(!pColName || !pStruID)
		{
			Clear();
			return *this;
		}

		memcpy(pColName,blk.pColName,nCol*16*sizeof(char));
		memcpy(pStruID,blk.pStruID,nStru*sizeof(int));
		if (blk.pIndex)
		{
			pIndex=new int[nStru];
			memcpy(pIndex,blk.pIndex,nStru*sizeof(int));
		}

		return *this;
	}

	void Clear(void)
	{
		delete[] pColName;
		delete[] pStruID;
		if(pIndex)delete[] pIndex;

		memset(pInfo,0,sizeof(pInfo));
		pColName=NULL;
		pStruID=NULL;
		pIndex=NULL;
	}

	BOOL ReadInfo(const CFile &fin);  //读pInfo，part3
	BOOL ReadColName(const CFile &fin); //创建并读pColName，part4
	BOOL ReadStruID(const CFile &fin); //创建并读pStruID，part5
	int CreateIndex(int iStart); //创建pIndex，iStart为起始编号，返回下一块的开始编号，即前面所有块的累计单元数量
};
//某一时刻某一块的单元数据的所有分量
class _SSG_DLLIMPEXP CStruFieldOneStepOneBlock
{
public:
	CStruFieldOneStepOneBlock(void) {nStrus=0;nMaxSteps=0;pStruID=NULL;pColName=NULL;}
	~CStruFieldOneStepOneBlock(void) {Clear();}

	CString sFilePath;  //文件名
	CString sTitle;  //文件标题
	CString sBlockName; //分块名称
	//CString sGroupName; //分组名称
	int nMaxSteps;  //文件中最大时间步，用于切换时间步，读入第一个块时可以得到此数据

	int iStep; //时间步
	int iStruType; //构件类型，0--一维构件，1--二维构件

 	int nStrus; //单元数
	int nComponents; //分量数
	CString *pColName; //分量名称
	int *pStruID;  //单元ID数组，下标=文件中数据序号

	CFieldOneStep cData;  //数据

	//得到时间分辨率，秒
	float GetDTime(void) 
	{
		if(nStrus==0) return 0;
		return cData.GetTime();
	}

	CStruFieldOneStepOneBlock &operator=(const CStruFieldOneStepOneBlock &blk)
	{
		if(this==&blk) return *this;

		ASSERT(FALSE);

		return *this;
	}
	void Clear(void)
	{
		sFilePath=L""; 
		sTitle=L""; 
		sBlockName=L"";
		//sGroupName=L"";
		nMaxSteps=0;
 		nStrus=0;

		delete[] pStruID;
		pStruID=NULL;
 		delete[] pColName;
 		pColName=NULL;
		cData.Clear();
	}

	BOOL IsValid(void) {return nStrus>0?TRUE:FALSE;}
	BOOL ReadOneStepOneType(const CString &fname,CF15Header hdr,CF15StruBlock *pblock,int istep,int iblock);
	BOOL WriteOneStepOneType(const CString &fname,CF15Header hdr,CF15StruBlock *pblock,int istep,int iblock);

};


//物理场的时间历程
class _SSG_DLLIMPEXP CStruFieldOneComponent
{
public:
	CStruFieldOneComponent()
	{
		pBeamIndex=NULL;
		pPlateIndex=NULL;
		ppData=NULL;
		pTime=NULL;
		nMaxSteps=0;
		nBlock=0;
		iStartStep=0;
	}

	~CStruFieldOneComponent() 
	{
		Clear();
		nBlock=0;
	}

	CString sFilePath;  //文件名
	CString sTitle;  //文件标题
	CString sGroupName; //分组名称
	int nMaxSteps;  //读入的时间步数
	int iStartStep; //读入的开始时间步序号


	int nBeam;  //实际读取的梁构件数，是全体梁构件的子集
	int nPlate; //实际读取的二维构件数，是全体二维构件的子集

	int iComponent;  //分量号，若存在多种类型分量，只保存被选择的第一种类型的分量号，此数据仅供用户参考，无实际意义

	//这两个变量在切换新文件时需要重新初始化，切换变量时不需要初始化
	int nBlock;  //分块数

	CString sComponentName;  //分量名称，若存在多种类型分量，只保存被选择的第一种类型的分量名称，此数据仅供用户参考，无实际意义

	int *pBeamIndex;  //梁整体编号到局部编号的索引，值为-1时表示此单元无数据
	int *pPlateIndex;  //二维构件整体编号到局部编号的索引，值为-1时表示此单元无数据

	float **ppData;  //物理量指针数组,每一个指针成员对应一个时刻的物理场,每一时刻包含nBeam+nPlate个构件的一个分量数据，先存梁数据，然后二维构件数据
	float *pTime;  //时间数组,每一个指针成员对应一个时刻，单位：秒

	CStruFieldOneComponent &operator=(const CStruFieldOneComponent &blk)
	{
		if(this==&blk) return *this;

		ASSERT(FALSE);

		return *this;
	}

	BOOL IsValid(void) {return nMaxSteps>0?TRUE:FALSE;}

	//得到时间分辨率,单位：秒，假设时间步是等间隔的，否则不正确
	float GetDTime(void) 
	{
		if(nMaxSteps==0) return 0;
		if(nMaxSteps==1) return pTime[0];
		return pTime[1]-pTime[0];
	}

	//返回ppData中第iStep时刻的数据地址
	float *GetStepPtr(int iStep) {return ppData[iStep];}  
	//得到ppData中第iStep时刻第idm梁单元的数据，是全局单元号
	float GetBeamData(int iStep,int idm) 
	{
		if(!ppData) return 0;
		if(!pBeamIndex) return 0;
		int index=pBeamIndex[idm];
		if(index<0) return 0;
		return (ppData[iStep])[index];
	} 

	//得到ppData中第iStep时刻第idm四边形壳单元的数据，是全局单元号
	float GetPlateData(int iStep,int idm) 
	{
		if(!ppData) return 0;
		if(!pPlateIndex) return 0;
		int index=pPlateIndex[idm];
		if(index<0) return 0;
		return (ppData[iStep])[index];
	}

	
	void Clear(void)
	{
		if(pBeamIndex)
		{
			delete[] pBeamIndex; 
			pBeamIndex=NULL;
		}
		if(pPlateIndex)
		{
			delete[] pPlateIndex;
			pPlateIndex=NULL;
		}
		if(ppData)
		{
			for(int i=0;i<nMaxSteps;i++) delete[] ppData[i];
			delete[] ppData;
			ppData=NULL;
		}
				
		delete[] pTime;
		pTime=NULL;
		sFilePath=L"";
		nMaxSteps=0;
		sComponentName=L"";
	}

	//读入所有时刻的二进制场函数的一个分量，F-5格式，返回分量号，-1失败
	BOOL ReadBinStruField_AllStep(const CString &fname,CF15Header hdr,CF15StruBlock *pblock,int iComponent); 

};

//读入F-5文件头及分块基本信息(P1~P4)，不包括单元集，创建相应动态数组，返回分量号，-1失败
extern "C" _SSG_DLLIMPEXP BOOL ReadF15Header(const CString &fname,CF15Header  &hdr,CF15StruBlock *&pblock);

//写入文件头
extern "C" _SSG_DLLIMPEXP BOOL WriteF15Header(const CString &fname,CF15Header hdr,CF15StruBlock *pblock);


