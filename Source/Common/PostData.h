#pragma once
#include "..\Common\data.h"

//ĳʱ�̵�����,�ȵ���Create�����ڴ�ռ䣬���溬��̬���飬������ɾ��ʱҪ�ȵ���Clear()  //��㡢��Ԫ��¥�㡢��������
class _SSG_DLLIMPEXP CFieldOneStep
{
public:
	CFieldOneStep(){pData=NULL;nRealNode=0;nDataNum=0;}
	~CFieldOneStep() 
	{
		Clear();
	}

	//ʵ�ʽ������Ԫ��������������Ϊ0����Ҫ���ڱ�ʶ�ֽ׶μ��ص����ݽ�ֹ��
	int nRealNode;

	//���������飬���ڶ�����������һ����Ϊʱ�̣����ھ������أ���һ����Ϊ�ý׶���ţ�����ģ̬��������һ����ΪƵ��
	//������ID�����д洢���±�=�к�*nItems+��Ŀ���+1,nItems�ڵ��ú����ж���
	float *pData; //��Ҫֱ�Ӵ����ڴ棬Ӧʹ��CreateBuf����֤nDataNum��pDataͬ��
	int nDataNum; //pData����,��λ��float

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

	//�õ�ʱ��,��λ��,���ڶ����������ݣ�pBuf�ĵ�һ�����ݾ���fTime
	float GetTime()
	{
		if(!pData) return 0;
		return pData[0];
	}

	//�õ�ʱ��,��λ��,���ھ����������ݣ�pBuf�ĵ�һ�����ݾ��ǽ׶κ�
	int GetStage()
	{
		if(!pData) return 0;
		return (int)pData[0];
	}

	//�õ�Ƶ��,��λHz,����ģ̬�������ݣ�pBuf�ĵ�һ�����ݾ���Ƶ�ʣ�������ģ̬�����ļ�
	float GetFreq()
	{
		if(!pData) return 0;
		return pData[0];
	}
	//�õ�ģ̬���ڣ���λ:s
	float GetPeriod() 
	{
		float fr=GetFreq();
		if(fr==0) return 10000.0f;
		return 1.0f/fr;
	}

	//�õ���������ʱ�ý׶ν����
	int GetRealNodeNum()
	{
		if(!pData) return 0;
		return nRealNode;
	}

	float *GetColPtr(int iCol,int nItems) {return pData+iCol*nItems+1;}  //�õ��������ַ��col�кţ�nItems��Ŀ������float����ƫ�Ʋ���*4
	float GetItemData(int iItem,int iCol,int nItems) {return pData[iCol*nItems+iItem+1];}  //�õ�һ�������iItem��Ŀ��,col�����ţ�nItems��Ŀ����
	float &GetItemDataRef(int iItem,int iCol,int nItems) {return pData[iCol*nItems+iItem+1];}  //�õ�һ��������ĵ�ַ��iItem��Ŀ��,col�����ţ�nItems��Ŀ����

	BOOL ReadStepBin(CFile &fin,int nItems,int nCols);  //F-3�ļ����ӵ�ǰλ�ö��������ļ����������з�����nNode�������nColҪ���ķ�����(�ӵ�0�п�ʼ)
	BOOL ReadColBin(CFile &fin,int nItems,int iCol);  //�ӵ�ǰλ�ö��������ļ������뵥��������nNode�������iColҪ����ķ�����
};

//���λ�����ݣ���Ӧ�ֽ׶ξ������أ������ڵ���������
class _SSG_DLLIMPEXP CNodeFieldSet
{
public:
	CNodeFieldSet()
	{
		iGroupID=-1;
		nMaxSteps=0;
	}

	~CNodeFieldSet() {Clear();}

	int iGroupID;  //��Ӧ�ķ�����ţ�-1��ʾȫ�����,����ֱ�Ӹ�ֵ,-2�������÷���

	//���������ڶ��ļ�ʱ��ֵ
	int nItems;        //��ȡ�Ľ����,���������ļ���ʹ�ô����ݣ�Ӧʹ��aFieldsPtr�е�GetRealNodeNum()��ȡ
	int nComponents;  //�ڴ������,Readǰ��ֵ����������ֵ�ķ�����ȡ�󱻶���
	int nFileComponents;  //�ļ��е�ʵ�ʷ�����,Readǰ��ֵ��
	CString sTitle;  //��������,Readǰ��ֵ
	CString pComponentName[Sys_Max_Node_Components];  //��������,Readǰ��ֵ��ǰ��������������dx,dy,dz
	float fMin[Sys_Max_Node_Components],fMax[Sys_Max_Node_Components];  //�����Сֵ,����󼴸�ֵ
	int nMaxSteps;  //�ļ������ʱ�䲽���������ļ�ʱ��ֵ

	CArray<CFieldOneStep*,CFieldOneStep*> aFieldsPtr; //���������飬�±�Ϊʱ�䲽��ţ�Read�и�ֵ


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

	//����
	BOOL IsValid(void) {return aFieldsPtr.GetSize()>0?TRUE:FALSE;}

	//�õ�ʱ��ֱ���
	float GetDTime(void) 
	{
		if(aFieldsPtr.GetCount()==0) return 0;
		if(aFieldsPtr.GetCount()==1) return aFieldsPtr[0]->GetTime();
		return aFieldsPtr[1]->GetTime()-aFieldsPtr[0]->GetTime();
	}

	inline int GetStepNumber() const {return (int)aFieldsPtr.GetSize();}  //�Ѿ������ʱ�䲽����ز�
	void Clear();  //����������ݣ��ͷ������ڴ�
	void GetMaxMin();  //���������Сֵ��

	//��������ƽ��λ�ƣ�bSelectCol=TRUEʱѡ��һ��������ȡ��FALSEʱ��ȡ���з���
	BOOL ReadBinNodeField_AllStep(const CString &fname,bool bSelectCol=false); 
	//��������ƽ��λ��;iTime--��ȡ��ʱ��(-1ʱȫ��),ֻ��һ�������GetStepNumber�᷵��1
	BOOL ReadBinNodeField_OneStep(const CString &fname,int iTime);

	//��������ƽ��λ�ƣ�����order��΢��;iTime--��ȡ��ʱ��(-1ʱȫ��),ʵ�ʶ�ȡ3����΢�ֺ���1�������GetStepNumber�᷵��1
	BOOL ReadBinNodeField_OneStep_Diff(const CString &fname,int iTime,int order);

	//��������Ʒֽ׶μ��ؽ��λ�ƣ�bSelectCol=TRUEʱѡ��һ��������ȡ��FALSEʱ��ȡ���з���
	BOOL ReadBinStaticNodeField_AllStage(const CString &fname,bool bSelectCol=false); 
	//��������Ʒֽ׶μ��ؽ��λ��;iTime--��ȡ��ʱ��(-1ʱȫ��),ֻ��һ�������GetStepNumber�᷵��1
	BOOL ReadBinStaticNodeField_OneStage(const CString &fname,int iStage);

	BOOL Disp2Speed(); //��λ�Ƽ����ٶ�
	BOOL Disp2Acce();  //��λ�Ƽ�����ٶ�

private:
	BOOL DispDiff(int order); //��λ�ƽ���΢��,order=1�õ��ٶȣ�order=2�õ����ٶ�

};



//¥���ļ�����F-7
class _SSG_DLLIMPEXP CStoryDataSet
{
public:
	CStoryDataSet()
	{
		nMaxSteps=0;
		fStoryMax = NULL;
	}

	~CStoryDataSet() {Clear();}

	int nItems;			//����������Ӧ�õ���¥����+1�������ػ�����
	int nComponents;	//������
	CString sTitle;		//����
	CString pComponentName[Sys_Max_Story_Components];  //��������,Readǰ��ֵ
	float fMin[Sys_Max_Story_Components],fMax[Sys_Max_Story_Components];  //�����Сֵ,����󼴸�ֵ
	int nMaxSteps;		//�ļ������ʱ�䲽���������ļ�ʱ��ֵ

	//cmliu 2016/2/16 ����ÿ��¥�����з��������ֵ
	float *fStoryMax; // ÿ��¥�����з��������ֵ��һ����������һ���������е���,Ӧ����nTotalStory*nComponents��


	CArray<CFieldOneStep*,CFieldOneStep*> aFieldsPtr; //���������飬�±�Ϊʱ�䲽��ţ���¥��Ӹߵ�����������

	CStoryDataSet &operator=(const CStoryDataSet &s)
	{
		if(this==&s) return *this;

		ASSERT(FALSE);

		return *this;
	}

	//����

	BOOL IsValid(void) {return aFieldsPtr.GetSize()>0?TRUE:FALSE;}

	//�õ�ʱ��
	float GetDTime(void) 
	{
		if(aFieldsPtr.GetCount()==0) return 0;
		if(aFieldsPtr.GetCount()==1) return aFieldsPtr[0]->GetTime();
		return aFieldsPtr[1]->GetTime()-aFieldsPtr[0]->GetTime();
	}

	int GetStepNumber(){return (int)aFieldsPtr.GetSize();}  //�Ѿ������ʱ�䲽
	void Clear();  //����������ݣ��ͷ������ڴ�
	void GetMaxMin();  //���������Сֵ��

	//cmliu 2016/2/16 ����ÿ��¥�����з��������ֵ
	void GetStoryMax();
	float *GetStoryMaxPtr(int iComponent);	// �õ�ĳ������������¥�����ֵ����   

	//����ȫ��ʱ��¥������F-7
	BOOL ReadBinStoryField_AllStep(const CString &fname); 
	//����ʱ�䲽��
	int ReadStep(const CString &fname,float& dtime);
	//���뵥��ʱ��¥������F-7
	BOOL ReadBinStoryField_OneStep(const CString &fname,int iTime); 
};

//���λ�ƺͲ��λ�ƽ��ļ�����
class _SSG_DLLIMPEXP CStoryDriftDataSet : public CStoryDataSet
{
public:
	//�õ����λ��dx��ʼ��ַ
	float *GetDXPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(0,nItems);}
	//�õ����λ�ƽ�ax��ʼ��ַ
	float *GetAXPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(1,nItems);}
	//�õ����λ��dy��ʼ��ַ
	float *GetDYPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(2,nItems);}
	//�õ����λ�ƽ�ay��ʼ��ַ
	float *GetAYPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(3,nItems);}
};

//�������ļ�����
class CStoryShearDataSet : public CStoryDataSet
{
public:
	//�õ����Ӳ�����Qx��ʼ��ַ
	float *GetPillarQxPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(0,nItems);}
	//�õ�б�Ų�����Qx��ʼ��ַ
	float *GetBraceQxPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(2,nItems);}
	//�õ�����ǽ������Qx��ʼ��ַ
	float *GetWallQxPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(4,nItems);}
	//�õ�¥���ܼ���Qx��ʼ��ַ
	float *GetStoryQxPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(6,nItems);}

	//�õ����Ӳ�����Qy��ʼ��ַ
	float *GetPillarQyPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(7,nItems);}
	//�õ�б�Ų�����Qy��ʼ��ַ
	float *GetBraceQyPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(9,nItems);}
	//�õ�����ǽ������Qy��ʼ��ַ
	float *GetWallQyPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(11,nItems);}
	//�õ�¥���ܼ���Qy��ʼ��ַ
	float *GetStoryQyPtr(int istep) {return aFieldsPtr[istep]->GetColPtr(13,nItems);}
};



