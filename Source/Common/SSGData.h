#pragma once

#include "HeadDefine.h"
#include "data.h"
#include "UserDefine.h"
#include "VisibleStruct.h" //定义输出分组修改 邱海 2016年7月11日
#include "Frame.h"
#include "Mesh.h"
//#include "..\StructGraph\SSGAppInterface.h"


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
	/////////////////////以上需要保存undo，需要存储到文件/////////////////////////////////


	
// 	//编辑控制数据
//	BOOL m_bModified; //模型数据修改标志
// 	BUILDRANGE m_Range;

	//虚点信息
// 	VIRTUAL_POINT_TYPE m_iVirtualPointType;  //虚点类型
// 	CVertex m_vVirtualPoint;  //虚点坐标
// 	CRefPoint m_cRefPoint;

//	CUndoRedo m_cUndo;
	
	BOOL IsFromPKPMPre(){return (m_iModelSource==MODEL_PRE);}

	vector<COMBO_STRUCT> m_vvCombGroup; //组合构件组，打开或关闭文件时需要清空
	void ClearCombGroup()
	{
		for (size_t i=0;i<m_vvCombGroup.size();i++)
		{
			m_vvCombGroup[i].Clear();
		}
		m_vvCombGroup.clear();
	};

	CString m_sPrjFile;    //项目文件名，不为空时一定有内存数据，即m_bProjectOpened=TRUE
	BOOL m_bAutoCross;  //画辅助线时自动检查与结构线的交叉情况

	//方法
public:

	
	//写出操作记录文件，用法与TRACE相同
	void WriteMsg(const char* fmt, ...);
	void WriteMsg(const wchar_t* fmt, ...);
	void WriteError(const char* fmt, ...);
	void WriteError(const wchar_t* fmt, ...);

	//清空操作记录文件
	void ClearMsg(void);
	void ClearFeaMsg(void);

	
	CString GetPrjPath(void); //得到项目根目录，例："d:\exam_path\"
	CString GetPrjName(void); //得到项目名，例："exam"
	CString GetPrjTempPath(void); //得到项目临时目录，例："d:\exam_path\temp\"
	CString GetUserDataPath(void); //得到用户数据目录，例："d:\exam_path\UserData\"
	CString GetStaticPath(void); //得到静力工况根目录，例："d:\exam_path\StaticResult\"
	CString GetEarthQuakeRoot(void); //得到地震工况根目录，例："d:\exam_path\EarthQuakeResult\"
	CString GetEarthQuakePath(const CString &sLoadCase); //得到任意工况子目录，例："d:\exam_path\EarthQuakeResult\case_n\"
	CString GetCurCaseFilePath(const CString &sExt,const CString &sGroupName=L"");  //得到当前工况文件全路径，根据扩展名不同辨认不同的子目录,sGroupName为选择集名称
	CString GetFilePath(const CString &sExt,const CString &sLoadCase=L"",const CString &sGroupName=L"");  //得到任意工况文件全路径，根据扩展名不同辨认不同的子目录,sGroupName为选择集名称

	int GetStoryByZ(float z);		//根据标高得到实际楼层号，采用楼层面包络计算
//	void InitialApp(ISSGApp* theExeApp);
	void ReadMatFile();//读取用户自定义材料文件

	int GetMatID(CString &mat);
	CString GetMatName(int id);

};

extern "C" _SSG_DLLIMPEXP CSSGData  theData;


