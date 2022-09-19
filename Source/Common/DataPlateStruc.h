#pragma once
#include "HeadDefine.h"
#include "SectionBaseHead.h"
#include "DataStrucProp.h"

class CVertex;
class CLine;
class CPlateSectionCollection;
class CProjectPara;

//��״�������ɶ���߶���ɶ���Σ����溬��̬���飬������ɾ��ʱҪ�ȵ���CPlateStruc::Clear()
class _SSG_DLLIMPEXP CPlateStruc: public CStrucProp
{
public:
	CPlateStruc(void);

	CPlateStruc(const CPlateStruc &plate)
	{
		pLineIDM=NULL;
		*this=plate;
	}

	CPlateStruc(STRUCT_TYPE istructype,int istory,DWORD color);

	~CPlateStruc(void){
		if(pLineIDM)
		{
			delete[] pLineIDM; 
			pLineIDM=NULL;
		}
	}

	//int id; //��������id����1��ʼ��ţ������湹���������
	//�߽��߶���
	int nLine; 
	//�߽��߶�����
	int *pLineIDM;
	int iSectionID;  //����ID

	float fThickness;  //����ܺ�ȣ������������͸ֲ�
	int iSubType;  //������ 0-ǽ����1-ǽ��
	int nRebarLayer; //�ֽ�������(ÿ������������)��0��ʾ�޸ֽ�
	int iBottomStory;  //�ײ���¥��ţ�ֻ��ǽ����Ч����ʱ����
	float fOffset; //ƫ�ľ࣬����3���򣨷��߷���
	float fRatio[2];  //����ʣ��壺���׽�,����������ʣ�ǽ��ˮƽ�����,���в㵥�������֮�ͣ��ٷ���
	float Angle[2];  //���ڸֽ��������XZƽ�潻�ߵļнǣ���λ���ȣ�����ǽ��������XYƽ��н�
	float fRebarArea;  //�ݽ������(m^2), ֻ��ǽ����Ч

	SECTION_MAT_TYPE SecType; //��������,��ѡ���Ͷ����� ȫ������gPlateSectionTypeTable[] ��,CFeaInterface::GetPlateTypeSpecValue�и��ݲ������ͶԸֽ����͸ְ�����������
	int nSteelLayer;   //�ְ������0��ʾ�޸ְ�
	float fSteelThick;  //�ְ��ܺ��

	//���²��������ڸ��������ֶ�
	float fAs; //��Ե���������(��λ��m2)����ֵ��ֻ��ǽ��Ч

	//����PKPM�ӿں���OnImportpkpm��ʹ�õ���ʱ�������������ļ���ֻ��ǽ��Ч
	float fAs_top;
	float fLine_Dead_load;
	float fLine_Live_load;
	float fAs_bot;

	//��ʱ���ݣ��������ļ�,u.x>1���Ϸ�����ʼ��u.x=10.0f��ʾδ���㣬���롢���ӡ��ƶ������ʱ��Ҫ����PlateLocalCoorVector���¼���
	Vector4 u,v,w,c0;  //���ֲ̾�����ϵ��ʸ��������ԭ�㣬wΪ���߷���,

	//���ظ�ֵ�����
	CPlateStruc & operator=(const CPlateStruc &plate);

	void Clear();

	//���ñ����������������Сԭ���ݱ����
	void SetLineNum(int nline) 
	{
		nLine=nline;
		if(pLineIDM) delete[] pLineIDM; 
		pLineIDM=new int[nLine];
		ASSERT(pLineIDM);
	}

	//���ض������������˳�����еĶ������PointID����β�㲻�غϣ��ⲿ����ά���ڴ�PointID��pLineΪϵͳ�߶α������飬
	//��������Ľ�����겻�غϣ���û��������ͬ�����벻ͬ�ĵ�
	int GetVexID(int *PointID,const CLine *pLine) const; 

	//���ص㵽��ID�Ĺ�����
	BOOL GetPt2Line(PT2LINE *pPt2Line,const CLine *pLine);


	//�����ι�ϵ����ֲ�����ʸ����wΪ���ߣ������ŷ������ֶ���
	BOOL PlateLocalCoorVector(const CVertex *pVexArray,const CLine *pLineArray);

	//���������߶�ID���ӵ�j���߶ο�ʼ��way>0�����������У�way<0������������
	void RenewLineID(int j,int way);

	//�������ֲ�,nLayer--�ֲ�����fThick--ÿ���ȣ����ȷֲ㣬pos--ÿ��λ�����飬iMaxLayers--pos��������
	//void GetConcLayer(int &nLayer,double &fThick,double *pos,int iMaxLayers);

	//���,���طֲ�����pThick--ÿ���ȣ�iMaxLayers--������
	int GetRebarLayer(double *pThick,int iMaxLayers);
	int GetRebarLayer(float *pThick,int iMaxLayers);
	// �� 2020��10��28��
	int GetRebarLayer(float *pThick);

	//�õ����귶Χ
	void GetRange(Vector4 &rMin,Vector4 &rMax);

	//����ǽ�ĸ߶ȺͿ�ȣ��ڰ�����
	void GetWallSize(float &fWidth,float &fHeight);

	//����ǽ�Ĺ涨��෶Χ��������
	void GetWallRebarUnitArea(float &fHorzArea,float &fVertArea);

	//������ǽ�ֽ���������λ��kN
	float GetRebarWeight();

	virtual BOOL Read(CASCFile &fin,STRUCT_TYPE iType,int &idf,CPlateSectionCollection &cPlateSection,CProjectPara &cPrjPara);   //�Զ��ͷ�ԭ��pLineIDM�ڴ棬���������ڴ�,iType֧��ǽ��
	virtual BOOL Write(CASCFile &fout,int idf);
	virtual BOOL Write2020(CASCFile &fout,int idf);

	//�����Ϣ��д
	virtual BOOL ReadDesignInfo(CASCFile &fin,int idf);   //�Զ��ͷ�ԭ��pLineIDM�ڴ棬���������ڴ�,iType֧��ǽ��
	virtual BOOL WriteDesignInfo(CASCFile &fout,int idf);
	virtual BOOL WriteDesignInfo2020(CASCFile &fout,int idf);

	//���ݽ�����Ϣˢ�¹�����Ϣ
	void RenewPlate();

	void GenLoadId(bool bRewrite=true);//��	float fDeadLoad ��float fLiveLoad����Load����mapload ��2020֮��汾��ȡ
	void GenLoadVal();//��mapload����fDeadLoad��fLiveLoad ��2020֮ǰ�汾��ȡ

	//���߽�˳�򷵻��ĸ��ǵ�ID�����¡����¡����ϡ�����
	BOOL GetCornerPoint(int &left_bottom,int &right_bottom,int &right_top,int &left_top)const;

	//����ǽ����ͻ��ֲ������ֳ�����ά
	void GetWall2BeamFibre(float fUnitWidth, int nDiv, BEAM_FIBRE_GEO* &pConcFibre, int &nConcFibre, BEAM_FIBRE_GEO* &pRebarFibre, 
		int &nRebarFibre, BEAM_FIBRE_GEO* &pSteelFibre, int &nSteelFibre);

	//����Ƥ�ж�
	BOOL IsShin() const;
};
