#pragma once
#include <wingdi.h>
#include <vector>
#include <set>

/** @class  IGenerateText
 *  @brief	�����ĵ��ӿ�
 *  @author Eric(½��Ԫ)
 *  @date	2015/03/11
 *  -----------------------------------------------------------------------------------------------
 *  �汾��ʷ			ע��                       ����
 *  -----------------------------------------------------------------------------------------------
 *  @version v1.0.0.0	��ʼ�汾														2015/03/11
 *  @version v1.0.0.1	��ӹ�ʽ��ͼ��													2015/07/25
 *  @version v1.0.0.4   ����ɢ��ͼ��													2015/08/20
 *  @version v1.0.0.5   ���Ʊ���ʽ����												2015/09/19
 *  @version v1.0.0.6	���Ʊ���ʽ����												2015/09/23
 *  @version v1.1.0.0   ����ͼ���ʽ���ü�ͼ�β���										2015/09/28
 *  @version v1.1.0.4   ����ͼ��������ʽ����ǩ��ʽ										2016/01/25
 *  @version v1.1.0.5   ����ͼ���ʽ����(���ͼ֮ǰ����һ����ʽ,���ڸĹ�����)           2016/01/27
 *  @version v1.1.0.6   ҳü�����Զ���													2016/02/25
 *  @version v1.1.0.7   ����A2ֽ�ŵ������ʽ											2016/04/11
 *  @version v1.1.0.8   ���������ɫ��ƽ����											2016/07/09
 *  @version v1.1.0.9   �����˱��ϲ��п�������BUG									2016/08/03
 *  @version V1.1.1.0   ��ӱ����-�û��Զ����ҳ���˱����Ƿ��ظ�����                 2017/01/18               
 *  -----------------------------------------------------------------------------------------------
 *  @note:  -  
 */

namespace sd
{
enum SdPageStyle
{//ֽ�����
	sdPageA2,               //A2ֽ��
	sdPageA3,				//A3ֽ��
	sdPageA4,				//A4ֽ��
};

enum SdPageDirection
{//ֽ�ŷ���
	sdPageDirVertical,		//����
	sdPageDirHorizontal,	//����
};

enum  SdAlign
{//���뷽ʽ
	sdAlignDefault=0,
	sdAlignLeft=1<<0,		//�����
	sdAlignHoriMid=1<<1,	//ˮƽ���ж���
	sdAlignRight=1<<2,		//�Ҷ���
	sdAlignTop=1<<3,		//�϶���
	sdAlignVeriMid=1<<4,	//������ж���
	sdAlignBottom=1<<5,		//�¶���
	sdAlignCenter=sdAlignHoriMid | sdAlignVeriMid,
							//ˮƽ���������
};

enum SdPosition
{//λ��
	sdPositionNone=0,			//��
	sdPositionLeft=1<<0,		//���
	sdPositionRight=1<<1,		//�Ҳ�
	sdPositionTop=1<<2,			//����
	sdPositionBottom=1<<3,		//�ײ�
	sdPositionCenter=1<<4,		//�м�
	sdPositionLeftTop=sdPositionLeft | sdPositionTop,
								//����
	sdPositionRightTop=sdPositionRight | sdPositionTop,
								//����
	sdPositionLeftBottom=sdPositionLeft | sdPositionBottom,
								//����
	sdPositionRightBottom=sdPositionRight | sdPositionBottom,
								//����
};

enum SdTextStyle
{//�ı���ʽ
	sdTextStyleNormal,			//������ʽ
	sdTextStyleTitle1,			//����1��ʽ
	sdTextStyleTitle2,			//����2��ʽ
	sdTextStyleTitle3,			//����3��ʽ
	sdTextStyleTitle4,			//����4��ʽ
	sdTextStyleTitle5,			//����5��ʽ
	sdTextStyleTitle6,			//����6��ʽ
	sdTextStyleTitle7,			//����7��ʽ
	sdTextStyleTitle,			//������ʽ
	sdTextStyleSubTitle,		//��������ʽ
};

/*  ��ɫ(���û�����ö��ֵ����ֱ�Ӵ�RGB��ֵ��Ex: (SdColor)RGB(0,100,235) */
enum SdColor
{//��ɫ(���û�����ö��ֵ����ֱ�Ӵ�RGB��ֵ��Ex: (SdColor)RGB(0,100,235)
	//Ĭ��
	sdColorAuto,                //ϵͳĬ��

	//1.������ɫ
	sdColorBlack,				//��ɫ		RGB(0,0,0)
	sdColorRed,					//��ɫ		RGB(255,0,0)
	sdColorOrange,				//��ɫ		RGB(255,97,0)
	sdColorYellow,				//��ɫ		RGB(255,255,0)
	sdColorGreen,				//��ɫ		RGB(0,255,0)
	sdColorCyan,				//��ɫ		RGB(0,255,255)
	sdColorBlue,				//��ɫ		RGB(0,0,255)
	sdColorPurple,				//��ɫ		RGB(160,32,240)
	sdColorWhite,				//��ɫ		RGB(255,255,255)

	//2.��ɫϵ��
	sdColorBlackLightGray1,		//ǳ��ɫ1	RGB(204,204,204)
	sdColorBlackLightGray2,		//ǳ��ɫ2	RGB(192,192,192)
	sdColorBlackMiddleGray1,	//�л�ɫ1	RGB(153,153,153)
	sdColorBlackMiddleGray2,	//�л�ɫ2	RGB(128,128,128)
	sdColorBlackDarkGray1,		//����ɫ1	RGB(102,102,102)
	sdColorBlackDarkGray2,		//����ɫ2	RGB(51,51,51)
	sdColorBlackLvory,			//������	RGB(41,36,33)

	//3.��ɫϵ��
	sdColorWhiteAntique,		//�Ŷ���	RGB(250,235,215)
	sdColorWhiteSkyBlue,		//������	RGB(240,255,255)
	sdColorWhiteSmoke,			//����		RGB(245,245,245)
	sdColorWhiteAlmond,			//������	RGB(255,235,205)
	sdColorWhiteEggShell,		//����ɫ	RGB(252,230,201)

	//4.��ɫϵ��
	sdColorRedBrick,			//ש��		RGB(156,102,31)
	sdColorRedCadmium,			//�Ӻ�		RGB(227,23,13)
	sdColorRedCoral,			//ɺ��ɫ	RGB(255,127,80)
	sdColorRedIndia,			//ӡ�Ⱥ�	RGB(176,23,31)
	sdColorRedMagenta,          //�Ϻ�ɫ    RGB(255,0,255)

	//5.��ɫϵ��
	sdColorYellowBanana,		//�㽶ɫ	RGB(227,207,87)
	sdColorYellowCadmium,		//�ӻ�		RGB(255,153,18)
	sdColorYellowGold,			//���		RGB(255,215,0)
	sdColorYellowFloowe,		//�ƻ�ɫ	RGB(218,165,105)
	sdColorYellowOlive,         //���ɫ    RGB(107,142,35)

	//6.��ɫϵ��
	sdColorOrangeCadmium,		//�ӳ�		RGB(255,97,3)
	sdColorOrangeCarrot,		//���ܲ�ɫ	RGB(237,145,33)
	sdColorOrangeTangerine,		//�ۻ�		RGB(255,128,0)
	sdColorOrangeLight,			//����ɫ	RGB(245,222,179)

	//7.��ɫϵ��
	sdColorBrown,				//��ɫ		RGB(128,42,42)
	sdColorBrownRice,			//��ɫ		RGB(163,148,128)
	sdColorBrownChocolate,		//�ɿ���ɫ	RGB(210,105,30)
	sdColorBrownFlesh,			//��ɫ		RGB(255,125,64)
	sdColorBrownTan,			//�ƺ�ɫ	RGB(240,230,140)
	sdColorBrownSoil,			//������	RGB(115,74,18)
	sdColorBrownHorse,			//����ɫ	RGB(139,69,19)
	sdColorBrownSand,			//ɳ��ɫ	RGB(244,164,96)

	//8.��ɫϵ��
	sdColorBlueLightGray,		//ǳ����	RGB(176,224,230)
	sdColorBlueReddish,			//Ʒ��		RGB(65,105,225)
	sdColorBlueShiBanlan,		//ʯ����	RGB(106,90,205)
	sdColorBlueSky,				//����ɫ	RGB(135,206,235)
	sdColorBlueNavy,            //������    RGB(0,0,139)

	//9.��ɫϵ��
	sdColorCyanDark,			//����		RGB(8,46,84)
	sdColorCyanBlue,			//����		RGB(64,224,208)
	sdColorCyanDark1,            //����      RGB(0,139,139)
 
	//10.��ɫϵ��
	sdColorGreenYellow,			//����		RGB(127,255,0)
	sdColorGreenViridity,		//����		RGB(0,201,87)
	sdColorGreenForest,			//ɭ����	RGB(34,139,34)
	sdColorGreenGrassland,		//�ݵ���	RGB(124,252,0)
	sdColorGreenMint,			//����ɫ	RGB(189,252,201)
	sdColorGreenGrass,			//����		RGB(107,142,35)
	sdColorGreenDark,			//����		RGB(48,128,20)
	sdColorGreenSea,			//����ɫ	RGB(46,139,87)
	sdColorGreenTender,			//����ɫ	RGB(0,255,127)
	sdColorGreenAqua,           //ˮ��ɫ    RGB(0,245,255)

	//11.��ɫϵ��
	sdColorPurpleViolet,		//������ɫ	RGB(138,43,226)
	sdColorPurpleLight,			//����ɫ	RGB(218,112,214)
};

enum SdUnderlineStyle
{//�»�����ʽ
	sdUnderlineNone,			//���»��� 
	sdUnderlineSingle,			//���»���(ϸ)
	sdUnderlineDouble,			//˫�»���
	sdUnderlineThick,			//���»���(��)
	sdUnderlineDot,				//��ʽ�»���		........
	sdUnderlineDash,			//���»���			- - - - -
	sdUnderlinePL,				//��-�����»���		.-.-.-.-
	sdUnderlinePPL,				//��-��-�����»���	..-..-..-
	sdUnderlineWave,			//�����»���
};

enum SdSubscriptStyle
{//���±���ʽ
	sdSubscriptNone,			//��
	sdSubscript,				//�±�
	sdSuperscript,				//�ϱ�
};

enum SdLineWidth
{//�������
	sdLineWidthNone,			//������
	sdLineWidthThin,			//ϸ����
	sdLineWidthWide,			//������
};

enum SdTabBorderStyle
{//���߿�������ʽ
	sdTabBorderCustom								=0,					//�û��Զ�����ʽ
	sdTabBorderThreeWire							=1,				    //����ʽ���(�����߶�Ϊϸ��)
	sdTabBorderThreeWireMidThin						=2,					//����ʽ���(�����ߴ֣�����ϸ)
	sdTabBorderHeadWide_NoneSide					=3,					//��ͷ�����ߴ֣�����ϸ��������߿�
	sdTabBorderHeadWide_OutlineWide					=4,					//��ͷ���߿�֣�����ϸ
	sdTabBorderDouble_OuterWide_InnerThin			=5,					//˫��������ʽ����֣���ϸ (����ڲ���ϸ)
	sdTabBorderDouble_OuterThin_InnerWide			=6,					//˫��������ʽ����ϸ���ڴ� (����ڲ���ϸ)
	sdTabBorderDouble_OuterThin_InnerThin			=7,					//˫��������ʽ����ϸ����ϸ (����ڲ���ϸ)
	sdTabBorderThree_OuterThin_MidWide_InnerThin	=8,					//����������ʽ����ϸ���д֣���ϸ (����ڲ���ϸ)
	sdTabBorderSolid								=9,					//��άʽ��������, (����ڲ���ϸ)
	
	sdTabBorderNoLine								=20,				//������
};

enum SdPageBorderStyle
{//ҳ��߿���ʽ
	sdPageBorderNone,									//��ҳ��߿�
	sdPageBorderThin,									//ϸ�߿�
	sdPageBorderWide,									//�ֱ߿�
	sdPageBorderShadow,									//��Ӱʽ
	sdPageBorderSolid,									//��άʽ
};


enum SdPageHeaderFooterContentType
{//ҳüҳ����������
	sdHFString,				//�ַ�����Ex: ����Ժ
	sdHFNumber,				//ҳ���� Ex: 1
	sdHFNumber1,			//- ҳ���� -  Ex: - 1 -
	sdHFNumber2,			//�� ҳ���� ҳ  Ex: ��1ҳ
	sdHFNumber3,			//ҳ�����/ҳ������ Ex: 1/5
	sdHFPrefixNumber,		//ǰ׺+ҳ�� Ex: A_1, A_2, ...
};

enum SdChartType
{//ͼ������
	sdChartHistogram,		//��״ͼ
	sdChartLine,			//����ͼ
	sdChartPie,				//��ͼ
	sdChartBar,				//����ͼ
	sdChartArea,			//���ͼ
	sdChartXYScatter,		//XYɢ��ͼ
	sdChartSharePrice,		//�ɼ�ͼ
	sdChartCurvedSurface,	//����ͼ
	sdChartRadar,			//�״�ͼ
};

enum SdChartSubType
{//ͼ��������
	//��״ͼ
	sdChartSub_Histogram_Cluster=0,			//��״��״ͼ
	sdChartSub_Histogram_Heap,				//�ѻ���״ͼ
	sdChartSub_Histogram_PercentageHeap,	//�ٷֱȶѻ���״ͼ
	sdChartSub_Histogram_3DCluster,			//��ά��״��״ͼ
	sdChartSub_Histogram_3DHeap,			//��ά�ѻ���״ͼ
	sdChartSub_Histogram_3DPercentageHeap,	//��ά�ٷֱȶѻ���״ͼ
	sdChartSub_Histogram_3D,				//��ά����ͼ

	//����ͼ
	sdChartSub_Line_Default,				//����ͼ
	sdChartSub_Line_Heap,					//�ѻ�����ͼ
	sdChartSub_Line_PercentageHeap,			//�ٷֱȶѻ�����ͼ
	sdChartSub_Line_DataMark,				//�����ݱ�ǵ�����ͼ
	sdChartSub_Line_HeapDataMark,			//�����ݱ�ǵĶѻ�����ͼ
	sdChartSub_Line_PercentageHeapDataMark,	//�����ݱ�ǵİٷֱȶѻ�����ͼ
	sdChartSub_Line_3D,						//��ά����ͼ

	//��ͼ
	sdChartSub_Pie_Default,					//��ͼ
	sdChartSub_Pie_3D,						//��ά��ͼ
	sdChartSub_Pie_Composite,				//���ϱ�ͼ
	sdChartSub_Pie_CompositeBar,			//��������ͼ

	//����ͼ
	sdChartSub_Bar_Cluster,					//��״����ͼ
	sdChartSub_Bar_Heap,					//�ѻ�����ͼ
	sdChartSub_Bar_PercentageHeap,			//�ٷֱȶѻ�����ͼ
	sdChartSub_Bar_3DCluster,				//��ά��״����ͼ
	sdChartSub_Bar_3DHeap,					//��ά�ѻ�����ͼ
	sdChartSub_Bar_3DPercentageHeap,		//��ά�ٷֱȶѻ�����ͼ

	//���ͼ
	sdChartSub_Area_Default,				//���ͼ
	sdChartSub_Area_Heap,					//�ѻ����ͼ
	sdChartSub_Area_PercentageHeap,			//�ٷֱȶѻ����ͼ
	sdChartSub_Area_3D,						//��ά���ͼ
	sdChartSub_Area_3DHeap,					//��ά�ѻ����ͼ
	sdChartSub_Area_3DPercentageHeap,		//��ά�ٷֱȶѻ����ͼ

	//XYɢ��ͼ
	sdChartSub_XYScatter_Default,			//ɢ��ͼ
	sdChartSub_XYScatter_SmoothDataMark,	//��ƽ���ߺ����ݱ�ǵ�ɢ��ͼ
	sdChartSub_XYScatter_Smooth,			//��ƽ���ߵ�ɢ��ͼ
	sdChartSub_XYScatter_LineDataMark,		//��ֱ�ߺ����ݱ�ǵ�ɢ��ͼ
	sdChartSub_XYScatter_Line,				//��ֱ�ߵ�ɢ��ͼ(����ֵ��ˮƽ��ʽ����)
	sdChartSub_XYScatter_Line_Verical,		//��ֱ�ߵ�ɢ��ͼ(����ֵ����ֱ��ʽ����)

	//�ɼ�ͼ
	sdChartSub_SharePrice_CloseQuotation,	//�̸�-�̵�-����ͼ
	//sdChartSub_SharePrice_OpenCloseQuot,	//����-�̸�-�̵�-����ͼ
	//sdChartSub_SharePrice_VolumeCloseQuot,	//�ɽ���-�̸�-�̵�-����ͼ
	//sdChartSub_SharePrice_VolumeOpenClose,	//�ɽ���-����-�̸�-�̵�-����ͼ

	//����ͼ
	sdChartSub_CurvedSurface_3D,			//��ά����ͼ
	sdChartSub_CurvedSurface_3DFrame,		//��ά������ͼ
	sdChartSub_CurvedSurface_Normal,		//����ͼ
	sdChartSub_CurvedSurface_Overlooking,	//���ӿ��ͼ

	//�״�ͼ
	sdChartSub_Radar_Default,				//�״�ͼ
	sdChartSub_Radar_DataMark,				//�����ݱ�ǵ��״�ͼ
	sdChartSub_Radar_Fill,					//����״�ͼ
};

enum SdChartMarkStyle
{//ͼ����̶���ʽ
	sdChartMarkNone,						//��
	sdChartMarkNormal,						//Ĭ�Ͽ̶�
	sdChartMarkThousandUnit,				//ǧ��λ�̶�
	sdChartMarkMillionUnit,					//����λ�̶�
	sdChartMarkBillionUnit,					//ʮ�ڵ�λ�̶�
};

enum SdChartGridStyle
{//ͼ����������ʽ
	sdChartGridNone=0,						//��
	sdChartGridMain=1<<0,					//��������
	sdChartGridSub=1<<1,					//��������
	sdChartGridMainSub=sdChartGridMain | sdChartGridSub,
											//����������
};

enum SdTitleLayoutStyle
{//�����Ų���ʽ
	sdTitleLayoutNone,						//���Ų�
	sdTitleLayoutHori,						//ˮƽ�Ų�
	sdTitleLayoutVeri,						//�����Ų�(���ֲ���ת)
	sdTitleLayoutRotation,					//��ת90���Ų�
};

enum SdFormulaType
{//��ʽ����
	sdFormulaEQ,							//EQ��ʽ(docx��ʽ�ĵ�֧��)
	sdFormulaMathML,						//MathML���͹�ʽ(pdf��cell��ʽ�ĵ�֧�֣���ͼƬ��ʽ����)
};

typedef struct tagMARGIN
{//�߾�(mm)
	unsigned top;		//�ϱ߾�
	unsigned bottom;	//�±߾�
	unsigned left;		//��߾�
	unsigned right;		//�ұ߾�

	tagMARGIN()
	{
		top=left=5;
		bottom=right=10;
	}
	tagMARGIN(unsigned _top,unsigned _bottom,unsigned _left,unsigned _right)
	{
		top=_top;
		bottom=_bottom;
		left=_left;
		right=_right;
	}
}MARGIN,*PMARGIN;

typedef struct tagBORDER_FORMAT
{//����߸�ʽ
	SdLineWidth top;	//�ϱ���
	SdLineWidth left;	//�����
	SdLineWidth bottom;	//�±���
	SdLineWidth right;	//�ұ���

	SdLineWidth diagonalLT2RB;	//б�����ϵ�����
	SdLineWidth diagonalLB2RT;	//б�����µ�����

	tagBORDER_FORMAT()
	{
		top=left=bottom=right=sdLineWidthThin;
		diagonalLB2RT = diagonalLT2RB = sdLineWidthNone;
	}
	tagBORDER_FORMAT(SdLineWidth top,SdLineWidth left,SdLineWidth bottom,SdLineWidth right, 
		SdLineWidth lt2rb=sdLineWidthNone, SdLineWidth lb2rt=sdLineWidthNone)
	{
		this->top=top;
		this->left=left;
		this->bottom=bottom;
		this->right=right;
		this->diagonalLT2RB = lt2rb;
		this->diagonalLB2RT = lb2rt;
	}
}BORDER_FORMAT,*PBORDER_FORMAT;

typedef struct tagTAB_BORDER_FORMAT 
{
	SdLineWidth top;	//�ϱ���
	SdLineWidth left;	//�����
	SdLineWidth bottom;	//�±���
	SdLineWidth right;	//�ұ���

	SdLineWidth insideH;//�ڲ�����
	SdLineWidth insideV;//�ڲ�����

	tagTAB_BORDER_FORMAT()
	{
		top=left=bottom=right=sdLineWidthThin;
		insideH=insideV=sdLineWidthThin;
	}
}TAB_BORDER_FORMAT,*PTAB_BORDER_FORMAT;

typedef struct tagTEXT_FORMAT
{//�ı���ʽ
	LOGFONTA font;				//����  (�ֺ������Ӧ��ϵ����:)
								//�ֺ�:  ���� С�� һ�� Сһ ���� С�� ���� С�� �ĺ� С�� ��� С�� ���� С�� �ߺ� �˺� 
								//��:	  42   36   26   24   22   18   16   15   14   12  10.5  9   7.5  6.55  5.5  5
	SdAlign align;				//���뷽ʽ(�����еĲ����ı������Դ˴�����)
	SdColor colorText;			//��ɫ
	SdColor colorBack;			//������ɫ
	bool	bold;				//�Ӵ�
	SdSubscriptStyle subscript;	//���±�

	tagTEXT_FORMAT()
	{
		font.lfHeight=12;
		font.lfWidth=(long)2.5;
		font.lfEscapement=font.lfOrientation=0;
		font.lfWeight=5;
		font.lfItalic=false;
		font.lfUnderline=sdUnderlineNone;
		font.lfStrikeOut=false;
		subscript=sdSubscriptNone;

		strcpy_s((CHAR *)font.lfFaceName,32,"����");

		bold=false;
		align = sdAlignLeft;
		colorText = sd::sdColorBlack;
		colorBack = sd::sdColorWhite;
	}
	tagTEXT_FORMAT &operator=(const tagTEXT_FORMAT &textFormat)
	{
		align=textFormat.align;
		font=textFormat.font;
		strcpy_s((CHAR *)font.lfFaceName,32,textFormat.font.lfFaceName);;
		colorText=textFormat.colorText;
		colorBack=textFormat.colorBack;
		bold=textFormat.bold;
		subscript=textFormat.subscript;
		return *this;
	}
}TEXT_FORMAT,*PTEXT_FORMAT;

typedef struct tagTITLE_FORMAT
{//������ʽ
	SdAlign align;  //���������ʽ

	tagTITLE_FORMAT()
	{//Ĭ�������
		pTitle=NULL;
		pFormat=new TEXT_FORMAT();
	}
	virtual ~tagTITLE_FORMAT()
	{
		if(pFormat)
		{
			delete pFormat;
			pFormat=NULL;
		}
		if(pTitle)
		{
			delete [] pTitle;
			pTitle=NULL;
		}
	}

	tagTITLE_FORMAT &operator=(const tagTITLE_FORMAT &titleFormat)
	{
		align=titleFormat.align;
		if(titleFormat.getFormat())
			setFormat(*(titleFormat.getFormat()));
		setTitle(titleFormat.getTitle());
		return *this;
	}
	void setFormat(const TEXT_FORMAT& textFormat)
	{
		if(!pFormat)
			pFormat=new TEXT_FORMAT();
		memcpy(pFormat,&textFormat,sizeof(TEXT_FORMAT));
		if(textFormat.font.lfFaceName)
			strcpy_s(pFormat->font.lfFaceName, 32, textFormat.font.lfFaceName);
	}
	PTEXT_FORMAT getFormat() const
	{
		return pFormat;
	}
	void setTitle(const char* title)
	{
		if(pTitle)
		{
			delete [] pTitle;
			pTitle=NULL;
		}

		if(!title)
			return;
		size_t nLen=strlen(title);
		pTitle=new char[nLen+1];
		memcpy(pTitle,title,nLen);
		pTitle[nLen]=0;
	}
	char* getTitle() const
	{
		return pTitle;
	}
private:
	PTEXT_FORMAT pFormat;	//�ı���ʽ
	char* pTitle;			//��������
}TITLE_FORMAT,*PTITLE_FORMAT;

typedef struct tagGRAPHIC_FORMAT
{//ͼƬ��ʽ
	//bool embedOLE;	//�Ƿ�ΪOLEǶ��(true)  ֱ�Ӳ���ͼƬ(false)  �ݲ�֧��
	SdAlign align;		//���뷽ʽ
	unsigned width;		//ͼƬ���(mm)
	unsigned height;	//ͼƬ�߶�(mm)
	TITLE_FORMAT titleFormat;    //ͼ��

	tagGRAPHIC_FORMAT()
	{
		width = height= 100;
		align=sdAlignCenter;
		//embedOLE=false;
	}
}GRAPHIC_FORMAT,*PGRAPHIC_FORMAT;

typedef struct tagCHART_AXIS
{//ͼ����
	SdTitleLayoutStyle titleLayout;		//��Ҫ����������Ų���ʽ
	SdChartMarkStyle markStyle;			//��̶�ֵ��ʽ
	SdChartGridStyle gridStyle;			//��������ʽ

	tagCHART_AXIS()
	{
		pTitle=NULL;
		titleLayout=sdTitleLayoutNone;
		markStyle=sdChartMarkNormal;
		gridStyle=sdChartGridMain;
	}

	~tagCHART_AXIS()
	{
		if(pTitle)
		{
			delete [] pTitle;
			pTitle=NULL;
		}
	}

	void setTitle(const char* title)
	{
		if(!title)
			return;
		if(pTitle)
			delete [] pTitle;
		size_t nLen=strlen(title);
		pTitle=new char[nLen+1];
		memcpy(pTitle,title,nLen);
		pTitle[nLen]=0;
	}
	char* getTitle() const
	{
		return pTitle;
	}
private:
	char * pTitle;		//�����
}CHART_AXIS,*PCHART_AXIS;

typedef struct tagCHART_FORMAT
{//ͼ���ʽ(��״ͼ��)
	SdChartType type;		//ͼ������
	SdChartSubType  subType;//ͼ��������(��ͼ����Word2013��ͼ��)

	SdAlign align;			//���뷽ʽ
	unsigned width;			//ͼƬ���(mm)
	unsigned height;		//ͼƬ�߶�(mm)
	unsigned nSpace;        //ָ����ǩ���

	bool showTable;			//��ʾ���ݱ�

	CHART_AXIS horiAxis;	//ˮƽ��
	CHART_AXIS veriAxis;	//��ֱ��

	SdPosition legendPosition;		//ͼ��λ��
	SdPosition dataLabelPosition;	//���ݱ�ǩλ��

	SdColor legendColor;            //ͼ���ı�����ɫ(ΪsdColorAutoʱ����ʾϵͳ�Զ�����ɫ)
	bool bOverlap;                  //ͼ���Ƿ���ͼ���ص�(false - ���ص�; true - �ص�)

	SdLineWidth borderWidth;//�߿��߿�
	SdColor borderColor;	//�߿�����ɫ

	tagCHART_FORMAT()
	{
		type=sdChartHistogram;
		subType=sdChartSub_Histogram_Cluster;
		align=sdAlignHoriMid;
		width=height=100;
		nSpace=1;
		pTitle=NULL;
		pVctLineColor= NULL;
		pVctFillColor = NULL;
		pVctLineWidth = NULL;
		pVctLineSmooth = NULL;
		showTable=false;
		horiAxis.gridStyle=sdChartGridNone;
		veriAxis.gridStyle=sdChartGridMain;
		borderWidth=sdLineWidthThin;
		borderColor=sdColorBlack;

		legendPosition=sdPositionRight;
		dataLabelPosition=sdPositionNone;

		//Ĭ��ϵͳ����
		legendColor = sdColorAuto; 
		bOverlap = false;
	}
	~tagCHART_FORMAT()
	{
		if(pTitle)
		{
			delete [] pTitle;
			pTitle=NULL;
		}
		if(pVctLineColor)
		{
			delete  pVctLineColor;
			pVctLineColor = NULL;
		}
		if(pVctLineWidth)
		{
			delete  pVctLineWidth;
			pVctLineWidth = NULL;
		}
		if(pVctLineSmooth)
		{
			delete pVctLineSmooth;
			pVctLineSmooth= NULL;
		}
		if(pVctFillColor)
		{
			delete pVctFillColor;
			pVctFillColor = NULL;
		}
	}

	void setTitle(const char* title)
	{
		if(!title)
			return;
		if(pTitle)
			delete [] pTitle;
		size_t nLen=strlen(title);
		pTitle=new char[nLen+1];
		memcpy(pTitle,title,nLen);
		pTitle[nLen]=0;
	}
	char* getTitle() const
	{
		return pTitle;
	}

	void setLineColor(int nLineIndex, SdColor eWidth)
	{
		if (NULL == pVctLineColor)
			pVctLineColor = new std::vector<SdColor>();

		//���
		int nVal = (int)(nLineIndex - pVctLineColor->size());
		for (int i=0; i<=nVal; ++i)
		{
			pVctLineColor->push_back(sdColorAuto);
		}

		//����
		(*pVctLineColor)[nLineIndex]=eWidth;
	}

	void setFillColor(int nIndex,SdColor eFill)
	{
		if (NULL == pVctFillColor)
			pVctFillColor = new std::vector<SdColor>();

		//���
		int nVal = (int)(nIndex - pVctFillColor->size());
		for (int i=0; i<=nVal; ++i)
		{
			pVctFillColor->push_back(sdColorAuto);
		}

		//����
		(*pVctFillColor)[nIndex]=eFill;
	}

	SdColor getLineColor(int nLineIndex)
	{
		if (NULL == pVctLineColor || nLineIndex >= (int)(pVctLineColor->size()))
			return sdColorAuto;

		return (*pVctLineColor)[nLineIndex];
	}

	SdColor getFillColor(int nIndex)
	{
		if (NULL == pVctFillColor || nIndex >= (int)(pVctFillColor->size()))
			return sdColorAuto;

		return (*pVctFillColor)[nIndex];
	}

	void setLineWidth(int nLineIndex, double dWidth)
	{
		if (NULL == pVctLineWidth)
			pVctLineWidth = new std::vector<double>();

		//���
		int nCha = (int)(nLineIndex - pVctLineWidth->size());
		for (int i=0; i<=nCha; ++i)
		{
			pVctLineWidth->push_back(0);
		}

		//����
		(*pVctLineWidth)[nLineIndex]=dWidth;	
	}

	void setLineSmooth(int nLineIndex, bool bSmooth)
	{
		if (NULL == pVctLineSmooth)
			pVctLineSmooth = new std::vector<bool>();
		//���
		int nVal = (int)(nLineIndex - pVctLineSmooth->size());
		for (int i=0; i<=nVal; ++i)
		{
			pVctLineSmooth->push_back(false);
		}
		(*pVctLineSmooth)[nLineIndex]=bSmooth;	
	}

	double getLineWidth(int nLineIndex)
	{
		if (NULL == pVctLineWidth || nLineIndex >= (int)(pVctLineWidth->size()))
			return 0;
		
		return (*pVctLineWidth)[nLineIndex];
	}
	
	bool getLineSmooth(int nLineIndex)
	{
		if (NULL == pVctLineSmooth || nLineIndex >= (int)(pVctLineSmooth->size()))
			return false;

		return (*pVctLineSmooth)[nLineIndex];	
	}
private:
	char * pTitle;		//ͼ��
	std::vector<SdColor> *pVctLineColor; //���߿��(ΪsdColorAutoʱ����ʾϵͳĬ�ϵ���ɫ)
	std::vector<double> *pVctLineWidth;  //������ɫ(Ϊ0ʱ����ʾϵͳĬ�ϵĿ��)
	std::vector<bool> *pVctLineSmooth; //����ͼ�����Ƿ�Ϊƽ����(Ϊtrueʱ��Ϊƽ���ߣ�ϵͳĬ�Ϸ�ƽ����)
	std::vector<SdColor> *pVctFillColor; //�����ɫ(ΪsdColorAutoʱ����ʾϵͳĬ�ϵ���ɫ)

}CHART_FORMAT,*PCHART_FORMAT;

typedef struct tagPAGE_COLUMNS
{//ҳ�����
	unsigned columnNum;	//������
	unsigned spacing;	//�����(mm)

	tagPAGE_COLUMNS()
	{
		columnNum=1;
		spacing=8;
	}
}PAGE_COLUMNS,*PPAGE_COLUMNS;

typedef struct tagPAGE_BORDER
{//ҳ��߿�
	SdPageBorderStyle style;	//�߿���ʽ

	SdColor color;				//�߿���ɫ
	MARGIN margin;				//�߾�

	tagPAGE_BORDER()
	{
		style=sdPageBorderNone;

		color=sdColorBlack;
		margin.left=margin.right=margin.top=margin.bottom=24;
	}
}PAGE_BORDER,*PPAGE_BORDER;

typedef class tagPAGE_HEADER_ITEM
{//ҳü��
public:
	SdAlign align;		//ˮƽ���뷽ʽ
	
	tagPAGE_HEADER_ITEM()
	{
		align=sdAlignCenter;
	}
	virtual ~tagPAGE_HEADER_ITEM()
	{
	}

	virtual bool operator==(const tagPAGE_HEADER_ITEM& val)
	{
		return align==val.align;
	}

	virtual void clone(tagPAGE_HEADER_ITEM *&pClone)
	{
		if(!pClone)
			return;
		pClone->align=align;
	}
}PAGE_HEADER_ITEM,*PPAGE_HEADER_ITEM;

class tagPAGE_HEADER_ITEM_TEXT
	: public tagPAGE_HEADER_ITEM
{//ҳü�ı���
public:

	tagPAGE_HEADER_ITEM_TEXT()
	{
		content=NULL;
		pFormat=NULL;
	}

	virtual ~tagPAGE_HEADER_ITEM_TEXT()
	{
		//delete content;
		if(pFormat)
		{
			delete pFormat;
			pFormat=NULL;
		}
		if(content)
		{
			delete [] content;
			content=NULL;
		}
	}
	void setFormat(const TEXT_FORMAT& textFormat)
	{
		if(!pFormat)
			pFormat=new TEXT_FORMAT();
		memcpy(pFormat,&textFormat,sizeof(TEXT_FORMAT));
	}
	PTEXT_FORMAT getFormat()
	{
		return pFormat;
	}
	void setContent(const char* text)
	{
		if(text==NULL)
			return;
		size_t nLen=strlen(text);
		if(content)
			delete [] content;
		content=new char[nLen+1];
		memcpy(content,text,nLen);
		content[nLen]=0;
	}
	char *getContent()
	{
		return content;
	}
	virtual void clone(tagPAGE_HEADER_ITEM *&pClone)
	{
		if(!pClone)
			pClone=new tagPAGE_HEADER_ITEM_TEXT();
		tagPAGE_HEADER_ITEM::clone(pClone);
		tagPAGE_HEADER_ITEM_TEXT *pCloneText=dynamic_cast<tagPAGE_HEADER_ITEM_TEXT*>(pClone);
		if(!pCloneText)
			return;
		pCloneText->setContent(content);

		if (NULL != pFormat)
		{
			tagPAGE_HEADER_ITEM_TEXT *pPHIT = (tagPAGE_HEADER_ITEM_TEXT *)pClone;
			pPHIT->pFormat = new TEXT_FORMAT;
			memcpy(pPHIT->pFormat, pFormat, sizeof(TEXT_FORMAT));
		}
	}
	virtual bool operator==(const tagPAGE_HEADER_ITEM_TEXT& val)
	{
		if(align!=val.align)
			return false;
		if(content==NULL && val.content==NULL)
			return true;
		else if(content && val.content==NULL)
			return false;
		else if(content==NULL && val.content)
			return false;
		else if(strcmp(content,val.content)!=0)
			return false;
		return true;
	}
private:
	char *content;  //�ı�����
	PTEXT_FORMAT pFormat; //�ı���ʽ
};
typedef tagPAGE_HEADER_ITEM_TEXT PAGE_HEADER_ITEM_TEXT;
typedef tagPAGE_HEADER_ITEM_TEXT* PPAGE_HEADER_ITEM_TEXT;

class tagPAGE_HEADER_ITEM_GRAPHIC
	: public tagPAGE_HEADER_ITEM
{
public:
	bool bLogoLeft;     //��logo������ͬһλ��ʱ���Ƿ����������

	tagPAGE_HEADER_ITEM_GRAPHIC()
	{
		pFileName=NULL;
		pFormat=NULL;
	}
	virtual ~tagPAGE_HEADER_ITEM_GRAPHIC()
	{
		if(pFormat)
		{
			delete pFormat;
			pFormat=NULL;
		}
		if(pFileName)
		{
			delete [] pFileName;
			pFileName=NULL;
		}
	}
	void setupFormat(GRAPHIC_FORMAT& mFormat)
	{
		if(!pFormat)
			pFormat=new GRAPHIC_FORMAT();
		//memcpy(pFormat,&mFormat,sizeof(GRAPHIC_FORMAT));
		pFormat->align=mFormat.align;		//���뷽ʽ
		pFormat->width=mFormat.width;		//ͼƬ���(mm)
		pFormat->height=mFormat.height;		//ͼƬ�߶�(mm)
		pFormat->titleFormat=mFormat.titleFormat;
	}
	PGRAPHIC_FORMAT getFormat()
	{
		return pFormat;
	}
	void setFileName(const char* filename)
	{
		if(filename==NULL)
			return;
		size_t nLen=strlen(filename);
		if(pFileName)
			delete [] pFileName;
		pFileName=new char[nLen+1];
		memcpy(pFileName,filename,nLen);
		pFileName[nLen]=0;
	}
	char *getFileName()
	{
		return pFileName;
	}

	virtual void clone(tagPAGE_HEADER_ITEM *&pClone)
	{
		if(!pClone)
			pClone=new tagPAGE_HEADER_ITEM_GRAPHIC();
		tagPAGE_HEADER_ITEM::clone(pClone);
		tagPAGE_HEADER_ITEM_GRAPHIC *pCloneGraphic=dynamic_cast<tagPAGE_HEADER_ITEM_GRAPHIC*>(pClone);
		if(!pCloneGraphic)
			return;
		pCloneGraphic->setFileName(pFileName);
		pCloneGraphic->bLogoLeft=bLogoLeft;
		if(pFormat)
			pCloneGraphic->setupFormat(*pFormat);
	}

	virtual bool operator==(const tagPAGE_HEADER_ITEM_GRAPHIC& val)
	{
		if(align!=val.align)
			return false;
		if(pFileName==NULL && val.pFileName==NULL)
			return true;
		else if(pFileName && val.pFileName==NULL)
			return false;
		else if(pFileName==NULL && val.pFileName)
			return false;
		else if(strcmp(pFileName,val.pFileName)!=0)
			return false;
		return true;
	}
private:
	char* pFileName;		//�ļ�·��������

	GRAPHIC_FORMAT *pFormat;//ͼƬ��ʽ
};
typedef tagPAGE_HEADER_ITEM_GRAPHIC PAGE_HEADER_ITEM_GRAPHIC;
typedef tagPAGE_HEADER_ITEM_GRAPHIC* PPAGE_HEADER_ITEM_GRAPHIC;

typedef class tagPAGE_HEADER
{//ҳü��ʽ
public:
	bool bUnderline;         //ҳü���� true - �� || false - ����
	bool bPageHomeDifferent; //��ҳ��ͬ true - ��ͬ || false - ��ͬ
	tagPAGE_HEADER()
	{
		pVctItems=NULL;
		bUnderline=true;
		bPageHomeDifferent = true;
	}

	tagPAGE_HEADER &operator=(const tagPAGE_HEADER &pageHeader)
	{
		clearItem();
		if(!pVctItems)
			pVctItems=new std::vector<PPAGE_HEADER_ITEM>();
		if(pageHeader.pVctItems==NULL)
			return *this;
		size_t nSizePageHeader = pageHeader.pVctItems->size();
		for (size_t i=0; i<nSizePageHeader; ++i)
		{
			PPAGE_HEADER_ITEM pHeaderOld = (*pageHeader.pVctItems)[i];
			if (NULL == pHeaderOld)
				continue;
			PPAGE_HEADER_ITEM pHeaderItem =NULL;
			pHeaderOld->clone(pHeaderItem);
			if(pHeaderItem)
				pVctItems->push_back(pHeaderItem);
		}
		return *this;
	}

	~tagPAGE_HEADER()
	{
		if(pVctItems)
		{
			int nSizeItems = (int)pVctItems->size();
			for (int i=0; i<nSizeItems; ++i)
			{
				PPAGE_HEADER_ITEM pItem =(*pVctItems)[i];
				if (NULL != pItem)
					delete pItem;
			}
			pVctItems->clear();

			delete pVctItems;
		}
	}

	PPAGE_HEADER_ITEM_TEXT appendItemText()
	{
		if(!pVctItems)
			pVctItems=new std::vector<PPAGE_HEADER_ITEM>();
		PPAGE_HEADER_ITEM_TEXT pItemText=new PAGE_HEADER_ITEM_TEXT();
		pVctItems->push_back(pItemText);
		return pItemText;
	}

	PPAGE_HEADER_ITEM_GRAPHIC appendItemGraphic()
	{
		if(!pVctItems)
			pVctItems=new std::vector<PPAGE_HEADER_ITEM>();
		PPAGE_HEADER_ITEM_GRAPHIC pItemGraphic=new PAGE_HEADER_ITEM_GRAPHIC();
		pVctItems->push_back(pItemGraphic);
		return pItemGraphic;
	}

	void clearItem()
	{
		if(pVctItems)
		{
			int nSizeItems = (int)pVctItems->size();
			for (int i=0; i<nSizeItems; ++i)
			{
				PPAGE_HEADER_ITEM pItem =(*pVctItems)[i];
				if (NULL != pItem)
					delete pItem;
			}
			pVctItems->clear();
		}
	}

	bool isEmpty()
	{
		if(!pVctItems || pVctItems->size()==0)
			return true;
		return false;
	}
	int getItemCount()
	{
		if(!pVctItems)
			return 0;
		return (int)pVctItems->size();
	}
	PPAGE_HEADER_ITEM getItem(int nIndex)
	{
		if(nIndex<0 || pVctItems==NULL || nIndex>=(int)pVctItems->size())
			return NULL;
		return (*pVctItems)[nIndex];
	}

	bool operator==(const tagPAGE_HEADER& val)
	{
		if(pVctItems==NULL && val.pVctItems==NULL)
			return true;
		else if(pVctItems==NULL)
			return false;
		else if(val.pVctItems==NULL)
			return false;
		int nSize1=(int)pVctItems->size();
		int nSize2=(int)val.pVctItems->size();
		if(nSize1!=nSize2)
			return false;
		for(int i=0;i<nSize1;i++)
		{
			PPAGE_HEADER_ITEM pItem1=(*pVctItems)[i];
			PPAGE_HEADER_ITEM pItem2=(*val.pVctItems)[i];
			if(pItem1!=pItem2)
				return false;
		}
		return true;
	}
private:

	std::vector<PPAGE_HEADER_ITEM> *pVctItems;

}PAGE_HEADER,*PPAGE_HEADER;

typedef class tagPAGE_FOOTER
{//ҳ����ʽ
public:
	SdAlign align;		//���뷽ʽ
	SdPageHeaderFooterContentType contentType;//��������
	
	tagPAGE_FOOTER()
	{
		align=sdAlignCenter;
		contentType=sdHFNumber;
		content=NULL;
		pFormat = NULL;
	}
	~tagPAGE_FOOTER()
	{
		if(content)
		{
			delete [] content;
			content=NULL;
		}
	}
	tagPAGE_FOOTER &operator=(const tagPAGE_FOOTER &pageFooter)
	{
		align=pageFooter.align;
		contentType=pageFooter.contentType;
		setContent(pageFooter.content);
		if (NULL != pageFooter.pFormat)
		{
			if (NULL == pFormat)
				pFormat = new TEXT_FORMAT;
			memcpy(pFormat, pageFooter.pFormat, sizeof(TEXT_FORMAT));
		}
		return *this;
	}

	void setContent(const char* text)
	{
		if(text==NULL)
			return;
		size_t nLen=strlen(text);
		if(content)
			delete [] content;
		content=new char[nLen+1];
		memcpy(content,text,nLen);
		content[nLen]=0;
	}
	char* getContent()
	{
		return content;
	}

	bool operator==(const tagPAGE_FOOTER& val)
	{
		if(align!=val.align || contentType!=val.contentType)
			return false;
		if(content==NULL && val.content==NULL)
			return true;
		else if(content && val.content==NULL)
			return false;
		else if(content==NULL && val.content)
			return false;
		else if(strcmp(content,val.content)!=0)
			return false;
		return true;
	}

	void setFormat(const TEXT_FORMAT& textFormat)
	{
		if(!pFormat)
			pFormat=new TEXT_FORMAT();
		memcpy(pFormat,&textFormat,sizeof(TEXT_FORMAT));
	}
	PTEXT_FORMAT getFormat()
	{
		return pFormat;
	}

private:
	char *content;
	PTEXT_FORMAT pFormat; //�ı���ʽ

}PAGE_FOOTER,*PPAGE_FOOTER;

typedef class tagPAGE_FORMAT
{//ҳ���ʽ
public:
	SdPageStyle pageStyle;		//ֽ�Ŵ�С
	SdPageDirection pageDir;	//ֽ�ŷ���
	MARGIN margin;				//ҳ�߾�
	PAGE_COLUMNS pageColumns;	//����
	PAGE_BORDER pageBorder;		//ҳ��߿�

	tagPAGE_FORMAT()
	{
		pageStyle=sdPageA3;
		pageDir=sdPageDirHorizontal;
		pPageHeader=NULL;
		pPageFooter=NULL;
	}
	~tagPAGE_FORMAT()
	{
		if(pPageHeader)
		{
			delete pPageHeader;
			pPageHeader=NULL;
		}
		if(pPageFooter)
		{
			delete pPageFooter;
			pPageFooter=NULL;
		}
	}
	tagPAGE_FORMAT &operator=(const tagPAGE_FORMAT &pageFormat)
	{
		pageStyle=pageFormat.pageStyle;
		pageDir=pageFormat.pageDir;
		margin=pageFormat.margin;
		pageColumns=pageFormat.pageColumns;
		pageBorder=pageFormat.pageBorder;
		if(!pageFormat.pPageHeader)
		{
			if(pPageHeader)
				delete pPageHeader;
			pPageHeader=NULL;
		}
		else
		{
			if(!pPageHeader)
				pPageHeader=new PAGE_HEADER();
			*pPageHeader=*pageFormat.pPageHeader;
		}
		if(!pageFormat.pPageFooter)
		{
			if(pPageFooter)
				delete pPageFooter;
			pPageFooter=NULL;
		}
		else
		{
			if(!pPageFooter)
				pPageFooter=new PAGE_FOOTER();
			*pPageFooter=*pageFormat.pPageFooter;
		}
		return *this;
	}

	PPAGE_HEADER getHeader()
	{
		return pPageHeader;
	}
	PPAGE_HEADER createHeader()
	{
		if (pPageHeader)
		{
			delete pPageHeader;
		}
		pPageHeader=new PAGE_HEADER();
		return pPageHeader;
	}
	PPAGE_FOOTER getFooter()
	{
		return pPageFooter;
	}
	PPAGE_FOOTER createFooter()
	{
		if (pPageFooter)
		{
			delete pPageFooter;
		}
		pPageFooter=new PAGE_FOOTER();
		return pPageFooter;
	}
private:
	PPAGE_HEADER pPageHeader;	//ҳü(�ڲ�����)
	PPAGE_FOOTER pPageFooter;	//ҳ��(�ڲ�����)

}PAGE_FORMAT,*PPAGE_FORMAT;

typedef struct tagTABLE_CELL
{//���Ԫ���
	unsigned row;		//�б��
	unsigned col;		//�б��

	tagTABLE_CELL()
	{
		row=col=1;
	}

	tagTABLE_CELL(unsigned uRow, unsigned uCol)
	{
		row = uRow;
		col = uCol;
	}
}TABLE_CELL;

typedef struct tagPARAGRAPH_FORMAT
{//�����ʽ
	SdAlign align;		//���뷽ʽ
	LOGFONTA font;		//����
	unsigned topSpacing;	//��ǰ�м��(mm)
	unsigned bottomSpacing;	//�κ��м��(mm)
	float leftSpacing;	//�������������(�ַ�)
	float rightSpacing;	//�����Ҳ�������(�ַ�)
	unsigned rowSpacing;	//�м��(mm)
	int		 previousSpacing;//���ж��������ַ���(�ַ�)

	tagPARAGRAPH_FORMAT()
	{
		reset();
	}

	void reset()
	{
		align=sdAlignLeft;
		font.lfHeight=12;
		font.lfWidth=5;
		font.lfEscapement=font.lfOrientation=0;
		font.lfWeight=5;
		previousSpacing=0;
		topSpacing=bottomSpacing=2;
		leftSpacing=rightSpacing=0;
		rowSpacing=2;

		strcpy_s((CHAR *)font.lfFaceName,32,"����");

	}
}PARAGRAPH_FORMAT,*PPARAGRAPH_FORMAT;


typedef struct tagCELL_TEXT_FORMAT : public tagTEXT_FORMAT
{//��Ԫ���ı���ʽ
	long lWidth;		//���ӿ��	//ͨ������(WORD�����õ�)
	SdColor colorFill;	//�����ɫ

	tagCELL_TEXT_FORMAT &operator=(const tagCELL_TEXT_FORMAT &cellFormat)
	{
		memcpy(this, &cellFormat, sizeof(tagCELL_TEXT_FORMAT));
		pBorder = NULL;
		lWidth=cellFormat.lWidth;
		if(NULL != cellFormat.pBorder)
		{
			pBorder = new BORDER_FORMAT;
			*pBorder = *(cellFormat.pBorder);
		}
		return *this;
	}

	tagCELL_TEXT_FORMAT()
	{
		pBorder=NULL;
		colorFill = sdColorWhite;
		lWidth=0;
	}
	~tagCELL_TEXT_FORMAT()
	{
		if(pBorder)
		{
			delete pBorder;
			pBorder=NULL;
		}
	}

	PBORDER_FORMAT createBorderFormat()
	{
		if(pBorder)
			delete pBorder;
		pBorder=new BORDER_FORMAT();
		return pBorder;
	}

	PBORDER_FORMAT getBorderFormat()
	{
		return pBorder;
	}
	void deleteBorderFormat()
	{
		if(pBorder)
		{
			delete pBorder;
			pBorder=NULL;
		}
	}
private:
	PBORDER_FORMAT pBorder;//�߿���ʽ

}CELL_FORMAT,*PCELL_FORMAT;

typedef struct tagFORMULA_TEXT_FORMAT : public tagTEXT_FORMAT
{//��ʽ�ı���ʽ
	SdFormulaType formulaType;	//��ʽ����

	tagFORMULA_TEXT_FORMAT &operator=(const tagFORMULA_TEXT_FORMAT &formulaFormat)
	{
		memcpy(this, &formulaFormat, sizeof(tagFORMULA_TEXT_FORMAT));
		formulaType = sdFormulaEQ;
		return *this;
	}

	tagFORMULA_TEXT_FORMAT()
	{
		formulaType = sdFormulaEQ;
	}
	
}FORMULA_FORMAT,*PFORMULA_FORMAT;

typedef struct tagCELL_FORMULA_FORMAT : public tagCELL_TEXT_FORMAT
{//��Ԫ���й�ʽ��ʽ
	SdFormulaType formulaType;	//��ʽ����

	tagCELL_FORMULA_FORMAT &operator=(const tagCELL_FORMULA_FORMAT &formulaFormat)
	{
		memcpy(this, &formulaFormat, sizeof(tagCELL_FORMULA_FORMAT));
		formulaType = sdFormulaEQ;
		return *this;
	}

	tagCELL_FORMULA_FORMAT()
	{
		formulaType = sdFormulaEQ;
	}
}CELL_FORMULA_FORMAT,*PCELL_FORMULA_FORMAT;

typedef struct tagGRAPHIC_EMBED_FORMAT : public tagGRAPHIC_FORMAT
{//Ƕ��ͼƬ��ʽ
	int leftOffset;		//ͼƬ���������߾�(��ֵ�����������)
	int topOffset;		//��������ϱ߾�

	PMARGIN pMargin;	//����Χ���ֵľ���(�ڲ�����)

	tagGRAPHIC_EMBED_FORMAT()
	{
		leftOffset=topOffset=0;
		pMargin=new MARGIN();
	}
	~tagGRAPHIC_EMBED_FORMAT()
	{
		if(pMargin)
		{
			delete pMargin;
			pMargin=NULL;
		}
	}
}GRAPHIC_EMBED_FORMAT,*PGRAPHIC_EMBED_FORMAT;

typedef struct tagTABLE_FORMAT
{//����ʽ
public:
	tagTABLE_FORMAT(const tagTABLE_FORMAT& tableFormat)
	{
		align = sdAlignLeft;
		nWidth = 0;
		nWidthPercent = 100;
		borderStyle=sdTabBorderCustom;
		bTopTitleRepeat = true;

		pColWidths = NULL;
		headerRows=1;
		colNum=0;
		operator=(tableFormat);
	}

	tagTABLE_FORMAT()
	{
		align = sdAlignLeft;
		nWidth = 0;
		nWidthPercent = 100;
		borderStyle=sdTabBorderCustom;
		bTopTitleRepeat = true;

		pColWidths = NULL;
		headerRows=1;
		colNum=0;
	}
	~tagTABLE_FORMAT()
	{
		if (NULL != pColWidths)
		{
			delete []pColWidths;
		}
	}
public:
	SdAlign align;			//���뷽ʽ(�����еĲ����ı������Դ˴�����)

	unsigned getColNum() const{ return colNum; }
	void setColNum(unsigned uColCount) 
	{
		int nOldColCount = colNum;
		unsigned *pOldWidths = pColWidths;

		colNum = uColCount;
		pColWidths = new unsigned[colNum];
		memset(pColWidths, 0, sizeof(pColWidths[0])*colNum);

		//���ƾɵ��п��µ��п���
		if (NULL != pOldWidths)
		{
			int nSize = min(nOldColCount, (int)colNum);
			for (int i=0; i<nSize; ++i)
			{
				pColWidths[i] = pOldWidths[i];
			}
		}

		if (NULL != pOldWidths)
		{
			delete []pOldWidths;
		}
	}
	bool setColWidth(int nColIndex, unsigned uWidth)
	{
		if (nColIndex < (int)colNum)
		{
			pColWidths[nColIndex] = uWidth;
			return true;
		}
		return false;
	}
	unsigned getColWidth(int nColIndex)
	{
		if (nColIndex < (int)colNum)
		{
			return pColWidths[nColIndex];
		}

		return 0;
	}
	unsigned nWidth;		//����С����λ��mm��Ϊ0ʱ��ʾʹ�ðٷֱȣ�
	unsigned nWidthPercent;	//�ٷֱȣ���������С��Ϊ0ʱ��Ч��
							//ע�⣺����������п���ָ�����������˱���ܿ����޷����ƴ˱�
							//      ���Կ���ָֻ��ĳЩ�У�������Ϊ0��ϵͳ�Զ�������

	bool bTopTitleRepeat;      //��ҳ���˱����ظ����� || true - �� || false - ��
	SdTabBorderStyle borderStyle;//�߿�������ʽ
	TAB_BORDER_FORMAT borderCustom;//�û��Զ���߿�����(��borderStyle=sdTabBorderCustomʱӦ�ô�ֵ)

	unsigned headerRows;	        //��ͷ����
	TITLE_FORMAT titleFormat;       //������ʽ

	tagTABLE_FORMAT &operator=(const tagTABLE_FORMAT &tableFormat)
	{
		align = tableFormat.align;
		nWidth = tableFormat.nWidth;
		nWidthPercent = tableFormat.nWidthPercent;
		bTopTitleRepeat = tableFormat.bTopTitleRepeat;
		borderStyle = tableFormat.borderStyle;
		headerRows = tableFormat.headerRows;
		borderCustom = tableFormat.borderCustom;

		titleFormat.align = tableFormat.titleFormat.align;
		if (tableFormat.titleFormat.getFormat() != NULL)
			titleFormat.setFormat(*(tableFormat.titleFormat.getFormat()));
		titleFormat.setTitle(tableFormat.titleFormat.getTitle());

		setColNum(tableFormat.getColNum());
		if(NULL != tableFormat.pColWidths)
		{
			unsigned nColNum = tableFormat.getColNum();
			memcpy(pColWidths, tableFormat.pColWidths, nColNum*sizeof(unsigned));
		}
		return *this;
	}



private:
	unsigned colNum;		//����
	unsigned *pColWidths;	//�п�(�ڲ�����)
	//ע1.�������Ϊ��.����еȿ�
	//  2.�����������������������������еȿ�
	//  3.�������������������������Գ���ֵ

}TABLE_FORMAT,*PTABLE_FORMAT;


class IGenerateText
{
public:
	virtual ~IGenerateText(){};

	/** 
	 * @brief ����ǰ��ʼ��
	 */
	virtual void init()=0;

public:	//ҳ��
	/** 
	* @brief ����ֽ��ҳ���ʽ
	* @para  PPAGE_FORMAT - ҳ���ʽ
	* @note  Ӱ�����ҳ���ʽ
	*        ���ҳüֻ������ʱ��֧�ֶ������֡���"\n"�ָ�ÿ�С�
	*        ���ҳü��ͬʱ�����ּ�ͼƬlogo,�������޷����У�������"\n"
	*/
	virtual void setupPage(PPAGE_FORMAT=NULL)=0;

	/** 
	 * @brief ��ҳ
	 */
	virtual void newPage()=0;

public:	//���䡢�ı�
	/** 
	 * @brief ׷�Ӷ���
	 * @para  PPARAGRAPH_FORMAT - �����ʽ
	 */
	virtual void beginParagraph(PPARAGRAPH_FORMAT=NULL)=0;
	
	/** 
	 * @brief ��������
	 */
	virtual void endParagraph()=0;

	/** 
	 * @brief ���ӱ���
	 * @para  pText - �����ı�
	 * @para  PTEXT_FORMAT - �ı���ʽ
	 * @note  ��������
	 */
	virtual void appendTitle(const char* pText,SdTextStyle,PTEXT_FORMAT=NULL)=0;

	/** 
	 * @brief �����ı�
	 * @para  pText - �ı�����
	 * @para  PTEXT_FORMAT - �ı���ʽ
	 * @para  pComment - ��ע
	 * @note  �����ж���������
	 */
	virtual bool appendText(const char* pText,PTEXT_FORMAT=NULL,const char* pComment=NULL)=0;

	/** 
	 * @brief ���Ӵ������ӵ��ı�
	 * @para  pText - �ı�����
	 * @para  PTEXT_FORMAT - �ı���ʽ
	 * @para  pHyperLinks - �����ӵ�·�����ļ���
	 * @note  ��������
	 */
	virtual bool appendHyperLinks(const char* pText,PTEXT_FORMAT=NULL,const char* pHyperLinks=NULL)=0;

public:	//ͼ��
	/** 
	 * @brief ����ͼ��
	 * @para  pFileName - ͼ���ļ����ƣ���·��
	 * @para  PGRAPHIC_FORMAT - ͼ�θ�ʽ
	 * @para  irotate    -  ͼ����ת�Ƕȣ�Ϊ0ʱ����ת��word��ֻ����ת90�ı�����
	 * @note  1.��ռһ������ 
	 *        2.��Ҫ������beginParagraph,endParagraph֮��
	 *        3.֧��jpg,png,tif,wmf,emf
	 *        4.���߻��ֵָ��Ϊ0ʱ��������ԭʼ�ߴ�
	 */
	virtual bool insertGraphi(const char* pFileName,PGRAPHIC_FORMAT=NULL,int irotate=0)=0;

	/** 
	 * @brief ����ͼ��
	 * @para  pFileName - ͼ���ļ����ƣ���·��
	 * @para  height - ͼƬ��
	 * @para  width - ͼƬ��
	 * @para  irotate    -  ͼ����ת�Ƕȣ�Ϊ0ʱ����ת��word��ֻ����ת90�ı�����
	 * @note  1.�ڵ�ǰ����������
	 *        2.Ҫ������beginParagraph,endParagraph֮��
	 *        3.��һ��������ͼ�Ļ���;������Ҳ�ɶ���ͼƬ
	 *        4.֧��jpg,png,tif,wmf,emf
	 *        5.���߻��ֵָ��Ϊ0ʱ��������ԭʼ�ߴ�
	 */
	virtual void appendGraphi(const char* pFileName,int height,int width,int irotate=0)=0;

	/** 
	 * @brief Ƕ��ͼ��
	 * @para  pFileName - ͼ���ļ����ƣ���·��ʽ)
	 * @para  PGRAPHIC_EMBED_FORMAT - ͼ�θ�ʽ
	 * @para  irotate    -  ͼ����ת�Ƕȣ�Ϊ0ʱ����ת��word��ֻ����ת90�ı�����
	 * @note  1.Ƕ���ڵ�ǰ����
	 *        2.֧��jpg,png,tif,wmf,emf
	 */
	virtual void embedGraphi(const char* pFileName,PGRAPHIC_EMBED_FORMAT=NULL,int irotate=0)=0;

	/** 
	 * @brief ����ͼ��(��״ͼ��)
	 * @para  PCHART_FORMAT - ͼ���ʽ
	 * @para  data - ͼ������
	 * @note  1.һ��ֻ�ܲ���һ��ͼ��
			  2.ͼ������ʵ��Ϊһ����ά��
			  3.���ݷ�Ϊ�����֣��ֱ�λ������{}�ڡ�
			  4.��һ��������������Ϊϵ������,����
			    �ڶ���������������Ϊ��������,��Щͼ������Ҫ��ֵ����{}���ÿռ��ɡ�
				������������������Ϊ��ֵ��  ��;�ָ���ÿ��Ϊһ�����ݡ�
			  5.���п��Բ��ȳ���
			  6.����Ҫ�������Ƶ�ͼ��Ϊ:����ͼ��XYɢ��ͼ����������Ҫ�������ơ�
	 ��1��
	          ϵ��1  ϵ��2  ϵ��3  ϵ��4
	   ����1    1      4      7      10
	   ����2    2      5      8      11
	   ����3    3      6      9      12
	   ��Ӧ���ַ���Ϊ��{ϵ��1,ϵ��2,ϵ��3,ϵͳ��}{����1,����2,����3}{1,2,3;4,5,6;7,8,9;10,11,12}
	 ��2:
	   �������������
			  ϵ��1  ϵ��2  ϵ��3
	           1      4      7
	           2      5      8
	           3      6      9
	   ��Ӧ���ַ���Ϊ��{ϵ��1,ϵ��2,ϵ��3}{}{1,2,3;4,5,6;7,8,9}
	 ��3:
	   �в��ȳ�
			  ϵ��1  ϵ��2  ϵ��3
		����1  1      4      9 
		����2  2      5     10
		����3  3      6     11
		����4         7     12
		����5         8
		��Ӧ���ַ���Ϊ��{ϵ��1,ϵ��2,ϵ��3,ϵͳ��}{����1,����2,����3,����4,����5}
		                {1,2,3;4,5,6,7,8;9,10,11,12}
	 ��4:
	   �в��ȳ���������������
	         ϵ��1  ϵ��2  ϵ��3
			  1      4      9 
			  2      5     10
	          3      6     11
	                 7     12
	                 8
	   ��Ӧ���ַ���Ϊ��{ϵ��1,ϵ��2,ϵ��3,ϵͳ��}{}{1,2,3;4,5,6,7,8;9,10,11,12}	    
	 */
	virtual void appendChart(const char* data,PCHART_FORMAT=NULL)=0;
public:	//���
	/** 
	 * @brief ��ʼ���ӱ��
	 * @para  PTABLE_FORMAT - �����ʽ
	 * @para  nCol			- �������
	 * @para  ���ñ����ʽ��
	 */
	virtual void beginTable(PTABLE_FORMAT=NULL)=0;

	/** 
	 * @brief ����һ��
	 * @para  rowHeight - �и�(0��ʾĬ���и�)
	 * @ret	  �����б��
	 */
	virtual int beginTableRow(unsigned rowHeight=0)=0;

	/** 
	 * @brief ������Ԫ�ı�
	 * @para  colIndex - �б��
	 * @para  pText - �ı�����
	 * @para  PCELL_FORMAT - ��Ԫ���ʽ
	 * @para  pComment - ��ע
	 * @note  ��ǰ���ǰ��
	 *		  ����˵�Ԫ�Ѵ������ݣ����滻
	 *        ����б�ų����������򲻻���벢����ʧ��
	 *		  �����Ԫ������"\n"��������
	 */
	virtual bool insertTableText(int colIndex,const char* pText,PCELL_FORMAT=NULL,const char* pComment=NULL)=0;

	/** 
	 * @brief ������Ԫͼ��
	 * @para  colIndex - �б��
	 * @para  pFileName - ͼ���ļ����ƣ���·��
	 * @para  pCellFormat - ��Ԫ���ʽ
	 * @para  pComment - ��ע
	 * @note  1.����˵�Ԫ�Ѵ������ݣ����滻
	 *        2.����б�ų����������򲻻���벢����ʧ��
	 *        3.֧��jpg,png,tif,wmf,emf
	 *        4.���߻��ֵָ��Ϊ0ʱ��������ԭʼ�ߴ�
	 */
	virtual bool insertTableGraphic(int colIndex,const char* pFileName,PCELL_FORMAT pCellFormat=NULL,
		int picHeight=0,int picWidth=0,int irotate=0)=0;

	/** 
	 * @brief ������Ԫͼ��
	 * @para  colIndex - �б��
	 * @para  pFileName - ͼ���ļ����ƣ���·��
	 * @para  pComment - ��ע
	 * @note  1.����˵�Ԫ�Ѵ������ݣ����滻
	 *        2.����б�ų����������򲻻���벢����ʧ��
	 *        3.֧��jpg,png,tif,wmf,emf
	 *        4.���߻��ֵָ��Ϊ0ʱ��������ԭʼ�ߴ�
	 */
	virtual bool appendTableGraphic(int colIndex,const char* pFileName,int picHeight=0,int picWidth=0,int irotate=0)=0;

	/** 
	 * @brief ������ʽ
	 * @para  colIndex - �б��
	 * @para  pCode - ��ʽ�����
	 * @para  PCELL_FORMULA_FORMAT - ��ʽ��ʽ
	 * @note  ��ǰ���ǰ��
	 *		  ����˵�Ԫ�Ѵ������ݣ����滻
	 *        ����б�ų����������򲻻���벢����ʧ��
	 */
	virtual bool insertTableFormula(int colIndex,const char* pCode,PCELL_FORMULA_FORMAT=NULL,const char* pComment=NULL)=0;

	/** 
	 * @brief ׷�ӱ��Ԫ�ı�
	 * @para  colIndex - �б��
	 * @para  pText - �ı�����
	 * @para  PTEXT_FORMAT - �ı���ʽ
	 * @para  pComment - ��ע
	 * @note  ��ǰ���ǰ��
	 *		  ����˵�Ԫ�Ѵ������ݣ����ں���׷��
	 *        ����б�ų����������򲻻���벢����ʧ��
	 */
	virtual bool appendTableText(int colIndex,const char* pText,PTEXT_FORMAT=NULL,const char* pComment=NULL)=0;

	/** 
	 * @brief ׷�ӱ��ʽ
	 * @para  colIndex - �б��
	 * @para  pCode - ��ʽ�����
	 * @para  PCELL_FORMULA_FORMAT - ��ʽ��ʽ
	 * @note  ��ǰ���ǰ��
	 *		  ����˵�Ԫ�Ѵ������ݣ����ں���׷��
	 *        ����б�ų����������򲻻���벢����ʧ��
	 */
	virtual bool appendTableFormula(int colIndex,const char* pCode,PCELL_FORMULA_FORMAT=NULL,const char* pComment=NULL)=0;

	/** 
	 * @brief ������ǰ��
	 */
	virtual void endTableRow()=0;

	/** 
	 * @brief �ϲ����Ԫ
	 * @para  leftTop - ���Ͻ�
	 * @para  rightBottom - ���½�
	 */
	virtual bool mergeTableCells(TABLE_CELL& leftTop,TABLE_CELL &rightBottom)=0;

	/** 
	 * @brief �������ӱ��
	 * @note  �����������뵽�ĵ���
	 */
	virtual void endTable()=0;
public: //��ǩ
	/** 
	 * @brief ������ǩ
	 * @note  �ڵ�ǰλ�ÿ�ʼ
	 */
	virtual void beginBookMark(const char *pMark)=0;

	/** 
	 * @brief ������ǰ��ǩ
	 */
	virtual void endBookMark()=0;
public:	//��ʽ(�ڶ���������)
	/** 
	 * @brief ���ӹ�ʽ������뷽ʽ��ӣ�
	 * @para  sCode - EQ�����(docx�ĵ�) Ex: EQ \\i(200,100,\\f(\\r(2,x),5))dx
	 *                ��MathML����(�����ĵ�) Ex: <msubsup><mo>&sum;</mo><mi>2</mi><mi>3</mi></msubsup>
	 *        docx��֧���ڶ��м��롣
	 *        ������ʽ��ռһ������
	 */
	virtual bool appendFormula(const char* sCode,PFORMULA_FORMAT pFormat)=0;
public: //Ŀ¼
	/** 
	 * @brief ����(�����Զ�����)
	 * @para  pFormat -	Ŀ¼��������ʽ
	 * @note  �ڵ�ǰλ�ò���Ŀ¼
	 *		  �����Զ���Ŀ¼������ҳ�롣
	 *        ���ڴ�docx�ĵ�ʱͨ��_Document -> TablesOfContents->update()��ʽ����ҳ�롣
	 */
	virtual void appendCatalog(PTEXT_FORMAT pFormat=NULL)=0;

public: //����
	/**
    * @brief  ����չʾ
	*/
	virtual void end()=0;

	/** 
	 * @brief �����ļ�
	 * @para  pName - �ļ���(��·��)
	 */
	virtual bool save(const char* pName)=0;

};
}


