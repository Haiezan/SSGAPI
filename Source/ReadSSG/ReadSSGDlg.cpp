
// ReadSSGDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ReadSSG.h"
#include "ReadSSGDlg.h"
#include "afxdialogex.h"
#include "..\Common\SSGData.h"
#include "..\Common\PostData.h"
#include "..\Common\CF5ElmFieldData.h"

#ifdef WIN64
#ifdef _DEBUG
#pragma comment(lib, "../../Lib/SSGAPI64_D.lib" )
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
	CString fname=L"";
	CString stitle=L"SAUSAGE文件|*.ssg||";
	CFileDialog dlg(TRUE,L"ssg",L"*.ssg",0,stitle);
	if(dlg.DoModal()!=IDOK) return;
	fname=dlg.GetPathName();

	//清除所有数据
	theData.Clear();
	theData.m_sPrjFile=fname;
	BOOL bSuccess=TRUE;

	DWORD tick0=GetTickCount(),tick1;	
	ClearMsg();
	AppendMsg(L"开始读入SSG模型数据...\r\n");

	//读入项目配置参数
	AppendMsg(L"读入*PROJECT ...\r\n");
	bSuccess&=theData.m_cPrjPara.Read(theData.m_sPrjFile);

	tick1=GetTickCount();
	tick0=tick1;

	//读入楼层数据
	CASCFile fin;
	if(!fin.Open(theData.m_sPrjFile,CFile::modeRead|CFile::shareDenyWrite)) return;
	tick1=GetTickCount();
	tick0=tick1;

	AppendMsg(L"读入*STORY ...\r\n");
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
	
	AppendMsg(L"读入*STYPROP ...\r\n");
	tick1=GetTickCount();
	tick0=tick1;

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
	AppendMsg(L"读入构件数据 ...\r\n");
	bSuccess&=theData.m_cFrame.Read(theData.m_sPrjFile, theData.m_cPrjPara);

	if(bSuccess)
	{
		//读入网格
		tick1=GetTickCount();
		tick0=tick1;
		AppendMsg(L"读入单元数据 ...\r\n");
		theData.m_cMesh.ReadMeshBin(theData.m_nStory,theData.m_pStory);


		//生成结点到单元的索引
		tick1=GetTickCount();
		tick0=tick1;

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

		if (fStoryDriftX) delete[] fStoryDriftX;
		if (iMaxStoryDriftNode) delete[] iMaxStoryDriftNode;
		if (fNodeDriftX) delete[] fNodeDriftX;
		if (fNodeDriftY) delete[] fNodeDriftY;

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

	
	if (fStoryDriftAll) delete[] fStoryDriftAll;
	if (story_pillar_node) delete[] story_pillar_node;
	if (fNodeDispX) delete[] fNodeDispX;

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

		if (fNodeDriftX) delete[] fNodeDriftX;
		if (fNodeDriftY) delete[] fNodeDriftY;
		if (fStoryDriftX) delete[] fStoryDriftX;
		if (iMaxStoryDriftNode) delete[] iMaxStoryDriftNode;
		if (fStoryDriftY) delete[]fStoryDriftY;

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

	if (fNodeDispX) delete[] fNodeDispX;
	if (story_pillar_node) delete[] story_pillar_node;
	if (fStoryDriftAll) delete[] fStoryDriftAll;


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


void CReadSSGDlg::OnBnClickedButton1()
{
	// 在此输入您的程序

	AfxMessageBox(L"用SSGAPI编写我的程序”！\r\n");

	return;
}
