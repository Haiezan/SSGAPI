#pragma once
#include "HeadDefine.h"
//���ݳ��ز����õ��淶����������
extern "C" _SSG_DLLIMPEXP float GetEQIntrinsicTerm(int iFieldGroup,int iFieldClass,int iEQProbability);
extern "C" _SSG_DLLIMPEXP float GetEQIntrinsicTerm2(int iFieldGroup,int iFieldClass,int iEQProbability);
//���ݵ��𼶱�õ��淶�������Ӧϵ������λ��g
//float GetEQMaxCoef(const CString &sEQGrade,int iProbability);
extern "C" _SSG_DLLIMPEXP float GetEQMaxCoef(float fGrade,int iProbability);
extern "C" _SSG_DLLIMPEXP float GetEQMainAmp(float fGrade,int iProbability);

//��Ʒ�Ӧ�׵ļ���,���ص���Ӱ��ϵ��alfa
//���룺
//fAmax -- ����Ӱ��ϵ�����ֵ
//fTg   -- �������������(��)
//fKsi  -- �����
//fTerm -- ����(��)
//iMethod -- ����6��ʱ�ļ��㷽����0--ֱ������ֱ���½��ι�ʽ��1--ȡ6��ʱ�ĺ㶨ֵ
extern "C" _SSG_DLLIMPEXP float DesignSpectrum(float fAmax,float fTg,float fKsi,float fTerm,int iMethod);

//������Ʒ�Ӧ�׵ļ���,���ص���Ӱ��ϵ��alfa(�����ڲ��������½���)  ��˼�� 20210531
//���룺
//fAmax -- ����Ӱ��ϵ�����ֵ
//fTg   -- �������������(��)
//fKsi  -- �����
//fTerm -- ����(��)
//iMethod -- ����6��ʱ�ļ��㷽����0--ֱ�����������½��ι�ʽ��1--ȡ6��ʱ�ĺ㶨ֵ
extern "C" _SSG_DLLIMPEXP float DesignSpectrumIso(float fAmax,float fTg,float fKsi,float fTerm,int iMethod);


class _SSG_DLLIMPEXP CSpectrum
{
public:
	CSpectrum();
	~CSpectrum();

	//������
	int m_nTerm;		//Ƶ���������
	float m_fMaxTerm;	//������ڣ��룩
	float *m_pTerm;		//Ƶ���������������(��)
	float *m_pMaxDisp;	//Ƶ����������λ������
	float *m_pMaxVelo;	//Ƶ������������������
	float *m_pMaxAcce;	//Ƶ������������ٶ�����

	/*���㵥���ɶȷ�Ӧ��Ƶ�ʵ�(��Ӧһ������Ⱥ�һ������ԲƵ��)
	nPoints		-- ���𲨲�������
	dt			-- ���𲨲���������룩
	pEQAcce		-- ���𲨼��ٶȲ�����
	fOmiga		-- �����ɶ�ϵͳ����ԲƵ��
	fKsi		-- �����ɶ�ϵͳ�����
	fMaxDisp	-- ���λ��
	fMaxVelo	-- �������
	fMaxAcce	-- �����ٶ�
	*/
	void Response(
		int nPoints,float dt,const float *pEQAcce,
		float fTerm,float fKsi,
		float &fMaxDisp,float &fMaxVelo,float &fMaxAcce);

	/*���㵥���ɶȷ�Ӧ������
	nPoints		-- ����ʱ���������
	dt			-- ����ʱ�����������룩
	pEQAcce		-- ����ʱ����ٶȲ�����
	fDamp		-- �����ɶ�ϵͳ�����
	*/
	void CalcSpectrum(int nPoints,float dt,const float *pEQAcce,float fMaxTerm,float fTermDist,float fDamp);
};
