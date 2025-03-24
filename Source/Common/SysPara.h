#pragma once

/*
系统编译宏定义：
	_SIMPLIFIED_CHINESE: 若定义则为中文版，文本常量应采用中文；否则为英文
	_PKPM: 若定义则为PKPM接口专用版程序，不包括前后处理图形显示和计算部分
	_NOFEM：若定义则为前处理专用版程序，不包括计算部分和PKPM接口；若未定义_PKPM和_NOFEM则为标准版程序，包括前处理和计算程序
	_SEP_FEM：独立的前处理和有限元计算EXE程序，不支持CUDA
	_HASP：若定义则为加密狗版
*/

const float Sys_FileVersion=2025.f; //IO文件版本号，递增精度>0.001，使用该数据时应注意float的精度问题，应留有余量例如设置误差0.05f。

//系统文件
const wchar_t FILE_DEFAULT_MATERIAL_LIB[]=L"DATA\\MATERIAL.MLB";  //系统缺省材料库，文本文件
const wchar_t FILE_DEFAULT_SECTION_LIB[]=L"DATA\\SECTION.MLB";  //系统缺省截面库，文本文件
const wchar_t FILE_DEFAULT_DAMPER_SECTION_LIB[]=L"DATA\\DAMPER_SECTION.MLB";  //系统缺省截面库，文本文件
const wchar_t FILE_SYS_INI[]=L"SAUSAGE.INI";  //用户配置ini文件，文本文件
const wchar_t FILE_SYS_MAT[]=L"SAUSAGE.MTL";  //用户自定义材料文件，文本文件，可用同ID进行参数替换
const wchar_t FILE_SECGEN[]=L"SECGEN.EXE";  //自定义截面程序，文本文件
const wchar_t FILE_PREP_PROJ[]=L"PrepSSGPath.txt";  //预处理返回的项目路径，文本文件


//项目根目录下的文件
const wchar_t FILE_PRJ_PARA[]=L"PAR";  //项目参数，ini格式文件，独立文件
const wchar_t FILE_BATCH_CMD[]=L".MCD";  //批处理文件，独立文件
const wchar_t FILE_MODIFY_HIST[]=L"MCM";  //修改模型属性用的指令历史记录，文本文件，独立文件
const wchar_t FILE_MESSAGE[]=L"MSG";  //程序运行的临时信息，文本文件，独立文件
const wchar_t FILE_MATERIAL[]=L"MLB";  //项目材料库，文本文件，独立文件，暂时不用
const wchar_t FILE_PRJ_TEMP[]=L"s~~"    ;  //临时备份的项目文件，存放项目相关信息，文本文件，暂时不用
const wchar_t FILE_OUT_PROFILE[]=L"IDX";  //输出数据的索引信息文件，文本文件，依赖于网格，暂时不用

const wchar_t FILE_FRAME[]=L"SSG"  ;  //框架数据，文本文件，依赖于MLB

const wchar_t FILE_CHECK_MODEL[]=L"WRN";  //检查模型数据交换，文本文件,依赖于SSG
const wchar_t FILE_COOR_BIN[]=L"BCR";  //结点坐标，二进制文件，依赖于SSG
const wchar_t FILE_COORL_BIN[]=L"BLR";  //结点荷载，二进制文件，依赖于SSG
const wchar_t FILE_ELEM_BIN[]=L"BEM";  //单元编码，二进制文件，依赖于SSG
const wchar_t FILE_COOR[]=L"COR";  //结点坐标，文本文件，用于输出接口，依赖于SSG
const wchar_t FILE_ELEM[]=L"ELM";  //单元编码，文本文件，用于输出接口，依赖于SSG
const wchar_t FILE_COORVL_BIN[]=L"BVL";  //节点时变荷载

const wchar_t FILE_SHADOW_COOR_BIN[]=L"SCR";  //三角形形心网格坐标，二进制文件，依赖于网格
const wchar_t FILE_SHADOW_POLY_BIN[]=L"SPL";  //三角形形心网格多边形，二进制文件，依赖于网格
const wchar_t FILE_FEA_INTERFACE[]=L"FEA";  //接口数据文本文件，仅供调试用，依赖于网格
const wchar_t FILE_POST_REPORT[]=L"OUT";  //PKPM格式的后处理报告，用于对比，文本文件，依赖于网格

const wchar_t FILE_WBEAM_COEF[]=L"WBC";  //PKPM格式的后处理报告，用于对比，文本文件，依赖于网格
const wchar_t FILE_DEFENSE_COEF[]=L"DFX";  //PKPM格式的后处理报告，用于对比，文本文件，依赖于网格
const wchar_t FILE_PERFORMDESIGN_COEF[]=L"PDC";  //PKPM格式的后处理报告，用于对比，文本文件，依赖于网格

const wchar_t FILE_OPTA_ELEM[] = L"OPTA";  //自动网格优化文件，依赖于网格
const wchar_t FILE_OPT_ELEM[] = L"OPTE";  //网格优化文件，依赖于网格

//以下为用于属性初始化的文件
const wchar_t FILE_WALLREBAR[]=L"D01";  //墙配筋信息，文本文件,不用
const wchar_t FILE_PLATEREBAR[]=L"D02";  //板配筋信息，文本文件，不用
const wchar_t FILE_HIDEBEAM[]=L"D03";  //虚梁生成参数，文本文件，独立文件
const wchar_t FILE_REBARTHICK[]=L"D04";  //面构件厚度与钢筋网层数关系，文本文件，独立文件
const wchar_t FILE_VISIBLEINFO[]=L"D05";  //可见的构件信息，文本文件，依赖于SSG
const wchar_t FILE_COMBINEFRAME[]=L"D06";  //组合构件索引，文本文件，依赖于SSG

//计算结果文件全部依赖于网格
//StaticResult子目录下的文件
const wchar_t FILE_MAX_FREQ[]=L"MFQ";  //最大频率文件，文本文件
const wchar_t FILE_STATIC_SUPPORT_FORCE[]=L"NSF";  //静力分析支座反力，文本文件
const wchar_t FILE_BUILDING_WEIGHT[]=L"STW";  //全楼总重，文本文件
const wchar_t FILE_MODAL_BIN[]=L"MOD";  //振型文件，二进制文件
const wchar_t FILE_FREQ[]=L"FRQ";  //频率文件，文本文件
const wchar_t FILE_BUCKLING[]=L"FRB";  //频率文件，文本文件
const wchar_t FILE_STATIC_DISP_BIN[]=L"NSD";  //竖向荷载加载的位移文件，二进制文件
const wchar_t FILE_BUCKLING_BIN[]=L"MOB";  //屈曲振型文件，二进制文件
const wchar_t FILE_DEFECT_BIN[]=L"IMP";  //缺陷文件，二进制文件
const wchar_t FILE_MAXMODAL_BIN[]=L"MOF";  //振型文件，二进制文件

//CModalResult子目录下的文件  林思齐 20210527
const wchar_t FILE_CMODAL_BIN[]=L"CMOD";        //振型文件，二进制文件
const wchar_t FILE_CFREQ[]=L"CFRQ";            //频率文件，文本文件
const wchar_t FILE_CMODAL_DISP_BIN[]=L"CBDS";  //等效地震力作用下结构节点位移文件，二进制文件

//EarthQuakeResult\case_n\子目录下的文件
const wchar_t FILE_DISP_BIN[]=L"BDS";  //动力分析结点位移，二进制文件
//const wchar_t FILE_VECT_BIN[]=L"BVE";  //动力分析结点速度，二进制文件
const wchar_t FILE_SPEED_BIN[] = L"BDS";  //动力分析结点速度，二进制文件，由位移文件计算
//const wchar_t FILE_ACCE_BIN[]=L"BAC";  //动力分析结点加速度，二进制文件
const wchar_t FILE_ACCE_BIN[] = L"BDS";  //动力分析结点加速度，二进制文件，由位移文件计算
const wchar_t FILE_ENERGY_BIN[]=L"BEE";  //动力分析单元能量，二进制文件
const wchar_t FILE_STIFF_BIN[]=L"ESC";  //动力分析单元等效刚度系数，二进制文件
const wchar_t FILE_FORCE_BIN[]=L"EFT";  //动力分析单元内力，选择集，二进制文件
const wchar_t FILE_STRESS_BIN[]=L"FST"; //动力分析单元应力应变，选择集，二进制文件
const wchar_t FILE_STRAIN_BIN[]=L"EST"; //动力分析单元变形，选择集，二进制文件
const wchar_t FILE_DAMAGE_BIN[]=L"ECR"; //混凝土损伤的强度折减系数，选择集，二进制文件
const wchar_t FILE_REBAR_PLASTIC_STRAIN_BIN[]=L"ERP"; //钢筋的塑性应变，选择集，二进制文件
const wchar_t FILE_STEEL_PLASTIC_STRAIN_BIN[]=L"ESP"; //钢材的塑性应变，选择集，二进制文件
const wchar_t FILE_TOP_STORY_FORCE_BIN[]=L"EMT";		//动力分析层间顶部单元内力，固定选择集，二进制文件
const wchar_t FILE_BOTTOM_STORY_FORCE_BIN[]=L"EMB";		//动力分析层间底部单元内力，固定选择集，二进制文件
const wchar_t FILE_STRU_FORCE_BIN[]=L"BSF";				//动力分析构件内力，固定选择集，二进制文件
const wchar_t FILE_STRU_AS_BIN[]=L"BSA";				//动力分析构件配筋面积，固定选择集，二进制文件
const wchar_t FILE_ELEM_PERFORM_BIN[]=L"BEP";				//动力分析单元性能水平，固定选择集，二进制文件
const wchar_t FILE_STRU_PERFORM_BIN[]=L"BSP";				//动力分析构件性能水平，固定选择集，二进制文件
const wchar_t FILE_DAMPER_PERFORM_BIN[] = L"BDP";			//动力分析一般连接性能水平，固定选择集，二进制文件
const wchar_t FILE_STRU_STIFF_BIN[]=L"BSR";				//构件刚度折减系数，仅最终时刻，固定选择集，二进制文件
const wchar_t FILE_ELEM_HINGE_BIN[]=L"BEH";				//动力分析单元塑性铰，固定选择集，二进制文件
const wchar_t FILE_STORY_DRIFT_BIN[]=L"SDR";			//层间位移角、层间位移、层位移，分组，二进制文件
const wchar_t FILE_STORY_RESIDUAL_BIN[] = L"RSD";		//残余变形
const wchar_t FILE_STORY_ENERGY_BIN[]=L"SENG";			//层间位移角、层间位移、层位移，分组，二进制文件
const wchar_t FILE_TOTALENERGY_BIN[]=L"ENG";			//全楼能量，二进制文件
const wchar_t FILE_STORY_SHEAR_BIN[]=L"SSH";			//层间剪力，二进制文件
const wchar_t FILE_SUPPORT_FORCE_BIN[] = L"SUF";			//支座反力，二进制文件
//const wchar_t FILE_ELM_BLOCK_INDEX[]=L"EBI";  //每个单元的分块索引，用于与F-5文件配合使用，二进制文件,无选择集
//const wchar_t FILE_TEMP_BIN[]=L"TMP";  //动力分析结点温度，二进制文件
const wchar_t FILE_OUTPUT_DEF[]=L"DEF";  //按楼层输出长柱子结点，文本文件，分组，用于输出接口，依赖于网格
const wchar_t FILE_OUTPUT_DED[]=L"DED";  //按楼层输出长柱子对应的层间位移角，文本文件，分组，依赖于网格
const wchar_t FILE_STRU_STRESSRATIO_BIN[]=L"BSS";				//动力分析构件配筋面积，固定选择集，二进制文件
const wchar_t FILE_LINK_BIN[]=L"LIK";										//一般连接动力分析结果，二进制文件
const wchar_t FILE_REBAR_STRESS_BIN[]=L"ERS";		//单元最大钢筋应力，二进制文件
const wchar_t FILE_STEEL_STRESS_BIN[]=L"ESS";		//单元最大钢材应力，二进制文件
const wchar_t FILE_SHEAR_COMPRESSION_RATIO_BIN[] = L"SCRS"; //剪压比，二进制文件
const wchar_t FILE_SHEAR_COMPRESSION_RATIO_ELM_BIN[] = L"SCRE";//剪压比单元存储，仅用于云图渲染，二进制文件
const wchar_t FILE_SHEAR_SPAN_RATIO_BIN[] = L"SSRS";//剪跨比，二进制文件
const wchar_t FILE_SHEAR_SPAN_RATIO_ELM_BIN[] = L"SSRE";//剪跨比单元储存，仅用于云图渲染，二进制文件
const wchar_t FILE_NOMINAL_TENSILE_STRESS_BIN[] = L"NTSS"; //名义拉应力，二进制文件
const wchar_t FILE_NOMINAL_TENSILE_STRESS_ELM_BIN[] = L"NTSE"; //名义拉应力单元存储，仅用于云图渲染，二进制文件
const wchar_t FILE_NOMINAL_TENSILE_STRESS_RATIO_ELM_BIN[] = L"NTSR";//名义拉应力比单元存储，仅用于云图渲染，二进制文件
const wchar_t FILE_AXIAL_COMP_COEF_BIN[] = L"ATC";//轴压力系数，二进制文件
const wchar_t FILE_AXIAL_COMP_COEF_ELM_BIN[] = L"ATCE";//轴压力系数单元储存，仅用于云图渲染，二进制文件
const wchar_t FILE_AXIAL_COMP_RATIO_BIN[] = L"ATR";//轴压力系数，二进制文件
const wchar_t FILE_AXIAL_COMP_RATIO_ELM_BIN[] = L"ATRE";//轴压力系数单元储存，仅用于云图渲染，二进制文件
const wchar_t FILE_SHEAR_STRESS_BIN[] = L"SRS";//抗剪承载力，二进制文件
const wchar_t FILE_SHEAR_STRESS_EELM_BIN[] = L"SREE";//抗剪承载力弹性存储，仅用于云图渲染，二进制文件
const wchar_t FILE_SHEAR_STRESS_KELM_BIN[] = L"SREK";//抗剪承载力不屈服存储，仅用于云图渲染，二进制文件
const wchar_t FILE_SHEAR_STRESS_LELM_BIN[] = L"SREL";//抗剪承载力极限存储，仅用于云图渲染，二进制文件
const wchar_t FILE_MOMENT_BIN[] = L"SMS";//抗弯承载力，二进制文件
const wchar_t FILE_MOMENT_EELM_BIN[] = L"SME";//抗剪承载力弹性存储，仅用于云图渲染，二进制文件
const wchar_t FILE_MOMENT_SHEAR_RATIO_BIN[] = L"MSR";//弯剪比，二进制文件
const wchar_t FILE_MOMENT_SHEAR_RATIO_ELM_BIN[] = L"MSRE";//弯剪比存储，仅用于云图渲染，二进制文件
const wchar_t FILE_DISP_ANGLE_BIN[] = L"DIA";//广东省位移角，二进制文件
const wchar_t FILE_DISP_ANGLE_ELM_BIN[] = L"DIAE";//广东省位移角单元存储，仅用于云图渲染，二进制文件
const wchar_t FILE_DISP_ANGLE_XUE_BIN[] = L"DIAX";//构件受力位移角，二进制文件
const wchar_t FILE_DISP_ANGLE_XUE_ELM_BIN[] = L"DIAXE";//构件受力位移角单元存储，仅用于云图渲染，二进制文件
const wchar_t FILE_DUCTILITY_RATIO_BLAST_BIN[] = L"DRB";//抗爆延性比，二进制文件

const wchar_t Sys_Group_All[]=L"All";  //内置全集名称
const int Sys_Group_All_ID=9999;  //内置全集ID
const wchar_t Sys_IData_FIle[]=L"IDataSwap";  //用于有限元数据交换文件

const wchar_t Sys_ClipBoard[]=L"SAUSAGE";

//拾取图元
const int Sys_SelectRange=10;  //拾取区域范围,单位:像素
//const int Sys_SelectRange=3;  //拾取区域范围,单位:像素	//乔保娟2016.7.19

//拾取返回的图元名称的起始编码,此顺序也代表了拾取的优先级
const int Sys_VirtualPointName0= 1       ;  //虚点
const int Sys_VertexName0=		 1000    ;  //第一个顶点名称，用于拾取
const int Sys_BeamName0=         10000000;  //第一个梁结构/单元名称，用于拾取
const int Sys_PillarName0=       20000000;  //第一个柱结构/柱单元名称，用于拾取
const int Sys_BracingName0=      30000000; 
const int Sys_EdgeName0=         40000000; 
const int Sys_HideBeamName0=     50000000; 
const int Sys_LongiRebarName0=   60000000; 
const int Sys_StructLineName0=   70000000;  //第一个结构线单元名称，用于拾取
const int Sys_GuidesName0=       80000000;  //第一个辅助线单元名称，用于拾取
const int Sys_PlateName0=        90000000;  //第一个板结构/面单元名称
const int Sys_WallName0=        100000000;  //第一个墙结构/墙单元名称
const int Sys_BodyName0=        110000000;  //第一个实体单元名称，用于拾取
const int Sys_NodeName0=        120000000;  //单元结点
const int Sys_ShadowPointName0= 130000000; 
const int Sys_BeamElmName0=     140000000;  //梁单元
const int Sys_Tri3ShellName0=   150000000;  //三结点三角形壳单元
const int Sys_Quad4ShellName0=  160000000;  //四结点四边形单元
const int Sys_ShadowPolyName0=  170000000; 
const int Sys_LinkName0=		180000000;	//乔保娟 2015.5.20

const int Sys_MaxName0=         220000000;  //最大图元编码

//物理场
const int Sys_Max_Node_Components=8; //最大结点物理量分量数
//const int Sys_Max_Elm_Components=16; //最大单元物理量分量数
const int Sys_Max_Story_Components=20; //最大楼层物理量分量数
const float Sys_DeformRatio=1000.0f; //变形倍数
const float Sys_StaticLoadTime=1.0f;  //竖向荷载加载时间

//数组大小
const int Sys_Max_View=4;  //最大视图窗口数
const int Sys_BoundaryArray=500; //面结构的最大边界点数目
const int Sys_MaxPSize=5000;  //mesh2d中用到的最大结点数
const int Sys_MaxESize=5000;  //mesh2d中用到的最大单元数
const int Sys_SUFFERED=100; //网格优化中用到的数组,插入一个点后受影响的三角形最大个数
const int Sys_IncAlloc=10000; //内存不够时realloc增加的规模
const int Sys_SubSectionParaNum=200;  //子截面几何参数个数，要与实际情况精确相符;  2020版本将最大点数改为 49， 原来12为6个点
const int Sys_MaxPoly=5; //一个截面中多边形边界的最大数量，包括外边界和内边界。一个独立区域是一个截面，可以是复连通域，一个截面必须是单一材料
const int Sys_MaxLabel =10; //一个截面最大标注数
const int Sys_Max_Stories  =300; //最大楼层
const int Sys_Max_Towers  =30; //最大塔数
const int Sys_DOF=6; //结点最大自由度
const int Sys_Max_ComponentLength =16; //分量名最大长度，字符数
const int Sys_Max_Connect_Wall =4;  //每个点最多关联的墙体数量
const int Sys_MAX_NEIGHBOR =100 ;  //一个结点周围最多三角形数
const int SYS_MAX_NEIGHBOR_IN_PLANE =30 ;  //平面内一个结点周围最多三角形数
const int Sys_StructTypeNum =6 ;  //系统支持的构件类型数	//乔保娟 2015.5.25 //混凝土、钢筋信息，不包括阻尼隔震构件
const int Sys_MaxDriftNum =300 ;  //最大层间位移角位置个数
const int Sys_EQ_Class_Num =6;  //地震级别数
const int Sys_MinModeNum =3 ;	//使用振型阻尼时的最小振型数
const int Sys_MaxModeNum =3000 ; //使用振型阻尼时的最大振型数
const int Sys_MinMRParaNum =2 ;	//使用自定义阻尼器时的最小数据点数
const int Sys_MaxMRParaNum =12 ;	//使用自定义速度型阻尼器时的最大数据点数
const int Sys_MaxMRParaNumDis =11 ;	//使用自定义位移型阻尼器时的最大数据点数
const int Sys_Material_Number =25 ;  //内置材料个数
const int Sys_CheckErrors = 31; //检查模型的项数
const int MAX_POLYGONPOINT =500;
const int Sys_MinPerformGrade=3;	//最少性能等级//2015.12.9
const int Sys_MaxPerformGrade=6;	//最多性能等级
const int Sys_MinHingeGrade=3;	//最多塑性铰等级
const int Sys_MaxHingeGrade=6;	//最多塑性铰等级
const int Sys_MaxLoadcase=20;	//最多荷载工况
const int Sys_MaxLoadcaseComb=200;	//最多荷载组合
const int Sys_MaxLoad=50;//最多荷载数


//状态栏设置
const int Sys_Pane_Coor=2;  //动态坐标显示状态栏
const int Sys_Pane_Case=3;  //工况信息显示状态栏
const int Sys_Pane_Step=4;  //时间步信息显示状态栏

//其它常数
const int Sys_Quad_Elm0=0x10000000;  //三角形和四边形单元统一编号时，四边形单元的开始编号，三角形单元从0开始
//const float Sys_StraightCosValue=0.94f;   //用于判断墙边线共线的方向余弦阈值，小于20度或大于160度则为共线
const float Sys_StraightCosValue=0.996f;   //用于判断墙边线共线的方向余弦阈值，小于5度或大于175度则为共线  //乔保娟 2015.2.13
const float Sys_MinPermitLineLength=0.3f;  //开洞和错位等设计原因造成的最小允许结构线尺寸，小于（不等于）该尺寸则使竖向结构线倾斜以消除短线
const float Sys_MinBraceAngle=20.0f;


#ifdef _SIMPLIFIED_CHINESE
const wchar_t Sys_DefaultFontName[]= L"宋体" ;  //缺省字体
#else
const wchar_t Sys_DefaultFontName[]=L"Arial";   //缺省字体
#endif

const int Sys_DefaultFontSize=12;        //字体大小，单位：像素,12像素=9磅

const wchar_t Sys_MakeLevelCase[]=L"make_level";  //找平用的工况名称

const int Sys_RC_Double_ConcFibre=36;		//普通双向RC截面混凝土纤维剖分数
const int Sys_RC_Single_ConcFibre=12;		//普通单向RC截面混凝土纤维剖分数
const int Sys_ST_SteelFibre=16;				//普通ST截面型钢纤维剖分数
const int Sys_CFT_SteelFibre=24;			//普通CFT截面型钢纤维剖分数
const int Sys_SRC_SteelFibre=16;			//普通SRC截面型钢纤维剖分数
const int Sys_Rebar=8;						//钢筋数
const int Sys_Rebar_Simple = 4;				//钢筋数  粗划 目前用于加固内芯
const int Sys_PlateConcLayer=1;	            //楼板的混凝土分层数
const int Sys_WallConcLayer=6;	            //墙的混凝土分层数
const int Sys_Rebar_RF_Fiber = 8;			//钢筋数  粗划 目前用于碳纤维加固截面，碳纤维用钢筋模拟

const int Sys_Arbitrary_ConcFibre=36;			//任意混凝土纤维截面数
const int Sys_Arbitrary_SteelFibre=64;			//任意钢纤维截面数

const int Sys_Geo_Num =6;				   //截面参数个数
const int Sys_Max_ModalDamage =100  ;      //一次最大实时模态分析个数

const int Sys_nLinkHead=5;			  //一般连接总体参数个数，用于中间数据
const int Sys_nLinkData =30;          //一般连接单自由度最大数据量，用于中间数据

const int Sys_nCrt1D_c =20;				//混凝土一维本构受压区点数
const int Sys_nCrt1D_t =10;				//混凝土一维本构受拉区点数
const int Sys_nCrt2D_c =21;				//混凝土二维本构受压区点数
const int Sys_nCrt2D_t =10;				//混凝土二维本构受拉区点数

//以下枚举值如果被明确定义数值了，则有特殊含义，不要随意更改

//材料类型，枚举值不得随意更改
enum MATERIAL_TYPE
{
	MAT_UNKNOWN		= 0, //未定义
	MAT_CONC		= 1, //混凝土
	MAT_REBAR		= 2, //钢筋
	MAT_STEEL		= 4, //型钢和钢板
	MAT_TENDON		= 8, //预应力筋材料
	MAT_LINK_EQV	= 16,
	MAT_MASONRY		= 32, // 砌体
	MAT_ALUMINIUM	= 64, // 铝合金
	MAT_FIBRE		= 256, // 纤维复合材料
	MAT_CONC_ALL	= MAT_CONC | MAT_MASONRY,
	MAT_REBAR_ALL	= MAT_REBAR | MAT_TENDON| MAT_FIBRE,
	MAT_STEEL_ALL	= MAT_STEEL | MAT_TENDON | MAT_ALUMINIUM,
	MAT_STEEL_ALL_REINFORCED = MAT_STEEL | MAT_TENDON | MAT_ALUMINIUM ,
};



//结构类型,实际上代表几何数据类型
enum STRUCT_TYPE
{
	STRUCT_UNKNOWN 		=0,          //未知

	//基础图元，分别存放在不同数组中
	STRUCT_VEX   		=0x01,       //点,包括构件点和网格点，捕捉网格点用STRUCT_NODE
	STRUCT_LINE    		=0x02,       //结构线

	//线状构件，存放在同一数组中
	STRUCT_BEAM    		=0x04,       //框架梁
	STRUCT_PILLAR  		=0x08,       //柱
	STRUCT_BRACING 		=0x10,       //斜撑
	STRUCT_EDGE			=0x20,       //边缘构件
	STRUCT_HIDEBEAM		=0x40,       //暗梁（虚梁）
	STRUCT_LONGIREBAR	=0x80,       //连梁纵筋
	STRUCT_LINK			=0x100,		//一般连接


	//面状构件，存放在同一数组中
	STRUCT_PLATE   		=0x1000,      //板
	STRUCT_WALL    		=0x2000,      //墙，包括墙梁
	STRUCT_GUIDES    	=0x10000,     //辅助线
	STRUCT_BODY    		=0x20000,      //实体，暂时不用

	//单元类型，分别存放在不同数组中
	STRUCT_NODE   		=0x100000,    //网格点，仅用于捕捉
	STRUCT_BEAM_ELM		=0x200000,    //梁单元，BEAM
	STRUCT_TRI3_SHELL	=0x400000,	  //三结点三角形壳单元，TRI3
	STRUCT_QUAD4_SHELL	=0x800000,	  //四结点四边形单元，QUAD

	//虚点
	STRUCT_VIRTUAL_POINT=0x1000000,

	//以下类型组合不能用于GetIDG，只用于逻辑判断
	STRUCT_ALL_BEAM		=STRUCT_BEAM | STRUCT_HIDEBEAM | STRUCT_LONGIREBAR ,  //广义梁构件,水平线构件	//乔保娟 2015.5.21
	STRUCT_ALL_PILLAR	=STRUCT_PILLAR | STRUCT_BRACING | STRUCT_EDGE ,  //广义柱构件，非水平线构件
	STRUCT_ALL_1DSTRUCT =STRUCT_ALL_BEAM | STRUCT_ALL_PILLAR|STRUCT_LINK,  //所有的线构件，对应m_cBeam全部数据
	STRUCT_ALL_2DSTRUCT =STRUCT_PLATE | STRUCT_WALL,  //所有的面构件，对应m_cPlate全部数据
	STRUCT_BEAMWALL		=STRUCT_BEAM|STRUCT_WALL, //墙梁，不是独立构件	
	STRUCT_ALL_SEMIRIGID = STRUCT_BEAM | STRUCT_PILLAR | STRUCT_BRACING,  // 半刚性连接(梁、柱、斜撑) 辛业文 2023年1月8日
	//STRUCT_ALL			=0x7fffffff,  //全部捕捉，包括结构线
	STRUCT_ALL			=STRUCT_ALL_1DSTRUCT|STRUCT_ALL_2DSTRUCT|STRUCT_VEX,  //全部捕捉，包括结构线	//乔保娟 2016.7.15
};

enum STRUCT_SUBTYPE_WALL
{
	STRUCT_WALL_UNKNOWN 		=0,		//未知
	STRUCT_WALL_WALLCOL			=0x01,	//墙柱
	STRUCT_WALL_WALLBEAM		=0x02,	//墙梁
};

//结构类型,实际上代表几何数据类型
enum LINK_SUBTYPE
{
	LINK_UNKNOWN 			=0,		//未知
	LINK_VELODAMPER			=0x1,	//阻尼器-速度型 //乔保娟2015.5.19	
	LINK_ISOLATOR			=0x2,	//隔震支座
	LINK_BRB				=0x4,	//BRB 
	LINK_SPRING				=0x8,	//弹簧
	LINK_USERDAMPERVEL		=0x10,//自定义速度型阻尼器
	LINK_DISPDAMPER			=0x20,
	LINK_CABLE				=0x40,
	LINK_GAP				=0x80,
	LINK_FRICPND			=0x100,
	LINK_HOOK				=0x200,
	LINK_USERDAMPERDIS		=0x400,//自定义位移型阻尼器
	LINK_WEN				=0x800,//Wen模型
	LINK_ISOLATOR3D			=0x1000,//三向耦合隔震支座
	LINK_TMD				=0x2000,//TMD
	LINK_PRESTRJOIN			=0x4000,//预应力连接键
	LINK_MAXWELL			=0x8000,//Maxwell 模型
	LINK_ESB				=0x10000,//弹性滑板支座
	LINK_RIGID				=0x20000,//刚性楼板
	LINK_KELVINSPRING		=0x40000,//Kelvin串联弹簧
	LINK_USER				=0x80000,//用户自定义
	LINK_TVMD				=0x100000,//调谐粘滞质量阻尼器
	LINK_ALL_LRB=LINK_ISOLATOR|LINK_ISOLATOR3D,
	LINK_ALL_ISOBEARING=LINK_ALL_LRB|LINK_FRICPND|LINK_ESB,
	LINK_VDAMPER	=LINK_VELODAMPER|LINK_MAXWELL|LINK_KELVINSPRING| LINK_USERDAMPERVEL,
	LINK_DDAMPER	=LINK_BRB| LINK_DISPDAMPER| LINK_USERDAMPERDIS| LINK_WEN| LINK_TMD | LINK_TVMD,
};

struct LinkName
{ 
	const wchar_t *sName;
	LINK_SUBTYPE iType;
};
const struct LinkName LinkNamesArray[]=
{
#ifdef _SIMPLIFIED_CHINESE
	L"速度型阻尼器(Kelvin)",LINK_VELODAMPER,
	L"速度型阻尼器(Maxwell)",LINK_MAXWELL,
	L"速度型阻尼器(Kelvin串联弹簧)",LINK_KELVINSPRING,
	L"位移型阻尼器(二折线)",LINK_DISPDAMPER,
	L"自定义速度阻尼器",LINK_USERDAMPERVEL,
	L"自定义位移阻尼器",LINK_USERDAMPERDIS,  // 辛业文 半刚性连接增加自定义位移型 2022年12月13
	L"调频质量阻尼器",LINK_TMD,
	L"防屈曲支撑",LINK_BRB,
	L"橡胶隔震支座(二折线)",LINK_ISOLATOR,
	L"橡胶隔震支座(Wen)",LINK_ISOLATOR3D,
	L"弹性滑板支座",LINK_ESB,
	L"摩擦摆支座",LINK_FRICPND,
	L"Wen模型",LINK_WEN,
	L"线性弹簧",LINK_SPRING,
	L"拉索",LINK_CABLE,
	L"钩",LINK_HOOK,
	L"间隙",LINK_GAP,
	L"自定义阻尼器",LINK_USER,
	L"调谐黏滞惯容系统",LINK_TVMD,
	//L"预应力连接键",LINK_PRESTRJOIN,
#else
	L"Dampers-Velocity(Kelvin)",LINK_VELODAMPER,
	L"Dampers-Velocity(Maxwell)",LINK_MAXWELL,
	L"Dampers-Velocity(Kelvin-spring)",LINK_KELVINSPRING,
	L"Dampers-Displacement",LINK_DISPDAMPER,
	L"Dampers-Velo User defined",LINK_USERDAMPERVEL,
	L"Dampers-Disp User defined",LINK_USERDAMPERDIS,
	L"TMD",LINK_TMD,
	L"BRB",LINK_BRB,
	L"Rubber Isolators(Bilinear curve)",LINK_ISOLATOR,
	L"Rubber Isolators(Wen)",LINK_ISOLATOR3D,
	L"Elastic Slide Bearing",LINK_ESB,
	L"Friction Pendulum",LINK_FRICPND,
	L"Plastic(Wen)",LINK_WEN,
	L"Spring",LINK_SPRING,	
	L"Cable",LINK_CABLE,
	L"Hook",LINK_HOOK,
	L"Gap",LINK_GAP,
	L"User Defined Damper",LINK_USER,
	L"TVMD",LINK_TVMD,
	//L"Prestressed Join-key",LINK_PRESTRJOIN
#endif
};

//组类型定义
enum GROUP_STYLE
{
	STYLE_BEAM=0,		//梁式
	STYLE_COUPLING,	//连梁式
	STYLE_BRACING,	    //撑式
	STYLE_WALL,				//墙板式:点击
	STYLE_WALL2,			//墙板式:自建墙
	STYLE_WALL3,			//墙板式:自建墙
	STYLE_WALL4,			//墙板式:加劲钢板墙
	STYLE_INVY1,				//正人字1型
	STYLE_Y1,					//倒人字1型
	STYLE_INVY2,				//正人字2型
	STYLE_Y2,					//倒人字2型
	STYLE_INVY3,				//正人字3型
	STYLE_Y3,					//倒人字3型
	STYLE_INVY4,				//正人字4型
	STYLE_Y4,					//倒人字4型
	STYLE_V,						//正V字型 ",L
	STYLE_INVV,				//倒V字型 ",L
	STYLE_DISAMP1,		//位移放大器1
	STYLE_DISAMP2,		//位移放大器2
	STYLE_DISAMP3,		//位移放大器3
	STYLE_DISAMP4,		//位移放大器4
	STYLE_USER1,			//自定义串联
	STYLE_USER2,			//自定义串并联
};	

struct LinkGroupStyle
{ 
	const wchar_t *sName;
	GROUP_STYLE iType;
};

//样式列表
const struct LinkGroupStyle sGroup_Style[]={
#ifdef _SIMPLIFIED_CHINESE
	L"梁式",						STYLE_BEAM,	
	L"连梁式",             		STYLE_COUPLING,
	L"撑式 ", 					STYLE_BRACING,	
	L"墙板式1 ", 				STYLE_WALL,			
	L"墙板式2 ", 				STYLE_WALL2,		
	L"墙板式3 ", 				STYLE_WALL3,
	L"加劲钢板墙 ", 			STYLE_WALL4,
	L"正人字1型 ",			STYLE_INVY1,			
	L"倒人字1型 ",			STYLE_Y1,				
	L"正人字2型 ",			STYLE_INVY2,			
	L"倒人字2型 ",			STYLE_Y2,				
	L"正人字3型 ",			STYLE_INVY3,			
	L"倒人字3型 ",			STYLE_Y3,				
	L"正人字4型",			STYLE_INVY4,			
	L"倒人字4型 ",			STYLE_Y4,				
	L"正V字型 ",				STYLE_V,					
	L"倒V字型 ",				STYLE_INVV,			
	L"位移放大器1 ",		STYLE_DISAMP1,	
	L"位移放大器2",		STYLE_DISAMP2,	
	L"位移放大器3 ",		STYLE_DISAMP3,	
	L"位移放大器4 ",		STYLE_DISAMP4,	
	L"自定义串联 ",		STYLE_USER1,
	L"自定义并联 ",		STYLE_USER2
#else
	L"Beam",                                        STYLE_BEAM,	
	L"Coupling Beam",					  STYLE_COUPLING,
	L"Bracing",									 STYLE_BRACING,	
	L"Wall1",								 STYLE_WALL,			
	L"Wall2",								 STYLE_WALL2,		
	L"Wall3",								 STYLE_WALL3,	
	L"加劲钢板墙 ", 						 STYLE_WALL4,
	L"Inverted Y-shape1",		  STYLE_INVY1,			
	L"Y-shape1",					   STYLE_Y1,				
	L"Inverted Y-shape2",		  STYLE_INVY2,			
	L"Y-shape2",					   STYLE_Y2,				
	L"Inverted Y-shape3",		  STYLE_INVY3,			
	L"Y-shape3",					   STYLE_Y3,				
	L"Inverted Y-shape4",		 STYLE_INVY4,			
	L"Y-shape4",					   STYLE_Y4,				
	L"V-shape",							   STYLE_V,					
	L"Inverted V-shape",			 STYLE_INVV,			
	L"Disp Amp1",				  STYLE_DISAMP1,	
	L"Disp Amp2",				  STYLE_DISAMP2,	
	L"Disp Amp3",				  STYLE_DISAMP3,	
	L"Disp Amp4",				  STYLE_DISAMP4,	
	L"User Define1",				   STYLE_USER1,
	L"User Define2 ",		           STYLE_USER2
#endif
}; 

//物理场类型
enum FIELD_TYPE
{
	FIELD_NONE=0,

	//以下为结点场
	FIELD_STATIC_DISP=0x0001,  //竖向荷载结点位移
	FIELD_MODAL		=0x0002,  //模态振型
	FIELD_DISP		=0x0004,  //结点位移
	FIELD_TEMP		=0x0008,  //结点温度
	FIELD_ACCE		=0x0010,  //结点加速度
	FIELD_SPEED		=0x0020,  //结点速度
	FIELD_MODAL_DAMAGE	=0x0012,  //实时模态振型
	FIELD_ENERGY		=0x0040,  //结点能量
	FIELD_BUCKLING		=0x0080,  //屈曲模态
	FIELD_DEFECT	  =0x0100,  //缺陷
	FIELD_MAXMODAL	=0x0200,  //最大频率

	FIELD_CMODAL	=0x0400,  //模态振型
	FIELD_CMODAL_DISP = 0x0800, // 复模态节点位移

	//以下为单元场，第16位为0
	FIELD_STRESS=0x10001,  //单元应力
	FIELD_STRAIN=0x10002,  //单元应变
	FIELD_FORCE =0x10004,   //单元内力
	FIELD_DAMAGE=0x10008,  //单元损伤
	FIELD_REBAR_PLASTIC_STRAIN=0x10010,  //单元塑性应变
	FIELD_STEEL_PLASTIC_STRAIN=0x10020,  //单元塑性应变
	FIELD_TOP_STORY_FORCE     =0x10040,  //楼层间顶部单元内力
	FIELD_BOTTOM_STORY_FORCE  =0x10080,  //楼层间底部单元内力
	FIELD_REBAR_STRESS=0x10100,  //单元钢筋应力
	FIELD_STEEL_STRESS=0x10200,  //单元钢材应力
	FIELD_LINK =0x10400,  //一般连接

	FIELD_PERFORM			=0x100400,  //单元性能
	FIELD_PERFORM_STRU		=0x100800,  //构件性能
	FIELD_HINGE				=0x101000,  //塑性铰

	FIELD_SHEAR_COMPRESSION_RATIO		= 0x1000000,//剪压比，判断比例输出为&0x10000，绕过0x110000
	FIELD_SHEAR_SPAN_RATIO				= 0x1020000,//剪跨比
	FIELD_NOMINAL_TENSILE_STRESS		= 0x1040100,//名义拉应力//避开速度及加速度场
	FIELD_NOMINAL_TENSILE_STRESS_RATIO	= 0x1040200,//名义拉应力比
	FIELD_AXIAL_COMPRESSION_COEF		= 0x1040400,//轴压力系数
	FIELD_AXIAL_COMPRESSION_RATIO		= 0x1040800,//轴压比
	FIELD_SHEAR_STRESS_ELA_RATIO		= 0x1080100,//抗剪承载力//避开速度及加速度场
	FIELD_MOMENT_SHEAR_RATIO	= 0x1080200,//抗剪承载力//避开速度及加速度场
	FIELD_FLEXURAL_BEARING_CAPACITY	= 0x1080800,//抗剪承载力//避开速度及加速度场
	FIELD_DISP_ANGLE					= 0x1080400,

	//韧性评价
	FIELD_RES_RESULT					= 0x1081000,
	//非线性屈曲分析
// 	FIELD_DISP					=0x10000004,  //结点位移 
// 	FIELD_DAMAGE				=0x10010008,  //单元损伤
// 	FIELD_REBAR_PLASTIC_STRAIN	=0x10010010,  //单元塑性应变
// 	FIELD_STEEL_PLASTIC_STRAIN	=0x10010020,  //单元塑性应变
// 	FIELD_PERFORM				=0x10100400,  //单元性能
// 	FIELD_PERFORM_STRU			=0x10100800,  //构件性能

};

enum PERFORM_FIELD
{
	PERFORM_NONE	=0,		//未知
	PERFORM_DC		=0x1,		//未知
	PERFORM_DT		=0x2,		//未知

	PERFORM_SIGMAP	=0x4,		//未知
	PERFORM_HINGE1	=0x8,		//未知
	PERFORM_HINGE2	=0x10,		//未知
	PERFORM_DAMPER	=0x12,		//2020.7.1王丹
};
//图例类型
enum LEGEND_TYPE
{
	LEGEND_ALLSTEP,          //按全程极值配置颜色
	LEGEND_ALLSTEP_VISIBLE,  //全程可见构件
	LEGEND_MOMENT,           //按瞬时极值配置颜色
	LEGEND_MOMENT_VISIBLE,   //瞬时可见构件
	LEGEND_USER,             //用户输入最大最小值
};

//变形图类型
enum DEFORM_TYPE
{
	DEFORM_NONE,  //不变形
	DEFORM_MODAL, //模态振型
	DEFORM_STATIC, //静力加载位移
	DEFORM_DYNA,   //动力加载位移
	DEFORM_SPECT,  //反应谱工况位移
	DEFORM_DEFECT, //缺陷
};

//建模范围
enum BUILDRANGE
{
	RANGE_INVALID=-1,
	RANGE_THISSTORY=0, //本楼层
	RANGE_ALLSTORIES=1,  //所有楼层
	RANGE_GROUP=2,     //本组
};

//视图类型
enum DRAWTYPE
{
	DRAWTYPE_UNKNOWN=0,
	DRAWTYPE_XY=0x01,
	DRAWTYPE_3D=0x02,
	DRAWTYPE_YZ=0x04,
	DRAWTYPE_ZX=0x08,
	DRAWTYPE_PROFILE=0x10,  //二维剖面图
	DRAWTYPE_CROSSSECTION=0x20,  //二维断面图
};

//鼠标左键工具状态
enum TOOLSTATUS
{
	TOOL_ASSIGNDRIFT,  //指定层间位移角输出位置(竖向构件)
	TOOL_ASSIGNDRIFT_ZONE, //框选指定层间位移角输出位置
	TOOL_BREAKLINE,   //用鼠标插入点，断开结构线
	TOOL_CLICKBEAM, //点击生成梁
	TOOL_CLICKPILLAR, //点击生成柱
	TOOL_CLICKBRACE, //点击生成斜撑
	TOOL_CLICKPLATE, //点击生成板
	TOOL_CLICKWALL, //点击生成墙
	TOOL_CHECKCROSS,   //强制布尔运算
	TOOL_DEFINECROSSSECTION,   //捕捉2个点，在第三个窗口显示断面图
	TOOL_DEFINEPROFILE,   //捕捉2个点和一个方向，在第三个窗口显示剖面图
	TOOL_DRAWBEAM, //绘梁结构
	TOOL_DRAWBRACING,  //绘制斜撑
	TOOL_DRAWLINK,  //绘制一般连接
	TOOL_CLICKLINK, //点击生成一般连接
	TOOL_CLICKDAMPERGROUP,//点击生成减震组件
	TOOL_DRAWDAMPERGROUP,//两点建减震组件

	TOOL_DRAWGUIDELINE, //绘辅助线
	TOOL_DRAWPILLAR,  //绘制柱
	TOOL_DRAWPLATE, //捕捉点围成板或墙
	TOOL_DRAWSTRUCTLINE, //绘结构线
	TOOL_DRAWWALL,  //绘制墙
	TOOL_CLICKDISSIPWALL,  //点击梁绘制消能墙
	TOOL_DRAWZONEBEAM, //按区域生成梁
	TOOL_DRAWZONEPILLAR, //按区域生成柱
	TOOL_DRAWZONEPLATE, //按区域生成板
	TOOL_DRAWZONELINK, //按区域生成一般连接
	TOOL_EDIT_MOVE,       //用鼠标捕捉两点构成矢量，移动剪辑板中的选择集
	TOOL_EDIT_PASTE,      //用鼠标捕捉粘贴参考点
	TOOL_EXTENDLINE,       //延伸线段带最近的相交线段,包括
	TOOL_HOLEWALL, //墙上开洞
	TOOL_MEASURE_DIST,       //测量两点距离
	TOOL_MEASURE_ANGLE,       //测量角度
	TOOL_MODIFYLINE,   //给定距离移动结构线，不能移动单点
	TOOL_MODIFYVERTEX, //用鼠标移动点
	TOOL_COPYVERTEX, //复制点构件不联动 邱海2016.01.29
	TOOL_MODIFY_PILLARANGLE,   //捕捉2个点，设置所选柱子的旋转角
	TOOL_SELECT_ZONE,  //框选图形
	TOOL_SET2NDBEAM, //设置次梁
	TOOL_SETANTICULATE, //设置铰接
	TOOL_SETANTICULATEONEDIRECTION1, //设置1端铰接 涂天驰20241030
	TOOL_SETANTICULATEONEDIRECTION2, //设置2端铰接 涂天驰20241030
	TOOL_SETANTICULATETWODIRECTION, //设置两端铰接 涂天驰20241030
	TOOL_SETMAINBEAM, //设置主梁
	TOOL_MERGELINE,   //合并重叠的结构线
	TOOL_WELDINGLINE, //删除分隔点，焊接线
	TOOL_WELDINGSURF, //删除分割线，焊接面
	TOOL_ZOOMIN,  //窗口放大
	TOOL_GETNODE, //拾取节点 邱海2016年3月3日
	TOOL_GETNODECOOR1, //捕捉切割线起点坐标 周璋鑫2022年11月9日
	TOOL_GETNODECOOR2, //捕捉切割线终点坐标 周璋鑫2022年11月9日
	TOOL_DRAWCUTLINE, //捕捉节点绘制切割线 周璋鑫2023年2月10日
	TOOL_DRAGMESHNODE, //捕捉节点移动节点 周璋鑫2023年3月17日
	TOOL_GETMESHNODE, //拾取网格节点 周璋鑫2022年11月22日
	TOOL_GETREMOVEMESHNODE, //拾取待移除的网格节点 周璋鑫2022年11月24日
	TOOL_GETMESHID, //拾取合并/删除的网格 周璋鑫2022年11月29日
	TOOL_GETMERGEMESHID, //拾取合并 周璋鑫2023年3月22日
	TOOL_GETDELETEMESHID, //删除的网格 周璋鑫2023年3月22日
    //TOOL_SETSTORYBASICPOINT,//设置楼层基点 王丹12/05/2021
	//TOOL_GETPMMSTRUCT,//拾取PMM曲线相关构件 王丹28/05/2021

	TOOL_ALIGNBEAM,//梁平面对齐
	TOOL_MODIFY_REINFORCEMENT,
	TOOL_CLICKDRAWCROSSREBAR,
	TOOL_DRAWCROSSREBARBY2PTS,
	TOOL_LAST, //结尾标识增加命令都放在这前面！！！这个在输出操作提示中有用SetOutputHistory
	TOOL_PICKMERGEORIGIN,	//拼接模型原点选择
	TOOL_DRAWSEMIRIGID,  //半刚性连接Ribbon 辛业文 2022年12月13日 
	TOOL_SETSEMIRIGIDANTICULATE, // 半刚性连接设置鼠标状态为铰接 辛业文 2022年12月27日
	TOOL_DRAWZONESETSEMIRIGID, //平面内生成半刚性连接（设置梁、柱、斜撑） 辛业文 2023年1月11日
	TOOL_DELETEZONESETSEMIRIGID, //平面内生成半刚性连接（设置梁、柱、斜撑） 辛业文 2023年1月11日
	TOOL_SETSTIFFNESSANTICULATE, // 半刚性连接设置鼠标状态为铰接 辛业文 2023年2月7日

	TOOL_ADDREINFORCEDCOMPONENT, //新增加固构件 辛业文  2023年4月18日
	TOOL_DELETEREINFORCEDCOMPONENT, //取消新增加固构件 辛业文  2023年4月18日
	TOOL_DRAWZONEPILLARREINFORCED, // 区域建 柱加固布置 辛业文  2023年6月6日
	TOOL_CLICKPILLARREINFORCED, //点击建 柱加固  辛业文  2023年6月6日
	TOOL_CLICKBEAMREINFORCED, //点击建 梁加固  辛业文  2023年6月6日
	TOOL_DRAWZONEBEAMREINFORCED, // 区域建 梁加固布置 辛业文  2023年6月6日
	TOOL_CANCLEREINFORCED, // 取消梁、柱加固布置 辛业文  2023年6月6日
	TOOL_CLICKWALLREINFORCED, //点击建 墙加固  辛业文  2023年11月1日
	TOOL_CLICKPLATEREINFORCED, //点击建 板加固  辛业文  2023年11月1日
	TOOL_CANCLEREINFORCEDREINFORCED, // 取消墙、板加固布置 辛业文  2023年11月1日
	TOOL_DRAWZONEPLATEREINFORCED, // 区域建 板加固布置 辛业文  2023年11月2日
	TOOL_DRAWZONEWALLREINFORCED, // 区域建 墙加固布置 辛业文  2023年11月2日

	TOOL_CLICKPARTITIONWALLGROUP,//点击生成隔墙组件  辛业文 2024年1月18日
	TOOL_DRAWPARTITIONWALLGROUP, //两点生成隔墙组件  辛业文 2024年1月18日
	TOOL_DRAWPRESTRESSINGTENDONGROUP,  // 两点建立预应力筋组 辛业文 2023年3月3日
};

//选取区域，修改参数类别
enum MODIFY_PROPERTY
{
	MODIFY_BEAM_SECTION,    //修改截面
	MODIFY_BEAM_REBAR_RATIO, //修改配筋率
	MODIFY_BEAM_MATERIAL,   //修改材料
	MODIFY_BEAM_LOAD,       //修改荷载
	MODIFY_BEAM_ANGLE,       //修改梁的角度
	MODIFY_BEAM_OFFSET,      //修改梁的偏心
	MODIFY_BEAM_DEFCET,     //修改梁初始几何缺陷
	MODIFY_BEAM_STIRRUP_AREA,     //修改梁箍筋面积
	MODIFY_BEAM_TYPE,     //转其它构件
	MODIFY_BEAM_SHEAR,     //修改梁剪切属性 周璋鑫 2023年1月10日
	MODIFY_BEAM_REBAR_SCALE, //修改配筋缩放

	MODIFY_BRACE_SECTION,    //修改截面
	MODIFY_BRACE_REBAR_RATIO, //修改配筋率
	MODIFY_BRACE_MATERIAL,   //修改材料
	MODIFY_BRACE_LOAD,       //修改荷载
	MODIFY_BRACE_ANGLE,       //修改角度
	MODIFY_BRACE_OFFSET,      //修改撑的偏心
	MODIFY_BRACE_DEFCET,     //修改初始几何缺陷
	MODIFY_BRACE_STIRRUP_AREA,     //修改箍筋面积
	MODIFY_BRACE_TYPE,     //转其它构件
	MODIFY_BRACE_SHEAR,     //修改剪切属性 周璋鑫 2023年1月10日
	MODIFY_BRACE_REBAR_SCALE, //修改配筋缩放

	MODIFY_PILLAR_SECTION,    //修改截面
	MODIFY_PILLAR_REBAR_RATIO, //修改配筋率
	MODIFY_PILLAR_MATERIAL,   //修改材料
	MODIFY_PILLAR_LOAD,       //修改荷载
	MODIFY_PILLAR_ANGLE,       //修改角度
	MODIFY_PILLAR_OFFSET,      //修改柱的偏心
	MODIFY_PILLAR_DEFCET,     //修改梁初始几何缺陷
	MODIFY_PILLAR_STIRRUP_AREA,     //修改箍筋面积
	MODIFY_PILLAR_TYPE,     //转其它构件
	MODIFY_PILLAR_APPENDMATERIAL, // 附加材料 目前韩林海截面用2021-12-16
	MODIFY_PILLAR_SHEAR,     //修改剪切属性 周璋鑫 2023年1月10日
	MODIFY_PILLAR_REBAR_SCALE, //修改配筋缩放

	MODIFY_LINK_ANGLE,       //修改角度
	MODIFY_LINK_TYPE,     //转其它构件
	MODIFY_LINK_EQVSTIFF, //等效刚度及等效阻尼

	MODIFY_PLATE_THICKNESS,  //修改厚度
	MODIFY_PLATE_SECTION,
	MODIFY_PLATE_REBAR_RATIO, //修改配筋率
	MODIFY_PLATE_MATERIAL,   //修改材料
	MODIFY_PLATE_LOAD,       //修改荷载
	MODIFY_PLATE_LAYER,       //修改分层
	MODIFY_PLATE_OFFSET,      //修改板的偏心
	MODIFY_PLATE_REBAR_SCALE, //修改配筋缩放

	MODIFY_WALL_THICKNESS,  //修改厚度
	MODIFY_WALL_SECTION,
	MODIFY_WALL_REBAR_RATIO, //修改配筋率
	MODIFY_WALL_STEEL_THICK, //修改墙钢板
	MODIFY_WALL_MATERIAL,   //修改材料
	MODIFY_WALL_LOAD,       //修改墙上线荷载
	MODIFY_WALL_LAYER,       //修改分层
	MODIFY_WALL_OFFSET,      //修改墙的偏心
	MODIFY_WALL_REBAR_SCALE, //修改配筋缩放

	MODIFY_LONGI_SECTION,    //修改连梁纵筋截面
	MODIFY_LONGI_MATERIAL,   //修改连梁纵筋材料
	MODIFY_LONGI_LOAD,       //修改连梁纵筋或虚梁荷载
	MODIFY_LONGI_OFFSET,      //修改连梁纵筋的偏心

	MODIFY_EDGE_SECTION,    //修改边缘构件截面
	MODIFY_EDGE_MATERIAL,   //修改边缘构件材料
	MODIFY_EDGE_REBAR_RATIO, //修改边缘构件配筋率 邱海 2016年2月18日
	MODIFY_EDGE_REBAR_SCALE, //修改边缘构件配筋

	MODIFY_POINT_LOAD,       //修改集中点荷载，包括构件和网格
	MODIFY_POINT_BC,         //修改网格点的边界条件

	MODIFY_MESH_RATIO,		 //修改网格加密系数
	MODIFY_MEMBER_CONSTITUTIVE, //修改构件本构关系类型
	MODIFY_MEMBER_SEISMICGRADE, //修改构件本构抗震等级
	
	MODIFY_MEMBER_SIGINIFICANT, //修改构件重要性分类等级

	MODIFY_MEMBER_VIPTYPE, //修改构件本构抗震等级
	MODIFY_MEMBER_TOWER, //修改构件本构抗震等级

	MODIFY_MEMBER_TEMPER,       //修改构件温度
	MODIFY_BEAM_INITIALSTRAIN,       //修改线构件初应变
	MODIFY_PLATE_INITIALSTRAIN,      //修改面构件初应变

	MODIFY_POINT_THLOAD,  //修改点动载
	MODIFY_AREA_THLOAD,  //修改面动载
	MODIFY_POINT_CROSS_STORY,
	MODIFY_MEMBER_FORCEADJUST,       //修改构件内力调整系数
	MODIFY_MEMBER_PROPADJUST,       //修改构件截面特性调整系数

	MODIFY_BEAM_SECTION_REINFORCED,    //梁加固属性修改：截面修改 辛业文2023年6月12日  
	MODIFY_PILLAR_SECTION_REINFORCED,    //柱加固属性修改：截面修改 辛业文2023年6月12日  

	MODIFY_PLATE_SECTION_REINFORCED,    //板加固属性修改：截面修改 辛业文2023年11月17日  
	MODIFY_WALL_SECTION_REINFORCED,    //墙加固属性修改：截面修改 辛业文2023年11月17日  

	MODIFY_BEAM_REINFORCEMENT,
	MODIFY_PILLAR_REINFORCEMENT,

	MODIFY_BEAM_STIFFNESSCOE, //修改梁构件刚度系数
	MODIFY_PLATE_STIFFNESSCOE, //修改板构件刚度系数

	MODIFY_BEAM_INITIALFORCE,       //修改线构件初拉力
	MODIFY_PLATE_INITIALFORCE,      //修改面构件初拉力
};

//模型数据来源
enum MODEL_SOURCE
{
	MODEL_PKPM=1, //PKPM导入
	MODEL_PRE=2, //预处理导入
	MODEL_SSG=3,  //sausage软件创建
	MODEL_ETABS=4,  //ETABS导入
	MODEL_DXF=5,  //DXF导入

	MODEL_SATWE		=6,
	MODEL_PMSAP		=7,
	MODEL_MIDAS		=8,

	MODEL_PKPM1=10, //旧版PKPM导入，1个模型，已废弃
	MODEL_PKPM2=11, //旧版PKPM导入，2个模型，已废弃
	MODEL_MP=12,     //新简化数据格式项目群
	MODEL_ABAQUS=14, //inp文件导入
	MODEL_SAP2K=15, //SAP2000文件导入
	MODEL_YJK=16, //YJK文件导入


};

//用户输入坐标的方式
enum COOR_TYPE
{
	COORTYPE_X_Y,
	COORTYPE_DX_DY,
	COORTYPE_X,
	COORTYPE_Y,
	COORTYPE_Z,
	COORTYPE_DX,
	COORTYPE_DY,
	COORTYPE_DZ,
	COORTYPE_ANGLE_R,
	COORTYPE_DANGLE,
	COORTYPE_DR,
	COORTYPE_NONE,
};

//结构体系定义
enum STRUCT_SYSTEM
{
	SS_FRAME            =0,    //框架
	SS_FRAME_WALL       =1,    //框架剪力墙
	SS_ALL_WALL         =2,    //全部落地剪力墙
	SS_PART_WALL        =3,    //部分框支剪力墙
	SS_FRAME_TUBE       =4,    //框架-核心筒
	SS_TUBE_TUBE        =5,    //筒中筒
	SS_PLATE_PILLAR_WALL=6,    //板柱-剪力墙
}; 

enum MESHING_METHOD
{
	MESHING_TRI_INSERTPOINT,  //使用边界点插入法生成三角网
	MESHING_TRI_BLOCK,  //使用大三角形分区算法生成三角网
	MESHING_QUAD_TRI,  //板和墙使用铺路法剖分四边形和三角形混合单元
	//MESHING_PLATEQUADTRI_WALLQUAD,  //墙全部剖分成四边形，板使用四边形和和三角形混合单元
};

//虚点类型
enum VIRTUAL_POINT_TYPE
{
	VIRTUAL_POINT_NONE,  //不存在
	VIRTUAL_POINT_MIDDLE,  //线段中点
	VIRTUAL_POINT_PERPENDICULAR, //垂足
	VIRTUAL_POINT_CROSS,  //与线段交点
	VIRTUAL_POINT_1THIRD,  //1/3点
};

//标记点形状，可以组合使用
enum MARKER_TYPE
{
	MARKER_CIRC  		=0x01, //圆形
	MARKER_BOX  		=0x02, //正方形
	MARKER_CROSS 		=0x04, //十字交叉
	MARKER_DELTA 		=0x08, //三角形
	MARKER_DOWNDELTA 	=0x10,//倒三角形
	MARKER_DIAGCROSS	=0x20,//45度交叉
	MARKER_PEDAL		=0x40,//直角标记
};

//复制粘贴类型
enum PASTE_TYPE
{
	PASTE_MOVING = 0,    //相对坐标移动
	PASTE_ROTATE = 1,  //旋转
	PASTE_NORMAL = 2,  //法向复制
	PASTE_MIRRORX = 3, //对称轴垂直于X轴
	PASTE_MIRRORY = 4, //对称轴垂直于Y轴
	PASTE_MIRROR = 6, //对任意轴镜像
	PASTE_STORY = 5,   //层间复制
};

enum FEA_CONTROL
{
	CTRL_REBAR_STIFF=0x02,	//刚度计入钢筋作用
	CTRL_SILENCE=0x100,		//静默执行
};


enum ANALYSIS_TYPE
{
	SOLVER_EXP		=0, //显式积分 修正的中心差分
	SOLVER_NEWMARK	=1, //NewMark
	SOLVER_MODAL	=2, //振型叠加法
	SOLVER_WANGDU	=3, //wang-du法
	SOLVER_SP		=4, //SP方法
	SOLVER_FNA		=5, //FNA方法
	SOLVER_CQC		=6, //反应谱法
	SOLVER_MNL		=7, //静力修正的N-L法
};

enum CRT_SKELETON_TYPE
{		
	CODE_POLYLINE 		=0,   	//规范多段线，用户自定义多段线			
	CODE_CURVE			=1,   	//规范全曲线			
	RUSCH				=2,	 	//Rusch						
	HONGNESTAD			=3,   	//Hongnestad				
	MANDER				=4,   	//Mander模型				
	QIAN				=5,   	//钱稼茹				
	KENTPARK			=6,   	//Kent-Park					
	HAN					=7,   	//韩林海箍筋约束混凝土模型		
	HAN_TUBE			=8,   	//韩林海圆、方钢管模型		
};
enum STEEL_SKELETON_TYPE
{		
	TWO_LINE 			=0,   	//二折线			
	THREE_LINE			=1,   	//三折线			
	ESMAEILY_XIAO		=2,   	//Esmaeily-Xiao				
	COM_BUCKLING		=3,   	//考虑受压屈曲的钢材本构				
};

enum DEVICE_TYPE
{
	DEVICE_CUDA		=0x2000, 
	DEVICE_CUDAS    =0x4000,
	DEVICE_OMP		=0x8000, 
	DEVICE_MASK		=DEVICE_CUDA| DEVICE_CUDAS|DEVICE_OMP,
};

enum RUN_CASE
{
	RUN_IMPSTATIC		=0x04,							//隐式竖向荷载加载
	RUN_MAXFREQ			=0x08,							//最大频率分析
	RUN_MODAL			=0x10,							//模态分析
	RUN_IMP				=RUN_IMPSTATIC|RUN_MAXFREQ|RUN_MODAL,			//一键隐式分析
	RUN_IMPMODAL = RUN_IMPSTATIC | RUN_MODAL,
	RUN_IMPMAXF = RUN_IMPSTATIC | RUN_MAXFREQ,	
	RUN_MODALFREQ = RUN_MAXFREQ | RUN_MODAL,
	RUN_BUCKLING		=0x40,							//线性屈曲分析

	RUN_EXPDYNA			=0x200,					//显式动力时程分析
	RUN_NONSTATIC		=0x400|RUN_EXPDYNA,		//非线性静力分析
	RUN_EXPDYNA_DESIGN	=0x800|RUN_EXPDYNA,		//设计工况分析
	RUN_TIMEHISTORY = 0x1000|RUN_EXPDYNA,    //多点激励时程分析	
	RUN_PUSHOVER = 0x2000|RUN_EXPDYNA,    //静力推覆分析	

	RUN_MODAL_DAMAGE		=0x20000,					//实时模态分析

	RUN_CMODE			=0x40000,							//复模态分析   林思齐 20210527
};

enum BUILD_TYPE
{
	BUILD_UNKNOWN =-1,						//布置命令未开启
	BUILD_BEAM			=0,						//布置梁
	BUILD_PILLAR		=1,						//布置柱
	BUILD_BRACING	=2,						//布置撑
	BUILD_SLAB           =3,                      //布置板
	BUILD_WALL          =4,                      //布置墙
	BUILD_HOLE			=5,                      //布置洞口
	BUILD_LINK			=6,                      //布置一般连接
	BUILD_LINE			=7,                      //布置线
	BUILD_SEMIRIGID     = 8,                      //布置半刚性连接 // 辛业文 半刚性连接增加自定义位移型 2022年12月13
	BUILD_CROSSREBAR=9,
};

//静力工况类型
enum STCASE_TYPE
{
	CASE_DEFAULT	=-1,       //默认工况：未施加到工况
	STCASE_DL			=0,		//恒					
	STCASE_LL			=1,		//活	
	STCASE_WL			=2,		//风
	STCASE_EL			=3,       //地震
	STCASE_TMP			=4,		//温度
	STCASE_PRESTS	=5,		//预应力
	STCASE_USER		=6,		//自定义
};

enum DYCASE_TYPE
{
	//	CASE_DEFAULT	=-1,       //默认工况：未施加到工况
	DYCASE_USER		=0,		//自定义：力 加速度 位移 速度
	DYCASE_FORCE	=1,		//力				
	DYCASE_ACC		=2,		//加速度	
	DYCASE_DISP 	=3,		//位移
	DYCASE_VELO 	=4,		//速度
	DYCASE_BLAST	=5,		//爆炸荷载
};

struct CaseTypeName
{ 
	const wchar_t *sName;
	int iType;
};
const struct CaseTypeName STCaseTypeNameArray[]=
{
	//_CHSL(L"恒荷载",L"Dead"),		STCASE_DL,
	//_CHSL(L"活荷载",L"Live"),		STCASE_LL,
	//_CHSL(L"风荷载",L"Wind"),		STCASE_WL,
	//_CHSL(L"地震作用",L"Earthquake"),	STCASE_EL,
	//_CHSL(L"用户自定义",L"User"),	STCASE_USER,
	//_CHSL(L"温度",L"Temper"),	STCASE_TMP,
	//_CHSL(L"预应力",L"Prestress"),	CASE_PRESTS
#ifdef _SIMPLIFIED_CHINESE
//	L"默认工况",		CASE_DEFAULT,
	L"恒荷载",		STCASE_DL,
	L"活荷载",		STCASE_LL,
	L"风荷载",		STCASE_WL,
	L"地震作用",	STCASE_EL,
	L"温度",	STCASE_TMP,
	L"预应力",	STCASE_PRESTS,
	L"自定义",	STCASE_USER
#else
//	L"Default",	CASE_DEFAULT,
	L"Dead",		STCASE_DL,
	L"Live",		STCASE_LL,
	L"Wind",		STCASE_WL,
	L"Earthquake",	STCASE_EL,
	L"Temper",	STCASE_TMP,
	L"Prestress",	STCASE_PRESTS,
	L"User",	STCASE_USER
#endif
};

const struct CaseTypeName DYCaseTypeNameArray[]=
{
#ifdef _SIMPLIFIED_CHINESE
	//	L"默认工况",		CASE_DEFAULT,
	L"自定义",	DYCASE_USER,
	L"力",			DYCASE_FORCE,
	L"加速度",	DYCASE_ACC,
	L"位移",		DYCASE_DISP,
	//L"速度",		DYCASE_VELO

#else
	//	L"Default",	CASE_DEFAULT,
	L"All",			DYCASE_USER,
	L"Force",		DYCASE_FORCE,
	L"Accel",		DYCASE_ACC,
	L"Disp",		DYCASE_DISP,
	//L"Velo'",		DYCASE_VELO
#endif
};

const float Sys_CoeffDeadMass=1.0f;

//静力工况组合类型
enum COMB_TYPE
{
	COMB_ADD			=0,	//线性和				
	COMB_ENVELOPE=1,	//包络
	COMB_ABSADD	=2,   //绝对值和
	COMB_SRSS 			=3,	//SRSS
	COMB_RangeADD  =4,   //RangeAdd
};


//构件性能水平
enum PERFORM_TYPE
{
	PERFORM_0			=0,					
	PERFORM_1			=1,					
	PERFORM_2			=2,		
	PERFORM_3			=3,		
	PERFORM_4			=4,     
	PERFORM_5			=5,		
	PERFORM_6			=6,		
};

const struct CaseTypeName PerformTypeNameArray[]=
{
#ifdef _SIMPLIFIED_CHINESE
	L"未设置",		PERFORM_0,
	L"无损坏",		PERFORM_1,
	L"轻微损坏",	PERFORM_2,
	L"轻度损坏",	PERFORM_3,
	L"中度损坏",	PERFORM_4,
	L"重度损坏",	PERFORM_5,
	L"严重损坏",	PERFORM_6,
#else
	L"Not define",	PERFORM_0,
	L"None",		PERFORM_1,
	L"Slight",		PERFORM_2,
	L"Light",		PERFORM_3,
	L"Moderate",	PERFORM_4,
	L"Heavy",		PERFORM_5,
	L"Severe",		PERFORM_6,
#endif
};

const struct CaseTypeName MatConstitutiveArray[] =
{
#ifdef _SIMPLIFIED_CHINESE
	L"弹塑性", 0,
	L"弹性",1,
	
#else
	L"Plastic",	0,
	L"Elastic",	1,	
	
#endif
};

const struct CaseTypeName PerformObjectArray[] =
{
#ifdef _SIMPLIFIED_CHINESE
	L"不考虑", 0,
	L"弹性",1,
	L"不屈服",2,
	L"极限承载力",3,

#else
	L"Not Consider",	0,
	L"Elastic",	1,
	L"Not Yield",	2,
	L"Ultimate Capacity",	3,

#endif
};

//构件性能评价标准
enum PERFORM_STANDARD_TYPE
{
	PERFORM_DEFAULT		= 0x00000000, //原RBS评价标准
	PERFORM_STRAIN		= 0x00000001,
	PERFORM_DRIFT		= 0x00000002,
	PERFORM_2023		= 0x00000003, //原默认评价标准（2023版本及之前）

	PERFORM_STEEL		= 0x00000004,
	PERFORM_STEEL_DRIFT = 0x00000005,
	PERFORM_STRESS,
	PERFORM_RBS,

	PERFORM_COLLAPSE	= 0x00000101,
	PERFORM_RES			= 0x00000201,
	PERFORM_PBSD		= 0x00000301,
};
//钢构件性能评价标准
//enum PERFORM_STEEL_STANDARD_TYPE
//{
//	PERFORM_STEEL = 0,
//	PERFORM_STEEL_DRIFT = 1,
//};

// Use for m_aRunISO
enum ISORUN_FLAG
{
	RUNISO = 1,
	RUNNOISO = 2,
	RUNALL = RUNISO | RUNNOISO
};


enum OUTPUT_CLOSE_FLAG
{
	ALL_OUTPUT = 0,
	CLOSE_STRU_FORCE = 0x01,//FILE_STRU_FORCE_BIN
};

const float Sys_SemiRigidElmLength = 0.1f;

// 新增加固构件 辛业文 2023年4月14日
enum REINFORCEDCOMPONENTS
{
	REINFORCED_DELETE = -1,
	REINFORCED_BEAM = 0,
	REINFORCED_PILLAR = 1,
};

//工况包络类型
enum ENVE_TYPE
{		
	ENVE_ENV = 0,	//包络
	ENVE_AVE = 1,	//SRSS
};

enum FILE_FLAG
{
	FLAG_DAMAGE_BIN = 0x1,	//FILE_DAMAGE_BIN,
	FLAG_REBAR_PLASTIC_STRAIN_BIN = 0x2,	//FILE_REBAR_PLASTIC_STRAIN_BIN,
	FLAG_STEEL_PLASTIC_STRAIN_BIN = 0x4,	//FILE_STEEL_PLASTIC_STRAIN_BIN,
	FLAG_REBAR_STRESS_BIN = 0x8,	//FILE_REBAR_STRESS_BIN,
	FLAG_STEEL_STRESS_BIN = 0x10,	//FILE_STEEL_STRESS_BIN,
	FLAG_ELEM_PERFORM_BIN = 0x20,	//FILE_ELEM_PERFORM_BIN,
	FLAG_STRU_PERFORM_BIN = 0x40,	//FILE_STRU_PERFORM_BIN,
	FLAG_LINK_BIN = 0x80,	//FILE_LINK_BIN,
	FLAG_STRESS_BIN = 0x100, //FILE_STRESS_BIN,
	FLAG_FORCE_BIN = 0x200, //FILE_FORCE_BIN,
	FLAG_STRAIN_BIN = 0x400,//FILE_STRAIN_BIN,
	FLAG_STRU_FORCE_BIN = 0x800,//FILE_STRU_FORCE_BIN,
	FLAG_STRU_AS_BIN = 0x1000, //FILE_STRU_AS_BIN
	FLAG_STRU_STIFF_BIN = 0x2000,//FILE_STRU_STIFF_BIN,
	FLAG_STRU_STRESSRATIO_BIN = 0x4000, //FILE_STRU_STRESSRATIO_BIN,
	FLAG_SHEAR_COMPRESSION_RATIO_ELM_BIN = 0x10000,// FILE_SHEAR_COMPRESSION_RATIO_ELM_BIN,
	FLAG_SHEAR_SPAN_RATIO_ELM_BIN = 0x20000,//FILE_SHEAR_SPAN_RATIO_ELM_BIN,
	FLAG_NOMINAL_TENSILE_STRESS_ELM_BIN = 0x40000, //FILE_NOMINAL_TENSILE_STRESS_ELM_BIN
	FLAG_NOMINAL_TENSILE_STRESS_RATIO_ELM_BIN = 0x80000, //FILE_NOMINAL_TENSILE_STRESS_RATIO_ELM_BIN
	FLAG_AXIAL_COMP_COEF_ELM_BIN = 0x100000,// FILE_AXIAL_COMP_COEF_ELM_BIN
	FLAG_AXIAL_COMP_RATIO_ELM_BIN = 0x200000,// FILE_AXIAL_COMP_RATIO_ELM_BIN
	FLAG_SHEAR_STRESS_EELM_BIN = 0x400000,// FILE_SHEAR_STRESS_EELM_BIN
	FLAG_SHEAR_STRESS_KELM_BIN = 0x800000,// FILE_SHEAR_STRESS_KELM_BIN,
	FLAG_SHEAR_STRESS_LELM_BIN = 0x1000000,// FILE_SHEAR_STRESS_LELM_BIN
	FLAG_DISP_ANGLE_ELM_BIN = 0x2000000,// FILE_DISP_ANGLE_ELM_BIN
	FLAG_DISP_ANGLE_BIN = 0x4000000,// FILE_DISP_ANGLE_BIN
	FLAG_DUCTILITY_RATIO_BLAST_BIN = 0x8000000,// FILE_DUCTILITY_RATIO_BLAST_BIN

	FLAG_DISP_ANGLE_XUE_ELM_BIN = 0x10000000,
	FLAG_DISP_ANGLE_XUE_BIN = 0x20000000, //FILE_DISP_ANGLE_XUE_BIN,

	FLAG_GROUP_BIN = FLAG_STRESS_BIN | FLAG_FORCE_BIN | FLAG_STRAIN_BIN,
	FLAG_STRU_BIN = FLAG_STRU_AS_BIN | FLAG_STRU_STIFF_BIN | FLAG_STRU_STRESSRATIO_BIN | FLAG_DISP_ANGLE_BIN | FLAG_DISP_ANGLE_XUE_BIN | FLAG_DUCTILITY_RATIO_BLAST_BIN,
	FLAG_BIN_DEFAULT = FLAG_GROUP_BIN | FLAG_DAMAGE_BIN | FLAG_REBAR_PLASTIC_STRAIN_BIN | FLAG_STEEL_PLASTIC_STRAIN_BIN | FLAG_REBAR_STRESS_BIN | FLAG_STEEL_STRESS_BIN
	| FLAG_ELEM_PERFORM_BIN | FLAG_STRU_PERFORM_BIN | FLAG_LINK_BIN | FLAG_STRU_FORCE_BIN | FLAG_STRU_AS_BIN | FLAG_STRU_STIFF_BIN | FLAG_STRU_STRESSRATIO_BIN
	| FLAG_DISP_ANGLE_XUE_BIN | FLAG_DISP_ANGLE_XUE_ELM_BIN,
};

struct OutputFile
{
	const wchar_t* sName;
	int iFlag;
};
const OutputFile OUTPUT_FILES[] =
{
	FILE_DAMAGE_BIN				 ,FLAG_DAMAGE_BIN,
	FILE_REBAR_PLASTIC_STRAIN_BIN,FLAG_REBAR_PLASTIC_STRAIN_BIN,
	FILE_STEEL_PLASTIC_STRAIN_BIN,FLAG_STEEL_PLASTIC_STRAIN_BIN,
	FILE_REBAR_STRESS_BIN,		  FLAG_REBAR_STRESS_BIN,
	FILE_STEEL_STRESS_BIN,		  FLAG_STEEL_STRESS_BIN,
	FILE_ELEM_PERFORM_BIN,		  FLAG_ELEM_PERFORM_BIN,
	FILE_STRU_PERFORM_BIN,		  FLAG_STRU_PERFORM_BIN,
	FILE_LINK_BIN,				  FLAG_LINK_BIN,
	FILE_STRESS_BIN,			  FLAG_STRESS_BIN,
	FILE_FORCE_BIN,				  FLAG_FORCE_BIN,
	FILE_STRAIN_BIN,			  FLAG_STRAIN_BIN,
	FILE_STRU_FORCE_BIN,		  FLAG_STRU_FORCE_BIN,
	FILE_STRU_AS_BIN,			  FLAG_STRU_AS_BIN,
	FILE_STRU_STIFF_BIN,	      FLAG_STRU_STIFF_BIN,
	FILE_STRU_STRESSRATIO_BIN,	  FLAG_STRU_STRESSRATIO_BIN,
	//FILE_DISP_ANGLE_XUE_BIN,	  FLAG_DISP_ANGLE_XUE_BIN,
	FILE_SHEAR_COMPRESSION_RATIO_ELM_BIN,		FLAG_SHEAR_COMPRESSION_RATIO_ELM_BIN,
    FILE_SHEAR_SPAN_RATIO_ELM_BIN,				FLAG_SHEAR_SPAN_RATIO_ELM_BIN,
    FILE_NOMINAL_TENSILE_STRESS_ELM_BIN,		FLAG_NOMINAL_TENSILE_STRESS_ELM_BIN,
    FILE_NOMINAL_TENSILE_STRESS_RATIO_ELM_BIN,	FLAG_NOMINAL_TENSILE_STRESS_RATIO_ELM_BIN,
    FILE_AXIAL_COMP_COEF_ELM_BIN,				FLAG_AXIAL_COMP_COEF_ELM_BIN,
    FILE_AXIAL_COMP_RATIO_ELM_BIN,				FLAG_AXIAL_COMP_RATIO_ELM_BIN,
    FILE_SHEAR_STRESS_EELM_BIN,					FLAG_SHEAR_STRESS_EELM_BIN,
	FILE_SHEAR_STRESS_KELM_BIN,					FLAG_SHEAR_STRESS_KELM_BIN,
    FILE_SHEAR_STRESS_LELM_BIN,					FLAG_SHEAR_STRESS_LELM_BIN,
    FILE_DISP_ANGLE_ELM_BIN,					FLAG_DISP_ANGLE_ELM_BIN,
    FILE_DISP_ANGLE_BIN,						FLAG_DISP_ANGLE_BIN,
	FILE_DISP_ANGLE_XUE_ELM_BIN,				FLAG_DISP_ANGLE_XUE_ELM_BIN,
	FILE_DISP_ANGLE_XUE_BIN,					FLAG_DISP_ANGLE_XUE_BIN,
	FILE_DUCTILITY_RATIO_BLAST_BIN,				FLAG_DUCTILITY_RATIO_BLAST_BIN,
};

const int CASEENV = 9999;
const wchar_t SCASEENV[] = L"-----------包络工况-----------";
const int ENVSTART = 10000;
const wchar_t sEnvPath[] = L"\\EnvelopeCase\\";

enum LOADCASETYPE
{
	STATIC = -1,
	EARTHQUAKE = 0,//大震验算，SSG默认，SSG可以打开 m_cLoad
	DIRECTANALY = 1,//设计工况 钢结构、减震、隔震 m_cLoadDesign
	NLSTATIC = 2,//静力非线性 m_cLoadStatic
	EQELASTIC = 3,//等效弹性设计 减震、隔震  m_cLoadElastic
	TIMEHISTORY = 4,//通用动力时程分析 m_cLoad
	PUSHOVER = 5,	//静力推覆结果 m_cLoadStatic
	MULTIPTEXCITE = 6,
	SPECTRUM = 7, // 反应谱工况  林思齐 20210722
	LINEARBUCKLING = 8, //线性屈曲分析 贾苏 2022.12.15
};

//加固软件非加固模型曲线前加字符串
const wchar_t Sys_sJGAdd[] = L"原-";



//隔墙组类型定义
enum PARTITIONWALL_GROUP_STYLE
{
	STYLE_SINGLE_DIAGONAL_BRACING = 0,//单斜撑
	STYLE_DOUBLE_DIAGONAL_BRACING,	//双斜撑
};


// 隔墙组 辛业文 2024年1月17日
struct PartitionWallGroupStyle
{
	const wchar_t* sName;
	enum PARTITIONWALL_GROUP_STYLE iType;
};

//隔墙模拟样式列表
const struct PartitionWallGroupStyle sPartitionWall_Group_Style[] = {
#ifdef _SIMPLIFIED_CHINESE
	L"等效单斜撑(只受压)",			STYLE_SINGLE_DIAGONAL_BRACING,
	L"等效双斜撑",             		STYLE_DOUBLE_DIAGONAL_BRACING,
#else
	L"Single diagonal braceing",    STYLE_SINGLE_DIAGONAL_BRACING,
	L"Double diagonal braceing",	STYLE_DOUBLE_DIAGONAL_BRACING,
#endif
};

//多模型方案组曲线前加字符串
const wchar_t Sys_sDamperSchemeAdd[] = L"方案组-";

// 层间剪力和基底剪力
enum SHEARECURVETYPE
{
	SHEARFORCECURVE = 0, // 自定义层间剪力
	BASESHEARTIMECURVE = 1, // 自定义基底剪力
};


// 绘制预应力筋 辛业文 2023年3月3日
// 应力筋组类型定义
enum PRESTRESSINGTENDONGROUP_STYLE
{
	STYLE_STAINGHT_LINE = 0,	//直线
	STYLE_SINGLE_FOLD_LINE,		//单折线
	STYLE_DOUBLE_FOLD_LINE,	    //双折线
	STYLE_PARABOLA,				//一段式抛物线
	STYLE_TWO_STAGE_PARABOLA,	//两段式抛物线
	STYLE_THREE_STAGE_PARABOLA_LEFT,	// 三段式抛物线（左边跨）
	STYLE_THREE_STAGE_PARABOLA_RIGHT,	// 三段式抛物线（右边跨）
	STYLE_FOUR_STAGE_PARABOLA,			// 四段式抛物线型
};
// 应力筋样式列表 辛业文 2023年3月3日
struct PrestressingTendonLinkGroupStyle
{
	const wchar_t* sName;
	PRESTRESSINGTENDONGROUP_STYLE iType;
};

// 应力筋样式列表 辛业文 2023年3月3日
const struct PrestressingTendonLinkGroupStyle sPrestressingTendoGroup_Style[] = {
#ifdef _SIMPLIFIED_CHINESE
	L"直线",				STYLE_STAINGHT_LINE,
	L"单折线 ", 			STYLE_SINGLE_FOLD_LINE,
	L"双折线 ", 			STYLE_DOUBLE_FOLD_LINE,
	L"一段式 ", 			STYLE_PARABOLA,
	L"两段式 ", 			STYLE_TWO_STAGE_PARABOLA,
	L"左边跨 ", 			STYLE_THREE_STAGE_PARABOLA_LEFT,
	L"右边跨 ",				STYLE_THREE_STAGE_PARABOLA_RIGHT,
	L"四段式 ",				STYLE_FOUR_STAGE_PARABOLA,
#else
	L"Strainght Line",                   STYLE_STAINGHT_LINE,
	L"Single Fold Line",				 STYLE_SINGLE_FOLD_LINE,
	L"Double Fold Line",				 STYLE_DOUBLE_FOLD_LINE,
	L"A Parabola",						 STYLE_PARABOLA,
	L"Two Stage Parabloa",				 STYLE_TWO_STAGE_PARABOLA,
	L"Three Stage Parabola Left Span",	 STYLE_THREE_STAGE_PARABOLA_LEFT,
	L"Three Stage Parabola Right Span",	 STYLE_THREE_STAGE_PARABOLA_RIGHT,
	L"Four Stage Parabola",		         STYLE_FOUR_STAGE_PARABOLA,
#endif
};

enum POST_ITEM
{
	POST_UNKNOWN = 0,		//未知

	//整体指标，层
	POST_STORY_DRIFT = 0x1,			//层间位移
	POST_STORY_SHEAR = 0x2,			//层间剪力
	POST_SUPPORT_FORCE = 0x4,		//支座反力
	POST_ALL_ENERGY = 0x8,			//全楼能量

	//节点
	POST_NODE_DISP = 0x10,			//节点位移
	POST_NODE_VEL = 0x20,			//节点速度
	POST_NODE_ACC = 0x40,			//节点加速度

	//单元
	//默认全输出
	POST_DAMAGE = 0x100,			//混凝土损伤
	POST_PLASTIC_REBAR = 0x200,		//钢筋塑性应变
	POST_PLASTIC_STEEL = 0x400,		//钢材塑性应变
	POST_STRESS_REBAR = 0x800,		//钢筋应力
	POST_STRESS_STEEL = 0x1000,		//钢材应力
	POST_LINK = 0x2000,				//一般连接
	POST_ELE_ENERGY = 0x4000,		//单元能量
	POST_ELE_STIFF = 0x8000,		//单元刚度

	//选择集输出
	POST_STRAIN = 0x10000,			//截面变形
	POST_STRESS = 0x20000,			//纤维应力应变
	POST_ELE_FORCE = 0x40000,		//单元内力

	//构件
	POST_STRU_FORCE = 0x100000,		//构件内力

	//默认输出
	POST_DEFAULT = POST_STORY_DRIFT| POST_STORY_SHEAR| POST_ALL_ENERGY|POST_NODE_DISP| POST_DAMAGE|
	POST_PLASTIC_REBAR| POST_PLASTIC_STEEL| POST_LINK| POST_STRU_FORCE,
};