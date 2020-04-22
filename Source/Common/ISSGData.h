#pragma once


/*
数据接口
2014年5月14日 刘慧鹏起草
*/


// LHP

enum IS_MEM_TYPE
{
	IS_MEM_UNKNOW=0,
	IS_MEM_BEAM,
	IS_MEM_COLUMN,
	IS_MEM_BRACE,
	IS_MEM_WALL,
	IS_MEM_SLAB,
	IS_MEM_EDGE
};

enum IS_FILE_TYPE
{
	IS_FL_TOTAL=0,				// 各类总体信息
	IS_FL_MODAL,				// 获取模态周期等结果
	IS_FL_MASS,					// 获取质量
	IS_FL_STA_DISP,				// 获取施工位移
	IS_FL_DYNA_DISP,			// 获取动力时程节点位移结果
	IS_FL_DYNA_DAMAGE,			// 获取动力时程下单元损伤结果
	IS_FL_DYNA_FORCE,			// 获取动力时程下单元节点内力
	IS_FL_DYNA_TOPFORCE,		// 获取楼层顶部构件内力
	IS_FL_DYNA_BTNFORCE,		// 获取楼层底部构件内力
	IS_FL_DYNA_STORY_DRIFT,		// 获取楼层位移位移角等
	IS_FL_DYNA_STORY_SHEAR		// 获取楼层剪力等
};

struct ISSGData
{
	// 跟该类相关数据的读取开始和结束清理
	void SetWorkPath(const char* sPath);
	void SetProjectName(const char* sPath);
	bool Begin(IS_FILE_TYPE type,const char* sGroupName);
	bool End();
	// 参数等
	// 判断是否成功进行静力分析
	bool IsSuccessStatic();
	// 判断是否成功进行模态分析
	bool IsSuccessModal();
	// 判断是否成功进行动力时程分析
	bool IsSuccessDynamic();
	// 获取楼层总数(不带0层)
	int GetStoryCount();
	// 获取节点总数
	int GetNodeCount();
	// 获取单元数 梁、柱、支撑、墙、板
	int GetElementCount(int nMem[5]);
	// 获取网格划分的尺寸,nMaxSize:最大网格尺寸 nMinSize：最小网格尺寸
	void GetMeshSize(float& nMaxSize,float& nMinSize);
	// 获取计算模型中容重，fCrtWeight：砼容重，fStlWeight：钢容重
	void GetMatWeight(float& fCrtWeight,float& fStlWeight);
	// 获取地震参数，fSeisIntensity：烈度，fSeisField场地，fSeisGroup地震分组，fSeisTg特征周期
	void GetSeismicParams(int& fSeisIntensity,int& fSeisField,int& fSeisGroup,float& fSeisTg);
	// 获取动力时程参数 bCrtEla砼是否弹塑性,bStlEla钢是否弹塑性,bNLGeom：几何非线性,nDampType阻尼类型
	void GetDynaParams(bool& bCrtEla,bool& bStlEla,float& fStep,bool& bNLGeom,int& nDampType);
	// 获取瑞雷阻尼参数，fPeriod前两阶周期，fDampRatio阻尼比
	bool GetRayleighDamp(float fPeriod[2],float fDampRatio[2]);
	// 获取模态阻尼参数，nModal返回的振型数，fDampRatio阻尼比，nMaxModal能填写的最多振型数
	bool GetModdalDamp(int& nModal,float* fDampRatio,int nMaxModal);
	// 工况和地震波信息
	// 获取工况个数，需要验证工况的有效性
	int GetCaseCount();
	// 获取工况地震波名称，nCaseSN工况序号，sWaveName:地震波名
	void GetCaseToWave(int nCaseSN,char* sWaveName);
	// 根据地震波名获取对应的工况序号，返回对应个数和nCaseSNs序号
	int GetWaveToCase(const char* sWaveName,int* nCaseSNs);
	// 获取某个工况参数，nCaseSN工况序号，fTotalTime总时间，fAccelMax三向地震波加速度，第一个为主方向加速度，后两个是相应比例
	void GetCaseParams(int nCaseSN,float& fTotalTime,float fAccelMax[3]);
	// 获取某个地震波数据，返回数据点个数和数据点值，sWaveName地震波名，fData地震波数据，nMaxData地震波数据最多点，如果超出则返回-1
	int GetWaveData(const char* sWaveName,float* fData,int nMaxData);
	// 获取地震波反应谱，返回数据点个数和数据点值，sWaveName地震波名，fData反应谱数据，nMaxData反应谱数据最多点，如果超出则返回-1
	int GetWaveSpectrumn(const char* sWaveName,float* fData,int nMaxData);																					
	// 获取规范反应谱，返回数据点个数和数据点值，fData规范反应谱数据，nMaxData规范反应谱数据最多点，如果超出则返回-1
	int GetStandardSpectrumn(float* fData,int nMaxData);																					

	// 质量
	// 恒载\活载\附加总质量\混凝土总质量\钢材总质量\钢筋总质量
	void GetTotalMass(float fTotalMass[6]);
	// fMass:恒载\活载\附加质量\质量比（上下层质量比）\砼质量\钢材质量\钢筋质量
	// nStorySN楼层序号（1开始）
	void GetSingleStoryMass(int nStorySN,float fMass[7]);
	
	// 模态
	// nStorySN楼层序号（1开始）
	// 5代表梁、柱、支撑、墙、板
	// nMem:构件数，nMemCrt构件砼等级，nMemRebar：钢筋等级，fHeight该层层高
	void GetModelInfo(int nStorySN,int nMem[5],int nMemCrt[5],int nMemRebar[5],float& fHeight);
	// 振型数
	int GetPeriodCount();
	// nModalSN:模态序号，返回对应的周期值
	float GetPeriodResult(int nModalSN);
	
	// 物理场结果输出接口
	bool SetCurCase(int nCaseSN);	// 设置当前操作工况，仅操作了之后才能Begin获取物理场结果
	int GetStepCount();				// 总分析步数

	// 结果部分 nNodeID：节点id号，iComponent：分量编号,fData:返回数据 
	// 静力计算时的节点位移
	bool GetStaticNodeDisp(int nNodeID,int iComponent,float* fData);
	// 动力时程节点位移
	int GetDynaNodeDispHistory(int nNodeID,int iComponent,float* fData);
	// 动力时程节点加速度
	int GetDynaNodeAccelHistory(int nNodeID,int iComponent,float* fData);

	// 构件 IS_MEM_TYPE type：明确构件类型,iComponent:分量号
	// 获取楼层相关构件ID号nMemIDs：返回ID号
	int GetFloorMember(int nStorySN,IS_MEM_TYPE type,int* nMemIDs);
	// 根据构件ID号获取该构件对应的单元编号，
	int GetMemberElemIDs(int nMemID,IS_MEM_TYPE type,int* nElemIDs);
	// 根据构件ID获取该构件底部、顶部对应节点编号
	int GetBtnMemberNodeIDs(int nMemID,IS_MEM_TYPE type,int* nNodeIDs);
	int GetTopMemberNodeIDs(int nMemID,IS_MEM_TYPE type,int* nNodeIDs);
	// 获取所有节点坐标，返回数组指针
	float* GetCoord();
	// 获取构件的底部、顶部时程内力,，排列顺序：（张老师补充）
	int GetMemberBtnForceHistory(int* nColIDs,int nCol,int* nBraceIDs,int nBrace,int* nWallColIDs,int nWallCol,
		float* fColFs,float* fBraceFs,float* fWallFs);
	// 获取单元的最大拉or压损伤，输入一批单元，返回对应个数的拉or压损伤，没有填0
	bool GetElemMaxDamage(int nElem,int* nElemIDs,float* fCondense,float* fTensile);
	// 获取单元时程损伤，返回个数
	int GetElemDamageHistory(int nElemID,float* fDamage);

	// 楼层
	// 获取某个分量下所有楼层时程位移、位移角，返回指针
	float* GetAllDriftHistory(int iComponent);
	// 获取某个分量下所有楼层时程剪力，返回指针
	float* GetAllShearHistory(int iComponent);


	void ClearCase(int nCaseSN);  //清除该工况下所有数据
	void Clear();				  // 清除所有数据，层数归0

private:
};





