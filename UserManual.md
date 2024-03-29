# 概述

SSG-API可用于SAUSG系列软件模型的前后处理数据读取和编辑。

# 更新说明

* 1 【2022版本】使用之前调用 theData.InitialAPI();

```C++
//清除所有数据
theData.Clear();
theData.InitialAPI(); //2022版本修改
theData.m_sPrjFile=fname;
```

* 2 【2022版本】材料类有改动;

* 3 【2022版本】需要调用SSGPub64_D.dll(Debug版本）或SSGPub64.dll（Release版本）;

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
#### 1.获取构件内力数据函数实现
```C++
/*
注释：
模型中构件包含了水平构件和竖向构件。此外，构件的内力分为 1 端内力和 2 端内力。
本小节仅仅介绍竖向构件1端（整体坐标系下，竖向构件底部的称为1端，顶部称为2端）的内力数据获取，
其他情况的构件内力可按照类似的方法获得相应的构件内力。
*/

BOOL AddForceUser(const CString &fname,CF15Header &hdrRead, CF15StruBlock *pblock) 
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


	int nOffset = 0;
	int nsteps  = pStruFieldSet[0].nMaxSteps; // 总时间步数

	// 对一维构件和二维构件进行构件内力统计
	for(int k = 0; k < nsteps; k++)   // 遍历总的时间步数
	{
		for(int itype = 0; itype < hdrRead.FileInfo.type_num; itype++) // 按一维构件和二维构件进行遍历
		{	
			if(!pStruFieldSet[itype].ReadOneStepOneType(fname, hdrRead, pblock, k, itype))
				break;

			if( CString(pblock[itype].pBlockName) == L"一维构件")
			{
				/*
				注释：
				通过索引构件的ID，可以得到每个构件在整体坐标系下的内力。
				需要注意一维构件包含：框架梁、柱、斜撑、边缘构件、暗梁（虚梁）、连梁纵筋和一般连接
				*/
				int nBeamOffset = nOffset;				
				for(int i = 0; i < pStruFieldSet[itype].nStrus; i++) 
				{
					int iStruId = pblock[itype].pStruID[i]; // 获取构件的ID
					CBeamStruc &beam = theData.m_cFrame.m_aBeam[iStruId]; 

					if(beam.iStrucType & STRUCT_ALL_PILLAR) // 非水平构件
					{
						if(beam.u.z < 0) // 局部坐标系相反
						{
							nBeamOffset = 6;
						}
					}

					Vector4 f0, m0;
					// 局部坐标系下的X向、Y向和Z向的力
					f0.x = pStruFieldSet[itype].cData.GetItemData(i, 0 + nBeamOffset, pStruFieldSet[itype].nStrus); 
					f0.y = pStruFieldSet[itype].cData.GetItemData(i, 1 + nBeamOffset, pStruFieldSet[itype].nStrus); 
					f0.z = pStruFieldSet[itype].cData.GetItemData(i, 2 + nBeamOffset, pStruFieldSet[itype].nStrus); 

					// 局部坐标系下的X向、Y向和Z向的弯矩
					m0.x = pStruFieldSet[itype].cData.GetItemData(i, 3 + nBeamOffset, pStruFieldSet[itype].nStrus); 
					m0.y = pStruFieldSet[itype].cData.GetItemData(i, 4 + nBeamOffset, pStruFieldSet[itype].nStrus); 
					m0.z = pStruFieldSet[itype].cData.GetItemData(i, 5 + nBeamOffset, pStruFieldSet[itype].nStrus); 

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
					f.x = Vector3Dotf(f0, u); // 得到构件在整体坐标系下的 X 向的力
					f.y = Vector3Dotf(f0, v); // 得到构件在整体坐标系下的 Y 向的力
					f.z = Vector3Dotf(f0, w); // 得到构件在整体坐标系下的 Z 向的力

					// 例如，如果想得到柱子的内力，通过构件类型来判断，可以得到柱子的内力；同样，其他构件可以按照类似的方式得到
					if( beam.iStrucType == STRUCT_PILLAR )  // 判断是否是柱子
					{
						float pillar_Fx = f.x; // 得到柱子在整体坐标系下的 X 向的力
						float pillar_Fy = f.y; // 得到柱子在整体坐标系下的 X 向的力
					}
				}
			}

			else if(CString(pblock[itype].pBlockName) == L"二维构件") 
			{
				for(int j = 0; j < pStruFieldSet[itype].nStrus; j++) 
				{
					/*
					注释：
					通过索引构件的ID，可以得到每个构件在整体坐标系下的内力
					需要注意二维构件包含：墙梁和墙柱，不包括楼板。
					*/
					int iStruId = pblock[itype].pStruID[j];  // 获取构件的ID
					CPlateStruc &Plate = theData.m_cFrame.m_aPlate[iStruId]; 


					Vector4 f0，m0;
					// 局部坐标系下的X向、Y向和Z向的力
					f0.x = pStruFieldSet[itype].cData.GetItemData(j, 0 + nOffset , pStruFieldSet[itype].nStrus);
					f0.y = pStruFieldSet[itype].cData.GetItemData(j, 1 + nOffset , pStruFieldSet[itype].nStrus);
					f0.z = pStruFieldSet[itype].cData.GetItemData(j, 2 + nOffset , pStruFieldSet[itype].nStrus);

					// 局部坐标系下的X向、Y向和Z向的弯矩
					m0.x = pStruFieldSet[itype].cData.GetItemData(j, 3 + nOffset , pStruFieldSet[itype].nStrus);
					m0.y = pStruFieldSet[itype].cData.GetItemData(j, 4 + nOffset , pStruFieldSet[itype].nStrus);
					m0.z = pStruFieldSet[itype].cData.GetItemData(j, 5 + nOffset , pStruFieldSet[itype].nStrus);

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
					f.x = Vector3Dotf(f0, u);  // 得到构件在整体坐标系下的 X 向的力
					f.y = Vector3Dotf(f0, v);  // 得到构件在整体坐标系下的 Y 向的力
					f.z = Vector3Dotf(f0, w);  // 得到构件在整体坐标系下的 Z 向的力

					
					// 如果想得到剪力墙构件内力，通过构件类型来判断，可得到构件内力；同样，墙梁可以按照类似的方式得到
					if( Plate->iSubType == 0 )  // 判断是否是墙柱。子类型 0-墙柱，1-墙梁，
					{
						float wall_Fx = f.x; // 得到墙柱在整体坐标系下的 X 向的力
						float wall_Fy = f.y; // 得到墙柱在整体坐标系下的 Y 向的力
					}
				}
			}		
		}
	}

	return TRUE;

}

```

#### 2.构件内力数据获取
```C++

BOOL  InternalForces(CArray<int, int> &aRunCase,CLoadCollection &cLoads )
{
	if (aRunCase.GetCount() < 1) return FALSE;  // 小于1，说明没有工况

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
	if(nsteps < 1) continue; // 步长小于1，下个循环

	// 统计构件的内力
	AddForceUser(sInternalForceFName, hdrRead, pblockRead);

	return TRUE;
}

// 遍历所有的工况
CLoadCollection *lc = theData.GetLoadCollecton();
CArray<int, int> aRunCase;
for (int i = 0; i < lc->GetCount(); i++)
{
	aRunCase.Add(i);
}

// 构件内力数据获取
InternalForces(aRunCase, theData.m_cFrame.m_cLoad);

```



### 构件设计数据

### 构件性能数据