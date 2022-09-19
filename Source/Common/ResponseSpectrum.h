#pragma once
#include "HeadDefine.h"
//根据场地参数得到规范的特征周期
extern "C" _SSG_DLLIMPEXP float GetEQIntrinsicTerm(int iFieldGroup,int iFieldClass,int iEQProbability);
extern "C" _SSG_DLLIMPEXP float GetEQIntrinsicTerm2(int iFieldGroup,int iFieldClass,int iEQProbability);
//根据地震级别得到规范的最大响应系数，单位：g
//float GetEQMaxCoef(const CString &sEQGrade,int iProbability);
extern "C" _SSG_DLLIMPEXP float GetEQMaxCoef(float fGrade,int iProbability);
extern "C" _SSG_DLLIMPEXP float GetEQMainAmp(float fGrade,int iProbability);

//设计反应谱的计算,返回地震影响系数alfa
//输入：
//fAmax -- 地震影响系数最大值
//fTg   -- 地震的特征周期(秒)
//fKsi  -- 阻尼比
//fTerm -- 周期(秒)
//iMethod -- 超过6秒时的计算方法，0--直接沿用直线下降段公式，1--取6秒时的恒定值
extern "C" _SSG_DLLIMPEXP float DesignSpectrum(float fAmax,float fTg,float fKsi,float fTerm,int iMethod);

//隔震设计反应谱的计算,返回地震影响系数alfa(长周期采用曲线下降段)  林思齐 20210531
//输入：
//fAmax -- 地震影响系数最大值
//fTg   -- 地震的特征周期(秒)
//fKsi  -- 阻尼比
//fTerm -- 周期(秒)
//iMethod -- 超过6秒时的计算方法，0--直接沿用曲线下降段公式，1--取6秒时的恒定值
extern "C" _SSG_DLLIMPEXP float DesignSpectrumIso(float fAmax,float fTg,float fKsi,float fTerm,int iMethod);


class _SSG_DLLIMPEXP CSpectrum
{
public:
	CSpectrum();
	~CSpectrum();

	//计算结果
	int m_nTerm;		//频域采样点数
	float m_fMaxTerm;	//最大周期（秒）
	float *m_pTerm;		//频域采样点周期数组(秒)
	float *m_pMaxDisp;	//频域采样点最大位移数组
	float *m_pMaxVelo;	//频域采样点最大速率数组
	float *m_pMaxAcce;	//频域采样点最大加速度数组

	/*计算单自由度反应谱频率点(对应一个阻尼比和一个特征圆频率)
	nPoints		-- 地震波采样点数
	dt			-- 地震波采样间隔（秒）
	pEQAcce		-- 地震波加速度采样点
	fOmiga		-- 单自由度系统特征圆频率
	fKsi		-- 单自由度系统阻尼比
	fMaxDisp	-- 最大位移
	fMaxVelo	-- 最大速率
	fMaxAcce	-- 最大加速度
	*/
	void Response(
		int nPoints,float dt,const float *pEQAcce,
		float fTerm,float fKsi,
		float &fMaxDisp,float &fMaxVelo,float &fMaxAcce);

	/*计算单自由度反应谱数组
	nPoints		-- 地震波时域采样点数
	dt			-- 地震波时域采样间隔（秒）
	pEQAcce		-- 地震波时域加速度采样点
	fDamp		-- 单自由度系统阻尼比
	*/
	void CalcSpectrum(int nPoints,float dt,const float *pEQAcce,float fMaxTerm,float fTermDist,float fDamp);
};
