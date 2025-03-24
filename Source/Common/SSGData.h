#pragma once

#include "Frame.h"
#include "Mesh.h"
#include "SSGAppInterface.h"

extern _SSG_DLLIMPEXP ISSGApp* pTheApp;

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

	CString m_sPrjFile2020;
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
	void ClearFeaMsg(const CString &sLoadCase);
	
	CString GetPrjPath(void) const; //得到项目根目录，例："d:\exam_path\"
	CString GetPrjPath2020(void);
	CString GetPrjName(void) const; //得到项目名，例："exam"
	CString GetPrjName2020(void); //得到项目名，例："exam"
	CString GetPrjBucklingRoot(void)const; //得到屈曲工况根目录，例："d:\exam_path\BucklingResult\"
	CString GetPrjBucklingPath(const CString& sLoadCase)const; //得到屈曲工况子目录，例："d:\exam_path\BucklingResult\BucklingCase\"
	CString GetUserDataPath(void); //得到用户数据目录，例："d:\exam_path\UserData\"
	CString GetStaticPath(void); //得到静力工况根目录，例："d:\exam_path\StaticResult\"
	CString GetEarthQuakeRoot(void)const; //得到地震工况根目录，例："d:\exam_path\EarthQuakeResult\"
	CString GetDefectPath(void)const; //得到初始缺陷根目录，例："d:\exam_path\DefectResult\"
	CString GetEarthQuakePath(const CString &sLoadCase)const; //得到任意工况子目录，例："d:\exam_path\EarthQuakeResult\case_n\"
	CString GetCurCaseFilePath(const CString &sExt,const CString &sGroupName=L"");  //得到当前工况文件全路径，根据扩展名不同辨认不同的子目录,sGroupName为选择集名称
	CString GetFilePath(const CString &sExt,const CString &sLoadCase=L"",const CString &sGroupName=L"")const;  //得到任意工况文件全路径，根据扩展名不同辨认不同的子目录,sGroupName为选择集名称
	CString GetNoDmpPath()const;

	//删除所有依赖于SSG的中间文件
	void RemoveAllIntFile(void);
	//删除所有计算结果文件
	void RemoveAllResultFile(void);

	CString GetCModePath(void)const; //得到复模态分析根目录，例："d:\exam_path\CModalResult\"
	CString GetCModalSpectCasePath(const CString &sLoadCase)const; //得到复模态反应谱工况子目录，例："d:\exam_path\CModalResult\case_n\"

	int GetStoryByZ(float z);		//根据标高得到实际楼层号，采用楼层面包络计算
	void InitialApp(ISSGApp* theExeApp);
	//For API 邱海 2022年9月16日
	void InitialAPI();
	bool ReadSSGAPI(const CString& sFile);

	BOOL GetBeamStoryMat(CBeamStruc &beam);
	BOOL GetPlateStoryMat(CPlateStruc &plate);

	CString GetCaseStaticPath(const CString &sLoadCase) const; //得到静力工况根目录，例："d:\exam_path\StaticResult\"
	//
	BOOL HasTimeHis(int iCmb);

	//得到当前工况列表
	CLoadCollection *GetLoadCollecton();

	//设置当前工况类型，用于读取结果文件
	void SetLoadCollection(int iType = 0) { m_iLoadCaseType = (LOADCASETYPE)iType;};
	void SetNoDmpPath() { m_bNoDmpPath = true; }
	void ResetNoDmpPath() { m_bNoDmpPath = false; }
	bool bNoDmpPath() { return m_bNoDmpPath; }
	void SetEnvCase(bool bEnv = true) { m_bEnvCase = bEnv; if (pDataBak) pDataBak->SetEnvCase(bEnv); }
	LOADCASETYPE GetLoadCollectionType(){return m_iLoadCaseType;};
	void GetCurCaseName(int id, CString &sCase);  //得到工况名称
	// 
	BOOL CreateOverallDefect(float* &coord, bool bShowMessage = false);
	int CreateMemberDefect(float* &coord);
	BOOL WriteBinStatcNodeFieldOneStep(const CString &fname,const int nNode,float *&coord,const CString &sCmpName);
	//
	int CreateOverallDefectFile();
	int CreateMemberDefectFile();
	int CreateSuperPosDefectFile();

	//按照工况生成初始缺陷
	int CreateDefectCaseFile();
	int CreateMemberDefectFile(int iLC);
	int CreateMemberDefect(int iLC, float*& coord); //iLC-工况号（从0开始）
	int CreateFrameDefectFile(int iLC);
	int CreateFrameDefect(int iLC, float*& coord, bool bShowMessage = false); //iLC-工况号（从0开始）
	//获取工况数据文件，构件缺陷与结构缺陷连续编号
	CString GetDefectFile(int iSel, CString* pCaseName = NULL);
	CString GetMemberDefectFile(int iSel, CString* pCaseName = NULL);
	CString GetFrameDefectFile(int iSel, CString* pCaseName = NULL);
	//加载节点初始缺陷数据
	BOOL LoadDefectFile(const CString& fname, float*& coord);
	//设置重新生成初始缺陷工况文件的状态，是否重新生成缺陷文件
	void SetDefectUpdateState(int iSel, BOOL bUpdate = TRUE);
	
	void GetMeshNum(int& nbeam, int& ntri, int& nquad);
	void GetFrameNum(int& nbeam, int& nplate);
	void GetData(const CFrame*& frame, const CMesh*& mesh, int& nStory);
	//仅用多模型
	bool ReadSSGAPIINSSG(const CString& sFile,BOOL bMultiplyModel = FALSE, BOOL bReadResult = TRUE); // bMultiplyModel控制是否new多个pDataBak  bReadResult是否读模型结果
	bool bLoadOtherData()const { return m_bReadOther; }
	void SetTheData(bool bTheData = true);
	CString GetOtherFilePath(const CString& sExt, const CString& sLoadCase = L"", const CString& sGroupName = L"") const;
	CLoadCollection* GetOtherLoadCollecton()const;
	CString GetOtherPrjPath();
	vector<CSSGData*> MultiModelTheData;
	bool bReadMultiModel()const { return m_bReadMultiModel; }
	bool ReadMultiplySSGAPIINSSG(const CString& m_sPrjFile_Scheme, BOOL bMultiplyModel = FALSE, BOOL bReadResult = FALSE);
private:
	LOADCASETYPE m_iLoadCaseType;
	bool m_bNoDmpPath;
	bool m_bEnvCase;
	bool m_btheData;
	bool m_bReadOther;
	CSSGData* pDataBak;
	bool m_bReadMultiModel; // 判断是否读取多模型计算结果

};

extern "C" _SSG_DLLIMPEXP CSSGData theData;

//extern "C" __declspec(dllexport) CSSGData theData;

// extern "C" _SSG_DLLIMPEXP int GetText();
// 
// extern "C" _SSG_DLLIMPEXP int kkk;

