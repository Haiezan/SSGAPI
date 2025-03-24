#pragma once
#include "HeadDefine.h"
#include "../Common/MatPara.h"
#include "ASCFile.h"

#define MATERIAL_TYPE_NUM 7

struct _SSG_DLLIMPEXP MATERIAL_TYPE_PROP
{
	MATERIAL_TYPE type;  //������� 
	CString name;  //�������
};
extern _SSG_DLLIMPEXP MATERIAL_TYPE_PROP MaterialTypeProp[]; //������ ���� 2021-10-26


//�������ߵ�
struct _SSG_DLLIMPEXP MATCURVE
{
	float strain; //Ӧ��
	float stress; //Ӧ��
	float damage; //����
};


//������
class _SSG_DLLIMPEXP CMaterial
{
public:
	CMaterial(void);
	CMaterial(const MAT_PROP& prop);
	//���ƹ��캯��
	CMaterial(const CMaterial &mat)
	{
		pConcPara1D = NULL; 
		pConcPara2DS = NULL; 
		pConcPara2DD = NULL; 
		pSteel1D = NULL; 
		pSteel2D = NULL; 

		*this=mat;
	};
	~CMaterial(void)
	{
		Clear();
	}
	void Clear(void);
	CMaterial & operator=(const CMaterial &mat);

	int id; //���ϱ�ţ�Ψһ�����ʶ����ϵͳ���Ͽ��Ų�ͬ 
	CString sName;   //�����û��Զ�������,������Ϊ����
	MATERIAL_TYPE iType; //��������

	//���ֲ���ͨ�ò���
	MAT_MECH_PROP m_linearMatProps;//���ϣ������������͸ֲġ��ֽ�����Բ�������λΪMPa
	inline float G(void) {return 0.5f*m_linearMatProps.E/(1.0f+m_linearMatProps.V);}  //�������ģ��,���ֲ���ͨ��

	//�����Բ�������λΪKPa
	float fc;	//���������ֽ�ֲĿ�ѹǿ�ȣ����ڷ����Լ��㣬��λ��KPa	
	float ft;	//���������ֽ�ֲĿ���ǿ�ȣ����ڷ����Լ��㣬��λ��KPa


	//������
	//һά
	int iCSkeleton_c;	//һά������(0-�û��Զ���,1-�淶ȫ����,2-Rusch,3-Hongnestad,4-Mander,5-Ǯ����,6-Kent-Park)
	int iCSkeletonTube;	//һά������(0-��iCSkeleton_c��ͬ,1-���ֺ�)
	int iCSkeleton_t;	//һά������(0-�û��Զ��壩 (1-�����(6points inc. zero)��2-˫����()
	int nConcComp1D;
	int nConcTens1D;
/*  һά�Ǽ����ߣ���ͬ�Ǽ�����ʱ�������岻ͬ
	��ѹ�Σ�21��
			�Զ������ߣ�20���㣬ÿ����3�������ֱ���Ӧ�䡢Ӧ��������
			�淶ȫ����: ��
			Rusch: fc,��c,��cu, n
			Hongnestad: fc,��c,��cu
			Mander: ��
			Qian: ��
			Kent-Park: ��
			Han: ��
	�����Σ�18��
			�Զ������ߣ�10���㣬ÿ����3�������ֱ���Ӧ�䡢Ӧ��������
			�淶ȫ����: ��
			˫���ߣ���tu
*/
	float *pConcPara1D;
	int iCHysRule;		//һά��������(0-��������,1-�򵥣�2-��ϸ)

	//��ά
	int nConcComp2DS;
	int nConcTens2DS;
	int nConcComp2DD;
	int nConcTens2DD;
	float *pConcPara2DS;
	float *pConcPara2DD;

	//�ֽ�ֲ�
	//һά
	int iSSkeleton;		//(0-�����ߣ�1-�����ߣ�2-������(Esmaeily-Xiao))
	int nSteelPara1D;   //pSteel1D����ĳ���
/*  һά�Ǽ����ߣ���ͬ�Ǽ�����ʱ�������岻ͬ
		������: ��cu,��tu,k
		������: ��cu,��tu,k,k1
		������: ��cu,��tu,k,k1,k2,k3
*/
	float *pSteel1D;	//�ֲġ��ֽ�һά����������ÿ�ֲ���6��
	int iSHysRule;		//(0-�涯ǿ����1-Clough��2-Legeron)	
	//��ά
	int nSteelPara2D;   //pSteel2D����ĳ���
	float *pSteel2D;	//�ֲġ��ֽ��ά����������2����,ÿ����2������,�ֱ���Ӧ��������Ӧ��

	void GetDefaultPara();
	
	void Read2021(CASCFile &fin);
	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);

};

class _SSG_DLLIMPEXP CMaterialCollection
{
public:
	CMaterialCollection(void);
	~CMaterialCollection(void){Clear();}

	CMaterialCollection(const CMaterialCollection &mat) 
	{
		*this=mat;
	}
	void Clear(void)
	{
		for (int i=0;i<aMaterial.GetCount();i++)
		{
			aMaterial[i].Clear();
		}
		aMaterial.RemoveAll();

	}
	CMaterialCollection & operator=(const CMaterialCollection &mat)
	{
		if(this==&mat) return *this;
		Clear();
		aMaterial.Copy(mat.aMaterial);
		return *this;
	}

	CArray<CMaterial,CMaterial&> aMaterial; 

public:
	int GetIndex(const CString &sName, int iType = MAT_CONC|MAT_REBAR|MAT_STEEL|MAT_TENDON|MAT_MASONRY| MAT_ALUMINIUM | MAT_FIBRE) const; 			//�������ֲ�����������,�Ҳ�������-1
	int GetIndexById(const int &id);

	int GetMatID(const CString &sName, int iType = MAT_CONC|MAT_REBAR|MAT_STEEL|MAT_TENDON | MAT_MASONRY| MAT_ALUMINIUM | MAT_FIBRE) const;
	CString GetMatName(const int &id);
	CMaterial *GetMat(const CString &sName); //�������Ʋ��Ҳ��ϵ�ַ

	float GetMatfc(CString& mat);
	float GetMatfck(CString &mat);
	float GetMatfcm(CString& mat);

	float GetMatft(CString& mat);
	float GetMatftk(CString& mat);
	float GetMatftm(CString& mat);

	float GetMatfcu(CString& mat);

	float GetMatE(CString &mat);
	float GetDensity(CString &mat);
	int GetMaterialType(CString& mat);
	float GetMatG(CString& mat);
	
	int GetConcCount(void);   //���������������
	int GetSteelCount(void);  //����ֲĲ������������ֽ�			
	int GetMaxId();
	void GetNewName(CString &sName, const CString &originalName) const ;

	void Read2021(CASCFile &fin);
	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void Write2020(CASCFile &fout);

	void LoadWholeLib(void);   //����ȫ������
	void LoadLibCommon();//���س��ò���
};
