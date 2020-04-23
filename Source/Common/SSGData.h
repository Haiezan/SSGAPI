#pragma once

#include "HeadDefine.h"
#include "data.h"
#include "UserDefine.h"
#include "VisibleStruct.h" //������������޸� �� 2016��7��11��
#include "Frame.h"
#include "Mesh.h"
//#include "..\StructGraph\SSGAppInterface.h"

enum LOADCASETYPE
{
	STATIC=-1,
	EARTHQUAKE=0,//�������㣬SSGĬ�ϣ�SSG���Դ� m_cLoad
	DIRECTANALY=1,//��ƹ��� �ֽṹ�����𡢸��� m_cLoadDesign
	NLSTATIC=2,//���������� m_cLoadStatic
};

class _SSG_DLLIMPEXP  CSSGData 
{
public:
	CSSGData();
	~CSSGData();
	void Clear(void);
public:
	CProjectPara m_cPrjPara;
	CFrame m_cFrame; //�ṹ��������,��Ҫundo/redo�����ݶ���������CFrame����
	CMesh m_cMesh; //��������
	CStory m_pStory[Sys_Max_Stories]; //¥�����飬��Ҫundo
	int m_nStory; //¥������
	MODEL_SOURCE m_iModelSource;  //ģ����Դ
	/////////////////////������Ҫ����undo����Ҫ�洢���ļ�/////////////////////////////////


	
// 	//�༭��������
//	BOOL m_bModified; //ģ�������޸ı�־
// 	BUILDRANGE m_Range;

	//�����Ϣ
// 	VIRTUAL_POINT_TYPE m_iVirtualPointType;  //�������
// 	CVertex m_vVirtualPoint;  //�������
// 	CRefPoint m_cRefPoint;

//	CUndoRedo m_cUndo;
	
	BOOL IsFromPKPMPre(){return (m_iModelSource==MODEL_PRE);}

	vector<COMBO_STRUCT> m_vvCombGroup; //��Ϲ����飬�򿪻�ر��ļ�ʱ��Ҫ���
	void ClearCombGroup()
	{
		for (size_t i=0;i<m_vvCombGroup.size();i++)
		{
			m_vvCombGroup[i].Clear();
		}
		m_vvCombGroup.clear();
	};

	CString m_sPrjFile;    //��Ŀ�ļ�������Ϊ��ʱһ�����ڴ����ݣ���m_bProjectOpened=TRUE
	BOOL m_bAutoCross;  //��������ʱ�Զ������ṹ�ߵĽ������

	//����
public:

	
	//д��������¼�ļ����÷���TRACE��ͬ
	void WriteMsg(const char* fmt, ...);
	void WriteMsg(const wchar_t* fmt, ...);
	void WriteError(const char* fmt, ...);
	void WriteError(const wchar_t* fmt, ...);

	//��ղ�����¼�ļ�
	void ClearMsg(void);
	void ClearFeaMsg(void);

	
	CString GetPrjPath(void); //�õ���Ŀ��Ŀ¼������"d:\exam_path\"
	CString GetPrjName(void); //�õ���Ŀ��������"exam"
	CString GetPrjBucklingPath(void); //�õ���Ŀ��ʱĿ¼������"d:\exam_path\Buckling\"
	CString GetUserDataPath(void); //�õ��û�����Ŀ¼������"d:\exam_path\UserData\"
	CString GetStaticPath(void); //�õ�����������Ŀ¼������"d:\exam_path\StaticResult\"
	CString GetEarthQuakeRoot(void); //�õ����𹤿���Ŀ¼������"d:\exam_path\EarthQuakeResult\"
	CString GetEarthQuakePath(const CString &sLoadCase); //�õ����⹤����Ŀ¼������"d:\exam_path\EarthQuakeResult\case_n\"
	CString GetCurCaseFilePath(const CString &sExt,const CString &sGroupName=L"");  //�õ���ǰ�����ļ�ȫ·����������չ����ͬ���ϲ�ͬ����Ŀ¼,sGroupNameΪѡ������
	CString GetFilePath(const CString &sExt,const CString &sLoadCase=L"",const CString &sGroupName=L"");  //�õ����⹤���ļ�ȫ·����������չ����ͬ���ϲ�ͬ����Ŀ¼,sGroupNameΪѡ������

	int GetStoryByZ(float z);		//���ݱ�ߵõ�ʵ��¥��ţ�����¥����������
	//void InitialApp(ISSGApp* theExeApp);
	void ReadMatFile();//��ȡ�û��Զ�������ļ�

	int GetMatID(CString &mat);
	CString GetMatName(int id);

	BOOL GetBeamStoryMat(CBeamStruc &beam);
	BOOL GetPlateStoryMat(CPlateStruc &plate);

	CString GetCaseStaticPath(const CString &sLoadCase); //�õ�����������Ŀ¼������"d:\exam_path\StaticResult\"
	//
	BOOL HasTimeHis(int iCmb);
	//
	float GetLoadCoef(CLoadCase *lc,CASE_TYPE nType,BOOL bConLoad=TRUE);
	//�õ���ǰ�����б�
	CLoadCollection *GetLoadCollecton();

	//���õ�ǰ�������ͣ����ڶ�ȡ����ļ�
	void SetLoadCollection(int iType=0){m_iLoadCaseType=(LOADCASETYPE)iType;};
	LOADCASETYPE GetLoadCollectionType(){return m_iLoadCaseType;};
	// 
	int CreateOverallDefect(float* &coord);
	int CreateMemberDefect(float* &coord);
	BOOL WriteBinStatcNodeFieldOneStep(const CString &fname,const int nNode,float *&coord,const CString &sCmpName);
	//
	int CreateOverallDefectFile();
	int CreateMemberDefectFile();
	int CreateSuperPosDefectFile();
private:
	LOADCASETYPE m_iLoadCaseType;
};

extern "C" _SSG_DLLIMPEXP CSSGData  theData;

//extern "C" __declspec(dllexport) CSSGData theData;

// extern "C" _SSG_DLLIMPEXP int GetText();
// 
// extern "C" _SSG_DLLIMPEXP int kkk;

