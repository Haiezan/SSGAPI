# 概述

SSG-API可用于SAUSG系列软件模型的前后处理数据读取和编辑。

# 数据结构

## 模型数据

### CSSGData类

CSSGData类：包含模型所有信息
// 语法：class+定义的宏+类名{}

theData对象：全局变量

```C++
class _SSG_DLLIMPEXP  CSSGData 	//  class _SSG_DLLMPEXP CSSGData，编译的时候会展开成class _declspect(dllexport)
{
public:
	CSSGData();		// 构造函数，构造函数是一个和类同名的方法
	~CSSGData();	// 析构函数，析构函数也是以类占用作为函数名，和构造函数不一样的是，需要在函数名前面添加一个“~”符号
	void Clear(void);	// 清空
public:
	CProjectPara m_cPrjPara;
	CFrame m_cFrame; //结构造型数据,需要undo/redo的数据都尽量放在CFrame类中
	CMesh m_cMesh; //网格数据
	CStory m_pStory[Sys_Max_Stories]; //楼层数组，需要undo
	int m_nStory; //楼层数量
	MODEL_SOURCE m_iModelSource;  //模型来源

	vector<COMBO_STRUCT> m_vvCombGroup; //组合构件组
	CString m_sPrjFile;    //项目文件名
}
```

* 清除数据(运行API前执行)
```C++
theData.Clear();	// theData是CSSGData对象
```

# 模型信息

获取并修改建模信息。

## *.ssg模的路径


```C++
//获取AA.ssg模型路径
CString fname = _T("E:模型\\ssg\\AA.ssg"); // _T()将string字符串 转为CString字符串

```

## 读取*.ssg模型

```C++
void Read_My_Model(CString& fname)
{
	theData.m_sPrjFile = fname;
	bool bSuccess = TRUE;

	//读入项目配置参数
	printf("读入*PROJECT ...\r\n");
	bSuccess &= theData.m_cPrjPara.Read(theData.m_sPrjFile); // 读取项目总信息，储存于m_cPrjPara中
	//打开ssg文件
	CASCFile fin;
<<<<<<< HEAD
	if (!fin.Open(theData.m_sPrjFile, CFile::modeRead | CFile::shareDenyWrite)) 	// theData.m_sPrjFile：项目文件名
	{
		printf("fail to open the file");
		return ;//或者抛出异常。
	}

	printf("读入*STORY ...\r\n");
=======
	if (!fin.Open(theData.m_sPrjFile, CFile::modeRead | CFile::shareDenyWrite)) return;		// theData.m_sPrjFile：项目文件名
	//根据*STORY关键字读取楼层信息
>>>>>>> adaaef7ffc87aa90d9fa49e846a5b11440e97136
	int count;
	//根据*STORY关键字读取楼层信息	
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

	//根据*STYPROP关键字读取楼层参数
	printf("读入*STYPROP ...\r\n");
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

	// 获取构件信息
	printf("读入构件数据 ...\r\n");
	bSuccess &= theData.m_cFrame.Read(theData.m_sPrjFile, theData.m_cPrjPara); // 判断是否读取成功，成功为1，否则为0


	// 获取单元信息数据
	if (bSuccess)
		{
		//读入网格
		printf(L"读入单元数据 ...\r\n");
		theData.m_cMesh.ReadMeshBin(theData.m_nStory, theData.m_pStory); // 读取单元和坐标


		//生成结点到单元的索引
		theData.m_cMesh.CreateNode2Elm(); // 生成结点到单元的索引数组m_pNode2Elm，读入网格后以及生成网格后要调用
		theData.m_cMesh.CreateShellSubElm();  // 创建细分单元
		}
	printf("SSG模型读取成功！\n");

}
```

<<<<<<< HEAD
=======
## 构件信息

获取构件信息并进行修改。

```C++
AppendMsg(L"读入构件数据 ...\r\n");
bSuccess &= theData.m_cFrame.Read(theData.m_sPrjFile, theData.m_cPrjPara);  // 判断是否读取成功，成功为1，否则为0
```
## 单元信息

获取单元信息并进行数据处理。
```C++
if (bSuccess)
	{
	//读入网格
	tick1 = GetTickCount(); // GetTickCount(),用来计算某个操作所使用的的时间
	tick0 = tick1;
	AppendMsg(L"读入单元数据 ...\r\n");
	theData.m_cMesh.ReadMeshBin(theData.m_nStory, theData.m_pStory);  // 读取单元和坐标


	//生成结点到单元的索引
	tick1 = GetTickCount();
	tick0 = tick1;

	theData.m_cMesh.CreateNode2Elm();		// 生成结点到单元的索引数组m_pNode2Elm，读入网格后以及生成网格后要调用
	theData.m_cMesh.CreateShellSubElm();	 // 创建细分单元
	}
AppendMsg(L"SSG模型读取成功！\r\n\r\n");
```
>>>>>>> adaaef7ffc87aa90d9fa49e846a5b11440e97136

## 节点信息

获取单元节点信息并进行数据处理。
```C++
//读取动力分析节点位移
CNodeFieldSet m_cDis;  // 定义 CNodeFieldSet 类的一个对象m_cDis，节点位移数据
m_cDis.Clear();		// 清除
<<<<<<< HEAD
printf("加载动力分析结点位移文件...\r\n"); 
=======
AppendMsg(L"加载动力分析结点位移文件...\r\n"); 
>>>>>>> adaaef7ffc87aa90d9fa49e846a5b11440e97136
fname = theData.GetFilePath(FILE_DISP_BIN, theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName); //直接写工况名称也可以
BOOL ret = m_cDis.ReadBinNodeField_AllStep(fname, false);  // 读入二进制结点位移, TRUE时选择一个分量读取，FALSE时读取所有分量

if (!ret || m_cDis.GetStepNumber() < 1)
	{
<<<<<<< HEAD
	printf(L"没找到结果文件！\r\n");
=======
	AppendMsg(L"没找到结果文件！\r\n");
>>>>>>> adaaef7ffc87aa90d9fa49e846a5b11440e97136
	m_cDis.Clear();
	return;
	}
```

# 结果数据

获取计算结果数据并进行数据处理。

## 结构数据

获取关于结构的计算结果。

## 节点数据

获取节点计算结果。

### 节点位移
```C++
<<<<<<< HEAD
int iNodeNum = 1000;	
int nStep = m_cDis.nMaxSteps; // 文件中最大时间步数，读入文件时赋值
=======
int iNodeNum = 1000;	// 文件中最大时间步数，读入文件时赋值
int nStep = m_cDis.nMaxSteps;
>>>>>>> adaaef7ffc87aa90d9fa49e846a5b11440e97136
float *fNodeDispX = new float[nStep];
memset(fNodeDispX, 0, sizeof(float)*nStep);	// memset()：指在一段内存块中填充某一个给定的值，返回一个指向存储区 str 的指针。

for (int iStep = 0; iStep < nStep; iStep++)
{
	Vector4 d;
	d.x = m_cDis.aFieldsPtr[iStep]->GetItemData(iNodeNum, 0, m_cDis.nItems);	//后三个分量是转角，前三个分量是平动位移
	d.y = m_cDis.aFieldsPtr[iStep]->GetItemData(iNodeNum, 1, m_cDis.nItems);	// 同上 
	d.z = m_cDis.aFieldsPtr[iStep]->GetItemData(iNodeNum, 2, m_cDis.nItems);	// 同时
	fNodeDispX[iStep] = d.x;
}

<<<<<<< HEAD
//读取DEF文件，DEF文件中存的是模型的节点号
printf("开始读取DEF文件...\r\n");
CString defname = theData.GetPrjPath() + theData.GetPrjName() + CString("_") + CString("All") + CString(".") + FILE_OUTPUT_DEF;	// DEF的文件路径
=======
//读取DEF文件
AppendMsg(L"开始读取DEF文件...\r\n");
//CString defname = theData.GetPrjPath() + theData.GetPrjName() + CString("_") + sGroup + CString(".") + FILE_OUTPUT_DEF;
CString defname = theData.GetPrjPath() + theData.GetPrjName() + CString("_") + CString("All") + CString(".") + FILE_OUTPUT_DEF;	// 文件的路径
>>>>>>> adaaef7ffc87aa90d9fa49e846a5b11440e97136
int *story_pillar_node = NULL;
int nstory1 = theData.m_nStory + 1;

int npillar = 0;
int nstory = 0;
if (fin.Open(defname, CFile::modeRead | CFile::shareDenyWrite))	// 打开DEF文件
{
	nstory = fin.GetInt() ;	// 模型的层数，读DEF文件的第一行数据
<<<<<<< HEAD

=======
	//ASSERT(nstory == theData.m_nStory);
>>>>>>> adaaef7ffc87aa90d9fa49e846a5b11440e97136
	npillar = fin.GetInt();	// 支柱的数量，读DEF文件的第二行数据
	for (int i = 0; i < npillar; i++)	// 这循环的目的是跳过DEF文件中的第三行的数据
	{
		fin.GetInt();
	}

	story_pillar_node = new int[nstory1 * npillar];	// 创建一个有nstory1 * npillar个元素动态整型数组
	for (int i = 0; i < nstory; i++)
	{
		int istory = fin.GetInt();
		for (int j = 0; j < npillar; j++)
		{
			story_pillar_node[istory + j * nstory] = fin.GetInt() - 1;	// 将DEF文件中的节点号读进来
		}
	}
	fin.Close();
}
<<<<<<< HEAD

printf("读取数据成功\r\n\r\n");

=======
AppendMsg(L"读取数据成功\r\n\r\n");

float *fStoryDriftAll = new float[fVectorAngle.size()*nstory];
memset(fStoryDriftAll, 0, sizeof(float)*(fVectorAngle.size()*nstory));	// memset()：指在一段内存块中填充某一个给定的值0，返回一个指向存储区 str 的指针。

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

			if (iNode0 < 0 || iNode1 < 0) continue;	// 只要iNode0或者iNode1小于0，就为True

			float fHeight = theData.m_pStory[i].fHeight;Q	// 楼层层高


			float fDriftX = 0;
			float fDriftY = 0;
			for (int iStep = 0; iStep < nStep; iStep++)
			{
				Vector4 d0, d1;
				d0.x = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode0, 0, m_cDis.nItems);	// 后三个分量是转角，前三个分量是平动位移
				d0.y = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode0, 1, m_cDis.nItems);	// 同上

				d1.x = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode1, 0, m_cDis.nItems);
				d1.y = m_cDis.aFieldsPtr[iStep]->GetItemData(iNode1, 1, m_cDis.nItems);

				fDriftX = abs((d1.x*cos(fAngle) + d1.y*sin(fAngle)) - (d0.x*cos(fAngle) + d0.y*sin(fAngle))) / fHeight;	// X向层间位移角取max
				fDriftY = abs((d1.x*sin(fAngle) - d1.y*cos(fAngle)) - (d0.x*sin(fAngle) - d0.y*cos(fAngle))) / fHeight;	// Y向层间位移角max
				fNodeDriftX[i + j * nstory] = max(fNodeDriftX[i + j * nstory], fDriftX);
				fNodeDriftY[i + j * nstory] = max(fNodeDriftY[i + j * nstory], fDriftY);
			}
			//最大位移角包络
			if (fNodeDriftX[i + j * nstory] > fStoryDriftX[i])
			{
				iMaxStoryDriftNode[i] = iNode1 + 1;	//X向最大层间位移角对应节点号
				fStoryDriftX[i] = fNodeDriftX[i + j * nstory];
			}
			//fStoryDriftX[i] = max(fStoryDriftX[i], fNodeDriftX[i + j * nstory]);
			//fStoryDriftY[i] = max(fStoryDriftY[i], fNodeDriftY[i + j * nstory]);
		}

		fStoryDriftAll[m*nstory + i] = fStoryDriftX[i];
	}

	//输出位移角文件
	CASCFile fout;
	char buf[512];	// 申请一个512大的空间
	CString str;
	str.Format(_T("%0.0f"), fAngle0);
	CString sOutFileName = theData.GetEarthQuakePath(theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName) + theData.GetPrjName() + L"_Drift_" + str + L".txt";	// 得到工况子目录
	if (!fout.Open(sOutFileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))return;
	USES_CONVERSION;

	AppendMsg(str);
	AppendMsg(L"\r\n");

	sprintf_s(buf, sizeof(buf), "**SAUSAGE层间位移角\r\n");	// sprintf_s()将数据格式化输出到字符串,
	fout.Write(buf, strlen(buf));	// 在".txt"文本中写入”**SAUSAGE层间位移角”

	sprintf_s(buf, sizeof(buf), "层号\t位移角°\t\t\t节点号\r\n", fAngle0);
	fout.Write(buf, strlen(buf));

	for (int iStory = 0; iStory < nstory; iStory++)	// 该循环主要是将"楼层号、层间位移角、节点号"写入".txt"文本中。
	{
		sprintf_s(buf, sizeof(buf), "%3d\t%f\t1/%0.0f\t%6d\t\r\n",
			iStory, fStoryDriftX[iStory], 1.0 / fStoryDriftX[iStory], iMaxStoryDriftNode[iStory]);
		fout.Write(buf, strlen(buf));
	}
	fout.Close();

	CString msgfile = L"notepad.exe \"" + sOutFileName + CString(L"\"");
	if (m_bOpenTxt) WinExec(T2A(msgfile), SW_SHOW);	// 如果为TRUE,SW_SHOW 表示以当前大小激活运行后的程序窗口并显示txt文本。
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
fout.Write(buf, strlen(buf));	// 在"_Drift_All.txt"文本中写入”**SAUSAGE层间位移角”

sprintf_s(buf, sizeof(buf), "层号\t");
fout.Write(buf, strlen(buf));	// 在"_Drift_All.txt"文本中写入”层号”二字

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


for (int iStory = 0; iStory < nstory; iStory++)	// 该循环主要是将"楼层号"和"层间位移角"写入"Drift_All.txt"文本
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
WinExec(T2A(msgfile), SW_SHOW);		// W_SHOW 表示以当前大小激活运行后的程序窗口并显示Drift_All.txt文本结果。


theData.Clear();
>>>>>>> adaaef7ffc87aa90d9fa49e846a5b11440e97136



```

### 节点速度

### 节点加速度

## 单元数据

获取单元计算结果。

### 单元损伤

### 单元性能

## 构件数据

获取构件计算结果。

### 构件内力数据

### 构件设计数据

### 构件性能数据