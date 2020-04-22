#pragma once
#include "HeadDefine.h"
//#include "..\Common\SysPara.h"
#include "../Common/MatPara.h"
#include "ASCFile.h"


#define MATERIAL_TYPE_NUM 3


struct _SSG_DLLIMPEXP MATERIAL_TYPE_PROP
{
	MATERIAL_TYPE type;  //������� 
	CString name;  //�������
};

//�������ߵ�
struct _SSG_DLLIMPEXP MATCURVE
{
	float strain; //Ӧ��
	float stress; //Ӧ��
	float damage; //����
};

//�õ���������g_Material��Ӧ���±�
int GetMatIndex(int id);
float GetMatE(int id);
float GetMatV(int id);

//������
class _SSG_DLLIMPEXP CMaterial
{
public:
	CMaterial(void){pComp=NULL;pTension=NULL;sName=L"";nCompPara=nTensPara=0;iConcType=0;id=-1;Fy=0;B=0;}

	//���ƹ��캯��
	CMaterial(const CMaterial &mat)
	{
		pComp=NULL;pTension=NULL;
		*this=mat;
	}

	~CMaterial(void)
	{
		if(pComp) delete[] pComp; pComp=NULL;
		if(pTension) delete[] pTension; pTension=NULL;
		nCompPara=nTensPara=0;
	}

	//��������
	int id; //���ϱ�ţ���һ������ 
	CString sName;   //��������,������Ϊ����
	MATERIAL_TYPE iType; //��������
	int iConcType;  //iType==MAT_CONCʱʹ�ã��������������0--ͨ�û�������1--�Զ���

	//���ֲ���ͨ�ò���
	float E;  //��ʼ����ģ����MPa=N/mm^2��
	float V;  //���ɱ�

	//ͨ�û��������ϲ��������庬����ĵ�,iType==MAT_CONC && iConcType==0ʱ��Ч
	float ConcPara[Sys_Conc_Para_Num];

	//�Զ�����������в���
	int nCompPara,nTensPara;  //ѹ������������
	MATCURVE *pComp;  //ѹ���߲���
	MATCURVE *pTension;  //�����߲���

	//�ֲ����в���
	float Fy; //����ǿ�ȣ�kN/m^2
	float B; //ǿ������

	//float G(void) {return E/(1.0f+2.0f*V);}  //�������ģ��,���ֲ���ͨ��
	/*Modified by Hexf 2010-10-08*/ 
	inline float G(void) {return 0.5f*E/(1.0f+V);}  //�������ģ��,���ֲ���ͨ��

	//�����Զ�����������ϲ���,�������е����ݽ��и���
	void SetConc(CString &sname,/*float dens,*/float e,float poission,int ntenpara,MATCURVE *ptension,int ncomppara,MATCURVE *pcomp);
	//���øֽ���ϲ���
	void SetRebr(CString &sname,/*float dens,*/float e,float poission,float fy,float b);
	//���øֲĲ��ϲ���
	void SetSteel(CString &sname,/*float dens,*/float e,float poission,float fy,float b);

	CMaterial & operator=(const CMaterial &mat);

	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
};

class _SSG_DLLIMPEXP CMaterialCollection
{
public:
	CMaterialCollection(void);
	~CMaterialCollection(void){Clear();}

	//���ƹ��캯��
	CMaterialCollection(const CMaterialCollection &mat) 
	{
		*this=mat;
	}

	CArray<CMaterial,CMaterial&> aMaterial; 

public:
	int GetIndex(const CString &sName);				//�������ֲ�����������,�Ҳ�������-1
	int GetConcIndex(const CString &sName);			//�������ֲ��һ������������������������ϵ������룩,�Ҳ�������-1
	int GetSteelIndex(const CString &sName);		//�������ֲ����͸ֲ����������͸ֲ��ϵ�����������ֽ���͸֡��ְ壩,�Ҳ�������-1
	//int GetID(CString &sName);   //�������ֲ���ID
	CMaterial *GetMat(const CString &sName); //�������Ʋ��Ҳ��ϵ�ַ

	int GetConcCount(void);   //���������������
	int GetSteelCount(void);  //����ֲĲ������������ֽ�

	void Clear(void)
	{
		aMaterial.RemoveAll();
	}

	CMaterialCollection & operator=(const CMaterialCollection &mat)
	{
		if(this==&mat) return *this;

		Clear();

		aMaterial.Copy(mat.aMaterial);
		//for(int i=0;i<mat.aMaterial.GetCount();i++)
		//{
		//	CMaterial imat=(mat.aMaterial[i]);
		//	aMaterial.Add(imat);
		//}
		return *this;
	}

	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void LoadWholeLib(void);   //����ȫ������
};
