#pragma once


/*
���ݽӿ�
2014��5��14�� ���������
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
	IS_FL_TOTAL=0,				// ����������Ϣ
	IS_FL_MODAL,				// ��ȡģ̬���ڵȽ��
	IS_FL_MASS,					// ��ȡ����
	IS_FL_STA_DISP,				// ��ȡʩ��λ��
	IS_FL_DYNA_DISP,			// ��ȡ����ʱ�̽ڵ�λ�ƽ��
	IS_FL_DYNA_DAMAGE,			// ��ȡ����ʱ���µ�Ԫ���˽��
	IS_FL_DYNA_FORCE,			// ��ȡ����ʱ���µ�Ԫ�ڵ�����
	IS_FL_DYNA_TOPFORCE,		// ��ȡ¥�㶥����������
	IS_FL_DYNA_BTNFORCE,		// ��ȡ¥��ײ���������
	IS_FL_DYNA_STORY_DRIFT,		// ��ȡ¥��λ��λ�ƽǵ�
	IS_FL_DYNA_STORY_SHEAR		// ��ȡ¥�������
};

struct ISSGData
{
	// ������������ݵĶ�ȡ��ʼ�ͽ�������
	void SetWorkPath(const char* sPath);
	void SetProjectName(const char* sPath);
	bool Begin(IS_FILE_TYPE type,const char* sGroupName);
	bool End();
	// ������
	// �ж��Ƿ�ɹ����о�������
	bool IsSuccessStatic();
	// �ж��Ƿ�ɹ�����ģ̬����
	bool IsSuccessModal();
	// �ж��Ƿ�ɹ����ж���ʱ�̷���
	bool IsSuccessDynamic();
	// ��ȡ¥������(����0��)
	int GetStoryCount();
	// ��ȡ�ڵ�����
	int GetNodeCount();
	// ��ȡ��Ԫ�� ��������֧�š�ǽ����
	int GetElementCount(int nMem[5]);
	// ��ȡ���񻮷ֵĳߴ�,nMaxSize:�������ߴ� nMinSize����С����ߴ�
	void GetMeshSize(float& nMaxSize,float& nMinSize);
	// ��ȡ����ģ�������أ�fCrtWeight�������أ�fStlWeight��������
	void GetMatWeight(float& fCrtWeight,float& fStlWeight);
	// ��ȡ���������fSeisIntensity���Ҷȣ�fSeisField���أ�fSeisGroup������飬fSeisTg��������
	void GetSeismicParams(int& fSeisIntensity,int& fSeisField,int& fSeisGroup,float& fSeisTg);
	// ��ȡ����ʱ�̲��� bCrtEla���Ƿ�����,bStlEla���Ƿ�����,bNLGeom�����η�����,nDampType��������
	void GetDynaParams(bool& bCrtEla,bool& bStlEla,float& fStep,bool& bNLGeom,int& nDampType);
	// ��ȡ�������������fPeriodǰ�������ڣ�fDampRatio�����
	bool GetRayleighDamp(float fPeriod[2],float fDampRatio[2]);
	// ��ȡģ̬���������nModal���ص���������fDampRatio����ȣ�nMaxModal����д�����������
	bool GetModdalDamp(int& nModal,float* fDampRatio,int nMaxModal);
	// �����͵�����Ϣ
	// ��ȡ������������Ҫ��֤��������Ч��
	int GetCaseCount();
	// ��ȡ�����������ƣ�nCaseSN������ţ�sWaveName:������
	void GetCaseToWave(int nCaseSN,char* sWaveName);
	// ���ݵ�������ȡ��Ӧ�Ĺ�����ţ����ض�Ӧ������nCaseSNs���
	int GetWaveToCase(const char* sWaveName,int* nCaseSNs);
	// ��ȡĳ������������nCaseSN������ţ�fTotalTime��ʱ�䣬fAccelMax������𲨼��ٶȣ���һ��Ϊ��������ٶȣ�����������Ӧ����
	void GetCaseParams(int nCaseSN,float& fTotalTime,float fAccelMax[3]);
	// ��ȡĳ���������ݣ��������ݵ���������ݵ�ֵ��sWaveName��������fData�������ݣ�nMaxData�����������㣬��������򷵻�-1
	int GetWaveData(const char* sWaveName,float* fData,int nMaxData);
	// ��ȡ���𲨷�Ӧ�ף��������ݵ���������ݵ�ֵ��sWaveName��������fData��Ӧ�����ݣ�nMaxData��Ӧ���������㣬��������򷵻�-1
	int GetWaveSpectrumn(const char* sWaveName,float* fData,int nMaxData);																					
	// ��ȡ�淶��Ӧ�ף��������ݵ���������ݵ�ֵ��fData�淶��Ӧ�����ݣ�nMaxData�淶��Ӧ���������㣬��������򷵻�-1
	int GetStandardSpectrumn(float* fData,int nMaxData);																					

	// ����
	// ����\����\����������\������������\�ֲ�������\�ֽ�������
	void GetTotalMass(float fTotalMass[6]);
	// fMass:����\����\��������\�����ȣ����²������ȣ�\������\�ֲ�����\�ֽ�����
	// nStorySN¥����ţ�1��ʼ��
	void GetSingleStoryMass(int nStorySN,float fMass[7]);
	
	// ģ̬
	// nStorySN¥����ţ�1��ʼ��
	// 5������������֧�š�ǽ����
	// nMem:��������nMemCrt�����ŵȼ���nMemRebar���ֽ�ȼ���fHeight�ò���
	void GetModelInfo(int nStorySN,int nMem[5],int nMemCrt[5],int nMemRebar[5],float& fHeight);
	// ������
	int GetPeriodCount();
	// nModalSN:ģ̬��ţ����ض�Ӧ������ֵ
	float GetPeriodResult(int nModalSN);
	
	// �����������ӿ�
	bool SetCurCase(int nCaseSN);	// ���õ�ǰ������������������֮�����Begin��ȡ�������
	int GetStepCount();				// �ܷ�������

	// ������� nNodeID���ڵ�id�ţ�iComponent���������,fData:�������� 
	// ��������ʱ�Ľڵ�λ��
	bool GetStaticNodeDisp(int nNodeID,int iComponent,float* fData);
	// ����ʱ�̽ڵ�λ��
	int GetDynaNodeDispHistory(int nNodeID,int iComponent,float* fData);
	// ����ʱ�̽ڵ���ٶ�
	int GetDynaNodeAccelHistory(int nNodeID,int iComponent,float* fData);

	// ���� IS_MEM_TYPE type����ȷ��������,iComponent:������
	// ��ȡ¥����ع���ID��nMemIDs������ID��
	int GetFloorMember(int nStorySN,IS_MEM_TYPE type,int* nMemIDs);
	// ���ݹ���ID�Ż�ȡ�ù�����Ӧ�ĵ�Ԫ��ţ�
	int GetMemberElemIDs(int nMemID,IS_MEM_TYPE type,int* nElemIDs);
	// ���ݹ���ID��ȡ�ù����ײ���������Ӧ�ڵ���
	int GetBtnMemberNodeIDs(int nMemID,IS_MEM_TYPE type,int* nNodeIDs);
	int GetTopMemberNodeIDs(int nMemID,IS_MEM_TYPE type,int* nNodeIDs);
	// ��ȡ���нڵ����꣬��������ָ��
	float* GetCoord();
	// ��ȡ�����ĵײ�������ʱ������,������˳�򣺣�����ʦ���䣩
	int GetMemberBtnForceHistory(int* nColIDs,int nCol,int* nBraceIDs,int nBrace,int* nWallColIDs,int nWallCol,
		float* fColFs,float* fBraceFs,float* fWallFs);
	// ��ȡ��Ԫ�������orѹ���ˣ�����һ����Ԫ�����ض�Ӧ��������orѹ���ˣ�û����0
	bool GetElemMaxDamage(int nElem,int* nElemIDs,float* fCondense,float* fTensile);
	// ��ȡ��Ԫʱ�����ˣ����ظ���
	int GetElemDamageHistory(int nElemID,float* fDamage);

	// ¥��
	// ��ȡĳ������������¥��ʱ��λ�ơ�λ�ƽǣ�����ָ��
	float* GetAllDriftHistory(int iComponent);
	// ��ȡĳ������������¥��ʱ�̼���������ָ��
	float* GetAllShearHistory(int iComponent);


	void ClearCase(int nCaseSN);  //����ù�������������
	void Clear();				  // ����������ݣ�������0

private:
};





