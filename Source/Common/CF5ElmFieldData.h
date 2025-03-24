#pragma once
#include "..\Common\PostData.h"

//F-5格式的一个单元块
class _SSG_DLLIMPEXP CF5ElemBlock
{
public:
	CF5ElemBlock(void) 
	{
		memset(pInfo,0,44);
		pColName=NULL;
		pElmID=NULL;
		pIndex=NULL;
	}

	~CF5ElemBlock(void) 
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
			int		nElm;		//单元数,		  若iOffset为-1，nElm=0
			char	pBlockName[32];    //块名称
		};
		char pInfo[44];  //块基本信息
	};

	char (*pColName)[16];   //Part4,分量名称数组,长度nCol，固定长度16，不能修改
	int	 *pElmID;			//Part5,单元总体编号集,长度nElm,下标为块内序号

	//由程序形成的数据
	int *pIndex; //单元在数据文件中的总体序号(所有块统一编号),长度nElm,下标为块内序号

	CF5ElemBlock &operator=(const CF5ElemBlock &blk)
	{
		if(this==&blk) return *this;

		Clear();

		memcpy(pInfo,blk.pInfo,sizeof(pInfo));

		pColName=new char[nCol][16];
		pElmID=new int[nElm];
		if(!pColName || !pElmID)
		{
			Clear();
			return *this;
		}
		memcpy(pColName,blk.pColName,nCol*16*sizeof(char));
		memcpy(pElmID,blk.pElmID,nElm*sizeof(int));
		if(blk.pIndex)
		{
			pIndex=new int[nElm];
			memcpy(pIndex,blk.pIndex,nElm*sizeof(int));
		}

		return *this;
	}

	void Clear(void)
	{
		delete[] pColName;
		delete[] pElmID;
		if(pIndex)delete[] pIndex;

		memset(pInfo,0,sizeof(pInfo));
		pColName=NULL;
		pElmID=NULL;
		pIndex=NULL;
	}

	BOOL ReadInfo(const CFile &fin);  //读pInfo，part3
	BOOL ReadColName(const CFile &fin); //创建并读pColName，part4
	BOOL ReadElmID(const CFile &fin); //创建并读pElmID，part5
	int CreateIndex(int iStart); //创建pIndex，iStart为起始编号，返回下一块的开始编号，即前面所有块的累计单元数量

};

//F-5文件头
class _SSG_DLLIMPEXP CF5Header
{
public:
	CF5Header(void){Clear();}
	~CF5Header(void){;}

	struct F5_PART1  //P1块的数据
	{
		int     flag;             //标识输出类型,  保留
		char	title[256];		//标题
		float	dtime;			 //显式计算步长,	  
		int		dsteps;		     //相邻时刻所间隔的步数,
		int		ntimes;		     //输出时刻的数量,  
		int     type_num;        //单元分类数,目前可包括：两节点梁单元、三节点三角形单元、四节点四边形单元
		int		blk_size;	     //单个时刻各块数据长度之和,
	} FileInfo; 

	//P2块的数据，单元数为0时表示文件中不存在该类单元
	struct F5_ELEMINFO
	{
		int elm_type;  //单元分类标识，0-两节点梁单元，1-三节点壳单元，2-四节点壳单元
		int blk_num;   //该类单元分块数
		int elm_sum;   //该类单元数
	} ElemInfo[3];  //目前最多三类单元,处于通用性考虑，三类单元顺序不限制，每种单元只能有一类
	typedef F5_ELEMINFO F5_PART2;

	//以下为根据ElemInfo计算得到的冗余数据
	int		blk_num1;	     //文件的梁单元分块数,	  blk_num1=vBeam.size()
	int		blk_num2;	     //文件的三角形壳单元分块数,	  blk_num2=vShell.size()
	int		blk_num3;	     //文件的四边形壳单元分块数,	  blk_num3=vQuad.size()
	int		Beam_sum;	     //梁单元总数
	int		Tri_sum;	     //三角形壳单元总数
	int		Quad_sum;	     //四边形壳单元总数

	//float GetTime(int istep) {return (istep+1)*FileInfo.dtime*FileInfo.dsteps;}
	float GetTime(int istep) {return istep*FileInfo.dtime*FileInfo.dsteps;}		//乔保娟 2018.4.28

	F5_ELEMINFO *GetBeamTypeBlock()
	{
		for (int i=0;i<FileInfo.type_num;i++)
		{
			if(ElemInfo[i].elm_type==0) return &(ElemInfo[i]);
		}
		return NULL;
	}

	F5_ELEMINFO *GetTriTypeBlock()
	{
		for (int i=0;i<FileInfo.type_num;i++)
		{
			if(ElemInfo[i].elm_type==1) return &(ElemInfo[i]);
		}
		return NULL;
	}

	F5_ELEMINFO *GetQuadTypeBlock()
	{
		for (int i=0;i<FileInfo.type_num;i++)
		{
			if(ElemInfo[i].elm_type==2) return &(ElemInfo[i]);
		}
		return NULL;
	}

	int GetFirstBeamBlockIndex(void) //得到第一个梁单元块的块编号，不存在则返回-1
	{
		int count=0;
		for (int i=0;i<FileInfo.type_num;i++)
		{
			if(ElemInfo[i].elm_type==0) return count;
			count+=ElemInfo[i].blk_num;
		}
		return -1;
	};
	int GetFirstTriBlock(void)  //得到第一个三角形壳单元块的块编号，不存在则返回-1
	{
		int count=0;
		for (int i=0;i<FileInfo.type_num;i++)
		{
			if(ElemInfo[i].elm_type==1) return count;
			count+=ElemInfo[i].blk_num;
		}
		return -1;
	};
	int GetFirstQuadBlock(void) //得到第一个四边形壳单元块的块编号，不存在则返回-1
	{
		int count=0;
		for (int i=0;i<FileInfo.type_num;i++)
		{
			if(ElemInfo[i].elm_type==2) return count;
			count+=ElemInfo[i].blk_num;
		}
		return -1;
	};

	int GetElemTypeNum(void) {return blk_num1+blk_num2+blk_num3;}

	void Clear(void) 
	{
		Beam_sum=Tri_sum=Quad_sum=0;
		blk_num1=blk_num2=blk_num3=0;
		for(int i=0;i<sizeof(ElemInfo)/sizeof(F5_ELEMINFO);i++)
		{
			ElemInfo[i].elm_type=-1;
			ElemInfo[i].blk_num=0;
			ElemInfo[i].elm_sum=0;
		}
	}
	bool  CheckEnvelope(CF5Header  hdrTmp);

	void InsertNewCol(char (*pInsertColName)[16], int nInsert,CF5ElemBlock *&pblock, int iBlock);

	CF5Header &operator=(const CF5Header &hdr)
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

		for(int i=0;i<sizeof(ElemInfo)/sizeof(F5_ELEMINFO);i++)
		{
			ElemInfo[i].elm_type =hdr.ElemInfo[i].elm_type;
			ElemInfo[i].blk_num  =hdr.ElemInfo[i].blk_num;
			ElemInfo[i].elm_sum =hdr.ElemInfo[i].elm_sum;
		}

		Beam_sum=hdr.Beam_sum;
		Tri_sum=hdr.Tri_sum;
		Quad_sum=hdr.Quad_sum;
		blk_num1=hdr.blk_num1;
		blk_num2=hdr.blk_num2;
		blk_num3=hdr.blk_num3;

		return *this;
	}
};


//物理场的时间历程
class _SSG_DLLIMPEXP CElmFieldOneComponent
{
public:
	CElmFieldOneComponent()
		: sFilePath(L"")
		, sTitle(L"")
		, sGroupName(L"")
		, nMaxSteps(0)
		, iStartStep(0)
		, nBeam(0)
		, nTriAngle(0)
		, nQuad(0)
		, iComponent(0)
		, nBlock(0)
		, pBlockCol(NULL)
		, fMin(0)
		, fMax(0)
		, iMinStep(0)
		, iMaxStep(0)
		, sComponentName(L"")
		, pBeamIndex(NULL)
		, pTriIndex(NULL)
		, pQuadIndex(NULL)
		, ppData(NULL)
		, pTime(NULL)
		, pEnvelope()
		, nBeamIndex(0)
		, nTriIndex(0)
		, nQuadInex(0)
	{
	}

	~CElmFieldOneComponent() 
	{
		Clear();

		nBlock=0;
		delete[] pBlockCol;	
		pBlockCol=NULL;
	}
	
	void Clear(void)
	{
		if(pBeamIndex)
			delete[] pBeamIndex; 

		if(pTriIndex)
			delete[] pTriIndex;

		if(pQuadIndex) 
			delete[] pQuadIndex;

		pBeamIndex=NULL;
		pTriIndex=NULL;
		pQuadIndex=NULL;

		if (ppData)
		{
			for (int i = 0; i < nMaxSteps; i++)
				delete[] ppData[i];

			delete[] ppData;
			ppData = NULL;
		}

		for (int i = 0; i < sizeof(pEnvelope) / sizeof(float*); i++)
		{
			delete pEnvelope[i];
			pEnvelope[i] = NULL;
		}

		delete[] pTime;
		pTime = NULL;
		sFilePath = L"";
		nMaxSteps = 0;
		sComponentName = L"";
	}

	CString sFilePath;  //文件名
	CString sTitle;  //文件标题
	CString sGroupName; //分组名称
	int nMaxSteps;  //读入的时间步数
	int iStartStep; //读入的开始时间步序号

	int nBeam;  //实际读取的梁单元数，是全体梁单元的子集
	int nTriAngle; //实际读取的三角形壳单元数，是全体三角形壳单元的子集
	int nQuad; //实际读取的四边形壳单元数，是全体四边形壳单元的子集

	int iComponent;  //分量号，若存在多种类型分量，只保存被选择的第一种类型的分量号，此数据仅供用户参考，无实际意义

	//这两个变量在切换新文件时需要重新初始化，切换变量时不需要初始化
	int nBlock;  //分块数
	int *pBlockCol;  //每个分块的分量在所有分量中的序号，长度为分块数，读文件时就是根据此变量确定的分量号进行读取

	//整个时程数据中最大最小值及对应的时刻,读入后即赋值
	float fMin,fMax;
	int iMinStep,iMaxStep;

	CString sComponentName;  //分量名称，若存在多种类型分量，只保存被选择的第一种类型的分量名称，此数据仅供用户参考，无实际意义

	int *pBeamIndex;  //梁单元整体编号到局部编号的索引，值为-1时表示此单元无数据
	int *pTriIndex;  //四边形壳单元整体编号到局部编号的索引，值为-1时表示此单元无数据
	int *pQuadIndex;  //四边形壳单元整体编号到局部编号的索引，值为-1时表示此单元无数据
	int nBeamIndex;	//全局梁数
	int nTriIndex;	//全局三角形数
	int nQuadInex;  //全局四边形数  

	float **ppData;  //物理量指针数组,每一个指针成员对应一个时刻的物理场,每一时刻包含nBeam+nTriAngle+nQuad个单元的一个分量数据，先存梁数据，然后三角形数据，最后是四边形壳数据
	float *pTime;  //时间数组,每一个指针成员对应一个时刻，单位：秒

	float *pEnvelope[2]; //包络数据，[0]-最大值,[1]-最小值

	CElmFieldOneComponent &operator=(const CElmFieldOneComponent &blk)
	{
		if(this==&blk) 
			return *this;

		ASSERT(FALSE);

		return *this;
	}

	BOOL IsValid(void)const {return nMaxSteps>0?TRUE:FALSE;}

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
	//得到ppData中第iStep时刻第idm三角形壳单元的数据，是全局单元号
	float GetTriData(int iStep,int idm) 
	{
		if(!ppData) return 0;
		if(!pTriIndex) return 0;
		int index=pTriIndex[idm];
		if(index<0) return 0;
		return (ppData[iStep])[index];
	}

	//得到ppData中第iStep时刻第idm四边形壳单元的数据，是全局单元号
	float GetQuadData(int iStep,int idm) 
	{
		if(!ppData) return 0;
		if(!pQuadIndex) return 0;
		int index=pQuadIndex[idm];
		if(index<0) return 0;
		return (ppData[iStep])[index];
	}

	//修改ppData中第iStep时刻第idm梁单元的数据，是全局单元号
	bool SetBeamData(int iStep,int idm,float fVal) 
	{
		if(!ppData) return false;
		if(!pBeamIndex) return false;
		int index=pBeamIndex[idm];
		if(index<0) return false;
		(ppData[iStep])[index]=fVal;
		return true;
	} 
	//修改ppData中第iStep时刻第idm三角形壳单元的数据，是全局单元号
	bool SetTriData(int iStep,int idm,float fVal) 
	{
		if(!ppData) return false;
		if(!pTriIndex) return false;
		int index=pTriIndex[idm];
		if(index<0) return false;
		(ppData[iStep])[index]=fVal;
		return true;
	}
	//修改ppData中第iStep时刻第idm四边形壳单元的数据，是全局单元号
	bool SetQuadData(int iStep,int idm,float fVal) 
	{
		if(!ppData) return false;
		if(!pQuadIndex) return false;
		int index=pQuadIndex[idm];
		if(index<0) return false;
		(ppData[iStep])[index]=fVal;
		return true;
	}
	//得到第idm梁单元的包络数据，idm是全局单元号,direct=0最大正值,1-最大负值绝对值，2-最大绝对值
	float GetBeamEnvelope(int direct,int idm) 
	{
		if(!pEnvelope[0]) return 0;
		if(!pEnvelope[1]) return 0;
		if(!pBeamIndex) return 0;
		int index=pBeamIndex[idm];
		if(index<0) return 0;
		switch(direct)
		{
		case 0:
			return abs((pEnvelope[0])[index]);
		case 1:
			return abs((pEnvelope[1])[index]);
		case 2:
			return max(abs((pEnvelope[0])[index]),abs((pEnvelope[1])[index]));
		}
		return 0;
	}

	float GetTriEnvelope(int direct,int idm) 
	{
		if(!pEnvelope[0]) return 0;
		if(!pEnvelope[1]) return 0;
		if(!pTriIndex) return 0;
		int index=pTriIndex[idm];
		if(index<0) return 0;
		switch(direct)
		{
		case 0:
			return abs((pEnvelope[0])[index]);
		case 1:
			return abs((pEnvelope[1])[index]);
		case 2:
			return max(abs((pEnvelope[0])[index]),abs((pEnvelope[1])[index]));
		}
		return 0;
	}

	float GetQuadEnvelope(int direct,int idm) 
	{
		if(!pEnvelope[0]) return 0;
		if(!pEnvelope[1]) return 0;
		if(!pQuadIndex) return 0;
		int index=pQuadIndex[idm];
		if(index<0) return 0;
		switch(direct)
		{
		case 0:
			return abs((pEnvelope[0])[index]);
		case 1:
			return abs((pEnvelope[1])[index]);
		case 2:
			return max(abs((pEnvelope[0])[index]),abs((pEnvelope[1])[index]));
		}
		return 0;
	}

	

	//读入所有时刻的二进制场函数的一个分量，F-5格式，返回分量号，-1失败
	BOOL ReadBinElmField_AllStep(const CString &fname,CF5Header hdr,CF5ElemBlock *pblock,int iStartStep0,int iSkip=1); 

	void GetMaxMin();
	bool CalInterDensity();	//计算应变能密度

};

//某一时刻某一块的单元数据的所有分量
class _SSG_DLLIMPEXP CElmFieldOneStepOneBlock
{
public:
	CElmFieldOneStepOneBlock(void) {nElms=0;nMaxSteps=0;pElmID=NULL;pColName=NULL;}
	~CElmFieldOneStepOneBlock(void) {Clear();}

	CString sFilePath;  //文件名
	CString sTitle;  //文件标题
	CString sBlockName; //分块名称
//CString sGroupName; //分组名称
	int nMaxSteps;  //文件中最大时间步，用于切换时间步，读入第一个块时可以得到此数据

	int iStep; //时间步
	int iBlock; //分块号
	int iElmType; //单元类型，0--梁，1--三角形壳，2--四边形壳

	int nElms; //单元数
	int nComponents; //分量数
	CString *pColName; //分量名称
	int *pElmID;  //单元ID数组，下标=文件中数据序号


	CFieldOneStep cData;  //数据


	//得到时间分辨率，秒
	float GetDTime(void) 
	{
		if(nElms==0) return 0;
		return cData.GetTime();
	}

	CElmFieldOneStepOneBlock &operator=(const CElmFieldOneStepOneBlock &blk)
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
		nElms=0;

		delete[] pElmID;
		pElmID=NULL;
		delete[] pColName;
		pColName=NULL;
		cData.Clear();

	}

	BOOL IsValid(void) {return nElms>0?TRUE:FALSE;}
	BOOL ReadOneStepOneBlock(const CString &fname,CF5Header hdr,CF5ElemBlock *pblock,int istep,int iblock);
	BOOL WriteOneStepOneBlock(const CString &fname,CF5Header hdr,CF5ElemBlock *pblock,int istep,int iblock);
};


//读入F-5文件头及分块基本信息(P1~P4)，不包括单元集，创建相应动态数组，返回分量号，-1失败
extern "C" _SSG_DLLIMPEXP BOOL ReadF5Header(const CString &fname,CF5Header  &hdr,CF5ElemBlock *&pblock);

//写入文件头
extern "C" _SSG_DLLIMPEXP BOOL WriteF5Header(const CString &fname,CF5Header hdr,CF5ElemBlock *pblock);


