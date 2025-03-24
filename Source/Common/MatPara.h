#pragma once
#include "HeadDefine.h"

#include "..\Common\SysPara.h"
#include "..\Common\PublicFunc_Cpp.h"

const int g_iMax_Material=261;//�����Ͻ���ά���ϲ�����ӽ�ֵ��200��Ϊ261
const int g_iMax_Conc=80;
const int g_iMax_Steel=100;


//����ͨ�ò����������������͸ֲġ��ֽ�
struct MAT_PROP
{
	int id;
	wchar_t *sName;//sName[256];��׼���Ͽ�Ĳ�������
	//CString sName;
	MATERIAL_TYPE iType;

	float E;	//��λ��MPa
	float V;	//���ɱ�
	float fcuk;	//�����忹ѹǿ�ȣ���׼ֵ������λ��MPa	
	float fck;	//��ѹǿ�ȣ���׼ֵ������λ��MPa	
	float ftk;	//����ǿ�ȣ���׼ֵ������λ��MPa		
	float fcd;	//��ѹǿ�ȣ����ֵ������λ��MPa���ֽ�ֲ����ֵû��ֵ�İ�0.9��׼ֵȡֵ
	float ftd;	//����ǿ�ȣ����ֵ������λ��MPa���ֽ�ֲ����ֵû��ֵ�İ�0.9��׼ֵȡֵ
	float fcm;	//��ѹǿ�ȣ�ƽ��ֵ���㶫ʡ������λ��MPa
	float ftm;	//����ǿ�ȣ�ƽ��ֵ���㶫ʡ������λ��MPa
	float fstk;	//����ǿ��(��׼ֵ������λ��MPa��������Ϊ��0.88��fcuk���ֽ�ΪΪ��1.5��ftk���ֲ�ΪΪ��1.5��ftk��ԤӦ����Ϊ����ǿ�ȣ�������
	float fTc;	//������ϵ��1/C
	float fDen;	//�����ܶ�
	//MAT_PROP & operator=(const MAT_PROP &mat_prop);
};

struct MAT_MECH_PROP
{
	MAT_MECH_PROP()
		: E(0)
		, V(0)
		, fcuk(0)
		, fck(0)
		, ftk(0)
		, fcd(0)
		, ftd(0)
		, fcm(0)
		, ftm(0)
		, fstk(0)
		, fTc(0)
		, fDen(0)
	{
	}
	MAT_MECH_PROP(const MAT_PROP& mat_prop)
		: E(mat_prop.E)
		, V(mat_prop.V)
		, fcuk(mat_prop.fcuk)
		, fck(mat_prop.fck)
		, ftk(mat_prop.ftk)
		, fcd(mat_prop.fcd)
		, ftd(mat_prop.ftd)
		, fcm(mat_prop.fcm)
		, ftm(mat_prop.ftm)
		, fstk(mat_prop.fstk)
		, fTc(mat_prop.fTc)
		, fDen(mat_prop.fDen)
	{
	}

	float E;	//��λ��MPa
	float V;	//���ɱ�
	float fcuk;	//�����忹ѹǿ�ȣ���׼ֵ������λ��MPa	
	float fck;	//��ѹǿ�ȣ���׼ֵ������λ��MPa	
	float ftk;	//����ǿ�ȣ���׼ֵ������λ��MPa		
	float fcd;	//��ѹǿ�ȣ����ֵ������λ��MPa���ֽ�ֲ����ֵû��ֵ�İ�0.9��׼ֵȡֵ
	float ftd;	//����ǿ�ȣ����ֵ������λ��MPa���ֽ�ֲ����ֵû��ֵ�İ�0.9��׼ֵȡֵ
	float fcm;	//��ѹǿ�ȣ�ƽ��ֵ���㶫ʡ������λ��MPa
	float ftm;	//����ǿ�ȣ�ƽ��ֵ���㶫ʡ������λ��MPa
	float fstk;	//����ǿ��(��׼ֵ������λ��MPa��������Ϊ��0.88��fcuk���ֽ�ΪΪ��1.5��ftk���ֲ�ΪΪ��1.5��ftk��ԤӦ����Ϊ����ǿ�ȣ�������
	float fTc;	//������ϵ��1/C
	float fDen;	//�����ܶ�
};



int _SSG_DLLIMPEXP GetMatNum(void);//��ȡ���в�����

MAT_PROP _SSG_DLLIMPEXP GetMatPropById(int id);

int _SSG_DLLIMPEXP GetMatByName(const CString& sMat);

extern _SSG_DLLIMPEXP MAT_PROP g_Material[];
