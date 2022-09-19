#pragma once

/*
ϵͳ����궨�壺
	_SIMPLIFIED_CHINESE: ��������Ϊ���İ棬�ı�����Ӧ�������ģ�����ΪӢ��
	_PKPM: ��������ΪPKPM�ӿ�ר�ð���򣬲�����ǰ����ͼ����ʾ�ͼ��㲿��
	_NOFEM����������Ϊǰ����ר�ð���򣬲��������㲿�ֺ�PKPM�ӿڣ���δ����_PKPM��_NOFEM��Ϊ��׼����򣬰���ǰ����ͼ������
	_SEP_FEM��������ǰ���������Ԫ����EXE���򣬲�֧��CUDA
	_HASP����������Ϊ���ܹ���
*/

const float Sys_FileVersion=2022.0f; //IO�ļ��汾�ţ���������>0.001��ʹ�ø�����ʱӦע��float�ľ������⣬Ӧ�������������������0.05f��

//ϵͳ�ļ�
const wchar_t FILE_DEFAULT_MATERIAL_LIB[]=L"DATA\\MATERIAL.MLB";  //ϵͳȱʡ���Ͽ⣬�ı��ļ�
const wchar_t FILE_DEFAULT_SECTION_LIB[]=L"DATA\\SECTION.MLB";  //ϵͳȱʡ����⣬�ı��ļ�
const wchar_t FILE_DEFAULT_DAMPER_SECTION_LIB[]=L"DATA\\DAMPER_SECTION.MLB";  //ϵͳȱʡ����⣬�ı��ļ�
const wchar_t FILE_SYS_INI[]=L"SAUSAGE.INI";  //�û�����ini�ļ����ı��ļ�
const wchar_t FILE_SYS_MAT[]=L"SAUSAGE.MTL";  //�û��Զ�������ļ����ı��ļ�������ͬID���в����滻
const wchar_t FILE_SECGEN[]=L"SECGEN.EXE";  //�Զ����������ı��ļ�
const wchar_t FILE_PREP_PROJ[]=L"PrepSSGPath.txt";  //Ԥ�����ص���Ŀ·�����ı��ļ�


//��Ŀ��Ŀ¼�µ��ļ�
const wchar_t FILE_PRJ_PARA[]=L"PAR";  //��Ŀ������ini��ʽ�ļ��������ļ�
const wchar_t FILE_BATCH_CMD[]=L".MCD";  //�������ļ��������ļ�
const wchar_t FILE_MODIFY_HIST[]=L"MCM";  //�޸�ģ�������õ�ָ����ʷ��¼���ı��ļ��������ļ�
const wchar_t FILE_MESSAGE[]=L"MSG";  //�������е���ʱ��Ϣ���ı��ļ��������ļ�
const wchar_t FILE_MATERIAL[]=L"MLB";  //��Ŀ���Ͽ⣬�ı��ļ��������ļ�����ʱ����
const wchar_t FILE_PRJ_TEMP[]=L"s~~"    ;  //��ʱ���ݵ���Ŀ�ļ��������Ŀ�����Ϣ���ı��ļ�����ʱ����
const wchar_t FILE_OUT_PROFILE[]=L"IDX";  //������ݵ�������Ϣ�ļ����ı��ļ���������������ʱ����

const wchar_t FILE_FRAME[]=L"SSG"  ;  //������ݣ��ı��ļ���������MLB

const wchar_t FILE_CHECK_MODEL[]=L"WRN";  //���ģ�����ݽ������ı��ļ�,������SSG
const wchar_t FILE_COOR_BIN[]=L"BCR";  //������꣬�������ļ���������SSG
const wchar_t FILE_COORL_BIN[]=L"BLR";  //�����أ��������ļ���������SSG
const wchar_t FILE_ELEM_BIN[]=L"BEM";  //��Ԫ���룬�������ļ���������SSG
const wchar_t FILE_COOR[]=L"COR";  //������꣬�ı��ļ�����������ӿڣ�������SSG
const wchar_t FILE_ELEM[]=L"ELM";  //��Ԫ���룬�ı��ļ�����������ӿڣ�������SSG
const wchar_t FILE_COORVL_BIN[]=L"BVL";  //�ڵ�ʱ�����

const wchar_t FILE_SHADOW_COOR_BIN[]=L"SCR";  //�����������������꣬�������ļ�������������
const wchar_t FILE_SHADOW_POLY_BIN[]=L"SPL";  //�����������������Σ��������ļ�������������
const wchar_t FILE_FEA_INTERFACE[]=L"FEA";  //�ӿ������ı��ļ������������ã�����������
const wchar_t FILE_POST_REPORT[]=L"OUT";  //PKPM��ʽ�ĺ����棬���ڶԱȣ��ı��ļ�������������

const wchar_t FILE_WBEAM_COEF[]=L"WBC";  //PKPM��ʽ�ĺ����棬���ڶԱȣ��ı��ļ�������������
const wchar_t FILE_DEFENSE_COEF[]=L"DFX";  //PKPM��ʽ�ĺ����棬���ڶԱȣ��ı��ļ�������������
const wchar_t FILE_PERFORMDESIGN_COEF[]=L"PDC";  //PKPM��ʽ�ĺ����棬���ڶԱȣ��ı��ļ�������������



//����Ϊ�������Գ�ʼ�����ļ�
const wchar_t FILE_WALLREBAR[]=L"D01";  //ǽ�����Ϣ���ı��ļ�,����
const wchar_t FILE_PLATEREBAR[]=L"D02";  //�������Ϣ���ı��ļ�������
const wchar_t FILE_HIDEBEAM[]=L"D03";  //�������ɲ������ı��ļ��������ļ�
const wchar_t FILE_REBARTHICK[]=L"D04";  //�湹�������ֽ���������ϵ���ı��ļ��������ļ�
const wchar_t FILE_VISIBLEINFO[]=L"D05";  //�ɼ��Ĺ�����Ϣ���ı��ļ���������SSG
const wchar_t FILE_COMBINEFRAME[]=L"D06";  //��Ϲ����������ı��ļ���������SSG

//�������ļ�ȫ������������
//StaticResult��Ŀ¼�µ��ļ�
const wchar_t FILE_MAX_FREQ[]=L"MFQ";  //���Ƶ���ļ����ı��ļ�
const wchar_t FILE_STATIC_SUPPORT_FORCE[]=L"NSF";  //��������֧���������ı��ļ�
const wchar_t FILE_BUILDING_WEIGHT[]=L"STW";  //ȫ¥���أ��ı��ļ�
const wchar_t FILE_MODAL_BIN[]=L"MOD";  //�����ļ����������ļ�
const wchar_t FILE_FREQ[]=L"FRQ";  //Ƶ���ļ����ı��ļ�
const wchar_t FILE_BUCKLING[]=L"FRB";  //Ƶ���ļ����ı��ļ�
const wchar_t FILE_STATIC_DISP_BIN[]=L"NSD";  //������ؼ��ص�λ���ļ����������ļ�
const wchar_t FILE_BUCKLING_BIN[]=L"MOB";  //���������ļ����������ļ�
const wchar_t FILE_DEFECT_BIN[]=L"IMP";  //ȱ���ļ����������ļ�
const wchar_t FILE_MAXMODAL_BIN[]=L"MOF";  //�����ļ����������ļ�

//CModalResult��Ŀ¼�µ��ļ�  ��˼�� 20210527
const wchar_t FILE_CMODAL_BIN[]=L"CMOD";        //�����ļ����������ļ�
const wchar_t FILE_CFREQ[]=L"CFRQ";            //Ƶ���ļ����ı��ļ�
const wchar_t FILE_CMODAL_DISP_BIN[]=L"CBDS";  //��Ч�����������½ṹ�ڵ�λ���ļ����������ļ�

//EarthQuakeResult\case_n\��Ŀ¼�µ��ļ�
const wchar_t FILE_DISP_BIN[]=L"BDS";  //�����������λ�ƣ��������ļ�
//const wchar_t FILE_VECT_BIN[]=L"BVE";  //������������ٶȣ��������ļ�
const wchar_t FILE_SPEED_BIN[]=L"BDS";  //������������ٶȣ��������ļ�����λ���ļ�����
//const wchar_t FILE_ACCE_BIN[]=L"BAC";  //�������������ٶȣ��������ļ�
const wchar_t FILE_ACCE_BIN[]=L"BDS";  //�������������ٶȣ��������ļ�����λ���ļ�����
const wchar_t FILE_ENERGY_BIN[]=L"BES";  //������������������������ļ�
const wchar_t FILE_FORCE_BIN[]=L"EFT";  //����������Ԫ������ѡ�񼯣��������ļ�
const wchar_t FILE_STRESS_BIN[]=L"FST"; //����������ԪӦ��Ӧ�䣬ѡ�񼯣��������ļ�
const wchar_t FILE_STRAIN_BIN[]=L"EST"; //����������Ԫ���Σ�ѡ�񼯣��������ļ�
const wchar_t FILE_DAMAGE_BIN[]=L"ECR"; //���������˵�ǿ���ۼ�ϵ����ѡ�񼯣��������ļ�
const wchar_t FILE_REBAR_PLASTIC_STRAIN_BIN[]=L"ERP"; //�ֽ������Ӧ�䣬ѡ�񼯣��������ļ�
const wchar_t FILE_STEEL_PLASTIC_STRAIN_BIN[]=L"ESP"; //�ֲĵ�����Ӧ�䣬ѡ�񼯣��������ļ�
const wchar_t FILE_TOP_STORY_FORCE_BIN[]=L"EMT";		//����������䶥����Ԫ�������̶�ѡ�񼯣��������ļ�
const wchar_t FILE_BOTTOM_STORY_FORCE_BIN[]=L"EMB";		//�����������ײ���Ԫ�������̶�ѡ�񼯣��������ļ�
const wchar_t FILE_STRU_FORCE_BIN[]=L"BSF";				//�������������������̶�ѡ�񼯣��������ļ�
const wchar_t FILE_STRU_AS_BIN[]=L"BSA";				//���������������������̶�ѡ�񼯣��������ļ�
const wchar_t FILE_ELEM_PERFORM_BIN[]=L"BEP";				//����������Ԫ����ˮƽ���̶�ѡ�񼯣��������ļ�
const wchar_t FILE_STRU_PERFORM_BIN[]=L"BSP";				//����������������ˮƽ���̶�ѡ�񼯣��������ļ�
const wchar_t FILE_DAMPER_PERFORM_BIN[] = L"BDP";			//��������һ����������ˮƽ���̶�ѡ�񼯣��������ļ�
const wchar_t FILE_STRU_STIFF_BIN[]=L"BSR";				//�����ն��ۼ�ϵ����������ʱ�̣��̶�ѡ�񼯣��������ļ�
const wchar_t FILE_ELEM_HINGE_BIN[]=L"BEH";				//����������Ԫ���Խ£��̶�ѡ�񼯣��������ļ�
const wchar_t FILE_STORY_DRIFT_BIN[]=L"SDR";			//���λ�ƽǡ����λ�ơ���λ�ƣ����飬�������ļ�
const wchar_t FILE_STORY_ENERGY_BIN[]=L"SENG";			//���λ�ƽǡ����λ�ơ���λ�ƣ����飬�������ļ�
const wchar_t FILE_TOTALENERGY_BIN[]=L"ENG";			//ȫ¥�������������ļ�
const wchar_t FILE_STORY_SHEAR_BIN[]=L"SSH";			//���������������ļ�
//const wchar_t FILE_ELM_BLOCK_INDEX[]=L"EBI";  //ÿ����Ԫ�ķֿ�������������F-5�ļ����ʹ�ã��������ļ�,��ѡ��
//const wchar_t FILE_TEMP_BIN[]=L"TMP";  //������������¶ȣ��������ļ�
const wchar_t FILE_OUTPUT_DEF[]=L"DEF";  //��¥����������ӽ�㣬�ı��ļ������飬��������ӿڣ�����������
const wchar_t FILE_OUTPUT_DED[]=L"DED";  //��¥����������Ӷ�Ӧ�Ĳ��λ�ƽǣ��ı��ļ������飬����������
const wchar_t FILE_STRU_STRESSRATIO_BIN[]=L"BSS";				//���������������������̶�ѡ�񼯣��������ļ�
const wchar_t FILE_LINK_BIN[]=L"LIK";										//һ�����Ӷ�������������������ļ�
const wchar_t FILE_REBAR_STRESS_BIN[]=L"ERS";		//��Ԫ���ֽ�Ӧ�����������ļ�
const wchar_t FILE_STEEL_STRESS_BIN[]=L"ESS";		//��Ԫ���ֲ�Ӧ�����������ļ�
const wchar_t FILE_SHEAR_COMPRESSION_RATIO_BIN[] = L"SCRS"; //��ѹ�ȣ��������ļ�
const wchar_t FILE_SHEAR_COMPRESSION_RATIO_ELM_BIN[] = L"SCRE";//��ѹ�ȵ�Ԫ�洢����������ͼ��Ⱦ���������ļ�
const wchar_t FILE_SHEAR_SPAN_RATIO_BIN[] = L"SSRS";//����ȣ��������ļ�
const wchar_t FILE_SHEAR_SPAN_RATIO_ELM_BIN[] = L"SSRE";//����ȵ�Ԫ���棬��������ͼ��Ⱦ���������ļ�
const wchar_t FILE_NOMINAL_TENSILE_STRESS_BIN[] = L"NTSS"; //������Ӧ�����������ļ�
const wchar_t FILE_NOMINAL_TENSILE_STRESS_ELM_BIN[] = L"NTSE"; //������Ӧ����Ԫ�洢����������ͼ��Ⱦ���������ļ�
const wchar_t FILE_NOMINAL_TENSILE_STRESS_RATIO_ELM_BIN[] = L"NTSR";//������Ӧ���ȵ�Ԫ�洢����������ͼ��Ⱦ���������ļ�
const wchar_t FILE_AXIAL_COMP_COEF_BIN[] = L"ATC";//��ѹ��ϵ�����������ļ�
const wchar_t FILE_AXIAL_COMP_COEF_ELM_BIN[] = L"ATCE";//��ѹ��ϵ����Ԫ���棬��������ͼ��Ⱦ���������ļ�
const wchar_t FILE_AXIAL_COMP_RATIO_BIN[] = L"ATR";//��ѹ��ϵ�����������ļ�
const wchar_t FILE_AXIAL_COMP_RATIO_ELM_BIN[] = L"ATRE";//��ѹ��ϵ����Ԫ���棬��������ͼ��Ⱦ���������ļ�
const wchar_t FILE_SHEAR_STRESS_BIN[] = L"SRS";//�������������������ļ�
const wchar_t FILE_SHEAR_STRESS_EELM_BIN[] = L"SREE";//�������������Դ洢����������ͼ��Ⱦ���������ļ�
const wchar_t FILE_SHEAR_STRESS_KELM_BIN[] = L"SREK";//�����������������洢����������ͼ��Ⱦ���������ļ�
const wchar_t FILE_SHEAR_STRESS_LELM_BIN[] = L"SREL";//�������������޴洢����������ͼ��Ⱦ���������ļ�
const wchar_t FILE_MOMENT_BIN[] = L"SMS";//������������������ļ�
const wchar_t FILE_MOMENT_EELM_BIN[] = L"SME";//�������������Դ洢����������ͼ��Ⱦ���������ļ�
const wchar_t FILE_MOMENT_SHEAR_RATIO_BIN[] = L"MSR";//����ȣ��������ļ�
const wchar_t FILE_MOMENT_SHEAR_RATIO_ELM_BIN[] = L"MSRE";//����ȴ洢����������ͼ��Ⱦ���������ļ�
const wchar_t FILE_DISP_ANGLE_BIN[] = L"DIA";//�㶫ʡλ�ƽǣ��������ļ�
const wchar_t FILE_DISP_ANGLE_ELM_BIN[] = L"DIAE";//�㶫ʡλ�ƽǵ�Ԫ�洢����������ͼ��Ⱦ���������ļ�
const wchar_t FILE_DISP_ANGLE_XUE_BIN[] = L"DIAX";//��������λ�ƽǣ��������ļ�
const wchar_t FILE_DISP_ANGLE_XUE_ELM_BIN[] = L"DIAXE";//��������λ�ƽǵ�Ԫ�洢����������ͼ��Ⱦ���������ļ�

const wchar_t Sys_Group_All[]=L"All";  //����ȫ������
const int Sys_Group_All_ID=9999;  //����ȫ��ID
const wchar_t Sys_IData_FIle[]=L"IDataSwap";  //��������Ԫ���ݽ����ļ�

const wchar_t Sys_ClipBoard[]=L"SAUSAGE";

//ʰȡͼԪ
const int Sys_SelectRange=10;  //ʰȡ����Χ,��λ:����
//const int Sys_SelectRange=3;  //ʰȡ����Χ,��λ:����	//�Ǳ���2016.7.19

//ʰȡ���ص�ͼԪ���Ƶ���ʼ����,��˳��Ҳ������ʰȡ�����ȼ�
const int Sys_VirtualPointName0= 1       ;  //���
const int Sys_VertexName0=		 1000    ;  //��һ���������ƣ�����ʰȡ
const int Sys_BeamName0=         10000000;  //��һ�����ṹ/��Ԫ���ƣ�����ʰȡ
const int Sys_PillarName0=       20000000;  //��һ�����ṹ/����Ԫ���ƣ�����ʰȡ
const int Sys_BracingName0=      30000000; 
const int Sys_EdgeName0=         40000000; 
const int Sys_HideBeamName0=     50000000; 
const int Sys_LongiRebarName0=   60000000; 
const int Sys_StructLineName0=   70000000;  //��һ���ṹ�ߵ�Ԫ���ƣ�����ʰȡ
const int Sys_GuidesName0=       80000000;  //��һ�������ߵ�Ԫ���ƣ�����ʰȡ
const int Sys_PlateName0=        90000000;  //��һ����ṹ/�浥Ԫ����
const int Sys_WallName0=        100000000;  //��һ��ǽ�ṹ/ǽ��Ԫ����
const int Sys_BodyName0=        110000000;  //��һ��ʵ�嵥Ԫ���ƣ�����ʰȡ
const int Sys_NodeName0=        120000000;  //��Ԫ���
const int Sys_ShadowPointName0= 130000000; 
const int Sys_BeamElmName0=     140000000;  //����Ԫ
const int Sys_Tri3ShellName0=   150000000;  //����������οǵ�Ԫ
const int Sys_Quad4ShellName0=  160000000;  //�Ľ���ı��ε�Ԫ
const int Sys_ShadowPolyName0=  170000000; 
const int Sys_LinkName0=		180000000;	//�Ǳ��� 2015.5.20

const int Sys_MaxName0=         220000000;  //���ͼԪ����

//����
const int Sys_Max_Node_Components=8; //�����������������
//const int Sys_Max_Elm_Components=16; //���Ԫ������������
const int Sys_Max_Story_Components=20; //���¥��������������
const float Sys_DeformRatio=1000.0f; //���α���
const float Sys_StaticLoadTime=1.0f;  //������ؼ���ʱ��

//�����С
const int Sys_Max_View=4;  //�����ͼ������
const int Sys_BoundaryArray=500; //��ṹ�����߽����Ŀ
const int Sys_MaxPSize=5000;  //mesh2d���õ����������
const int Sys_MaxESize=5000;  //mesh2d���õ������Ԫ��
const int Sys_SUFFERED=100; //�����Ż����õ�������,����һ�������Ӱ���������������
const int Sys_IncAlloc=10000; //�ڴ治��ʱrealloc���ӵĹ�ģ
const int Sys_SubSectionParaNum=200;  //�ӽ��漸�β���������Ҫ��ʵ�������ȷ���;  2020�汾����������Ϊ 49�� ԭ��12Ϊ6����
const int Sys_MaxPoly=5; //һ�������ж���α߽�����������������߽���ڱ߽硣һ������������һ�����棬�����Ǹ���ͨ��һ����������ǵ�һ����
const int Sys_MaxLabel =10; //һ����������ע��
const int Sys_Max_Stories  =300; //���¥��
const int Sys_Max_Towers  =30; //�������
const int Sys_DOF=6; //���������ɶ�
const int Sys_Max_ComponentLength =16; //��������󳤶ȣ��ַ���
const int Sys_Max_Connect_Wall =4;  //ÿ������������ǽ������
const int Sys_MAX_NEIGHBOR =100 ;  //һ�������Χ�����������
const int SYS_MAX_NEIGHBOR_IN_PLANE =30 ;  //ƽ����һ�������Χ�����������
const int Sys_StructTypeNum =6 ;  //ϵͳ֧�ֵĹ���������	//�Ǳ��� 2015.5.25 //���������ֽ���Ϣ��������������𹹼�
const int Sys_MaxDriftNum =300 ;  //�����λ�ƽ�λ�ø���
const int Sys_EQ_Class_Num =6;  //���𼶱���
const int Sys_MinModeNum =3 ;	//ʹ����������ʱ����С������
const int Sys_MaxModeNum =3000 ; //ʹ����������ʱ�����������
const int Sys_MinMRParaNum =2 ;	//ʹ���Զ���������ʱ����С���ݵ���
const int Sys_MaxMRParaNum =12 ;	//ʹ���Զ����ٶ���������ʱ��������ݵ���
const int Sys_MaxMRParaNumDis =12 ;	//ʹ���Զ���λ����������ʱ��������ݵ���
const int Sys_Material_Number =25 ;  //���ò��ϸ���
const int Sys_CheckErrors = 26; //���ģ�͵�����
const int MAX_POLYGONPOINT =500;
const int Sys_MinPerformGrade=3;	//�������ܵȼ�//2015.12.9
const int Sys_MaxPerformGrade=6;	//������ܵȼ�
const int Sys_MinHingeGrade=3;	//������Խµȼ�
const int Sys_MaxHingeGrade=6;	//������Խµȼ�
const int Sys_MaxLoadcase=20;	//�����ع���
const int Sys_MaxLoadcaseComb=200;	//���������
const int Sys_MaxLoad=50;//��������


//״̬������
const int Sys_Pane_Coor=2;  //��̬������ʾ״̬��
const int Sys_Pane_Case=3;  //������Ϣ��ʾ״̬��
const int Sys_Pane_Step=4;  //ʱ�䲽��Ϣ��ʾ״̬��

//��������
const int Sys_Quad_Elm0=0x10000000;  //�����κ��ı��ε�Ԫͳһ���ʱ���ı��ε�Ԫ�Ŀ�ʼ��ţ������ε�Ԫ��0��ʼ
//const float Sys_StraightCosValue=0.94f;   //�����ж�ǽ���߹��ߵķ���������ֵ��С��20�Ȼ����160����Ϊ����
const float Sys_StraightCosValue=0.996f;   //�����ж�ǽ���߹��ߵķ���������ֵ��С��5�Ȼ����175����Ϊ����  //�Ǳ��� 2015.2.13
const float Sys_MinPermitLineLength=0.3f;  //�����ʹ�λ�����ԭ����ɵ���С����ṹ�߳ߴ磬С�ڣ������ڣ��óߴ���ʹ����ṹ����б����������
const float Sys_MinBraceAngle=20.0f;


#ifdef _SIMPLIFIED_CHINESE
const wchar_t Sys_DefaultFontName[]= L"����" ;  //ȱʡ����
#else
const wchar_t Sys_DefaultFontName[]=L"Arial";   //ȱʡ����
#endif

const int Sys_DefaultFontSize=12;        //�����С����λ������,12����=9��

const wchar_t Sys_MakeLevelCase[]=L"make_level";  //��ƽ�õĹ�������

const int Sys_RC_Double_ConcFibre=36;		//��ͨ˫��RC�����������ά�ʷ���
const int Sys_RC_Single_ConcFibre=12;		//��ͨ����RC�����������ά�ʷ���
const int Sys_ST_SteelFibre=16;				//��ͨST�����͸���ά�ʷ���
const int Sys_CFT_SteelFibre=24;			//��ͨCFT�����͸���ά�ʷ���
const int Sys_SRC_SteelFibre=16;			//��ͨSRC�����͸���ά�ʷ���
const int Sys_Rebar=8;						//�ֽ���
const int Sys_PlateConcLayer=1;	            //¥��Ļ������ֲ���
const int Sys_WallConcLayer=6;	            //ǽ�Ļ������ֲ���

const int Sys_Arbitrary_ConcFibre=36;			//�����������ά������
const int Sys_Arbitrary_SteelFibre=64;			//�������ά������

const int Sys_Geo_Num =6;				   //�����������
const int Sys_Max_ModalDamage =100  ;      //һ�����ʵʱģ̬��������

const int Sys_nLinkHead=5;			  //һ������������������������м�����
const int Sys_nLinkData =30;          //һ�����ӵ����ɶ�����������������м�����

const int Sys_nCrt1D_c =20;				//������һά������ѹ������
const int Sys_nCrt1D_t =10;				//������һά��������������
const int Sys_nCrt2D_c =21;				//��������ά������ѹ������
const int Sys_nCrt2D_t =10;				//��������ά��������������

//����ö��ֵ�������ȷ������ֵ�ˣ��������⺬�壬��Ҫ�������

//�������ͣ�ö��ֵ�����������
enum MATERIAL_TYPE
{
	MAT_UNKNOWN		= 0, //δ����
	MAT_CONC		= 1, //������
	MAT_REBAR		= 2, //�ֽ�
	MAT_STEEL		= 4, //�͸ֺ͸ְ�
	MAT_TENDON		= 8, //ԤӦ�������
};


//�ṹ����,ʵ���ϴ�������������
enum STRUCT_TYPE
{
	STRUCT_UNKNOWN 		=0,          //δ֪

	//����ͼԪ���ֱ����ڲ�ͬ������
	STRUCT_VEX   		=0x01,       //��,���������������㣬��׽�������STRUCT_NODE
	STRUCT_LINE    		=0x02,       //�ṹ��

	//��״�����������ͬһ������
	STRUCT_BEAM    		=0x04,       //�����
	STRUCT_PILLAR  		=0x08,       //��
	STRUCT_BRACING 		=0x10,       //б��
	STRUCT_EDGE			=0x20,       //��Ե����
	STRUCT_HIDEBEAM		=0x40,       //������������
	STRUCT_LONGIREBAR	=0x80,       //�����ݽ�
	STRUCT_LINK			=0x100,		//һ������

	//��״�����������ͬһ������
	STRUCT_PLATE   		=0x1000,      //��
	STRUCT_WALL    		=0x2000,      //ǽ������ǽ��
	STRUCT_GUIDES    	=0x10000,     //������
	STRUCT_BODY    		=0x20000,      //ʵ�壬��ʱ����

	//��Ԫ���ͣ��ֱ����ڲ�ͬ������
	STRUCT_NODE   		=0x100000,    //����㣬�����ڲ�׽
	STRUCT_BEAM_ELM		=0x200000,    //����Ԫ��BEAM
	STRUCT_TRI3_SHELL	=0x400000,	  //����������οǵ�Ԫ��TRI3
	STRUCT_QUAD4_SHELL	=0x800000,	  //�Ľ���ı��ε�Ԫ��QUAD

	//���
	STRUCT_VIRTUAL_POINT=0x1000000,

	//����������ϲ�������GetIDG��ֻ�����߼��ж�
	STRUCT_ALL_BEAM		=STRUCT_BEAM | STRUCT_HIDEBEAM | STRUCT_LONGIREBAR ,  //����������,ˮƽ�߹���	//�Ǳ��� 2015.5.21
	STRUCT_ALL_PILLAR	=STRUCT_PILLAR | STRUCT_BRACING | STRUCT_EDGE ,  //��������������ˮƽ�߹���
	STRUCT_ALL_1DSTRUCT =STRUCT_ALL_BEAM | STRUCT_ALL_PILLAR|STRUCT_LINK,  //���е��߹�������Ӧm_cBeamȫ������
	STRUCT_ALL_2DSTRUCT =STRUCT_PLATE | STRUCT_WALL,  //���е��湹������Ӧm_cPlateȫ������
	STRUCT_BEAMWALL		=STRUCT_BEAM|STRUCT_WALL, //ǽ�������Ƕ�������	

	//STRUCT_ALL			=0x7fffffff,  //ȫ����׽�������ṹ��
	STRUCT_ALL			=STRUCT_ALL_1DSTRUCT|STRUCT_ALL_2DSTRUCT|STRUCT_VEX,  //ȫ����׽�������ṹ��	//�Ǳ��� 2016.7.15
};

enum STRUCT_SUBTYPE_WALL
{
	STRUCT_WALL_UNKNOWN 		=0,		//δ֪
	STRUCT_WALL_WALLCOL			=0x01,	//ǽ��
	STRUCT_WALL_WALLBEAM		=0x02,	//ǽ��
};

//�ṹ����,ʵ���ϴ�������������
enum LINK_SUBTYPE
{
	LINK_UNKNOWN 			=0,		//δ֪
	LINK_VELODAMPER			=0x1,	//������-�ٶ��� //�Ǳ���2015.5.19	
	LINK_ISOLATOR			=0x2,	//����֧��
	LINK_BRB				=0x4,	//BRB 
	LINK_SPRING				=0x8,	//����
	LINK_USERDAMPERVEL		=0x10,//�Զ����ٶ���������
	LINK_DISPDAMPER			=0x20,
	LINK_CABLE				=0x40,
	LINK_GAP				=0x80,
	LINK_FRICPND			=0x100,
	LINK_HOOK				=0x200,
	LINK_USERDAMPERDIS		=0x400,//�Զ���λ����������
	LINK_WEN				=0x800,//Wenģ��
	LINK_ISOLATOR3D			=0x1000,//������ϸ���֧��
	LINK_TMD				=0x2000,//TMD
	LINK_PRESTRJOIN			=0x4000,//ԤӦ�����Ӽ�
	LINK_MAXWELL			=0x8000,//Maxwell ģ��
	LINK_ESB				=0x10000,//���Ի���֧��
	LINK_ALL_LRB=LINK_ISOLATOR|LINK_ISOLATOR3D,
	LINK_ALL_ISOBEARING=LINK_ALL_LRB|LINK_FRICPND|LINK_ESB,
	LINK_VDAMPER	=LINK_VELODAMPER|LINK_MAXWELL,
};

struct LinkName
{ 
	const wchar_t *sName;
	LINK_SUBTYPE iType;
};
const struct LinkName LinkNamesArray[]=
{
#ifdef _SIMPLIFIED_CHINESE
	L"�ٶ���������(Kelvin)",LINK_VELODAMPER,
	L"�ٶ���������(Maxwell)",LINK_MAXWELL,
	L"λ����������(������)",LINK_DISPDAMPER,
	L"�Զ����ٶ�������",LINK_USERDAMPERVEL,
	//L"�Զ���λ��������",LINK_USERDAMPERDIS,
	L"��Ƶ����������",LINK_TMD,
	L"������֧��",LINK_BRB,
	L"����֧��",LINK_ISOLATOR,
	L"����֧��(Wen)",LINK_ISOLATOR3D,
	L"���Ի���֧��",LINK_ESB,
	L"Ħ����֧��",LINK_FRICPND,
	L"Wenģ��",LINK_WEN,
	L"���Ե���",LINK_SPRING,
	L"����",LINK_CABLE,
	L"��",LINK_HOOK,
	L"��϶",LINK_GAP,
	//L"ԤӦ�����Ӽ�",LINK_PRESTRJOIN,
#else
	L"Dampers-Velocity(Kelvin)",LINK_VELODAMPER,
	L"Dampers-Velocity(Maxwell)",LINK_MAXWELL,
	L"Dampers-Displacement",LINK_DISPDAMPER,
	L"Dampers-Velo User defined",LINK_USERDAMPERVEL,
	//L"Dampers-Disp User defined",LINK_USERDAMPERDIS,
	L"TMD",LINK_TMD,
	L"BRB",LINK_BRB,
	L"Isolators",LINK_ISOLATOR,
	L"3D Isolators",LINK_ISOLATOR3D,
	L"Elastic Slide Bearing",LINK_ESB,
	L"Friction Pendulum",LINK_FRICPND,
	L"Plastic(Wen)",LINK_WEN,
	L"Spring",LINK_SPRING,	
	L"Cable",LINK_CABLE,
	L"Hook",LINK_HOOK,
	L"Gap",LINK_GAP,
	//L"Prestressed Join-key",LINK_PRESTRJOIN
#endif
};

//�����Ͷ���
enum GROUP_STYLE
{
	STYLE_BEAM=0,		//��ʽ
	STYLE_COUPLING,	//����ʽ
	STYLE_BRACING,	    //��ʽ
	STYLE_WALL,				//ǽ��ʽ:���
	STYLE_WALL2,			//ǽ��ʽ:�Խ�ǽ
	STYLE_WALL3,			//ǽ��ʽ:�Խ�ǽ
	STYLE_INVY1,				//������1��
	STYLE_Y1,					//������1��
	STYLE_INVY2,				//������2��
	STYLE_Y2,					//������2��
	STYLE_INVY3,				//������3��
	STYLE_Y3,					//������3��
	STYLE_INVY4,				//������4��
	STYLE_Y4,					//������4��
	STYLE_V,						//��V���� ",L
	STYLE_INVV,				//��V���� ",L
	STYLE_DISAMP1,		//λ�ƷŴ���1
	STYLE_DISAMP2,		//λ�ƷŴ���2
	STYLE_DISAMP3,		//λ�ƷŴ���3
	STYLE_DISAMP4,		//λ�ƷŴ���4
	STYLE_USER1,			//�Զ��崮��
	STYLE_USER2,			//�Զ��崮����
};	

struct LinkGroupStyle
{ 
	const wchar_t *sName;
	GROUP_STYLE iType;
};

//��ʽ�б�
const struct LinkGroupStyle sGroup_Style[]={
#ifdef _SIMPLIFIED_CHINESE
	L"��ʽ",						STYLE_BEAM,	
	L"����ʽ",             		STYLE_COUPLING,
	L"��ʽ ", 					STYLE_BRACING,	
	L"ǽ��ʽ1 ", 				STYLE_WALL,			
	L"ǽ��ʽ2 ", 				STYLE_WALL2,		
	L"ǽ��ʽ3 ", 				STYLE_WALL3,		
	L"������1�� ",			STYLE_INVY1,			
	L"������1�� ",			STYLE_Y1,				
	L"������2�� ",			STYLE_INVY2,			
	L"������2�� ",			STYLE_Y2,				
	L"������3�� ",			STYLE_INVY3,			
	L"������3�� ",			STYLE_Y3,				
	L"������4��",			STYLE_INVY4,			
	L"������4�� ",			STYLE_Y4,				
	L"��V���� ",				STYLE_V,					
	L"��V���� ",				STYLE_INVV,			
	L"λ�ƷŴ���1 ",		STYLE_DISAMP1,	
	L"λ�ƷŴ���2",		STYLE_DISAMP2,	
	L"λ�ƷŴ���3 ",		STYLE_DISAMP3,	
	L"λ�ƷŴ���4 ",		STYLE_DISAMP4,	
	L"�Զ��崮�� ",		STYLE_USER1,
	L"�Զ��岢�� ",		STYLE_USER2
#else
	L"Beam",                                        STYLE_BEAM,	
	L"Coupling Beam",					  STYLE_COUPLING,
	L"Bracing",									 STYLE_BRACING,	
	L"Wall1",								 STYLE_WALL,			
	L"Wall2",								 STYLE_WALL2,		
	L"Wall3",								 STYLE_WALL3,		
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

//��������
enum FIELD_TYPE
{
	FIELD_NONE=0,

	//����Ϊ��㳡
	FIELD_STATIC_DISP=0x0001,  //������ؽ��λ��
	FIELD_MODAL		=0x0002,  //ģ̬����
	FIELD_DISP		=0x0004,  //���λ��
	FIELD_TEMP		=0x0008,  //����¶�
	FIELD_ACCE		=0x0010,  //�����ٶ�
	FIELD_SPEED		=0x0020,  //����ٶ�
	FIELD_MODAL_DAMAGE	=0x0012,  //ʵʱģ̬����
	FIELD_ENERGY		=0x0040,  //�������
	FIELD_BUCKLING		=0x0080,  //����ģ̬
	FIELD_DEFECT	  =0x0100,  //ȱ��
	FIELD_MAXMODAL	=0x0200,  //���Ƶ��

	FIELD_CMODAL	=0x0400,  //ģ̬����
	FIELD_CMODAL_DISP = 0x0800, // ��ģ̬�ڵ�λ��

	//����Ϊ��Ԫ������16λΪ0
	FIELD_STRESS=0x10001,  //��ԪӦ��
	FIELD_STRAIN=0x10002,  //��ԪӦ��
	FIELD_FORCE =0x10004,   //��Ԫ����
	FIELD_DAMAGE=0x10008,  //��Ԫ����
	FIELD_REBAR_PLASTIC_STRAIN=0x10010,  //��Ԫ����Ӧ��
	FIELD_STEEL_PLASTIC_STRAIN=0x10020,  //��Ԫ����Ӧ��
	FIELD_TOP_STORY_FORCE     =0x10040,  //¥��䶥����Ԫ����
	FIELD_BOTTOM_STORY_FORCE  =0x10080,  //¥���ײ���Ԫ����
	FIELD_REBAR_STRESS=0x10100,  //��Ԫ�ֽ�Ӧ��
	FIELD_STEEL_STRESS=0x10200,  //��Ԫ�ֲ�Ӧ��
	FIELD_LINK =0x10400,  //һ������

	FIELD_PERFORM			=0x100400,  //��Ԫ����
	FIELD_PERFORM_STRU		=0x100800,  //��������
	FIELD_HINGE				=0x101000,  //���Խ�

	FIELD_SHEAR_COMPRESSION_RATIO		= 0x1000000,//��ѹ�ȣ��жϱ������Ϊ&0x10000���ƹ�0x110000
	FIELD_SHEAR_SPAN_RATIO				= 0x1020000,//�����
	FIELD_NOMINAL_TENSILE_STRESS		= 0x1040100,//������Ӧ��//�ܿ��ٶȼ����ٶȳ�
	FIELD_NOMINAL_TENSILE_STRESS_RATIO	= 0x1040200,//������Ӧ����
	FIELD_AXIAL_COMPRESSION_COEF		= 0x1040400,//��ѹ��ϵ��
	FIELD_AXIAL_COMPRESSION_RATIO		= 0x1040800,//��ѹ��
	FIELD_SHEAR_STRESS_ELA_RATIO		= 0x1080100,//����������//�ܿ��ٶȼ����ٶȳ�
	FIELD_MOMENT_SHEAR_RATIO	= 0x1080200,//����������//�ܿ��ٶȼ����ٶȳ�
	FIELD_FLEXURAL_BEARING_CAPACITY	= 0x1080800,//����������//�ܿ��ٶȼ����ٶȳ�
	FIELD_DISP_ANGLE					= 0x1080400,


	//��������������
// 	FIELD_DISP					=0x10000004,  //���λ�� 
// 	FIELD_DAMAGE				=0x10010008,  //��Ԫ����
// 	FIELD_REBAR_PLASTIC_STRAIN	=0x10010010,  //��Ԫ����Ӧ��
// 	FIELD_STEEL_PLASTIC_STRAIN	=0x10010020,  //��Ԫ����Ӧ��
// 	FIELD_PERFORM				=0x10100400,  //��Ԫ����
// 	FIELD_PERFORM_STRU			=0x10100800,  //��������

};

enum PERFORM_FIELD
{
	PERFORM_NONE	=0,		//δ֪
	PERFORM_DC		=0x1,		//δ֪
	PERFORM_DT		=0x2,		//δ֪

	PERFORM_SIGMAP	=0x4,		//δ֪
	PERFORM_HINGE1	=0x8,		//δ֪
	PERFORM_HINGE2	=0x10,		//δ֪
	PERFORM_DAMPER	=0x12,		//2020.7.1����
};
//ͼ������
enum LEGEND_TYPE
{
	LEGEND_ALLSTEP,          //��ȫ�̼�ֵ������ɫ
	LEGEND_ALLSTEP_VISIBLE,  //ȫ�̿ɼ�����
	LEGEND_MOMENT,           //��˲ʱ��ֵ������ɫ
	LEGEND_MOMENT_VISIBLE,   //˲ʱ�ɼ�����
	LEGEND_USER,             //�û����������Сֵ
};

//����ͼ����
enum DEFORM_TYPE
{
	DEFORM_NONE,  //������
	DEFORM_MODAL, //ģ̬����
	DEFORM_STATIC, //��������λ��
	DEFORM_DYNA,   //��������λ��
	DEFORM_SPECT,  //��Ӧ�׹���λ��
	DEFORM_DEFECT, //ȱ��
};

//��ģ��Χ
enum BUILDRANGE
{
	RANGE_INVALID=-1,
	RANGE_THISSTORY=0, //��¥��
	RANGE_ALLSTORIES=1,  //����¥��
	RANGE_GROUP=2,     //����
};

//��ͼ����
enum DRAWTYPE
{
	DRAWTYPE_UNKNOWN=0,
	DRAWTYPE_XY=0x01,
	DRAWTYPE_3D=0x02,
	DRAWTYPE_YZ=0x04,
	DRAWTYPE_ZX=0x08,
	DRAWTYPE_PROFILE=0x10,  //��ά����ͼ
	DRAWTYPE_CROSSSECTION=0x20,  //��ά����ͼ
};

//����������״̬
enum TOOLSTATUS
{
	TOOL_ASSIGNDRIFT,  //ָ�����λ�ƽ����λ��(���򹹼�)
	TOOL_BREAKLINE,   //��������㣬�Ͽ��ṹ��
	TOOL_CLICKBEAM, //���������
	TOOL_CLICKPILLAR, //���������
	TOOL_CLICKBRACE, //�������б��
	TOOL_CLICKPLATE, //������ɰ�
	TOOL_CLICKWALL, //�������ǽ
	TOOL_CHECKCROSS,   //ǿ�Ʋ�������
	TOOL_DEFINECROSSSECTION,   //��׽2���㣬�ڵ�����������ʾ����ͼ
	TOOL_DEFINEPROFILE,   //��׽2�����һ�������ڵ�����������ʾ����ͼ
	TOOL_DRAWBEAM, //�����ṹ
	TOOL_DRAWBRACING,  //����б��
	TOOL_DRAWLINK,  //����һ������
	TOOL_CLICKLINK, //�������һ������
	TOOL_CLICKDAMPERGROUP,//������ɼ������
	TOOL_DRAWDAMPERGROUP,//���㽨�������

	TOOL_DRAWGUIDELINE, //�渨����
	TOOL_DRAWPILLAR,  //������
	TOOL_DRAWPLATE, //��׽��Χ�ɰ��ǽ
	TOOL_DRAWSTRUCTLINE, //��ṹ��
	TOOL_DRAWWALL,  //����ǽ
	TOOL_CLICKDISSIPWALL,  //�������������ǽ
	TOOL_DRAWZONEBEAM, //������������
	TOOL_DRAWZONEPILLAR, //������������
	TOOL_DRAWZONEPLATE, //���������ɰ�
	TOOL_DRAWZONELINK, //����������һ������
	TOOL_EDIT_MOVE,       //����겶׽���㹹��ʸ�����ƶ��������е�ѡ��
	TOOL_EDIT_PASTE,      //����겶׽ճ���ο���
	TOOL_EXTENDLINE,       //�����߶δ�������ཻ�߶�,����
	TOOL_HOLEWALL, //ǽ�Ͽ���
	TOOL_MEASURE_DIST,       //�����������
	TOOL_MODIFYLINE,   //���������ƶ��ṹ�ߣ������ƶ�����
	TOOL_MODIFYVERTEX, //������ƶ���
	TOOL_COPYVERTEX, //���Ƶ㹹�������� ��2016.01.29
	TOOL_MODIFY_PILLARANGLE,   //��׽2���㣬������ѡ���ӵ���ת��
	TOOL_SELECT_ZONE,  //��ѡͼ��
	TOOL_SET2NDBEAM, //���ô���
	TOOL_SETANTICULATE, //���ý½�
	TOOL_SETMAINBEAM, //��������
	TOOL_MERGELINE,   //�ϲ��ص��Ľṹ��
	TOOL_WELDINGLINE, //ɾ���ָ��㣬������
	TOOL_WELDINGSURF, //ɾ���ָ��ߣ�������
	TOOL_ZOOMIN,  //���ڷŴ�
	TOOL_GETNODE, //ʰȡ�ڵ� ��2016��3��3��
    //TOOL_SETSTORYBASICPOINT,//����¥����� ����12/05/2021
	//TOOL_GETPMMSTRUCT,//ʰȡPMM������ع��� ����28/05/2021

	TOOL_ALIGNBEAM,//��ƽ�����

	TOOL_LAST, //��β��ʶ�������������ǰ�棡������������������ʾ������SetOutputHistory
	TOOL_PICKMERGEORIGIN,	//ƴ��ģ��ԭ��ѡ��
};

//ѡȡ�����޸Ĳ������
enum MODIFY_PROPERTY
{
	MODIFY_BEAM_SECTION,    //�޸Ľ���
	MODIFY_BEAM_REBAR_RATIO, //�޸������
	MODIFY_BEAM_MATERIAL,   //�޸Ĳ���
	MODIFY_BEAM_LOAD,       //�޸ĺ���
	MODIFY_BEAM_ANGLE,       //�޸����ĽǶ�
	MODIFY_BEAM_DEFCET,     //�޸�����ʼ����ȱ��
	MODIFY_BEAM_STIRRUP_AREA,     //�޸����������
	MODIFY_BEAM_TYPE,     //ת��������

	MODIFY_BRACE_SECTION,    //�޸Ľ���
	MODIFY_BRACE_REBAR_RATIO, //�޸������
	MODIFY_BRACE_MATERIAL,   //�޸Ĳ���
	MODIFY_BRACE_LOAD,       //�޸ĺ���
	MODIFY_BRACE_ANGLE,       //�޸ĽǶ�
	MODIFY_BRACE_DEFCET,     //�޸ĳ�ʼ����ȱ��
	MODIFY_BRACE_STIRRUP_AREA,     //�޸Ĺ������
	MODIFY_BRACE_TYPE,     //ת��������

	MODIFY_PILLAR_SECTION,    //�޸Ľ���
	MODIFY_PILLAR_REBAR_RATIO, //�޸������
	MODIFY_PILLAR_MATERIAL,   //�޸Ĳ���
	MODIFY_PILLAR_LOAD,       //�޸ĺ���
	MODIFY_PILLAR_ANGLE,       //�޸ĽǶ�
	MODIFY_PILLAR_DEFCET,     //�޸�����ʼ����ȱ��
	MODIFY_PILLAR_STIRRUP_AREA,     //�޸Ĺ������
	MODIFY_PILLAR_TYPE,     //ת��������
	MODIFY_PILLAR_APPENDMATERIAL, // ���Ӳ��� Ŀǰ���ֺ�������2021-12-16

	MODIFY_LINK_ANGLE,       //�޸ĽǶ�
	MODIFY_LINK_TYPE,     //ת��������

	MODIFY_PLATE_THICKNESS,  //�޸ĺ��
	MODIFY_PLATE_SECTION,
	MODIFY_PLATE_REBAR_RATIO, //�޸������
	MODIFY_PLATE_MATERIAL,   //�޸Ĳ���
	MODIFY_PLATE_LOAD,       //�޸ĺ���
	MODIFY_PLATE_LAYER,       //�޸ķֲ�

	MODIFY_WALL_THICKNESS,  //�޸ĺ��
	MODIFY_WALL_SECTION,
	MODIFY_WALL_REBAR_RATIO, //�޸������
	MODIFY_WALL_STEEL_THICK, //�޸�ǽ�ְ�
	MODIFY_WALL_MATERIAL,   //�޸Ĳ���
	MODIFY_WALL_LOAD,       //�޸�ǽ���ߺ���
	MODIFY_WALL_LAYER,       //�޸ķֲ�

	MODIFY_LONGI_SECTION,    //�޸������ݽ����
	MODIFY_LONGI_MATERIAL,   //�޸������ݽ����
	MODIFY_LONGI_LOAD,       //�޸������ݽ����������

	MODIFY_EDGE_SECTION,    //�޸ı�Ե��������
	MODIFY_EDGE_MATERIAL,   //�޸ı�Ե��������
	MODIFY_EDGE_REBAR_RATIO, //�޸ı�Ե��������� �� 2016��2��18��

	MODIFY_POINT_LOAD,       //�޸ļ��е���أ���������������
	MODIFY_POINT_BC,         //�޸������ı߽�����

	MODIFY_MESH_RATIO,		 //�޸��������ϵ��
	MODIFY_MEMBER_CONSTITUTIVE, //�޸Ĺ���������ϵ����
	MODIFY_MEMBER_SEISMICGRADE, //�޸Ĺ�����������ȼ�

	MODIFY_MEMBER_VIPTYPE, //�޸Ĺ�����������ȼ�
	MODIFY_MEMBER_TOWER, //�޸Ĺ�����������ȼ�

	MODIFY_MEMBER_TEMPER,       //�޸Ĺ����¶�
	MODIFY_BEAM_INITIALSTRAIN,       //�޸��߹�����Ӧ��
	MODIFY_PLATE_INITIALSTRAIN,      //�޸��湹����Ӧ��

	MODIFY_POINT_THLOAD,  //�޸ĵ㶯��
	MODIFY_POINT_CROSS_STORY,
	MODIFY_MEMBER_FORCEADJUST,       //�޸Ĺ�����������ϵ��
	MODIFY_MEMBER_PROPADJUST,       //�޸Ĺ����������Ե���ϵ��
};

//ģ��������Դ
enum MODEL_SOURCE
{
	MODEL_PKPM=1, //PKPM����
	MODEL_PRE=2, //Ԥ������
	MODEL_SSG=3,  //sausage�������
	MODEL_ETABS=4,  //ETABS����
	MODEL_DXF=5,  //DXF����

	MODEL_SATWE		=6,
	MODEL_PMSAP		=7,
	MODEL_MIDAS		=8,

	MODEL_PKPM1=10, //�ɰ�PKPM���룬1��ģ�ͣ��ѷ���
	MODEL_PKPM2=11, //�ɰ�PKPM���룬2��ģ�ͣ��ѷ���
	MODEL_MP=12,     //�¼����ݸ�ʽ��ĿȺ
	MODEL_ABAQUS=14, //inp�ļ�����
	MODEL_SAP2K=15, //SAP2000�ļ�����
	MODEL_YJK=16, //YJK�ļ�����


};

//�û���������ķ�ʽ
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

//�ṹ��ϵ����
enum STRUCT_SYSTEM
{
	SS_FRAME            =0,    //���
	SS_FRAME_WALL       =1,    //��ܼ���ǽ
	SS_ALL_WALL         =2,    //ȫ����ؼ���ǽ
	SS_PART_WALL        =3,    //���ֿ�֧����ǽ
	SS_FRAME_TUBE       =4,    //���-����Ͳ
	SS_TUBE_TUBE        =5,    //Ͳ��Ͳ
	SS_PLATE_PILLAR_WALL=6,    //����-����ǽ
}; 

enum MESHING_METHOD
{
	MESHING_TRI_INSERTPOINT,  //ʹ�ñ߽����뷨����������
	MESHING_TRI_BLOCK,  //ʹ�ô������η����㷨����������
	MESHING_QUAD_TRI,  //���ǽʹ����·���ʷ��ı��κ������λ�ϵ�Ԫ
	//MESHING_PLATEQUADTRI_WALLQUAD,  //ǽȫ���ʷֳ��ı��Σ���ʹ���ı��κͺ������λ�ϵ�Ԫ
};

//�������
enum VIRTUAL_POINT_TYPE
{
	VIRTUAL_POINT_NONE,  //������
	VIRTUAL_POINT_MIDDLE,  //�߶��е�
	VIRTUAL_POINT_PERPENDICULAR, //����
	VIRTUAL_POINT_CROSS,  //���߶ν���
	VIRTUAL_POINT_1THIRD,  //1/3��
};

//��ǵ���״���������ʹ��
enum MARKER_TYPE
{
	MARKER_CIRC  		=0x01, //Բ��
	MARKER_BOX  		=0x02, //������
	MARKER_CROSS 		=0x04, //ʮ�ֽ���
	MARKER_DELTA 		=0x08, //������
	MARKER_DOWNDELTA 	=0x10,//��������
	MARKER_DIAGCROSS	=0x20,//45�Ƚ���
	MARKER_PEDAL		=0x40,//ֱ�Ǳ��
};

//����ճ������
enum PASTE_TYPE
{
	PASTE_MOVING = 0,    //��������ƶ�
	PASTE_ROTATE = 1,  //��ת
	PASTE_NORMAL = 2,  //������
	PASTE_MIRRORX = 3, //�Գ��ᴹֱ��X��
	PASTE_MIRRORY = 4, //�Գ��ᴹֱ��Y��
	PASTE_MIRROR = 6, //�������᾵��
	PASTE_STORY = 5,   //��临��
};

enum FEA_CONTROL
{
	CTRL_REBAR_STIFF=0x02,	//�նȼ���ֽ�����
	CTRL_SILENCE=0x100,		//��Ĭִ��
};


enum ANALYSIS_TYPE
{
	SOLVER_EXP		=0, //��ʽ���� ���������Ĳ��
	SOLVER_NEWMARK	=1, //NewMark
	SOLVER_MODAL	=2, //���͵��ӷ�
	SOLVER_WANGDU	=3, //wang-du��
	SOLVER_SP		=4, //SP����
	SOLVER_FNA		=5, //FNA����
	SOLVER_CQC		=6, //��Ӧ�׷�
	SOLVER_MNL		=7, //����������N-L��
};

enum CRT_SKELETON_TYPE
{		
	CODE_POLYLINE 		=0,   	//�淶����ߣ��û��Զ�������			
	CODE_CURVE			=1,   	//�淶ȫ����			
	RUSCH				=2,	 	//Rusch						
	HONGNESTAD			=3,   	//Hongnestad				
	MANDER				=4,   	//Manderģ��				
	QIAN				=5,   	//Ǯ����				
	KENTPARK			=6,   	//Kent-Park					
	HAN					=7,   	//���ֺ�����Լ��������ģ��		
	HAN_TUBE			=8,   	//���ֺ�Բ�����ֹ�ģ��		
};
enum STEEL_SKELETON_TYPE
{		
	TWO_LINE 			=0,   	//������			
	THREE_LINE			=1,   	//������			
	ESMAEILY_XIAO		=2,   	//Esmaeily-Xiao				
	COM_BUCKLING		=3,   	//������ѹ�����ĸֲı���				
};

enum DEVICE_TYPE
{
	DEVICE_CUDA		=0x2000, 
	DEVICE_OMP		=0x4000, 
	DEVICE_MASK		=DEVICE_CUDA|DEVICE_OMP,
};

enum RUN_CASE
{
	RUN_IMPSTATIC		=0x04,							//��ʽ������ؼ���
	RUN_MAXFREQ			=0x08,							//���Ƶ�ʷ���
	RUN_MODAL			=0x10,							//ģ̬����
	RUN_IMP				=RUN_IMPSTATIC|RUN_MAXFREQ|RUN_MODAL,			//һ����ʽ����
	RUN_BUCKLING		=0x40,							//������������

	RUN_EXPDYNA			=0x200,					//��ʽ����ʱ�̷���
	RUN_NONSTATIC		=0x400|RUN_EXPDYNA,		//�����Ծ�������
	RUN_EXPDYNA_DESIGN	=0x800|RUN_EXPDYNA,		//��ƹ�������
	RUN_TIMEHISTORY = 0x1000|RUN_EXPDYNA,    //��㼤��ʱ�̷���	
	RUN_PUSHOVER = 0x2000|RUN_EXPDYNA,    //�����Ƹ�����	

	RUN_MODAL_DAMAGE		=0x20000,					//ʵʱģ̬����

	RUN_CMODE			=0x40000,							//��ģ̬����   ��˼�� 20210527
};

enum BUILD_TYPE
{
	BUILD_UNKNOWN =-1,						//��������δ����
	BUILD_BEAM			=0,						//������
	BUILD_PILLAR		=1,						//������
	BUILD_BRACING	=2,						//���ó�
	BUILD_SLAB           =3,                      //���ð�
	BUILD_WALL          =4,                      //����ǽ
	BUILD_HOLE			=5,                      //���ö���
	BUILD_LINK			=6,                      //����һ������
	BUILD_LINE			=7,                      //������
};

//������������
enum STCASE_TYPE
{
	CASE_DEFAULT	=-1,       //Ĭ�Ϲ�����δʩ�ӵ�����
	STCASE_DL			=0,		//��					
	STCASE_LL			=1,		//��	
	STCASE_WL			=2,		//��
	STCASE_EL			=3,       //����
	STCASE_TMP			=4,		//�¶�
	STCASE_PRESTS	=5,		//ԤӦ��
	STCASE_USER		=6,		//�Զ���
};

enum DYCASE_TYPE
{
	//	CASE_DEFAULT	=-1,       //Ĭ�Ϲ�����δʩ�ӵ�����
	DYCASE_USER		=0,		//�Զ��壺�� ���ٶ� λ�� �ٶ�
	DYCASE_FORCE	=1,		//��				
	DYCASE_ACC		=2,		//���ٶ�	
	DYCASE_DISP 		=3,		//λ��
	DYCASE_VELO 		=4,		//�ٶ�
};

struct CaseTypeName
{ 
	const wchar_t *sName;
	int iType;
};
const struct CaseTypeName STCaseTypeNameArray[]=
{
	//_CHSL(L"�����",L"Dead"),		STCASE_DL,
	//_CHSL(L"�����",L"Live"),		STCASE_LL,
	//_CHSL(L"�����",L"Wind"),		STCASE_WL,
	//_CHSL(L"��������",L"Earthquake"),	STCASE_EL,
	//_CHSL(L"�û��Զ���",L"User"),	STCASE_USER,
	//_CHSL(L"�¶�",L"Temper"),	STCASE_TMP,
	//_CHSL(L"ԤӦ��",L"Prestress"),	CASE_PRESTS
#ifdef _SIMPLIFIED_CHINESE
//	L"Ĭ�Ϲ���",		CASE_DEFAULT,
	L"�����",		STCASE_DL,
	L"�����",		STCASE_LL,
	L"�����",		STCASE_WL,
	L"��������",	STCASE_EL,
	L"�¶�",	STCASE_TMP,
	L"Ӧ��",	STCASE_PRESTS,
	L"�Զ���",	STCASE_USER
#else
//	L"Default",	CASE_DEFAULT,
	L"Dead",		STCASE_DL,
	L"Live",		STCASE_LL,
	L"Wind",		STCASE_WL,
	L"Earthquake",	STCASE_EL,
	L"Temper",	STCASE_TMP,
	L"Prestrain",	STCASE_PRESTS,
	L"User",	STCASE_USER
#endif
};

const struct CaseTypeName DYCaseTypeNameArray[]=
{
#ifdef _SIMPLIFIED_CHINESE
	//	L"Ĭ�Ϲ���",		CASE_DEFAULT,
	L"�Զ���",	DYCASE_USER,
	L"��",			DYCASE_FORCE,
	L"���ٶ�",	DYCASE_ACC,
	L"λ��",		DYCASE_DISP,
	//L"�ٶ�",		DYCASE_VELO

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

//���������������
enum COMB_TYPE
{
	COMB_ADD			=0,	//���Ժ�				
	COMB_ENVELOPE=1,	//����
	COMB_ABSADD	=2,   //����ֵ��
	COMB_SRSS 			=3,	//SRSS
	COMB_RangeADD  =4,   //RangeAdd
};


//��������ˮƽ
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
	L"δ����",		PERFORM_0,
	L"����",		PERFORM_1,
	L"��΢��",	PERFORM_2,
	L"�����",	PERFORM_3,
	L"�ж���",	PERFORM_4,
	L"�ض���",	PERFORM_5,
	L"������",	PERFORM_6,
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

//�����������۱�׼
enum PERFORM_STANDARD_TYPE
{
	PERFORM_DEFAULT			=0,					
	PERFORM_RBSM = 1,
	PERFORM_STRAIN = 2,
	PERFORM_DRIFT			=3,		
	PERFORM_STRESS = 4,
	PERFORM_RBS = 5,
	PERFORM_COLLAPSE = 21,
};
