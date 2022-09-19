#pragma once
#include "..\Common\data.h"
#include "..\Common\PostData.h"


//F-15�ļ�ͷ
class _SSG_DLLIMPEXP CF15Header
{
public:
	CF15Header(void){Clear();}
	~CF15Header(void){;}

	struct F15_PART1  //P1�������
	{
		int     flag;             //��ʶ�������,  ����
		char	title[256];		//����
		float	dtime;			 //��ʽ���㲽��,	  
		int		dsteps;		     //����ʱ��������Ĳ���,
		int		ntimes;		     //���ʱ�̵�����,  
		int     type_num;        //����������,Ŀǰ�ɰ�����һά��������ά������ѡ���п���û��ĳ��
		int		blk_size;	     //����ʱ�̸������ݳ���֮��,
	} FileInfo; 

	float GetTime(int istep) {return istep*FileInfo.dtime*FileInfo.dsteps;} //�Ǳ��� 2018.5.2 

	void Clear(void) 
	{
	}

	 bool operator!=(const CF15Header &hdr)
	{
		//FileInfo �Ƚ�
		//���ⲻͬ�޷�ȡ����
		if(0!=strcmp(FileInfo.title,hdr.FileInfo.title)) return true;
		//���ʱ���Ĳ�����ʱ�䲽������Ҫ��ͬ
		//��Ԫ����
		if(FileInfo.type_num!=hdr.FileInfo.type_num)return true;
		//����
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

//F-15��ʽ��һ����Ԫ��
class _SSG_DLLIMPEXP CF15StruBlock  //��CF5ElemBlock��ͬ
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


	//�ļ�����
	union
	{
		struct
		{
			int		iOffset;	//������ʼλ��,	  ����Ϊ-1����ʾ�ÿ�������Ч��������ʼλ�ã����ļ�ͷ��ʼ����
			int		nCol;		//������,		  ��iOffsetΪ-1��n=0
			int		nStru;		//������,		  ��iOffsetΪ-1��nElm=0
			char	pBlockName[32];    //������
		};
		char pInfo[44];  //�������Ϣ
	};

	char (*pColName)[16];   //Part4,������������,����nCol���̶�����16�������޸�
	int	 *pStruID;			//Part5,���������ż�,����nElm,�±�Ϊ�������

	//�ɳ����γɵ�����
	int *pIndex; //�����������ļ��е��������(���п�ͳһ���),����nElm,�±�Ϊ�������

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

	BOOL ReadInfo(const CFile &fin);  //��pInfo��part3
	BOOL ReadColName(const CFile &fin); //��������pColName��part4
	BOOL ReadStruID(const CFile &fin); //��������pStruID��part5
	int CreateIndex(int iStart); //����pIndex��iStartΪ��ʼ��ţ�������һ��Ŀ�ʼ��ţ���ǰ�����п���ۼƵ�Ԫ����
};
//ĳһʱ��ĳһ��ĵ�Ԫ���ݵ����з���
class _SSG_DLLIMPEXP CStruFieldOneStepOneBlock
{
public:
	CStruFieldOneStepOneBlock(void) {nStrus=0;nMaxSteps=0;pStruID=NULL;pColName=NULL;}
	~CStruFieldOneStepOneBlock(void) {Clear();}

	CString sFilePath;  //�ļ���
	CString sTitle;  //�ļ�����
	CString sBlockName; //�ֿ�����
	//CString sGroupName; //��������
	int nMaxSteps;  //�ļ������ʱ�䲽�������л�ʱ�䲽�������һ����ʱ���Եõ�������

	int iStep; //ʱ�䲽
	int iStruType; //�������ͣ�0--һά������1--��ά����

 	int nStrus; //��Ԫ��
	int nComponents; //������
	CString *pColName; //��������
	int *pStruID;  //��ԪID���飬�±�=�ļ����������

	CFieldOneStep cData;  //����

	//�õ�ʱ��ֱ��ʣ���
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


//������ʱ������
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

	CString sFilePath;  //�ļ���
	CString sTitle;  //�ļ�����
	CString sGroupName; //��������
	int nMaxSteps;  //�����ʱ�䲽��
	int iStartStep; //����Ŀ�ʼʱ�䲽���


	int nBeam;  //ʵ�ʶ�ȡ��������������ȫ�����������Ӽ�
	int nPlate; //ʵ�ʶ�ȡ�Ķ�ά����������ȫ���ά�������Ӽ�

	int iComponent;  //�����ţ������ڶ������ͷ�����ֻ���汻ѡ��ĵ�һ�����͵ķ����ţ������ݽ����û��ο�����ʵ������

	//�������������л����ļ�ʱ��Ҫ���³�ʼ�����л�����ʱ����Ҫ��ʼ��
	int nBlock;  //�ֿ���

	CString sComponentName;  //�������ƣ������ڶ������ͷ�����ֻ���汻ѡ��ĵ�һ�����͵ķ������ƣ������ݽ����û��ο�����ʵ������

	int *pBeamIndex;  //�������ŵ��ֲ���ŵ�������ֵΪ-1ʱ��ʾ�˵�Ԫ������
	int *pPlateIndex;  //��ά���������ŵ��ֲ���ŵ�������ֵΪ-1ʱ��ʾ�˵�Ԫ������

	float **ppData;  //������ָ������,ÿһ��ָ���Ա��Ӧһ��ʱ�̵�����,ÿһʱ�̰���nBeam+nPlate��������һ���������ݣ��ȴ������ݣ�Ȼ���ά��������
	float *pTime;  //ʱ������,ÿһ��ָ���Ա��Ӧһ��ʱ�̣���λ����

	CStruFieldOneComponent &operator=(const CStruFieldOneComponent &blk)
	{
		if(this==&blk) return *this;

		ASSERT(FALSE);

		return *this;
	}

	BOOL IsValid(void) {return nMaxSteps>0?TRUE:FALSE;}

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

	//�õ�ppData�е�iStepʱ�̵�idm�ı��οǵ�Ԫ�����ݣ���ȫ�ֵ�Ԫ��
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

	//��������ʱ�̵Ķ����Ƴ�������һ��������F-5��ʽ�����ط����ţ�-1ʧ��
	BOOL ReadBinStruField_AllStep(const CString &fname,CF15Header hdr,CF15StruBlock *pblock,int iComponent); 

};

//����F-5�ļ�ͷ���ֿ������Ϣ(P1~P4)����������Ԫ����������Ӧ��̬���飬���ط����ţ�-1ʧ��
extern "C" _SSG_DLLIMPEXP BOOL ReadF15Header(const CString &fname,CF15Header  &hdr,CF15StruBlock *&pblock);

//д���ļ�ͷ
extern "C" _SSG_DLLIMPEXP BOOL WriteF15Header(const CString &fname,CF15Header hdr,CF15StruBlock *pblock);


