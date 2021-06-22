// DlgReadDispRatio.cpp: 实现文件
//

#include "stdafx.h"
#include "ReadSSG.h"
#include "DlgReadDispRatio.h"
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

// CDlgReadDispRatio 对话框

IMPLEMENT_DYNAMIC(CDlgReadDispRatio, CDialogEx)

CDlgReadDispRatio::CDlgReadDispRatio(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DISPRATIO, pParent)
	, m_sMsg(_T(""))
	, m_iCaseNum(1)
	, m_bOpenTxt(TRUE)
	, m_fError(0.99f)
	, m_fAngle(0.f)
	, m_bMinusGra(FALSE)
{

}

CDlgReadDispRatio::~CDlgReadDispRatio()
{
}

void CDlgReadDispRatio::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sMsg);
	DDX_Text(pDX, IDC_EDIT_CASE, m_iCaseNum);
	DDX_Control(pDX, IDC_EDIT1, m_cEditMsg);
	DDX_Check(pDX, IDC_CHECK_OPENTXT, m_bOpenTxt);
	DDX_Text(pDX, IDC_EDIT_ERROR, m_fError);
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_fAngle);
	DDX_Check(pDX, IDC_CHECK_MINUSGRA, m_bMinusGra);
}


BEGIN_MESSAGE_MAP(CDlgReadDispRatio, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DISPRATIO, &CDlgReadDispRatio::OnBnClickedButtonDispratio)
END_MESSAGE_MAP()


// CDlgReadDispRatio 消息处理程序


void CDlgReadDispRatio::OnBnClickedButtonDispratio()
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

	float fAngle = m_fAngle * 3.14f / 180.f;

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

	//FILE* fd0 = fopen("TEST.csv", "wb");

	for (int iStep = 0; iStep < nStep; iStep++)
	{
		//fprintf(fd0, "%d,", iStep);
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
				//int iNode0 = story_pillar_node[i - 1 + j * nstory];
				int iNode1 = story_pillar_node[i + j * nstory];

				//if (iNode0 < 0 || iNode1 < 0) continue;
				if (iNode1 < 0) continue;

				//float fHeight = theData.m_pStory[i].fHeight;

				Vector4 d0, d1;
				//d0.x = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode0, 0, m_cDis.nItems);
				//d0.y = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode0, 1, m_cDis.nItems);

				//扣除静力位移
				float d0x = 0.f;
				float d0y = 0.f;
				if (m_bMinusGra)
				{
					d0x = m_cDis.aFieldsPtr[0]->GetItemData(iNode1, 0, m_cDis.nItems);
					d0y = m_cDis.aFieldsPtr[0]->GetItemData(iNode1, 1, m_cDis.nItems);
				}

				d1.x = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode1, 0, m_cDis.nItems) - d0x;
				d1.y = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode1, 1, m_cDis.nItems) - d0y;

				float fdisp = d1.x*cos(fAngle) + d1.y*sin(fAngle);

				if (abs(fdisp) > abs(fDispMax1))
				{
					fDispMax1 = fdisp;
					iDispNodeID = iNode1;
				}

				//fDispMax1 = max(fDispMax1, abs(d1.x));
				fDispSum1 += fdisp;
				nNum++;


				//if (i == 33)
				//{
				//	fprintf(fd0, "%10.8f,", fdisp);
				//}
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

			if (fDispAve1 > 1e-8)
			{
				fRatio1 = fDispMax1 / fDispAve1;
			}
			else
			{
				fRatio1 = 0.f;
			}
			

			fDispMax[i][iStep] = fDispMax1;
			iDispMax[i][iStep] = iDispNodeID;
			fDispAve[i][iStep] = fDispAve1;
			fRatio[i][iStep] = fRatio1;

			fprintf(fdHs, "%6d,%4d,%10.8f,%10.8f,%10.8f,%5d\n", iStep, i, fDispMax1, fDispAve1, fRatio1, iDispNodeID + 1);

		}
		//fprintf(fd0, "\n");
	}

	fclose(fdHs);

	//fclose(fd0);

	AppendMsg(L"正在输出层位移...\r\n");

	//输出层位移数据
	//各层最大位移数据
	float fError = m_fError;
	float* fRatio0 = new float[nstory];
	float* fDispMax0 = new float[nstory];
	int* iDispMaxID0 = new int[nstory];
	float* fDispAve0 = new float[nstory];
	memset(fRatio0, 0, sizeof(float)*(nstory));
	memset(fDispMax0, 0, sizeof(float)*(nstory));
	memset(iDispMaxID0, 0, sizeof(int)*(nstory));
	memset(fDispAve0, 0, sizeof(float)*(nstory));

	CString sFileDisp = sPath + theData.GetPrjName() + L"_Disp.csv";
	string strFileDisp = CT2A(sFileDisp);
	FILE* fdDisp = fopen(strFileDisp.c_str(), "wb");
	fprintf(fdDisp, "层号,最大位移,平均位移,位移比,节点号\n");

	for (int i = 1; i < nstory; i++)
	{
		for (int j = 0; j < nStep; j++)
		{
			if (abs(fDispMax[i][j]) > abs(fDispMax0[i]))
			{
				fDispMax0[i] = fDispMax[i][j];
				iDispMaxID0[i] = iDispMax[i][j];
			}
			if (abs(fDispAve[i][j]) > abs(fDispAve0[i]))
			{
				fDispAve0[i] = fDispAve[i][j];
			}

			if (fDispMax[i][j] <= fError * fDispMaxTH[i] && fDispMax[i][j] >= fError * fDispMinTH[i]) continue;

			fRatio0[i] = max(fRatio0[i], fDispMax[i][j] / fDispAve[i][j]);
		}
		fprintf(fdDisp, "%4d,%10.8f,%10.8f,%10.8f,%5d\n", i, fDispMax0[i], fDispAve0[i], fRatio0[i], iDispMaxID0[i] + 1);
	}

	fclose(fdDisp);

	CString msgfile1 = L"notepad.exe \"" + sFileHs + CString(L"\"");
	CString msgfile2 = L"notepad.exe \"" + sFileDisp + CString(L"\"");
	if (m_bOpenTxt) WinExec(CT2A(msgfile1), SW_SHOW);
	if (m_bOpenTxt) WinExec(CT2A(msgfile2), SW_SHOW);

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
	delete[] fDispMax0;
	delete[] iDispMaxID0;
	delete[] fDispAve0;
	delete[] story_pillar_node;

	theData.Clear();

	return;

}
void CDlgReadDispRatio::AppendMsg(CString sMsg)
{
	UpdateData();
	m_sMsg += L"\n" + sMsg;
	UpdateData(FALSE);
	UpdateWindow();//2016.5.19
	m_cEditMsg.LineScroll(m_cEditMsg.GetLineCount());
}
void CDlgReadDispRatio::ClearMsg()
{
	UpdateData();
	m_sMsg = L"";
	UpdateData(FALSE);
	UpdateWindow();//2016.5.19
}