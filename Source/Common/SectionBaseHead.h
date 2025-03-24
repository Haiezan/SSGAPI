#pragma once
#include "HeadDefine.h"

//�ӽ������Ͷ���,��һ����
enum SUBSECTION_MAT_TYPE 
{
	SUBSECTION_MAT_TYPE_NONE=0,		//�޲���
	SUBSECTION_MAT_TYPE_CONC=1,		//������
	SUBSECTION_MAT_TYPE_REBAR=2,	//�ֽ���
	SUBSECTION_MAT_TYPE_ST=4,		//�͸�
};

//������ඨ�壬���ϲ���
enum SECTION_MAT_TYPE
{
	//��λ��ϣ�bit0����������bit1-�ֽbit2-�ֲģ�
	//����				                           ������	   �ֽ�	   �ֲ�
	SECTION_MAT_TYPE_RC=3,		//�ֽ��������      ��			��
	SECTION_MAT_TYPE_ST=4,		//�͸֣�								��
	SECTION_MAT_TYPE_SRC=7,		//�ֹǻ�������      ��			��		��
	SECTION_MAT_TYPE_CFT=5,		//�ֹܻ�������      ��					��
	SECTION_MAT_TYPE_REBAR=2,	//���ڸ����������棬			��
	//�����0��ʼ�������,����ֵ�����޸�
};

// �������ͣ�������桢�͸���Ͻ���
enum SECTION_TYPE
{
	SECTION_UNKNOWN_SECTION = -1,		//δ֪
	REGULAR_CONCRETE_SECTION = 0, // �������������
	REGULAR_STEEL_SECTION = 1, // �����͸ֽ���
	COMBIEND_SECTION = 2, // ��Ͻ���
	STEEL_COMBIEND_SECTION = 3, //�͸���Ͻ���
};

//������״����,ģ��ID
//��ֵ�����ʽ��
//RECT-ʵ�ľ��Σ�BOX-���ľ��Σ�CIRC-ʵ��Բ�Σ�PIPE����Բ�Σ�I-�����Σ�CROSS-ʮ�ֹ��Σ�CRISS-ʮ����
//RC-�ֽ��������ST-�͸֣�SRC-�ֹǻ�������CFT-�ֹܻ�����
enum SECTION_SHAPE  
{
	//������,0-99
	//BEAM_ARBITRARY	=0,		//������Ͻ�����

	BEAM_RC_RECT		=1,     //��������
	BEAM_ST_BOX			=2,     //���ֹ���
	BEAM_ST_I			=3,     //�����͸���
	BEAM_CFT_BOX_RECT	=4,     //���ֹܻ�������������ֹܣ�
	BEAM_SRC_RECT_I		=5,     //������-�ֹǻ���������

	//����
	BEAM_RC_I			=6,		//�����ͻ�������
	BEAM_RC_CIRC		=7,		//Բ�λ�������
	BEAM_RC_REGPOLY		=8,		//������λ�������
	BEAM_RC_CHANNEL		=9,		//���ͻ�������
	BEAM_RC_CRISS		=10,    //ʮ���ͻ������������˻�ΪT�ͻ�������
	BEAM_RC_BOX			=11,	//���ιܻ�������
	BEAM_RC_DBLCHANNEL	=12,	//˫���ͻ�������
	BEAM_RC_CROSS		=13,    //ʮ�ֹ��ͻ�������
	BEAM_RC_TRAP		=14,    //���λ�������

	BEAM_CFT_PIPE_CIRC	=15,    //Բ�ֹܻ�������������ֹܣ�

	BEAM_SRC_RECT_BOX	=16,    //���ֹ�-�ֹǻ���������
	BEAM_SRC_RECT_CROSS	=17,    //ʮ�ֹ���-�ֹǻ���������
	BEAM_RC_VAR			=18,    //��������������--�ݲ�֧��
	BEAM_RC_L			=19,    //L�ͻ�������
	BEAM_SRC_RECT_PIPE	=20,    //Բ�͸ֹ�-�ֹǻ���������

	BEAM_SRC_CIRC_I		=21,    //������-�ֹǻ�����Բ��
	BEAM_SRC_CIRC_PIPE	=22,    //Բ�ֹ�-�ֹǻ�����Բ��
	BEAM_SRC_CIRC_CROSS	=23,    //ʮ�ֹ���-�ֹǻ�����Բ��
	BEAM_RC_T			=24,    //T�ͻ�������
	BEAM_RC_PIPE		=25,	//Բ���λ�������
	BEAM_ST_PIPE		=26,	//Բ�ֹ���
	BEAM_ST_RECT		=27,	//���θ���  //�Ǳ��� 2015.5.5
	BEAM_ST_CIRC		=28,	//ʵ��Բ�θ���  //�Ǳ��� 2015.5.5

	
	BEAM_ST_CROSS			=29,
	BEAM_ST_CRISS	    	=30,
	BEAM_ST_REGPOLY   		=31,
	BEAM_ST_CHANNEL			=32,
	BEAM_ST_DBLCHANNEL		=33,
	BEAM_ST_TRAP	    	=34,
	BEAM_ST_L	    		=35,
	BEAM_ST_T	    		=36,

	BEAM_ST_DOUBLELIMBS_CHANNEL = 37, // ˫֫���͸�
	BEAM_ST_DOUBLELIMBS_H = 38, // ˫֫H�͸�
	BEAM_ANGLE_ST_FOURLIMBS = 39, // ��֫�Ǹ�
	BEAM_ST_H_ADD_PLATE = 40, // H�ͼ��ϰ��
	BEAM_ANGLE_ST_DOUBLELIMBS = 41, // ˫֫�Ǹ�
	BEAM_ST_THREELIMBS_PIPE = 42, // ��֫Բ�ܸ�

	//����б�Ž���,100-199
	PILLAR_ARBITRARY		=100,		//������Ͻ�����

	PILLAR_RC_RECT			=101,      //����������
	PILLAR_RC_CIRC			=102,      //������Բ��

	PILLAR_ST_BOX			=103,      //���ֹ���
	PILLAR_ST_PIPE			=104,      //Բ�ֹ���
	PILLAR_ST_I				=105,      //�����͸���
	PILLAR_ST_CROSS			=106,      //ʮ�ֹ��͸���

	PILLAR_CFT_BOX_RECT		=107,   //���ֹܻ���������������ֹܣ�
	PILLAR_CFT_PIPE_CIRC	=108,   //Բ�ֹܻ�����Բ��������ֹܣ�

	PILLAR_SRC_RECT_BOX		=109,   //���ֹ�-�ֹǻ���������
	PILLAR_SRC_RECT_I		=110,   //������-�ֹǻ���������
	PILLAR_SRC_RECT_CROSS	=111,   //ʮ�ֹ���-�ֹǻ���������

	PILLAR_SRC_CIRC_PIPE	=112,   //Բ�ֹ�-�ֹǻ�����Բ��
	PILLAR_SRC_CIRC_I		=113,   //������-�ֹǻ�����Բ��
	PILLAR_SRC_CIRC_CROSS	=114,   //ʮ�ֹ���-�ֹǻ�����Բ��

	//����
	PILLAR_RC_I				=115,	//�����ͻ�������
	PILLAR_RC_REGPOLY		=116,	//������λ�������
	PILLAR_RC_CHANNEL		=117,	//���ͻ�������
	PILLAR_RC_CRISS		    =118,   //ʮ���ͻ������������˻�ΪT�ͻ�������
	PILLAR_RC_BOX			=119,	//���ιܻ�������
	PILLAR_RC_DBLCHANNEL	=120,	//˫���ͻ�������
	PILLAR_RC_CROSS			=121,   //ʮ�ֹ��ͻ�������
	PILLAR_RC_TRAP			=122,   //���λ�������
	PILLAR_RC_VAR			=123,   //��������������--�ݲ�֧��
	PILLAR_RC_L				=124,   //L�ͻ�������
	PILLAR_RC_PIPE			=125,	//Բ���λ�������
	PILLAR_SRC_RECT_PIPE	=126,	//Բ�ֹ�-�ֹǻ���������
	PILLAR_RC_T				=127,	//T�λ�������		//�Ǳ��� 2015.5.5
	PILLAR_ST_RECT			=128,	//���θ���		//�Ǳ��� 2015.5.5
	PILLAR_ST_CIRC			=129,	//ʵ��Բ�θ���		//�Ǳ��� 2015.5.5

	PILLAR_ST_CRISS			=130,
	PILLAR_ST_REGPOLY   	=131,
	PILLAR_ST_CHANNEL		=132,
	PILLAR_ST_DBLCHANNEL	=133,
	PILLAR_ST_TRAP			=134,
	PILLAR_ST_L	    		=135,
	PILLAR_ST_T	    		=136,

	PILLAR_HANLINHAI		=137,	//���ֺ�

	PILLAR_ST_DOUBLELIMBS_CHANNEL = 138, // ˫֫���͸���
	PILLAR_ST_DOUBLELIMBS_H = 139, // ˫֫H�͸���
	PILLAR_ANGLE_ST_FOURLIMBS = 140, // ��֫�Ǹ���
	PILLAR_ST_H_ADD_PLATE = 141, // H�ͼ��ϰ����
	PILLAR_ANGLE_ST_DOUBLELIMBS = 142, // ˫֫�Ǹ���
	PILLAR_ST_THREELIMBS_PIPE = 143, // ��֫Բ�ܸ���

	//��Ե�����������������ݽ����,200-299
	AUX_REBAR_BOX	=200,		//����������������Ե����,�����������ݽ��������ΪSECTION_MAT_TYPE_REBAR���ӽ�������ΪSUBSECTION_MAT_TYPE_REBAR��������ֻ�иֽ�
	AUX_REBAR_CIRC = 201,//����б��

	SHAPE_LAST, //��β��ʶ���ӽ��涼������ǰ�棡����
};

//�ӽ�����״����
enum SUBSECTION_SHAPE 
{
	SUBSHAPE_UNKNOWN	=-1,	//��Ч
	SUBSHAPE_ARBITRARY  =0,		//�������
	SUBSHAPE_RECT       =1,		//ʵ�ľ���
	SUBSHAPE_BOX		=2,		//���ι�
	SUBSHAPE_CIRC       =3,		//ʵ��Բ
	SUBSHAPE_PIPE       =4,		//Բ��
	SUBSHAPE_I          =5,		//������
	SUBSHAPE_CROSS		=6,		//ʮ�ֹ���
	SUBSHAPE_LINE		=7,		//һ�����Σ������߲�����ʾ����
	SUBSHAPE_REBAR		=8,		//�ֽ�㣬��ʱ��������֧���ݽ�����
	SUBSHAPE_CRISS      =9,     //ʮ����

	SUBSHAPE_REGPOLY    =10,	//�������
	SUBSHAPE_CHANNEL    =11,	//����
	SUBSHAPE_DBLCHANNEL =12,	//˫����
	SUBSHAPE_TRAPEZOID  =13,	//����
	SUBSHAPE_L			=14,	//L��
	SUBSHAPE_T			=15,	//T��

	SUBSHAPE_HANLINHAI_OUTER		=16,	//���ֺ������  ���ֺ��Բ�������
	SUBSHAPE_HANLINHAI_INNERSTEEL	=17,	//���ֺ����ĸ��ֹܽ���
	SUBSHAPE_HANLINHAI_INNERCONC	=18,	//���ֺ����ĸ���������Ĭ��Ϊ�ⲿ�Ļ�����

	SUBSHAPE_DOUBLELIMBS_CHANNEL = 19,	//˫֫���͸���
	SUBSHAPE_DOUBLELIMBS_H = 20,	//˫֫H�͸���
	SUBSHAPE_FOURLIMBS_L = 21,	//��֫�Ǹ���
	SUBSHAPE_H_ADD_PLATE = 22,	//H��+�����
	SUBSHAPE_DOUBLELIMBS_L = 23,	//˫֫�Ǹ���
	SUBSHAPE_THREELIMBS_PIPE = 24,	//��֫Բ�ܸ���

};

//����߽��
struct SECTION_POINT
{
	float x2,x3;  //��λ����
	int iBnd;  //�߽���ţ���߽�Ϊ0,����ʱ�����У��ڱ߽�Ϊ1�����Զ���ڱ߽磬�߽���Ŵ�1��ʼ��ţ���˳ʱ�����У��߽��Ҫ�������
};

//��ά�������ݽṹ
struct BEAM_FIBRE_GEO
{
	BEAM_FIBRE_GEO() :FibreH2(0), FibreH3(0), FibreArea(0) {}
	BEAM_FIBRE_GEO(float H2, float H3, float Area) :FibreH2(H2), FibreH3(H3), FibreArea(Area) {}
	float FibreH2, FibreH3, FibreArea; //��ά�����������������������������ԭ�㣨�������ӽ��棩���Ѿ������ӽ���ƫ�ľ�
};

//����������壬��λ����
struct GEO_RECT	//ʵ�ľ���
{
	float B,H;  //������B������߶�H
};

struct GEO_BOX		//���ľ���
{
	float Bs,Hs,tf1,tf2,tw1,tw2; //�����ܿ��B�������ܸ߶�H������Ե���tf1,����Ե���tf2,�󸹰���tw1,�Ҹ�����tw2
};

struct GEO_CIRC	//ʵ��Բ��
{
	float D;	//ֱ��D
};

struct GEO_PIPE	//����Բ��
{
	float Ds,tw; //��ֱ��D���ں�tw
};

struct GEO_I	//������
{
	float Hs,tw,B1,tf1,B2,tf2;  //�����ܸ߶�Hs��������tw1������Ե���B1������Ե���tf1������Ե���B2������Ե���tf2
};

struct GEO_CROSS	//ʮ�ֹ���
{
	//�������ܸ߶�H1�������θ�����tw1������������Ե���B1������������Ե���tf1������������Ե���B2������������Ե���tf2��
	float H1,tw1,B1,tf1,B2,tf2;
	//�������ܸ߶�H2�������θ�����tw2������������Ե���B3������������Ե���tf3������������Ե���B4������������Ե���tf4
	float H2,tw2,B3,tf3,B4,tf4;
};

struct GEO_CRISS	//ʮ����
{
	//L"������(m)",L"����߶�(m)",L"��Ե�ϱ߾�(m)",L"��Ե���(m)",L"��Ե����(m)",L"��Ե�ҿ��(m)",
	float B,H,U,T,D,F;
};

struct GEO_REGPOLY	//�������
{
	//L"���Բֱ��(m)",L"����α���"
	float B,N;
};

struct GEO_CHANNEL	//����
{
	//L"������(m)",L"�����ܸ߶�(m)",L"����Ե���(m��Ϊ+)",L"����Ե���(m)",L"����Ե���(m��Ϊ+)",L"����Ե���(m)",
	float B,H,U,T,D,F;
};

struct GEO_DBLCHANNEL	//˫����
{
	//L"������(m)",L"�����ܸ߶�(m)",L"����Ե���(m����+)",L"��Ե���(m)",L"����Ե���(m����+)",L"֫����С���(m)",
	float B,H,U,T,D,F;
};

struct GEO_TRAPEZOID	//����
{
	//L"���εױ߿��(m)",L"�����ܸ߶�(m)",L"���ϱ��쳤(m����+)",L"���ϱ��쳤(m����+)",
	float B,H,T,F;
};

struct GEO_L	//L��
{
	//L"������(m)",L"�����ܸ߶�(m��Ϊ+)",L"��Ե���(m��Ϊ+)",L"��Ե���(m)",
	float B,H,D,F;
};

struct GEO_T	//T��
{
	//L"������(m)",L"�����ܸ߶�(m��Ϊ+)",L"��Ե���(m)",L"��Ե���(m)",
	float B,H,D,F;
};

struct GEO_HANLINHAI_OUTER  //���ֺ� ��
{
	//float B, H, D, d, tc, ca, a, b;    //������B���߶�H���⾶D�����d���������Ե�����������Ե��������Ե����tc���ֹ����Ե�����������Ե���� ca
										//�˱��ο��ı߳� a���˱��ο��ı߳�b
	float B, H, D, t, b1, h1, hf1, hf2, tc1, tc2, ac1, ac2, ac3, ac4;
};

struct GEO_HANLINHAI_INNERSTEEL		//���ֺ��ĸ��ֹ�
{
	float B, H, D, t, ac1, ac2, ac3, ac4;
};

struct GEO_HANLINHAI_INNERCONC		//���ֺ��ĸ�������
{
//	float B, H, D, d, ca;
	float B, H, D, t, ac1, ac2, ac3, ac4;
};

struct GEO_DOUBLELIMBS_H	//˫֫H����
{
	//L"�����ܸ߶�(m)",L"����Ե���(m)",L"����Ե���(m)",L"����Ե���(m)",L"����Ե���(m)",L"����1���(m)",,L"����2���(m)"L"��֫����(m)��L"��֫����(m)",
	float H, B1, tf1,tw1, d1;
};

struct GEO_FOURLIMBS_L	//��֫L��
{
	//L"��Ե���",L"�����ܸ߶�(m)",L"��Ե���(m)",L"������(m)",L"����֫����(m)",L"����֫����(m)"
	float D, H, F, B,d1,d2;
};

struct GEO_H_ADD_PLATE	//H���� + ��
{
	//L"�����ܸ߶�(m)",L"����Ե���(m)",L"����Ե���(m)",L"����Ե���(m)",L"����Ե���(m)",L"����1���(m)",,L"����2���(m)"L"�Ӿ�����(m)��L"�Ӿ�����(m)",
	float H, B1, tf1, tw1, ts,Bs;
};

struct GEO_DOUBLELIMBS_L	//˫֫L��
{
	//L"��Ե���",L"�����ܸ߶�(m)",L"��Ե���(m)",L"������(m)",L"���(m)""
	float D, H, F, B, d1;
};

struct GEO_THREELIMBS_PIPE  // ��֫Բ�ܸ���
{
	//L"����߶�",L"������(m)",L"��ֱ��(m)",L"�ں�(m)"
	float  H, B, Ds, tw;
};

struct GEO_RECT_VAR //�����
{
	//L"������(m)",L"����߶�1(m)",L"����߶�2(m)",
	float B,H1,H2;
};

struct GEO_LINE	//һ���Σ�����
{
	float y1,z1,y2,z2,t;  //�ֲ�����: ���y���꣬���z���꣬�յ�y���꣬�յ�z���꣬���
};

struct GEO_REBAR	//�ֽ��
{
	float y,z,d;  //�ֲ����꣬y���꣬ z���ֱ꣬����m��
};

struct GEO_CONC	//��������ά��
{
	float y,z,area;  //�ֲ����꣬y���꣬ z���꣬�����m^2��
};

struct GEO_STEEL	//����ά��
{
	float y,z,area;  //�ֲ����꣬y���꣬ z���꣬�����m^2��
};

//����������ʹ���,1-��������2-����ְ��������3-˫��ְ��������4-���ְ�
enum PALTESECTION_MAT_TYPE 
{
	PALTESECTION_MAT_TYPE_NONE=0,	//�޲���
	PALTESECTION_MAT_TYPE_CONC=1,	//������
	PALTESECTION_MAT_TYPE_SRC=2,		//����ְ������
	PALTESECTION_MAT_TYPE_CFT=3,		//˫��ְ������
	PALTESECTION_MAT_TYPE_ST=4,			//���ְ�
	PALTESECTION_MAT_TYPE_CONCHOLLOW=5,			//˫�������
	PALTESECTION_MAT_TYPE_STHOLLOW=6,			//˫��ְ�
};


//  �ӹ̷������� ��ҵ�� 2023��5��5��
enum REINFORCED_METHOD
{
	METHOD_UNKNOWN = -1,				//��Ч

	// ��
	BEAM_METHOD_ENLARGED_SECTION = 0,		//������淨
	BEAM_METHOD_DISPLACEMENT_CONCRETE = 1,	//�û���������
	BEAM_METHOD_WRAPPED_SECTION_STEEL = 2,	//����͸շ�
	BEAM_METHOD_PASTE_STELL_PLATE = 3,		//�����ְ巨
	BEAM_METHOD_PASTE_FIBER = 4,			//������ά��

	// ��
	PILLAR_METHOD_ENLARGED_SECTION = 5,		//������淨
	PILLAR_METHOD_DISPLACEMENT_CONCRETE = 6,	//�û���������
	PILLAR_METHOD_WRAPPED_SECTION_STEEL = 7,	//����͸շ�
	PILLAR_METHOD_PASTE_STELL_PLATE = 8,		//�����ְ巨
	PILLAR_METHOD_PASTE_FIBER = 9,				//������ά��

};

//  �ӹ̽��淽������ ��ҵ�� 2023��5��5��
enum SUBSECTION_REINFORCED_TYPE
{
	REINFORCED_TYPE_UNKNOWN = -1,				//��Ч

	// ��
	BEAM_ENLARGED_SECTION_TYPE = 0,		//�������
	BEAM_DISPLACEMENT_CONCRETE_TYPE = 1,	//�û�������
	BEAM_WRAPPED_SECTION_STEEL_TYPE = 2,	//����͸�
	BEAM_PASTE_STELL_PLATE_TYPE = 3,		//�����ְ�
	BEAM_PASTE_FIBE_TYPE = 4,				//������ά

	// ��
	PILLAR_ENLARGED_SECTION_TYPE = 5,		//�������
	PILLAR_DISPLACEMENT_CONCRETE_TYPE = 6,	//�û�������
	PILLAR_WRAPPED_SECTION_STEE_TYPE = 7,	//����͸�
	PILLAR_PASTE_STELL_PLATE_TYPE = 8,		//�����ְ�
	PILLAR_PASTE_FIBER_TYPE = 9,			//������ά

};



// ���ӹ̷����������� ��ҵ�� 2023��5��5���壬��λ����
struct BEAM_ENLARGED_SECTION	//������淨
{
	float B, H1, H2;  //������B�����ӣ�����H1������, ����H2������
};

struct BEAM_DISPLACEMENT_CONCRETE		//�û���������
{
	float H1, H2; //�����û����H1�� �����û����H2
};

struct BEAM_WRAPPED_SECTION_STEEL		//����ְ巨
{
	float L1, L2, T1, L3, L4, T2, B, T3, D; //�ײ��Ǹֵĳߴ�:Y��L1�� X��L2�� ���T1�� �����Ǹֵĳߴ�:Y��L3�� X��L4�� ���T2�� ������Ϣ�����B�����T3�� ���D
};

struct BEAM_PASTE_STELL_PLATE		//�����ְ巨
{
	// �����ְ��ȣ������ְ��ȣ����׸ְ��ȣ����׸ְ��ȣ�����ճ�������ȣ�����ճ�������ȣ� ����ճ��������
	float B1, T1, B2, T2, B3, T3, D; 
};

struct BEAM_PASTE_FIBER		//������ά��
{
	//�������ϲĲ������������ϲĲ�����ȣ����׸��ϲĲ��������׸��ϲĲ�����ȣ����ิ�ϲĲ��������ิ�ϲĲ�����ȣ����ิ�ϲļ�࣬���ϲĵ�ÿ����,��Ҫ�� 
	float N1, B1, N2, B2, N3, B3, D, T; 
	float iComponentType;  // 0��һ�㹹���� 1����Ҫ����
};


// ���ӹ̷����������� ��ҵ�� 2023��5��5���壬��λ����
struct PILLAR_ENLARGED_SECTION	//������淨
{
	float B1,B2, H1, H2;  //������B1�����ӣ�������B2������,������H1������, ������H2������
};

struct PILLAR_DISPLACEMENT_CONCRETE		//�û���������
{
	float B, H; //������B���û����B�� ������H���û����H
};

struct PILLAR_WRAPPED_SECTION_STEEL		//����ְ巨
{
	float  L1, L2, T1, B, T, D; ////�Ǹֵĳߴ�:Y��L1�� X��L2�� ���T1��׺����Ϣ�����B�����T�� ���D
};

struct PILLAR_PASTE_STELL_PLATE		//�����ְ巨
{
	float B, H, T; // ����B��ְ��ȣ� ����H��ְ���, ���T
};

struct PILLAR_PASTE_FIBER		//������ά��
{
	float B1, H, B2, D, N, T; //����B1���������Ͽ��, ����H1���������Ͽ��, ���ι����B2, ���ι����ļ��D, ���ϲĲ���N, ���ϲĵ�ÿ����T,��Ҫ�� 
	float iComponentType; // 0��һ�㹹���� 1����Ҫ����
};


//  ��ǽ�ӹ̷������� ��ҵ�� 2023��5��5��
enum PLATE_REINFORCED_METHOD
{
	PLATE_METHOD_UNKNOWN = -1,				//��Ч

	// ��
	PLATE_METHOD_ENLARGED_SECTION = 0,		//������淨
	PLATE_METHOD_PASTE_STELL_PLATE = 1,		//�����ְ巨
	PLATE_METHOD_PASTE_FIBER = 2,			//������ά��

	// ǽ
	WALL_METHOD_ENLARGED_SECTION = 3,		//������淨
	WALL_METHOD_PASTE_STELL_PLATE = 4,		//�����ְ巨
};

// ǽ��ӹ̲���
enum PALTESECTION_REINFORCED_MAT_TYPE
{
	PALTESECTION_REINFORCED_MAT_TYPE_NONE = 0,	//�޲���
	PALTESECTION_REINFORCED_MAT_TYPE_CONC = 1,	//������
	PALTESECTION_REINFORCED_MAT_TYPE_ST = 2,	//���ְ�
	PALTESECTION_REINFORCED_MAT_TYPE_FIBER = 3,	//��ά
};

// ��ӹ̷����������� ��ҵ��  2023��10��18���壬��λ����
struct PLATE_ENLARGED_SECTION	//������淨
{
	float H1, H2;  // �嶥H1������, ���H2������
};

struct PLATE_PASTE_STELL_PLATE		//�����ְ巨
{
	// �ְ�ļӹ̷��� �嶥�ְ��ȣ��嶥�ְ��ȣ��嶥�ְ��࣬�ְ�ļӹ̷��� �嶥�ְ��ȣ��嶥�ְ��ȣ��嶥�ְ���
	float Location1, B1, T1, D1, Location2, B2, T2, D2; // Location1 �� Location2 ��-1��0��1��2��ʾ��-1��ʾ���ӹ̣� 0 ��ʾX�� 1��ʾY��2��ʾ ��ʾ˫��
};

struct PLATE_PASTE_FIBER		//������ά��
{
	//���׸��ϲĲ��������׸��ϲĲ�����ȣ��������ϲĲ������������ϲĲ�����ȣ����ิ�ϲĲ��������ิ�ϲĲ�����ȣ����ิ�ϲļ�࣬���ϲĵ�ÿ����
	float N1, B1, N2, B2, N3, B3, D, T;
};

// ǽ�ӹ̷����������� ��ҵ�� 2023��10��18���壬��λ����
struct WALL_ENLARGED_SECTION	//������淨
{
	float B1, B2;  // ǽ1������, ǽ2������
};

struct WALL_PASTE_STELL_PLATE		//�����ְ巨
{
	// ǽ1��ְ��ȣ�ǽ1��ְ��ȣ�ǽ1��ְ��࣬  ǽ2�ְ��ȣ� ǽ2�ְ��ȣ� ǽ2�ְ���
	float B1, T1, D1, B2, T2, D2;
};