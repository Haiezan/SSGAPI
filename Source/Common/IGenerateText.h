#pragma once
#include <wingdi.h>
#include <vector>
#include <set>

/** @class  IGenerateText
 *  @brief	生成文档接口
 *  @author Eric(陆中元)
 *  @date	2015/03/11
 *  -----------------------------------------------------------------------------------------------
 *  版本历史			注释                       日期
 *  -----------------------------------------------------------------------------------------------
 *  @version v1.0.0.0	初始版本														2015/03/11
 *  @version v1.0.0.1	添加公式，图表													2015/07/25
 *  @version v1.0.0.4   完善散点图表													2015/08/20
 *  @version v1.0.0.5   完善表格格式设置												2015/09/19
 *  @version v1.0.0.6	完善表格格式设置												2015/09/23
 *  @version v1.1.0.0   完善图表格式设置及图形插入										2015/09/28
 *  @version v1.1.0.4   设置图标线条格式及标签格式										2016/01/25
 *  @version v1.1.0.5   完善图表格式设置(面积图之前都是一种样式,现在改过来了)           2016/01/27
 *  @version v1.1.0.6   页眉横线自定义													2016/02/25
 *  @version v1.1.0.7   增加A2纸张的输出样式											2016/04/11
 *  @version v1.1.0.8   增加填充颜色及平滑线											2016/07/09
 *  @version v1.1.0.9   修正了表格合并列宽有误差的BUG									2016/08/03
 *  @version V1.1.1.0   添加表格功能-用户自定义各页顶端标题是否重复出现                 2017/01/18               
 *  -----------------------------------------------------------------------------------------------
 *  @note:  -  
 */

namespace sd
{
enum SdPageStyle
{//纸张类别
	sdPageA2,               //A2纸张
	sdPageA3,				//A3纸张
	sdPageA4,				//A4纸张
};

enum SdPageDirection
{//纸张方向
	sdPageDirVertical,		//竖向
	sdPageDirHorizontal,	//横向
};

enum  SdAlign
{//对齐方式
	sdAlignDefault=0,
	sdAlignLeft=1<<0,		//左对齐
	sdAlignHoriMid=1<<1,	//水平居中对齐
	sdAlignRight=1<<2,		//右对齐
	sdAlignTop=1<<3,		//上对齐
	sdAlignVeriMid=1<<4,	//竖向居中对齐
	sdAlignBottom=1<<5,		//下对齐
	sdAlignCenter=sdAlignHoriMid | sdAlignVeriMid,
							//水平及竖向居中
};

enum SdPosition
{//位置
	sdPositionNone=0,			//无
	sdPositionLeft=1<<0,		//左侧
	sdPositionRight=1<<1,		//右侧
	sdPositionTop=1<<2,			//顶部
	sdPositionBottom=1<<3,		//底部
	sdPositionCenter=1<<4,		//中间
	sdPositionLeftTop=sdPositionLeft | sdPositionTop,
								//左上
	sdPositionRightTop=sdPositionRight | sdPositionTop,
								//右上
	sdPositionLeftBottom=sdPositionLeft | sdPositionBottom,
								//左下
	sdPositionRightBottom=sdPositionRight | sdPositionBottom,
								//右下
};

enum SdTextStyle
{//文本样式
	sdTextStyleNormal,			//正文样式
	sdTextStyleTitle1,			//标题1样式
	sdTextStyleTitle2,			//标题2样式
	sdTextStyleTitle3,			//标题3样式
	sdTextStyleTitle4,			//标题4样式
	sdTextStyleTitle5,			//标题5样式
	sdTextStyleTitle6,			//标题6样式
	sdTextStyleTitle7,			//标题7样式
	sdTextStyleTitle,			//标题样式
	sdTextStyleSubTitle,		//副标题样式
};

/*  颜色(如果没有这个枚举值，可直接传RGB数值，Ex: (SdColor)RGB(0,100,235) */
enum SdColor
{//颜色(如果没有这个枚举值，可直接传RGB数值，Ex: (SdColor)RGB(0,100,235)
	//默认
	sdColorAuto,                //系统默认

	//1.常用颜色
	sdColorBlack,				//黑色		RGB(0,0,0)
	sdColorRed,					//红色		RGB(255,0,0)
	sdColorOrange,				//橙色		RGB(255,97,0)
	sdColorYellow,				//黄色		RGB(255,255,0)
	sdColorGreen,				//绿色		RGB(0,255,0)
	sdColorCyan,				//青色		RGB(0,255,255)
	sdColorBlue,				//蓝色		RGB(0,0,255)
	sdColorPurple,				//紫色		RGB(160,32,240)
	sdColorWhite,				//白色		RGB(255,255,255)

	//2.黑色系列
	sdColorBlackLightGray1,		//浅灰色1	RGB(204,204,204)
	sdColorBlackLightGray2,		//浅灰色2	RGB(192,192,192)
	sdColorBlackMiddleGray1,	//中灰色1	RGB(153,153,153)
	sdColorBlackMiddleGray2,	//中灰色2	RGB(128,128,128)
	sdColorBlackDarkGray1,		//暗灰色1	RGB(102,102,102)
	sdColorBlackDarkGray2,		//暗灰色2	RGB(51,51,51)
	sdColorBlackLvory,			//象牙黑	RGB(41,36,33)

	//3.白色系列
	sdColorWhiteAntique,		//古董白	RGB(250,235,215)
	sdColorWhiteSkyBlue,		//天蓝白	RGB(240,255,255)
	sdColorWhiteSmoke,			//白烟		RGB(245,245,245)
	sdColorWhiteAlmond,			//白杏仁	RGB(255,235,205)
	sdColorWhiteEggShell,		//蛋壳色	RGB(252,230,201)

	//4.红色系列
	sdColorRedBrick,			//砖红		RGB(156,102,31)
	sdColorRedCadmium,			//镉红		RGB(227,23,13)
	sdColorRedCoral,			//珊瑚色	RGB(255,127,80)
	sdColorRedIndia,			//印度红	RGB(176,23,31)
	sdColorRedMagenta,          //紫红色    RGB(255,0,255)

	//5.黄色系列
	sdColorYellowBanana,		//香蕉色	RGB(227,207,87)
	sdColorYellowCadmium,		//镉黄		RGB(255,153,18)
	sdColorYellowGold,			//金黄		RGB(255,215,0)
	sdColorYellowFloowe,		//黄花色	RGB(218,165,105)
	sdColorYellowOlive,         //橄榄色    RGB(107,142,35)

	//6.橙色系列
	sdColorOrangeCadmium,		//镉橙		RGB(255,97,3)
	sdColorOrangeCarrot,		//胡萝卜色	RGB(237,145,33)
	sdColorOrangeTangerine,		//桔黄		RGB(255,128,0)
	sdColorOrangeLight,			//淡黄色	RGB(245,222,179)

	//7.棕色系列
	sdColorBrown,				//棕色		RGB(128,42,42)
	sdColorBrownRice,			//米色		RGB(163,148,128)
	sdColorBrownChocolate,		//巧克力色	RGB(210,105,30)
	sdColorBrownFlesh,			//肉色		RGB(255,125,64)
	sdColorBrownTan,			//黄褐色	RGB(240,230,140)
	sdColorBrownSoil,			//标土棕	RGB(115,74,18)
	sdColorBrownHorse,			//马棕色	RGB(139,69,19)
	sdColorBrownSand,			//沙棕色	RGB(244,164,96)

	//8.蓝色系列
	sdColorBlueLightGray,		//浅灰蓝	RGB(176,224,230)
	sdColorBlueReddish,			//品蓝		RGB(65,105,225)
	sdColorBlueShiBanlan,		//石板蓝	RGB(106,90,205)
	sdColorBlueSky,				//天蓝色	RGB(135,206,235)
	sdColorBlueNavy,            //海军蓝    RGB(0,0,139)

	//9.青色系列
	sdColorCyanDark,			//靛青		RGB(8,46,84)
	sdColorCyanBlue,			//青绿		RGB(64,224,208)
	sdColorCyanDark1,            //暗青      RGB(0,139,139)
 
	//10.绿色系列
	sdColorGreenYellow,			//黄绿		RGB(127,255,0)
	sdColorGreenViridity,		//翠绿		RGB(0,201,87)
	sdColorGreenForest,			//森林绿	RGB(34,139,34)
	sdColorGreenGrassland,		//草地绿	RGB(124,252,0)
	sdColorGreenMint,			//薄荷色	RGB(189,252,201)
	sdColorGreenGrass,			//草绿		RGB(107,142,35)
	sdColorGreenDark,			//暗绿		RGB(48,128,20)
	sdColorGreenSea,			//海绿色	RGB(46,139,87)
	sdColorGreenTender,			//嫩绿色	RGB(0,255,127)
	sdColorGreenAqua,           //水绿色    RGB(0,245,255)

	//11.紫色系列
	sdColorPurpleViolet,		//紫罗蓝色	RGB(138,43,226)
	sdColorPurpleLight,			//淡紫色	RGB(218,112,214)
};

enum SdUnderlineStyle
{//下划线样式
	sdUnderlineNone,			//无下划线 
	sdUnderlineSingle,			//单下划线(细)
	sdUnderlineDouble,			//双下划线
	sdUnderlineThick,			//单下划线(粗)
	sdUnderlineDot,				//点式下划线		........
	sdUnderlineDash,			//虚下划线			- - - - -
	sdUnderlinePL,				//点-短线下划线		.-.-.-.-
	sdUnderlinePPL,				//点-点-短线下划线	..-..-..-
	sdUnderlineWave,			//波浪下划线
};

enum SdSubscriptStyle
{//上下标样式
	sdSubscriptNone,			//无
	sdSubscript,				//下标
	sdSuperscript,				//上标
};

enum SdLineWidth
{//线条宽度
	sdLineWidthNone,			//无线条
	sdLineWidthThin,			//细线条
	sdLineWidthWide,			//粗线条
};

enum SdTabBorderStyle
{//表格边框线条样式
	sdTabBorderCustom								=0,					//用户自定义样式
	sdTabBorderThreeWire							=1,				    //三线式表格(三条线都为细线)
	sdTabBorderThreeWireMidThin						=2,					//三线式表格(顶底线粗，中线细)
	sdTabBorderHeadWide_NoneSide					=3,					//表头及底线粗，内线细，无两侧边框
	sdTabBorderHeadWide_OutlineWide					=4,					//表头及边框粗，内线细
	sdTabBorderDouble_OuterWide_InnerThin			=5,					//双外轮廓线式，外粗，内细 (表格内部线细)
	sdTabBorderDouble_OuterThin_InnerWide			=6,					//双外轮廓线式，外细，内粗 (表格内部线细)
	sdTabBorderDouble_OuterThin_InnerThin			=7,					//双外轮廓线式，外细，内细 (表格内部线细)
	sdTabBorderThree_OuterThin_MidWide_InnerThin	=8,					//三外轮廓线式，外细，中粗，内细 (表格内部线细)
	sdTabBorderSolid								=9,					//三维式外轮廓线, (表格内部线细)
	
	sdTabBorderNoLine								=20,				//无线条
};

enum SdPageBorderStyle
{//页面边框样式
	sdPageBorderNone,									//无页面边框
	sdPageBorderThin,									//细边框
	sdPageBorderWide,									//粗边框
	sdPageBorderShadow,									//阴影式
	sdPageBorderSolid,									//三维式
};


enum SdPageHeaderFooterContentType
{//页眉页脚内容类型
	sdHFString,				//字符串，Ex: 建研院
	sdHFNumber,				//页码编号 Ex: 1
	sdHFNumber1,			//- 页面编号 -  Ex: - 1 -
	sdHFNumber2,			//第 页面编号 页  Ex: 第1页
	sdHFNumber3,			//页面编码/页码总数 Ex: 1/5
	sdHFPrefixNumber,		//前缀+页码 Ex: A_1, A_2, ...
};

enum SdChartType
{//图表类型
	sdChartHistogram,		//柱状图
	sdChartLine,			//折线图
	sdChartPie,				//饼图
	sdChartBar,				//条形图
	sdChartArea,			//面积图
	sdChartXYScatter,		//XY散点图
	sdChartSharePrice,		//股价图
	sdChartCurvedSurface,	//曲面图
	sdChartRadar,			//雷达图
};

enum SdChartSubType
{//图表子类型
	//柱状图
	sdChartSub_Histogram_Cluster=0,			//簇状柱状图
	sdChartSub_Histogram_Heap,				//堆积柱状图
	sdChartSub_Histogram_PercentageHeap,	//百分比堆积柱状图
	sdChartSub_Histogram_3DCluster,			//三维簇状柱状图
	sdChartSub_Histogram_3DHeap,			//三维堆积柱状图
	sdChartSub_Histogram_3DPercentageHeap,	//三维百分比堆积柱状图
	sdChartSub_Histogram_3D,				//三维柱形图

	//折线图
	sdChartSub_Line_Default,				//折线图
	sdChartSub_Line_Heap,					//堆积折线图
	sdChartSub_Line_PercentageHeap,			//百分比堆积折线图
	sdChartSub_Line_DataMark,				//带数据标记的折线图
	sdChartSub_Line_HeapDataMark,			//带数据标记的堆积折线图
	sdChartSub_Line_PercentageHeapDataMark,	//带数据标记的百分比堆积折线图
	sdChartSub_Line_3D,						//三维折线图

	//饼图
	sdChartSub_Pie_Default,					//饼图
	sdChartSub_Pie_3D,						//三维饼图
	sdChartSub_Pie_Composite,				//复合饼图
	sdChartSub_Pie_CompositeBar,			//复合条饼图

	//条形图
	sdChartSub_Bar_Cluster,					//簇状条形图
	sdChartSub_Bar_Heap,					//堆积条形图
	sdChartSub_Bar_PercentageHeap,			//百分比堆积条形图
	sdChartSub_Bar_3DCluster,				//三维簇状条形图
	sdChartSub_Bar_3DHeap,					//三维堆积条形图
	sdChartSub_Bar_3DPercentageHeap,		//三维百分比堆积条形图

	//面积图
	sdChartSub_Area_Default,				//面积图
	sdChartSub_Area_Heap,					//堆积面积图
	sdChartSub_Area_PercentageHeap,			//百分比堆积面积图
	sdChartSub_Area_3D,						//三维面积图
	sdChartSub_Area_3DHeap,					//三维堆积面积图
	sdChartSub_Area_3DPercentageHeap,		//三维百分比堆积面积图

	//XY散点图
	sdChartSub_XYScatter_Default,			//散点图
	sdChartSub_XYScatter_SmoothDataMark,	//带平滑线和数据标记的散点图
	sdChartSub_XYScatter_Smooth,			//带平滑线的散点图
	sdChartSub_XYScatter_LineDataMark,		//带直线和数据标记的散点图
	sdChartSub_XYScatter_Line,				//带直线的散点图(类型值沿水平方式绘制)
	sdChartSub_XYScatter_Line_Verical,		//带直线的散点图(类型值沿竖直方式绘制)

	//股价图
	sdChartSub_SharePrice_CloseQuotation,	//盘高-盘低-收盘图
	//sdChartSub_SharePrice_OpenCloseQuot,	//开盘-盘高-盘低-收盘图
	//sdChartSub_SharePrice_VolumeCloseQuot,	//成交量-盘高-盘低-收盘图
	//sdChartSub_SharePrice_VolumeOpenClose,	//成交量-开盘-盘高-盘低-收盘图

	//曲面图
	sdChartSub_CurvedSurface_3D,			//三维曲面图
	sdChartSub_CurvedSurface_3DFrame,		//三维曲面框架图
	sdChartSub_CurvedSurface_Normal,		//曲面图
	sdChartSub_CurvedSurface_Overlooking,	//俯视框架图

	//雷达图
	sdChartSub_Radar_Default,				//雷达图
	sdChartSub_Radar_DataMark,				//带数据标记的雷达图
	sdChartSub_Radar_Fill,					//填充雷达图
};

enum SdChartMarkStyle
{//图表轴刻度样式
	sdChartMarkNone,						//无
	sdChartMarkNormal,						//默认刻度
	sdChartMarkThousandUnit,				//千单位刻度
	sdChartMarkMillionUnit,					//百万单位刻度
	sdChartMarkBillionUnit,					//十亿单位刻度
};

enum SdChartGridStyle
{//图表网格线样式
	sdChartGridNone=0,						//无
	sdChartGridMain=1<<0,					//主网格线
	sdChartGridSub=1<<1,					//次网格线
	sdChartGridMainSub=sdChartGridMain | sdChartGridSub,
											//主次网格线
};

enum SdTitleLayoutStyle
{//标题排布方式
	sdTitleLayoutNone,						//不排布
	sdTitleLayoutHori,						//水平排布
	sdTitleLayoutVeri,						//竖向排布(文字不旋转)
	sdTitleLayoutRotation,					//旋转90度排布
};

enum SdFormulaType
{//公式类型
	sdFormulaEQ,							//EQ域公式(docx格式文档支持)
	sdFormulaMathML,						//MathML类型公式(pdf、cell格式文档支持，以图片方式插入)
};

typedef struct tagMARGIN
{//边距(mm)
	unsigned top;		//上边距
	unsigned bottom;	//下边距
	unsigned left;		//左边距
	unsigned right;		//右边距

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
{//表格线格式
	SdLineWidth top;	//上边线
	SdLineWidth left;	//左边线
	SdLineWidth bottom;	//下边线
	SdLineWidth right;	//右边线

	SdLineWidth diagonalLT2RB;	//斜线左上到右下
	SdLineWidth diagonalLB2RT;	//斜线左下到右上

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
	SdLineWidth top;	//上边线
	SdLineWidth left;	//左边线
	SdLineWidth bottom;	//下边线
	SdLineWidth right;	//右边线

	SdLineWidth insideH;//内部横线
	SdLineWidth insideV;//内部竖线

	tagTAB_BORDER_FORMAT()
	{
		top=left=bottom=right=sdLineWidthThin;
		insideH=insideV=sdLineWidthThin;
	}
}TAB_BORDER_FORMAT,*PTAB_BORDER_FORMAT;

typedef struct tagTEXT_FORMAT
{//文本格式
	LOGFONTA font;				//字体  (字号与磅对应关系见下:)
								//字号:  初号 小初 一号 小一 二号 小二 三号 小三 四号 小四 五号 小五 六号 小六 七号 八号 
								//磅:	  42   36   26   24   22   18   16   15   14   12  10.5  9   7.5  6.55  5.5  5
	SdAlign align;				//对齐方式(段落中的部分文本将忽略此处设置)
	SdColor colorText;			//颜色
	SdColor colorBack;			//背景颜色
	bool	bold;				//加粗
	SdSubscriptStyle subscript;	//上下标

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

		strcpy_s((CHAR *)font.lfFaceName,32,"宋体");

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
{//标题样式
	SdAlign align;  //标题居中样式

	tagTITLE_FORMAT()
	{//默认左对齐
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
	PTEXT_FORMAT pFormat;	//文本格式
	char* pTitle;			//标题名称
}TITLE_FORMAT,*PTITLE_FORMAT;

typedef struct tagGRAPHIC_FORMAT
{//图片格式
	//bool embedOLE;	//是否为OLE嵌入(true)  直接插入图片(false)  暂不支持
	SdAlign align;		//对齐方式
	unsigned width;		//图片宽度(mm)
	unsigned height;	//图片高度(mm)
	TITLE_FORMAT titleFormat;    //图名

	tagGRAPHIC_FORMAT()
	{
		width = height= 100;
		align=sdAlignCenter;
		//embedOLE=false;
	}
}GRAPHIC_FORMAT,*PGRAPHIC_FORMAT;

typedef struct tagCHART_AXIS
{//图表轴
	SdTitleLayoutStyle titleLayout;		//主要坐标轴标题排布方式
	SdChartMarkStyle markStyle;			//轴刻度值样式
	SdChartGridStyle gridStyle;			//网格线样式

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
	char * pTitle;		//轴标题
}CHART_AXIS,*PCHART_AXIS;

typedef struct tagCHART_FORMAT
{//图表格式(柱状图等)
	SdChartType type;		//图表类型
	SdChartSubType  subType;//图表子类型(详图参照Word2013中图表)

	SdAlign align;			//对齐方式
	unsigned width;			//图片宽度(mm)
	unsigned height;		//图片高度(mm)
	unsigned nSpace;        //指定标签间隔

	bool showTable;			//显示数据表

	CHART_AXIS horiAxis;	//水平轴
	CHART_AXIS veriAxis;	//竖直轴

	SdPosition legendPosition;		//图例位置
	SdPosition dataLabelPosition;	//数据标签位置

	SdColor legendColor;            //图例的背景颜色(为sdColorAuto时，表示系统自动的颜色)
	bool bOverlap;                  //图例是否与图表重叠(false - 不重叠; true - 重叠)

	SdLineWidth borderWidth;//边框线宽
	SdColor borderColor;	//边框线颜色

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

		//默认系统设置
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

		//填充
		int nVal = (int)(nLineIndex - pVctLineColor->size());
		for (int i=0; i<=nVal; ++i)
		{
			pVctLineColor->push_back(sdColorAuto);
		}

		//设置
		(*pVctLineColor)[nLineIndex]=eWidth;
	}

	void setFillColor(int nIndex,SdColor eFill)
	{
		if (NULL == pVctFillColor)
			pVctFillColor = new std::vector<SdColor>();

		//填充
		int nVal = (int)(nIndex - pVctFillColor->size());
		for (int i=0; i<=nVal; ++i)
		{
			pVctFillColor->push_back(sdColorAuto);
		}

		//设置
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

		//填充
		int nCha = (int)(nLineIndex - pVctLineWidth->size());
		for (int i=0; i<=nCha; ++i)
		{
			pVctLineWidth->push_back(0);
		}

		//设置
		(*pVctLineWidth)[nLineIndex]=dWidth;	
	}

	void setLineSmooth(int nLineIndex, bool bSmooth)
	{
		if (NULL == pVctLineSmooth)
			pVctLineSmooth = new std::vector<bool>();
		//填充
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
	char * pTitle;		//图名
	std::vector<SdColor> *pVctLineColor; //折线宽度(为sdColorAuto时，表示系统默认的颜色)
	std::vector<double> *pVctLineWidth;  //折线颜色(为0时，表示系统默认的宽度)
	std::vector<bool> *pVctLineSmooth; //折线图线型是否为平滑线(为true时，为平滑线，系统默认非平滑线)
	std::vector<SdColor> *pVctFillColor; //填充颜色(为sdColorAuto时，表示系统默认的颜色)

}CHART_FORMAT,*PCHART_FORMAT;

typedef struct tagPAGE_COLUMNS
{//页面分栏
	unsigned columnNum;	//分栏数
	unsigned spacing;	//栏间距(mm)

	tagPAGE_COLUMNS()
	{
		columnNum=1;
		spacing=8;
	}
}PAGE_COLUMNS,*PPAGE_COLUMNS;

typedef struct tagPAGE_BORDER
{//页面边框
	SdPageBorderStyle style;	//边框样式

	SdColor color;				//边框颜色
	MARGIN margin;				//边距

	tagPAGE_BORDER()
	{
		style=sdPageBorderNone;

		color=sdColorBlack;
		margin.left=margin.right=margin.top=margin.bottom=24;
	}
}PAGE_BORDER,*PPAGE_BORDER;

typedef class tagPAGE_HEADER_ITEM
{//页眉项
public:
	SdAlign align;		//水平对齐方式
	
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
{//页眉文本项
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
	char *content;  //文本内容
	PTEXT_FORMAT pFormat; //文本格式
};
typedef tagPAGE_HEADER_ITEM_TEXT PAGE_HEADER_ITEM_TEXT;
typedef tagPAGE_HEADER_ITEM_TEXT* PPAGE_HEADER_ITEM_TEXT;

class tagPAGE_HEADER_ITEM_GRAPHIC
	: public tagPAGE_HEADER_ITEM
{
public:
	bool bLogoLeft;     //当logo和文字同一位置时，是否在文字左边

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
		pFormat->align=mFormat.align;		//对齐方式
		pFormat->width=mFormat.width;		//图片宽度(mm)
		pFormat->height=mFormat.height;		//图片高度(mm)
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
	char* pFileName;		//文件路径和名称

	GRAPHIC_FORMAT *pFormat;//图片格式
};
typedef tagPAGE_HEADER_ITEM_GRAPHIC PAGE_HEADER_ITEM_GRAPHIC;
typedef tagPAGE_HEADER_ITEM_GRAPHIC* PPAGE_HEADER_ITEM_GRAPHIC;

typedef class tagPAGE_HEADER
{//页眉样式
public:
	bool bUnderline;         //页眉横线 true - 画 || false - 不画
	bool bPageHomeDifferent; //首页不同 true - 相同 || false - 不同
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
{//页脚样式
public:
	SdAlign align;		//对齐方式
	SdPageHeaderFooterContentType contentType;//内容类型
	
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
	PTEXT_FORMAT pFormat; //文本格式

}PAGE_FOOTER,*PPAGE_FOOTER;

typedef class tagPAGE_FORMAT
{//页面格式
public:
	SdPageStyle pageStyle;		//纸张大小
	SdPageDirection pageDir;	//纸张方向
	MARGIN margin;				//页边距
	PAGE_COLUMNS pageColumns;	//分栏
	PAGE_BORDER pageBorder;		//页面边框

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
	PPAGE_HEADER pPageHeader;	//页眉(内部析构)
	PPAGE_FOOTER pPageFooter;	//页脚(内部析构)

}PAGE_FORMAT,*PPAGE_FORMAT;

typedef struct tagTABLE_CELL
{//表格单元编号
	unsigned row;		//行编号
	unsigned col;		//列编号

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
{//段落格式
	SdAlign align;		//对齐方式
	LOGFONTA font;		//字体
	unsigned topSpacing;	//段前行间距(mm)
	unsigned bottomSpacing;	//段后行间距(mm)
	float leftSpacing;	//段落左侧缩进量(字符)
	float rightSpacing;	//段落右侧缩进量(字符)
	unsigned rowSpacing;	//行间距(mm)
	int		 previousSpacing;//首行段首缩进字符数(字符)

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

		strcpy_s((CHAR *)font.lfFaceName,32,"宋体");

	}
}PARAGRAPH_FORMAT,*PPARAGRAPH_FORMAT;


typedef struct tagCELL_TEXT_FORMAT : public tagTEXT_FORMAT
{//单元格文本格式
	long lWidth;		//格子宽度	//通常不用(WORD可以用到)
	SdColor colorFill;	//填充颜色

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
	PBORDER_FORMAT pBorder;//边框样式

}CELL_FORMAT,*PCELL_FORMAT;

typedef struct tagFORMULA_TEXT_FORMAT : public tagTEXT_FORMAT
{//公式文本格式
	SdFormulaType formulaType;	//公式类型

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
{//单元格中公式格式
	SdFormulaType formulaType;	//公式类型

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
{//嵌入图片格式
	int leftOffset;		//图片距离段落左边距(负值将延伸出段落)
	int topOffset;		//距离段落上边距

	PMARGIN pMargin;	//与周围文字的距离(内部析构)

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
{//表格格式
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
	SdAlign align;			//对齐方式(段落中的部分文本将忽略此处设置)

	unsigned getColNum() const{ return colNum; }
	void setColNum(unsigned uColCount) 
	{
		int nOldColCount = colNum;
		unsigned *pOldWidths = pColWidths;

		colNum = uColCount;
		pColWidths = new unsigned[colNum];
		memset(pColWidths, 0, sizeof(pColWidths[0])*colNum);

		//复制旧的列宽到新的列宽中
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
	unsigned nWidth;		//表格大小，单位：mm（为0时表示使用百分比）
	unsigned nWidthPercent;	//百分比（当“表格大小”为0时有效）
							//注意：如果所有列列宽都已指定，并超出了表格总宽，将无法绘制此表
							//      所以可以只指定某些列，其它列为0由系统自动计算宽度

	bool bTopTitleRepeat;      //各页顶端标题重复出现 || true - 是 || false - 否
	SdTabBorderStyle borderStyle;//边框线条样式
	TAB_BORDER_FORMAT borderCustom;//用户自定义边框线条(当borderStyle=sdTabBorderCustom时应用此值)

	unsigned headerRows;	        //表头行数
	TITLE_FORMAT titleFormat;       //标题样式

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
	unsigned colNum;		//列数
	unsigned *pColWidths;	//列宽(内部析构)
	//注1.如果集合为空.则各列等宽
	//  2.如果集合数量少于列数。则其余各列等宽
	//  3.如果集合数量大于列数。则忽略超出值

}TABLE_FORMAT,*PTABLE_FORMAT;


class IGenerateText
{
public:
	virtual ~IGenerateText(){};

	/** 
	 * @brief 生成前初始化
	 */
	virtual void init()=0;

public:	//页面
	/** 
	* @brief 设置纸张页面格式
	* @para  PPAGE_FORMAT - 页面格式
	* @note  影响后续页面格式
	*        如果页眉只有文字时，支持多行文字。以"\n"分隔每行。
	*        如果页眉中同时有文字及图片logo,则文字无法多行，将忽略"\n"
	*/
	virtual void setupPage(PPAGE_FORMAT=NULL)=0;

	/** 
	 * @brief 换页
	 */
	virtual void newPage()=0;

public:	//段落、文本
	/** 
	 * @brief 追加段落
	 * @para  PPARAGRAPH_FORMAT - 段落格式
	 */
	virtual void beginParagraph(PPARAGRAPH_FORMAT=NULL)=0;
	
	/** 
	 * @brief 结束段落
	 */
	virtual void endParagraph()=0;

	/** 
	 * @brief 增加标题
	 * @para  pText - 标题文本
	 * @para  PTEXT_FORMAT - 文本样式
	 * @note  独立段落
	 */
	virtual void appendTitle(const char* pText,SdTextStyle,PTEXT_FORMAT=NULL)=0;

	/** 
	 * @brief 增加文本
	 * @para  pText - 文本内容
	 * @para  PTEXT_FORMAT - 文本样式
	 * @para  pComment - 批注
	 * @note  在现有段落中增加
	 */
	virtual bool appendText(const char* pText,PTEXT_FORMAT=NULL,const char* pComment=NULL)=0;

	/** 
	 * @brief 增加带超链接的文本
	 * @para  pText - 文本内容
	 * @para  PTEXT_FORMAT - 文本样式
	 * @para  pHyperLinks - 超链接的路径与文件名
	 * @note  独立段落
	 */
	virtual bool appendHyperLinks(const char* pText,PTEXT_FORMAT=NULL,const char* pHyperLinks=NULL)=0;

public:	//图形
	/** 
	 * @brief 增加图形
	 * @para  pFileName - 图形文件名称，含路径
	 * @para  PGRAPHIC_FORMAT - 图形格式
	 * @para  irotate    -  图形旋转角度（为0时不旋转，word中只能旋转90的倍数）
	 * @note  1.独占一个段落 
	 *        2.不要放置在beginParagraph,endParagraph之间
	 *        3.支持jpg,png,tif,wmf,emf
	 *        4.当高或宽值指定为0时，将采用原始尺寸
	 */
	virtual bool insertGraphi(const char* pFileName,PGRAPHIC_FORMAT=NULL,int irotate=0)=0;

	/** 
	 * @brief 增加图形
	 * @para  pFileName - 图形文件名称，含路径
	 * @para  height - 图片高
	 * @para  width - 图片宽
	 * @para  irotate    -  图形旋转角度（为0时不旋转，word中只能旋转90的倍数）
	 * @note  1.在当前段落中增加
	 *        2.要放置在beginParagraph,endParagraph之间
	 *        3.可一个段落中图文混排;段落中也可多张图片
	 *        4.支持jpg,png,tif,wmf,emf
	 *        5.当高或宽值指定为0时，将采用原始尺寸
	 */
	virtual void appendGraphi(const char* pFileName,int height,int width,int irotate=0)=0;

	/** 
	 * @brief 嵌入图形
	 * @para  pFileName - 图形文件名称，含路径式)
	 * @para  PGRAPHIC_EMBED_FORMAT - 图形格式
	 * @para  irotate    -  图形旋转角度（为0时不旋转，word中只能旋转90的倍数）
	 * @note  1.嵌入在当前段落
	 *        2.支持jpg,png,tif,wmf,emf
	 */
	virtual void embedGraphi(const char* pFileName,PGRAPHIC_EMBED_FORMAT=NULL,int irotate=0)=0;

	/** 
	 * @brief 增加图表(柱状图等)
	 * @para  PCHART_FORMAT - 图表格式
	 * @para  data - 图表数据
	 * @note  1.一次只能插入一张图表
			  2.图表数据实际为一个二维表。
			  3.数据分为三部分，分别位于三对{}内。
			  4.第一个大括号内数据为系列名称,必有
			    第二个大括号内数据为类型名称,有些图表无需要此值，则{}内置空即可。
				第三个大括号内数据为数值。  以;分隔，每组为一行数据。
			  5.各列可以不等长。
			  6.不需要类型名称的图表为:气泡图、XY散点图；其它都需要类型名称。
	 例1：
	          系列1  系列2  系列3  系列4
	   类型1    1      4      7      10
	   类型2    2      5      8      11
	   类型3    3      6      9      12
	   对应的字符串为：{系列1,系列2,系列3,系统列}{类型1,类型2,类型3}{1,2,3;4,5,6;7,8,9;10,11,12}
	 例2:
	   对于下面的数据
			  系列1  系列2  系列3
	           1      4      7
	           2      5      8
	           3      6      9
	   对应的字符串为：{系列1,系列2,系列3}{}{1,2,3;4,5,6;7,8,9}
	 例3:
	   列不等长
			  系列1  系列2  系列3
		类型1  1      4      9 
		类型2  2      5     10
		类型3  3      6     11
		类型4         7     12
		类型5         8
		对应的字符串为：{系列1,系列2,系列3,系统列}{类型1,类型2,类型3,类型4,类型5}
		                {1,2,3;4,5,6,7,8;9,10,11,12}
	 例4:
	   列不等长，且无类型名称
	         系列1  系列2  系列3
			  1      4      9 
			  2      5     10
	          3      6     11
	                 7     12
	                 8
	   对应的字符串为：{系列1,系列2,系列3,系统列}{}{1,2,3;4,5,6,7,8;9,10,11,12}	    
	 */
	virtual void appendChart(const char* data,PCHART_FORMAT=NULL)=0;
public:	//表格
	/** 
	 * @brief 开始增加表格
	 * @para  PTABLE_FORMAT - 表格样式
	 * @para  nCol			- 表格列数
	 * @para  设置表格样式等
	 */
	virtual void beginTable(PTABLE_FORMAT=NULL)=0;

	/** 
	 * @brief 新增一行
	 * @para  rowHeight - 行高(0表示默认行高)
	 * @ret	  返回行编号
	 */
	virtual int beginTableRow(unsigned rowHeight=0)=0;

	/** 
	 * @brief 插入表格单元文本
	 * @para  colIndex - 列编号
	 * @para  pText - 文本内容
	 * @para  PCELL_FORMAT - 单元格格式
	 * @para  pComment - 批注
	 * @note  当前表格当前行
	 *		  如果此单元已存在内容，将替换
	 *        如果列编号超出列数，则不会插入并返回失败
	 *		  如果单元格中有"\n"，将换行
	 */
	virtual bool insertTableText(int colIndex,const char* pText,PCELL_FORMAT=NULL,const char* pComment=NULL)=0;

	/** 
	 * @brief 插入表格单元图形
	 * @para  colIndex - 列编号
	 * @para  pFileName - 图形文件名称，含路径
	 * @para  pCellFormat - 单元格格式
	 * @para  pComment - 批注
	 * @note  1.如果此单元已存在内容，将替换
	 *        2.如果列编号超出列数，则不会插入并返回失败
	 *        3.支持jpg,png,tif,wmf,emf
	 *        4.当高或宽值指定为0时，将采用原始尺寸
	 */
	virtual bool insertTableGraphic(int colIndex,const char* pFileName,PCELL_FORMAT pCellFormat=NULL,
		int picHeight=0,int picWidth=0,int irotate=0)=0;

	/** 
	 * @brief 插入表格单元图形
	 * @para  colIndex - 列编号
	 * @para  pFileName - 图形文件名称，含路径
	 * @para  pComment - 批注
	 * @note  1.如果此单元已存在内容，将替换
	 *        2.如果列编号超出列数，则不会插入并返回失败
	 *        3.支持jpg,png,tif,wmf,emf
	 *        4.当高或宽值指定为0时，将采用原始尺寸
	 */
	virtual bool appendTableGraphic(int colIndex,const char* pFileName,int picHeight=0,int picWidth=0,int irotate=0)=0;

	/** 
	 * @brief 插入表格公式
	 * @para  colIndex - 列编号
	 * @para  pCode - 公式域编码
	 * @para  PCELL_FORMULA_FORMAT - 公式格式
	 * @note  当前表格当前行
	 *		  如果此单元已存在内容，将替换
	 *        如果列编号超出列数，则不会插入并返回失败
	 */
	virtual bool insertTableFormula(int colIndex,const char* pCode,PCELL_FORMULA_FORMAT=NULL,const char* pComment=NULL)=0;

	/** 
	 * @brief 追加表格单元文本
	 * @para  colIndex - 列编号
	 * @para  pText - 文本内容
	 * @para  PTEXT_FORMAT - 文本格式
	 * @para  pComment - 批注
	 * @note  当前表格当前行
	 *		  如果此单元已存在内容，将在后面追加
	 *        如果列编号超出列数，则不会插入并返回失败
	 */
	virtual bool appendTableText(int colIndex,const char* pText,PTEXT_FORMAT=NULL,const char* pComment=NULL)=0;

	/** 
	 * @brief 追加表格公式
	 * @para  colIndex - 列编号
	 * @para  pCode - 公式域编码
	 * @para  PCELL_FORMULA_FORMAT - 公式格式
	 * @note  当前表格当前行
	 *		  如果此单元已存在内容，将在后面追加
	 *        如果列编号超出列数，则不会插入并返回失败
	 */
	virtual bool appendTableFormula(int colIndex,const char* pCode,PCELL_FORMULA_FORMAT=NULL,const char* pComment=NULL)=0;

	/** 
	 * @brief 结束当前行
	 */
	virtual void endTableRow()=0;

	/** 
	 * @brief 合并表格单元
	 * @para  leftTop - 左上角
	 * @para  rightBottom - 右下角
	 */
	virtual bool mergeTableCells(TABLE_CELL& leftTop,TABLE_CELL &rightBottom)=0;

	/** 
	 * @brief 结束增加表格
	 * @note  真正将表格加入到文档中
	 */
	virtual void endTable()=0;
public: //书签
	/** 
	 * @brief 增加书签
	 * @note  在当前位置开始
	 */
	virtual void beginBookMark(const char *pMark)=0;

	/** 
	 * @brief 结束当前书签
	 */
	virtual void endBookMark()=0;
public:	//公式(在段落中增加)
	/** 
	 * @brief 增加公式（域编码方式添加）
	 * @para  sCode - EQ域编码(docx文档) Ex: EQ \\i(200,100,\\f(\\r(2,x),5))dx
	 *                或MathML编码(其它文档) Ex: <msubsup><mo>&sum;</mo><mi>2</mi><mi>3</mi></msubsup>
	 *        docx中支持在段中加入。
	 *        其它格式独占一个段落
	 */
	virtual bool appendFormula(const char* sCode,PFORMULA_FORMAT pFormat)=0;
public: //目录
	/** 
	 * @brief 增加(内容自动生成)
	 * @para  pFormat -	目录标题行样式
	 * @note  在当前位置插入目录
	 *		  不会自动在目录中生成页码。
	 *        可在打开docx文档时通过_Document -> TablesOfContents->update()方式生成页码。
	 */
	virtual void appendCatalog(PTEXT_FORMAT pFormat=NULL)=0;

public: //结束
	/**
    * @brief  结束展示
	*/
	virtual void end()=0;

	/** 
	 * @brief 保存文件
	 * @para  pName - 文件名(含路径)
	 */
	virtual bool save(const char* pName)=0;

};
}


