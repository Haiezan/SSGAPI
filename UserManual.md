# 概述

SSG-API可用于SAUSG系列软件模型的前后处理数据读取和编辑。

# 数据结构

## 模型数据

### CSSGData类

CSSGData类：包含模型所有信息

theData对象：全局变量

```C++
class _SSG_DLLIMPEXP  CSSGData 
{
public:
	CSSGData();
	~CSSGData();
	void Clear(void);
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
theData.Clear();
```

# 模型信息

获取并修改建模信息。

## 项目信息

读取项目总信息，储存于m_cPrjPara中

```C++
//读取项目总信息
CString fname = L"D:/AA.ssg"; //ssg文件
bSuccess &= theData.m_cPrjPara.Read(fname);
```

## 楼层数据

读入楼层数据，储存于m_nStory中

```C++
//打开ssg文件
CASCFile fin;
if (!fin.Open(theData.m_sPrjFile, CFile::modeRead | CFile::shareDenyWrite)) return;
//根据*STORY关键字读取楼层信息
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
```

## 构件信息

获取构件信息并进行修改。

## 单元信息

获取单元信息并进行数据处理。

## 节点信息

获取单元节点信息并进行数据处理。

# 结果数据

获取计算结果数据并进行数据处理。

## 结构数据

获取关于结构的计算结果。

## 节点数据

获取节点计算结果。

### 节点位移

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