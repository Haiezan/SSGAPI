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

	if (!fin.Open(theData.m_sPrjFile, CFile::modeRead | CFile::shareDenyWrite)) 	// theData.m_sPrjFile：项目文件名
	{
		printf("fail to open the file");
		return ;//或者抛出异常。
	}

	printf("读入*STORY ...\r\n");

	if (!fin.Open(theData.m_sPrjFile, CFile::modeRead | CFile::shareDenyWrite)) return;		// theData.m_sPrjFile：项目文件名
	//根据*STORY关键字读取楼层信息

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


## 节点信息

获取单元节点信息并进行数据处理。
```C++
//读取动力分析节点位移
CNodeFieldSet m_cDis;  // 定义 CNodeFieldSet 类的一个对象m_cDis，节点位移数据
m_cDis.Clear();		// 清除
printf("加载动力分析结点位移文件...\r\n"); 
fname = theData.GetFilePath(FILE_DISP_BIN, theData.m_cFrame.m_cLoad[m_iCaseNum - 1]->sCaseName); //直接写工况名称也可以
BOOL ret = m_cDis.ReadBinNodeField_AllStep(fname, false);  // 读入二进制结点位移, TRUE时选择一个分量读取，FALSE时读取所有分量

if (!ret || m_cDis.GetStepNumber() < 1)
	{
	printf(L"没找到结果文件！\r\n");
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
int iNodeNum = 1000;	
int nStep = m_cDis.nMaxSteps; // 文件中最大时间步数，读入文件时赋值
int iNodeNum = 1000;	// 文件中最大时间步数，读入文件时赋值
int nStep = m_cDis.nMaxSteps;
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

//读取DEF文件，DEF文件中存的是模型的节点号
printf("开始读取DEF文件...\r\n");
CString defname = theData.GetPrjPath() + theData.GetPrjName() + CString("_") + CString("All") + CString(".") + FILE_OUTPUT_DEF;	// DEF的文件路径
int *story_pillar_node = NULL;
int nstory1 = theData.m_nStory + 1;

int npillar = 0;
int nstory = 0;
if (fin.Open(defname, CFile::modeRead | CFile::shareDenyWrite))	// 打开DEF文件
{
	nstory = fin.GetInt() ;	// 模型的层数，读DEF文件的第一行数据
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

printf("读取数据成功\r\n\r\n");




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