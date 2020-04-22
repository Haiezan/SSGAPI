#pragma once
#include "HeadDefine.h"
#include "ASCFile.h"
#include "SectionBase.h"

//�湹��������
class _SSG_DLLIMPEXP CPlateSection
{
public:
	//��������������
	CPlateSection(void) {pLayers=NULL; Clear();}
	CPlateSection(const CPlateSection &sec)	{ pLayers=NULL; nUsedCount=0; *this=sec; }
	~CPlateSection(void) { Clear(); }

	//��������
	int id;  //����ID
	CString sName;  //��������,���������ý����������ԣ�һ���������Ʊ��Ķ�������ݸĶ�ǰ��Ķ�Ӧ��ϵ�滻������
	int iStructType;  //�������ͣ�1-�壻2-ǽ
	int iPlateMatType;		//����������ʹ���,1-��������2-����ְ��������3-˫��ְ��������4-���ְ�
	int nLayers; //������
	struct LAYER_INFO
	{
		float fLayerThick;				//���ȣ���λ����
		SUBSECTION_MAT_TYPE iLayerMatType;	//�����
		float fOffset;					//������λ��,��λ����
	} *pLayers; //����Ϣ
	
	float fThick; //�ܺ�ȣ��ɸ����ۼӵõ������뼰�޸�Ҫ����
	COLORREF dwColor; //��ʾ��ɫ, ���ڿ���Ѱ��
	int nUsedCount;  //������ʹ�õĴ�����һ��Ҫ�ȼ�����ʹ��,��ʱ����

	void Clear(void);
	//void GetThick(void);//������
	CPlateSection & operator=(const CPlateSection &sec);
	BOOL operator==(const CPlateSection &sec) const;
	BOOL operator!=(const CPlateSection &sec) const;

	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	CString sMatName();
};


