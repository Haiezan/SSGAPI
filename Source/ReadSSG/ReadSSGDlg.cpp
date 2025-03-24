
// ReadSSGDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CReadSSGDlg �Ի���




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


// CReadSSGDlg ��Ϣ�������

BOOL CReadSSGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CReadSSGDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	CString stitle=L"SAUSAGE�ļ�|*.ssg||";
	CFileDialog dlg(TRUE,L"ssg",L"*.ssg",0,stitle);
	if(dlg.DoModal()!=IDOK) return;
	fname=dlg.GetPathName();

	//�����������
	theData.Clear();
	theData.m_sPrjFile=fname;
	BOOL bSuccess=TRUE;

	DWORD tick0=GetTickCount(),tick1;	
	ClearMsg();
	AppendMsg(L"��ʼ����SSGģ������...\r\n");

	//������Ŀ���ò���
	AppendMsg(L"����*PROJECT ...\r\n");
	bSuccess&=theData.m_cPrjPara.Read(theData.m_sPrjFile);

	tick1=GetTickCount();
	tick0=tick1;

	//����¥������
	CASCFile fin;
	if(!fin.Open(theData.m_sPrjFile,CFile::modeRead|CFile::shareDenyWrite)) return;
	tick1=GetTickCount();
	tick0=tick1;

	AppendMsg(L"����*STORY ...\r\n");
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
	
	AppendMsg(L"����*STYPROP ...\r\n");
	tick1=GetTickCount();
	tick0=tick1;

	if(fin.FindKey("*STYPROP"))  //¥�����
	{
		fin.GetKeyValueInt("NPARA=");  //����������������������Ϊ¥����������0�㣩
		fin.GetKeyValueInt("NSTRUCTTYPE=");  //��������
		int nrec=fin.GetKeyValueInt("NUMBER=");  //��¼��
		for(int i=0;i<nrec;i++)
		{
			CString key=fin.GetStr();  //�ṹ���͹ؼ���
			int iStruct=GetStructKeywordIndex(key);
			if(iStruct==-1) continue;
			int iStory=fin.GetInt();  //¥���
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


	//����ģ������
	AppendMsg(L"���빹������ ...\r\n");
	bSuccess&=theData.m_cFrame.Read(theData.m_sPrjFile, theData.m_cPrjPara);

	if(bSuccess)
	{
		//��������
		tick1=GetTickCount();
		tick0=tick1;
		AppendMsg(L"���뵥Ԫ���� ...\r\n");
		theData.m_cMesh.ReadMeshBin(theData.m_nStory,theData.m_pStory);


		//���ɽ�㵽��Ԫ������
		tick1=GetTickCount();
		tick0=tick1;

		theData.m_cMesh.CreateNode2Elm();
		theData.m_cMesh.CreateShellSubElm();		
	}
	AppendMsg(L"SSGģ�Ͷ�ȡ�ɹ���\r\n\r\n");


	AppendMsg(L"��ʼ��ȡ���...\r\n");

	//��ȡ���������ڵ�λ��
	CNodeFieldSet m_cDis;
	m_cDis.Clear();
	AppendMsg(L"���ض����������λ���ļ�...\r\n");
	fname = theData.GetFilePath(FILE_DISP_BIN, theData.m_cFrame.m_cLoad[0]->sCaseName); //ֱ��д��������Ҳ����
	BOOL ret=m_cDis.ReadBinNodeField_AllStep(fname,false); 
	if (!ret||m_cDis.GetStepNumber()<1)
	{
		AppendMsg(L"û�ҵ�����ļ���\r\n");
		m_cDis.Clear();
		return;
	}


	//��������ʱ������ڵ����ת��
	int nNode=theData.m_cMesh.m_nNode;
	float *fNodeThetaMaxX= new float[nNode];	//�ڵ����ֵ����ת�ǣ���������
	float *fNodeThetaMaxY= new float[nNode];	//�ڵ����ֵ����ת�ǣ���������
	float *fNodeThetaMaxZ= new float[nNode];	//�ڵ����ֵ����ת�ǣ���������	//ע��������������ת�ǿ��ܲ���ͬʱ�̷�����
	memset(fNodeThetaMaxX,0,sizeof(float)*nNode);
	memset(fNodeThetaMaxY,0,sizeof(float)*nNode);
	memset(fNodeThetaMaxZ,0,sizeof(float)*nNode);
	int nStep = m_cDis.nMaxSteps;
	for(int iStep=0;iStep<nStep;iStep++) 
	{
		for (int iNode=0;iNode<nNode;iNode++)
		{
			Vector4 d;
			d.x=m_cDis.aFieldsPtr[iStep]->GetItemData(iNode,3,m_cDis.nItems);	//������������ת�ǣ�ǰ����������ƽ��λ��
			d.y=m_cDis.aFieldsPtr[iStep]->GetItemData(iNode,4,m_cDis.nItems);
			d.z=m_cDis.aFieldsPtr[iStep]->GetItemData(iNode,5,m_cDis.nItems);
			if (abs(d.x)>abs(fNodeThetaMaxX[iNode])) fNodeThetaMaxX[iNode]=d.x;
			if (abs(d.y)>abs(fNodeThetaMaxY[iNode])) fNodeThetaMaxY[iNode]=d.y;
			if (abs(d.z)>abs(fNodeThetaMaxZ[iNode])) fNodeThetaMaxZ[iNode]=d.z;
		}
	}

	//�󹹼����ת��
	int nBeam=theData.m_cFrame.m_aBeam.GetCount();
	float *fThetaX1= new float[nBeam];	//�������ת��
	float *fThetaX2= new float[nBeam];	//�����Ҷ�ת��
	float *fThetaXMax= new float[nBeam];	//�������ת��
	memset(fThetaX1,0,sizeof(float)*nBeam);
	memset(fThetaX2,0,sizeof(float)*nBeam);
	memset(fThetaXMax,0,sizeof(float)*nBeam);

	float *fThetaY1= new float[nBeam];	//�������ת��
	float *fThetaY2= new float[nBeam];	//�����Ҷ�ת��
	float *fThetaYMax= new float[nBeam];	//�������ת��
	memset(fThetaY1,0,sizeof(float)*nBeam);
	memset(fThetaY2,0,sizeof(float)*nBeam);
	memset(fThetaYMax,0,sizeof(float)*nBeam);


	float *fThetaZ1= new float[nBeam];	//�������ת��
	float *fThetaZ2= new float[nBeam];	//�����Ҷ�ת��
	float *fThetaZMax= new float[nBeam];	//�������ת��
	memset(fThetaZ1,0,sizeof(float)*nBeam);
	memset(fThetaZ2,0,sizeof(float)*nBeam);
	memset(fThetaZMax,0,sizeof(float)*nBeam);

	//�������е�Ԫ���ҵ��������ת��
	for (int iEle=0;iEle<theData.m_cMesh.m_nBeam;iEle++)
	{
		int iEleId1=theData.m_cMesh.m_pBeam[iEle].VexIDM1;
		int iEleId2=theData.m_cMesh.m_pBeam[iEle].VexIDM2;
		CVertex &Vex1=theData.m_cMesh.m_pNode[iEleId1];	//����Ԫ���
		CVertex &Vex2=theData.m_cMesh.m_pNode[iEleId2];

		int iBeamId=theData.m_cMesh.m_pBeam[iEle].BeamStrucIDM;
		CBeamStruc &beam=theData.m_cFrame.m_aBeam[iBeamId];	//����Ԫ������������		
		CLine &line=theData.m_cFrame.m_aLine[beam.LineIDM]; //�ṹ��		
		CVertex &v1=theData.m_cFrame.m_aVex[line.VexIDM1];	//�˵�����
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

	//���ת���ļ�
	AppendMsg(L"�����������ת���ļ�...\r\n");
	CASCFile fout;
	char buf[512];
	CString sOutFileName=theData.GetPrjPath()+theData.GetPrjName()+L"Theta.txt";
	if (!fout.Open(sOutFileName,CFile::modeCreate|CFile::modeWrite|CFile::shareDenyWrite))return;
	USES_CONVERSION;

	sprintf_s(buf,sizeof(buf),"**SAUSAGEһά����ת��\r\n");
	fout.Write(buf,strlen(buf));

	sprintf_s(buf,sizeof(buf),"*һά������Ŀ=%d\r\n",nBeam);
	fout.Write(buf,strlen(buf));

	sprintf_s(buf,sizeof(buf),"���\t����\t���\t��������\t�������ȼ�\t�ֽ�ȼ�\t����ȼ�\t�ֲĵȼ�\t���ת�Ǧ�x\t���ת�Ǧ�y\t���ת�Ǧ�z\t\t�յ�ת�Ǧ�x\t�յ�ת�Ǧ�y\t�յ�ת�Ǧ�z\t\t���ת�Ǧ�x\t���ת�Ǧ�y\t���ת�Ǧ�z\r\n");
	fout.Write(buf,strlen(buf));

	for (int iBeam=0;iBeam<nBeam;iBeam++)
	{
		CBeamStruc &beam=theData.m_cFrame.m_aBeam[iBeam];
		if(beam.iStatus==0) continue;	//��ɱ���Ĺ���
		
		CString sType;	//��������		
		switch(beam.iStrucType)
		{
		case STRUCT_UNKNOWN 	: 
			sType=L"δ֪����";
			break;			
		case STRUCT_BEAM    	:    
			sType=L"��";
			break;
		case STRUCT_PILLAR  	:    
			sType=L"��";
			break;
		case STRUCT_BRACING 	:    
			sType=L"б��";
			break;
		case STRUCT_EDGE  : 
			sType=L"��Ե����";
			break;
		case STRUCT_HIDEBEAM   : 
			sType=L"����";
			break;
		case STRUCT_LONGIREBAR   : 
			sType=L"�����ݽ�";
			break;
		case STRUCT_LINK   : 
			sType=L"һ������";
			break;			
		default:
			sType=L"δ֪����";
			break;
		}
		int iStory=beam.idmStory;	//¥��
		//����
		CBeamSection *psec=theData.m_cFrame.m_cSection.GetBeamSection(beam.iSectionID);
		//����
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
		//�ṹ��
		CLine &line=theData.m_cFrame.m_aLine[beam.LineIDM];

		//�˵�����
		CVertex &v1=theData.m_cFrame.m_aVex[line.VexIDM1];
		CVertex &v2=theData.m_cFrame.m_aVex[line.VexIDM2];

		//����
		CBeamSection *psec=theData.m_cFrame.m_cSection.GetBeamSection(beam.iSectionID);
		//Ѱ�һ���������
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


 		//�ֲ�����ϵ
 		Vector4 u,v,w;
 		beam.LocalCoorVector(u,v,w);
 
 		//ת��
 		float angle=beam.fRotateAng;

		//����
		CString sSteel=beam.SteelMat;
		CString sConc=beam.ConcMat;
		CString sRebar=beam.RebarMat;
		int iMat=theData.m_cFrame.m_cMaterial.GetIndex(sConc);
		iMat=0;
		CMaterial &mat=theData.m_cFrame.m_cMaterial.aMaterial[iMat];

		*/
	}
	fout.Close();

	AppendMsg(L"����ת���ļ�����ɹ���\r\n");

	CString msgfile=L"notepad.exe \"" + sOutFileName + CString(L"\"");
	WinExec(T2A(msgfile),SW_SHOW);


	/*
	//��ȡ����������Ԫ����������ˡ�����ˮƽ��
	CElmFieldOneComponent m_cElmFieldSet; 
	fname=theData.GetFilePath(sTypeName,m_sCaseFile,Sys_Group_All);
	if (!IsFileExists(fname))return;
	if(m_cElmFieldSet.pBlockCol){delete[] m_cElmFieldSet.pBlockCol;	m_cElmFieldSet.pBlockCol=NULL;}
	m_cElmFieldSet.nBlock=0;
	//�������ļ�
	CF5Header  hdr;  //�ļ�ͷ
	CF5ElemBlock *pblock=NULL;  //�ֿ�����
	BOOL ret=ReadF5Header(fname,hdr,pblock);
	if(!ret)return FALSE;
	int nBlock=hdr.GetElemTypeNum();  //�ֿܷ���
	m_cElmFieldSet.pBlockCol=new int[nBlock];
	for (int i=0;i<nBlock;i++)
	{
		m_cElmFieldSet.pBlockCol[i]=0;
	}
	ret=m_cElmFieldSet.ReadBinElmField_AllStep(fname,hdr,pblock,0);
	delete[] pblock;pblock=NULL;

	//���ý�����Զ�ȡ���һ�����Ϊ����Ҳ���� for(int j=0;j<fieldstep;j++) 
	int fieldstep=m_cElmFieldSet.nMaxSteps;  //����ʱ�䲽��

	//����Ԫ
	for(int i=0;i<theData.m_cMesh.m_nBeam;i++)
	{
		int index=m_cElmFieldSet.pBeamIndex[i]; //ppData�����е�λ������
		if(index==-1) continue;
		float v=m_cElmFieldSet.GetBeamData(fieldstep-1,i);

	}	

	//�����ε�Ԫ
	for(int i=0;i<theData.m_cMesh.m_nTriangle;i++)
	{
		int index=m_cElmFieldSet.pTriIndex[i]; //ppData�����е�λ������
		if(index==-1) continue;
		float v=m_cElmFieldSet.GetTriData(fieldstep-1,i);			
	}

	//�ı��ε�Ԫ
	for(int i=0;i<theData.m_cMesh.m_nQuad;i++)
	{
		int index=m_cElmFieldSet.pQuadIndex[i]; //ppData�����е�λ������
		if(index==-1) continue;
		float v=m_cElmFieldSet.GetQuadData(fieldstep-1,i);
	}
	*/


	theData.Clear();
}


void CReadSSGDlg::OnBnClickedButtonHelp()
{
	
	AfxMessageBox(L"SSGAPI����ϸ��Ϣ���ע��SAUSAGE�����ԡ���\r\n");
}

//ͳ�Ʋ��λ�ƽ�
void CReadSSGDlg::OnBnClickedButtonDisp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	//��ȡλ�ƽǽǶ�����
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
	CString stitle = L"SAUSAGE�ļ�|*.ssg||";
	CFileDialog dlg(TRUE, L"ssg", L"*.ssg", 0, stitle);
	if (dlg.DoModal() != IDOK) return;
	fname = dlg.GetPathName();

	//�����������
	theData.Clear();
	theData.m_sPrjFile = fname;
	BOOL bSuccess = TRUE;

	DWORD tick0 = GetTickCount(), tick1;
	ClearMsg();
	AppendMsg(L"��ʼ����SSGģ������...\r\n");

	//������Ŀ���ò���
	AppendMsg(L"����*PROJECT ...\r\n");
	bSuccess &= theData.m_cPrjPara.Read(theData.m_sPrjFile);

	tick1 = GetTickCount();
	tick0 = tick1;

	//����¥������
	CASCFile fin;
	if (!fin.Open(theData.m_sPrjFile, CFile::modeRead | CFile::shareDenyWrite)) return;
	tick1 = GetTickCount();
	tick0 = tick1;

	AppendMsg(L"����*STORY ...\r\n");
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

	AppendMsg(L"����*STYPROP ...\r\n");
	tick1 = GetTickCount();
	tick0 = tick1;

	if (fin.FindKey("*STYPROP"))  //¥�����
	{
		fin.GetKeyValueInt("NPARA=");  //����������������������Ϊ¥����������0�㣩
		fin.GetKeyValueInt("NSTRUCTTYPE=");  //��������
		int nrec = fin.GetKeyValueInt("NUMBER=");  //��¼��
		for (int i = 0; i < nrec; i++)
		{
			CString key = fin.GetStr();  //�ṹ���͹ؼ���
			int iStruct = GetStructKeywordIndex(key);
			if (iStruct == -1) continue;
			int iStory = fin.GetInt();  //¥���
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


	//����ģ������
	AppendMsg(L"���빹������ ...\r\n");
	bSuccess &= theData.m_cFrame.Read(theData.m_sPrjFile, theData.m_cPrjPara);

	if (bSuccess)
	{
		//��������
		tick1 = GetTickCount();
		tick0 = tick1;
		AppendMsg(L"���뵥Ԫ���� ...\r\n");
		theData.m_cMesh.ReadMeshBin(theData.m_nStory, theData.m_pStory);


		//���ɽ�㵽��Ԫ������
		tick1 = GetTickCount();
		tick0 = tick1;

		theData.m_cMesh.CreateNode2Elm();
		theData.m_cMesh.CreateShellSubElm();
	}
	AppendMsg(L"SSGģ�Ͷ�ȡ�ɹ���\r\n\r\n");

	//�жϹ������
	if (m_iCaseNum > theData.m_cFrame.m_cLoad.GetCount())
	{
		AfxMessageBox(L"�����������\r\n");
		return;
	}
	else
	{
		CString str;
		str.Format(L"��ȡ*%s*�������\r\n", theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName);
		AppendMsg(str);
	}


	AppendMsg(L"��ʼ��ȡ���...\r\n");

	//��ȡ���������ڵ�λ��
	CNodeFieldSet m_cDis;
	m_cDis.Clear();
	AppendMsg(L"���ض����������λ���ļ�...\r\n");
	fname = theData.GetFilePath(FILE_DISP_BIN, theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName); //ֱ��д��������Ҳ����
	BOOL ret = m_cDis.ReadBinNodeField_AllStep(fname, false);
	if (!ret || m_cDis.GetStepNumber() < 1)
	{
		AppendMsg(L"û�ҵ�����ļ���\r\n");
		m_cDis.Clear();
		return;
	}


	//��ڵ�λ��
	int iNodeNum = 1000;
	int nStep = m_cDis.nMaxSteps;
	float *fNodeDispX = new float[nStep];
	memset(fNodeDispX, 0, sizeof(float)*nStep);

	for (int iStep = 0; iStep < nStep; iStep++)
	{
		Vector4 d;
		d.x = m_cDis.aFieldsPtr[iStep]->GetItemData(iNodeNum, 0, m_cDis.nItems);	//������������ת�ǣ�ǰ����������ƽ��λ��
		d.y = m_cDis.aFieldsPtr[iStep]->GetItemData(iNodeNum, 1, m_cDis.nItems);
		d.z = m_cDis.aFieldsPtr[iStep]->GetItemData(iNodeNum, 2, m_cDis.nItems);
		fNodeDispX[iStep] = d.x;
	}

	//��ȡDEF�ļ�
	AppendMsg(L"��ʼ��ȡDEF�ļ�...\r\n");
	//CString defname = theData.GetPrjPath() + theData.GetPrjName() + CString("_") + sGroup + CString(".") + FILE_OUTPUT_DEF;
	CString defname = theData.GetPrjPath() + theData.GetPrjName() + CString("_") + CString("All") + CString(".") + FILE_OUTPUT_DEF;
	int *story_pillar_node = NULL;
	int nstory1 = theData.m_nStory + 1;

	int npillar = 0;
	int nstory = 0;
	if (fin.Open(defname, CFile::modeRead | CFile::shareDenyWrite))
	{
		nstory = fin.GetInt() ;//����
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
	AppendMsg(L"��ȡ���ݳɹ�\r\n\r\n");

	float *fStoryDriftAll = new float[fVectorAngle.size()*nstory];
	memset(fStoryDriftAll, 0, sizeof(float)*(fVectorAngle.size()*nstory));

	AppendMsg(L"����������λ�ƽ��ļ�...\r\n");

	for (int m = 0; m < fVectorAngle.size(); m++)
	{

		//��������ǶȲ��λ�ƽ�
		float fAngle0 = fVectorAngle[m];
		float fAngle = fAngle0 * 3.14 / 180;
		float *fNodeDriftX = new float[nstory * npillar];
		float *fNodeDriftY = new float[nstory * npillar];

		memset(fNodeDriftX, 0, sizeof(float)*(nstory * npillar));
		memset(fNodeDriftY, 0, sizeof(float)*(nstory * npillar));

		float *fStoryDriftX = new float[nstory];
		int *iMaxStoryDriftNode = new int[nstory];	//X�������λ�ƽǶ�Ӧ�ڵ��
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
				//���λ�ƽǰ���
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

		//���λ�ƽ��ļ�
		CASCFile fout;
		char buf[512];
		CString str;
		str.Format(_T("%0.0f"), fAngle0);
		CString sOutFileName = theData.GetEarthQuakePath(theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName) + theData.GetPrjName() + L"_Drift_" + str + L".txt";
		if (!fout.Open(sOutFileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))return;
		USES_CONVERSION;

		AppendMsg(str);
		AppendMsg(L"\r\n");

		sprintf_s(buf, sizeof(buf), "**SAUSAGE���λ�ƽ�\r\n");
		fout.Write(buf, strlen(buf));

		sprintf_s(buf, sizeof(buf), "���\t%0.0f��\t\t�ڵ��\r\n", fAngle0);
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

	//������в��λ�ƽ�
	AppendMsg(L"����������з�����λ�ƽ��ļ�...\r\n");
	CASCFile fout;
	char buf[512];
	//int i = m_iCaseNum;
	//CString sss = theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName;
	CString sOutFileName = theData.GetEarthQuakePath(theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName) + theData.GetPrjName() + L"_Drift_All.txt";
	if (!fout.Open(sOutFileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))return;
	USES_CONVERSION;

	sprintf_s(buf, sizeof(buf), "**SAUSAGE���λ�ƽ�\r\n");
	fout.Write(buf, strlen(buf));

	sprintf_s(buf, sizeof(buf), "���\t");
	fout.Write(buf, strlen(buf));

	for (int i = 0; i < fVectorAngle.size(); i++)
	{
		float fAngle0 = fVectorAngle[i];
		CString str;
		str.Format(_T("%0.0f"), fAngle0);

		sprintf_s(buf, sizeof(buf), "%0.0f��\t", fAngle0);
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

	AppendMsg(L"�ṹ���λ�ƽ�����ɹ���\r\n");

	CString msgfile = L"notepad.exe \"" + sOutFileName + CString(L"\"");
	WinExec(T2A(msgfile), SW_SHOW);

	
	if (fStoryDriftAll) delete[] fStoryDriftAll;
	if (story_pillar_node) delete[] story_pillar_node;
	if (fNodeDispX) delete[] fNodeDispX;

	theData.Clear();
}

//ͳ���к����λ�ƽ�
void CReadSSGDlg::OnBnClickedButtonHarmDisp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	//��ȡλ�ƽǽǶ�����
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
	CString stitle = L"SAUSAGE�ļ�|*.ssg||";
	CFileDialog dlg(TRUE, L"ssg", L"*.ssg", 0, stitle);
	if (dlg.DoModal() != IDOK) return;
	fname = dlg.GetPathName();

	//�����������
	theData.Clear();
	theData.m_sPrjFile = fname;
	BOOL bSuccess = TRUE;

	DWORD tick0 = GetTickCount(), tick1;
	ClearMsg();
	AppendMsg(L"��ʼ����SSGģ������...\r\n");

	//������Ŀ���ò���
	AppendMsg(L"����*PROJECT ...\r\n");
	bSuccess &= theData.m_cPrjPara.Read(theData.m_sPrjFile);

	tick1 = GetTickCount();
	tick0 = tick1;

	//����¥������
	CASCFile fin;
	if (!fin.Open(theData.m_sPrjFile, CFile::modeRead | CFile::shareDenyWrite)) return;
	tick1 = GetTickCount();
	tick0 = tick1;

	AppendMsg(L"����*STORY ...\r\n");
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

	AppendMsg(L"����*STYPROP ...\r\n");
	tick1 = GetTickCount();
	tick0 = tick1;

	if (fin.FindKey("*STYPROP"))  //¥�����
	{
		fin.GetKeyValueInt("NPARA=");  //����������������������Ϊ¥����������0�㣩
		fin.GetKeyValueInt("NSTRUCTTYPE=");  //��������
		int nrec = fin.GetKeyValueInt("NUMBER=");  //��¼��
		for (int i = 0; i < nrec; i++)
		{
			CString key = fin.GetStr();  //�ṹ���͹ؼ���
			int iStruct = GetStructKeywordIndex(key);
			if (iStruct == -1) continue;
			int iStory = fin.GetInt();  //¥���
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


	//����ģ������
	AppendMsg(L"���빹������ ...\r\n");
	bSuccess &= theData.m_cFrame.Read(theData.m_sPrjFile, theData.m_cPrjPara);

	if (bSuccess)
	{
		//��������
		tick1 = GetTickCount();
		tick0 = tick1;
		AppendMsg(L"���뵥Ԫ���� ...\r\n");
		theData.m_cMesh.ReadMeshBin(theData.m_nStory, theData.m_pStory);


		//���ɽ�㵽��Ԫ������
		tick1 = GetTickCount();
		tick0 = tick1;

		theData.m_cMesh.CreateNode2Elm();
		theData.m_cMesh.CreateShellSubElm();
	}
	AppendMsg(L"SSGģ�Ͷ�ȡ�ɹ���\r\n\r\n");

	//�жϹ������
	if (m_iCaseNum > theData.m_cFrame.m_cLoad.GetCount())
	{
		AfxMessageBox(L"�����������\r\n");
		return;
	}
	else
	{
		CString str;
		str.Format(L"��ȡ*%s*�������\r\n", theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName);
		AppendMsg(str);
	}


	AppendMsg(L"��ʼ��ȡ���...\r\n");

	//��ȡ���������ڵ�λ��
	CNodeFieldSet m_cDis;
	m_cDis.Clear();
	AppendMsg(L"���ض����������λ���ļ�...\r\n");
	fname = theData.GetFilePath(FILE_DISP_BIN, theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName); //ֱ��д��������Ҳ����
	BOOL ret = m_cDis.ReadBinNodeField_AllStep(fname, false);
	if (!ret || m_cDis.GetStepNumber() < 1)
	{
		AppendMsg(L"û�ҵ�����ļ���\r\n");
		m_cDis.Clear();
		return;
	}


	//��ڵ�λ��
	int iNodeNum = 1000;
	int nStep = m_cDis.nMaxSteps;
	float *fNodeDispX = new float[nStep];
	memset(fNodeDispX, 0, sizeof(float)*nStep);

	for (int iStep = 0; iStep < nStep; iStep++)
	{
		Vector4 d;
		d.x = m_cDis.aFieldsPtr[iStep]->GetItemData(iNodeNum, 0, m_cDis.nItems);	//������������ת�ǣ�ǰ����������ƽ��λ��
		d.y = m_cDis.aFieldsPtr[iStep]->GetItemData(iNodeNum, 1, m_cDis.nItems);
		d.z = m_cDis.aFieldsPtr[iStep]->GetItemData(iNodeNum, 2, m_cDis.nItems);
		fNodeDispX[iStep] = d.x;
	}

	//��ȡDEF�ļ�
	AppendMsg(L"��ʼ��ȡDEF�ļ�...\r\n");
	//CString defname = theData.GetPrjPath() + theData.GetPrjName() + CString("_") + sGroup + CString(".") + FILE_OUTPUT_DEF;
	CString defname = theData.GetPrjPath() + theData.GetPrjName() + CString("_") + CString("All") + CString(".") + FILE_OUTPUT_DEF;
	int *story_pillar_node = NULL;
	int nstory1 = theData.m_nStory + 1;

	int npillar = 0;
	int nstory = 0;
	if (fin.Open(defname, CFile::modeRead | CFile::shareDenyWrite))
	{
		nstory = fin.GetInt();//����
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
	AppendMsg(L"��ȡ���ݳɹ�\r\n\r\n");

	float *fStoryDriftAll = new float[fVectorAngle.size()*nstory];
	memset(fStoryDriftAll, 0, sizeof(float)*(fVectorAngle.size()*nstory));

	AppendMsg(L"����������λ�ƽ��ļ�...\r\n");

	for (int m = 0; m < fVectorAngle.size(); m++)
	{

		//��������ǶȲ��λ�ƽ�
		float fAngle0 = fVectorAngle[m];
		float fAngle = fAngle0 * 3.14 / 180;
		float *fNodeDriftX = new float[nstory * npillar];
		float *fNodeDriftY = new float[nstory * npillar];

		memset(fNodeDriftX, 0, sizeof(float)*(nstory * npillar));
		memset(fNodeDriftY, 0, sizeof(float)*(nstory * npillar));

		float *fStoryDriftX = new float[nstory];	//X����λ�ƽ�
		int *iMaxStoryDriftNode = new int[nstory];	//X�������λ�ƽǶ�Ӧ�ڵ��
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
				//���λ�ƽǰ���
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

		//���λ�ƽ��ļ�
		CASCFile fout;
		char buf[512];
		CString str;
		str.Format(_T("%0.0f"), fAngle0);
		CString sOutFileName = theData.GetEarthQuakePath(theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName) + theData.GetPrjName() + L"_HARM0_Drift_" + str + L".txt";
		if (!fout.Open(sOutFileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))return;
		USES_CONVERSION;

		AppendMsg(str);
		AppendMsg(L"\r\n");

		sprintf_s(buf, sizeof(buf), "**SAUSAGE�к����λ�ƽ�\r\n");
		fout.Write(buf, strlen(buf));

		sprintf_s(buf, sizeof(buf), "���\t%0.0f��\t\t�ڵ��\r\n", fAngle0);
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

	//������в��λ�ƽ�
	AppendMsg(L"����������з����к����λ�ƽ��ļ�...\r\n");
	CASCFile fout;
	char buf[512];
	//int i = m_iCaseNum;
	//CString sss = theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName;
	CString sOutFileName = theData.GetEarthQuakePath(theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName) + theData.GetPrjName() + L"_HARM0_Drift_All.txt";
	if (!fout.Open(sOutFileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))return;
	USES_CONVERSION;

	sprintf_s(buf, sizeof(buf), "**SAUSAGE�к����λ�ƽ�\r\n");
	fout.Write(buf, strlen(buf));

	sprintf_s(buf, sizeof(buf), "���\t");
	fout.Write(buf, strlen(buf));

	for (int i = 0; i < fVectorAngle.size(); i++)
	{
		float fAngle0 = fVectorAngle[i];
		CString str;
		str.Format(_T("%0.0f"), fAngle0);

		sprintf_s(buf, sizeof(buf), "%0.0f��\t", fAngle0);
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


	AppendMsg(L"�ṹ���λ�ƽ�����ɹ���\r\n");

	CString msgfile = L"notepad.exe \"" + sOutFileName + CString(L"\"");
	WinExec(T2A(msgfile), SW_SHOW);


	theData.Clear();
}

// �ָ��ַ���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// �ڴ��������ĳ���

	AfxMessageBox(L"��SSGAPI��д�ҵĳ��򡱣�\r\n");

	return;
}
