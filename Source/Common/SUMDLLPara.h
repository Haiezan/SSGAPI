#pragma once
#include "..\Common\SectionBaseHead.h"
#include "..\Common\SysPara.h"

struct SectPara
{
	SectPara():/*SectFlag(0),B(0),H(0),*/a0(0), ConcGrade(1), ZJGrade(1), GJGrade(1), KZGrade(0)/*,B1(0),H1(0),bfc(0),hfc(0),bft(0),hft(0)*/
	{
		type_column = 0;
		l0 = 2400;
		rho_w = 0.003f;
		typeStrength = 0;
	}
	SUBSECTION_SHAPE iShape; //������״��Ԥ������״��ԭʼ��״��
	//���漸�β���
	//Ԥ������״���β���
	union
	{
		struct GEO_RECT rect;
		struct GEO_BOX box;
		struct GEO_CIRC circ;
		struct GEO_PIPE pipe;
		struct GEO_I I;
		struct GEO_CROSS cross;
		struct GEO_REBAR rebar;
		struct GEO_CRISS criss;
		struct GEO_REGPOLY regpoly;
		struct GEO_CHANNEL channel;
		struct GEO_DBLCHANNEL dblchannel;
		struct GEO_TRAPEZOID trapzoid;
		struct GEO_L L;
		struct GEO_T T;
		struct GEO_RECT_VAR rect_var;
		float fValue[Sys_SubSectionParaNum];	//��λ: ��
	};

	//int SectFlag; //�������������� 0 ���� 1 Բ�� 2 T�� 3 ������
	//float B;		//����ߴ� r
	//float H;		//����ߴ� rs

	float a0;		//��������
	int ConcGrade;	//
	int ZJGrade;	//�ݽ�ȼ�
	int GJGrade;	//����ȼ�
	int KZGrade;	//����ȼ�
	//float B1;	
	//float bfc;		��ѹ����Ե���

	//���ӳ��ȣ� ���ͣ����������ţ�
	int type;		//����

	int typeStrength;

	int type_column;	//�������� //0=��ͨ����1=������2=��֧����3=��֧������
	float l0;			//����	���Ӽ�����
	float rho_w;		//ǽ�ľ���
};

struct SectForce
{
	SectForce() : M(0), V(0), T(0), N(1), M1(1), V1(1) {}
	float M;	//�����
	float V;	//������
	float T;	//����Ť��
	float N;	//��������

	float M1;	//������һ�������
	float V1;	//������һ�������
};

//�������
struct SectOut
{
	SectOut()
		//, AsT2(0), AsC2(1), TorSect1(1), ShearSect2(1)
	{
		Yis1 = 0;
		ShearSect1 = 0;
		Asu = 0;
		Asd = 0;
		Asv = 0;
		Ast = 0;
		//Yis2 = 0;
		//TorSect2 = 0;
		//AsShear2 = 0;
		//AsTor2 = 0;
		As = 0;
		Asc = 0;
		Asx = 0;
		Asy = 0;
		Asvx = 0;
		Asvy = 0;
		Asvx15 = 0;
		Asvy15 = 0;
		Ast = 0;
	}

	//��
	int Yis1;			//��������־    �����ѹ���߶�				

	float Asu;			//���ֽ�
	float Asd;			//ѹ�ֽ�

	int ShearSect1;		//���н����Ƿ�����Ҫ�� ��־
	//	int TorSect1;		//Ťת�����Ƿ�����Ҫ��			//��ʹ��

	float Asv;		//���й���
	float Ast;		//Ťת����

	//	float Yis2;			//������һ���������ѹ���߶�	//��ʹ��
	//	float AsT2;			//������һ�������ֽ�			//��ʹ��	
	//	float AsC2;			//������һ����ѹ�ֽ�			//��ʹ��

	//	int ShearSect2;		//������һ������н����Ƿ�����Ҫ�� (1 ����  0 ������)
	//	int TorSect2;		//������һ������н����Ƿ�����Ҫ�� (1 ����  0 ������)		//��ʹ��

	//	float AsShear2; 	//������һ������й���
	//	float AsTor2;		//������һ����Ťת����

	//���������ʶ

	//���ɹ���ʶ


	//����
	float As;			//�����ݽ���� -- ����Բ��

	float Asc;			//�ǽ���� ����

	float Asx;			//x�����ݽ���� �����ǽ�
	float Asy;			//y�����ݽ���� �����ǽ�

	float Asvx;			//x���򹿽����
	float Asvy;			//y���򹿽����

	float Asvx15;		//x����Ǽ������������
	float Asvy15;		//y����Ǽ������������
};
