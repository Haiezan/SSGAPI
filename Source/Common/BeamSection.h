#pragma once
#include "HeadDefine.h"
#include "..\Common\SysPara.h"
#include "ASCFile.h"
#include "SectionBase.h"
#include <afxtempl.h>

#define gSectionTypeNum 5	//��������������
#define gPlateSectionNum 3	//���������������

//Ԥ����Ľ�����״����
//ȥ���������BEAM_ARBITRARY��PILLAR_ARBITRARY�ͱ����������BEAM_RC_VAR��PILLAR_RC_VAR
#define gSectionShapeNum 71   

#define Sys_SubSectionShapeNum 16 //Ԥ������ӽ�����״����

//������ν����Ťת���Ծ�J1���Զ��ж�B,H��С
extern "C" _SSG_DLLIMPEXP float J1_Rect(float B,float H);

//���ݲ������Ƶõ���������
extern "C" _SSG_DLLIMPEXP SECTION_MAT_TYPE GetSecType(const CString &sConc,const CString &sRebar,const CString &sSteel);

//��ģ��õ���������
extern "C" _SSG_DLLIMPEXP SECTION_MAT_TYPE GetSectionMatType(SECTION_SHAPE iSectionShape);

//�õ�ģ����ȫ����������gSectionShapeTable�е����,ʧ�ܷ���-1
extern "C" _SSG_DLLIMPEXP int GetSectionPropIndex(SECTION_SHAPE iSectionShape);

//�ɲ���������������
extern "C" _SSG_DLLIMPEXP PLATE_SECTION_MAT_TYPE *GetPlateSectionType(SECTION_MAT_TYPE MatType);

static SECTION_TYPE_PROP_TABLE gSectionTypeTable[gSectionTypeNum]={
#ifdef _SIMPLIFIED_CHINESE
	SECTION_MAT_TYPE_RC,	 L"RC",	L"�ֽ������",
	SECTION_MAT_TYPE_ST,	 L"ST",	L"�ֲ�",
	SECTION_MAT_TYPE_CFT,	 L"CFT",	L"�ֹܻ�����",		//Concrete Filled Tube
	SECTION_MAT_TYPE_SRC,	 L"SRC",	L"�ֹǻ�����",		//Steel Reinforced Concrete
	SECTION_MAT_TYPE_REBAR,	 L"REBAR",	L"�ֽ�",
#else
	SECTION_MAT_TYPE_RC,	 L"RC",	L"Reinforced Concrete",
	SECTION_MAT_TYPE_ST,	 L"ST",	L"Section Steel",
	SECTION_MAT_TYPE_CFT,	 L"CFT",	L"Concrete Filled Tube",
	SECTION_MAT_TYPE_SRC,	 L"SRC",	L"Steel Reinforced Concrete",
	SECTION_MAT_TYPE_REBAR,	 L"REBAR",	L"Rebar",
#endif
};

//��������Ͷ�Ӧ������
static PLATE_SECTION_MAT_TYPE gPlateSectionTypeTable[gPlateSectionNum]=
{
#ifdef _SIMPLIFIED_CHINESE
	SECTION_MAT_TYPE_RC, L"RC",	L"�ֽ������",
	SECTION_MAT_TYPE_ST, L"ST",	L"�ְ�",
	SECTION_MAT_TYPE_SRC,L"SRC",L"�ְ������",  
#else
	SECTION_MAT_TYPE_RC, L"RC",	L"Reforced Concrete",
	SECTION_MAT_TYPE_ST, L"ST",	L"Steel Plate",
	SECTION_MAT_TYPE_SRC,L"SRC",L"Steel Reinforced Concrete",
#endif
};

//�ӽ������ͱ�
static SUBSECTIONTYPE_PROP_TABLE gSubSectionTypePropTable[]={
#ifdef _SIMPLIFIED_CHINESE
	SUBSECTION_MAT_TYPE_CONC, L"RC",	L"�ֽ������",  //������     
	SUBSECTION_MAT_TYPE_ST, L"ST",	L"�ֲ�",	//�ֲ�
	SUBSECTION_MAT_TYPE_REBAR, L"REBAR",	L"�ֽ�",	//�ֽ�

#else
	SUBSECTION_MAT_TYPE_CONC, L"RC",	L"Reinforced Concrete",  //������     
	SUBSECTION_MAT_TYPE_ST, L"ST",	L"Section Steel",	//�ֲ�
	SUBSECTION_MAT_TYPE_REBAR, L"REBAR",	L"Rebar",	//�ֽ�
#endif
};

static SECTION_SHAPE_PROP_TABLE gSectionShapeTable[gSectionShapeNum]=
{
#ifdef _SIMPLIFIED_CHINESE
	//������,0-99
	//BEAM_ARBITRARY		,	   L"������Ͻ����������", SECTION_MAT_TYPE_RC,

	BEAM_RC_RECT		,	L"��������",SECTION_MAT_TYPE_RC,				SUBSHAPE_RECT,		SUBSHAPE_UNKNOWN,	
	BEAM_ST_BOX			,	L"���ֹ���",SECTION_MAT_TYPE_ST,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,	
	BEAM_ST_I			,	L"�����͸���",SECTION_MAT_TYPE_ST,				SUBSHAPE_I,			SUBSHAPE_UNKNOWN,
	BEAM_CFT_BOX_RECT	,	L"���ֹܻ�������",SECTION_MAT_TYPE_CFT,			SUBSHAPE_BOX,		SUBSHAPE_RECT,
	BEAM_SRC_RECT_I		,	L"������-�ֹǻ�������",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_I,
	BEAM_RC_CRISS		,	L"ʮ���ͻ�������",SECTION_MAT_TYPE_RC,			SUBSHAPE_CRISS,		SUBSHAPE_UNKNOWN,
	
	BEAM_RC_I			,	L"�����ͻ�������",SECTION_MAT_TYPE_RC,			SUBSHAPE_I,			SUBSHAPE_UNKNOWN,
	BEAM_RC_CIRC		,	L"Բ�λ�������",SECTION_MAT_TYPE_RC,			SUBSHAPE_CIRC,		SUBSHAPE_UNKNOWN,
	BEAM_RC_REGPOLY		,	L"������λ�������",SECTION_MAT_TYPE_RC,		SUBSHAPE_REGPOLY,	SUBSHAPE_UNKNOWN,
	BEAM_RC_CHANNEL		,	L"���ͻ�������",SECTION_MAT_TYPE_RC,			SUBSHAPE_CHANNEL,	SUBSHAPE_UNKNOWN,
	BEAM_RC_BOX			,	L"���ιܻ�������",SECTION_MAT_TYPE_RC,			SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	BEAM_RC_DBLCHANNEL	,	L"˫���ͻ�������",SECTION_MAT_TYPE_RC,			SUBSHAPE_DBLCHANNEL,SUBSHAPE_UNKNOWN,
	BEAM_RC_CROSS		,	L"ʮ�ֹ��ͻ�������",SECTION_MAT_TYPE_RC,		SUBSHAPE_CROSS,		SUBSHAPE_UNKNOWN,
	BEAM_RC_TRAP		,	L"���λ�������",SECTION_MAT_TYPE_RC,			SUBSHAPE_TRAPEZOID,	SUBSHAPE_UNKNOWN,

	BEAM_CFT_PIPE_CIRC	,	L"Բ�ֹܻ�������",SECTION_MAT_TYPE_CFT,			SUBSHAPE_PIPE,		SUBSHAPE_CIRC,

	BEAM_SRC_RECT_BOX	,	L"���ֹ�-�ֹǻ���������",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_BOX,
	BEAM_SRC_RECT_CROSS	,	L"ʮ�ֹ���-�ֹǻ���������",SECTION_MAT_TYPE_SRC,SUBSHAPE_RECT,		SUBSHAPE_CROSS,

	//BEAM_RC_VAR		,	L"��������������",SECTION_MAT_TYPE_RC,
	BEAM_RC_L			,	L"L�ͻ�������",SECTION_MAT_TYPE_RC,				SUBSHAPE_L,			SUBSHAPE_UNKNOWN,

	BEAM_SRC_RECT_PIPE	,	L"Բ�͸ֹ�-�ֹǻ���������",SECTION_MAT_TYPE_SRC,SUBSHAPE_RECT,		SUBSHAPE_PIPE,

	BEAM_SRC_CIRC_I		,	L"������-�ֹǻ�����Բ��",SECTION_MAT_TYPE_SRC,	SUBSHAPE_CIRC,		SUBSHAPE_I,
	BEAM_SRC_CIRC_PIPE	,	L"Բ�ֹ�-�ֹǻ�����Բ��",SECTION_MAT_TYPE_SRC,	SUBSHAPE_CIRC,		SUBSHAPE_PIPE,
	BEAM_SRC_CIRC_CROSS	,	L"ʮ�ֹ���-�ֹǻ�����Բ��",SECTION_MAT_TYPE_SRC,SUBSHAPE_CIRC,		SUBSHAPE_CROSS,

	BEAM_RC_T			,	L"T�ͻ�������",SECTION_MAT_TYPE_RC,				SUBSHAPE_T,			SUBSHAPE_UNKNOWN,
	BEAM_RC_PIPE		,	L"������Բ����",SECTION_MAT_TYPE_RC,			SUBSHAPE_PIPE,		SUBSHAPE_UNKNOWN,
	BEAM_ST_PIPE		,	L"Բ�ֹ���",SECTION_MAT_TYPE_ST,			SUBSHAPE_PIPE,		SUBSHAPE_UNKNOWN,
	BEAM_ST_RECT		,	L"���θ���",SECTION_MAT_TYPE_ST,				SUBSHAPE_RECT,		SUBSHAPE_UNKNOWN,  //�Ǳ��� 2015.5.5
	BEAM_ST_CIRC		,	L"Բ�θ���",SECTION_MAT_TYPE_ST,			SUBSHAPE_CIRC,		SUBSHAPE_UNKNOWN,  //�Ǳ��� 2015.5.5

	BEAM_ST_CROSS	    ,	L"ʮ�ֹ��͸���",SECTION_MAT_TYPE_ST,			SUBSHAPE_CROSS,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	BEAM_ST_CRISS	    ,	L"ʮ���͸���",SECTION_MAT_TYPE_ST,			SUBSHAPE_CRISS,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	BEAM_ST_REGPOLY   ,	L"������θ���",SECTION_MAT_TYPE_ST,		SUBSHAPE_REGPOLY,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	BEAM_ST_CHANNEL	 ,	L"���͸���",SECTION_MAT_TYPE_ST,			SUBSHAPE_CHANNEL,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	BEAM_ST_DBLCHANNEL ,	L"˫���͸���",SECTION_MAT_TYPE_ST,			SUBSHAPE_DBLCHANNEL,	SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	BEAM_ST_TRAP	     ,	L"���θ���",SECTION_MAT_TYPE_ST,			SUBSHAPE_TRAPEZOID,	SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	BEAM_ST_L	    ,	L"L�͸���",SECTION_MAT_TYPE_ST,			SUBSHAPE_L,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6	
	BEAM_ST_T	    ,	L"T�͸���",SECTION_MAT_TYPE_ST,			SUBSHAPE_T,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6


//������,100-199
//PILLAR_ARBITRARY	,	L"������Ͻ����������",SECTION_MAT_TYPE_RC,

	PILLAR_RC_RECT		,	L"����������",SECTION_MAT_TYPE_RC,				SUBSHAPE_RECT,		SUBSHAPE_UNKNOWN,
	PILLAR_RC_CIRC		,	L"������Բ��",SECTION_MAT_TYPE_RC,				SUBSHAPE_CIRC,		SUBSHAPE_UNKNOWN,

	PILLAR_ST_BOX		,	L"���ֹ���",SECTION_MAT_TYPE_ST,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	PILLAR_ST_PIPE		,	L"Բ�ֹ���",SECTION_MAT_TYPE_ST,				SUBSHAPE_PIPE,		SUBSHAPE_UNKNOWN,
	PILLAR_ST_I			,	L"�����͸���",SECTION_MAT_TYPE_ST,				SUBSHAPE_I,			SUBSHAPE_UNKNOWN,
	PILLAR_ST_CROSS		,	L"ʮ�ֹ��͸���",SECTION_MAT_TYPE_ST,			SUBSHAPE_CROSS,		SUBSHAPE_UNKNOWN,

	PILLAR_CFT_BOX_RECT ,	L"���ֹܻ�������",SECTION_MAT_TYPE_CFT,			SUBSHAPE_BOX,		SUBSHAPE_RECT,
	PILLAR_CFT_PIPE_CIRC,	L"Բ�ֹܻ�������",SECTION_MAT_TYPE_CFT,			SUBSHAPE_PIPE,		SUBSHAPE_CIRC,

	PILLAR_SRC_RECT_BOX		,L"���ֹ�-�ֹǻ�������",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_BOX,
	PILLAR_SRC_RECT_I		,L"������-�ֹǻ���������",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_I,
	PILLAR_SRC_RECT_CROSS	,L"ʮ�ֹ���-�ֹǻ���������",SECTION_MAT_TYPE_SRC,SUBSHAPE_RECT,		SUBSHAPE_CROSS,

	PILLAR_SRC_CIRC_PIPE,	L"Բ�ֹ�-�ֹǻ�������",SECTION_MAT_TYPE_SRC,	SUBSHAPE_CIRC,		SUBSHAPE_PIPE,
	PILLAR_SRC_CIRC_I	,	L"������-�ֹǻ�����Բ��",SECTION_MAT_TYPE_SRC,	SUBSHAPE_CIRC,		SUBSHAPE_I,
	PILLAR_SRC_CIRC_CROSS,	L"ʮ�ֹ���-�ֹǻ�����Բ��",SECTION_MAT_TYPE_SRC,SUBSHAPE_CIRC,		SUBSHAPE_CROSS,
	PILLAR_RC_CRISS	    ,	L"ʮ���ͻ�������",SECTION_MAT_TYPE_RC,			SUBSHAPE_CRISS,		SUBSHAPE_UNKNOWN,

	PILLAR_RC_I			,	L"�����ͻ�������",SECTION_MAT_TYPE_RC,			SUBSHAPE_I,			SUBSHAPE_UNKNOWN,
	PILLAR_RC_REGPOLY	,	L"������λ�������",SECTION_MAT_TYPE_RC,		SUBSHAPE_REGPOLY,	SUBSHAPE_UNKNOWN,
	PILLAR_RC_CHANNEL	,	L"���ͻ�������",SECTION_MAT_TYPE_RC,			SUBSHAPE_CHANNEL,	SUBSHAPE_UNKNOWN,
	PILLAR_RC_BOX		,	L"���ιܻ�������",SECTION_MAT_TYPE_RC,			SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	PILLAR_RC_DBLCHANNEL,	L"˫���ͻ�������",SECTION_MAT_TYPE_RC,			SUBSHAPE_DBLCHANNEL,SUBSHAPE_UNKNOWN,
	PILLAR_RC_CROSS		,	L"ʮ�ֹ��ͻ�������",SECTION_MAT_TYPE_RC,		SUBSHAPE_CROSS,		SUBSHAPE_UNKNOWN,
	PILLAR_RC_TRAP		,	L"���λ�������",SECTION_MAT_TYPE_RC,			SUBSHAPE_TRAPEZOID,	SUBSHAPE_UNKNOWN,

	//PILLAR_RC_VAR		,	L"��������������",SECTION_MAT_TYPE_RC,
	PILLAR_RC_L			,	L"L�ͻ�������",SECTION_MAT_TYPE_RC,				SUBSHAPE_L,			SUBSHAPE_UNKNOWN,
	PILLAR_RC_PIPE		,	L"������Բ����",SECTION_MAT_TYPE_RC,			SUBSHAPE_PIPE,		SUBSHAPE_UNKNOWN,
	PILLAR_SRC_RECT_PIPE,		L"Բ�ֹ�-�ֹǻ���������",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_PIPE,
	PILLAR_RC_T			,	L"T�ͻ�������",SECTION_MAT_TYPE_RC,				SUBSHAPE_T,			SUBSHAPE_UNKNOWN,  //�Ǳ��� 2015.5.5
	PILLAR_ST_RECT		,	L"���θ���",SECTION_MAT_TYPE_ST,				SUBSHAPE_RECT,		SUBSHAPE_UNKNOWN,  //�Ǳ��� 2015.5.5
	PILLAR_ST_CIRC		,	L"Բ�θ���",SECTION_MAT_TYPE_ST,			SUBSHAPE_CIRC,		SUBSHAPE_UNKNOWN,  //�Ǳ��� 2015.5.5

	PILLAR_ST_CRISS	    ,	L"ʮ���͸���",SECTION_MAT_TYPE_ST,			SUBSHAPE_CRISS,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	PILLAR_ST_REGPOLY	    ,	L"������θ���",SECTION_MAT_TYPE_ST,			SUBSHAPE_REGPOLY,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	PILLAR_ST_CHANNEL	    ,	L"���͸���",SECTION_MAT_TYPE_ST,			SUBSHAPE_CHANNEL,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	PILLAR_ST_DBLCHANNEL    ,	L"˫���͸���",SECTION_MAT_TYPE_ST,			SUBSHAPE_DBLCHANNEL,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	PILLAR_ST_TRAP	    ,	L"���θ���",SECTION_MAT_TYPE_ST,			SUBSHAPE_TRAPEZOID,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	PILLAR_ST_L	    ,		L"L�͸���",SECTION_MAT_TYPE_ST,			SUBSHAPE_L,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6	
	PILLAR_ST_T	    ,		L"T�͸���",SECTION_MAT_TYPE_ST,			SUBSHAPE_T,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6

	AUX_REBAR_BOX		,	L"��������",SECTION_MAT_TYPE_REBAR,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
#else
	//������,0-99
	//BEAM_ARBITRARY		,	   L"������Ͻ����������", SECTION_MAT_TYPE_RC,

	BEAM_RC_RECT		,	L"Concrete Rectangular Beam",SECTION_MAT_TYPE_RC,				SUBSHAPE_RECT,		SUBSHAPE_UNKNOWN,	
	BEAM_ST_BOX			,	L"Steel Box Beam",SECTION_MAT_TYPE_ST,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,	
	BEAM_ST_I			,	L"Steel I-shaped Beam",SECTION_MAT_TYPE_ST,				SUBSHAPE_I,			SUBSHAPE_UNKNOWN,
	BEAM_CFT_BOX_RECT	,	L"Concrete Filled Steel Box Beam",SECTION_MAT_TYPE_CFT,			SUBSHAPE_BOX,		SUBSHAPE_RECT,
	BEAM_SRC_RECT_I		,	L"I-shaped Steel Reinforced Concrete Rectangular Beam",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_I,
	BEAM_RC_CRISS		,	L"Concrete Cross-shaped Beam",SECTION_MAT_TYPE_RC,			SUBSHAPE_CRISS,		SUBSHAPE_UNKNOWN,
	
	BEAM_RC_I			,	L"Concrete I-shaped Beam",SECTION_MAT_TYPE_RC,			SUBSHAPE_I,			SUBSHAPE_UNKNOWN,
	BEAM_RC_CIRC		,	L"Concrete Circular Beam",SECTION_MAT_TYPE_RC,			SUBSHAPE_CIRC,		SUBSHAPE_UNKNOWN,
	BEAM_RC_REGPOLY		,	L"Concrete Regular Polygon Beam",SECTION_MAT_TYPE_RC,		SUBSHAPE_REGPOLY,	SUBSHAPE_UNKNOWN,
	BEAM_RC_CHANNEL		,	L"Concrete Channel Beam",SECTION_MAT_TYPE_RC,			SUBSHAPE_CHANNEL,	SUBSHAPE_UNKNOWN,
	BEAM_RC_BOX			,	L"Concrete Box Beam",SECTION_MAT_TYPE_RC,			SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	BEAM_RC_DBLCHANNEL	,	L"Concrete Double Channel Beam",SECTION_MAT_TYPE_RC,			SUBSHAPE_DBLCHANNEL,SUBSHAPE_UNKNOWN,
	BEAM_RC_CROSS		,	L"Concrete Cross-I-shaped Beam",SECTION_MAT_TYPE_RC,		SUBSHAPE_CROSS,		SUBSHAPE_UNKNOWN,
	BEAM_RC_TRAP		,	L"Concrete Trapezoidal Beam",SECTION_MAT_TYPE_RC,			SUBSHAPE_TRAPEZOID,	SUBSHAPE_UNKNOWN,

	BEAM_CFT_PIPE_CIRC	,	L"Concrete Filled Steel Pipe Beam",SECTION_MAT_TYPE_CFT,			SUBSHAPE_PIPE,		SUBSHAPE_CIRC,

	BEAM_SRC_RECT_BOX	,	L"Box Steel Reinforced Concrete Rectangular Beam",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_BOX,
	BEAM_SRC_RECT_CROSS	,	L"Cross-I-shaped Steel Reinforced Concrete Rectangular Beam",SECTION_MAT_TYPE_SRC,SUBSHAPE_RECT,		SUBSHAPE_CROSS,

	//BEAM_RC_VAR		,	L"��������������",SECTION_MAT_TYPE_RC,
	BEAM_RC_L			,	L"Concrete L-shaped Beam",SECTION_MAT_TYPE_RC,				SUBSHAPE_L,			SUBSHAPE_UNKNOWN,

	BEAM_SRC_RECT_PIPE	,	L"Pipe Steel Reinforced Concrete Rectangular Beam",SECTION_MAT_TYPE_SRC,SUBSHAPE_RECT,		SUBSHAPE_PIPE,

	BEAM_SRC_CIRC_I		,	L"I-shaped Steel Reinforced Concrete Circular Beam",SECTION_MAT_TYPE_SRC,	SUBSHAPE_CIRC,		SUBSHAPE_I,
	BEAM_SRC_CIRC_PIPE	,	L"Pipe Steel Reinforced Concrete Circular Beam",SECTION_MAT_TYPE_SRC,	SUBSHAPE_CIRC,		SUBSHAPE_PIPE,
	BEAM_SRC_CIRC_CROSS	,	L"Cross-I-shaped Steel Reinforced Concrete Circular Beam",SECTION_MAT_TYPE_SRC,SUBSHAPE_CIRC,		SUBSHAPE_CROSS,

	BEAM_RC_T			,	L"Concrete T-shaped Beam",SECTION_MAT_TYPE_RC,				SUBSHAPE_T,			SUBSHAPE_UNKNOWN,
	BEAM_RC_PIPE		,	L"Concrete Pipe Beam",SECTION_MAT_TYPE_RC,			SUBSHAPE_PIPE,		SUBSHAPE_UNKNOWN,
	BEAM_ST_PIPE		,	L"Steel Pipe Beam",SECTION_MAT_TYPE_ST,			SUBSHAPE_PIPE,		SUBSHAPE_UNKNOWN,
	BEAM_ST_RECT		,	L"Steel Rectangular Beam",SECTION_MAT_TYPE_ST,				SUBSHAPE_RECT,		SUBSHAPE_UNKNOWN,  //�Ǳ��� 2015.5.5
	BEAM_ST_CIRC		,	L"Steel Circular Beam",SECTION_MAT_TYPE_ST,			SUBSHAPE_CIRC,		SUBSHAPE_UNKNOWN,  //�Ǳ��� 2015.5.5

	BEAM_ST_CROSS	    ,	L"Steel Cross-I-shaped Beam",SECTION_MAT_TYPE_ST,			SUBSHAPE_CROSS,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	BEAM_ST_CRISS	    ,	L"Steel Cross-shaped Beam",SECTION_MAT_TYPE_ST,			SUBSHAPE_CRISS,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	BEAM_ST_REGPOLY   ,	L"Steel Regular Polygon Beam",SECTION_MAT_TYPE_ST,		SUBSHAPE_REGPOLY,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	BEAM_ST_CHANNEL	 ,	L"Steel Channel Beam",SECTION_MAT_TYPE_ST,			SUBSHAPE_CHANNEL,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	BEAM_ST_DBLCHANNEL ,	L"Steel Double Channel Beam",SECTION_MAT_TYPE_ST,			SUBSHAPE_DBLCHANNEL,	SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	BEAM_ST_TRAP	     ,	L"Steel Trapezoidal Beam",SECTION_MAT_TYPE_ST,			SUBSHAPE_TRAPEZOID,	SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	BEAM_ST_L	    ,	L"Steel L-shaped Beam",SECTION_MAT_TYPE_ST,			SUBSHAPE_L,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6	
	BEAM_ST_T	    ,	L"Steel T-shaped Beam",SECTION_MAT_TYPE_ST,			SUBSHAPE_T,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6


//������,100-199
//PILLAR_ARBITRARY	,	L"������Ͻ����������",SECTION_MAT_TYPE_RC,

	PILLAR_RC_RECT		,	L"Concrete Rectangular Column",SECTION_MAT_TYPE_RC,				SUBSHAPE_RECT,		SUBSHAPE_UNKNOWN,
	PILLAR_RC_CIRC		,	L"Concrete Circular Column",SECTION_MAT_TYPE_RC,				SUBSHAPE_CIRC,		SUBSHAPE_UNKNOWN,

	PILLAR_ST_BOX		,	L"Steel Box Column",SECTION_MAT_TYPE_ST,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	PILLAR_ST_PIPE		,	L"Steel Pipe Column",SECTION_MAT_TYPE_ST,				SUBSHAPE_PIPE,		SUBSHAPE_UNKNOWN,
	PILLAR_ST_I			,	L"Steel I-shaped Column",SECTION_MAT_TYPE_ST,				SUBSHAPE_I,			SUBSHAPE_UNKNOWN,
	PILLAR_ST_CROSS		,	L"Steel Cross-I-shaped Column",SECTION_MAT_TYPE_ST,			SUBSHAPE_CROSS,		SUBSHAPE_UNKNOWN,

	PILLAR_CFT_BOX_RECT ,	L"Concrete Filled Steel Box Column",SECTION_MAT_TYPE_CFT,			SUBSHAPE_BOX,		SUBSHAPE_RECT,
	PILLAR_CFT_PIPE_CIRC,	L"Concrete Filled Steel Pipe Column",SECTION_MAT_TYPE_CFT,			SUBSHAPE_PIPE,		SUBSHAPE_CIRC,

	PILLAR_SRC_RECT_BOX		,L"Box Steel Reinforced Concrete Rectangular Column",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_BOX,
	PILLAR_SRC_RECT_I		,L"I-shaped Steel Reinforced Concrete Rectangular Column",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_I,
	PILLAR_SRC_RECT_CROSS	,L"Cross-I-shaped Steel Reinforced Concrete Rectangular Column",SECTION_MAT_TYPE_SRC,SUBSHAPE_RECT,		SUBSHAPE_CROSS,

	PILLAR_SRC_CIRC_PIPE,	L"Pipe Steel Reinforced Concrete Circular Column",SECTION_MAT_TYPE_SRC,	SUBSHAPE_CIRC,		SUBSHAPE_PIPE,
	PILLAR_SRC_CIRC_I	,	L"I-shaped Steel Reinforced Concrete Circular Column",SECTION_MAT_TYPE_SRC,	SUBSHAPE_CIRC,		SUBSHAPE_I,
	PILLAR_SRC_CIRC_CROSS,	L"Cross-I-shaped Steel Reinforced Concrete Circular Column",SECTION_MAT_TYPE_SRC,SUBSHAPE_CIRC,		SUBSHAPE_CROSS,
	PILLAR_RC_CRISS	    ,	L"Concrete Cross-shaped Column",SECTION_MAT_TYPE_RC,			SUBSHAPE_CRISS,		SUBSHAPE_UNKNOWN,

	PILLAR_RC_I			,	L"Concrete I-shaped Column",SECTION_MAT_TYPE_RC,			SUBSHAPE_I,			SUBSHAPE_UNKNOWN,
	PILLAR_RC_REGPOLY	,	L"Concrete Regular Polygon Column",SECTION_MAT_TYPE_RC,		SUBSHAPE_REGPOLY,	SUBSHAPE_UNKNOWN,
	PILLAR_RC_CHANNEL	,	L"Concrete Channel Column",SECTION_MAT_TYPE_RC,			SUBSHAPE_CHANNEL,	SUBSHAPE_UNKNOWN,
	PILLAR_RC_BOX		,	L"Concrete Box Column",SECTION_MAT_TYPE_RC,			SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
	PILLAR_RC_DBLCHANNEL,	L"Concrete Double Channel Column",SECTION_MAT_TYPE_RC,			SUBSHAPE_DBLCHANNEL,SUBSHAPE_UNKNOWN,
	PILLAR_RC_CROSS		,	L"Concrete Cross-I-shaped Column",SECTION_MAT_TYPE_RC,		SUBSHAPE_CROSS,		SUBSHAPE_UNKNOWN,
	PILLAR_RC_TRAP		,	L"Concrete Trapezoidal Column",SECTION_MAT_TYPE_RC,			SUBSHAPE_TRAPEZOID,	SUBSHAPE_UNKNOWN,

	//PILLAR_RC_VAR		,	L"��������������",SECTION_MAT_TYPE_RC,
	PILLAR_RC_L			,	L"Concrete L-shaped Column",SECTION_MAT_TYPE_RC,				SUBSHAPE_L,			SUBSHAPE_UNKNOWN,
	PILLAR_RC_PIPE		,	L"Concrete Pipe Column",SECTION_MAT_TYPE_RC,			SUBSHAPE_PIPE,		SUBSHAPE_UNKNOWN,
	PILLAR_SRC_RECT_PIPE,		L"Pipe Steel Reinforced Concrete Rectangular Column",SECTION_MAT_TYPE_SRC,	SUBSHAPE_RECT,		SUBSHAPE_PIPE,
	PILLAR_RC_T			,	L"Concrete T-shaped Column",SECTION_MAT_TYPE_RC,				SUBSHAPE_T,			SUBSHAPE_UNKNOWN,  //�Ǳ��� 2015.5.5
	PILLAR_ST_RECT		,	L"Steel Rectangular Column",SECTION_MAT_TYPE_ST,				SUBSHAPE_RECT,		SUBSHAPE_UNKNOWN,  //�Ǳ��� 2015.5.5
	PILLAR_ST_CIRC		,	L"Steel Circular Column",SECTION_MAT_TYPE_ST,			SUBSHAPE_CIRC,		SUBSHAPE_UNKNOWN,  //�Ǳ��� 2015.5.5

	PILLAR_ST_CRISS	    ,	L"Steel Cross-shaped Column",SECTION_MAT_TYPE_ST,			SUBSHAPE_CRISS,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	PILLAR_ST_REGPOLY	    ,	L"Steel Regular Polygon Column",SECTION_MAT_TYPE_ST,			SUBSHAPE_REGPOLY,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	PILLAR_ST_CHANNEL	    ,	L"Steel Channel Column",SECTION_MAT_TYPE_ST,			SUBSHAPE_CHANNEL,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	PILLAR_ST_DBLCHANNEL    ,	L"Steel Double Channel Column",SECTION_MAT_TYPE_ST,			SUBSHAPE_DBLCHANNEL,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	PILLAR_ST_TRAP	    ,	L"Steel Trapezoidal Column",SECTION_MAT_TYPE_ST,			SUBSHAPE_TRAPEZOID,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6
	PILLAR_ST_L	    ,		L"Steel L-shaped Column",SECTION_MAT_TYPE_ST,			SUBSHAPE_L,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6	
	PILLAR_ST_T	    ,		L"Steel T-shaped Column",SECTION_MAT_TYPE_ST,			SUBSHAPE_T,		SUBSHAPE_UNKNOWN,	//�Ǳ��� 2015.7.6

	AUX_REBAR_BOX		,	L"Auxiliary Member",SECTION_MAT_TYPE_REBAR,				SUBSHAPE_BOX,		SUBSHAPE_UNKNOWN,
#endif
};


//�ɽ�����״תΪ����������ϣ���ȡ����Ӧ����&����
extern "C" _SSG_DLLIMPEXP int GetStructTypeByShape(SECTION_SHAPE iShape);

//��ע��
class _SSG_DLLIMPEXP CLabel
{
public:
	void SetLabel(float a2,float a3,float b2,float b3,CString str)
	{
		A2=a2;
		A3=a3;
		B2=b2;
		B3=b3;
		Str=str;
	};

	//void Draw(CDC *pdc,DWORD color); //���Ʊ�ע���������ߡ���ע�ߡ�����
	void Read(CASCFile &fin);
	void Write(CASCFile &fout);

private:
	float A2,A3,B2,B3;  //��ʼ�����꣬�����ṹ�߽�
	CString Str; //��ע����

	//��ע,��ĩ���߼�����,�ַ���
	//Pos=����λ�ã�0-�߼䣬1-�Ҷˣ�2-���
	//ArrowType��ͷ���ͣ�0-���ˣ�1-�Ҷˣ�2-���,3-�޼�ͷ
	void DrawLabel(CDC *pdc,float ratio,COLORREF color=RGB(0,0,0),int ArrowType=0,int Pos=0);  //����ע�ߺ�����,ratioΪ����任ϵ��
};

//�����ӽ���,һ������������һ�����棬�����Ǹ���ͨ��һ����������ǵ�һ����,ֻ���弸�γߴ磬���漰���ͺͲ���
class _SSG_DLLIMPEXP CSubSection
{
public:
	CSubSection(SUBSECTION_SHAPE ishape=SUBSHAPE_RECT,SUBSECTION_MAT_TYPE iSubMatType=SUBSECTION_MAT_TYPE_CONC);
	CSubSection(const CSubSection &sec) {pPoint=NULL; *this=sec; }  //���ƹ��캯��
	~CSubSection(void) { Clear(); }

	//��Ա����--------------------
	SUBSECTION_SHAPE iShape;  //������״��Ԥ������״���Ի���״��
	SUBSECTION_MAT_TYPE iSubMatType; //�ӽ���������ͣ����������͸ֵȵ�һ����,�����ǻ�ϲ��ϣ�

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
		struct GEO_TRAPEZOID trapezoid;
		struct GEO_L L;
		struct GEO_T T;
		struct GEO_RECT_VAR rect_var;
		float fValue[Sys_SubSectionParaNum];  //��λ����
	};
	float p2,p3; //�ӽ���2��3�����ƫ�ľࣨm�����ӽ������ĵ���Ͻ���ֲ�����ԭ��ľ��룬��Ͻ�������ԭ��ѡ��������ε����ĵ�

	//�Զ�����״���β���
	int nPoint;  //�߽����
	SECTION_POINT *pPoint;  //�߽�����꣬����ԭ�������ģ�֧�ָ���ͨ��
	int nLabel; //��ע����
	CLabel Label[Sys_MaxLabel]; //��ע

	//static int GetValueIndex(CString &sValueName);  //�ɲ������õ��������

	//��Ա����--------------------
	//int CalBoundary(void); //����Ԥ������״�������ߴ����߽�㣬�����Զ�����״ʲô�����������ر߽�����=1����ͨ��>1��Ϊ����ͨ��
	SECTION_POINT *GetOuterBoundary(int &n);  //������߽���׵�ַ�ͱ߽����
	SECTION_POINT *GetNextBoundary(const SECTION_POINT *p0,int &n);  //������һ���߽���׵�ַ�ͱ߽����,p0Ϊ��ǰ�߽��׵�ַ

	//�ʷ���ά��Ԫ,������ά������̬����,�������ֽ�
	BEAM_FIBRE_GEO *FibreMesh(int nFibre);
	//����������������ά������������ڷ��صĶ�̬������pmesh�����У������ڲ��������
	//BEAM_FIBRE_GEO *GetFibrePara(int nFibre,POINT_LIST *PointCoor,ELEM_LIST *Tri);

	//����������γߴ�
	void GetRectSize(float &fWidth,float &fHeight);
	float Area(void); //����������
	float ShearArea2(void); //����2������Ч�������
	float ShearArea3(void); //����3������Ч�������
	float I2(void); //2������Ծ�(��Ӧ2�������ʸ��)���������Ͻ���ľֲ�����ԭ�㣬����Ҫ��������ƫ�ľ�
	float I3(void); //3������Ծ�(��Ӧ3�������ʸ��)���������Ͻ���ľֲ�����ԭ�㣬����Ҫ��������ƫ�ľ�
	float J1(void);  //Ťת���Ծأ��������Ͻ���ľֲ�����ԭ�㣬����Ҫ��������ƫ�ľ�

	CSubSection & operator=(const CSubSection &sec); //���ظ�ֵ����

	void Clear(void); //�������

	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
};


//�߹���������
class _SSG_DLLIMPEXP CBeamSection
{
public:
	//��������������
	CBeamSection(void) {pConcFibreBuf=pSteelFibreBuf=NULL; Clear();}
	//CBeamSection(CString &sName) {pConcFibreBuf=pSteelFibreBuf=NULL; Clear(); this->sName=sName;}

	CBeamSection(const CBeamSection &sec)	{ pConcFibreBuf=pSteelFibreBuf=NULL; nUsedCount=0; *this=sec; }

	~CBeamSection(void) { Clear(); }

	//��������
	int id;  //����ID
	CString sName;  //��������,���������ý����������ԣ�һ���������Ʊ��Ķ�������ݸĶ�ǰ��Ķ�Ӧ��ϵ�滻������
	SECTION_MAT_TYPE iMatType;		//����������ʹ���
	SECTION_SHAPE iSectionShape;	//������״����,ģ��ID
	CArray<CSubSection,CSubSection&> aSubSec; //�ӽ�������

	//iFibreMethod--��ά�ʷַ�����
	//0--�����ʷ֣���ϵͳ��������������Sys_RC_Double_ConcFibre��
	//1--���ʷ֣���ϵͳ��������������Sys_RC_Single_ConcFibre��
	//2--�Զ����ʷ�,ʹ��iUserConcFibre��iUserSteelFibre
	int iFibreMethod;

	COLORREF dwColor; //��ʾ��ɫ, ���ڿ���Ѱ��

	//��������ֵ����,�־����ݣ����浽�ļ����û���������������޸ģ��޸Ľ���ʱ����GetFeatures���м���
	enum {BEAMSECTION_PARA=12};	//����������������
	float ConcArea,      SteelArea;			//���������,�ֲ����(������������ʼ���ĸֽ��ͬ)
	float ConcShearArea2,SteelShearArea2;	//2���򿹼����
	float ConcShearArea3,SteelShearArea3;	//3���򿹼����
	float ConcI2,        SteelI2;			//2����ת����������Ӧ����M2����
	float ConcI3,        SteelI3;			//3����ת����������Ӧ����M3����
	float ConcJ1,        SteelJ1;			//1����ת�������������Ծأ���ӦŤ��M1

	//��ʱ����,�����浽�ļ�,��ȡ���桢�޸Ľ���ʱ���޸���ά���Ʋ���ʱ����GetFibres����
	float fWidth,fHeight; //��ȷ�Χ,�߶ȷ�Χ������������ʾ����Χ�ⶨ��δ����ת�ǣ���Ϊת���ǹ������ԣ����ǽ�������
	int nConcFibre,nStructSteelFibre;  //��������ά����������ά�������������ֽ
	BEAM_FIBRE_GEO *pConcFibreBuf,*pSteelFibreBuf;   //��������ά���飬����ά���飨�������ֲ��ֽ��������Ե�����ĸֽ�����

	int nUsedCount;  //������ʹ�õĴ�����һ��Ҫ�ȼ�����ʹ��,��ʱ����
	
	//����ģ�崴�����棬���ԭ������
	BOOL CreateSectionByTemplete(SECTION_SHAPE iShape);

	//�����������ֵ�������޸ĺ���е���
	void GetFeatures(void);  

	//����ˮƽ��������ĸֽ������,����ʵ�λ1
	float GetBeamRebarArea(float ratioB,float ratioH);

	//��������ʼ������򹹼�����ĸֽ������
	//fCorner--�ǽ������������,��λ��m^2�����޷�ȷ���ǽ��0
	float GetPillarRebarArea(float ratioB,float ratioH,float &fCorner);

	//Ѱ�һ������ӽ�����ţ�����-1��δ�ҵ�
	int GetConcSubSecIndex(void);

	//���¼������ߴ�fWidth,fHeight�����ڻ�ͼ
	void GetMaxSize(void);

	//����������ʱ���ݣ�ǿ���ʷֽ�����ά��Ԫ,�Զ����ڴ�.ֱ�ӷ�����ά���ݣ��������ֽ�,���������GetMaxSize()
	void GetFibres(int iUserConcFibre=0,int iUserSteelFibre=0);

	//���ݽ������������Զ��������
	CString &AutoName(void);

	//������Ͻ���������ӽ�������ڲ��ӽ���ĳߴ�
	//�Ե��ӽ���ʲô��������ֱ�ӷ���
	//�ֹܻ������ڲ�����Ӧ����������ܽ��
	//�ֹǻ������ڲ�����ĳߴ�ҪС���ⲿ����ߴ磬�������ֱ��ض�
	void GetInnerSubSectionSize(void);

	//�������ֽ���ά,��������ʺ͸ֽ�ֱ����ֻ�Ի�����������������������ֻ��һ�����������棬������ά���궯̬�ڴ漰��ά�����������浽���Ա��ʱ����
	//��ratioUpper��������,ratioLower�׽������,��λ1
	BEAM_FIBRE_GEO *CreateBeamRebar(float ratioUpper,float ratioLower);

	//�������ֽ���ά,��������ʺ͸ֽ�ֱ����ֻ�Ի�����������������������ֻ��һ�����������棬������ά���궯̬�ڴ漰��ά�����������浽���Ա��ʱ����
	//��ratioB--B���������,ratioH--H��������ʣ�Բ����ֻ�õ�һ�������,��λ1
	BEAM_FIBRE_GEO *CreatePillarRebar(float ratioB,float ratioH,float &fCorner);

	//�ж��ǲ���ĳ���ͽṹ�Ŀ��ý���
	int IsUsable(STRUCT_TYPE iType);
	STRUCT_TYPE GetType(); //�õ��ý���Ľṹ����

	//��񻯱�Ե�������ֹܽ���ĳߴ�
	//area--�����Ľ��������ref_width--�����Ľ����ȣ�sec_width--���صĹ�񻯽����ȣ�sec_t--���صĹ�񻯱ں�
	//fThickPrec--��ȼ����λ����
	static float GetEdgeSize(float area,float ref_width,float &sec_width,float &sec_t,float fThickPrec=0.0002f);

	CBeamSection & operator=(const CBeamSection &sec);

	void Clear(void);

	float DrawSection(CDC *pDC,BOOL bGrid,BOOL bFibre,const CRect &re);  //������Ͻ���,���ػ��Ʊ���

	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
};


//�����༯��
class _SSG_DLLIMPEXP CSectionCollection
{
public:
	CSectionCollection(void){;}
	~CSectionCollection(void){Clear();}

	CSectionCollection(const CSectionCollection &sec)
	{
		*this=sec;
	}

	CArray<CBeamSection*,CBeamSection*> aBeamSectionPtr;  //��������ָ��
	int iMaxID;  //��ǰ�õ������ID

	int GetID(int iStrucType,const CString &sName);  //���ݽṹ���ͺͽ������ƻ�ý���ID,�Ҳ�������-1
	int GetIndex(int id) const;  //���ݸ�����������id��������,�Ҳ�������-1
	int GetIDByArea(STRUCT_TYPE iStrucType,float area); //���ݽ��������ý���ID,˫�������5%���Ҳ�������-1
	CBeamSection *GetBeamSection(int id) const;  //���ݸ�����������id���ؽ���ָ��
	//int GetIndex(const CString &SecName);  //���ݸ��������������Ʒ�������,�Ҳ�������-1
	//CBeamSection *GetBeamSection(const CString &SecName);  //���ݸ��������������Ʒ��ؽ���ָ��
	//int GetAvailableID(void);  //�õ���Ч������ID
	int *CreateIndex(void);  //����ID-->��ŵ��������飬���ó�����Ҫɾ���������鳤��ΪiMaxID+1

	void AppendSection(CBeamSection *psec);  //�����½��棬�Զ���ȡID

	//���ӻ�������Ե�������棬fThickPrec--��ȼ���
	//���ؽ���ID
	int AppendEdgeSection(float area,float width,float fThickPrec=0.0002f);

	CSectionCollection & operator=(const CSectionCollection &sec)
	{
		if(this==&sec) return *this; //����ֵʱֱ�ӷ���

		Clear();
		for(int i=0;i<sec.aBeamSectionPtr.GetCount();i++) 
		{
			CBeamSection *s1=new CBeamSection(*(sec.aBeamSectionPtr[i]));
			//*s1=*sec.aBeamSectionPtr[i];
			aBeamSectionPtr.Add(s1);  //���ﲻ����AppendSection�����ı�ID
			iMaxID=max(iMaxID,s1->id);  //��¼���ID
		}

		return *this;
	}

	void Clear();

	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
	void LoadDefaultLib(void);  //����ϵͳ��

};

struct _SSG_DLLIMPEXP SUBSECTION_SHAPE_PROP_TABLE
{
	SUBSECTION_SHAPE iShape;	//��״����
	CString sName;				//��״����
	int nPara;					//��������
	CString sParaName[Sys_SubSectionParaNum]; //��������
};

extern "C" _SSG_DLLIMPEXP SUBSECTION_SHAPE_PROP_TABLE aSubShapePropTable[Sys_SubSectionShapeNum];