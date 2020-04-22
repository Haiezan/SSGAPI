#pragma once

const int Sys_Conc_Para_Num=14; //���Ͽ��л�������������
const int g_iMax_Material=100;
const int g_iMax_Conc=80;
const int g_iMax_Steel=80;


//�������ͣ�ö��ֵ�����������
enum MATERIAL_TYPE
{
	MAT_UNKNOWN=0, //δ����
	MAT_CONC=1, //������
	MAT_REBAR=2, //�ֽ�
	MAT_STEEL=4, //�͸ֺ͸ְ�
};

//����ͨ�ò����������������͸ֲġ��ֽ�
struct MAT_PROP
{
	int id;
	wchar_t sName[256];
	MATERIAL_TYPE iType;
	float E;  //��λ��MPa
	float V;
	float fck; //��ѹǿ�� ����׼ǿ�ȣ�,��λ��MPa
	float ftk; //����ǿ�ȣ���׼ǿ�ȣ�,��λ��MPa
};

//���������ϲ���
struct MAT_CONCETE_PROP
{
	int id;
	double Para[Sys_Conc_Para_Num];  //���庬��͵�λδ֪
};

//�������ϸ��Ӳ�����������E,V
struct MAT_STEEL_PROP
{
	int id;
	double Fy,B;
};

//��ȡ���в�����
int GetMatNum(void);

//��ȡ������������
int GetConcNum(void);

//��ȡ�ֲĺ͸ֽ��������
int GetSteelNum(void);

extern MAT_PROP g_Material[];
extern MAT_CONCETE_PROP g_Concete_Prop[];
extern MAT_STEEL_PROP g_Steel_Prop[];