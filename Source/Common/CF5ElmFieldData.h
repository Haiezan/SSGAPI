#pragma once
#include "..\Common\PostData.h"

//F-5��ʽ��һ����Ԫ��
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


	//�ļ�����
	union
	{
		struct
		{
			int		iOffset;	//������ʼλ��,	  ����Ϊ-1����ʾ�ÿ�������Ч��������ʼλ�ã����ļ�ͷ��ʼ����
			int		nCol;		//������,		  ��iOffsetΪ-1��n=0
			int		nElm;		//��Ԫ��,		  ��iOffsetΪ-1��nElm=0
			char	pBlockName[32];    //������
		};
		char pInfo[44];  //�������Ϣ
	};

	char (*pColName)[16];   //Part4,������������,����nCol���̶�����16�������޸�
	int	 *pElmID;			//Part5,��Ԫ�����ż�,����nElm,�±�Ϊ�������

	//�ɳ����γɵ�����
	int *pIndex; //��Ԫ�������ļ��е��������(���п�ͳһ���),����nElm,�±�Ϊ�������

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

	BOOL ReadInfo(const CFile &fin);  //��pInfo��part3
	BOOL ReadColName(const CFile &fin); //��������pColName��part4
	BOOL ReadElmID(const CFile &fin); //��������pElmID��part5
	int CreateIndex(int iStart); //����pIndex��iStartΪ��ʼ��ţ�������һ��Ŀ�ʼ��ţ���ǰ�����п���ۼƵ�Ԫ����

};

//F-5�ļ�ͷ
class _SSG_DLLIMPEXP CF5Header
{
public:
	CF5Header(void){Clear();}
	~CF5Header(void){;}

	struct F5_PART1  //P1�������
	{
		int     flag;             //��ʶ�������,  ����
		char	title[256];		//����
		float	dtime;			 //��ʽ���㲽��,	  
		int		dsteps;		     //����ʱ��������Ĳ���,
		int		ntimes;		     //���ʱ�̵�����,  
		int     type_num;        //��Ԫ������,Ŀǰ�ɰ��������ڵ�����Ԫ�����ڵ������ε�Ԫ���Ľڵ��ı��ε�Ԫ
		int		blk_size;	     //����ʱ�̸������ݳ���֮��,
	} FileInfo; 

	//P2������ݣ���Ԫ��Ϊ0ʱ��ʾ�ļ��в����ڸ��൥Ԫ
	struct F5_ELEMINFO
	{
		int elm_type;  //��Ԫ�����ʶ��0-���ڵ�����Ԫ��1-���ڵ�ǵ�Ԫ��2-�Ľڵ�ǵ�Ԫ
		int blk_num;   //���൥Ԫ�ֿ���
		int elm_sum;   //���൥Ԫ��
	} ElemInfo[3];  //Ŀǰ������൥Ԫ,����ͨ���Կ��ǣ����൥Ԫ˳�����ƣ�ÿ�ֵ�Ԫֻ����һ��
	typedef F5_ELEMINFO F5_PART2;

	//����Ϊ����ElemInfo����õ�����������
	int		blk_num1;	     //�ļ�������Ԫ�ֿ���,	  blk_num1=vBeam.size()
	int		blk_num2;	     //�ļ��������οǵ�Ԫ�ֿ���,	  blk_num2=vShell.size()
	int		blk_num3;	     //�ļ����ı��οǵ�Ԫ�ֿ���,	  blk_num3=vQuad.size()
	int		Beam_sum;	     //����Ԫ����
	int		Tri_sum;	     //�����οǵ�Ԫ����
	int		Quad_sum;	     //�ı��οǵ�Ԫ����

	//float GetTime(int istep) {return (istep+1)*FileInfo.dtime*FileInfo.dsteps;}
	float GetTime(int istep) {return istep*FileInfo.dtime*FileInfo.dsteps;}		//�Ǳ��� 2018.4.28

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

	int GetFirstBeamBlockIndex(void) //�õ���һ������Ԫ��Ŀ��ţ��������򷵻�-1
	{
		int count=0;
		for (int i=0;i<FileInfo.type_num;i++)
		{
			if(ElemInfo[i].elm_type==0) return count;
			count+=ElemInfo[i].blk_num;
		}
		return -1;
	};
	int GetFirstTriBlock(void)  //�õ���һ�������οǵ�Ԫ��Ŀ��ţ��������򷵻�-1
	{
		int count=0;
		for (int i=0;i<FileInfo.type_num;i++)
		{
			if(ElemInfo[i].elm_type==1) return count;
			count+=ElemInfo[i].blk_num;
		}
		return -1;
	};
	int GetFirstQuadBlock(void) //�õ���һ���ı��οǵ�Ԫ��Ŀ��ţ��������򷵻�-1
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


//������ʱ������
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

	CString sFilePath;  //�ļ���
	CString sTitle;  //�ļ�����
	CString sGroupName; //��������
	int nMaxSteps;  //�����ʱ�䲽��
	int iStartStep; //����Ŀ�ʼʱ�䲽���

	int nBeam;  //ʵ�ʶ�ȡ������Ԫ������ȫ������Ԫ���Ӽ�
	int nTriAngle; //ʵ�ʶ�ȡ�������οǵ�Ԫ������ȫ�������οǵ�Ԫ���Ӽ�
	int nQuad; //ʵ�ʶ�ȡ���ı��οǵ�Ԫ������ȫ���ı��οǵ�Ԫ���Ӽ�

	int iComponent;  //�����ţ������ڶ������ͷ�����ֻ���汻ѡ��ĵ�һ�����͵ķ����ţ������ݽ����û��ο�����ʵ������

	//�������������л����ļ�ʱ��Ҫ���³�ʼ�����л�����ʱ����Ҫ��ʼ��
	int nBlock;  //�ֿ���
	int *pBlockCol;  //ÿ���ֿ�ķ��������з����е���ţ�����Ϊ�ֿ��������ļ�ʱ���Ǹ��ݴ˱���ȷ���ķ����Ž��ж�ȡ

	//����ʱ�������������Сֵ����Ӧ��ʱ��,����󼴸�ֵ
	float fMin,fMax;
	int iMinStep,iMaxStep;

	CString sComponentName;  //�������ƣ������ڶ������ͷ�����ֻ���汻ѡ��ĵ�һ�����͵ķ������ƣ������ݽ����û��ο�����ʵ������

	int *pBeamIndex;  //����Ԫ�����ŵ��ֲ���ŵ�������ֵΪ-1ʱ��ʾ�˵�Ԫ������
	int *pTriIndex;  //�ı��οǵ�Ԫ�����ŵ��ֲ���ŵ�������ֵΪ-1ʱ��ʾ�˵�Ԫ������
	int *pQuadIndex;  //�ı��οǵ�Ԫ�����ŵ��ֲ���ŵ�������ֵΪ-1ʱ��ʾ�˵�Ԫ������
	int nBeamIndex;	//ȫ������
	int nTriIndex;	//ȫ����������
	int nQuadInex;  //ȫ���ı�����  

	float **ppData;  //������ָ������,ÿһ��ָ���Ա��Ӧһ��ʱ�̵�����,ÿһʱ�̰���nBeam+nTriAngle+nQuad����Ԫ��һ���������ݣ��ȴ������ݣ�Ȼ�����������ݣ�������ı��ο�����
	float *pTime;  //ʱ������,ÿһ��ָ���Ա��Ӧһ��ʱ�̣���λ����

	float *pEnvelope[2]; //�������ݣ�[0]-���ֵ,[1]-��Сֵ

	CElmFieldOneComponent &operator=(const CElmFieldOneComponent &blk)
	{
		if(this==&blk) 
			return *this;

		ASSERT(FALSE);

		return *this;
	}

	BOOL IsValid(void)const {return nMaxSteps>0?TRUE:FALSE;}

	//�õ�ʱ��ֱ���,��λ���룬����ʱ�䲽�ǵȼ���ģ�������ȷ
	float GetDTime(void) 
	{
		if(nMaxSteps==0) return 0;
		if(nMaxSteps==1) return pTime[0];
		return pTime[1]-pTime[0];
	}

	//����ppData�е�iStepʱ�̵����ݵ�ַ
	float *GetStepPtr(int iStep) {return ppData[iStep];}  
	//�õ�ppData�е�iStepʱ�̵�idm����Ԫ�����ݣ���ȫ�ֵ�Ԫ��
	float GetBeamData(int iStep,int idm) 
	{
		if(!ppData) return 0;
		if(!pBeamIndex) return 0;
		int index=pBeamIndex[idm];
		if(index<0) return 0;
		return (ppData[iStep])[index];
	} 
	//�õ�ppData�е�iStepʱ�̵�idm�����οǵ�Ԫ�����ݣ���ȫ�ֵ�Ԫ��
	float GetTriData(int iStep,int idm) 
	{
		if(!ppData) return 0;
		if(!pTriIndex) return 0;
		int index=pTriIndex[idm];
		if(index<0) return 0;
		return (ppData[iStep])[index];
	}

	//�õ�ppData�е�iStepʱ�̵�idm�ı��οǵ�Ԫ�����ݣ���ȫ�ֵ�Ԫ��
	float GetQuadData(int iStep,int idm) 
	{
		if(!ppData) return 0;
		if(!pQuadIndex) return 0;
		int index=pQuadIndex[idm];
		if(index<0) return 0;
		return (ppData[iStep])[index];
	}

	//�޸�ppData�е�iStepʱ�̵�idm����Ԫ�����ݣ���ȫ�ֵ�Ԫ��
	bool SetBeamData(int iStep,int idm,float fVal) 
	{
		if(!ppData) return false;
		if(!pBeamIndex) return false;
		int index=pBeamIndex[idm];
		if(index<0) return false;
		(ppData[iStep])[index]=fVal;
		return true;
	} 
	//�޸�ppData�е�iStepʱ�̵�idm�����οǵ�Ԫ�����ݣ���ȫ�ֵ�Ԫ��
	bool SetTriData(int iStep,int idm,float fVal) 
	{
		if(!ppData) return false;
		if(!pTriIndex) return false;
		int index=pTriIndex[idm];
		if(index<0) return false;
		(ppData[iStep])[index]=fVal;
		return true;
	}
	//�޸�ppData�е�iStepʱ�̵�idm�ı��οǵ�Ԫ�����ݣ���ȫ�ֵ�Ԫ��
	bool SetQuadData(int iStep,int idm,float fVal) 
	{
		if(!ppData) return false;
		if(!pQuadIndex) return false;
		int index=pQuadIndex[idm];
		if(index<0) return false;
		(ppData[iStep])[index]=fVal;
		return true;
	}
	//�õ���idm����Ԫ�İ������ݣ�idm��ȫ�ֵ�Ԫ��,direct=0�����ֵ,1-���ֵ����ֵ��2-������ֵ
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

	

	//��������ʱ�̵Ķ����Ƴ�������һ��������F-5��ʽ�����ط����ţ�-1ʧ��
	BOOL ReadBinElmField_AllStep(const CString &fname,CF5Header hdr,CF5ElemBlock *pblock,int iStartStep0,int iSkip=1); 

	void GetMaxMin();
	bool CalInterDensity();	//����Ӧ�����ܶ�

};

//ĳһʱ��ĳһ��ĵ�Ԫ���ݵ����з���
class _SSG_DLLIMPEXP CElmFieldOneStepOneBlock
{
public:
	CElmFieldOneStepOneBlock(void) {nElms=0;nMaxSteps=0;pElmID=NULL;pColName=NULL;}
	~CElmFieldOneStepOneBlock(void) {Clear();}

	CString sFilePath;  //�ļ���
	CString sTitle;  //�ļ�����
	CString sBlockName; //�ֿ�����
//CString sGroupName; //��������
	int nMaxSteps;  //�ļ������ʱ�䲽�������л�ʱ�䲽�������һ����ʱ���Եõ�������

	int iStep; //ʱ�䲽
	int iBlock; //�ֿ��
	int iElmType; //��Ԫ���ͣ�0--����1--�����οǣ�2--�ı��ο�

	int nElms; //��Ԫ��
	int nComponents; //������
	CString *pColName; //��������
	int *pElmID;  //��ԪID���飬�±�=�ļ����������


	CFieldOneStep cData;  //����


	//�õ�ʱ��ֱ��ʣ���
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


//����F-5�ļ�ͷ���ֿ������Ϣ(P1~P4)����������Ԫ����������Ӧ��̬���飬���ط����ţ�-1ʧ��
extern "C" _SSG_DLLIMPEXP BOOL ReadF5Header(const CString &fname,CF5Header  &hdr,CF5ElemBlock *&pblock);

//д���ļ�ͷ
extern "C" _SSG_DLLIMPEXP BOOL WriteF5Header(const CString &fname,CF5Header hdr,CF5ElemBlock *pblock);


