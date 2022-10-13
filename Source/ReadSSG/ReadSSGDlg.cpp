
// ReadSSGDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ReadSSG.h"
#include "ReadSSGDlg.h"
#include "afxdialogex.h"
#include "..\Common\SSGData.h"
#include "..\Common\PostData.h"
#include "..\Common\CF5ElmFieldData.h"

#include "..\Common\CF15StruFieldData.h"
#include "..\Common\Data.h"
//#include "..\Common\PublicFunc_Cpp.h"

#ifdef WIN64
#ifdef _DEBUG
#pragma comment(lib, "../../Lib/SSGAPI64_D.lib" )
#pragma comment(lib, "../../Lib/SSGPub64_D.lib" ) //2022版本修改
#else  
#pragma comment(lib, "../../Lib/SSGAPI64.lib" )
#endif  
#else
#ifdef _DEBUG
#pragma comment(lib, "../../Lib/SSGAPI32_D.lib" )
#else  
#pragma comment(lib, "../../Lib/SSGAPI32.lib" )
#endif  
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CReadSSGDlg 对话框




CReadSSGDlg::CReadSSGDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReadSSGDlg::IDD, pParent)
	, m_sMsg(_T(""))
	, m_iCaseNum(1)
	, m_fAngleGap(15)
	, m_sAngle(_T("0,"))
	, m_bOpenTxt(FALSE)
	, m_fError(0.5f)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON);
}

void CReadSSGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sMsg);
	DDX_Text(pDX, IDC_EDIT_CASE, m_iCaseNum);
	DDX_Text(pDX, IDC_EDIT_ANGLEGAP, m_fAngleGap);
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_sAngle);
	DDX_Control(pDX, IDC_EDIT1, m_cEditMsg);
	DDX_Check(pDX, IDC_CHECK_OPENTXT, m_bOpenTxt);
	DDX_Text(pDX, IDC_EDIT_ERROR, m_fError);
}

BEGIN_MESSAGE_MAP(CReadSSGDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON2, &CReadSSGDlg::OnBnClickedButtonReadSSG)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CReadSSGDlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_DISP, &CReadSSGDlg::OnBnClickedButtonDisp)
	ON_BN_CLICKED(IDC_BUTTON_HARM_DISP, &CReadSSGDlg::OnBnClickedButtonHarmDisp)
	ON_EN_KILLFOCUS(IDC_EDIT_NUM, &CReadSSGDlg::OnEnKillfocusEditNum)
	ON_BN_CLICKED(IDC_BUTTON1, &CReadSSGDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_DISPRATIO, &CReadSSGDlg::OnBnClickedButtonDispratio)
	ON_EN_CHANGE(IDC_EDIT_ANGLE, &CReadSSGDlg::OnEnChangeEditAngle)
END_MESSAGE_MAP()


// CReadSSGDlg 消息处理程序

BOOL CReadSSGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CReadSSGDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CReadSSGDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CReadSSGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CReadSSGDlg:: AppendMsg(CString sMsg)
{
	UpdateData();
	m_sMsg+=L"\n"+sMsg;
	UpdateData(FALSE);
	UpdateWindow();//2016.5.19
	m_cEditMsg.LineScroll(m_cEditMsg.GetLineCount());
}
void CReadSSGDlg:: ClearMsg()
{
	UpdateData();
	m_sMsg=L"";
	UpdateData(FALSE);
	UpdateWindow();//2016.5.19
}

CString GetMatName(int id)
{
	int n=GetMatNum();
	for (int i=0;i<n;i++)
	{
		if(g_Material[i].id==id) return g_Material[i].sName;
	}

	return L"";
}


void CReadSSGDlg::OnBnClickedButtonReadSSG()
{
	//打开SSG模型
	CString fname=L"";
	CString stitle=L"SAUSAGE文件|*.ssg||";
	CFileDialog dlg(TRUE,L"ssg",L"*.ssg",0,stitle);
	if(dlg.DoModal()!=IDOK) return;
	fname=dlg.GetPathName();

	//清除所有数据
	theData.Clear();
	theData.InitialAPI(); //2022版本修改
	theData.m_sPrjFile=fname;
	BOOL bSuccess=TRUE;

	DWORD tick0=GetTickCount(),tick1;	
	ClearMsg();
	AppendMsg(L"开始读入SSG模型数据...\r\n");

	//读入项目配置参数
	bSuccess&=theData.m_cPrjPara.Read(theData.m_sPrjFile);

	//读入楼层数据
	CASCFile fin;
	if(!fin.Open(theData.m_sPrjFile,CFile::modeRead|CFile::shareDenyWrite)) return;
	int count;
	if(fin.FindKey("*STORY"))
	{
		count=fin.GetKeyValueInt("NUMBER=");
		if(count>0)
		{
			theData.m_nStory=count-1;
			for(int i=0;i<=theData.m_nStory;i++)
			{
				theData.m_pStory[i].Read(fin);
			}
		}
	}
	if(fin.FindKey("*STYPROP"))  //楼层参数
	{
		fin.GetKeyValueInt("NPARA=");  //参数个数（列数），行数为楼层数（包括0层）
		fin.GetKeyValueInt("NSTRUCTTYPE=");  //构件种类
		int nrec=fin.GetKeyValueInt("NUMBER=");  //记录数
		for(int i=0;i<nrec;i++)
		{
			CString key=fin.GetStr();  //结构类型关键字
			int iStruct=GetStructKeywordIndex(key);
			if(iStruct==-1) continue;
			int iStory=fin.GetInt();  //楼层号
			int id_conc=fin.GetInt();
			int id_rebar=fin.GetInt();
			int id_steel=fin.GetInt();
			theData.m_pStory[iStory].sConc[iStruct]=GetMatName(id_conc);
			theData.m_pStory[iStory].sRebar[iStruct]=GetMatName(id_rebar);
			theData.m_pStory[iStory].sSteel[iStruct]=GetMatName(id_steel);
			switch (g_StructKeyword[iStruct].iType)
			{
			case STRUCT_BEAM:
				theData.m_pStory[iStory].fPara[1][iStruct]=fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[2][iStruct]=fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[3][iStruct]=fin.GetFloat();
				theData.m_pStory[iStory].fPara[4][iStruct]=fin.GetFloat();
				break;
			case STRUCT_PILLAR:
				theData.m_pStory[iStory].fPara[9 ][iStruct]=fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[10][iStruct]=fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[11][iStruct]=fin.GetFloat();
				theData.m_pStory[iStory].fPara[12][iStruct]=fin.GetFloat();
				break;
			case STRUCT_BRACING:
				theData.m_pStory[iStory].fPara[9 ][iStruct]=fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[10][iStruct]=fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[11][iStruct]=fin.GetFloat();
				theData.m_pStory[iStory].fPara[12][iStruct]=fin.GetFloat();
				break;
			case STRUCT_PLATE:	
				theData.m_pStory[iStory].fPara[1][iStruct]=fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[2][iStruct]=fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[3][iStruct]=fin.GetFloat();
				theData.m_pStory[iStory].fPara[4][iStruct]=fin.GetFloat();
				break;
			case STRUCT_WALL:		
			case STRUCT_BEAMWALL:	
				theData.m_pStory[iStory].fPara[9 ][iStruct]=fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[10][iStruct]=fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[11][iStruct]=fin.GetFloat();
				theData.m_pStory[iStory].fPara[12][iStruct]=fin.GetFloat();
				break;
			default:
				theData.m_pStory[iStory].fPara[1][iStruct]=fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[2][iStruct]=fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[3][iStruct]=fin.GetFloat();
				theData.m_pStory[iStory].fPara[4][iStruct]=fin.GetFloat();
				break;
			}
		}
	}
	fin.Close();


	//读入模型数据
	bSuccess&=theData.m_cFrame.Read(theData.m_sPrjFile, theData.m_cPrjPara);
	if(bSuccess)
	{
		//读入网格
		theData.m_cMesh.ReadMeshBin(theData.m_nStory,theData.m_pStory);
		//生成结点到单元的索引
		theData.m_cMesh.CreateNode2Elm();
		theData.m_cMesh.CreateShellSubElm();		
	}
	AppendMsg(L"SSG模型读取成功！\r\n\r\n");


	AppendMsg(L"开始读取结果...\r\n");

	//读取动力分析节点位移
	CNodeFieldSet m_cDis;
	m_cDis.Clear();
	AppendMsg(L"加载动力分析结点位移文件...\r\n");
	fname = theData.GetFilePath(FILE_DISP_BIN, theData.m_cFrame.m_cLoad[0]->sCaseName); //直接写工况名称也可以
	BOOL ret=m_cDis.ReadBinNodeField_AllStep(fname,false); 
	if (!ret||m_cDis.GetStepNumber()<1)
	{
		AppendMsg(L"没找到结果文件！\r\n");
		m_cDis.Clear();
		return;
	}


	//遍历所有时步，求节点最大转角
	int nNode=theData.m_cMesh.m_nNode;
	float *fNodeThetaMaxX= new float[nNode];	//节点绝对值最大的转角，带正负号
	float *fNodeThetaMaxY= new float[nNode];	//节点绝对值最大的转角，带正负号
	float *fNodeThetaMaxZ= new float[nNode];	//节点绝对值最大的转角，带正负号	//注意三个方向的最大转角可能不是同时刻发生的
	memset(fNodeThetaMaxX,0,sizeof(float)*nNode);
	memset(fNodeThetaMaxY,0,sizeof(float)*nNode);
	memset(fNodeThetaMaxZ,0,sizeof(float)*nNode);
	int nStep = m_cDis.nMaxSteps;
	for(int iStep=0;iStep<nStep;iStep++) 
	{
		for (int iNode=0;iNode<nNode;iNode++)
		{
			Vector4 d;
			d.x=m_cDis.aFieldsPtr[iStep]->GetItemData(iNode,3,m_cDis.nItems);	//后三个分量是转角，前三个分量是平动位移
			d.y=m_cDis.aFieldsPtr[iStep]->GetItemData(iNode,4,m_cDis.nItems);
			d.z=m_cDis.aFieldsPtr[iStep]->GetItemData(iNode,5,m_cDis.nItems);
			if (abs(d.x)>abs(fNodeThetaMaxX[iNode])) fNodeThetaMaxX[iNode]=d.x;
			if (abs(d.y)>abs(fNodeThetaMaxY[iNode])) fNodeThetaMaxY[iNode]=d.y;
			if (abs(d.z)>abs(fNodeThetaMaxZ[iNode])) fNodeThetaMaxZ[iNode]=d.z;
		}
	}

	//求构件最大转角
	int nBeam=theData.m_cFrame.m_aBeam.GetCount();
	float *fThetaX1= new float[nBeam];	//构件左端转角
	float *fThetaX2= new float[nBeam];	//构件右端转角
	float *fThetaXMax= new float[nBeam];	//构件最大转角
	memset(fThetaX1,0,sizeof(float)*nBeam);
	memset(fThetaX2,0,sizeof(float)*nBeam);
	memset(fThetaXMax,0,sizeof(float)*nBeam);

	float *fThetaY1= new float[nBeam];	//构件左端转角
	float *fThetaY2= new float[nBeam];	//构件右端转角
	float *fThetaYMax= new float[nBeam];	//构件最大转角
	memset(fThetaY1,0,sizeof(float)*nBeam);
	memset(fThetaY2,0,sizeof(float)*nBeam);
	memset(fThetaYMax,0,sizeof(float)*nBeam);


	float *fThetaZ1= new float[nBeam];	//构件左端转角
	float *fThetaZ2= new float[nBeam];	//构件右端转角
	float *fThetaZMax= new float[nBeam];	//构件最大转角
	memset(fThetaZ1,0,sizeof(float)*nBeam);
	memset(fThetaZ2,0,sizeof(float)*nBeam);
	memset(fThetaZMax,0,sizeof(float)*nBeam);

	//遍历所有单元，找到构件最大转角
	for (int iEle=0;iEle<theData.m_cMesh.m_nBeam;iEle++)
	{
		int iEleId1=theData.m_cMesh.m_pBeam[iEle].VexIDM1;
		int iEleId2=theData.m_cMesh.m_pBeam[iEle].VexIDM2;
		CVertex &Vex1=theData.m_cMesh.m_pNode[iEleId1];	//梁单元起点
		CVertex &Vex2=theData.m_cMesh.m_pNode[iEleId2];

		int iBeamId=theData.m_cMesh.m_pBeam[iEle].BeamStrucIDM;
		CBeamStruc &beam=theData.m_cFrame.m_aBeam[iBeamId];	//梁单元所属的梁构件		
		CLine &line=theData.m_cFrame.m_aLine[beam.LineIDM]; //结构线		
		CVertex &v1=theData.m_cFrame.m_aVex[line.VexIDM1];	//端点坐标
		CVertex &v2=theData.m_cFrame.m_aVex[line.VexIDM2];

		if (Vex1==v1)
		{
			fThetaX1[iBeamId]=fNodeThetaMaxX[iEleId1];
			fThetaY1[iBeamId]=fNodeThetaMaxY[iEleId1];
			fThetaZ1[iBeamId]=fNodeThetaMaxZ[iEleId1];
		}
		else if (Vex1==v2)
		{
			fThetaX2[iBeamId]=fNodeThetaMaxX[iEleId1];
			fThetaY2[iBeamId]=fNodeThetaMaxY[iEleId1];
			fThetaZ2[iBeamId]=fNodeThetaMaxZ[iEleId1];
		}

		if (Vex2==v1)
		{
			fThetaX1[iBeamId]=fNodeThetaMaxX[iEleId2];
			fThetaY1[iBeamId]=fNodeThetaMaxY[iEleId2];
			fThetaZ1[iBeamId]=fNodeThetaMaxZ[iEleId2];
		}
		else if (Vex2==v2)
		{
			fThetaX2[iBeamId]=fNodeThetaMaxX[iEleId2];
			fThetaY2[iBeamId]=fNodeThetaMaxY[iEleId2];
			fThetaZ2[iBeamId]=fNodeThetaMaxZ[iEleId2];
		}

		if (abs(fNodeThetaMaxX[iEleId1])>abs(fThetaXMax[iBeamId])) fThetaXMax[iBeamId]=fNodeThetaMaxX[iEleId1];
		if (abs(fNodeThetaMaxY[iEleId1])>abs(fThetaYMax[iBeamId])) fThetaYMax[iBeamId]=fNodeThetaMaxY[iEleId1];
		if (abs(fNodeThetaMaxZ[iEleId1])>abs(fThetaZMax[iBeamId])) fThetaZMax[iBeamId]=fNodeThetaMaxZ[iEleId1];

		if (abs(fNodeThetaMaxX[iEleId2])>abs(fThetaXMax[iBeamId])) fThetaXMax[iBeamId]=fNodeThetaMaxX[iEleId2];
		if (abs(fNodeThetaMaxY[iEleId2])>abs(fThetaYMax[iBeamId])) fThetaYMax[iBeamId]=fNodeThetaMaxY[iEleId2];
		if (abs(fNodeThetaMaxZ[iEleId2])>abs(fThetaZMax[iBeamId])) fThetaZMax[iBeamId]=fNodeThetaMaxZ[iEleId2];
	}

	//输出转角文件
	AppendMsg(L"正在输出构件转角文件...\r\n");
	CASCFile fout;
	char buf[512];
	CString sOutFileName=theData.GetPrjPath()+theData.GetPrjName()+L"Theta.txt";
	if (!fout.Open(sOutFileName,CFile::modeCreate|CFile::modeWrite|CFile::shareDenyWrite))return;
	USES_CONVERSION;

	sprintf_s(buf,sizeof(buf),"**SAUSAGE一维构件转角\r\n");
	fout.Write(buf,strlen(buf));

	sprintf_s(buf,sizeof(buf),"*一维构件数目=%d\r\n",nBeam);
	fout.Write(buf,strlen(buf));

	sprintf_s(buf,sizeof(buf),"编号\t类型\t层号\t截面名称\t混凝土等级\t钢筋等级\t箍筋等级\t钢材等级\t起点转角θx\t起点转角θy\t起点转角θz\t\t终点转角θx\t终点转角θy\t终点转角θz\t\t最大转角θx\t最大转角θy\t最大转角θz\r\n");
	fout.Write(buf,strlen(buf));

	for (int iBeam=0;iBeam<nBeam;iBeam++)
	{
		CBeamStruc &beam=theData.m_cFrame.m_aBeam[iBeam];
		if(beam.iStatus==0) continue;	//被杀死的构件

		CString sType;	//构件类型		
		switch(beam.iStrucType)
		{
		case STRUCT_UNKNOWN 	: 
			sType=L"未知类型";
			break;			
		case STRUCT_BEAM    	:    
			sType=L"梁";
			break;
		case STRUCT_PILLAR  	:    
			sType=L"柱";
			break;
		case STRUCT_BRACING 	:    
			sType=L"斜撑";
			break;
		case STRUCT_EDGE  : 
			sType=L"边缘构件";
			break;
		case STRUCT_HIDEBEAM   : 
			sType=L"虚梁";
			break;
		case STRUCT_LONGIREBAR   : 
			sType=L"连梁纵筋";
			break;
		case STRUCT_LINK   : 
			sType=L"一般连接";
			break;			
		default:
			sType=L"未知类型";
			break;
		}
		int iStory=beam.idmStory;	//楼层
		//截面
		CBeamSection *psec=theData.m_cFrame.m_cSection.GetBeamSection(beam.iSectionID);
		//材料
		CString sConc=beam.ConcMat;
		CString sRebar=beam.RebarMat;
		CString sStirrup=beam.StirrupMat;
		CString sSteel=beam.SteelMat;


		sprintf_s(buf,sizeof(buf),"%d\t%s\t%d\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%g\t%g\t%g\t\t%g\t%g\t%g\t\t%g\t%g\t%g\t\r\n",
			iBeam+1,T2A(sType),iStory,T2A(psec->sName),T2A(sConc),T2A(sRebar),T2A(sStirrup),T2A(sSteel),
			fThetaX1[iBeam],fThetaY1[iBeam],fThetaZ1[iBeam],
			fThetaX2[iBeam],fThetaY2[iBeam],fThetaZ2[iBeam],
			fThetaXMax[iBeam],fThetaYMax[iBeam],fThetaZMax[iBeam]);
		fout.Write(buf,strlen(buf));


		/*
		//结构线
		CLine &line=theData.m_cFrame.m_aLine[beam.LineIDM];

		//端点坐标
		CVertex &v1=theData.m_cFrame.m_aVex[line.VexIDM1];
		CVertex &v2=theData.m_cFrame.m_aVex[line.VexIDM2];

		//截面
		CBeamSection *psec=theData.m_cFrame.m_cSection.GetBeamSection(beam.iSectionID);
		//寻找混凝土截面
		int nSec=psec->aSubSec.GetCount();
		int iSec=-1;
		for(int k=0;k<nSec;k++)
		{
		if(psec->aSubSec[k].iSubMatType==SUBSECTION_MAT_TYPE_CONC)
		{
		iSec=k;
		break;
		}
		}
		iSec=0;
		CSubSection &sub=psec->aSubSec[iSec];
		int iShape=sub.iShape;


		//局部坐标系
		Vector4 u,v,w;
		beam.LocalCoorVector(u,v,w);

		//转角
		float angle=beam.fRotateAng;

		//材料
		CString sSteel=beam.SteelMat;
		CString sConc=beam.ConcMat;
		CString sRebar=beam.RebarMat;
		int iMat=theData.m_cFrame.m_cMaterial.GetIndex(sConc);
		iMat=0;
		CMaterial &mat=theData.m_cFrame.m_cMaterial.aMaterial[iMat];

		*/
	}
	fout.Close();

	AppendMsg(L"构件转角文件输出成功！\r\n");

	CString msgfile=L"notepad.exe \"" + sOutFileName + CString(L"\"");
	WinExec(T2A(msgfile),SW_SHOW);


	/*
	//读取动力分析单元结果，如损伤、性能水平等
	CElmFieldOneComponent m_cElmFieldSet; 
	fname=theData.GetFilePath(sTypeName,m_sCaseFile,Sys_Group_All);
	if (!IsFileExists(fname))return;
	if(m_cElmFieldSet.pBlockCol){delete[] m_cElmFieldSet.pBlockCol;	m_cElmFieldSet.pBlockCol=NULL;}
	m_cElmFieldSet.nBlock=0;
	//读数据文件
	CF5Header  hdr;  //文件头
	CF5ElemBlock *pblock=NULL;  //分块数组
	BOOL ret=ReadF5Header(fname,hdr,pblock);
	if(!ret)return FALSE;
	int nBlock=hdr.GetElemTypeNum();  //总分块数
	m_cElmFieldSet.pBlockCol=new int[nBlock];
	for (int i=0;i<nBlock;i++)
	{
	m_cElmFieldSet.pBlockCol[i]=0;
	}
	ret=m_cElmFieldSet.ReadBinElmField_AllStep(fname,hdr,pblock,0);
	delete[] pblock;pblock=NULL;

	//引用结果，以读取最后一步结果为例，也可以 for(int j=0;j<fieldstep;j++) 
	int fieldstep=m_cElmFieldSet.nMaxSteps;  //物理场时间步数

	//梁单元
	for(int i=0;i<theData.m_cMesh.m_nBeam;i++)
	{
	int index=m_cElmFieldSet.pBeamIndex[i]; //ppData数组中的位置索引
	if(index==-1) continue;
	float v=m_cElmFieldSet.GetBeamData(fieldstep-1,i);

	}	

	//三角形单元
	for(int i=0;i<theData.m_cMesh.m_nTriangle;i++)
	{
	int index=m_cElmFieldSet.pTriIndex[i]; //ppData数组中的位置索引
	if(index==-1) continue;
	float v=m_cElmFieldSet.GetTriData(fieldstep-1,i);			
	}

	//四边形单元
	for(int i=0;i<theData.m_cMesh.m_nQuad;i++)
	{
	int index=m_cElmFieldSet.pQuadIndex[i]; //ppData数组中的位置索引
	if(index==-1) continue;
	float v=m_cElmFieldSet.GetQuadData(fieldstep-1,i);
	}
	*/


	theData.Clear();
}


void CReadSSGDlg::OnBnClickedButtonHelp()
{

	AfxMessageBox(L"SSGAPI，详细信息请关注“SAUSAGE非线性”！\r\n");
}

//统计层间位移角
void CReadSSGDlg::OnBnClickedButtonDisp()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	//获取位移角角度数据
	if (m_sAngle.IsEmpty()) return;

	vector <float> fVectorAngle;
	CStringArray strArr;
	SplitStr(m_sAngle, L",", strArr);

	for (int i = 0; i < strArr.GetSize(); i++)
	{
		fVectorAngle.push_back(_tstof(strArr.GetAt(i)));
	}
	strArr.RemoveAll();

	CString fname = L"";
	CString stitle = L"SAUSAGE文件|*.ssg||";
	CFileDialog dlg(TRUE, L"ssg", L"*.ssg", 0, stitle);
	if (dlg.DoModal() != IDOK) return;
	fname = dlg.GetPathName();

	//清除所有数据
	theData.Clear();
	theData.InitialAPI(); //2022版本修改
	theData.m_sPrjFile = fname;
	BOOL bSuccess = TRUE;

	DWORD tick0 = GetTickCount(), tick1;
	ClearMsg();
	AppendMsg(L"开始读入SSG模型数据...\r\n");

	//读入项目配置参数
	AppendMsg(L"读入*PROJECT ...\r\n");
	bSuccess &= theData.m_cPrjPara.Read(theData.m_sPrjFile);

	tick1 = GetTickCount();
	tick0 = tick1;

	//读入楼层数据
	CASCFile fin;
	if (!fin.Open(theData.m_sPrjFile, CFile::modeRead | CFile::shareDenyWrite)) return;
	tick1 = GetTickCount();
	tick0 = tick1;

	AppendMsg(L"读入*STORY ...\r\n");
	int count;
	if (fin.FindKey("*STORY"))
	{
		count = fin.GetKeyValueInt("NUMBER=");
		if (count > 0)
		{
			theData.m_nStory = count - 1;
			for (int i = 0; i <= theData.m_nStory; i++)
			{
				theData.m_pStory[i].Read(fin);
			}
		}
	}

	AppendMsg(L"读入*STYPROP ...\r\n");
	tick1 = GetTickCount();
	tick0 = tick1;

	if (fin.FindKey("*STYPROP"))  //楼层参数
	{
		fin.GetKeyValueInt("NPARA=");  //参数个数（列数），行数为楼层数（包括0层）
		fin.GetKeyValueInt("NSTRUCTTYPE=");  //构件种类
		int nrec = fin.GetKeyValueInt("NUMBER=");  //记录数
		for (int i = 0; i < nrec; i++)
		{
			CString key = fin.GetStr();  //结构类型关键字
			int iStruct = GetStructKeywordIndex(key);
			if (iStruct == -1) continue;
			int iStory = fin.GetInt();  //楼层号
			int id_conc = fin.GetInt();
			int id_rebar = fin.GetInt();
			int id_steel = fin.GetInt();
			theData.m_pStory[iStory].sConc[iStruct] = GetMatName(id_conc);
			theData.m_pStory[iStory].sRebar[iStruct] = GetMatName(id_rebar);
			theData.m_pStory[iStory].sSteel[iStruct] = GetMatName(id_steel);
			switch (g_StructKeyword[iStruct].iType)
			{
			case STRUCT_BEAM:
				theData.m_pStory[iStory].fPara[1][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[2][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[3][iStruct] = fin.GetFloat();
				theData.m_pStory[iStory].fPara[4][iStruct] = fin.GetFloat();
				break;
			case STRUCT_PILLAR:
				theData.m_pStory[iStory].fPara[9][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[10][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[11][iStruct] = fin.GetFloat();
				theData.m_pStory[iStory].fPara[12][iStruct] = fin.GetFloat();
				break;
			case STRUCT_BRACING:
				theData.m_pStory[iStory].fPara[9][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[10][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[11][iStruct] = fin.GetFloat();
				theData.m_pStory[iStory].fPara[12][iStruct] = fin.GetFloat();
				break;
			case STRUCT_PLATE:
				theData.m_pStory[iStory].fPara[1][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[2][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[3][iStruct] = fin.GetFloat();
				theData.m_pStory[iStory].fPara[4][iStruct] = fin.GetFloat();
				break;
			case STRUCT_WALL:
			case STRUCT_BEAMWALL:
				theData.m_pStory[iStory].fPara[9][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[10][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[11][iStruct] = fin.GetFloat();
				theData.m_pStory[iStory].fPara[12][iStruct] = fin.GetFloat();
				break;
			default:
				theData.m_pStory[iStory].fPara[1][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[2][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[3][iStruct] = fin.GetFloat();
				theData.m_pStory[iStory].fPara[4][iStruct] = fin.GetFloat();
				break;
			}
		}
	}
	fin.Close();


	//读入模型数据
	AppendMsg(L"读入构件数据 ...\r\n");
	bSuccess &= theData.m_cFrame.Read(theData.m_sPrjFile, theData.m_cPrjPara);

	if (bSuccess)
	{
		//读入网格
		tick1 = GetTickCount();
		tick0 = tick1;
		AppendMsg(L"读入单元数据 ...\r\n");
		theData.m_cMesh.ReadMeshBin(theData.m_nStory, theData.m_pStory);


		//生成结点到单元的索引
		tick1 = GetTickCount();
		tick0 = tick1;

		theData.m_cMesh.CreateNode2Elm();
		theData.m_cMesh.CreateShellSubElm();
	}
	AppendMsg(L"SSG模型读取成功！\r\n\r\n");

	//判断工况编号
	if (m_iCaseNum > theData.m_cFrame.m_cLoad.GetCount())
	{
		AfxMessageBox(L"工况定义错误！\r\n");
		return;
	}
	else
	{
		CString str;
		str.Format(L"读取*%s*工况结果\r\n", theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName);
		AppendMsg(str);
	}


	AppendMsg(L"开始读取结果...\r\n");

	//读取动力分析节点位移
	CNodeFieldSet m_cDis;
	m_cDis.Clear();
	AppendMsg(L"加载动力分析结点位移文件...\r\n");
	fname = theData.GetFilePath(FILE_DISP_BIN, theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName); //直接写工况名称也可以
	BOOL ret = m_cDis.ReadBinNodeField_AllStep(fname, false);
	if (!ret || m_cDis.GetStepNumber() < 1)
	{
		AppendMsg(L"没找到结果文件！\r\n");
		m_cDis.Clear();
		return;
	}


	//求节点位移
	int iNodeNum = 1000;
	int nStep = m_cDis.nMaxSteps;
	float *fNodeDispX = new float[nStep];
	memset(fNodeDispX, 0, sizeof(float)*nStep);

	for (int iStep = 0; iStep < nStep; iStep++)
	{
		Vector4 d;
		d.x = m_cDis.aFieldsPtr[iStep]->GetItemData(iNodeNum, 0, m_cDis.nItems);	//后三个分量是转角，前三个分量是平动位移
		d.y = m_cDis.aFieldsPtr[iStep]->GetItemData(iNodeNum, 1, m_cDis.nItems);
		d.z = m_cDis.aFieldsPtr[iStep]->GetItemData(iNodeNum, 2, m_cDis.nItems);
		fNodeDispX[iStep] = d.x;
	}

	//读取DEF文件
	AppendMsg(L"开始读取DEF文件...\r\n");
	//CString defname = theData.GetPrjPath() + theData.GetPrjName() + CString("_") + sGroup + CString(".") + FILE_OUTPUT_DEF;
	CString defname = theData.GetPrjPath() + theData.GetPrjName() + CString("_") + CString("All") + CString(".") + FILE_OUTPUT_DEF;
	int *story_pillar_node = NULL;
	int nstory1 = theData.m_nStory + 1;

	int npillar = 0;
	int nstory = 0;
	if (fin.Open(defname, CFile::modeRead | CFile::shareDenyWrite))
	{
		nstory = fin.GetInt() ;//层数
		//ASSERT(nstory == theData.m_nStory);
		npillar = fin.GetInt();
		for (int i = 0; i < npillar; i++)
		{
			fin.GetInt();
		}

		story_pillar_node = new int[nstory1 * npillar];
		for (int i = 0; i < nstory; i++)
		{
			int istory = fin.GetInt();
			for (int j = 0; j < npillar; j++)
			{
				story_pillar_node[istory + j * nstory] = fin.GetInt() - 1;
			}
		}
		fin.Close();
	}
	AppendMsg(L"读取数据成功\r\n\r\n");

	float *fStoryDriftAll = new float[fVectorAngle.size()*nstory];
	memset(fStoryDriftAll, 0, sizeof(float)*(fVectorAngle.size()*nstory));

	AppendMsg(L"正在输出层间位移角文件...\r\n");

	for (int m = 0; m < fVectorAngle.size(); m++)
	{

		//计算任意角度层间位移角
		float fAngle0 = fVectorAngle[m];
		float fAngle = fAngle0 * 3.14 / 180;
		float *fNodeDriftX = new float[nstory * npillar];
		float *fNodeDriftY = new float[nstory * npillar];

		memset(fNodeDriftX, 0, sizeof(float)*(nstory * npillar));
		memset(fNodeDriftY, 0, sizeof(float)*(nstory * npillar));

		float *fStoryDriftX = new float[nstory];
		int *iMaxStoryDriftNode = new int[nstory];	//X向最大层间位移角对应节点号
		//float *fStoryDriftY = new float[nstory];
		memset(fStoryDriftX, 0, sizeof(float)*nstory);
		memset(iMaxStoryDriftNode, 0, sizeof(float)*nstory);
		//memset(fStoryDriftY, 0, sizeof(float)*nstory);

		for (int i = 1; i < nstory; i++)
		{
			for (int j = 0; j < npillar; j++)
			{
				int iNode0 = story_pillar_node[i - 1 + j * nstory];
				int iNode1 = story_pillar_node[i + j * nstory];

				if (iNode0 < 0 || iNode1 < 0) continue;

				float fHeight = theData.m_pStory[i].fHeight;


				float fDriftX = 0;
				float fDriftY = 0;
				for (int iStep = 0; iStep < nStep; iStep++)
				{
					Vector4 d0, d1;
					d0.x = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode0, 0, m_cDis.nItems);
					d0.y = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode0, 1, m_cDis.nItems);

					d1.x = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode1, 0, m_cDis.nItems);
					d1.y = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode1, 1, m_cDis.nItems);

					fDriftX = abs((d1.x*cos(fAngle) + d1.y*sin(fAngle)) - (d0.x*cos(fAngle) + d0.y*sin(fAngle))) / fHeight;
					fDriftY = abs((d1.x*sin(fAngle) - d1.y*cos(fAngle)) - (d0.x*sin(fAngle) - d0.y*cos(fAngle))) / fHeight;
					fNodeDriftX[i + j * nstory] = max(fNodeDriftX[i + j * nstory], fDriftX);
					fNodeDriftY[i + j * nstory] = max(fNodeDriftY[i + j * nstory], fDriftY);
				}
				//最大位移角包络
				if (fNodeDriftX[i + j * nstory] > fStoryDriftX[i])
				{
					iMaxStoryDriftNode[i] = iNode1 + 1;
					fStoryDriftX[i] = fNodeDriftX[i + j * nstory];
				}
				//fStoryDriftX[i] = max(fStoryDriftX[i], fNodeDriftX[i + j * nstory]);
				//fStoryDriftY[i] = max(fStoryDriftY[i], fNodeDriftY[i + j * nstory]);
			}

			fStoryDriftAll[m*nstory + i] = fStoryDriftX[i];
		}

		//输出位移角文件
		CASCFile fout;
		char buf[512];
		CString str;
		str.Format(_T("%0.0f"), fAngle0);
		CString sOutFileName = theData.GetEarthQuakePath(theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName) + theData.GetPrjName() + L"_Drift_" + str + L".txt";
		if (!fout.Open(sOutFileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))return;
		USES_CONVERSION;

		AppendMsg(str);
		AppendMsg(L"\r\n");

		sprintf_s(buf, sizeof(buf), "**SAUSAGE层间位移角\r\n");
		fout.Write(buf, strlen(buf));

		sprintf_s(buf, sizeof(buf), "层号\t%0.0f°\t\t节点号\r\n", fAngle0);
		fout.Write(buf, strlen(buf));

		for (int iStory = 0; iStory < nstory; iStory++)
		{
			sprintf_s(buf, sizeof(buf), "%3d\t%f\t1/%0.0f\t%6d\t\r\n",
				iStory, fStoryDriftX[iStory], 1.0 / fStoryDriftX[iStory], iMaxStoryDriftNode[iStory]);
			fout.Write(buf, strlen(buf));
		}
		fout.Close();

		CString msgfile = L"notepad.exe \"" + sOutFileName + CString(L"\"");
		if (m_bOpenTxt) WinExec(T2A(msgfile), SW_SHOW);
	}

	//输出所有层间位移角
	AppendMsg(L"正在输出所有方向层间位移角文件...\r\n");
	CASCFile fout;
	char buf[512];
	//int i = m_iCaseNum;
	//CString sss = theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName;
	CString sOutFileName = theData.GetEarthQuakePath(theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName) + theData.GetPrjName() + L"_Drift_All.txt";
	if (!fout.Open(sOutFileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))return;
	USES_CONVERSION;

	sprintf_s(buf, sizeof(buf), "**SAUSAGE层间位移角\r\n");
	fout.Write(buf, strlen(buf));

	sprintf_s(buf, sizeof(buf), "层号\t");
	fout.Write(buf, strlen(buf));

	for (int i = 0; i < fVectorAngle.size(); i++)
	{
		float fAngle0 = fVectorAngle[i];
		CString str;
		str.Format(_T("%0.0f"), fAngle0);

		sprintf_s(buf, sizeof(buf), "%0.0f°\t", fAngle0);
		fout.Write(buf, strlen(buf));
	}
	sprintf_s(buf, sizeof(buf), "\r\n");
	fout.Write(buf, strlen(buf));


	for (int iStory = 0; iStory < nstory; iStory++)
	{
		sprintf_s(buf, sizeof(buf), "%3d\t", iStory);
		fout.Write(buf, strlen(buf));
		for (int i = 0; i < fVectorAngle.size(); i++)
		{
			sprintf_s(buf, sizeof(buf), "%f\t", fStoryDriftAll[iStory + i * nstory]);
			fout.Write(buf, strlen(buf));
		}
		sprintf_s(buf, sizeof(buf), "\r\n");
		fout.Write(buf, strlen(buf));
	}
	fout.Close();

	AppendMsg(L"结构层间位移角输出成功！\r\n");

	CString msgfile = L"notepad.exe \"" + sOutFileName + CString(L"\"");
	WinExec(T2A(msgfile), SW_SHOW);


	theData.Clear();
}

//统计有害层间位移角
void CReadSSGDlg::OnBnClickedButtonHarmDisp()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	//获取位移角角度数据
	if (m_sAngle.IsEmpty()) return;

	vector <float> fVectorAngle;
	CStringArray strArr;
	SplitStr(m_sAngle, L",", strArr);

	for (int i = 0; i < strArr.GetSize(); i++)
	{
		fVectorAngle.push_back(_tstof(strArr.GetAt(i)));
	}
	strArr.RemoveAll();

	CString fname = L"";
	CString stitle = L"SAUSAGE文件|*.ssg||";
	CFileDialog dlg(TRUE, L"ssg", L"*.ssg", 0, stitle);
	if (dlg.DoModal() != IDOK) return;
	fname = dlg.GetPathName();

	//清除所有数据
	theData.Clear();
	theData.InitialAPI(); //2022版本修改
	theData.m_sPrjFile = fname;
	BOOL bSuccess = TRUE;

	DWORD tick0 = GetTickCount(), tick1;
	ClearMsg();
	AppendMsg(L"开始读入SSG模型数据...\r\n");

	//读入项目配置参数
	AppendMsg(L"读入*PROJECT ...\r\n");
	bSuccess &= theData.m_cPrjPara.Read(theData.m_sPrjFile);

	tick1 = GetTickCount();
	tick0 = tick1;

	//读入楼层数据
	CASCFile fin;
	if (!fin.Open(theData.m_sPrjFile, CFile::modeRead | CFile::shareDenyWrite)) return;
	tick1 = GetTickCount();
	tick0 = tick1;

	AppendMsg(L"读入*STORY ...\r\n");
	int count;
	if (fin.FindKey("*STORY"))
	{
		count = fin.GetKeyValueInt("NUMBER=");
		if (count > 0)
		{
			theData.m_nStory = count - 1;
			for (int i = 0; i <= theData.m_nStory; i++)
			{
				theData.m_pStory[i].Read(fin);
			}
		}
	}

	AppendMsg(L"读入*STYPROP ...\r\n");
	tick1 = GetTickCount();
	tick0 = tick1;

	if (fin.FindKey("*STYPROP"))  //楼层参数
	{
		fin.GetKeyValueInt("NPARA=");  //参数个数（列数），行数为楼层数（包括0层）
		fin.GetKeyValueInt("NSTRUCTTYPE=");  //构件种类
		int nrec = fin.GetKeyValueInt("NUMBER=");  //记录数
		for (int i = 0; i < nrec; i++)
		{
			CString key = fin.GetStr();  //结构类型关键字
			int iStruct = GetStructKeywordIndex(key);
			if (iStruct == -1) continue;
			int iStory = fin.GetInt();  //楼层号
			int id_conc = fin.GetInt();
			int id_rebar = fin.GetInt();
			int id_steel = fin.GetInt();
			theData.m_pStory[iStory].sConc[iStruct] = GetMatName(id_conc);
			theData.m_pStory[iStory].sRebar[iStruct] = GetMatName(id_rebar);
			theData.m_pStory[iStory].sSteel[iStruct] = GetMatName(id_steel);
			switch (g_StructKeyword[iStruct].iType)
			{
			case STRUCT_BEAM:
				theData.m_pStory[iStory].fPara[1][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[2][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[3][iStruct] = fin.GetFloat();
				theData.m_pStory[iStory].fPara[4][iStruct] = fin.GetFloat();
				break;
			case STRUCT_PILLAR:
				theData.m_pStory[iStory].fPara[9][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[10][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[11][iStruct] = fin.GetFloat();
				theData.m_pStory[iStory].fPara[12][iStruct] = fin.GetFloat();
				break;
			case STRUCT_BRACING:
				theData.m_pStory[iStory].fPara[9][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[10][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[11][iStruct] = fin.GetFloat();
				theData.m_pStory[iStory].fPara[12][iStruct] = fin.GetFloat();
				break;
			case STRUCT_PLATE:
				theData.m_pStory[iStory].fPara[1][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[2][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[3][iStruct] = fin.GetFloat();
				theData.m_pStory[iStory].fPara[4][iStruct] = fin.GetFloat();
				break;
			case STRUCT_WALL:
			case STRUCT_BEAMWALL:
				theData.m_pStory[iStory].fPara[9][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[10][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[11][iStruct] = fin.GetFloat();
				theData.m_pStory[iStory].fPara[12][iStruct] = fin.GetFloat();
				break;
			default:
				theData.m_pStory[iStory].fPara[1][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[2][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[3][iStruct] = fin.GetFloat();
				theData.m_pStory[iStory].fPara[4][iStruct] = fin.GetFloat();
				break;
			}
		}
	}
	fin.Close();


	//读入模型数据
	AppendMsg(L"读入构件数据 ...\r\n");
	bSuccess &= theData.m_cFrame.Read(theData.m_sPrjFile, theData.m_cPrjPara);

	if (bSuccess)
	{
		//读入网格
		tick1 = GetTickCount();
		tick0 = tick1;
		AppendMsg(L"读入单元数据 ...\r\n");
		theData.m_cMesh.ReadMeshBin(theData.m_nStory, theData.m_pStory);


		//生成结点到单元的索引
		tick1 = GetTickCount();
		tick0 = tick1;

		theData.m_cMesh.CreateNode2Elm();
		theData.m_cMesh.CreateShellSubElm();
	}
	AppendMsg(L"SSG模型读取成功！\r\n\r\n");

	//判断工况编号
	if (m_iCaseNum > theData.m_cFrame.m_cLoad.GetCount())
	{
		AfxMessageBox(L"工况定义错误！\r\n");
		return;
	}
	else
	{
		CString str;
		str.Format(L"读取*%s*工况结果\r\n", theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName);
		AppendMsg(str);
	}


	AppendMsg(L"开始读取结果...\r\n");

	//读取动力分析节点位移
	CNodeFieldSet m_cDis;
	m_cDis.Clear();
	AppendMsg(L"加载动力分析结点位移文件...\r\n");
	fname = theData.GetFilePath(FILE_DISP_BIN, theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName); //直接写工况名称也可以
	BOOL ret = m_cDis.ReadBinNodeField_AllStep(fname, false);
	if (!ret || m_cDis.GetStepNumber() < 1)
	{
		AppendMsg(L"没找到结果文件！\r\n");
		m_cDis.Clear();
		return;
	}


	//求节点位移
	int iNodeNum = 1000;
	int nStep = m_cDis.nMaxSteps;
	float *fNodeDispX = new float[nStep];
	memset(fNodeDispX, 0, sizeof(float)*nStep);

	for (int iStep = 0; iStep < nStep; iStep++)
	{
		Vector4 d;
		d.x = m_cDis.aFieldsPtr[iStep]->GetItemData(iNodeNum, 0, m_cDis.nItems);	//后三个分量是转角，前三个分量是平动位移
		d.y = m_cDis.aFieldsPtr[iStep]->GetItemData(iNodeNum, 1, m_cDis.nItems);
		d.z = m_cDis.aFieldsPtr[iStep]->GetItemData(iNodeNum, 2, m_cDis.nItems);
		fNodeDispX[iStep] = d.x;
	}

	//读取DEF文件
	AppendMsg(L"开始读取DEF文件...\r\n");
	//CString defname = theData.GetPrjPath() + theData.GetPrjName() + CString("_") + sGroup + CString(".") + FILE_OUTPUT_DEF;
	CString defname = theData.GetPrjPath() + theData.GetPrjName() + CString("_") + CString("All") + CString(".") + FILE_OUTPUT_DEF;
	int *story_pillar_node = NULL;
	int nstory1 = theData.m_nStory + 1;

	int npillar = 0;
	int nstory = 0;
	if (fin.Open(defname, CFile::modeRead | CFile::shareDenyWrite))
	{
		nstory = fin.GetInt();//层数
		//ASSERT(nstory == theData.m_nStory);
		npillar = fin.GetInt();
		for (int i = 0; i < npillar; i++)
		{
			fin.GetInt();
		}

		story_pillar_node = new int[nstory1 * npillar];
		for (int i = 0; i < nstory; i++)
		{
			int istory = fin.GetInt();
			for (int j = 0; j < npillar; j++)
			{
				story_pillar_node[istory + j * nstory] = fin.GetInt() - 1;
			}
		}
		fin.Close();
	}
	AppendMsg(L"读取数据成功\r\n\r\n");

	float *fStoryDriftAll = new float[fVectorAngle.size()*nstory];
	memset(fStoryDriftAll, 0, sizeof(float)*(fVectorAngle.size()*nstory));

	AppendMsg(L"正在输出层间位移角文件...\r\n");

	for (int m = 0; m < fVectorAngle.size(); m++)
	{

		//计算任意角度层间位移角
		float fAngle0 = fVectorAngle[m];
		float fAngle = fAngle0 * 3.14 / 180;
		float *fNodeDriftX = new float[nstory * npillar];
		float *fNodeDriftY = new float[nstory * npillar];

		memset(fNodeDriftX, 0, sizeof(float)*(nstory * npillar));
		memset(fNodeDriftY, 0, sizeof(float)*(nstory * npillar));

		float *fStoryDriftX = new float[nstory];	//X向层间位移角
		int *iMaxStoryDriftNode = new int[nstory];	//X向最大层间位移角对应节点号
		float *fStoryDriftY = new float[nstory];
		memset(fStoryDriftX, 0, sizeof(float)*nstory);
		memset(iMaxStoryDriftNode, 0, sizeof(float)*nstory);
		memset(fStoryDriftY, 0, sizeof(float)*nstory);

		for (int i = 1; i < nstory; i++)
		{
			for (int j = 0; j < npillar; j++)
			{
				int iNode_1 = -1;
				int iNode0 = story_pillar_node[i - 1 + j * nstory];
				int iNode1 = story_pillar_node[i + j * nstory];

				if (iNode0 < 0 || iNode1 < 0) continue;

				float fHeight0 = 1.0;
				float fHeight = theData.m_pStory[i].fHeight;

				if (i > 1)
				{
					iNode_1 = story_pillar_node[i - 2 + j * nstory];
					fHeight0 = theData.m_pStory[i - 1].fHeight;
					if (iNode_1 == -1)
					{
						iNode_1 = 0;
						fHeight0 = theData.m_pStory[i - 1].zTop;
						continue;
					}
				}

				if (iNode1 + 1 == 15048)
				{
					int a = 1;
				}

				float fDriftX = 0;
				float fDriftY = 0;
				for (int iStep = 0; iStep < nStep; iStep++)
				{
					Vector4 d_1, d0, d1, r0;
					float fDrift_1 = 0.0;

					d0.x = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode0, 0, m_cDis.nItems);
					d0.y = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode0, 1, m_cDis.nItems);

					d1.x = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode1, 0, m_cDis.nItems);
					d1.y = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode1, 1, m_cDis.nItems);

					if (iNode_1 > -1)
					{
						d_1.x = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode_1, 0, m_cDis.nItems);
						d_1.y = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode_1, 1, m_cDis.nItems);
						fDrift_1 = ((d0.x*cos(fAngle) + d0.y*sin(fAngle)) - (d_1.x*cos(fAngle) + d_1.y*sin(fAngle))) / fHeight0;
					}

					//fDriftX = abs(d1.x - d0.x - (d0.x - d_1.x) / fHeight0 * fHeight) / fHeight;
					//fDriftX = abs(((d1.x*cos(fAngle) + d1.y*sin(fAngle)) - (d0.x*cos(fAngle) + d0.y*sin(fAngle))) / fHeight - (r0.y*cos(fAngle) - r0.x*sin(fAngle)));

					fDriftX = abs(((d1.x*cos(fAngle) + d1.y*sin(fAngle)) - (d0.x*cos(fAngle) + d0.y*sin(fAngle))) / fHeight - fDrift_1);
					fNodeDriftX[i + j * nstory] = max(fNodeDriftX[i + j * nstory], fDriftX);
					//fNodeDriftY[i + j * nstory] = max(fNodeDriftY[i + j * nstory], fDriftY);
				}
				//最大位移角包络
				if (fNodeDriftX[i + j * nstory] > fStoryDriftX[i])
				{
					iMaxStoryDriftNode[i] = iNode1 + 1;
					fStoryDriftX[i] = fNodeDriftX[i + j * nstory];
				}
				//fStoryDriftX[i] = max(fStoryDriftX[i], fNodeDriftX[i + j * nstory]);
				//fStoryDriftY[i] = max(fStoryDriftY[i], fNodeDriftY[i + j * nstory]);
			}
			fStoryDriftAll[m*nstory + i] = fStoryDriftX[i];
		}

		//输出位移角文件
		CASCFile fout;
		char buf[512];
		CString str;
		str.Format(_T("%0.0f"), fAngle0);
		CString sOutFileName = theData.GetEarthQuakePath(theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName) + theData.GetPrjName() + L"_HARM0_Drift_" + str + L".txt";
		if (!fout.Open(sOutFileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))return;
		USES_CONVERSION;

		AppendMsg(str);
		AppendMsg(L"\r\n");

		sprintf_s(buf, sizeof(buf), "**SAUSAGE有害层间位移角\r\n");
		fout.Write(buf, strlen(buf));

		sprintf_s(buf, sizeof(buf), "层号\t%0.0f°\t\t节点号\r\n", fAngle0);
		fout.Write(buf, strlen(buf));

		for (int iStory = 0; iStory < nstory; iStory++)
		{
			sprintf_s(buf, sizeof(buf), "%3d\t%f\t1/%0.0f\t%6d\t\r\n",
				iStory, fStoryDriftX[iStory], 1.0 / fStoryDriftX[iStory], iMaxStoryDriftNode[iStory]);
			fout.Write(buf, strlen(buf));
		}
		fout.Close();

		CString msgfile = L"notepad.exe \"" + sOutFileName + CString(L"\"");
		if (m_bOpenTxt) WinExec(T2A(msgfile), SW_SHOW);
	}

	//输出所有层间位移角
	AppendMsg(L"正在输出所有方向有害层间位移角文件...\r\n");
	CASCFile fout;
	char buf[512];
	//int i = m_iCaseNum;
	//CString sss = theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName;
	CString sOutFileName = theData.GetEarthQuakePath(theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName) + theData.GetPrjName() + L"_HARM0_Drift_All.txt";
	if (!fout.Open(sOutFileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))return;
	USES_CONVERSION;

	sprintf_s(buf, sizeof(buf), "**SAUSAGE有害层间位移角\r\n");
	fout.Write(buf, strlen(buf));

	sprintf_s(buf, sizeof(buf), "层号\t");
	fout.Write(buf, strlen(buf));

	for (int i = 0; i < fVectorAngle.size(); i++)
	{
		float fAngle0 = fVectorAngle[i];
		CString str;
		str.Format(_T("%0.0f"), fAngle0);

		sprintf_s(buf, sizeof(buf), "%0.0f°\t", fAngle0);
		fout.Write(buf, strlen(buf));
	}
	sprintf_s(buf, sizeof(buf), "\r\n");
	fout.Write(buf, strlen(buf));


	for (int iStory = 0; iStory < nstory; iStory++)
	{
		sprintf_s(buf, sizeof(buf), "%3d\t", iStory);
		fout.Write(buf, strlen(buf));
		for (int i = 0; i < fVectorAngle.size(); i++)
		{
			sprintf_s(buf, sizeof(buf), "%f\t", fStoryDriftAll[iStory + i * nstory]);
			fout.Write(buf, strlen(buf));
		}
		sprintf_s(buf, sizeof(buf), "\r\n");
		fout.Write(buf, strlen(buf));
	}
	fout.Close();

	AppendMsg(L"结构层间位移角输出成功！\r\n");

	CString msgfile = L"notepad.exe \"" + sOutFileName + CString(L"\"");
	WinExec(T2A(msgfile), SW_SHOW);


	theData.Clear();
}

// 分割字符串
void CReadSSGDlg::SplitStr(CString strSrc, CString strGap, CStringArray &strResult)
{
	int nPos = strSrc.Find(strGap);
	CString strLeft = _T("");

	while (0 <= nPos)
	{
		strLeft = strSrc.Left(nPos);
		if (!strLeft.IsEmpty())
		{
			strResult.Add(strLeft);
		}

		strSrc = strSrc.Right(strSrc.GetLength() - nPos - strGap.GetLength());
		nPos = strSrc.Find(strGap);
	}

	if (!strSrc.IsEmpty())
	{
		strResult.Add(strSrc);
	}
}

void CReadSSGDlg::OnEnKillfocusEditNum()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_sAngle.Empty();
	float fAngle = 0.f;
	while (fAngle < 360.001)
	{
		CString str;
		str.Format(_T("%0.0f,"), fAngle);
		m_sAngle = m_sAngle + str;
		fAngle = fAngle + m_fAngleGap;
	}
	UpdateData(false);
}



// 20220830-辛业文
//文件路径
bool ProjectPath(CString& fname)
{
	//CString fname = L"";
	CString stitle = L"SAUSAGE文件|*.ssg||";
	CFileDialog dlg(TRUE, L"ssg", L"*.ssg", 0, stitle);
	if (dlg.DoModal() != IDOK) return false;
	fname = dlg.GetPathName();
	return 1;
}

// 读取模型
void ReadMyModel(CString& fname)
{
	//清除所有数据
	theData.Clear();
	theData.InitialAPI(); 
	theData.m_sPrjFile = fname;
	BOOL bSuccess = TRUE;

	//读入项目配置参数
	//AppendMsg(L"读入*PROJECT ...\r\n");
	bSuccess &= theData.m_cPrjPara.Read(theData.m_sPrjFile);

	//读入楼层数据
	CASCFile fin;
	if (!fin.Open(theData.m_sPrjFile, CFile::modeRead | CFile::shareDenyWrite)) return;

	//AppendMsg(L"读入*STORY ...\r\n");
	int count;
	if (fin.FindKey("*STORY"))
	{
		count = fin.GetKeyValueInt("NUMBER=");
		if (count > 0)
		{
			theData.m_nStory = count - 1;
			for (int i = 0; i <= theData.m_nStory; i++)
			{
				theData.m_pStory[i].Read(fin);
			}
		}
	}

	fin.Close();


	//读入模型数据
	//AppendMsg(L"读入构件数据 ...\r\n");
	bSuccess &= theData.m_cFrame.Read(theData.m_sPrjFile, theData.m_cPrjPara);

	if (bSuccess)
	{
		//读入网格
		//AppendMsg(L"读入单元数据 ...\r\n");
		theData.m_cMesh.ReadMeshBin(theData.m_nStory, theData.m_pStory);

		//生成结点到单元的索引
		theData.m_cMesh.CreateNode2Elm();
		theData.m_cMesh.CreateShellSubElm();
	}
	

}

BOOL AddForceUser1(const CString &fname,CF15Header &hdrRead, CF15StruBlock *pblock,float* pData, int nComp) 
{
	// 读入第一个时刻的数据，iType类单元的所有分块
	CStruFieldOneStepOneBlock *pStruFieldSet = new CStruFieldOneStepOneBlock[2]; // 一维构件和二维构件，总2块


	for(int i = 0; i <2; i++) // 分2块，一维构件和二维构件
	{
		if(!pStruFieldSet[i].ReadOneStepOneType(fname,hdrRead, pblock, 0, i))
		{
			for(int j = 0; j < i; j++)
			{
				pStruFieldSet[j].Clear();
			}
			delete[]pStruFieldSet;pStruFieldSet = NULL;
			return FALSE;
		}
	}

	int nBeam = 0; // 初始化
	int nPlate = 0;

	int *pBeam = NULL;
	int *pPlate = NULL;

	// 一维构件
	for (int i = 0; i < pStruFieldSet[0].nStrus; i++) // 一维构件的数量
	{
		int iStruId = -1;
		iStruId = pblock[0].pStruID[i]; // 获取构件的ID
		if(iStruId < 0  ||iStruId > theData.m_cFrame.m_aBeam.GetCount() ) continue;
		CBeamStruc *beam = &theData.m_cFrame.m_aBeam[iStruId];
		if(beam->iStrucType == STRUCT_BEAM || beam->iStrucType == STRUCT_LONGIREBAR)continue;  // 剔除框架梁和连梁纵筋

		// 20220929修改，考虑竖向的一维构件出现被打节点断的情况，统计底部柱子的剪力
		int iStory = beam->idmStory - 1;
		if(iStory < 0) continue;

		// 取构件端点id号
		int iVertex1 = theData.m_cFrame.m_aLine[beam->LineIDM].VexIDM1;
		int iVertex2 = theData.m_cFrame.m_aLine[beam->LineIDM].VexIDM2;

		// 判断构件是否是跨层点，如果是，则统计该构件
		if (theData.m_cFrame.m_aVex[iVertex1].IsCrossStory() && theData.m_cFrame.m_aVex[iVertex1].idmStory == iStory) 
		{
			nBeam++;
		}
		else if(theData.m_cFrame.m_aVex[iVertex2].IsCrossStory() && theData.m_cFrame.m_aVex[iVertex2].idmStory == iStory)
		{
			nBeam++;
		}
	}

	// 二维构件
	for (int i = 0; i < pStruFieldSet[1].nStrus; i++) // 二维构件统计不包括楼板，因构件内力文件中没有存储楼板的内力数据
	{
		int iStruId = -1;
		iStruId = pblock[1].pStruID[i];
		if(iStruId < 0  ||iStruId > theData.m_cFrame.m_aPlate.GetCount() ) continue;
		CPlateStruc *Plate  = &theData.m_cFrame.m_aPlate[iStruId];
		
		// 20220928修改辛业文，不考虑楼层底部有墙梁这种情况的统计（原因目前输出的楼层底部的墙梁构件内力只输出两端）
		if (Plate->iStrucType == STRUCT_WALL) 
		{
			if(Plate->iSubType == 0 ) // 如果是==0，为墙柱
			{
				int iStory = Plate->idmStory - 1;
				int cp4p[4]; // 二维构件4个结点有4个id
				Plate->GetCornerPoint(cp4p[0], cp4p[1], cp4p[2], cp4p[3]); // 返回四个角点ID，左下、右下、右上、左上
				CVertex V4[4] = {theData.m_cFrame.m_aVex[cp4p[0]], theData.m_cFrame.m_aVex[cp4p[1]], 
					theData.m_cFrame.m_aVex[cp4p[2]], theData.m_cFrame.m_aVex[cp4p[3]]};/// ???????????????????????????????


				//for (int j = 0; j < 4; j++)
				//{
				//	if (V4[j].idmStory < iStory) 
				//	{
				//		iStory = V4[j].idmStory;
				//	}
				//}

				if (iStory < 0) return 0;

				int k = 0;
				for (int j = 0; j < 4; j++)
				{
					if (V4[j].IsCrossStory() && V4[j].idmStory == iStory)
					{
						k++;				
					}	
				}

				if (k == 1 || k == 2)
				{
					nPlate++;
				}
				else if (k >= 3)
				{
					theData.WriteError(_CHS("错误：可能存在跨层的墙梁或者三点共线"));
				}
			}
		}

		// 20220923修改，不考虑楼层底部有墙梁这种情况的统计（原因目前输出的楼层底部的墙梁构件内力只输出两端）
		//	else if (Plate->iSubType == 1)
		//	{
		//		int iStory = Plate->idmStory - 1;
		//		int cp4p[4]; // 二维构件4个结点有4个id
		//		Plate->GetCornerPoint(cp4p[0], cp4p[1], cp4p[2], cp4p[3]); // 返回四个角点ID，左下、右下、右上、左上
		//		CVertex V4[4] = {theData.m_cFrame.m_aVex[cp4p[0]], theData.m_cFrame.m_aVex[cp4p[1]], 
		//			theData.m_cFrame.m_aVex[cp4p[2]], theData.m_cFrame.m_aVex[cp4p[3]]};

		//		for (int j = 0; j < 4; j++)
		//		{
		//			if (V4[j].idmStory < iStory) 
		//			{
		//				iStory = V4[j].idmStory;
		//			}
		//		}

		//		if (iStory < 0) return 0;

		//		int k = 0;
		//		for (int j = 0; j < 4; j++)
		//		{
		//			if (V4[j].IsCrossStory() && V4[j].idmStory == iStory)
		//			{
		//				k++;				
		//			}	
		//		}

		//		if (k == 1 || k == 2)
		//		{
		//			nPlate++;
		//		}
		//		else if (k >= 3)
		//		{
		//			theData.WriteError(_CHS("错误：可能存在跨层的墙梁或者三点共线"));
		//		}
		//	}
		//}
	}



	// 统计一维构件数
	int *BeamIndex = new int[nBeam];
	//统计二维构件数
	int *PlateIndex =  new int[nPlate];


	for (int itype = 0; itype < hdrRead.FileInfo.type_num; itype++)
	{
		if (CString(pblock[itype].pBlockName) == L"一维构件")
		{
			int m = 0;
			for (int i = 0; i < pStruFieldSet[0].nStrus; i++)
			{
				int iStruId = -1;
				iStruId = pblock[0].pStruID[i];
				if(iStruId < 0 ||iStruId > pStruFieldSet[0].nStrus ) continue;
				CBeamStruc *beam = &theData.m_cFrame.m_aBeam[iStruId];
				if (beam->iStrucType == STRUCT_BEAM || beam->iStrucType == STRUCT_LONGIREBAR)continue;

				// 20220929修改，考虑竖向的一维构件出现被打节点断的情况，统计底部柱子的剪力
				int iStory = beam->idmStory - 1;
				if(iStory < 0) continue;

				// 取构件端点id号
				int iVertex1 = theData.m_cFrame.m_aLine[beam->LineIDM].VexIDM1;
				int iVertex2 = theData.m_cFrame.m_aLine[beam->LineIDM].VexIDM2;

				// 判断构件是否是跨层点，如果是，则统计该构件
				if (theData.m_cFrame.m_aVex[iVertex1].IsCrossStory() && theData.m_cFrame.m_aVex[iVertex1].idmStory == iStory) 
				{
					BeamIndex[m++] = i;
				}
				else if(theData.m_cFrame.m_aVex[iVertex2].IsCrossStory() && theData.m_cFrame.m_aVex[iVertex2].idmStory == iStory)
				{
					BeamIndex[m++] = i;
				}

				// 取构件端点id号
				/*				int iVer1 = theData.m_cFrame.m_aLine[beam->LineIDM].VexIDM1;
				int iVer2 = theData.m_cFrame.m_aLine[beam->LineIDM].VexIDM2;
				CVertex V2[2] = {theData.m_cFrame.m_aVex[iVer1], theData.m_cFrame.m_aVex[iVer2]};
				for (int j = 0; j < 2; j++)
				{
				if (V2[j].IsCrossStory() && V2[j].idmStory == iStory)
				{
				BeamIndex[m++] = i;
				}			
				}*/		
			}
		}

		else if(CString(pblock[itype].pBlockName) == L"二维构件")
		{
			int m = 0;
			for (int i = 0; i < pStruFieldSet[1].nStrus; i++)
			{
				int iStruId = -1;
				iStruId = pblock[1].pStruID[i];
				if(iStruId < 0 ||iStruId > theData.m_cFrame.m_aPlate.GetCount()) continue;
				CPlateStruc *Plate  = &theData.m_cFrame.m_aPlate[iStruId];
				if (Plate->iStrucType ==  STRUCT_WALL)
				{
					if(Plate->iSubType == 0)
					{
						int iStory = Plate->idmStory - 1;
						int iCornerPoint[4]; // 构件4个角点的id
						Plate->GetCornerPoint(iCornerPoint[0], iCornerPoint[1], iCornerPoint[2], iCornerPoint[3]);
						CVertex V4[4] = {
							theData.m_cFrame.m_aVex[iCornerPoint[0]],
							theData.m_cFrame.m_aVex[iCornerPoint[1]],
							theData.m_cFrame.m_aVex[iCornerPoint[2]],
							theData.m_cFrame.m_aVex[iCornerPoint[3]]};

						if (iStory < 0) return 0;

						int k = 0;
						for (int j = 0; j < 4; j++)
						{
							if (V4[j].IsCrossStory() && V4[j].idmStory == iStory)
							{
								k++;				
							}	
						}
						if (k == 1 || k == 2)
						{
							PlateIndex[m++] = i;
						}
					}

					// 20220928修改辛业文，不考虑楼层底部有墙梁这种情况的统计（原因目前输出的楼层底部的墙梁构件内力只输出两端）
					//else if (Plate->iSubType == 1)
					//{
					//int iStory = Plate->idmStory - 1;
					//int iCornerPoint[4]; // 构件4个角点的id
					//Plate->GetCornerPoint(iCornerPoint[0], iCornerPoint[1], iCornerPoint[2], iCornerPoint[3]);
					//CVertex V4[4] = {
					//	theData.m_cFrame.m_aVex[iCornerPoint[0]],
					//	theData.m_cFrame.m_aVex[iCornerPoint[1]],
					//	theData.m_cFrame.m_aVex[iCornerPoint[2]],
					//	theData.m_cFrame.m_aVex[iCornerPoint[3]]};

					//	for (int j = 0; j < 4; j++)
					//	{
					//		if (V4[j].idmStory < iStory) 
					//		{
					//			iStory = V4[j].idmStory;
					//		}
					//	}

					//	if (iStory < 0) return 0;

					//	int k = 0;
					//	for (int j = 0; j < 4; j++)
					//	{
					//		if (V4[j].IsCrossStory() && V4[j].idmStory == iStory)
					//		{
					//			k++;				
					//		}	
					//	}
					//	if (k == 1 || k == 2)
					//	{
					//		PlateIndex[m++] = i;
					//	}			
				}
			}
		}			
	}

	int nOffset =0;
	int nstory1 = theData.m_nStory + 1;
	int nsteps  = pStruFieldSet[0].nMaxSteps; // 总时间步数

	for(int k = 0; k < nsteps; k++)
	{
		float *p = pData + k * nstory1 * nComp;
		// 按一维和二维构件进行剪力统计
		for(int itype = 0; itype < hdrRead.FileInfo.type_num; itype++)
		{	
			if(!pStruFieldSet[itype].ReadOneStepOneType(fname, hdrRead, pblock, k, itype))
				break;

			if( CString(pblock[itype].pBlockName) == L"一维构件")
			{
				int nBeamOffset = nOffset;
				for(int i = 0; i < nBeam; i++)
				{
					int m = BeamIndex[i];
					int iStruId = pblock[itype].pStruID[m];

					int iStroy = theData.m_cFrame.m_aBeam[iStruId].idmStory;
					int n =theData.m_nStory - iStroy;

					CBeamStruc &beam = theData.m_cFrame.m_aBeam[iStruId]; // m_aBeam: 梁和柱和斜撑的数值

					//if(beam.iStrucType == STRUCT_BEAM || beam.iStrucType == STRUCT_LONGIREBAR) continue;  // 剔除框架梁和连梁纵筋
					if(beam.iStrucType & STRUCT_ALL_PILLAR) // 非水平构件
					{
						if(beam.u.z < 0) // 局部坐标系相反
						{
							nBeamOffset = 6;
						}
					}

					Vector4 f0;
					f0.x = pStruFieldSet[itype].cData.GetItemData(BeamIndex[i],0 + nBeamOffset, pStruFieldSet[itype].nStrus);
					f0.y = pStruFieldSet[itype].cData.GetItemData(BeamIndex[i],1 + nBeamOffset, pStruFieldSet[itype].nStrus);
					f0.z = pStruFieldSet[itype].cData.GetItemData(BeamIndex[i],2 + nBeamOffset, pStruFieldSet[itype].nStrus);

					// 转换到整体坐标系下
					Vector4 u, v, w;

					u.x = beam.u.x;
					u.y = beam.v.x;
					u.z = beam.w.x;

					v.x = beam.u.y;
					v.y = beam.v.y;
					v.z = beam.w.y;

					w.x = beam.u.z;
					w.y = beam.v.z;
					w.z = beam.w.z;


					Vector4 f;
					f.x = Vector3Dotf(f0, u);
					f.y = Vector3Dotf(f0, v);
					f.z = Vector3Dotf(f0, w);

					if( beam.iStrucType == STRUCT_PILLAR ) // 柱子的统计
					{
						p[n + 0 * nstory1] += f.x;
						p[n + 9 * nstory1] += f.y;
					}
					else if(beam.iStrucType == STRUCT_BRACING) // 斜撑的统计
					{
						CLine &line = theData.m_cFrame.m_aLine[beam.LineIDM]; // 结构线数组
						if(line.Angle(theData.m_cFrame.m_aVex.GetData()) < Sys_MinBraceAngle * MATH_PI / 180.) // 角度小于20度统计为撑
						{
							p[n + 0 * nstory1] += f.x;
							p[n + 9 * nstory1] += f.y;
						}
						else // 角度大于20度统计为柱子 
						{
							p[n + 2 * nstory1] += f.x;
							p[n + 11 * nstory1] += f.y;
						}
					}
					else if(beam.iStrucType == STRUCT_LINK) // 一般连接的统计
					{
						p[n + 4 * nstory1] += f.x;
						p[n + 13 * nstory1] += f.y;

					}
					else if(beam.iStrucType == STRUCT_EDGE ) // 边缘构件的统计
					{
						p[n + 6 * nstory1] += f.x;
						p[n + 15 * nstory1] += f.y;
					}

					//楼层剪力Vx、Vy、Fz统计
					p[n + 8 * nstory1] += f.x;
					p[n + 17 * nstory1] += f.y;
					p[n + 18 * nstory1] += f.z;
				}
			}

			else if(CString(pblock[itype].pBlockName) == L"二维构件") 
			{
				for(int j = 0; j < nPlate; j++) // 只统计墙柱
				{
					int m = PlateIndex[j];
					int iStruId = pblock[itype].pStruID[m];

					CPlateStruc &Plate = theData.m_cFrame.m_aPlate[iStruId]; 
					int iStroy = theData.m_cFrame.m_aPlate[iStruId].idmStory;
					int n =theData.m_nStory - iStroy;

					Vector4 f0;
					f0.x = pStruFieldSet[itype].cData.GetItemData(PlateIndex[j],0+ nOffset , pStruFieldSet[itype].nStrus);
					f0.y = pStruFieldSet[itype].cData.GetItemData(PlateIndex[j],1+ nOffset , pStruFieldSet[itype].nStrus);
					f0.z = pStruFieldSet[itype].cData.GetItemData(PlateIndex[j],2+ nOffset , pStruFieldSet[itype].nStrus);


					//转换到整体坐标系
					Vector4 c0,u, v, w;

					u.x = Plate.u.x;
					u.y = Plate.v.x;
					u.z = Plate.w.x;

					v.x = Plate.u.y;
					v.y = Plate.v.y;
					v.z = Plate.w.y;

					w.x = Plate.u.z;
					w.y = Plate.v.z;
					w.z = Plate.w.z;

					Vector4 f;
					f.x = Vector3Dotf(f0, u); 
					f.y = Vector3Dotf(f0, v); 
					f.z = Vector3Dotf(f0, w); 


					// 墙的统计
					p[n + 6 * nstory1] += f.x;
					p[n + 15 * nstory1] += f.y;


					//楼层剪力Vx、Vy、Fz统计
					p[n + 8 * nstory1] += f.x;
					p[n + 17 * nstory1] += f.y;
					p[n + 18 * nstory1] += f.z;

				}
			}		
		}
	}

	for(int i = 0; i < hdrRead.FileInfo.type_num; i++)
	{
		pStruFieldSet[i].Clear();
	}

	// 释放内存
	if ( NULL != pStruFieldSet)
	{
		delete[] pStruFieldSet; pStruFieldSet = NULL;
	}
	else if (NULL != BeamIndex)
	{
		delete[] BeamIndex; BeamIndex = NULL;
	}
	else if (NULL != PlateIndex)
	{
		delete[] PlateIndex; PlateIndex = NULL;
	}

	return TRUE;

}

BOOL AddForceUser(const CString &fname,CF15Header &hdrRead, CF15StruBlock *pblock,float* pData, int nComp) 
{
	// 读入第一个时刻的数据，iType类单元的所有分块
	CStruFieldOneStepOneBlock *pStruFieldSet = new CStruFieldOneStepOneBlock[hdrRead.FileInfo.type_num]; // 一维构件和二维构件，总2块

	for(int i = 0; i < hdrRead.FileInfo.type_num; i++) // 分2块，一维构件和二维构件
	{
		if(!pStruFieldSet[i].ReadOneStepOneType(fname,hdrRead, pblock, 0, i))
		{
			for(int j = 0; j < i; j++)
			{
				pStruFieldSet[j].Clear();
			}
			delete[]pStruFieldSet;pStruFieldSet = NULL;
			return FALSE;
		}
	}

	// 定义一维构件和二维构件的数组
	int *BeamIndex;	// 一维构件
	int *PlateIndex; // 二维构件

	// 过滤掉不满足条件的构件（例如：水平构件框架梁等），将满足条件的一维构件（竖向构件）和二维构件（竖向构件）分别记录到BeamIndex和PlateIndex中
	for (int itype = 0; itype < hdrRead.FileInfo.type_num; itype++)
	{
		if (CString(pblock[itype].pBlockName) == L"一维构件")
		{
			BeamIndex = new int[pStruFieldSet[itype].nStrus];	// 一维构件数量（含框架梁、柱、斜撑、边缘构件、暗梁（虚梁）、连梁纵筋和一般连接）

			int m = 0;
			for (int i = 0; i < pStruFieldSet[itype].nStrus; i++)
			{
				BeamIndex[i] = -1;
				int iStruId = -1;
				iStruId = pblock[itype].pStruID[i]; // 获取构件的ID
				if(iStruId < 0 ||iStruId > pStruFieldSet[itype].nStrus ) continue;
				CBeamStruc *beam = &theData.m_cFrame.m_aBeam[iStruId];
				if (beam->iStrucType == STRUCT_BEAM || beam->iStrucType == STRUCT_LONGIREBAR)continue; // 剔除框架梁和连梁纵筋

				// 20220929修改，考虑竖向的一维构件（竖向构件）出现被节点分割为多段构件的情况
				int iStory = beam->idmStory - 1;
				if(iStory < 0) continue;

				int iVertex1 = theData.m_cFrame.m_aLine[beam->LineIDM].VexIDM1; // 取构件端点id号
				int iVertex2 = theData.m_cFrame.m_aLine[beam->LineIDM].VexIDM2; // 取构件端点id号

				// 判断构件节点是否是跨层点，如果是，则统计该构件
				if (theData.m_cFrame.m_aVex[iVertex1].IsCrossStory() && theData.m_cFrame.m_aVex[iVertex1].idmStory == iStory) 
				{
					BeamIndex[m++] = i;
				}
				else if(theData.m_cFrame.m_aVex[iVertex2].IsCrossStory() && theData.m_cFrame.m_aVex[iVertex2].idmStory == iStory)
				{
					BeamIndex[m++] = i;
				}
			}
		}

		else if(CString(pblock[itype].pBlockName) == L"二维构件")
		{
			PlateIndex =  new int[pStruFieldSet[itype].nStrus]; // 二维构件数量（只含有墙柱和墙梁，不包含楼板）

			int m = 0;
			for (int i = 0; i < pStruFieldSet[itype].nStrus; i++)
			{
				PlateIndex[i] = -1;
				int iStruId = -1;
				iStruId = pblock[itype].pStruID[i];
				if(iStruId < 0 ||iStruId > theData.m_cFrame.m_aPlate.GetCount()) continue;
				CPlateStruc *Plate  = &theData.m_cFrame.m_aPlate[iStruId];

				// 统计墙柱的数量
				if(Plate->iSubType == 0) // 子类型 0-墙柱，1-墙梁，
				{
					int iStory = Plate->idmStory - 1;
					if (iStory < 0) continue;
					int iCornerPoint[4]; // 墙柱有4个角点
					Plate->GetCornerPoint(iCornerPoint[0], iCornerPoint[1], iCornerPoint[2], iCornerPoint[3]); // 获取墙柱4个角点的id
					//CVertex V4[4] = {
					//	theData.m_cFrame.m_aVex[iCornerPoint[0]],
					//	theData.m_cFrame.m_aVex[iCornerPoint[1]],
					//	theData.m_cFrame.m_aVex[iCornerPoint[2]],
					//	theData.m_cFrame.m_aVex[iCornerPoint[3]]};

					//if (iStory < 0) return 0;

					//int k = 0;
					//for (int j = 0; j < 4; j++)
					//{
					//	if (V4[j].IsCrossStory() && V4[j].idmStory == iStory) // 墙柱的节点是否是跨层点
					//	{
					//		k++;				
					//	}	
					//}

					int k = 0;
					for (int j = 0; j < 4; j++)
					{
						if (theData.m_cFrame.m_aVex[iCornerPoint[j]].IsCrossStory() && 
							theData.m_cFrame.m_aVex[iCornerPoint[j]].idmStory == iStory) // 墙柱的节点是否是跨层点
						{
							k++;				
						}	
					}

					if (k == 1 || k == 2)
					{
						PlateIndex[m++] = i;
					}
				}

				// 20220928修改辛业文，不考虑楼层底部有墙梁这种情况的统计（原因目前输出的楼层底部的墙梁构件内力只输出两端）
				//else if (Plate->iSubType == 1)
				//{
				//int iStory = Plate->idmStory - 1;
				//int iCornerPoint[4]; // 构件4个角点的id
				//Plate->GetCornerPoint(iCornerPoint[0], iCornerPoint[1], iCornerPoint[2], iCornerPoint[3]);
				//CVertex V4[4] = {
				//	theData.m_cFrame.m_aVex[iCornerPoint[0]],
				//	theData.m_cFrame.m_aVex[iCornerPoint[1]],
				//	theData.m_cFrame.m_aVex[iCornerPoint[2]],
				//	theData.m_cFrame.m_aVex[iCornerPoint[3]]};

				//	if (iStory < 0) return 0;

				//	int k = 0;
				//	for (int j = 0; j < 4; j++)
				//	{
				//		if (V4[j].IsCrossStory() && V4[j].idmStory == iStory)
				//		{
				//			k++;				
				//		}	
				//	}
				//	if (k == 1 || k == 2)
				//	{
				//		PlateIndex[m++] = i;
				//	}			

			}
		}			
	}

	int nOffset =0;
	int nstory1 = theData.m_nStory + 1;
	int nsteps  = pStruFieldSet[0].nMaxSteps; // 总时间步数

	// 对一维构件和二维构件进行层间剪力统计
	for(int k = 0; k < nsteps; k++)
	{
		float *p = pData + k * nstory1 * nComp;

		for(int itype = 0; itype < hdrRead.FileInfo.type_num; itype++) // 按一维构件和二维构件统计
		{	
			if(!pStruFieldSet[itype].ReadOneStepOneType(fname, hdrRead, pblock, k, itype))
				break;

			if( CString(pblock[itype].pBlockName) == L"一维构件")
			{
				int nBeamOffset = nOffset;
				for(int i = 0; i < pStruFieldSet[itype].nStrus; i++)
				{
					if (BeamIndex[i] == -1) continue;					
					int m = BeamIndex[i];
					int iStruId = pblock[itype].pStruID[m]; // 获取构件的ID
					int iStroy = theData.m_cFrame.m_aBeam[iStruId].idmStory; // 获取构件的楼层号
					int n =theData.m_nStory - iStroy;

					CBeamStruc &beam = theData.m_cFrame.m_aBeam[iStruId]; 
					if(beam.iStrucType & STRUCT_ALL_PILLAR) // 非水平构件
					{
						if(beam.u.z < 0) // 局部坐标系相反
						{
							nBeamOffset = 6;
						}
					}

					Vector4 f0;
					f0.x = pStruFieldSet[itype].cData.GetItemData(BeamIndex[i],0 + nBeamOffset, pStruFieldSet[itype].nStrus); // 局部坐标系下的X向的力
					f0.y = pStruFieldSet[itype].cData.GetItemData(BeamIndex[i],1 + nBeamOffset, pStruFieldSet[itype].nStrus); // 局部坐标系下的Y向的力
					f0.z = pStruFieldSet[itype].cData.GetItemData(BeamIndex[i],2 + nBeamOffset, pStruFieldSet[itype].nStrus); // 局部坐标系下的Z向的力

					// 将局部坐标系转为整体坐标系
					Vector4 u, v, w;

					u.x = beam.u.x;
					u.y = beam.v.x;
					u.z = beam.w.x;

					v.x = beam.u.y;
					v.y = beam.v.y;
					v.z = beam.w.y;

					w.x = beam.u.z;
					w.y = beam.v.z;
					w.z = beam.w.z;


					Vector4 f;
					f.x = Vector3Dotf(f0, u); // 得到整体坐标系下的X向的力
					f.y = Vector3Dotf(f0, v); // 得到整体坐标系下的Y向的力
					f.z = Vector3Dotf(f0, w); // 得到整体坐标系下的Z向的力

					if( beam.iStrucType == STRUCT_PILLAR ) // 柱子的统计
					{
						p[n + 0 * nstory1] += f.x;
						p[n + 9 * nstory1] += f.y;
					}
					else if(beam.iStrucType == STRUCT_BRACING) // 斜撑的统计
					{
						CLine &line = theData.m_cFrame.m_aLine[beam.LineIDM]; // 结构线数组
						if(line.Angle(theData.m_cFrame.m_aVex.GetData()) < Sys_MinBraceAngle * MATH_PI / 180.) // 角度小于20度统计为撑
						{
							p[n + 0 * nstory1] += f.x;
							p[n + 9 * nstory1] += f.y;
						}
						else // 角度大于20度统计为柱子 
						{
							p[n + 2 * nstory1] += f.x;
							p[n + 11 * nstory1] += f.y;
						}
					}
					else if(beam.iStrucType == STRUCT_LINK) // 一般连接的统计
					{
						p[n + 4 * nstory1] += f.x;
						p[n + 13 * nstory1] += f.y;

					}
					else if(beam.iStrucType == STRUCT_EDGE ) // 边缘构件的统计
					{
						p[n + 6 * nstory1] += f.x;
						p[n + 15 * nstory1] += f.y;
					}

					//楼层剪力Vx、Vy、Fz统计
					p[n + 8 * nstory1] += f.x;
					p[n + 17 * nstory1] += f.y;
					p[n + 18 * nstory1] += f.z;
				}
			}

			else if(CString(pblock[itype].pBlockName) == L"二维构件") 
			{
				for(int j = 0; j < pStruFieldSet[itype].nStrus; j++) 
				{
					if (PlateIndex[j] == -1) continue; 

					int m = PlateIndex[j];
					int iStruId = pblock[itype].pStruID[m];

					CPlateStruc &Plate = theData.m_cFrame.m_aPlate[iStruId]; 
					int iStroy = theData.m_cFrame.m_aPlate[iStruId].idmStory;
					int n =theData.m_nStory - iStroy;

					Vector4 f0;
					f0.x = pStruFieldSet[itype].cData.GetItemData(PlateIndex[j],0+ nOffset , pStruFieldSet[itype].nStrus);
					f0.y = pStruFieldSet[itype].cData.GetItemData(PlateIndex[j],1+ nOffset , pStruFieldSet[itype].nStrus);
					f0.z = pStruFieldSet[itype].cData.GetItemData(PlateIndex[j],2+ nOffset , pStruFieldSet[itype].nStrus);


					//转换到整体坐标系
					Vector4 c0,u, v, w;

					u.x = Plate.u.x;
					u.y = Plate.v.x;
					u.z = Plate.w.x;

					v.x = Plate.u.y;
					v.y = Plate.v.y;
					v.z = Plate.w.y;

					w.x = Plate.u.z;
					w.y = Plate.v.z;
					w.z = Plate.w.z;

					Vector4 f;
					f.x = Vector3Dotf(f0, u); 
					f.y = Vector3Dotf(f0, v); 
					f.z = Vector3Dotf(f0, w); 


					// 墙的统计
					p[n + 6 * nstory1] += f.x;
					p[n + 15 * nstory1] += f.y;


					//楼层剪力Vx、Vy、Fz统计
					p[n + 8 * nstory1] += f.x;
					p[n + 17 * nstory1] += f.y;
					p[n + 18 * nstory1] += f.z;

				}
			}		
		}
	}

	for(int i = 0; i < hdrRead.FileInfo.type_num; i++)
	{
		pStruFieldSet[i].Clear();
	}

	// 释放内存
	if ( NULL != pStruFieldSet)
	{
		delete[] pStruFieldSet; pStruFieldSet = NULL;
	}
	else if (NULL != BeamIndex)
	{
		delete[] BeamIndex; BeamIndex = NULL;
	}
	else if (NULL != PlateIndex)
	{
		delete[] PlateIndex; PlateIndex = NULL;
	}

	return TRUE;

}

BOOL CalcStoryShearUser(CArray<int, int> &aRunCase,CLoadCollection &cLoads )
{
	if (aRunCase.GetCount() < 1) return FALSE;
	
	int nComp = 19; // sComp: 总共19个分量
	char *sTitle = _CHS("层间剪力", "Story Shear");
	char *sComp = _CHS("柱子Vx % 斜撑Vx % 一般连接Vx % 剪力墙Vx % 楼层剪力Vx 柱子Vy % 斜撑Vy % 一般连接Vy % 剪力墙Vy % 楼层剪力Vy Fz ");

	for (int iCase = 0; iCase < aRunCase.GetCount(); iCase++)
	{
		CString sLoadCase = cLoads[aRunCase[iCase]]->sCaseName;

		// 读取构件内力结果文件
		CString sInternalForceFName = theData.GetFilePath(FILE_STRU_FORCE_BIN,sLoadCase,L"All"); 

		if(!IsFileExists(sInternalForceFName)) continue;

		// 读取构件内力文件数据文件
		CF15Header hdrRead; // 文件头
		CF15StruBlock *pblockRead = NULL; // 分块数组
		hdrRead.Clear();

		if(!ReadF15Header(sInternalForceFName, hdrRead, pblockRead)) continue;

		int nsteps = hdrRead.FileInfo.ntimes; // 输出时刻的数量（行数的数量）
		if(nsteps < 1) continue;

		int nstory1 = theData.m_nStory + 1;
		float *pData = new float[nsteps * nstory1 * nComp];
		//for(int istory = 0; istory < nstory1; istory++)
		//{
		//	for(int icom = 0;icom < nComp; icom++)
		//	{
		//		for(int istep = 0; istep < nsteps; istep++)
		//		{
		//			pData[istory + icom * nstory1 + istep * nstory1 * nComp] = 0;
		//		}
		//	}
		//}
		for(int num = 0; num < nsteps * nstory1 * nComp; num++)
		{
			pData[num] = 0;
		}


		// 统计竖向构件的内力
		//AddForceUser1(sInternalForceFName, hdrRead, pblockRead, pData, nComp);
		AddForceUser(sInternalForceFName, hdrRead, pblockRead, pData, nComp);

		//CString sOutFileName = theData.GetFilePath(FILE_STORY_SHEAR_BIN,sLoadCase,L"User");


		//CString sOutFileName = L"E:\\辛业文\\工作\\01 Opensausg二次开发\\01 代码测试模型\\07 框剪结构-中南院\\ssg - 副本\\EarthQuakeResult\\RH2TG045_X\\" + theData.GetPrjName()+L"_All.SSH";

		CString sOutFileName = L"D:\\00 用户模型问题解答汇集\\08 华阳国际-林工\\ssg - 副本\\EarthQuakeResult\\RH4TG035_X\\" + theData.GetPrjName()+L"_All.SSH";


		//CString sOutFileName = L"E:\\辛业文\\工作\\01 Opensausg二次开发\\01 代码测试模型\\06 分析模型-SAUSAGE - 副本\\分析模型-SAUSAGE\\EarthQuakeResult\\RH3TG065_X\\" + theData.GetPrjName()+L"_All.SSH";

		// 写入和保存层间剪力文件

		CFile fout;
		if (fout.Open(sOutFileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))
		{
			float dt = hdrRead.FileInfo.dtime * hdrRead.FileInfo.dsteps; // dsteps:相邻时刻所间隔的步数。
			int neib = 1;

			fout.Write(&nComp, 4);
			fout.Write(sTitle, 256);
			fout.Write(sComp, 256);
			fout.Write(&dt, 4);
			fout.Write(&neib, 4);
			fout.Write(&nsteps, 4);
			fout.Write(&nstory1, 4);
			fout.Write(pData, nsteps * nstory1 * nComp * 4);
			fout.Close();
		}

		if (NULL != pData)
		{
			delete[] pData; pData = NULL;
		}
		else if (NULL != pblockRead)
		{
			delete[] pblockRead; pblockRead = NULL;
		}
	}

	return TRUE;
}



void CReadSSGDlg::OnBnClickedButton1()
{
	// 测试代码运行时间
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);


	//AfxMessageBox(L"用SSGAPI编写我的程序”！\r\n");
	CString fname;
	ProjectPath(fname);
	ReadMyModel(fname);

	//AppendMsg(L"SSG模型读取成功！\r\n\r\n");

	CLoadCollection *lc = theData.GetLoadCollecton();
	CArray<int, int> aRunCase;
	for (int i = 0; i < lc->GetCount(); i++)
	{
		aRunCase.Add(i);
	}
	
	AppendMsg(L"开始读取结果...\r\n");

	// 读取构件内力结果文件
	AppendMsg(L"读取动力分析构件内力文件...\r\n\r\n");

	// 统计自定义层间剪力
	CalcStoryShearUser(aRunCase, theData.m_cFrame.m_cLoad);


	AppendMsg(L"统计结果输出成功！\r\n");

	theData.Clear();

	QueryPerformanceCounter(&t2);
	double time = (double)(t2.QuadPart - t1.QuadPart)/(double)tc.QuadPart;
	AppendMsg(L"统计结果输出成功！\r\n");
}


void CReadSSGDlg::OnBnClickedButtonDispratio()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

	CString fname = L"";
	CString stitle = L"SAUSAGE文件|*.ssg||";
	CFileDialog dlg(TRUE, L"ssg", L"*.ssg", 0, stitle);
	if (dlg.DoModal() != IDOK) return;
	fname = dlg.GetPathName();

	//清除所有数据
	theData.Clear();
	theData.InitialAPI(); //2022版本修改
	theData.m_sPrjFile = fname;
	BOOL bSuccess = TRUE;

	DWORD tick0 = GetTickCount(), tick1;
	ClearMsg();
	AppendMsg(L"开始读入SSG模型数据...\r\n");

	//读入项目配置参数
	AppendMsg(L"读入*PROJECT ...\r\n");
	bSuccess &= theData.m_cPrjPara.Read(theData.m_sPrjFile);

	tick1 = GetTickCount();
	tick0 = tick1;

	//读入楼层数据
	CASCFile fin;
	if (!fin.Open(theData.m_sPrjFile, CFile::modeRead | CFile::shareDenyWrite)) return;
	tick1 = GetTickCount();
	tick0 = tick1;

	AppendMsg(L"读入*STORY ...\r\n");
	int count;
	if (fin.FindKey("*STORY"))
	{
		count = fin.GetKeyValueInt("NUMBER=");
		if (count > 0)
		{
			theData.m_nStory = count - 1;
			for (int i = 0; i <= theData.m_nStory; i++)
			{
				theData.m_pStory[i].Read(fin);
			}
		}
	}

	AppendMsg(L"读入*STYPROP ...\r\n");
	tick1 = GetTickCount();
	tick0 = tick1;

	if (fin.FindKey("*STYPROP"))  //楼层参数
	{
		fin.GetKeyValueInt("NPARA=");  //参数个数（列数），行数为楼层数（包括0层）
		fin.GetKeyValueInt("NSTRUCTTYPE=");  //构件种类
		int nrec = fin.GetKeyValueInt("NUMBER=");  //记录数
		for (int i = 0; i < nrec; i++)
		{
			CString key = fin.GetStr();  //结构类型关键字
			int iStruct = GetStructKeywordIndex(key);
			if (iStruct == -1) continue;
			int iStory = fin.GetInt();  //楼层号
			int id_conc = fin.GetInt();
			int id_rebar = fin.GetInt();
			int id_steel = fin.GetInt();
			theData.m_pStory[iStory].sConc[iStruct] = GetMatName(id_conc);
			theData.m_pStory[iStory].sRebar[iStruct] = GetMatName(id_rebar);
			theData.m_pStory[iStory].sSteel[iStruct] = GetMatName(id_steel);
			switch (g_StructKeyword[iStruct].iType)
			{
			case STRUCT_BEAM:
				theData.m_pStory[iStory].fPara[1][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[2][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[3][iStruct] = fin.GetFloat();
				theData.m_pStory[iStory].fPara[4][iStruct] = fin.GetFloat();
				break;
			case STRUCT_PILLAR:
				theData.m_pStory[iStory].fPara[9][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[10][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[11][iStruct] = fin.GetFloat();
				theData.m_pStory[iStory].fPara[12][iStruct] = fin.GetFloat();
				break;
			case STRUCT_BRACING:
				theData.m_pStory[iStory].fPara[9][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[10][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[11][iStruct] = fin.GetFloat();
				theData.m_pStory[iStory].fPara[12][iStruct] = fin.GetFloat();
				break;
			case STRUCT_PLATE:
				theData.m_pStory[iStory].fPara[1][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[2][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[3][iStruct] = fin.GetFloat();
				theData.m_pStory[iStory].fPara[4][iStruct] = fin.GetFloat();
				break;
			case STRUCT_WALL:
			case STRUCT_BEAMWALL:
				theData.m_pStory[iStory].fPara[9][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[10][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[11][iStruct] = fin.GetFloat();
				theData.m_pStory[iStory].fPara[12][iStruct] = fin.GetFloat();
				break;
			default:
				theData.m_pStory[iStory].fPara[1][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[2][iStruct] = fin.GetFloat()*100.0f;
				theData.m_pStory[iStory].fPara[3][iStruct] = fin.GetFloat();
				theData.m_pStory[iStory].fPara[4][iStruct] = fin.GetFloat();
				break;
			}
		}
	}
	fin.Close();


	//读入模型数据
	AppendMsg(L"读入构件数据 ...\r\n");
	bSuccess &= theData.m_cFrame.Read(theData.m_sPrjFile, theData.m_cPrjPara);

	if (bSuccess)
	{
		//读入网格
		tick1 = GetTickCount();
		tick0 = tick1;
		AppendMsg(L"读入单元数据 ...\r\n");
		theData.m_cMesh.ReadMeshBin(theData.m_nStory, theData.m_pStory);


		//生成结点到单元的索引
		tick1 = GetTickCount();
		tick0 = tick1;

		theData.m_cMesh.CreateNode2Elm();
		theData.m_cMesh.CreateShellSubElm();
	}
	AppendMsg(L"SSG模型读取成功！\r\n\r\n");

	//判断工况编号
	if (m_iCaseNum > theData.m_cFrame.m_cLoad.GetCount())
	{
		AfxMessageBox(L"工况定义错误！\r\n");
		return;
	}
	else
	{
		CString str;
		str.Format(L"读取*%s*工况结果\r\n", theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName);
		AppendMsg(str);
	}


	AppendMsg(L"开始读取结果...\r\n");

	//读取动力分析节点位移
	CNodeFieldSet m_cDis;
	m_cDis.Clear();
	AppendMsg(L"加载动力分析结点位移文件...\r\n");
	fname = theData.GetFilePath(FILE_DISP_BIN, theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName); //直接写工况名称也可以
	BOOL ret = m_cDis.ReadBinNodeField_AllStep(fname, false);
	if (!ret || m_cDis.GetStepNumber() < 1)
	{
		AppendMsg(L"没找到结果文件！\r\n");
		m_cDis.Clear();
		return;
	}

	//读取DEF文件
	AppendMsg(L"开始读取DEF文件...\r\n");
	//CString defname = theData.GetPrjPath() + theData.GetPrjName() + CString("_") + sGroup + CString(".") + FILE_OUTPUT_DEF;
	CString defname = theData.GetPrjPath() + theData.GetPrjName() + CString("_") + CString("All") + CString(".") + FILE_OUTPUT_DEF;
	int *story_pillar_node = NULL;
	int nstory1 = theData.m_nStory + 1;

	int npillar = 0;
	int nstory = 0;
	if (fin.Open(defname, CFile::modeRead | CFile::shareDenyWrite))
	{
		nstory = fin.GetInt();//层数
		//ASSERT(nstory == theData.m_nStory);
		npillar = fin.GetInt();
		for (int i = 0; i < npillar; i++)
		{
			fin.GetInt();
		}

		story_pillar_node = new int[nstory1 * npillar];
		for (int i = 0; i < nstory; i++)
		{
			int istory = fin.GetInt();
			for (int j = 0; j < npillar; j++)
			{
				story_pillar_node[istory + j * nstory] = fin.GetInt() - 1;
			}
		}
		fin.Close();
	}
	AppendMsg(L"读取数据成功\r\n\r\n");

	float *fDispMaxTH = new float[nstory];	//时程层位移最大值
	float *fDispMinTH = new float[nstory];	//时程层位移最小值
	memset(fDispMaxTH, 0, sizeof(float)*(nstory));
	memset(fDispMinTH, 0, sizeof(float)*(nstory));

	float **fDispMax; //层位移最大值
	fDispMax = new float *[nstory];

	int **iDispMax; //层位移最大值对应节点
	iDispMax = new int *[nstory];

	float **fDispAve; //层平均位移
	fDispAve = new float *[nstory];

	float **fRatio; //层位移比
	fRatio = new float *[nstory];

	int nStep = m_cDis.nMaxSteps;
	for (int i = 0; i < nstory; i++)
	{
		fDispMax[i] = new float[nStep];
		iDispMax[i] = new int[nStep];
		fDispAve[i] = new float[nStep];
		fRatio[i] = new float[nStep];

		memset(fDispMax[i], 0, sizeof(float)*(nStep));
		memset(iDispMax[i], 0, sizeof(int)*(nStep));
		memset(fDispAve[i], 0, sizeof(float)*(nStep));
		memset(fRatio[i], 0, sizeof(float)*(nStep));
	}

	AppendMsg(L"正在计算层位移...\r\n");

	CString sPath = theData.GetEarthQuakePath(theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName);
	CString sFileHs = sPath + theData.GetPrjName() + L"_DispHs.csv";
	string strFileHs = CT2A(sFileHs);
	FILE* fdHs = fopen(strFileHs.c_str(), "wb");
	fprintf(fdHs, "分析步,层号,最大位移,平均位移,位移比,节点号\n");

	for (int iStep = 0; iStep < nStep; iStep++)
	{
		for (int i = 1; i < nstory; i++)
		{
			float fRatio1 = 0.f;

			float fDispMax1 = 0.f;
			int iDispNodeID = 0;
			float fDispAve1 = 0.f;
			float fDispSum1 = 0.f;
			int nNum = 0;

			for (int j = 0; j < npillar; j++)
			{
				int iNode0 = story_pillar_node[i - 1 + j * nstory];
				int iNode1 = story_pillar_node[i + j * nstory];

				//if (iNode0 < 0 || iNode1 < 0) continue;
				if (iNode1 < 0) continue;

				//float fHeight = theData.m_pStory[i].fHeight;

				Vector4 d0, d1;
				d0.x = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode0, 0, m_cDis.nItems);
				d0.y = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode0, 1, m_cDis.nItems);

				d1.x = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode1, 0, m_cDis.nItems);
				d1.y = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode1, 1, m_cDis.nItems);

				if (abs(d1.x) > abs(fDispMax1))
				{
					fDispMax1 = d1.x;
					iDispNodeID = iNode1;
				}

				//fDispMax1 = max(fDispMax1, abs(d1.x));
				fDispSum1 += d1.x;
				nNum++;
			}

			if (fDispMax1 > fDispMaxTH[i])
			{
				fDispMaxTH[i] = fDispMax1;
			}
			else if (fDispMax1 < fDispMinTH[i])
			{
				fDispMinTH[i] = fDispMax1;
			}

			fDispAve1 = fDispSum1 / nNum;
			fRatio1 = fDispMax1 / fDispAve1;

			fDispMax[i][iStep] = fDispMax1;
			iDispMax[i][iStep] = iDispNodeID;
			fDispAve[i][iStep] = fDispAve1;
			fRatio[i][iStep] = fRatio1;

			fprintf(fdHs, "%6d,%4d,%10.8f,%10.8f,%10.8f,%5d\n", iStep, i, fDispMax1, fDispAve1, fRatio1, iDispNodeID);

		}

	}

	fclose(fdHs);

	AppendMsg(L"正在输出层位移...\r\n");

	//输出层位移数据
	float fError = m_fError;
	float* fRatio0 = new float[nstory];
	memset(fRatio0, 0, sizeof(float)*(nstory));

	CString sFileDisp = sPath + theData.GetPrjName() + L"_Disp.csv";
	string strFileDisp = CT2A(sFileDisp);
	FILE* fdDisp = fopen(strFileDisp.c_str(), "wb");
	fprintf(fdDisp, "层号,位移比\n");

	for (int i = 1; i < nstory; i++)
	{
		for (int j = 0; j < nStep; j++)
		{
			if (fDispMax[i][j] <= fError*fDispMaxTH[i] && fDispMax[i][j] >= fError*fDispMinTH[i]) continue;

			fRatio0[i] = max(fRatio0[i], fDispMax[i][j] / fDispAve[i][j]);
		}
		fprintf(fdDisp, "%d,%10.8f\n", i, fRatio0[i]);
	}

	fclose(fdDisp);

	CString msgfile = L"notepad.exe \"" + sFileDisp + CString(L"\"");
	if (m_bOpenTxt) WinExec(CT2A(msgfile), SW_SHOW);

	AppendMsg(L"结构层位移输出成功！\r\n");

	//delete[] fDispMax;
	//delete[] fDispAve;
	//delete[] fRatio;

	delete[] fDispMaxTH;
	delete[] fDispMinTH;
	for (int i = 0; i < nstory; i++)
	{
		delete[] fDispMax[i];
		delete[] iDispMax[i];
		delete[] fDispAve[i];
		delete[] fRatio[i];
	}
	delete[] fDispMax;
	delete[] iDispMax;
	delete[] fDispAve;
	delete[] fRatio;

	delete[] fRatio0;
	delete[] story_pillar_node;

	theData.Clear();

	return;
}


//void CReadSSGDlg::OnEnChangeEditAngle()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}
