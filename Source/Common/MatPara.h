#pragma once
#include "HeadDefine.h"

#include "..\Common\SysPara.h"
#include "..\Common\PublicFunc_Cpp.h"

const int g_iMax_Material=125;//��ԤӦ������ӽ�ֵ��100��Ϊ120
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


//��ȡ���в�����
int _SSG_DLLIMPEXP GetMatNum(void);
extern _SSG_DLLIMPEXP MAT_PROP g_Material[];
